# sha256_avx
A fast implementation for processing messages parallel processing single message blocks with SHA256.

The AVX implementation needs 2.72 Cycles/Byte to process 8 independent blocks of 512-bit on
Intel Haswell (i7-4770S) compiled with gcc 5.4.0.
