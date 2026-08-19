# R012 — One-dimensional Fourier sign-uncertainty upper bound

**Unsolved Labs Research Release R012**

R012 gives an explicit, exactly certified Fourier-invariant Schwartz witness proving

$$
A_+(1)\leq \sqrt{\frac{1912071}{2000000\pi}}<0.551649
$$

under the normalization

$$
\widehat f(y)=\int_{\mathbb R} f(x)e^{-2\pi ixy}\,dx.
$$

The witness is a degree-1800 Laguerre-Gaussian combination with 900 frozen integer coefficients. The search that found those coefficients is **not** part of the proof: the public theorem is replayed from frozen data using exact integer/rational arithmetic.

## Why this matters

The rigorous one-dimensional comparison used by this release is the published upper bound `0.594` from arXiv:1602.03366. R012 replaces that comparison point by an explicit certificate below `0.551649` while keeping a deliberately narrow claim boundary.

This release does **not** determine the exact value of $A_+(1)$, provide a matching lower bound, or prove that the degree-1800 witness is optimal.

## Paper

- [LaTeX manuscript source](manuscript/r012_fourier_sign_uncertainty.tex)
- [Reproducible manuscript build instructions](manuscript/README.md)
- [Concise GitHub-rendered proof companion](proof.md)
- [Formal proof note](manuscript/proof_note.md)

Run `make` in `manuscript/` to produce `r012_fourier_sign_uncertainty.pdf`. CI rebuilds the PDF from the canonical LaTeX source on every push and pull request; the generated PDF is treated as a build artifact rather than a separately edited source of truth.

## Verification

### Complete production replay

Requirements: a C++17 compiler and Boost headers.

```bash
./verify_release.sh
```

The production checker `verify.cpp`:

1. parses exactly 900 frozen integer coefficients;
2. reconstructs the degree-1800 scaled Laguerre polynomial exactly;
3. proves strict positivity on the complete finite interval $[1912071/1000000,12000]$ by exact Bernstein-basis subdivision;
4. proves positivity on $[12000,\infty)$ from nonnegative shifted power-basis coefficients; and
5. proves the strict comparison with `0.551649` using exact rational arithmetic and a rigorous lower bound for $\pi$.

No optimizer, sampled positivity test, or floating-point root finder is part of the proof boundary.

### Independent exact partial replay

```bash
python3 verify_independent.py
```

The separately written Python implementation independently reconstructs the witness, checks the infinite-tail certificate, and proves the radius comparison with unbounded integers / `Fraction`. It intentionally does **not** duplicate the complete finite Bernstein subdivision, so the repository does not overstate this as a fully independent second proof.

### Lean certificate-to-bound bridge

R012 also contains a pinned Lean 4 / Mathlib **partial formalization** of the theorem-level bridge:

```bash
lake exe cache get
lake build R012 Challenge Solution R012.Audit
lake env lean --trust=0 R012/Audit.lean
```

The main production declaration is

`R012.r012_exact_and_decimal_bounds_from_certificate`.

Under explicit hypotheses for the externally certified positivity of $p$, integrability and nontriviality of its Gaussian lift, and actual Mathlib Fourier self-duality, Lean proves

$$
A^{\mathrm{sf}}_+(1)\leq
\sqrt{\frac{1912071/1000000}{2\pi}}
<\frac{551649}{1000000}.
$$

Here $A^{\mathrm{sf}}_+(1)$ denotes the precise self-Fourier sign-radius infimum defined in `R012/Bridge.lean`. `IsSelfFourier` uses Mathlib's actual real Fourier transform, not an uninterpreted proposition.

The Lean package does **not** formalize the full 900-coefficient Bernstein certificate, the generalized Laguerre-Gaussian Fourier eigenfunction identity for the concrete witness, or equivalence with every alternative literature formulation of $A_+(1)$. It must therefore be described as a partial formal bridge, not a full Lean proof of R012.

The Lean package is pinned to Lean 4.32.0 and Mathlib commit `81a5d257c8e410db227a6665ed08f64fea08e997`. Its trust boundary includes a production-source shortcut scan, trust-zero axiom audit, fresh-kernel replay, Comparator challenge/solution check, and the immutable reusable release contract at commit `db99fd22330138ca6f2effe6eaf4088d8e7a7b07`.

See [VERIFICATION.md](VERIFICATION.md) for the precise trust boundary and [STATEMENT_AUDIT.md](STATEMENT_AUDIT.md) for claim-by-claim correspondence.

## Repository map

- `CLAIM.md` — canonical theorem and explicit non-claims
- `STATEMENT_AUDIT.md` — public claim → manuscript → checker/formalization dependency map
- `VERIFICATION.md` — clean-checkout commands, trust boundary, data identity
- `SOURCE_AUDIT.md` / `NOVELTY_AUDIT.md` — literature, provenance, and formalization-scope controls
- `proof.md` — GitHub-rendered proof companion
- `manuscript/` — reproducible LaTeX paper source, proof note, and build instructions
- `verify.cpp` — complete production exact certificate checker
- `verify_independent.py` — independent exact reconstruction/tail/radius checker
- `R012/` and `R012.lean` — production Lean bridge and trust-zero audit
- `Challenge.lean` / `Solution.lean` — isolated Comparator statement boundary
- `formalization.yaml` — machine-readable v0.3 formalization scope and trust metadata
- `comparator/r012_bridge.json` — Comparator configuration
- `campaign/claim_mapping.json` — formal claim/declaration mapping
- `coefficients/` — frozen 900-integer witness
- `verify_release.sh` — one-command complete production replay
- `verification-report.json` — machine-readable frozen claim
- `.github/workflows/verify.yml` — sharded production certificate CI
- `.github/workflows/lean.yml` — pinned Lean build, axiom audit, and kernel replay
- `.github/workflows/release-contract.yml` — immutable reusable release contract
- `.github/workflows/release-quality.yml` — independent replay, manuscript build, and public-boundary checks
- `CITATION.cff` — citation metadata
- `LICENSE` — public research-artifact rights notice

## Claim boundary

The exact public claim is frozen in [CLAIM.md](CLAIM.md). In particular:

- **proved:** an explicit upper bound $A_+(1)\leq\sqrt{1912071/(2000000\pi)}<0.551649$;
- **not proved:** the exact value of $A_+(1)$;
- **not supplied:** a matching lower bound;
- **not claimed:** optimality of the witness or verification of the coefficient search;
- **Lean:** the certificate-to-exact-radius and decimal-comparison bridge is formalized conditionally on explicit witness obligations; the concrete full R012 proof is not fully formalized;
- **independent specialist review:** pending.

## Reproducibility and AI-generation disclosure

This is an AI-generated research artifact released by Unsolved Labs with an artifact-based verification boundary. The theorem is intended to be auditable from the public witness, manuscript source, exact checkers, partial Lean bridge, and pinned repository history; private model conversations or hidden reasoning traces are not part of the evidence.

## Public release page

https://unsolved-labs.github.io/results/r012-fourier-sign-uncertainty/
