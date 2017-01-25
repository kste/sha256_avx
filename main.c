/*
Implementation of SHA256 for hashing single blocks or 8x single blocks in
parallel using AVX2.
*/

#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "sha256avx.h"
#include "sha256.h"
#include "timing.h"

void checkTestvectorAvx() {
  unsigned char *in, *out;
  int i, j;

  in = malloc(64 * 8);
  out = malloc(32 * 8);

  memset(in, 0, 64 * 8);

  // Test Vector "abc" for all 8 blocks
  for (i = 0; i < 8; i++) {
    in[64 * i + 0] = 0x80;
    in[64 * i + 1] = 0x63;
    in[64 * i + 2] = 0x62;
    in[64 * i + 3] = 0x61;
    in[64 * i + 60] = 0x18;
  }

  sha256_8x(out, in);

  for (i = 0; i < 32; i++) {
    for (j = 0; j < 8; j++) {
      if (out[32 * j + i] != testvector_abc[i]) {
        printf("ERROR SHA256AVX: Output does not match with testvector.\n");
      }
    }
  }

  free(in);
  free(out);
}

void checkTestvector() {
  //TODO:
  unsigned char *in, *out;
  int i;

  in = malloc(64);
  out = malloc(32);

  memset(in, 0, 64);

  // Test Vector "abc" from
  // http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA_All.pdf
  in[0] = 0x80;
  in[1] = 0x63;
  in[2] = 0x62;
  in[3] = 0x61;
  in[60] = 0x18;

  sha256(out, in);

  for (i = 0; i < 32; i++) {
    if (out[i] != testvector_abc[i]) {
      printf("ERROR SHA256: Output does not match with testvector.\n");
    }
  }

  free(in);
  free(out);
}

int main() {
  unsigned char *in, *out;
  unsigned long long inlen;
  unsigned long long timer = 0;
  double timings[NUM_TIMINGS];

  int i, j;

  checkTestvector();
  checkTestvectorAvx();

  srand(0);
  inlen = 64 * 8; // Hash 8 * 512 bits
  in = malloc(inlen);
  out = malloc(inlen / 2);

  for (i = -100; i < NUM_TIMINGS; i++) {
    //Get random input
    for (j = 0; j < inlen; j++) {
      in[j] = rand() & 0xff;
    }

    timer = startTimer();
    sha256_8x(out, in);
    timer = endTimer() - timer;

    if (i >= 0 && i < NUM_TIMINGS) {
      timings[i] = ((double)timer) / inlen;
    }
  }

  //Get Median
  qsort(timings, NUM_TIMINGS, sizeof(double), compareDouble);
  printf("Sha256_8x: %f cycles per byte\n", timings[NUM_TIMINGS / 2]);

  free(out);
  free(in);
}
