# R012 formal proof note

This note records the exact relationship between the mathematical manuscript, the exact computational certificate, and the partial Lean formalization.

## Public theorem

The mathematical release proves

$$
A_+(1)\leq\sqrt{\frac{1912071}{2000000\pi}}<0.551649.
$$

The complete released proof still has two complementary layers:

1. the C++ exact checker reconstructs the frozen degree-1800 polynomial and certifies positivity for every $t\geq1912071/1000000$;
2. the mathematical manuscript supplies the Laguerre-Gaussian Fourier eigenfunction argument and the sign-uncertainty interpretation.

## What Lean now proves

`R012.r012_decimal_bound_from_certificate` uses Mathlib's actual real Fourier transform to encode self-Fourier admissibility and proves the following implication.

Given a real function $p$ such that:

- $p(0)=0$;
- $p(t)\geq0$ for all $t\geq1912071/1000000$;
- its Gaussian lift $p(2\pi x^2)e^{-\pi x^2}$ is integrable and nonzero; and
- that Gaussian lift is self-Fourier under Mathlib's real Fourier transform,

Lean proves that the corresponding self-Fourier sign-radius infimum is at most $0.551649$. The proof includes the transfer from polynomial threshold to spatial radius and a rigorous Mathlib proof that

$$
\frac{1912071}{1000000}<2\pi\left(\frac{551649}{1000000}\right)^2.
$$

## What Lean does not yet prove

The package deliberately leaves the following as external obligations:

- the complete 900-coefficient Bernstein positivity certificate;
- the generalized Laguerre-Gaussian Fourier eigenfunction identity used by the concrete witness;
- the derivation that the concrete degree-1800 witness discharges the abstract `p` hypotheses; and
- equivalence between the release-specific self-Fourier infimum definition and every alternate literature formulation of $A_+(1)$.

The public repository therefore describes this as a **partial Lean bridge**, never as a full Lean proof of R012.

## Statement identity

The trusted statement is isolated in `Challenge.lean`. `Solution.lean` has the same declaration and delegates to the production theorem. Comparator configuration is in `comparator/r012_bridge.json`; the sole intentional `sorry` is confined to the challenge fixture.
