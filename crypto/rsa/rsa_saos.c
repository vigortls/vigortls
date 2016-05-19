/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <string.h>

#include <openssl/bn.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/objects.h>
#include <openssl/x509.h>

int RSA_sign_ASN1_OCTET_STRING(int type,
                               const uint8_t *m, unsigned int m_len,
                               uint8_t *sigret, unsigned int *siglen, RSA *rsa)
{
    ASN1_OCTET_STRING sig;
    int i, j, ret = 1;
    uint8_t *p, *s;

    sig.type = V_ASN1_OCTET_STRING;
    sig.length = m_len;
    sig.data = (uint8_t *)m;

    i = i2d_ASN1_OCTET_STRING(&sig, NULL);
    j = RSA_size(rsa);
    if (i > (j - RSA_PKCS1_PADDING_SIZE)) {
        RSAerr(RSA_F_RSA_SIGN_ASN1_OCTET_STRING, RSA_R_DIGEST_TOO_BIG_FOR_RSA_KEY);
        return (0);
    }
    s = malloc((unsigned int)j + 1);
    if (s == NULL) {
        RSAerr(RSA_F_RSA_SIGN_ASN1_OCTET_STRING, ERR_R_MALLOC_FAILURE);
        return (0);
    }
    p = s;
    i2d_ASN1_OCTET_STRING(&sig, &p);
    i = RSA_private_encrypt(i, s, sigret, rsa, RSA_PKCS1_PADDING);
    if (i <= 0)
        ret = 0;
    else
        *siglen = i;

    vigortls_zeroize(s, (unsigned int)j + 1);
    free(s);
    return (ret);
}

int RSA_verify_ASN1_OCTET_STRING(int dtype, const uint8_t *m,
                                 unsigned int m_len, uint8_t *sigbuf,
                                 unsigned int siglen, RSA *rsa)
{
    int i, ret = 0;
    uint8_t *s;
    const uint8_t *p;
    ASN1_OCTET_STRING *sig = NULL;

    if (siglen != (unsigned int)RSA_size(rsa)) {
        RSAerr(RSA_F_RSA_VERIFY_ASN1_OCTET_STRING, RSA_R_WRONG_SIGNATURE_LENGTH);
        return (0);
    }

    s = malloc(siglen);
    if (s == NULL) {
        RSAerr(RSA_F_RSA_VERIFY_ASN1_OCTET_STRING, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    i = RSA_public_decrypt((int)siglen, sigbuf, s, rsa, RSA_PKCS1_PADDING);
    if (i <= 0)
        goto err;

    p = s;
    sig = d2i_ASN1_OCTET_STRING(NULL, &p, (long)i);
    if (sig == NULL)
        goto err;

    if (((unsigned int)sig->length != m_len) || (memcmp(m, sig->data, m_len) != 0)) {
        RSAerr(RSA_F_RSA_VERIFY_ASN1_OCTET_STRING, RSA_R_BAD_SIGNATURE);
    } else
        ret = 1;
err:
    ASN1_OCTET_STRING_free(sig);
    vigortls_zeroize(s, (unsigned int)siglen);
    free(s);
    return ret;
}
