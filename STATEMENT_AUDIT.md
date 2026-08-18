# R012 statement audit

This file maps each public/load-bearing claim to its mathematical source and machine-verification boundary. It is the statement-identity layer for R012.

| Public claim | Mathematical basis | Machine evidence | Status / trust boundary |
|---|---|---|---|
| Fourier normalization is $\widehat f(y)=\int f(x)e^{-2\pi ixy}\,dx$ | Definition used throughout the release | Recorded in `verification-report.json` | Frozen convention |
| Witness is $f(x)=p(2\pi x^2)e^{-\pi x^2}$ with $p(t)=\sum_{k=1}^{900}N_k(L_{2k}^{-1/2}(t)-L_{2k}^{-1/2}(0))$ | Construction in `proof.md` / manuscript | `verify.cpp` loads exactly 900 integers and reconstructs the scaled polynomial | Exact data + standard Laguerre definition |
| $f(0)=0$ | Every Laguerre term is centered by its value at zero | `verify.cpp` requires reconstructed $P(0)=0$ | Exact integer check |
| $\widehat f=f$ | Standard Laguerre-Gaussian identity gives eigenvalue $(-1)^n$; only even $n=2k$ occur | Not proved inside C++; documented in proof/manuscript | Mathematical dependency; formalization target |
| $f$ is nonzero Schwartz | Polynomial times Gaussian; degree 1800 with positive leading coefficient | `verify.cpp` requires degree 1800 and positive leading coefficient | Mixed standard theorem + exact check |
| $P(t)>0$ for $T\le t\le12000$, $T=1912071/1000000$ | Positivity of Bernstein basis on $[0,1]$ plus exact affine changes and dyadic de Casteljau subdivision | `verify near`, all documented `verify range A B` shards, and CI | Exact integer certificate replay |
| $P(t)>0$ for $t\ge12000$ | Nonnegative shifted power-basis coefficients with positive constant term | `verify tail` | Exact integer check |
| Therefore $f(x)>0$ when $2\pi x^2\ge T$ | Gaussian factor is positive and $P$ is a positive scalar multiple of $p$ | Follows from exact positivity plus construction | Mathematical bridge stated in proof/manuscript |
| $A_+(1)\le\sqrt{T/(2\pi)}$ | Definition of the $+1$ sign-uncertainty constant applied to the admissible self-Fourier witness | Not encoded as a theorem in C++ | Mathematical dependency; formalization target |
| $\sqrt{T/(2\pi)}<0.551649$ | Rational arithmetic plus a rigorous lower bound for $\pi$ | `verify radius` | Exact rational check |
| Published comparison point is rigorous upper bound $0.594$ | Frozen prior-work citation `arXiv:1602.03366` | Source listed in proof/report | Literature/provenance dependency |
| R012 does not determine the exact value or prove witness optimality | Scope statement | `CLAIM.md`, README, report | Required non-claim |

## Production verification commands

```bash
./verify_release.sh
```

CI additionally shards the exact finite-interval replay in `.github/workflows/verify.yml`.

## Statement-control rule

Any future change to the README, manuscript, public release page, verifier, threshold, Fourier convention, or comparison baseline must update this file in the same pull request. Public wording must never imply a stronger theorem than the rows above support.
