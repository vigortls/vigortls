/*
 * Copyright 1999-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>

#include <openssl/err.h>
#include <openssl/pkcs12.h>

/* PKCS#12 PBE algorithms now in static table */

void PKCS12_PBE_add(void)
{
}

int PKCS12_PBE_keyivgen(EVP_CIPHER_CTX *ctx, const char *pass, int passlen,
                        ASN1_TYPE *param, const EVP_CIPHER *cipher, const EVP_MD *md, int en_de)
{
    PBEPARAM *pbe;
    int saltlen, iter, ret;
    uint8_t *salt;
    uint8_t key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];

    if (cipher == NULL)
        return 0;

    /* Extract useful info from parameter */

    pbe = ASN1_TYPE_unpack_sequence(ASN1_ITEM_rptr(PBEPARAM), param);
    if (pbe == NULL) {
        PKCS12err(PKCS12_F_PKCS12_PBE_KEYIVGEN, PKCS12_R_DECODE_ERROR);
        return 0;
    }

    if (!pbe->iter)
        iter = 1;
    else
        iter = ASN1_INTEGER_get(pbe->iter);
    salt = pbe->salt->data;
    saltlen = pbe->salt->length;
    if (!PKCS12_key_gen(pass, passlen, salt, saltlen, PKCS12_KEY_ID,
                        iter, EVP_CIPHER_key_length(cipher), key, md)) {
        PKCS12err(PKCS12_F_PKCS12_PBE_KEYIVGEN, PKCS12_R_KEY_GEN_ERROR);
        PBEPARAM_free(pbe);
        return 0;
    }
    if (!PKCS12_key_gen(pass, passlen, salt, saltlen, PKCS12_IV_ID,
                        iter, EVP_CIPHER_iv_length(cipher), iv, md)) {
        PKCS12err(PKCS12_F_PKCS12_PBE_KEYIVGEN, PKCS12_R_IV_GEN_ERROR);
        PBEPARAM_free(pbe);
        return 0;
    }
    PBEPARAM_free(pbe);
    ret = EVP_CipherInit_ex(ctx, cipher, NULL, key, iv, en_de);
    vigortls_zeroize(key, EVP_MAX_KEY_LENGTH);
    vigortls_zeroize(iv, EVP_MAX_IV_LENGTH);
    return ret;
}
