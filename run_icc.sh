#!/bin/bash
make
echo 'GCC'
./gcc_sse2
echo 'GCC - AVX'
./gcc_avx
echo 'ICC - Without Vectorization'
./icc_unvec
echo 'ICC - SSE2'
./icc_sse2
echo 'ICC - With Vectorization'
./icc_vec
