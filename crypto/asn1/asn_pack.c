/*
 * Copyright 1999-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>

#include <openssl/asn1.h>
#include <openssl/err.h>

/* ASN1 packing and unpacking functions */

ASN1_STRING *ASN1_item_pack(void *obj, const ASN1_ITEM *it, ASN1_STRING **oct)
{
    ASN1_STRING *octmp;

    if (!oct || !*oct) {
        if (!(octmp = ASN1_STRING_new())) {
            ASN1err(ASN1_F_ASN1_ITEM_PACK, ERR_R_MALLOC_FAILURE);
            return NULL;
        }
        if (oct)
            *oct = octmp;
    } else
        octmp = *oct;

    if (octmp->data) {
        free(octmp->data);
        octmp->data = NULL;
    }

    if (!(octmp->length = ASN1_item_i2d(obj, &octmp->data, it))) {
        ASN1err(ASN1_F_ASN1_ITEM_PACK, ASN1_R_ENCODE_ERROR);
        return NULL;
    }
    if (!octmp->data) {
        ASN1err(ASN1_F_ASN1_ITEM_PACK, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    return octmp;
}

/* Extract an ASN1 object from an ASN1_STRING */

void *ASN1_item_unpack(ASN1_STRING *oct, const ASN1_ITEM *it)
{
    const uint8_t *p;
    void *ret;

    p = oct->data;
    if (!(ret = ASN1_item_d2i(NULL, &p, oct->length, it)))
        ASN1err(ASN1_F_ASN1_ITEM_UNPACK, ASN1_R_DECODE_ERROR);
    return ret;
}
