// R012 exact verifier: A_+(1) <= sqrt(1912071/(2000000*pi)) < 0.551649.
// C++17 + Boost headers. All proof checks use exact integer/rational arithmetic.
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/rational.hpp>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using boost::multiprecision::cpp_int;
using Poly=std::vector<cpp_int>;
constexpr int N=900, DEGREE=1800, T_NUM=1912071, T_DEN=1000000, TAIL_START=12000;

static void trim(Poly& p){while(p.size()>1&&p.back()==0)p.pop_back();}

static std::vector<long long> load_numerators(){
  std::vector<long long> v; v.reserve(N);
  for(int part=1;part<=6;++part){
    std::ifstream in("coefficients/part"+std::to_string(part)+".txt");
    if(!in) throw std::runtime_error("missing coefficient file");
    long long x; while(in>>x)v.push_back(x);
    if(!in.eof()) throw std::runtime_error("invalid coefficient file");
  }
  if((int)v.size()!=N) throw std::runtime_error("expected 900 coefficients");
  return v;
}

// R_n(t)=2^n n! L_n^{-1/2}(t).
// R_{n+1}=(4n+1-2t)R_n-2n(2n-1)R_{n-1}.
static Poly build_integer_polynomial(){
  const auto num=load_numerators();
  Poly p(1,0), r0{cpp_int(1)}, r1{cpp_int(1),cpp_int(-2)};
  cpp_int fact=1; for(int j=2;j<=DEGREE;++j)fact*=j;
  cpp_int factor=(cpp_int(1)<<DEGREE)*fact;
  for(int n=1;n<=DEGREE;++n){
    factor/=(2*n);
    if(n>=2){
      const int j=n-1; Poly next(r1.size()+1,0); const long long a=4LL*j+1;
      for(size_t i=0;i<r1.size();++i){next[i]+=a*r1[i];next[i+1]-=2*r1[i];}
      const long long b=2LL*j*(2LL*j-1);
      for(size_t i=0;i<r0.size();++i)next[i]-=b*r0[i];
      r0.swap(r1);r1.swap(next);
    }
    if((n&1)==0){
      const int k=n/2; const cpp_int scale=factor*num[k-1];
      if(p.size()<r1.size())p.resize(r1.size(),0);
      // Omitting the constant term exactly implements L_{2k}(t)-L_{2k}(0).
      for(size_t i=1;i<r1.size();++i)p[i]+=scale*r1[i];
    }
  }
  trim(p);
  if((int)p.size()!=DEGREE+1||p[0]!=0||p.back()<=0)
    throw std::runtime_error("witness reconstruction failed");
  return p;
}

static Poly shift_polynomial(const Poly& p,int a){
  Poly q{p.back()};
  for(size_t rev=1;rev<p.size();++rev){
    const cpp_int& c=p[p.size()-1-rev]; Poly next(q.size()+1,0);
    for(size_t j=0;j<q.size();++j){next[j]+=a*q[j];next[j+1]+=q[j];}
    next[0]+=c; q.swap(next);
  }
  trim(q); return q;
}

// Positive multiple of p(a/d + (b-a/d)y), 0<=y<=1.
static Poly affine_polynomial(const Poly& p,int a,int d,int b){
  const int n=(int)p.size()-1, span=d*b-a; Poly q{p.back()}; cpp_int dp=1;
  for(int j=n-1;j>=0;--j){
    dp*=d; Poly next(q.size()+1,0);
    for(size_t i=0;i<q.size();++i){next[i]+=a*q[i];next[i+1]+=span*q[i];}
    next[0]+=p[j]*dp; q.swap(next);
  }
  return q;
}

// Returns n! times the Bernstein coefficients, preserving signs.
static Poly power_to_scaled_bernstein(const Poly& q){
  const int n=(int)q.size()-1; std::vector<cpp_int> fact(n+1); fact[0]=1;
  for(int i=1;i<=n;++i)fact[i]=fact[i-1]*i;
  Poly c(n+1); for(int j=0;j<=n;++j)c[j]=q[j]*fact[j]*fact[n-j];
  for(int stage=1;stage<=n;++stage)for(int j=n;j>=stage;--j)c[j]+=c[j-1];
  return c;
}

static std::pair<Poly,Poly> split_midpoint(Poly w){
  const int n=(int)w.size()-1; Poly l(n+1),r(n+1); l[0]=w[0]<<n; r[n]=w[n]<<n;
  for(int level=1;level<=n;++level){
    const int len=n-level+1; for(int i=0;i<len;++i)w[i]+=w[i+1];
    const int s=n-level; l[level]=w[0]<<s; r[n-level]=w[len-1]<<s;
  }
  return {std::move(l),std::move(r)};
}
static bool all_positive(const Poly& c){for(const auto&x:c)if(x<=0)return false;return true;}
static std::tuple<int,int,int> certify(Poly root,int max_depth=55){
  struct Node{Poly c;int d;}; std::vector<Node> st; st.push_back({std::move(root),0});
  int leaves=0,nodes=0,deep=0;
  while(!st.empty()){
    Node n=std::move(st.back());st.pop_back();++nodes;deep=std::max(deep,n.d);
    if(all_positive(n.c)){++leaves;continue;}
    if(n.d>=max_depth)throw std::runtime_error("Bernstein certificate exceeded depth");
    auto ch=split_midpoint(std::move(n.c));
    st.push_back({std::move(ch.second),n.d+1});st.push_back({std::move(ch.first),n.d+1});
  }
  return {leaves,nodes,deep};
}

static int check_interval(int a,int d,int b,const std::string& label){
  Poly p=build_integer_polynomial(); Poly q=affine_polynomial(p,a,d,b); Poly c=power_to_scaled_bernstein(q);
  auto [l,n,z]=certify(std::move(c));
  std::cout<<"PASS "<<label<<" "<<l<<"/"<<n<<"/"<<z<<"\n"; return 0;
}
static int check_tail(){
  Poly p=build_integer_polynomial(), tail=shift_polynomial(p,TAIL_START);
  if(tail[0]<=0)throw std::runtime_error("tail constant not positive");
  for(const auto&x:tail)if(x<0)throw std::runtime_error("negative tail coefficient");
  Poly q=affine_polynomial(tail,-500,1,0), c=power_to_scaled_bernstein(q);
  auto [l,n,z]=certify(std::move(c),30);
  std::cout<<"PASS tail [11500,12000] and [12000,infinity) "<<l<<"/"<<n<<"/"<<z<<"\n";return 0;
}
static bool lessq(long long an,long long ad,long long bn,long long bd){return cpp_int(an)*bd<cpp_int(bn)*ad;}
static int check_radius(){
  using Q=boost::rational<long long>;
  const Q a5=Q(1,5)-Q(1,3*5*5*5)+Q(1,5*5*5*5*5*5)-Q(1,7*5*5*5*5*5*5*5);
  const Q pil=16*a5-4*Q(1,239);
  if(!lessq(333,106,pil.numerator(),pil.denominator()))throw std::runtime_error("pi lower bound failed");
  const cpp_int lhs=cpp_int(T_NUM)*pil.denominator()*1000000LL*1000000LL;
  const cpp_int rhs=cpp_int(T_DEN)*2*pil.numerator()*551649LL*551649LL;
  if(!(lhs<rhs))throw std::runtime_error("radius comparison failed");
  long double r=std::sqrt((static_cast<long double>(T_NUM)/T_DEN)/(2.0L*std::acos(-1.0L)));
  std::cout.precision(15);std::cout<<std::fixed<<"PASS radius "<<r<<" < 0.551649\n";return 0;
}
int main(int argc,char**argv){
  try{
    if(argc==2&&std::string(argv[1])=="near")return check_interval(T_NUM,T_DEN,2,"[T,2]");
    if(argc==2&&std::string(argv[1])=="tail")return check_tail();
    if(argc==2&&std::string(argv[1])=="radius")return check_radius();
    if(argc==4&&std::string(argv[1])=="range"){
      int a=std::stoi(argv[2]),b=std::stoi(argv[3]);if(!(a<b))throw std::runtime_error("bad range");
      return check_interval(a,1,b,"["+std::to_string(a)+","+std::to_string(b)+"]");
    }
    std::cerr<<"usage: verify near|tail|radius | verify range A B\n";return 2;
  }catch(const std::exception&e){std::cerr<<"VERIFICATION FAILED: "<<e.what()<<"\n";return 1;}
}
