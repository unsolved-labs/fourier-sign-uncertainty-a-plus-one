# R012 canonical claim

## Exact result

Use the Fourier-transform normalization

$$
\widehat f(y)=\int_{\mathbb R} f(x)e^{-2\pi ixy}\,dx.
$$

Let $A_+(1)$ denote the one-dimensional Bourgain-Clozel-Kahane / Cohn-Goncalves sign-uncertainty constant in the $+1$ Fourier-eigenfunction formulation. R012 proves

$$
A_+(1)\leq \sqrt{\frac{1912071}{2000000\pi}}<0.551649.
$$

The proof is by an explicit degree-1800 Laguerre-Gaussian self-Fourier witness whose 900 integer coefficients are frozen in `coefficients/part1.txt` through `coefficients/part6.txt`. The released C++17 verifier reconstructs the witness exactly, certifies strict positivity for all $t\geq 1912071/1000000$, and proves the displayed decimal comparison by exact rational arithmetic.

## What the production machine check establishes

The production verifier checks, using exact integer/rational arithmetic:

1. the six coefficient files contain exactly 900 integers;
2. the scaled Laguerre recurrence reconstructs a degree-1800 integer polynomial $P$ with $P(0)=0$ and positive leading coefficient;
3. exact Bernstein-basis certificates prove $P(t)>0$ on the full finite interval from $T=1912071/1000000$ through $12000$;
4. the shifted power-basis coefficients prove $P(t)>0$ for every $t\geq12000$; and
5. an exact rational lower bound for $\pi$ proves $\sqrt{T/(2\pi)}<0.551649$.

The search process that found the coefficient vector is not part of the proof.

## Lean-verified bridge

The repository additionally contains a pinned Lean 4 / Mathlib partial formalization. The production declaration

`R012.r012_exact_and_decimal_bounds_from_certificate`

uses Mathlib's actual real Fourier transform and proves the certificate-to-radius logic and exact-radius/decimal inequalities under explicit hypotheses for:

- exact eventual positivity of the polynomial-side function;
- integrability and nontriviality of the Gaussian lift; and
- actual Fourier self-duality of the Gaussian lift.

Thus Lean checks the implication from those explicit obligations to the exact self-Fourier sign-radius bound and the strict `0.551649` comparison. The formal bridge is statement-checked with Comparator and subjected to trust-zero axiom auditing and fresh-kernel replay.

## Mathematical inputs still outside the full formal package

For the concrete 900-coefficient witness, the remaining principal mathematical inputs outside Lean are:

1. the generalized Laguerre-Gaussian Fourier eigenfunction identity at parameter $-1/2$ in the frozen normalization;
2. the proof that the concrete degree-1800 witness discharges the abstract Lean hypotheses, including full finite Bernstein positivity; and
3. identification of the release-specific self-Fourier infimum formalized in Lean with every alternate literature formulation of $A_+(1)$.

The complete finite certificate remains exactly machine checked by `verify.cpp`; it is not currently kernel-checked in Lean.

`STATEMENT_AUDIT.md` records this boundary claim by claim.

## Non-claims

R012 does **not** claim:

- the exact value of $A_+(1)$;
- a matching lower bound;
- optimality of the degree-1800 witness, even inside the chosen finite-dimensional Laguerre space;
- that the witness-generation/search procedure is verified;
- that a second implementation currently proves the full finite-interval Bernstein certificate independently;
- that the complete concrete R012 proof is fully formalized in Lean; or
- completed independent specialist review.

## Public status

- Exact explicit construction: **released**
- Production exact certificate replay: **available in CI and from a clean checkout**
- Independent implementation coverage: **partial; see `VERIFICATION.md`**
- Lean formalization: **partial certificate-to-bound bridge; see `formalization.yaml` and `VERIFICATION.md`**
- Independent specialist review: **pending**
