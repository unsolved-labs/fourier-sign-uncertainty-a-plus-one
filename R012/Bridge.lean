import Mathlib.Analysis.Fourier.FourierTransform
import Mathlib.Analysis.Real.Pi.Bounds

/-!
# R012 formal bridge

This file formalizes the theorem-level bridge used by R012 from an exactly
certified polynomial positivity statement to a one-dimensional self-Fourier
sign-uncertainty upper bound.

It deliberately does **not** assume that a finite test suite is a proof of the
external positivity certificate, and it does not encode the 900-coefficient
Laguerre identity. Those remain separate verification obligations documented in
`STATEMENT_AUDIT.md` and `VERIFICATION.md`.
-/

noncomputable section

open MeasureTheory
open scoped FourierTransform

namespace R012

/-- Regard a real-valued function as a complex-valued function for Mathlib's
Fourier transform. -/
def complexify (f : ℝ → ℝ) : ℝ → ℂ := fun x => (f x : ℂ)

/-- Self-Fourier property in Mathlib's real Fourier normalization, whose kernel
is `exp (-2 * π * i * x * y)`. -/
def IsSelfFourier (f : ℝ → ℝ) : Prop :=
  ∀ y : ℝ, 𝓕 (complexify f) y = (f y : ℂ)

/-- The release-specific admissibility conditions needed by the self-Fourier
`+1` formulation: integrability, nontriviality, vanishing at the origin, and
Fourier self-duality. -/
def IsAdmissible (f : ℝ → ℝ) : Prop :=
  Integrable (complexify f) ∧ f ≠ 0 ∧ f 0 = 0 ∧ IsSelfFourier f

/-- `f` is nonnegative outside the symmetric radius `r`. -/
def HasNonnegativeRadius (f : ℝ → ℝ) (r : ℝ) : Prop :=
  ∀ x : ℝ, r ≤ |x| → 0 ≤ f x

/-- The infimum of nonnegative radii attained by admissible self-Fourier
witnesses. This is the precise self-Fourier formulation used by the R012 bridge;
it is not presented as a formalization of every equivalent literature
definition of `A_+(1)`. -/
def APlusOneSelfFourier : ℝ :=
  sInf {r : ℝ | 0 ≤ r ∧ ∃ f : ℝ → ℝ, IsAdmissible f ∧ HasNonnegativeRadius f r}

/-- Any admissible witness at radius `r` bounds the self-Fourier infimum by `r`. -/
theorem APlusOneSelfFourier_le_of_radius {r : ℝ}
    (hr : 0 ≤ r ∧ ∃ f : ℝ → ℝ, IsAdmissible f ∧ HasNonnegativeRadius f r) :
    APlusOneSelfFourier ≤ r := by
  refine csInf_le ?_ hr
  exact ⟨0, by
    intro a ha
    exact ha.1⟩

/-- Lift a polynomial-side function `p(t)` to the Gaussian witness used by the
release. -/
def gaussianLift (p : ℝ → ℝ) (x : ℝ) : ℝ :=
  p (2 * Real.pi * x ^ 2) * Real.exp (-Real.pi * x ^ 2)

@[simp]
theorem gaussianLift_zero {p : ℝ → ℝ} (hp0 : p 0 = 0) :
    gaussianLift p 0 = 0 := by
  simp [gaussianLift, hp0]

/-- A positivity certificate in the polynomial variable `t` transfers to
nonnegativity of the Gaussian witness outside any radius whose squared scale
reaches the certified threshold. -/
theorem gaussianLift_nonnegative_outside {p : ℝ → ℝ} {T r : ℝ}
    (hr : 0 ≤ r)
    (hscale : T ≤ 2 * Real.pi * r ^ 2)
    (hp : ∀ t : ℝ, T ≤ t → 0 ≤ p t) :
    HasNonnegativeRadius (gaussianLift p) r := by
  intro x hx
  have hsq_abs : r ^ 2 ≤ |x| ^ 2 := (sq_le_sq₀ hr (abs_nonneg x)).2 hx
  have hsq : r ^ 2 ≤ x ^ 2 := by simpa using hsq_abs
  have hfactor : 0 ≤ 2 * Real.pi := mul_nonneg (by norm_num) Real.pi_pos.le
  have hmul : 2 * Real.pi * r ^ 2 ≤ 2 * Real.pi * x ^ 2 :=
    mul_le_mul_of_nonneg_left hsq hfactor
  have ht : T ≤ 2 * Real.pi * x ^ 2 := hscale.trans hmul
  exact mul_nonneg (hp _ ht) (Real.exp_pos _).le

/-- Exact R012 polynomial threshold. -/
def threshold : ℝ := (1912071 : ℝ) / 1000000

/-- Public decimal comparison radius `0.551649`. -/
def decimalRadius : ℝ := (551649 : ℝ) / 1000000

@[positivity]
theorem threshold_nonneg : 0 ≤ threshold := by
  norm_num [threshold]

@[positivity]
theorem decimalRadius_nonneg : 0 ≤ decimalRadius := by
  norm_num [decimalRadius]

/-- Mathlib's rigorous lower bound on π suffices to prove that the R012
threshold is reached strictly before radius `0.551649`. -/
theorem threshold_lt_scale_decimal :
    threshold < 2 * Real.pi * decimalRadius ^ 2 := by
  dsimp [threshold, decimalRadius]
  nlinarith [Real.pi_gt_d6]

/-- Load-bearing formal bridge for the public decimal bound.

The external obligations are explicit hypotheses:
* exact positivity of `p(t)` for `t ≥ threshold`;
* integrability and nontriviality of the resulting Gaussian witness; and
* the actual Mathlib Fourier self-duality of that witness.

Given those obligations, Lean proves the sign-radius implication and the strict
numerical scale comparison used by R012. -/
theorem r012_decimal_bound_from_certificate (p : ℝ → ℝ)
    (hp0 : p 0 = 0)
    (hp : ∀ t : ℝ, threshold ≤ t → 0 ≤ p t)
    (hint : Integrable (complexify (gaussianLift p)))
    (hnonzero : gaussianLift p ≠ 0)
    (hself : IsSelfFourier (gaussianLift p)) :
    APlusOneSelfFourier ≤ decimalRadius := by
  apply APlusOneSelfFourier_le_of_radius
  refine ⟨decimalRadius_nonneg, gaussianLift p, ?_, ?_⟩
  · exact ⟨hint, hnonzero, gaussianLift_zero hp0, hself⟩
  · exact gaussianLift_nonnegative_outside decimalRadius_nonneg
      threshold_lt_scale_decimal.le hp

end R012
