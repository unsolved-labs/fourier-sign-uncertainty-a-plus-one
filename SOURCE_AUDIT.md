# R012 source and novelty audit

This file records the public sources and provenance assumptions used by the release. It is not a substitute for the mathematical proof or exact certificate replay.

## Mathematical comparison source

The frozen rigorous comparison used by R012 is:

- arXiv:1602.03366 (2016), by F. Goncalves, D. Oliveira e Silva, and S. Steinerberger.

R012 uses the rigorous one-dimensional interval reported there, in particular the upper comparison point

$$
A_+(1)\leq0.594.
$$

The repository must not strengthen the priority statement beyond what a current primary-source literature audit supports. The exact R012 theorem does not depend on being the first such improvement; only the comparative/novelty wording does.

## Numerical-context source

- arXiv:2003.10771 (2020) is cited as later sign-uncertainty context containing substantially sharper numerical/conjectural structure.

Numerical evidence from that line of work is not treated as a rigorous theorem unless the cited source explicitly proves the relevant statement.

## Witness provenance

The theorem witness is completely public and frozen in:

- `coefficients/part1.txt` — Git blob `f10f19a24a4e7e1738799b726064d458ab099bfb`
- `coefficients/part2.txt` — Git blob `855466445093d7ef863f3b90c2a302f113d802ef`
- `coefficients/part3.txt` — Git blob `4f720c5461fbb83187fab4323be1631bfef3a6e9`
- `coefficients/part4.txt` — Git blob `5615439c2def17727f30713034c974549f546bfa`
- `coefficients/part5.txt` — Git blob `9040f34ec50ae648a3c5e618e3e1a55a90b1b136`
- `coefficients/part6.txt` — Git blob `b8b42878a42c50dc38c0dc793e2de5a64d86d708`

The coefficient-search process is discovery provenance, not proof evidence. R012 is reproducible from the frozen coefficients and public verification code without reproducing the search.

## Novelty boundary

The release may state objectively that it provides an explicit exactly certified witness proving

$$
A_+(1)\leq\sqrt{\frac{1912071}{2000000\pi}}<0.551649.
$$

It must not state or imply, without an updated source audit, that:

- `0.551649` is the globally best rigorous upper bound known at every later date;
- the witness is optimal;
- the search method is itself a theorem/proof contribution; or
- numerical candidates from other work are rigorous comparisons.

Any future change to baseline/priority wording should update this file and `STATEMENT_AUDIT.md` in the same pull request.
