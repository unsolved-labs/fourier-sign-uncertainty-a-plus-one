import R012.Main

open R012

/-- Comparator solution wrapper. Its statement is verbatim the trusted
challenge declaration. -/
theorem r012_exact_and_decimal_bounds_from_certificate (p : ℝ → ℝ)
    (hp0 : p 0 = 0)
    (hp : ∀ t : ℝ, threshold ≤ t → 0 ≤ p t)
    (hint : MeasureTheory.Integrable (complexify (gaussianLift p)))
    (hnonzero : gaussianLift p ≠ 0)
    (hself : IsSelfFourier (gaussianLift p)) :
    APlusOneSelfFourier ≤ exactRadius ∧ exactRadius < decimalRadius :=
  R012.r012_exact_and_decimal_bounds_from_certificate p hp0 hp hint hnonzero hself
