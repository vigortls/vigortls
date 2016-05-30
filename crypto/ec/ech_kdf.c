/*
 * Copyright 2013-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <openssl/ecdh.h>
#include <openssl/evp.h>
#include <string.h>

/* Key derivation function from X9.62/SECG */

#define ECDH_KDF_MAX (1L << 31)

int ECDH_KDF_X9_62(uint8_t *out, size_t outlen, const uint8_t *Z, size_t Zlen,
                   const uint8_t *sinfo, size_t sinfolen, const EVP_MD *md)
{
    EVP_MD_CTX mctx;
    int rv = 0;
    unsigned int i;
    size_t mdlen;
    uint8_t ctr[4];
    if (sinfolen > ECDH_KDF_MAX || outlen > ECDH_KDF_MAX || Zlen > ECDH_KDF_MAX)
        return 0;
    mdlen = EVP_MD_size(md);
    EVP_MD_CTX_init(&mctx);
    for (i = 1;; i++) {
        uint8_t mtmp[EVP_MAX_MD_SIZE];
        EVP_DigestInit_ex(&mctx, md, NULL);
        ctr[3] = i & 0xFF;
        ctr[2] = (i >> 8) & 0xFF;
        ctr[1] = (i >> 16) & 0xFF;
        ctr[0] = (i >> 24) & 0xFF;
        if (!EVP_DigestUpdate(&mctx, Z, Zlen))
            goto err;
        if (!EVP_DigestUpdate(&mctx, ctr, sizeof(ctr)))
            goto err;
        if (!EVP_DigestUpdate(&mctx, sinfo, sinfolen))
            goto err;
        if (outlen > mdlen) {
            if (!EVP_DigestFinal(&mctx, out, NULL))
                goto err;
            outlen -= mdlen;
            if (outlen == 0)
                break;
            out += mdlen;
        } else {
            if (!EVP_DigestFinal(&mctx, mtmp, NULL))
                goto err;
            memcpy(out, mtmp, outlen);
            vigortls_zeroize(mtmp, mdlen);
            break;
        }
    }
    rv = 1;
err:
    EVP_MD_CTX_cleanup(&mctx);
    return rv;
}