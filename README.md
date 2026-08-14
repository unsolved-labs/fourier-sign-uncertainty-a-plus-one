# R012 — One-dimensional Fourier sign-uncertainty upper bound

**Unsolved Labs Research Release R012**

An explicit Fourier-invariant Schwartz function gives a certified one-dimensional upper bound

\[
A_+(1)\leq \sqrt{\frac{1912071}{2000000\pi}}
=0.551648031984764\ldots<0.551649.
\]

## Status

- Exact explicit construction
- Self-contained integer/rational positivity verifier
- GitHub Actions replay
- Independent specialist review: pending

## Reproduce

The verifier requires a C++17 compiler and Boost headers.

```bash
./verify_release.sh
```

The script compiles `verify.cpp` and replays the full half-line positivity certificate in exact arithmetic, including the rational comparison with `0.551649`.

For a single exact interval check:

```bash
./verify range 100 200
```

## Files

- `proof.md` — theorem, construction, certificate logic, baseline, and limitations
- `verify.cpp` — exact verifier with the complete degree-1800 witness embedded
- `verify_release.sh` — clean-checkout full replay
- `verification-report.json` — machine-readable frozen claim
- `.github/workflows/verify.yml` — CI replay

## Claim boundary

This release proves an upper bound only. It does not determine the exact value of `A_+(1)`, prove a matching lower bound, or claim that the displayed construction is extremal.

## Public release page

https://unsolved-labs.github.io/results/r012-fourier-sign-uncertainty/
