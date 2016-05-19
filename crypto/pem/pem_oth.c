/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>

#include <openssl/buffer.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/objects.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/x509.h>

/* Handle 'other' PEMs: not private keys */

void *PEM_ASN1_read_bio(d2i_of_void *d2i, const char *name, BIO *bp, void **x,
                        pem_password_cb *cb, void *u)
{
    const uint8_t *p = NULL;
    uint8_t *data = NULL;
    long len;
    char *ret = NULL;

    if (!PEM_bytes_read_bio(&data, &len, NULL, name, bp, cb, u))
        return NULL;
    p = data;
    ret = d2i(x, &p, len);
    if (ret == NULL)
        PEMerr(PEM_F_PEM_ASN1_READ_BIO, ERR_R_ASN1_LIB);
    free(data);
    return (ret);
}
