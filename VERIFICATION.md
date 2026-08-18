# R012 verification and reproducibility

R012 is a computer-assisted proof with an explicit finite witness. The search that produced the witness is **not** trusted. The released theorem depends on a frozen coefficient vector, exact arithmetic, and standard Fourier/Laguerre mathematics.

## Clean-checkout replay

Requirements:

- a C++17 compiler;
- Boost headers;
- Python 3.11+ for the independent structural/tail replay.

Run the production proof replay:

```bash
./verify_release.sh
```

Run the independent exact reconstruction/tail/radius replay:

```bash
python3 verify_independent.py
```

The GitHub Actions workflow `.github/workflows/verify.yml` shards the production finite-interval proof and also runs the independent Python path.

## Production checker: `verify.cpp`

The C++17 checker is the production certificate checker for the theorem. It uses only exact integer/rational arithmetic for proof obligations.

It reconstructs

$$
p(t)=\sum_{k=1}^{900}N_k\bigl(L_{2k}^{-1/2}(t)-L_{2k}^{-1/2}(0)\bigr)
$$

through the integer-scaled recurrence

$$
R_n(t)=2^n n!L_n^{-1/2}(t),
$$

checks the expected degree/constant/leading-sign invariants, and proves positivity in two stages:

1. **Finite interval:** exact affine changes to `[0,1]`, conversion to a scaled Bernstein basis, and recursive dyadic de Casteljau subdivision until every leaf has strictly positive Bernstein coefficients.
2. **Infinite tail:** exact expansion of $P(12000+u)$ and verification that the constant coefficient is positive and every remaining coefficient is nonnegative.

The command `./verify radius` proves the displayed decimal comparison using rational arithmetic and a rigorous lower bound for $\pi$ derived from Machin's identity and alternating arctangent truncation.

### Exact finite coverage

The release replay covers continuously from

$$
T=\frac{1912071}{1000000}
$$

to `12000`, using the interval partition encoded in `verify_release.sh` / CI. The partition is an implementation detail, not a mathematical assumption.

## Independent checker: `verify_independent.py`

The Python checker is a separately written exact implementation using Python arbitrary-precision integers and `fractions.Fraction`. It independently:

- parses all six coefficient files and requires exactly 900 integers;
- reconstructs the degree-1800 scaled Laguerre polynomial;
- checks zero constant term and positive leading coefficient;
- expands the polynomial at `12000` and checks the full nonnegative tail-coefficient certificate; and
- proves the `0.551649` radius comparison using exact rational arithmetic.

It intentionally does **not** duplicate the complete finite `[T,12000]` Bernstein subdivision. Accordingly, the current release has meaningful independent coverage of witness reconstruction, the infinite tail, and the numerical-radius inequality, while the finite Bernstein certificate is still checked by one production implementation.

This distinction is part of the public trust boundary and must not be described as a fully independent second proof of the entire theorem.

## Mathematical dependencies outside the checkers

The checkers certify the polynomial/certificate arithmetic. The following mathematical bridge remains conventional mathematical reasoning documented in `proof.md` and the manuscript:

1. the Laguerre-Gaussian Fourier identity

   $$
   \mathcal F\!\left[L_n^{-1/2}(2\pi x^2)e^{-\pi x^2}\right]
   =(-1)^nL_n^{-1/2}(2\pi x^2)e^{-\pi x^2};
   $$

2. only even indices occur, hence the witness is self-Fourier;
3. polynomial times Gaussian is Schwartz and the Gaussian factor is positive; and
4. an admissible self-Fourier witness positive outside radius $r$ yields $A_+(1)\le r$ under the frozen definition/convention.

These are the highest-value targets for future proof-assistant formalization. A full Lean formalization is **not currently claimed**. Adding a Lean file containing these facts merely as assumptions would not strengthen the trust boundary and should not be done.

## Source-data identity

The coefficient data are frozen in the following Git blobs on the audited `main` baseline:

| File | Git blob SHA |
|---|---|
| `coefficients/part1.txt` | `f10f19a24a4e7e1738799b726064d458ab099bfb` |
| `coefficients/part2.txt` | `855466445093d7ef863f3b90c2a302f113d802ef` |
| `coefficients/part3.txt` | `4f720c5461fbb83187fab4323be1631bfef3a6e9` |
| `coefficients/part4.txt` | `5615439c2def17727f30713034c974549f546bfa` |
| `coefficients/part5.txt` | `9040f34ec50ae648a3c5e618e3e1a55a90b1b136` |
| `coefficients/part6.txt` | `b8b42878a42c50dc38c0dc793e2de5a64d86d708` |

Future coefficient changes constitute a new witness and require a new statement/data audit and verification report.

## Trust boundary summary

Trusted inputs/dependencies:

- standard C++ compiler/Boost multiprecision semantics for the production replay;
- Python integer/Fraction semantics for the independent partial replay;
- the standard mathematical Fourier/Laguerre facts listed above;
- the six frozen coefficient files.

Not trusted:

- the optimizer/search process that found the witness;
- floating-point root finding or sampled positivity;
- the printed floating-point decimal emitted for convenience by `verify radius`.

The proof claim depends only on exact checks and the stated mathematical bridge.
