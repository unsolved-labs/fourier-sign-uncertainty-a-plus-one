# R012 formal proof note

This note records the exact relationship between the mathematical manuscript, the exact computational certificate, and the partial Lean formalization.

## Public theorem

The mathematical release proves

$$
A_+(1)\leq\sqrt{\frac{1912071}{2000000\pi}}<0.551649.
$$

The complete released proof still combines complementary layers:

1. the C++ exact checker reconstructs the frozen degree-1800 polynomial and certifies positivity for every $t\geq1912071/1000000$;
2. the mathematical manuscript supplies the concrete Laguerre-Gaussian Fourier eigenfunction argument and sign-uncertainty interpretation; and
3. the Lean package kernel-checks a substantial theorem-level certificate-to-radius bridge while leaving the concrete witness obligations explicit.

## What Lean proves

`R012.r012_exact_and_decimal_bounds_from_certificate` uses Mathlib's actual real Fourier transform to encode self-Fourier admissibility.

Given a real function $p$ such that:

- $p(0)=0$;
- $p(t)\geq0$ for all $t\geq1912071/1000000$;
- its Gaussian lift $p(2\pi x^2)e^{-\pi x^2}$ is integrable and nonzero; and
- that Gaussian lift is self-Fourier under Mathlib's real Fourier transform,

Lean proves

$$
A^{\mathrm{sf}}_+(1)
\leq\sqrt{\frac{1912071/1000000}{2\pi}}
<\frac{551649}{1000000},
$$

where $A^{\mathrm{sf}}_+(1)$ is the exact self-Fourier sign-radius infimum defined in `R012/Bridge.lean`.

The kernel-checked proof includes:

- witness-at-radius to infimum upper bound;
- transfer from polynomial positivity to Gaussian-lift nonnegativity outside a symmetric radius;
- the exact identity between the threshold and $2\pi r^2$ for the square-root radius; and
- the strict `0.551649` comparison using Mathlib's rigorous lower bound for $\pi$.

## What Lean does not yet prove

The package deliberately leaves the following as external obligations for the concrete release:

- the complete 900-coefficient Bernstein positivity certificate;
- the generalized Laguerre-Gaussian Fourier eigenfunction identity used by the concrete witness;
- the derivation that the concrete degree-1800 witness discharges the abstract positivity, integrability, nontriviality, and self-duality hypotheses; and
- equivalence between the release-specific self-Fourier infimum definition and every alternate literature formulation of $A_+(1)$.

The public repository therefore describes this as a **partial Lean bridge**, never as a full Lean proof of R012.

## Statement identity and trust boundary

The trusted combined statement is isolated in `Challenge.lean`. `Solution.lean` has the same declaration and delegates to the production theorem. Comparator configuration is in `comparator/r012_bridge.json`; the sole intentional `sorry` is confined to the challenge fixture.

Production Lean sources are scanned for proof shortcuts, audited at trust level zero, replayed with `leanchecker`, and checked through the immutable reusable release contract. The allowed axioms are only `propext`, `Classical.choice`, and `Quot.sound`.
