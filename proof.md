# Certified upper bound for the one-dimensional +1 Fourier sign-uncertainty constant

For the full paper, see [`manuscript/r012_fourier_sign_uncertainty.tex`](manuscript/r012_fourier_sign_uncertainty.tex) and its reproducible build instructions. The exact public statement is frozen in [`CLAIM.md`](CLAIM.md), and [`STATEMENT_AUDIT.md`](STATEMENT_AUDIT.md) maps each load-bearing step to the machine/formal verification boundary.

## Frozen theorem

Use

$$
\widehat f(y)=\int_{\mathbb R} f(x)e^{-2\pi ixy}\,dx.
$$

Let $A_+(1)$ be the one-dimensional Bourgain-Clozel-Kahane / Cohn-Goncalves sign-uncertainty constant in the $+1$ Fourier-eigenfunction formulation. Then

$$
\boxed{A_+(1)\leq \sqrt{\frac{1912071}{2000000\pi}}<0.551649.}
$$

The approximate radius `0.551648031984764...` is displayed for orientation only; floating-point arithmetic is not proof evidence.

## Construction

Let $L_n^{-1/2}$ denote the generalized Laguerre polynomial and define

$$
p(t)=\sum_{k=1}^{900}N_k\left(L_{2k}^{-1/2}(t)-L_{2k}^{-1/2}(0)\right),
\qquad
f(x)=p(2\pi x^2)e^{-\pi x^2},
$$

where the 900 integers $N_k$ are frozen in `coefficients/part1.txt` through `coefficients/part6.txt`.

By construction $p(0)=f(0)=0$. The standard Laguerre-Gaussian Fourier identity gives

$$
\mathcal F\!\left[L_n^{-1/2}(2\pi x^2)e^{-\pi x^2}\right]
=(-1)^nL_n^{-1/2}(2\pi x^2)e^{-\pi x^2}.
$$

Only even indices $n=2k$ occur, hence $\widehat f=f$. The reconstructed polynomial has degree 1800 and positive leading coefficient, so $f$ is nonzero; polynomial times Gaussian is Schwartz.

It remains to certify eventual positivity.

## Exact positivity certificate

Set

$$
T=\frac{1912071}{1000000}=1.912071.
$$

The production verifier uses the integer-scaled Laguerre polynomials

$$
R_n(t)=2^n n!L_n^{-1/2}(t)
$$

with recurrence

$$
R_0=1,\qquad R_1=1-2t,
$$

$$
R_{n+1}=(4n+1-2t)R_n-2n(2n-1)R_{n-1}.
$$

From these data it reconstructs an exact integer polynomial $P(t)$ that is a positive scalar multiple of $p(t)$. It requires $P(0)=0$, degree 1800, and positive leading coefficient.

### Finite region

For each rational interval, `verify.cpp` applies an exact affine substitution to `[0,1]`, converts the polynomial to a scaled Bernstein basis, and recursively performs dyadic de Casteljau subdivision until every Bernstein coefficient on every leaf is strictly positive. Since Bernstein basis functions are nonnegative on `[0,1]`, this proves positivity on the whole interval rather than at sampled points.

The production replay covers the complete interval

$$
[T,12000].
$$

The block partition in `verify_release.sh` and CI is only an operational partition; it does not alter the theorem or polynomial.

### Infinite tail

The verifier expands

$$
P(12000+u)=\sum_{j=0}^{1800}d_ju^j
$$

and checks $d_0>0$ and $d_j\geq0$ for every $j$. Thus $P(t)>0$ for all $t\geq12000$.

Consequently

$$
p(t)>0\qquad(t\geq T),
$$

so

$$
f(x)>0\qquad\text{whenever}\qquad2\pi x^2\geq T.
$$

Therefore

$$
A_+(1)\leq\sqrt{\frac{T}{2\pi}}
=\sqrt{\frac{1912071}{2000000\pi}}.
$$

The verifier proves the comparison with `0.551649` using a rational lower bound for $\pi$ derived from Machin's identity and alternating arctangent series.

## Independent exact partial replay

`verify_independent.py` is a separately written Python implementation. It independently parses all six coefficient files, reconstructs the degree-1800 scaled polynomial, verifies the translated infinite-tail coefficient certificate, and proves the radius comparison using exact `Fraction` arithmetic.

It does **not** duplicate the complete finite Bernstein subdivision. That limitation is deliberate and public; the finite interval proof currently has one production implementation.

## Partial Lean bridge

The repository contains a pinned Lean 4 / Mathlib formalization of the certificate-to-bound bridge. `R012.IsSelfFourier` uses Mathlib's actual real Fourier transform. The main theorem

`R012.r012_exact_and_decimal_bounds_from_certificate`

proves, from explicit hypotheses of polynomial-side eventual positivity, Gaussian-lift integrability/nontriviality, and actual Fourier self-duality, that the formalized self-Fourier sign-radius infimum satisfies

$$
A^{\mathrm{sf}}_+(1)\leq
\sqrt{\frac{T}{2\pi}}<0.551649.
$$

Lean also checks the exact rescaling identity and the strict decimal comparison using Mathlib's rigorous $\pi$ bound. The formal statement is isolated in `Challenge.lean` and checked against `Solution.lean` by Comparator; production Lean sources contain no `sorry` or `admit`.

This is not a full Lean proof of the concrete R012 witness. The concrete 900-coefficient finite Bernstein certificate and generalized Laguerre-Gaussian Fourier identity remain outside the Lean kernel boundary. See [`manuscript/proof_note.md`](manuscript/proof_note.md) and [`VERIFICATION.md`](VERIFICATION.md).

## Baseline and novelty boundary

The frozen rigorous comparison is the one-dimensional upper bound `0.594` from:

- https://arxiv.org/abs/1602.03366

Later work reports substantially sharper numerical phenomena while separating numerical evidence from rigorous proof:

- https://arxiv.org/abs/2003.10771

The novelty claim is intentionally narrow: an explicit, exactly certified construction proving the displayed `0.551649` upper bound.

## Trust boundary

The search that found the coefficient vector is not part of the proof. The public claim depends on:

1. the generalized Laguerre-Gaussian Fourier eigenfunction identity for the concrete witness;
2. the 900 frozen integer coefficients;
3. exact reconstruction and positivity/radius checks in `verify.cpp`; and
4. the definition-to-bound bridge, now partially kernel-checked in Lean with the remaining concrete-witness obligations explicit.

The production checker contains no optimizer and does not trust sampled positivity or floating-point root finding. The Lean package does not hide the remaining mathematical dependencies as axioms or opaque declarations.

## Limitations

- Upper bound only; the exact value of $A_+(1)$ is not determined.
- No matching lower bound is supplied.
- The degree-1800 witness is not claimed optimal, even in its finite Laguerre space.
- The coefficient search is not part of the verified proof.
- The finite Bernstein certificate currently has one production implementation.
- The Lean verification is a partial bridge, not a full formalization of the concrete witness.
- Independent specialist review remains pending.
