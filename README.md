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

The witness is a degree-1800 Laguerre-Gaussian combination with 900 frozen integer coefficients. The search that found those coefficients is **not** part of the proof: the public theorem is replayed from the frozen data using exact integer/rational arithmetic.

## Why this matters

The rigorous one-dimensional comparison used by this release is the published upper bound `0.594` from arXiv:1602.03366. R012 replaces that comparison point by an explicit certificate below `0.551649` while keeping a deliberately narrow claim boundary.

This release does **not** determine the exact value of $A_+(1)$, provide a matching lower bound, or prove that the degree-1800 witness is optimal.

## Paper

- [Typeset proof manuscript](manuscript/r012_fourier_sign_uncertainty.pdf)
- [LaTeX source](manuscript/r012_fourier_sign_uncertainty.tex)
- [Concise proof companion](proof.md)

The manuscript explains the mathematical reduction, exact certificate architecture, trust boundary, prior-work comparison, limitations, and reproducibility path.

## Verification

### Complete production replay

Requirements: a C++17 compiler and Boost headers.

```bash
./verify_release.sh
```

The production checker `verify.cpp`:

1. parses exactly 900 frozen integer coefficients;
2. reconstructs the degree-1800 scaled Laguerre polynomial exactly;
3. proves strict positivity on the complete finite interval
   $[1912071/1000000,12000]$ by exact Bernstein-basis subdivision;
4. proves positivity on $[12000,\infty)$ from nonnegative shifted power-basis coefficients; and
5. proves the strict comparison with `0.551649` using exact rational arithmetic and a rigorous lower bound for $\pi$.

No optimizer, sampled positivity test, or floating-point root finder is part of the proof boundary.

### Independent exact partial replay

```bash
python3 verify_independent.py
```

The separately written Python implementation independently reconstructs the witness, checks the infinite-tail certificate, and proves the radius comparison with unbounded integers / `Fraction`. It intentionally does **not** duplicate the complete finite Bernstein subdivision, so the repository does not overstate this as a fully independent second proof.

See [VERIFICATION.md](VERIFICATION.md) for the precise trust boundary and [STATEMENT_AUDIT.md](STATEMENT_AUDIT.md) for claim-by-claim correspondence.

## Repository map

- `CLAIM.md` — canonical theorem and explicit non-claims
- `STATEMENT_AUDIT.md` — public claim → manuscript → checker dependency map
- `VERIFICATION.md` — clean-checkout commands, trust boundary, data identity
- `proof.md` — GitHub-rendered proof companion
- `manuscript/` — reproducible LaTeX paper and PDF
- `verify.cpp` — complete production exact certificate checker
- `verify_independent.py` — independent exact reconstruction/tail/radius checker
- `coefficients/` — frozen 900-integer witness
- `verify_release.sh` — one-command complete production replay
- `verification-report.json` — machine-readable frozen claim
- `.github/workflows/verify.yml` — sharded production CI replay
- `.github/workflows/release-quality.yml` — independent replay and manuscript build checks
- `CITATION.cff` — citation metadata

## Claim boundary

The exact public claim is frozen in [CLAIM.md](CLAIM.md). In particular:

- **proved:** an explicit upper bound
  $A_+(1)\leq\sqrt{1912071/(2000000\pi)}<0.551649$;
- **not proved:** the exact value of $A_+(1)$;
- **not supplied:** a matching lower bound;
- **not claimed:** optimality of the witness or verification of the coefficient search;
- **formal proof assistant:** not currently part of this release; the analytic bridge is identified as a future formalization target in `VERIFICATION.md`;
- **independent specialist review:** pending.

## Reproducibility and AI-generation disclosure

This is an AI-generated research artifact released by Unsolved Labs with an artifact-based verification boundary. The theorem is intended to be auditable from the public witness, manuscript, exact checkers, and pinned repository history; private model conversations or hidden reasoning traces are not part of the evidence.

## Public release page

https://unsolved-labs.github.io/results/r012-fourier-sign-uncertainty/
