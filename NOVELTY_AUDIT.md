# R012 novelty audit

The canonical literature/provenance audit for the mathematical release is [SOURCE_AUDIT.md](SOURCE_AUDIT.md). That file freezes the rigorous comparison source, numerical-context source, witness provenance, and limits on priority language.

This companion file exists because the reusable Lean release contract requires an explicit novelty-audit boundary alongside the formal package.

## Mathematical novelty boundary

R012 may state that its public degree-1800 witness and exact certificate establish

$$
A_+(1)\leq\sqrt{\frac{1912071}{2000000\pi}}<0.551649.
$$

The theorem does not depend on a claim that this is the globally best rigorous upper bound at every later date. Any such comparative statement requires a current primary-source literature audit.

## Formalization boundary

The Lean package added to R012 is a **partial verification layer**, not a new mathematical result and not a full formalization of the release. It formalizes the certificate-to-radius bridge and exact decimal comparison under explicit hypotheses. In particular it does not formalize:

- reconstruction or finite Bernstein verification of all 900 frozen coefficients;
- the generalized Laguerre-Gaussian Fourier eigenfunction identity;
- the search that found the witness; or
- every literature-equivalent definition of the sign-uncertainty constant.

No novelty or priority claim is made for the Lean bridge itself. Its purpose is to reduce and expose the proof trust boundary.

## Control rule

Changes to mathematical priority wording must update `SOURCE_AUDIT.md`. Changes to the formalization scope must update this file, `formalization.yaml`, `STATEMENT_AUDIT.md`, and `VERIFICATION.md` in the same pull request.
