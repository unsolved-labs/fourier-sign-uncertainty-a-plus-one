# R012 formal claim-mapping provenance

`claim_mapping.json` follows the reusable release-contract schema. This note records what its hashes mean so the mapping is reproducible rather than opaque.

## Base snapshot

`base_snapshot_sha256` is the SHA-256 digest of the canonical `CLAIM.md` content at the pre-Lean release merge commit:

`5933f9c83f29621bc009d95fd01d6a0b88a09ca6`

The recorded digest is:

`134b06da454dbce57f5aae321b0b9f4adfa448ebf91fb49856e5d6c9c23b619c`

This freezes the public theorem boundary that existed before adding the partial formalization.

## Formal target statement

The exact UTF-8 preimage for `target_statement_sha256` is the following single line, without a trailing newline:

```text
R012 formal bridge: for any real function p with p(0)=0, p(t) nonnegative for every t at least 1912071/1000000, whose Gaussian lift is integrable, nonzero, and self-Fourier in Mathlib's real Fourier normalization, the self-Fourier sign-radius infimum is at most sqrt((1912071/1000000)/(2*pi)), and that exact radius is strictly less than 551649/1000000.
```

Its SHA-256 digest is:

`a4d75acb011f140a1bcd68530d50a289771af13476174cf3a4ff8ea056a7f8fc`

## Mapped claim statement

The exact UTF-8 preimage for claim `C1` is:

```text
R012.r012_exact_and_decimal_bounds_from_certificate proves both public bridge inequalities from explicit external positivity, integrability, nontriviality, and Fourier self-duality obligations.
```

Its SHA-256 digest is:

`892c488b10a1075081dbfedf91b432ab2a61324c5b6046f9f9797d9ed00fb7ec`

The mapping role is `supporting_lemma`, not `parent_resolution`, because the complete concrete R012 theorem still relies on external obligations that are not fully discharged inside Lean.
