#!/usr/bin/env python3
"""Independent exact R012 structural/tail/radius replay.

This implementation deliberately uses Python's unbounded integers/Fraction and a
separate code path from verify.cpp. It independently reconstructs the frozen
Laguerre witness, checks its structural invariants, verifies the shifted tail
coefficient certificate, and verifies the 0.551649 radius comparison.

The finite [T,12000] Bernstein-subdivision proof remains the responsibility of
verify.cpp; see VERIFICATION.md for the precise trust boundary.
"""
from fractions import Fraction
from pathlib import Path

N = 900
DEGREE = 1800
T_NUM = 1912071
T_DEN = 1000000
TAIL_START = 12000


def load_coefficients():
    out = []
    for part in range(1, 7):
        text = Path(f"coefficients/part{part}.txt").read_text(encoding="utf-8")
        out.extend(int(x) for x in text.split())
    if len(out) != N:
        raise AssertionError(f"expected {N} coefficients, found {len(out)}")
    return out


def add_scaled(dst, src, scale):
    if len(dst) < len(src):
        dst.extend([0] * (len(src) - len(dst)))
    for i in range(1, len(src)):  # centered Laguerre term: omit constant
        dst[i] += scale * src[i]


def reconstruct_integer_polynomial(nums):
    # R_n(t)=2^n n! L_n^{-1/2}(t), with the same mathematical recurrence
    # but an independently written Python implementation.
    r_prev = [1]
    r_cur = [1, -2]
    p = [0]

    fact = 1
    for j in range(2, DEGREE + 1):
        fact *= j
    factor = (1 << DEGREE) * fact

    for n in range(1, DEGREE + 1):
        factor //= 2 * n
        if n >= 2:
            j = n - 1
            nxt = [0] * (len(r_cur) + 1)
            a = 4 * j + 1
            for i, c in enumerate(r_cur):
                nxt[i] += a * c
                nxt[i + 1] -= 2 * c
            b = 2 * j * (2 * j - 1)
            for i, c in enumerate(r_prev):
                nxt[i] -= b * c
            r_prev, r_cur = r_cur, nxt
        if n % 2 == 0:
            add_scaled(p, r_cur, factor * nums[n // 2 - 1])

    while len(p) > 1 and p[-1] == 0:
        p.pop()
    assert len(p) == DEGREE + 1
    assert p[0] == 0
    assert p[-1] > 0
    return p


def shift_polynomial(coeffs, a):
    # Horner expansion of P(a+u), exact over Z.
    q = [coeffs[-1]]
    for c in reversed(coeffs[:-1]):
        nxt = [0] * (len(q) + 1)
        for j, x in enumerate(q):
            nxt[j] += a * x
            nxt[j + 1] += x
        nxt[0] += c
        q = nxt
    return q


def check_radius():
    # Machin: pi = 16 atan(1/5) - 4 atan(1/239).
    # A four-term alternating truncation of atan(1/5) is a lower bound;
    # replacing atan(1/239) by 1/239 preserves a lower bound for pi.
    a5 = Fraction(1, 5) - Fraction(1, 3 * 5**3) + Fraction(1, 5 * 5**5) - Fraction(1, 7 * 5**7)
    pi_lower = 16 * a5 - 4 * Fraction(1, 239)
    assert pi_lower > Fraction(333, 106)
    lhs = Fraction(T_NUM, T_DEN) / (2 * pi_lower)
    rhs = Fraction(551649, 1_000_000) ** 2
    assert lhs < rhs


def main():
    nums = load_coefficients()
    p = reconstruct_integer_polynomial(nums)
    tail = shift_polynomial(p, TAIL_START)
    assert tail[0] > 0
    assert all(c >= 0 for c in tail)
    check_radius()
    print("PASS independent exact witness reconstruction")
    print("PASS independent exact tail certificate")
    print("PASS independent exact radius comparison")
    print("NOTE finite [T,12000] Bernstein certificate is checked by verify.cpp")


if __name__ == "__main__":
    main()
