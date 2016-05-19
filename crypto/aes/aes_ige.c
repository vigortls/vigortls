/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <string.h>

#include <openssl/aes.h>
#include <openssl/crypto.h>

#define N_WORDS (AES_BLOCK_SIZE / sizeof(unsigned long))
typedef struct {
    unsigned long data[N_WORDS];
} aes_block_t;

/* XXX: probably some better way to do this */
#if defined(VIGORTLS_X86) || defined(VIGORTLS_X86_64)
#define UNALIGNED_MEMOPS_ARE_FAST 1
#else
#define UNALIGNED_MEMOPS_ARE_FAST 0
#endif

#if UNALIGNED_MEMOPS_ARE_FAST
#define load_block(d, s) (d) = *(const aes_block_t *)(s)
#define store_block(d, s) *(aes_block_t *)(d) = (s)
#else
#define load_block(d, s) memcpy((d).data, (s), AES_BLOCK_SIZE)
#define store_block(d, s) memcpy((d), (s).data, AES_BLOCK_SIZE)
#endif

/* N.B. The IV for this mode is _twice_ the block size */

void AES_ige_encrypt(const uint8_t *in, uint8_t *out, size_t length,
                     const AES_KEY *key, uint8_t *ivec, const int enc)
{
    size_t n;
    size_t len = length;

    OPENSSL_assert(in && out && key && ivec);
    OPENSSL_assert((AES_ENCRYPT == enc) || (AES_DECRYPT == enc));
    OPENSSL_assert((length % AES_BLOCK_SIZE) == 0);

    len = length / AES_BLOCK_SIZE;

    if (AES_ENCRYPT == enc) {
        if (in != out
            && (UNALIGNED_MEMOPS_ARE_FAST
                || ((size_t)in | (size_t)out | (size_t)ivec) % sizeof(long) == 0)) {

            aes_block_t *ivp = (aes_block_t *)ivec;
            aes_block_t *iv2p = (aes_block_t *)(ivec + AES_BLOCK_SIZE);

            while (len) {
                aes_block_t *inp = (aes_block_t *)in;
                aes_block_t *outp = (aes_block_t *)out;

                for (n = 0; n < N_WORDS; ++n)
                    outp->data[n] = inp->data[n] ^ ivp->data[n];
                AES_encrypt((uint8_t *)outp->data,
                            (uint8_t *)outp->data, key);
                for (n = 0; n < N_WORDS; ++n)
                    outp->data[n] ^= iv2p->data[n];
                ivp = outp;
                iv2p = inp;
                --len;
                in += AES_BLOCK_SIZE;
                out += AES_BLOCK_SIZE;
            }
            memcpy(ivec, ivp->data, AES_BLOCK_SIZE);
            memcpy(ivec + AES_BLOCK_SIZE, iv2p->data, AES_BLOCK_SIZE);
        } else {
            aes_block_t tmp, tmp2;
            aes_block_t iv;
            aes_block_t iv2;

            load_block(iv, ivec);
            load_block(iv2, ivec + AES_BLOCK_SIZE);

            while (len) {
                load_block(tmp, in);
                for (n = 0; n < N_WORDS; ++n)
                    tmp2.data[n] = tmp.data[n] ^ iv.data[n];
                AES_encrypt((uint8_t *)tmp2.data, (uint8_t *)tmp2.data, key);
                for (n = 0; n < N_WORDS; ++n)
                    tmp2.data[n] ^= iv2.data[n];
                store_block(out, tmp2);
                iv = tmp2;
                iv2 = tmp;
                --len;
                in += AES_BLOCK_SIZE;
                out += AES_BLOCK_SIZE;
            }
            memcpy(ivec, iv.data, AES_BLOCK_SIZE);
            memcpy(ivec + AES_BLOCK_SIZE, iv2.data, AES_BLOCK_SIZE);
        }
    } else {
        if (in != out
            && (UNALIGNED_MEMOPS_ARE_FAST
                || ((size_t)in | (size_t)out | (size_t)ivec) % sizeof(long) == 0)) {

            aes_block_t *ivp = (aes_block_t *)ivec;
            aes_block_t *iv2p = (aes_block_t *)(ivec + AES_BLOCK_SIZE);

            while (len) {
                aes_block_t tmp;
                aes_block_t *inp = (aes_block_t *)in;
                aes_block_t *outp = (aes_block_t *)out;

                for (n = 0; n < N_WORDS; ++n)
                    tmp.data[n] = inp->data[n] ^ iv2p->data[n];
                AES_decrypt((uint8_t *)tmp.data, (uint8_t *)outp->data, key);
                for (n = 0; n < N_WORDS; ++n)
                    outp->data[n] ^= ivp->data[n];
                ivp = inp;
                iv2p = outp;
                --len;
                in += AES_BLOCK_SIZE;
                out += AES_BLOCK_SIZE;
            }
            memcpy(ivec, ivp->data, AES_BLOCK_SIZE);
            memcpy(ivec + AES_BLOCK_SIZE, iv2p->data, AES_BLOCK_SIZE);
        } else {
            aes_block_t tmp, tmp2;
            aes_block_t iv;
            aes_block_t iv2;

            load_block(iv, ivec);
            load_block(iv2, ivec + AES_BLOCK_SIZE);

            while (len) {
                load_block(tmp, in);
                tmp2 = tmp;
                for (n = 0; n < N_WORDS; ++n)
                    tmp.data[n] ^= iv2.data[n];
                AES_decrypt((uint8_t *)tmp.data, (uint8_t *)tmp.data, key);
                for (n = 0; n < N_WORDS; ++n)
                    tmp.data[n] ^= iv.data[n];
                store_block(out, tmp);
                iv = tmp2;
                iv2 = tmp;
                --len;
                in += AES_BLOCK_SIZE;
                out += AES_BLOCK_SIZE;
            }
            memcpy(ivec, iv.data, AES_BLOCK_SIZE);
            memcpy(ivec + AES_BLOCK_SIZE, iv2.data, AES_BLOCK_SIZE);
        }
    }
}
