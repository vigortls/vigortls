/*
 * Copyright 2001-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include <openssl/pkcs12.h>

PKCS8_PRIV_KEY_INFO *PKCS8_decrypt(X509_SIG *p8, const char *pass, int passlen)
{
    return PKCS12_item_decrypt_d2i(p8->algor, ASN1_ITEM_rptr(PKCS8_PRIV_KEY_INFO), pass,
                                   passlen, p8->digest, 1);
}
