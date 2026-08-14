# Certified upper bound for the one-dimensional +1 Fourier sign-uncertainty constant

## Frozen theorem

Use

\[
\widehat f(y)=\int_{\mathbb R} f(x)e^{-2\pi ixy}\,dx.
\]

Let `A_+(1)` be the one-dimensional Bourgain–Clozel–Kahane/Cohn–Gonçalves sign-uncertainty constant in the `+1` Fourier-eigenfunction formulation. Then

\[
\boxed{A_+(1)\leq \sqrt{\frac{1912071}{2000000\pi}}<0.551649.}
\]

Numerically, the certified radius is

\[
0.551648031984764\ldots.
\]

## Construction

Let `L_n^{-1/2}` denote the generalized Laguerre polynomial and define

\[
p(t)=\sum_{k=1}^{900} N_k\left(L_{2k}^{-1/2}(t)-L_{2k}^{-1/2}(0)\right),
\qquad
f(x)=p(2\pi x^2)e^{-\pi x^2},
\]

where the 900 integer coefficients `N_k` are frozen verbatim in `coefficients/part1.txt` through `coefficients/part6.txt`.

By construction `p(0)=f(0)=0`. The standard Laguerre–Gaussian Fourier identity gives

\[
\mathcal F\left[L_n^{-1/2}(2\pi x^2)e^{-\pi x^2}\right]
=(-1)^nL_n^{-1/2}(2\pi x^2)e^{-\pi x^2}.
\]

Only even indices `n=2k` occur, hence `\widehat f=f`. The polynomial has degree 1800 and positive leading coefficient, so `f` is nonzero; being a polynomial times a Gaussian, it is Schwartz.

Therefore it remains only to certify eventual nonnegativity at the claimed radius.

## Exact positivity certificate

Set

\[
T=\frac{1912071}{1000000}=1.912071.
\]

The verifier uses the integer-scaled Laguerre polynomials

\[
R_n(t)=2^n n!L_n^{-1/2}(t),
\]

with recurrence

\[
R_0=1,\qquad R_1=1-2t,
\]

\[
R_{n+1}=(4n+1-2t)R_n-2n(2n-1)R_{n-1}.
\]

From these it reconstructs an exact integer polynomial `P(t)` that is a positive scalar multiple of `p(t)`. It checks `P(0)=0`, degree 1800, and positive leading coefficient.

For each finite interval, `verify.cpp` applies an exact affine substitution to `[0,1]`, converts the polynomial to a scaled Bernstein basis, and recursively performs dyadic de Casteljau subdivision until every Bernstein coefficient is strictly positive. Since Bernstein basis functions are nonnegative on `[0,1]`, this proves strict positivity on every certified interval.

The release replay covers the complete interval

\[
[T,12000]
\]

with exact Bernstein certificates. The wide numerical region `[100,1000]` is intentionally split into 100-unit blocks to keep exact arithmetic tractable; this is only a verifier partition and does not change the polynomial or theorem.

For the infinite tail, the verifier expands

\[
P(12000+u)=\sum_{j=0}^{1800}d_ju^j
\]

and checks `d_0>0` and `d_j\geq0` for every `j`. Thus `P(t)>0` for all `t\geq12000`.

Consequently

\[
p(t)>0\quad(t\geq T),
\]

so

\[
f(x)>0\quad\text{whenever}\quad 2\pi x^2\geq T.
\]

Therefore

\[
A_+(1)\leq\sqrt{\frac{T}{2\pi}}
=\sqrt{\frac{1912071}{2000000\pi}}.
\]

The verifier also proves the comparison with `0.551649` using a rational lower bound for `\pi` derived from Machin's identity and alternating arctangent series. No floating-point number is used as evidence for the theorem.

## Baseline and novelty boundary

The 2016 paper of Gonçalves, Oliveira e Silva, and Steinerberger proves the rigorous one-dimensional bound `0.45 <= A_+(1) <= 0.594` in the self-Fourier formulation and constructs the upper-bound witness:

- https://arxiv.org/abs/1602.03366

Later sign-uncertainty work reports numerical evidence and conjectural structure substantially below `0.594`, but explicitly separates those computations from rigorous proof:

- https://arxiv.org/abs/2003.10771

The novelty claim of this release is deliberately narrow: an explicit, exactly certified construction proving the displayed `0.551649` upper bound. It does not claim the exact value of `A_+(1)`.

A primary-source search through 2026-08-14 did not locate a published rigorous one-dimensional upper bound below `0.594`. Independent specialist review remains pending.

## Trust boundary

The generated search that found the coefficient vector is not part of the proof. The public claim depends only on:

1. the standard Laguerre–Gaussian Fourier eigenfunction identity;
2. the 900 frozen integer coefficients in `coefficients/`;
3. exact integer/rational reconstruction and Bernstein positivity checks in `verify.cpp`; and
4. exact rational verification of the numerical radius comparison.

The verifier contains no optimizer and does not trust sampled positivity or floating-point root finding.

## Limitations

- The result is an upper bound, not an exact determination of `A_+(1)`.
- No matching lower bound is supplied.
- The degree-1800 witness is not claimed to be optimal even within its finite-dimensional Laguerre space.
- Stronger numerical candidates from the research campaign are excluded from this release because they do not have a complete exact replay.
- Independent specialist review is pending.
