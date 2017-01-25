#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>

#define u32 uint32_t

static const u32 RC[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static const unsigned char testvector_abc[] = {0xbf, 0x16, 0x78, 0xba, 0xea,
                                               0xcf, 0x01, 0x8f, 0xde, 0x40,
                                               0x41, 0x41, 0x23, 0x22, 0xae,
                                               0x5d, 0xa3, 0x61, 0x03, 0xb0,
                                               0x9c, 0x7a, 0x17, 0x96, 0x61,
                                               0xff, 0x10, 0xb4, 0xad, 0x15,
                                               0x00, 0xf2};

#define MAJ(a, b, c) ((a&b) ^ (a&c) ^ (b&c))
#define CH(a, b, c) ((a&b) ^ (~(a)&c))

inline u32 ROTR32(u32 x, uint8_t r) {
    asm("ror %1,%0" : "+r" (x) : "c" (r));
    return x;
}

#define SIGMA1(x) (ROTR32(x, 6) ^ ROTR32(x, 11) ^ ROTR32(x, 25))
#define SIGMA0(x) (ROTR32(x, 2) ^ ROTR32(x, 13) ^ ROTR32(x, 22))

#define WSIGMA1(x) (ROTR32(x, 17) ^ ROTR32(x, 19) ^ (x >> 10))
#define WSIGMA0(x) (ROTR32(x, 7) ^ ROTR32(x, 18) ^ (x >> 3))

#define SHA256ROUND(a, b, c, d, e, f, g, h, rc, w) \
    T0 = h + SIGMA1(e) + CH(e, f, g) + RC[rc] + w; \
    d = d + T0; \
    T1 = SIGMA0(a) + MAJ(a, b, c); \
    h = T0 + T1;

void sha256(unsigned char *out, const unsigned char *in);

#endif