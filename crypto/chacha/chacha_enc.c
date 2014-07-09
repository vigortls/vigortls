/* Copyright (c) 2014, Google Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

/* Adapted from the public domain, estream code by D. Bernstein. */

#include <stdint.h>
#include <string.h>
#include <openssl/opensslconf.h>

#if !defined(OPENSSL_NO_CHACHA)

#include <openssl/chacha.h>

/* sigma contains the ChaCha constants, which happen to be an ASCII string. */
static const char sigma[16] = "expand 32-byte k";

#define ROTATE(v, n) (((v) << (n)) | ((v) >> (32 - (n))))
#define XOR(v, w) ((v) ^ (w))
#define PLUS(x, y) ((x) + (y))
#define PLUSONE(v) (PLUS((v), 1))

#define U32TO8_LITTLE(p, v) \
    { (p)[0] = (v >>  0) & 0xff; (p)[1] = (v >>  8) & 0xff; \
      (p)[2] = (v >> 16) & 0xff; (p)[3] = (v >> 24) & 0xff; }
#define U8TO32_LITTLE(p)   \
    (((uint32_t)((p)[0])      ) | ((uint32_t)((p)[1]) <<  8) | \
     ((uint32_t)((p)[2]) << 16) | ((uint32_t)((p)[3]) << 24)   )

/* QUARTERROUND updates a, b, c, d with a ChaCha "quarter" round. */
#define QUARTERROUND(a,b,c,d) \
  x[a] = PLUS(x[a],x[b]); x[d] = ROTATE(XOR(x[d],x[a]),16); \
  x[c] = PLUS(x[c],x[d]); x[b] = ROTATE(XOR(x[b],x[c]),12); \
  x[a] = PLUS(x[a],x[b]); x[d] = ROTATE(XOR(x[d],x[a]), 8); \
  x[c] = PLUS(x[c],x[d]); x[b] = ROTATE(XOR(x[b],x[c]), 7);

typedef unsigned int uint32_t;

/* chacha_core performs |num_rounds| rounds of ChaCha20 on the input words in
 * |input| and writes the 64 output bytes to |output|. */
static void chacha_core(unsigned char output[64], const uint32_t input[16],
            int num_rounds)
{
    uint32_t x[16];
    int i;

    memcpy(x, input, sizeof(uint32_t) * 16);
    for (i = 20; i > 0; i -= 2) {
        QUARTERROUND( 0, 4, 8,12)
        QUARTERROUND( 1, 5, 9,13)
        QUARTERROUND( 2, 6,10,14)
        QUARTERROUND( 3, 7,11,15)
        QUARTERROUND( 0, 5,10,15)
        QUARTERROUND( 1, 6,11,12)
        QUARTERROUND( 2, 7, 8,13)
        QUARTERROUND( 3, 4, 9,14)
    }

    for (i = 0; i < 16; ++i)
        x[i] = PLUS(x[i], input[i]);
    for (i = 0; i < 16; ++i)
        U32TO8_LITTLE(output + 4 * i, x[i]);
}

void CRYPTO_chacha_20(unsigned char *out,
              const unsigned char *in, size_t in_len,
              const unsigned char key[32],
              const unsigned char nonce[8],
              size_t counter)
{
    uint32_t input[16];
    unsigned char buf[64];
    size_t todo, i;

    input[0] = U8TO32_LITTLE(sigma + 0);
    input[1] = U8TO32_LITTLE(sigma + 4);
    input[2] = U8TO32_LITTLE(sigma + 8);
    input[3] = U8TO32_LITTLE(sigma + 12);

    input[4] = U8TO32_LITTLE(key + 0);
    input[5] = U8TO32_LITTLE(key + 4);
    input[6] = U8TO32_LITTLE(key + 8);
    input[7] = U8TO32_LITTLE(key + 12);

    input[8] = U8TO32_LITTLE(key + 16);
    input[9] = U8TO32_LITTLE(key + 20);
    input[10] = U8TO32_LITTLE(key + 24);
    input[11] = U8TO32_LITTLE(key + 28);

    input[12] = counter;
    input[13] = ((uint64_t) counter) >> 32;
    input[14] = U8TO32_LITTLE(nonce + 0);
    input[15] = U8TO32_LITTLE(nonce + 4);

    while (in_len > 0) {
        todo = sizeof(buf);
        if (in_len < todo)
            todo = in_len;

        chacha_core(buf, input, 20);
        for (i = 0; i < todo; i++)
            out[i] = in[i] ^ buf[i];

        out += todo;
        in += todo;
        in_len -= todo;

        input[12]++;
        if (input[12] == 0)
            input[13]++;
    }
}

#endif  /* !OPENSSL_NO_CHACHA */
