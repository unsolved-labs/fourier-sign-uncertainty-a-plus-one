#!/usr/bin/env bash
set -euo pipefail
CXX=${CXX:-g++}
"$CXX" -O3 -std=c++17 verify.cpp -o verify

./verify near
for a in 2 3 4 5 6 7 8 9; do ./verify range "$a" "$((a+1))"; done
for a in 10 15 20 25 30 35 40 45 50 60 70 80 90; do
  if [ "$a" -lt 50 ]; then b=$((a+5)); else b=$((a+10)); fi
  ./verify range "$a" "$b"
done
for a in 100 200 300 400 500 600 700 800 900; do ./verify range "$a" "$((a+100))"; done
for a in 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 11000; do
  b=$((a+1000));
  if [ "$a" -eq 11000 ]; then b=11500; fi
  ./verify range "$a" "$b"
done
./verify tail
./verify radius

echo "R012 FULL EXACT REPLAY PASSED"
echo "A_+(1) <= sqrt(1912071/(2000000*pi)) < 0.551649"
