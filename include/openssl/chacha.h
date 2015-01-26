/*
 * Copyright (c) 2014 - 2015, Kurt Cancemi (kurt@x64architecture.com)
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef HEADER_CHACHA_H
#define HEADER_CHACHA_H

#include <openssl/opensslconf.h>

#if defined(OPENSSL_NO_CHACHA)
#error ChaCha is disabled.
#endif

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned int input[16];
    unsigned char ks[64];
    unsigned char unused;
} ChaCha_ctx;

void ChaCha_set_key(ChaCha_ctx *ctx, const unsigned char *key,
                    unsigned int keybits);
void ChaCha_set_iv(ChaCha_ctx *ctx, const unsigned char *iv,
                   const unsigned char *counter);
void ChaCha(ChaCha_ctx *ctx, unsigned char *out, const unsigned char *in,
            size_t inlen);

void CRYPTO_chacha_20(unsigned char *out, const unsigned char *in, size_t inlen,
                      const unsigned char key[32], const unsigned char nonce[8], size_t counter);

#ifdef __cplusplus
}
#endif

#endif
