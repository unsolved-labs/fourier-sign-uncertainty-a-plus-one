# R012 manuscript

The canonical manuscript source is `r012_fourier_sign_uncertainty.tex`.

Build a PDF with:

```bash
make
```

This requires `latexmk` and a standard LaTeX installation. The expected output is:

```text
r012_fourier_sign_uncertainty.pdf
```

CI rebuilds the manuscript from source on every push and pull request. The generated PDF is intentionally treated as a build product rather than a hand-edited source of truth; the LaTeX source, claim files, and exact verification artifacts are canonical.

The manuscript must remain statement-identical to `CLAIM.md` and `STATEMENT_AUDIT.md`.
