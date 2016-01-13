/*
 * Copyright (C) 2016, Kurt Cancemi
 * Copyright (c) 2014, Google Inc.
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
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */



#include <stdint.h>
#include <string.h>

#include <openssl/opensslconf.h>

#if !defined(OPENSSL_NO_CHACHA) && !defined(OPENSSL_NO_POLY1305)

#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/chacha.h>
#include <openssl/poly1305.h>

#include "evp_locl.h"

#define POLY1305_TAG_LEN 16
#define CHACHA20_NONCE_LEN 8

/*
 * RFC 7539 (ChaCha20 and Poly1305 for IETF Protocols)
 *
 * RFC 7539 introduces a new AEAD construction that is incompatable
 * with the draft version that has been in use in TLS for some time.
 * The IETF version also adds a salt of 4 bytes that is prepended to
 * the nonce of 8 bytes.
 */
#define CHACHA20_IETF_NONCE_LEN 12

struct aead_chacha20_poly1305_ctx {
    uint8_t key[32];
    uint8_t tag_len;
};

static int aead_chacha20_poly1305_init(EVP_AEAD_CTX *ctx, const uint8_t *key,
                                       size_t key_len, size_t tag_len)
{
    struct aead_chacha20_poly1305_ctx *c20_ctx;

    if (tag_len == 0)
        tag_len = POLY1305_TAG_LEN;

    if (tag_len > POLY1305_TAG_LEN) {
        EVPerr(EVP_F_AEAD_CHACHA20_POLY1305_INIT, EVP_R_TOO_LARGE);
        return 0;
    }

    /* Internal error - EVP_AEAD_CTX_init should catch this. */
    if (key_len != sizeof(c20_ctx->key))
        return 0;

    c20_ctx = malloc(sizeof(struct aead_chacha20_poly1305_ctx));
    if (c20_ctx == NULL)
        return 0;

    memcpy(&c20_ctx->key[0], key, key_len);
    c20_ctx->tag_len = tag_len;
    ctx->aead_state = c20_ctx;

    return 1;
}

static void aead_chacha20_poly1305_cleanup(EVP_AEAD_CTX *ctx)
{
    struct aead_chacha20_poly1305_ctx *c20_ctx = ctx->aead_state;

    vigortls_zeroize(c20_ctx->key, sizeof(c20_ctx->key));
    free(c20_ctx);
}

static void poly1305_update_with_length(poly1305_state *poly1305,
                                        const uint8_t *data, size_t data_len)
{
    size_t j = data_len;
    uint8_t length_bytes[8];
    unsigned i;

    for (i = 0; i < sizeof(length_bytes); i++) {
        length_bytes[i] = j;
        j >>= 8;
    }

    if (data != NULL)
        CRYPTO_poly1305_update(poly1305, data, data_len);
    CRYPTO_poly1305_update(poly1305, length_bytes, sizeof(length_bytes));
}

static void poly1305_update_padded_16(poly1305_state *poly1305, const uint8_t *data,
                                      size_t data_len)
{
    static const uint8_t padding[16] = { 0 };

    CRYPTO_poly1305_update(poly1305, data, data_len);

    /* pad16() RFC 7539 2.8.1 */
    if (data_len % 16 == 0)
        return;

    CRYPTO_poly1305_update(poly1305, padding, sizeof(padding) - (data_len % 16));
}


static int aead_chacha20_poly1305_seal(const EVP_AEAD_CTX *ctx, uint8_t *out,
                                       size_t *out_len, size_t max_out_len, const uint8_t *nonce,
                                       size_t nonce_len, const uint8_t *in, size_t in_len,
                                       const uint8_t *ad, size_t ad_len)
{
    const struct aead_chacha20_poly1305_ctx *c20_ctx = ctx->aead_state;
    uint8_t poly1305_key[32];
    poly1305_state poly1305;
    const uint8_t *iv;
    const uint64_t in_len_64 = in_len;
    uint64_t ctr;

    /* The underlying ChaCha implementation may not overflow the block
     * counter into the second counter word. Therefore we disallow
     * individual operations that work on more than 2TB at a time.
     * in_len_64 is needed because, on 32-bit platforms, size_t is only
     * 32-bits and this produces a warning because it's always false.
     * Casting to uint64_t inside the conditional is not sufficient to stop
     * the warning.
     */
    if (in_len_64 >= (1ULL << 32) * 64 - 64) {
        EVPerr(EVP_F_AEAD_CHACHA20_POLY1305_SEAL, EVP_R_TOO_LARGE);
        return 0;
    }

    if (max_out_len < in_len + c20_ctx->tag_len) {
        EVPerr(EVP_F_AEAD_CHACHA20_POLY1305_SEAL,
               EVP_R_BUFFER_TOO_SMALL);
        return 0;
    }

    if (nonce_len != ctx->aead->nonce_len) {
        EVPerr(EVP_F_AEAD_CHACHA20_POLY1305_SEAL, EVP_R_IV_TOO_LARGE);
        return 0;
    }


    if (nonce_len == CHACHA20_NONCE_LEN) {
        /* draft-agl-tls-chacha20poly1305-04 */
        memset(poly1305_key, 0, sizeof(poly1305_key));
        CRYPTO_chacha_20(poly1305_key, poly1305_key, sizeof(poly1305_key),
                         c20_ctx->key, nonce, 0);

        CRYPTO_poly1305_init(&poly1305, poly1305_key);
        poly1305_update_with_length(&poly1305, ad, ad_len);
        CRYPTO_chacha_20(out, in, in_len, c20_ctx->key, nonce, 1);
        poly1305_update_with_length(&poly1305, out, in_len);
    } else if (nonce_len == CHACHA20_IETF_NONCE_LEN) {
        /* RFC 7539 */

        ctr = (uint64_t)(nonce[0] | nonce[1] << 8 |
                nonce[2] << 16 | nonce[3] << 24) << 32;
        iv = nonce + 4;
        
        memset(poly1305_key, 0, sizeof(poly1305_key));
        CRYPTO_chacha_20(poly1305_key, poly1305_key, sizeof(poly1305_key),
                         c20_ctx->key, iv, ctr);

        CRYPTO_poly1305_init(&poly1305, poly1305_key);
        poly1305_update_padded_16(&poly1305, ad, ad_len);
        CRYPTO_chacha_20(out, in, in_len, c20_ctx->key, iv, ctr + 1);
        poly1305_update_padded_16(&poly1305, in, in_len);
        poly1305_update_with_length(&poly1305, NULL, ad_len);
        poly1305_update_with_length(&poly1305, NULL, in_len);
    }

    if (c20_ctx->tag_len != POLY1305_TAG_LEN) {
        uint8_t tag[POLY1305_TAG_LEN];
        CRYPTO_poly1305_finish(&poly1305, tag);
        memcpy(out + in_len, tag, c20_ctx->tag_len);
        *out_len = in_len + c20_ctx->tag_len;
        return 1;
    }

    CRYPTO_poly1305_finish(&poly1305, out + in_len);
    *out_len = in_len + POLY1305_TAG_LEN;
    return 1;
}

static int aead_chacha20_poly1305_open(const EVP_AEAD_CTX *ctx, uint8_t *out,
                                       size_t *out_len, size_t max_out_len, const uint8_t *nonce,
                                       size_t nonce_len, const uint8_t *in, size_t in_len,
                                       const uint8_t *ad, size_t ad_len)
{
    const struct aead_chacha20_poly1305_ctx *c20_ctx = ctx->aead_state;
    uint8_t mac[POLY1305_TAG_LEN];
    uint8_t poly1305_key[32];
    const uint8_t *iv;
    poly1305_state poly1305;
    const uint64_t in_len_64 = in_len;
    size_t plaintext_len;
    uint64_t ctr;

    if (in_len < c20_ctx->tag_len) {
        EVPerr(EVP_F_AEAD_CHACHA20_POLY1305_OPEN, EVP_R_BAD_DECRYPT);
        return 0;
    }

    /* The underlying ChaCha implementation may not overflow the block
     * counter into the second counter word. Therefore we disallow
     * individual operations that work on more than 2TB at a time.
     * in_len_64 is needed because, on 32-bit platforms, size_t is only
     * 32-bits and this produces a warning because it's always false.
     * Casting to uint64_t inside the conditional is not sufficient to stop
     * the warning. */
    if (in_len_64 >= (1ULL << 32) * 64 - 64) {
        EVPerr(EVP_F_AEAD_CHACHA20_POLY1305_OPEN, EVP_R_TOO_LARGE);
        return 0;
    }

    if (nonce_len != ctx->aead->nonce_len) {
        EVPerr(EVP_F_AEAD_CHACHA20_POLY1305_OPEN, EVP_R_IV_TOO_LARGE);
        return 0;
    }

    plaintext_len = in_len - c20_ctx->tag_len;

    if (max_out_len < plaintext_len) {
        EVPerr(EVP_F_AEAD_CHACHA20_POLY1305_OPEN,
               EVP_R_BUFFER_TOO_SMALL);
        return 0;
    }

    if (nonce_len == CHACHA20_NONCE_LEN) {
        /* draft-agl-tls-chacha20poly1305-04 */

        memset(poly1305_key, 0, sizeof(poly1305_key));
        CRYPTO_chacha_20(poly1305_key, poly1305_key, sizeof(poly1305_key),
                         c20_ctx->key, nonce, 0);

        CRYPTO_poly1305_init(&poly1305, poly1305_key);
        poly1305_update_with_length(&poly1305, ad, ad_len);
        poly1305_update_with_length(&poly1305, in, plaintext_len);
    } else if (nonce_len == CHACHA20_IETF_NONCE_LEN) {
        /* RFC 7539 */

        ctr = (uint64_t)(nonce[0] | nonce[1] << 8 | nonce[2] << 16 |
                nonce[3] << 24) << 32;
        iv = nonce + 4;
        
        memset(poly1305_key, 0, sizeof(poly1305_key));
        CRYPTO_chacha_20(poly1305_key, poly1305_key, sizeof(poly1305_key),
                         c20_ctx->key, iv, ctr);

        CRYPTO_poly1305_init(&poly1305, poly1305_key);
        poly1305_update_padded_16(&poly1305, ad, ad_len);
        poly1305_update_padded_16(&poly1305, in, plaintext_len);
        poly1305_update_with_length(&poly1305, NULL, ad_len);
        poly1305_update_with_length(&poly1305, NULL, plaintext_len);
    }

    CRYPTO_poly1305_finish(&poly1305, mac);

    if (CRYPTO_memcmp(mac, in + plaintext_len, c20_ctx->tag_len) != 0) {
        EVPerr(EVP_F_AEAD_CHACHA20_POLY1305_OPEN, EVP_R_BAD_DECRYPT);
        return 0;
    }

    CRYPTO_chacha_20(out, in, plaintext_len, c20_ctx->key, nonce, 1);
    *out_len = plaintext_len;
    return 1;
}

static const EVP_AEAD aead_chacha20_poly1305 = {
    .key_len = 32,
    .nonce_len = CHACHA20_NONCE_LEN,
    .overhead = POLY1305_TAG_LEN,
    .max_tag_len = POLY1305_TAG_LEN,

    .init = aead_chacha20_poly1305_init,
    .cleanup = aead_chacha20_poly1305_cleanup,
    .seal = aead_chacha20_poly1305_seal,
    .open = aead_chacha20_poly1305_open,
};

static const EVP_AEAD aead_chacha20_poly1305_ietf = {
    .key_len = 32,
    .nonce_len = CHACHA20_IETF_NONCE_LEN,
    .overhead = POLY1305_TAG_LEN,
    .max_tag_len = POLY1305_TAG_LEN,

    .init = aead_chacha20_poly1305_init,
    .cleanup = aead_chacha20_poly1305_cleanup,
    .seal = aead_chacha20_poly1305_seal,
    .open = aead_chacha20_poly1305_open,
};

const EVP_AEAD *EVP_aead_chacha20_poly1305()
{
    return &aead_chacha20_poly1305;
}

const EVP_AEAD *EVP_aead_chacha20_poly1305_ietf()
{
    return &aead_chacha20_poly1305_ietf;
}

#endif /* !OPENSSL_NO_CHACHA && !OPENSSL_NO_POLY1305 */
