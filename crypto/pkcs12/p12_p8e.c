/*
 * Copyright 2001-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <openssl/err.h>
#include <openssl/pkcs12.h>

X509_SIG *PKCS8_encrypt(int pbe_nid, const EVP_CIPHER *cipher,
                        const char *pass, int passlen,
                        uint8_t *salt, int saltlen, int iter,
                        PKCS8_PRIV_KEY_INFO *p8inf)
{
    X509_SIG *p8 = NULL;
    X509_ALGOR *pbe;

    if (!(p8 = X509_SIG_new())) {
        PKCS12err(PKCS12_F_PKCS8_ENCRYPT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (pbe_nid == -1)
        pbe = PKCS5_pbe2_set(cipher, iter, salt, saltlen);
    else
        pbe = PKCS5_pbe_set(pbe_nid, iter, salt, saltlen);
    if (!pbe) {
        PKCS12err(PKCS12_F_PKCS8_ENCRYPT, ERR_R_ASN1_LIB);
        goto err;
    }
    X509_ALGOR_free(p8->algor);
    p8->algor = pbe;
    ASN1_OCTET_STRING_free(p8->digest);
    p8->digest = PKCS12_item_i2d_encrypt(pbe, ASN1_ITEM_rptr(PKCS8_PRIV_KEY_INFO),
                                         pass, passlen, p8inf, 1);
    if (!p8->digest) {
        PKCS12err(PKCS12_F_PKCS8_ENCRYPT, PKCS12_R_ENCRYPT_ERROR);
        goto err;
    }

    return p8;

err:
    X509_SIG_free(p8);
    return NULL;
}
