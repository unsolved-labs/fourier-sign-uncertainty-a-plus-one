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

## What the machine check establishes

The production verifier checks, using exact integer/rational arithmetic:

1. the six coefficient files contain exactly 900 integers;
2. the scaled Laguerre recurrence reconstructs a degree-1800 integer polynomial $P$ with $P(0)=0$ and positive leading coefficient;
3. exact Bernstein-basis certificates prove $P(t)>0$ on the full finite interval from $T=1912071/1000000$ through $12000$;
4. the shifted power-basis coefficients prove $P(t)>0$ for every $t\geq12000$; and
5. an exact rational lower bound for $\pi$ proves
   $\sqrt{T/(2\pi)}<0.551649$.

The search process that found the coefficient vector is not part of the proof.

## Mathematical inputs outside the production checker

The final implication from the certified polynomial inequalities to the sign-uncertainty bound uses standard mathematical facts stated explicitly in `proof.md` and the manuscript, most importantly the Laguerre-Gaussian Fourier eigenfunction identity for parameter $-1/2$ and the definition of $A_+(1)$.

`STATEMENT_AUDIT.md` records this boundary claim by claim.

## Non-claims

R012 does **not** claim:

- the exact value of $A_+(1)$;
- a matching lower bound;
- optimality of the degree-1800 witness, even inside the chosen finite-dimensional Laguerre space;
- that the witness-generation/search procedure is verified;
- that a second implementation currently proves the full finite-interval Bernstein certificate independently; or
- completed independent specialist review.

## Public status

- Exact explicit construction: **released**
- Production exact certificate replay: **available in CI and from a clean checkout**
- Independent implementation coverage: **partial; see `VERIFICATION.md`**
- Proof-assistant formalization: **not currently part of the release; see `VERIFICATION.md`**
- Independent specialist review: **pending**
