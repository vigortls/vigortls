/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#include <stdcompat.h>
#include <stdio.h>
#include <stdlib.h>

#include <openssl/asn1t.h>
#include <openssl/x509.h>

#include "ssl_locl.h"

typedef struct {
    long version;
    long ssl_version;
    ASN1_OCTET_STRING *cipher;
    ASN1_OCTET_STRING *comp_id;
    ASN1_OCTET_STRING *master_key;
    ASN1_OCTET_STRING *session_id;
    ASN1_OCTET_STRING *key_arg;
    long time;
    long timeout;
    X509 *peer;
    ASN1_OCTET_STRING *session_id_context;
    long verify_result;
    ASN1_OCTET_STRING *tlsext_hostname;
    long tlsext_tick_lifetime_hint;
    ASN1_OCTET_STRING *tlsext_tick;
    long flags;
} SSL_SESSION_ASN1;

ASN1_SEQUENCE(SSL_SESSION_ASN1) = {
    ASN1_SIMPLE(SSL_SESSION_ASN1, version, LONG),
    ASN1_SIMPLE(SSL_SESSION_ASN1, ssl_version, LONG),
    ASN1_SIMPLE(SSL_SESSION_ASN1, cipher, ASN1_OCTET_STRING),
    ASN1_SIMPLE(SSL_SESSION_ASN1, session_id, ASN1_OCTET_STRING),
    ASN1_SIMPLE(SSL_SESSION_ASN1, master_key, ASN1_OCTET_STRING),
    ASN1_IMP_OPT(SSL_SESSION_ASN1, key_arg, ASN1_OCTET_STRING, 0),
    ASN1_EXP_OPT(SSL_SESSION_ASN1, time, ZLONG, 1),
    ASN1_EXP_OPT(SSL_SESSION_ASN1, timeout, ZLONG, 2),
    ASN1_EXP_OPT(SSL_SESSION_ASN1, peer, X509, 3),
    ASN1_EXP_OPT(SSL_SESSION_ASN1, session_id_context, ASN1_OCTET_STRING, 4),
    ASN1_EXP_OPT(SSL_SESSION_ASN1, verify_result, ZLONG, 5),
    ASN1_EXP_OPT(SSL_SESSION_ASN1, tlsext_tick_lifetime_hint, ZLONG, 9),
    ASN1_EXP_OPT(SSL_SESSION_ASN1, tlsext_tick, ASN1_OCTET_STRING, 10),
    ASN1_EXP_OPT(SSL_SESSION_ASN1, comp_id, ASN1_OCTET_STRING, 11),
    ASN1_EXP_OPT(SSL_SESSION_ASN1, flags, ZLONG, 13)
} ASN1_SEQUENCE_END(SSL_SESSION_ASN1)

IMPLEMENT_STATIC_ASN1_ENCODE_FUNCTIONS(SSL_SESSION_ASN1)

/* Utility functions for i2d_SSL_SESSION */

/* Initialise OCTET STRING from buffer and length */

static void ssl_session_oinit(ASN1_OCTET_STRING **dest, ASN1_OCTET_STRING *os,
                              uint8_t *data, size_t len)
{
    os->data = data;
    os->length = len;
    os->flags = 0;
    *dest = os;
}

/* Initialise OCTET STRING from string */
static void ssl_session_sinit(ASN1_OCTET_STRING **dest, ASN1_OCTET_STRING *os,
                              char *data)
{
    if (data != NULL)
        ssl_session_oinit(dest, os, (uint8_t *)data, strlen(data));
    else
        *dest = NULL;
}

int i2d_SSL_SESSION(SSL_SESSION *in, uint8_t **pp)
{

    SSL_SESSION_ASN1 as;

    ASN1_OCTET_STRING cipher;
    uint8_t cipher_data[2];
    ASN1_OCTET_STRING master_key, session_id, sid_ctx;
    ASN1_OCTET_STRING tlsext_hostname, tlsext_tick;
    long l;

    if ((in == NULL) || ((in->cipher == NULL) && (in->cipher_id == 0)))
        return 0;

    memset(&as, 0, sizeof(as));

    as.version = SSL_SESSION_ASN1_VERSION;
    as.ssl_version = in->ssl_version;

    if (in->cipher == NULL)
        l = in->cipher_id;
    else
        l = in->cipher->id;
    cipher_data[0] = ((uint8_t)(l >> 8L)) & 0xff;
    cipher_data[1] = ((uint8_t)(l)) & 0xff;

    ssl_session_oinit(&as.cipher, &cipher, cipher_data, 2);

    ssl_session_oinit(&as.master_key, &master_key,
                      in->master_key, in->master_key_length);

    ssl_session_oinit(&as.session_id, &session_id,
                      in->session_id, in->session_id_length);

    ssl_session_oinit(&as.session_id_context, &sid_ctx,
                      in->sid_ctx, in->sid_ctx_length);

    as.time = in->time;
    as.timeout = in->timeout;
    as.verify_result = in->verify_result;

    as.peer = in->peer;

    ssl_session_sinit(&as.tlsext_hostname, &tlsext_hostname,
                      in->tlsext_hostname);
    if (in->tlsext_tick) {
        ssl_session_oinit(&as.tlsext_tick, &tlsext_tick,
                          in->tlsext_tick, in->tlsext_ticklen);
    }
    if (in->tlsext_tick_lifetime_hint > 0)
        as.tlsext_tick_lifetime_hint = in->tlsext_tick_lifetime_hint;

    as.flags = in->flags;

    return i2d_SSL_SESSION_ASN1(&as, pp);

}

/* Utility functions for d2i_SSL_SESSION */

/* BUF_strndup an OCTET STRING */

static int ssl_session_strndup(char **pdst, ASN1_OCTET_STRING *src)
{
    if (*pdst) {
        free(*pdst);
        *pdst = NULL;
    }
    if (src == NULL)
        return 1;
    *pdst = strndup((char *)src->data, src->length);
    if (*pdst == NULL)
        return 0;
    return 1;
}

/* Copy an OCTET STRING, return error if it exceeds maximum length */

static int ssl_session_memcpy(uint8_t *dst, unsigned int *pdstlen,
                              ASN1_OCTET_STRING *src, int maxlen)
{
    if (src == NULL) {
        *pdstlen = 0;
        return 1;
    }
    if (src->length > maxlen)
        return 0;
    memcpy(dst, src->data, src->length);
    *pdstlen = src->length;
    return 1;
}

SSL_SESSION *d2i_SSL_SESSION(SSL_SESSION **a, const uint8_t **pp,
                             long length)
{
    long id;
    unsigned int tmpl;
    const uint8_t *p = *pp;
    SSL_SESSION_ASN1 *as = NULL;
    SSL_SESSION *ret = NULL;

    as = d2i_SSL_SESSION_ASN1(NULL, &p, length);
    /* ASN.1 code returns suitable error */
    if (as == NULL)
        goto err;

    if (0) {
        i2d_SSL_SESSION_ASN1(NULL, NULL);
    }

    if (!a || !*a) {
        ret = SSL_SESSION_new();
        if (ret == NULL)
            goto err;
    } else {
        ret = *a;
    }

    if (as->version != SSL_SESSION_ASN1_VERSION) {
        SSLerr(SSL_F_D2I_SSL_SESSION, SSL_R_UNKNOWN_SSL_VERSION);
        goto err;
    }

    if ((as->ssl_version >> 8) != SSL3_VERSION_MAJOR
        && (as->ssl_version >> 8) != DTLS1_VERSION_MAJOR)
    {
        SSLerr(SSL_F_D2I_SSL_SESSION, SSL_R_UNSUPPORTED_SSL_VERSION);
        goto err;
    }

    ret->ssl_version = (int)as->ssl_version;

    if (as->cipher->length != 2) {
        SSLerr(SSL_F_D2I_SSL_SESSION, SSL_R_CIPHER_CODE_WRONG_LENGTH);
        goto err;
    }

    p = as->cipher->data;
    id = 0x03000000L | ((unsigned long)p[0] << 8L) | (unsigned long)p[1];

    ret->cipher = NULL;
    ret->cipher_id = id;

    if (!ssl_session_memcpy(ret->session_id, &ret->session_id_length,
                            as->session_id, SSL3_MAX_SSL_SESSION_ID_LENGTH))
        goto err;

    if (!ssl_session_memcpy(ret->master_key, &tmpl,
                            as->master_key, SSL_MAX_MASTER_KEY_LENGTH))
        goto err;

    ret->master_key_length = tmpl;

    if (as->time != 0)
        ret->time = as->time;
    else
        ret->time = (unsigned long)time(NULL);

    if (as->timeout != 0)
        ret->timeout = as->timeout;
    else
        ret->timeout = 3;

    X509_free(ret->peer);
    ret->peer = as->peer;
    as->peer = NULL;

    if (!ssl_session_memcpy(ret->sid_ctx, &ret->sid_ctx_length,
                            as->session_id_context, SSL_MAX_SID_CTX_LENGTH))
        goto err;

    /* NB: this defaults to zero which is X509_V_OK */
    ret->verify_result = as->verify_result;

    if (!ssl_session_strndup(&ret->tlsext_hostname, as->tlsext_hostname))
        goto err;

    ret->tlsext_tick_lifetime_hint = as->tlsext_tick_lifetime_hint;
    if (as->tlsext_tick) {
        ret->tlsext_tick = as->tlsext_tick->data;
        ret->tlsext_ticklen = as->tlsext_tick->length;
        as->tlsext_tick->data = NULL;
    } else {
        ret->tlsext_tick = NULL;
    }
    /* Flags defaults to zero which is fine */
    ret->flags = as->flags;

    M_ASN1_free_of(as, SSL_SESSION_ASN1);

    if ((a != NULL) && (*a == NULL))
        *a = ret;
    *pp = p;
    return ret;

err:
    M_ASN1_free_of(as, SSL_SESSION_ASN1);
    if ((a == NULL) || (*a != ret))
        SSL_SESSION_free(ret);
    return NULL;
}
