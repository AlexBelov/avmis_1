#!/bin/bash
make
echo 'GCC'
./gcc
echo 'ICC - Without Vectorization'
./icc_unvec
echo 'ICC - SSE2'
./icc_sse2
echo 'ICC - With Vectorization'
./icc_vec
