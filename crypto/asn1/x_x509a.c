/*
 * Copyright 1999-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/asn1t.h>
#include <openssl/x509.h>

/* X509_CERT_AUX routines. These are used to encode additional
 * user modifiable data about a certificate. This data is
 * appended to the X509 encoding when the *_X509_AUX routines
 * are used. This means that the "traditional" X509 routines
 * will simply ignore the extra data.
 */

static X509_CERT_AUX *aux_get(X509 *x);

ASN1_SEQUENCE(X509_CERT_AUX) = {
    ASN1_SEQUENCE_OF_OPT(X509_CERT_AUX, trust, ASN1_OBJECT),
    ASN1_IMP_SEQUENCE_OF_OPT(X509_CERT_AUX, reject, ASN1_OBJECT, 0),
    ASN1_OPT(X509_CERT_AUX, alias, ASN1_UTF8STRING),
    ASN1_OPT(X509_CERT_AUX, keyid, ASN1_OCTET_STRING),
    ASN1_IMP_SEQUENCE_OF_OPT(X509_CERT_AUX, other, X509_ALGOR, 1)
} ASN1_SEQUENCE_END(X509_CERT_AUX)

X509_CERT_AUX *d2i_X509_CERT_AUX(X509_CERT_AUX **a, const uint8_t **in, long len)
{
    return (X509_CERT_AUX *)ASN1_item_d2i((ASN1_VALUE **)a, in, len, &X509_CERT_AUX_it);
}

int i2d_X509_CERT_AUX(X509_CERT_AUX *a, uint8_t **out)
{
    return ASN1_item_i2d((ASN1_VALUE *)a, out, &X509_CERT_AUX_it);
}

X509_CERT_AUX *X509_CERT_AUX_new(void)
{
    return (X509_CERT_AUX *)ASN1_item_new(&X509_CERT_AUX_it);
}

void X509_CERT_AUX_free(X509_CERT_AUX *a)
{
    ASN1_item_free((ASN1_VALUE *)a, &X509_CERT_AUX_it);
}

static X509_CERT_AUX * aux_get(X509 * x)
{
    if (!x)
        return NULL;
    if (!x->aux && !(x->aux = X509_CERT_AUX_new()))
        return NULL;
    return x->aux;
}

int X509_alias_set1(X509 *x, uint8_t *name, int len)
{
    X509_CERT_AUX *aux;
    if (!name) {
        if (!x || !x->aux || !x->aux->alias)
            return 1;
        ASN1_UTF8STRING_free(x->aux->alias);
        x->aux->alias = NULL;
        return 1;
    }
    if (!(aux = aux_get(x)))
        return 0;
    if (!aux->alias && !(aux->alias = ASN1_UTF8STRING_new()))
        return 0;
    return ASN1_STRING_set(aux->alias, name, len);
}

int X509_keyid_set1(X509 *x, uint8_t *id, int len)
{
    X509_CERT_AUX *aux;
    if (!id) {
        if (!x || !x->aux || !x->aux->keyid)
            return 1;
        ASN1_OCTET_STRING_free(x->aux->keyid);
        x->aux->keyid = NULL;
        return 1;
    }
    if (!(aux = aux_get(x)))
        return 0;
    if (!aux->keyid && !(aux->keyid = ASN1_OCTET_STRING_new()))
        return 0;
    return ASN1_STRING_set(aux->keyid, id, len);
}

uint8_t *X509_alias_get0(X509 *x, int *len)
{
    if (!x->aux || !x->aux->alias)
        return NULL;
    if (len)
        *len = x->aux->alias->length;
    return x->aux->alias->data;
}

uint8_t *X509_keyid_get0(X509 *x, int *len)
{
    if (!x->aux || !x->aux->keyid)
        return NULL;
    if (len)
        *len = x->aux->keyid->length;
    return x->aux->keyid->data;
}

int X509_add1_trust_object(X509 *x, ASN1_OBJECT *obj)
{
    X509_CERT_AUX *aux;
    ASN1_OBJECT *objtmp = NULL;

    if (obj) {
        objtmp = OBJ_dup(obj);
        if (!objtmp)
            return 0;
    }
    if (!(aux = aux_get(x)))
        goto err;
    if (!aux->trust && !(aux->trust = sk_ASN1_OBJECT_new_null()))
        goto err;
    if (!objtmp || sk_ASN1_OBJECT_push(aux->trust, objtmp))
        return 1;
err:
    if (objtmp)
        ASN1_OBJECT_free(objtmp);
    return 0;
}

int X509_add1_reject_object(X509 *x, ASN1_OBJECT *obj)
{
    X509_CERT_AUX *aux;
    ASN1_OBJECT *objtmp = NULL;

    if (obj) {
        objtmp = OBJ_dup(obj);
        if (!objtmp)
            return 0;
    }
    if(!(aux = aux_get(x)))
        goto err;
    if (!aux->reject && !(aux->reject = sk_ASN1_OBJECT_new_null()))
        goto err;

    return sk_ASN1_OBJECT_push(aux->reject, objtmp);

err:
    if (objtmp)
        ASN1_OBJECT_free(objtmp);
    return 0;
}

void X509_trust_clear(X509 *x)
{
    if (x->aux && x->aux->trust) {
        sk_ASN1_OBJECT_pop_free(x->aux->trust, ASN1_OBJECT_free);
        x->aux->trust = NULL;
    }
}

void X509_reject_clear(X509 *x)
{
    if (x->aux && x->aux->reject) {
        sk_ASN1_OBJECT_pop_free(x->aux->reject, ASN1_OBJECT_free);
        x->aux->reject = NULL;
    }
}
