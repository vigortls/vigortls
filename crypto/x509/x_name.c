/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <ctype.h>
#include <string.h>

#include <openssl/asn1t.h>
#include <openssl/err.h>
#include <openssl/x509.h>

#include "internal/x509_int.h"
#include "internal/asn1_int.h"

typedef STACK_OF(X509_NAME_ENTRY) STACK_OF_X509_NAME_ENTRY;
DECLARE_STACK_OF(STACK_OF_X509_NAME_ENTRY)

/*
 * Maximum length of X509_NAME: much larger than anything we should
 * ever see in practice.
 */
#define X509_NAME_MAX (1024 * 1024)

static int x509_name_ex_d2i(ASN1_VALUE **val,
                            const uint8_t **in, long len,
                            const ASN1_ITEM *it,
                            int tag, int aclass, char opt, ASN1_TLC *ctx);

static int x509_name_ex_i2d(ASN1_VALUE **val, uint8_t **out,
                            const ASN1_ITEM *it, int tag, int aclass);
static int x509_name_ex_new(ASN1_VALUE **val, const ASN1_ITEM *it);
static void x509_name_ex_free(ASN1_VALUE **val, const ASN1_ITEM *it);

static int x509_name_encode(X509_NAME *a);
static int x509_name_canon(X509_NAME *a);
static int asn1_string_canon(ASN1_STRING *out, ASN1_STRING *in);
static int i2d_name_canon(STACK_OF(STACK_OF_X509_NAME_ENTRY) *intname,
                          uint8_t **in);

static int x509_name_ex_print(BIO *out, ASN1_VALUE **pval,
                              int indent,
                              const char *fname,
                              const ASN1_PCTX *pctx);

ASN1_SEQUENCE(X509_NAME_ENTRY) = {
    ASN1_SIMPLE(X509_NAME_ENTRY, object, ASN1_OBJECT),
    ASN1_SIMPLE(X509_NAME_ENTRY, value, ASN1_PRINTABLE)
} ASN1_SEQUENCE_END(X509_NAME_ENTRY)

X509_NAME_ENTRY *d2i_X509_NAME_ENTRY(X509_NAME_ENTRY **a, const uint8_t **in, long len)
{
    return (X509_NAME_ENTRY *)ASN1_item_d2i((ASN1_VALUE **)a, in, len, &X509_NAME_ENTRY_it);
}

int i2d_X509_NAME_ENTRY(X509_NAME_ENTRY *a, uint8_t **out)
{
    return ASN1_item_i2d((ASN1_VALUE *)a, out, &X509_NAME_ENTRY_it);
}

X509_NAME_ENTRY *X509_NAME_ENTRY_new(void)
{
    return (X509_NAME_ENTRY *)ASN1_item_new(&X509_NAME_ENTRY_it);
}

void X509_NAME_ENTRY_free(X509_NAME_ENTRY *a)
{
    ASN1_item_free((ASN1_VALUE *)a, &X509_NAME_ENTRY_it);
}

X509_NAME_ENTRY *X509_NAME_ENTRY_dup(X509_NAME_ENTRY *x)
{
    return ASN1_item_dup(&X509_NAME_ENTRY_it, x);
}

/* For the "Name" type we need a SEQUENCE OF { SET OF X509_NAME_ENTRY }
 * so declare two template wrappers for this
 */

ASN1_ITEM_TEMPLATE(X509_NAME_ENTRIES) = ASN1_EX_TEMPLATE_TYPE(ASN1_TFLG_SET_OF, 0, RDNS, X509_NAME_ENTRY)
ASN1_ITEM_TEMPLATE_END(X509_NAME_ENTRIES)

ASN1_ITEM_TEMPLATE(X509_NAME_INTERNAL) = ASN1_EX_TEMPLATE_TYPE(ASN1_TFLG_SEQUENCE_OF, 0, Name, X509_NAME_ENTRIES)
ASN1_ITEM_TEMPLATE_END(X509_NAME_INTERNAL)

/* Normally that's where it would end: we'd have two nested STACK structures
 * representing the ASN1. Unfortunately X509_NAME uses a completely different
 * form and caches encodings so we have to process the internal form and convert
 * to the external form.
 */

const ASN1_EXTERN_FUNCS x509_name_ff = {
    NULL,
    x509_name_ex_new,
    x509_name_ex_free,
    0, /* Default clear behaviour is OK */
    x509_name_ex_d2i,
    x509_name_ex_i2d,
    x509_name_ex_print
};

IMPLEMENT_EXTERN_ASN1(X509_NAME, V_ASN1_SEQUENCE, x509_name_ff)

X509_NAME *d2i_X509_NAME(X509_NAME **a, const uint8_t **in, long len)
{
    return (X509_NAME *)ASN1_item_d2i((ASN1_VALUE **)a, in, len, &X509_NAME_it);
}

int i2d_X509_NAME(X509_NAME *a, uint8_t **out)
{
    return ASN1_item_i2d((ASN1_VALUE *)a, out, &X509_NAME_it);
}

X509_NAME *X509_NAME_new(void)
{
    return (X509_NAME *)ASN1_item_new(&X509_NAME_it);
}

void X509_NAME_free(X509_NAME *a)
{
    ASN1_item_free((ASN1_VALUE *)a, &X509_NAME_it);
}

X509_NAME *X509_NAME_dup(X509_NAME *x)
{
    return ASN1_item_dup(&X509_NAME_it, x);
}

static int x509_name_ex_new(ASN1_VALUE **val, const ASN1_ITEM *it)
{
    X509_NAME *ret = NULL;
    ret = malloc(sizeof(X509_NAME));
    if (!ret)
        goto memerr;
    if ((ret->entries = sk_X509_NAME_ENTRY_new_null()) == NULL)
        goto memerr;
    if ((ret->bytes = BUF_MEM_new()) == NULL)
        goto memerr;
    ret->canon_enc = NULL;
    ret->canon_enclen = 0;
    ret->modified = 1;
    *val = (ASN1_VALUE *)ret;
    return 1;

memerr:
    ASN1err(ASN1_F_X509_NAME_EX_NEW, ERR_R_MALLOC_FAILURE);
    if (ret) {
        if (ret->entries)
            sk_X509_NAME_ENTRY_free(ret->entries);
        free(ret);
    }
    return 0;
}

static void x509_name_ex_free(ASN1_VALUE **pval, const ASN1_ITEM *it)
{
    X509_NAME *a;
    if (!pval || !*pval)
        return;
    a = (X509_NAME *)*pval;

    BUF_MEM_free(a->bytes);
    sk_X509_NAME_ENTRY_pop_free(a->entries, X509_NAME_ENTRY_free);
    free(a->canon_enc);
    free(a);
    *pval = NULL;
}

static int x509_name_ex_d2i(ASN1_VALUE **val,
                            const uint8_t **in, long len, const ASN1_ITEM *it,
                            int tag, int aclass, char opt, ASN1_TLC *ctx)
{
    const uint8_t *p = *in, *q;
    union {
        STACK_OF(STACK_OF_X509_NAME_ENTRY) *s;
        ASN1_VALUE *a;
    } intname = { NULL };
    union {
        X509_NAME *x;
        ASN1_VALUE *a;
    } nm = { NULL };
    int i, j, ret;
    STACK_OF(X509_NAME_ENTRY) *entries;
    X509_NAME_ENTRY *entry;
    
    if (len > X509_NAME_MAX) {
        len = X509_NAME_MAX;
    }
    q = p;

    /* Get internal representation of Name */
    ret = ASN1_item_ex_d2i(&intname.a,
                           &p, len, ASN1_ITEM_rptr(X509_NAME_INTERNAL),
                           tag, aclass, opt, ctx);

    if (ret <= 0)
        return ret;

    if (*val)
        x509_name_ex_free(val, NULL);
    if (!x509_name_ex_new(&nm.a, NULL))
        goto err;
    /* We've decoded it: now cache encoding */
    if (!BUF_MEM_grow(nm.x->bytes, p - q))
        goto err;
    memcpy(nm.x->bytes->data, q, p - q);

    /* Convert internal representation to X509_NAME structure */
    for (i = 0; i < sk_STACK_OF_X509_NAME_ENTRY_num(intname.s); i++) {
        entries = sk_STACK_OF_X509_NAME_ENTRY_value(intname.s, i);
        for (j = 0; j < sk_X509_NAME_ENTRY_num(entries); j++) {
            entry = sk_X509_NAME_ENTRY_value(entries, j);
            entry->set = i;
            if (!sk_X509_NAME_ENTRY_push(nm.x->entries, entry))
                goto err;
        }
        sk_X509_NAME_ENTRY_free(entries);
    }
    sk_STACK_OF_X509_NAME_ENTRY_free(intname.s);
    ret = x509_name_canon(nm.x);
    if (!ret)
        goto err;
    nm.x->modified = 0;
    *val = nm.a;
    *in = p;
    return ret;
err:
    X509_NAME_free(nm.x);
    ASN1err(ASN1_F_X509_NAME_EX_D2I, ERR_R_NESTED_ASN1_ERROR);
    return 0;
}

static int x509_name_ex_i2d(ASN1_VALUE **val, uint8_t **out, const ASN1_ITEM *it, int tag, int aclass)
{
    int ret;
    X509_NAME *a = (X509_NAME *)*val;
    if (a->modified) {
        ret = x509_name_encode(a);
        if (ret < 0)
            return ret;
        ret = x509_name_canon(a);
        if (ret < 0)
            return ret;
    }
    ret = a->bytes->length;
    if (out != NULL) {
        memcpy(*out, a->bytes->data, ret);
        *out += ret;
    }
    return ret;
}

static void local_sk_X509_NAME_ENTRY_free(STACK_OF(X509_NAME_ENTRY) *ne)
{
    sk_X509_NAME_ENTRY_free(ne);
}

static void local_sk_X509_NAME_ENTRY_pop_free(STACK_OF(X509_NAME_ENTRY) *ne)
{
    sk_X509_NAME_ENTRY_pop_free(ne, X509_NAME_ENTRY_free);
}

static int x509_name_encode(X509_NAME *a)
{
    union {
        STACK_OF(STACK_OF_X509_NAME_ENTRY) *s;
        ASN1_VALUE *a;
    } intname = { NULL };
    int len;
    uint8_t *p;
    STACK_OF(X509_NAME_ENTRY) *entries = NULL;
    X509_NAME_ENTRY *entry;
    int i, set = -1;
    intname.s = sk_STACK_OF_X509_NAME_ENTRY_new_null();
    if (!intname.s)
        goto memerr;
    for (i = 0; i < sk_X509_NAME_ENTRY_num(a->entries); i++) {
        entry = sk_X509_NAME_ENTRY_value(a->entries, i);
        if (entry->set != set) {
            entries = sk_X509_NAME_ENTRY_new_null();
            if (!entries)
                goto memerr;
            if (!sk_STACK_OF_X509_NAME_ENTRY_push(intname.s,
                                                  entries))
                goto memerr;
            set = entry->set;
        }
        if (!sk_X509_NAME_ENTRY_push(entries, entry))
            goto memerr;
    }
    len = ASN1_item_ex_i2d(&intname.a, NULL,
                           ASN1_ITEM_rptr(X509_NAME_INTERNAL), -1, -1);
    if (!BUF_MEM_grow(a->bytes, len))
        goto memerr;
    p = (uint8_t *)a->bytes->data;
    ASN1_item_ex_i2d(&intname.a,
                     &p, ASN1_ITEM_rptr(X509_NAME_INTERNAL), -1, -1);
    sk_STACK_OF_X509_NAME_ENTRY_pop_free(intname.s,
                                         local_sk_X509_NAME_ENTRY_free);
    a->modified = 0;
    return len;
memerr:
    sk_STACK_OF_X509_NAME_ENTRY_pop_free(intname.s,
                                         local_sk_X509_NAME_ENTRY_free);
    ASN1err(ASN1_F_X509_NAME_ENCODE, ERR_R_MALLOC_FAILURE);
    return -1;
}

static int x509_name_ex_print(BIO *out, ASN1_VALUE **pval,
                              int indent,
                              const char *fname,
                              const ASN1_PCTX *pctx)
{
    if (X509_NAME_print_ex(out, (X509_NAME *)*pval,
                           indent, pctx->nm_flags) <= 0)
        return 0;
    return 2;
}

/* This function generates the canonical encoding of the Name structure.
 * In it all strings are converted to UTF8, leading, trailing and
 * multiple spaces collapsed, converted to lower case and the leading
 * SEQUENCE header removed.
 *
 * In future we could also normalize the UTF8 too.
 *
 * By doing this comparison of Name structures can be rapidly
 * perfomed by just using memcmp() of the canonical encoding.
 * By omitting the leading SEQUENCE name constraints of type
 * dirName can also be checked with a simple memcmp().
 */

static int x509_name_canon(X509_NAME *a)
{
    uint8_t *p;
    STACK_OF(STACK_OF_X509_NAME_ENTRY) *intname = NULL;
    STACK_OF(X509_NAME_ENTRY) *entries = NULL;
    X509_NAME_ENTRY *entry, *tmpentry = NULL;
    int i, len, set = -1, ret = 0;

    if (a->canon_enc) {
        free(a->canon_enc);
        a->canon_enc = NULL;
    }
    /* Special case: empty X509_NAME => null encoding */
    if (sk_X509_NAME_ENTRY_num(a->entries) == 0) {
        a->canon_enclen = 0;
        return 1;
    }
    intname = sk_STACK_OF_X509_NAME_ENTRY_new_null();
    if (!intname)
        goto err;
    for (i = 0; i < sk_X509_NAME_ENTRY_num(a->entries); i++) {
        entry = sk_X509_NAME_ENTRY_value(a->entries, i);
        if (entry->set != set) {
            entries = sk_X509_NAME_ENTRY_new_null();
            if (!entries)
                goto err;
            if (!sk_STACK_OF_X509_NAME_ENTRY_push(intname, entries))
                goto err;
            set = entry->set;
        }
        tmpentry = X509_NAME_ENTRY_new();
        if (tmpentry == NULL)
            goto err;
        tmpentry->object = OBJ_dup(entry->object);
        if (!asn1_string_canon(tmpentry->value, entry->value))
            goto err;
        if (!sk_X509_NAME_ENTRY_push(entries, tmpentry))
            goto err;
        tmpentry = NULL;
    }

    /* Finally generate encoding */

    len = i2d_name_canon(intname, NULL);
    if (len < 0)
        goto err;
    p = malloc(len);
    if (p == NULL)
        goto err;
    a->canon_enc = p;
    a->canon_enclen = len;
    i2d_name_canon(intname, &p);
    ret = 1;

err:
    if (tmpentry)
        X509_NAME_ENTRY_free(tmpentry);
    if (intname)
        sk_STACK_OF_X509_NAME_ENTRY_pop_free(intname,
                                             local_sk_X509_NAME_ENTRY_pop_free);
    return ret;
}

/* Bitmap of all the types of string that will be canonicalized. */

#define ASN1_MASK_CANON                                             \
    (B_ASN1_UTF8STRING | B_ASN1_BMPSTRING | B_ASN1_UNIVERSALSTRING  \
     | B_ASN1_PRINTABLESTRING | B_ASN1_T61STRING | B_ASN1_IA5STRING \
     | B_ASN1_VISIBLESTRING)

static int asn1_string_canon(ASN1_STRING *out, ASN1_STRING *in)
{
    uint8_t *to, *from;
    int len, i;

    /* If type not in bitmask just copy string across */
    if (!(ASN1_tag2bit(in->type) & ASN1_MASK_CANON)) {
        if (!ASN1_STRING_copy(out, in))
            return 0;
        return 1;
    }

    out->type = V_ASN1_UTF8STRING;
    out->length = ASN1_STRING_to_UTF8(&out->data, in);
    if (out->length == -1)
        return 0;

    to = out->data;
    from = to;

    len = out->length;

    /* Convert string in place to canonical form.
     * Ultimately we may need to handle a wider range of characters
     * but for now ignore anything with MSB set and rely on the
     * isspace() and tolower() functions.
     */

    /* Ignore leading spaces */
    while ((len > 0) && !(*from & 0x80) && isspace(*from)) {
        from++;
        len--;
    }

    to = from + len - 1;

    /* Ignore trailing spaces */
    while ((len > 0) && !(*to & 0x80) && isspace(*to)) {
        to--;
        len--;
    }

    to = out->data;

    i = 0;
    while (i < len) {
        /* If MSB set just copy across */
        if (*from & 0x80) {
            *to++ = *from++;
            i++;
        }
        /* Collapse multiple spaces */
        else if (isspace(*from)) {
            /* Copy one space across */
            *to++ = ' ';
            /* Ignore subsequent spaces. Note: don't need to
             * check len here because we know the last
             * character is a non-space so we can't overflow.
             */
            do {
                from++;
                i++;
            } while (!(*from & 0x80) && isspace(*from));
        } else {
            *to++ = tolower(*from);
            from++;
            i++;
        }
    }

    out->length = to - out->data;

    return 1;
}

static int i2d_name_canon(STACK_OF(STACK_OF_X509_NAME_ENTRY) *_intname,
                          uint8_t **in)
{
    int i, len, ltmp;
    ASN1_VALUE *v;
    STACK_OF(ASN1_VALUE) *intname = (STACK_OF(ASN1_VALUE) *)_intname;

    len = 0;
    for (i = 0; i < sk_ASN1_VALUE_num(intname); i++) {
        v = sk_ASN1_VALUE_value(intname, i);
        ltmp = ASN1_item_ex_i2d(&v, in,
                                ASN1_ITEM_rptr(X509_NAME_ENTRIES), -1, -1);
        if (ltmp < 0)
            return ltmp;
        len += ltmp;
    }
    return len;
}

int X509_NAME_set(X509_NAME **xn, X509_NAME *name)
{
    X509_NAME *in;

    if (!xn || !name)
        return (0);

    if (*xn != name) {
        in = X509_NAME_dup(name);
        if (in != NULL) {
            X509_NAME_free(*xn);
            *xn = in;
        }
    }
    return (*xn != NULL);
}
