# R012 statement audit

This file maps each public/load-bearing claim to its mathematical source and machine-verification boundary. It is the statement-identity layer for R012.

| Public claim | Mathematical basis | Machine/formal evidence | Status / trust boundary |
|---|---|---|---|
| Fourier normalization is $\widehat f(y)=\int f(x)e^{-2\pi ixy}\,dx$ | Definition used throughout the release | Recorded in `verification-report.json`; `R012.IsSelfFourier` uses Mathlib's real Fourier transform | Frozen convention; Lean bridge uses actual Fourier transform |
| Witness is $f(x)=p(2\pi x^2)e^{-\pi x^2}$ with $p(t)=\sum_{k=1}^{900}N_k(L_{2k}^{-1/2}(t)-L_{2k}^{-1/2}(0))$ | Construction in `proof.md` / manuscript | `verify.cpp` loads exactly 900 integers and reconstructs the scaled polynomial | Exact data + standard Laguerre definition; concrete coefficients not encoded in Lean |
| $f(0)=0$ | Every Laguerre term is centered by its value at zero | `verify.cpp` requires reconstructed $P(0)=0$; `R012.gaussianLift_zero` proves the abstract Gaussian-lift implication | Exact integer check + Lean bridge lemma |
| $\widehat f=f$ for the concrete witness | Generalized Laguerre-Gaussian identity gives eigenvalue $(-1)^n$; only even $n=2k$ occur | `R012.IsSelfFourier` is defined using Mathlib's actual Fourier transform, but concrete self-duality is an explicit hypothesis of the bridge | Concrete Laguerre identity remains outside Lean |
| $f$ is nonzero Schwartz/integrable | Polynomial times Gaussian; degree 1800 with positive leading coefficient | `verify.cpp` checks degree/leading sign; Lean bridge takes nontriviality and integrability as explicit hypotheses | Mixed standard theorem + exact check; concrete discharge not yet formalized |
| $P(t)>0$ for $T\le t\le12000$, $T=1912071/1000000$ | Positivity of Bernstein basis on $[0,1]$ plus exact affine changes and dyadic de Casteljau subdivision | `verify near`, all `verify range A B` shards, and CI | Exact integer certificate replay; not currently kernel-checked in Lean |
| $P(t)>0$ for $t\ge12000$ | Nonnegative shifted power-basis coefficients with positive constant term | `verify tail`; independent partial Python replay | Exact integer checks in two implementations |
| Polynomial positivity transfers to Gaussian-witness nonnegativity outside a radius | Positive Gaussian factor and monotonicity of $x^2$ in $|x|$ | `R012.gaussianLift_nonnegative_outside` | Lean-verified abstract bridge |
| Exact threshold radius is $\sqrt{T/(2\pi)}$ | Algebra and positivity of $2\pi$ | `R012.threshold_eq_scale_exact` and `R012.r012_exact_bound_from_certificate` | Lean-verified under explicit witness hypotheses |
| Self-Fourier admissible witness at radius $r$ bounds the release-specific self-Fourier infimum | Definition of `R012.APlusOneSelfFourier` | `R012.APlusOneSelfFourier_le_of_radius` | Lean-verified for the precise formalized self-Fourier formulation |
| $A^{\mathrm{sf}}_+(1)\le\sqrt{T/(2\pi)}<0.551649$ under the bridge hypotheses | Previous two rows plus rigorous $\pi$ bound | `R012.r012_exact_and_decimal_bounds_from_certificate`; `R012.exactRadius_lt_decimal` | Lean-verified partial theorem; Comparator statement boundary |
| Public concrete claim $A_+(1)\le\sqrt{T/(2\pi)}<0.551649$ | Concrete Laguerre witness + exact certificate + mathematical/formal bridge | C++ full certificate, manuscript, partial Lean bridge | Full concrete theorem is not yet wholly Lean-formalized |
| Published comparison point is rigorous upper bound $0.594$ | Frozen prior-work citation `arXiv:1602.03366` | `SOURCE_AUDIT.md` | Literature/provenance dependency |
| R012 does not determine the exact value or prove witness optimality | Scope statement | `CLAIM.md`, README, report | Required non-claim |

## Production verification commands

Complete exact certificate replay:

```bash
./verify_release.sh
```

Independent partial exact replay:

```bash
python3 verify_independent.py
```

Pinned Lean bridge:

```bash
lake exe cache get
lake build R012 Challenge Solution R012.Audit
lake env lean --trust=0 R012/Audit.lean
```

CI additionally shards the finite-interval replay, rebuilds the manuscript, performs the Lean trust-zero and fresh-kernel checks, and invokes the immutable reusable release contract.

## Formal statement boundary

The trusted Comparator theorem is `r012_exact_and_decimal_bounds_from_certificate` in `Challenge.lean`; its production counterpart is `R012.r012_exact_and_decimal_bounds_from_certificate` in `R012/Bridge.lean`. `Challenge.lean` contains the sole intentional formalization `sorry`; production sources contain none.

`formalization.yaml` is authoritative for the precise partial-formalization scope. It must not be interpreted as asserting Lean verification of the concrete coefficient certificate or generalized Laguerre-Gaussian Fourier identity.

## Statement-control rule

Any future change to the README, manuscript, public release page, verifier, formalization, threshold, Fourier convention, or comparison baseline must update this file in the same pull request. Public wording must never imply a stronger theorem than the rows above support.
