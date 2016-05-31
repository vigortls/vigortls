/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include <stdcompat.h>

#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/objects.h>
#include <openssl/ocsp.h>
#include <openssl/rand.h>

#include "ssl_locl.h"
#include "bytestring.h"

static int tls_decrypt_ticket(SSL *s, const uint8_t *tick, int ticklen,
                              const uint8_t *sess_id, int sesslen,
                              SSL_SESSION **psess);

SSL3_ENC_METHOD TLSv1_enc_data = {
    .enc = tls1_enc,
    .mac = tls1_mac,
    .setup_key_block = tls1_setup_key_block,
    .generate_master_secret = tls1_generate_master_secret,
    .change_cipher_state = tls1_change_cipher_state,
    .final_finish_mac = tls1_final_finish_mac,
    .finish_mac_length = TLS1_FINISH_MAC_LENGTH,
    .cert_verify_mac = tls1_cert_verify_mac,
    .client_finished_label = TLS_MD_CLIENT_FINISH_CONST,
    .client_finished_label_len = TLS_MD_CLIENT_FINISH_CONST_SIZE,
    .server_finished_label = TLS_MD_SERVER_FINISH_CONST,
    .server_finished_label_len = TLS_MD_SERVER_FINISH_CONST_SIZE,
    .alert_value = tls1_alert_code,
    .export_keying_material = tls1_export_keying_material,
    .enc_flags = 0,
    .hhlen = SSL3_HM_HEADER_LENGTH,
    .set_handshake_header = ssl3_set_handshake_header,
    .do_write = ssl3_handshake_write,
};

SSL3_ENC_METHOD TLSv1_1_enc_data = {
    .enc = tls1_enc,
    .mac = tls1_mac,
    .setup_key_block = tls1_setup_key_block,
    .generate_master_secret = tls1_generate_master_secret,
    .change_cipher_state = tls1_change_cipher_state,
    .final_finish_mac = tls1_final_finish_mac,
    .finish_mac_length = TLS1_FINISH_MAC_LENGTH,
    .cert_verify_mac = tls1_cert_verify_mac,
    .client_finished_label = TLS_MD_CLIENT_FINISH_CONST,
    .client_finished_label_len = TLS_MD_CLIENT_FINISH_CONST_SIZE,
    .server_finished_label = TLS_MD_SERVER_FINISH_CONST,
    .server_finished_label_len = TLS_MD_SERVER_FINISH_CONST_SIZE,
    .alert_value = tls1_alert_code,
    .export_keying_material = tls1_export_keying_material,
    .enc_flags = SSL_ENC_FLAG_EXPLICIT_IV,
    .hhlen = SSL3_HM_HEADER_LENGTH,
    .set_handshake_header = ssl3_set_handshake_header,
    .do_write = ssl3_handshake_write,
};

SSL3_ENC_METHOD TLSv1_2_enc_data = {
    .enc = tls1_enc,
    .mac = tls1_mac,
    .setup_key_block = tls1_setup_key_block,
    .generate_master_secret = tls1_generate_master_secret,
    .change_cipher_state = tls1_change_cipher_state,
    .final_finish_mac = tls1_final_finish_mac,
    .finish_mac_length = TLS1_FINISH_MAC_LENGTH,
    .cert_verify_mac = tls1_cert_verify_mac,
    .client_finished_label = TLS_MD_CLIENT_FINISH_CONST,
    .client_finished_label_len = TLS_MD_CLIENT_FINISH_CONST_SIZE,
    .server_finished_label = TLS_MD_SERVER_FINISH_CONST,
    .server_finished_label_len = TLS_MD_SERVER_FINISH_CONST_SIZE,
    .alert_value = tls1_alert_code,
    .export_keying_material = tls1_export_keying_material,
    .enc_flags = SSL_ENC_FLAG_EXPLICIT_IV | SSL_ENC_FLAG_SIGALGS |
        SSL_ENC_FLAG_SHA256_PRF | SSL_ENC_FLAG_TLS1_2_CIPHERS,
    .hhlen = SSL3_HM_HEADER_LENGTH,
    .set_handshake_header = ssl3_set_handshake_header,
    .do_write = ssl3_handshake_write,
};

long tls1_default_timeout(void)
{
    /* 2 hours, the 24 hours mentioned in the TLSv1 spec
     * is way too long for http, the cache would over fill */
    return (60 * 60 * 2);
}

int tls1_new(SSL *s)
{
    if (!ssl3_new(s))
        return (0);
    s->method->ssl_clear(s);
    return (1);
}

void tls1_free(SSL *s)
{
    free(s->tlsext_session_ticket);
    ssl3_free(s);
}

void tls1_clear(SSL *s)
{
    ssl3_clear(s);
    s->version = s->method->version;
}

static int nid_list[] = {
    NID_sect163k1,        /* sect163k1 (1) */
    NID_sect163r1,        /* sect163r1 (2) */
    NID_sect163r2,        /* sect163r2 (3) */
    NID_sect193r1,        /* sect193r1 (4) */
    NID_sect193r2,        /* sect193r2 (5) */
    NID_sect233k1,        /* sect233k1 (6) */
    NID_sect233r1,        /* sect233r1 (7) */
    NID_sect239k1,        /* sect239k1 (8) */
    NID_sect283k1,        /* sect283k1 (9) */
    NID_sect283r1,        /* sect283r1 (10) */
    NID_sect409k1,        /* sect409k1 (11) */
    NID_sect409r1,        /* sect409r1 (12) */
    NID_sect571k1,        /* sect571k1 (13) */
    NID_sect571r1,        /* sect571r1 (14) */
    NID_secp160k1,        /* secp160k1 (15) */
    NID_secp160r1,        /* secp160r1 (16) */
    NID_secp160r2,        /* secp160r2 (17) */
    NID_secp192k1,        /* secp192k1 (18) */
    NID_X9_62_prime192v1, /* secp192r1 (19) */
    NID_secp224k1,        /* secp224k1 (20) */
    NID_secp224r1,        /* secp224r1 (21) */
    NID_secp256k1,        /* secp256k1 (22) */
    NID_X9_62_prime256v1, /* secp256r1 (23) */
    NID_secp384r1,        /* secp384r1 (24) */
    NID_secp521r1,        /* secp521r1 (25) */
    NID_brainpoolP256r1,  /* brainpoolP256r1 (26) */        
    NID_brainpoolP384r1,  /* brainpoolP384r1 (27) */        
    NID_brainpoolP512r1,  /* brainpoolP512r1 (28) */ 
};

static const uint8_t ecformats_default[] = {
    TLSEXT_ECPOINTFORMAT_uncompressed,
    TLSEXT_ECPOINTFORMAT_ansiX962_compressed_prime,
    TLSEXT_ECPOINTFORMAT_ansiX962_compressed_char2
};

static const uint16_t eccurves_default[] = {
    14,   /* sect571r1 (14) */
    13,   /* sect571k1 (13) */
    25,   /* secp521r1 (25) */
    28,   /* brainpool512r1 (28) */ 
    11,   /* sect409k1 (11) */
    12,   /* sect409r1 (12) */
    27,   /* brainpoolP384r1 (27) */ 
    24,   /* secp384r1 (24) */
    9,    /* sect283k1 (9) */
    10,   /* sect283r1 (10) */
    26,   /* brainpoolP256r1 (26) */  
    22,   /* secp256k1 (22) */
    23,   /* secp256r1 (23) */
    8,    /* sect239k1 (8) */
    6,    /* sect233k1 (6) */
    7,    /* sect233r1 (7) */
    20,   /* secp224k1 (20) */
    21,   /* secp224r1 (21) */
    4,    /* sect193r1 (4) */
    5,    /* sect193r2 (5) */
    18,   /* secp192k1 (18) */
    19,   /* secp192r1 (19) */
    1,    /* sect163k1 (1) */
    2,    /* sect163r1 (2) */
    3,    /* sect163r2 (3) */
    15,   /* secp160k1 (15) */
    16,   /* secp160r1 (16) */
    17,   /* secp160r2 (17) */
};

static const uint16_t suiteb_curves[] =
{
    TLSEXT_curve_P_256,
    TLSEXT_curve_P_384
};

int tls1_ec_curve_id2nid(uint16_t curve_id)
{
    /* ECC curves from RFC 4492 */
    if ((curve_id < 1) || ((unsigned int)curve_id > sizeof(nid_list) / sizeof(nid_list[0])))
        return 0;
    return nid_list[curve_id - 1];
}

uint16_t tls1_ec_nid2curve_id(int nid)
{
    /* ECC curves from RFC 4492 */
    switch (nid) {
        case NID_sect163k1: /* sect163k1 (1) */
            return 1;
        case NID_sect163r1: /* sect163r1 (2) */
            return 2;
        case NID_sect163r2: /* sect163r2 (3) */
            return 3;
        case NID_sect193r1: /* sect193r1 (4) */
            return 4;
        case NID_sect193r2: /* sect193r2 (5) */
            return 5;
        case NID_sect233k1: /* sect233k1 (6) */
            return 6;
        case NID_sect233r1: /* sect233r1 (7) */
            return 7;
        case NID_sect239k1: /* sect239k1 (8) */
            return 8;
        case NID_sect283k1: /* sect283k1 (9) */
            return 9;
        case NID_sect283r1: /* sect283r1 (10) */
            return 10;
        case NID_sect409k1: /* sect409k1 (11) */
            return 11;
        case NID_sect409r1: /* sect409r1 (12) */
            return 12;
        case NID_sect571k1: /* sect571k1 (13) */
            return 13;
        case NID_sect571r1: /* sect571r1 (14) */
            return 14;
        case NID_secp160k1: /* secp160k1 (15) */
            return 15;
        case NID_secp160r1: /* secp160r1 (16) */
            return 16;
        case NID_secp160r2: /* secp160r2 (17) */
            return 17;
        case NID_secp192k1: /* secp192k1 (18) */
            return 18;
        case NID_X9_62_prime192v1: /* secp192r1 (19) */
            return 19;
        case NID_secp224k1: /* secp224k1 (20) */
            return 20;
        case NID_secp224r1: /* secp224r1 (21) */
            return 21;
        case NID_secp256k1: /* secp256k1 (22) */
            return 22;
        case NID_X9_62_prime256v1: /* secp256r1 (23) */
            return 23;
        case NID_secp384r1: /* secp384r1 (24) */
            return 24;
        case NID_secp521r1: /* secp521r1 (25) */
            return 25;
        case NID_brainpoolP256r1: /* brainpoolP256r1 (26) */
            return 26;
        case NID_brainpoolP384r1: /* brainpoolP384r1 (27) */
            return 27;
        case NID_brainpoolP512r1: /* brainpoolP512r1 (28) */
            return 28;
        default:
            return 0;
    }
}

/*
 * Return the appropriate format list. If client_formats is non-zero, return
 * the client/session formats. Otherwise return the custom format list if one
 * exists, or the default formats if a custom list has not been specified.
 */
static void tls1_get_formatlist(SSL *s, int client_formats,
                                const uint8_t **pformats, size_t *pformatslen)
{
    if (client_formats != 0) {
        *pformats = s->session->tlsext_ecpointformatlist;
        *pformatslen = s->session->tlsext_ecpointformatlist_length;
        return;
    }

    *pformats = s->tlsext_ecpointformatlist;
    *pformatslen = s->tlsext_ecpointformatlist_length;
    if (*pformats == NULL) {
        *pformats = ecformats_default;
        *pformatslen = sizeof(ecformats_default);
    }
}

/*
 * Return the appropriate curve list. If client_curves is non-zero, return
 * the client/session curves. Otherwise return the custom curve list if one
 * exists, or the default curves if a custom list has not been specified.
 */
static void tls1_get_curvelist(SSL *s, int client_curves, const uint16_t **pcurves,
                               size_t *pcurveslen)
{
    if (client_curves != 0) {
        *pcurves = s->session->tlsext_ellipticcurvelist;
        *pcurveslen = s->session->tlsext_ellipticcurvelist_length;
        return;
    }

    /* For Suite B mode only include P-256, P-384 */
    switch (tls1_suiteb(s)) {
        case SSL_CERT_FLAG_SUITEB_128_LOS:
            *pcurves = suiteb_curves;
            *pcurveslen = sizeof(suiteb_curves) / 2;
            break;

        case SSL_CERT_FLAG_SUITEB_128_LOS_ONLY:
            *pcurves = suiteb_curves;
            *pcurveslen = 2;
            break;

        case SSL_CERT_FLAG_SUITEB_192_LOS:
            *pcurves = suiteb_curves + 2;
            *pcurveslen = 2;
            break;

        default:
            *pcurves = s->tlsext_ellipticcurvelist;
            *pcurveslen = s->tlsext_ellipticcurvelist_length;
            break;
    }
    if (*pcurves == NULL) {
        *pcurves = eccurves_default;
        *pcurveslen = sizeof(eccurves_default) / 2;
    }
}

/* Check that a curve is one of our preferences. */
int tls1_check_curve(SSL *s, const uint8_t *p, size_t len)
{
    CBS cbs;
    uint8_t type;
    const uint16_t *curves;
    uint16_t curve_id;
    size_t curves_len, i;
    unsigned int suiteb_flags = tls1_suiteb(s);

    CBS_init(&cbs, p, len);

    /* Only named curves are supported. */
    if (CBS_len(&cbs) != 3 || !CBS_get_u8(&cbs, &type) ||
        type != NAMED_CURVE_TYPE ||
        !CBS_get_u16(&cbs, &curve_id))
        return 0;

    /* Check curve matches Suite B preferences */
    if (suiteb_flags) {
        unsigned long cid = s->s3->tmp.new_cipher->id;
        if (cid == TLS1_CK_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256) {
            if (curve_id != TLSEXT_curve_P_256)
                return 0;
        } else if (cid == TLS1_CK_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384) {
            if (curve_id != TLSEXT_curve_P_384)
                return 0;
        } else {
            /* Should never happen */
            return 0;
        }
    }

    tls1_get_curvelist(s, 0, &curves, &curves_len);

    for (i = 0; i < curves_len; i++) {
        if (curves[i] == curve_id)
            return 1;
    }
    return 0;
}

/*
 * Return nth shared curve. If nmatch == -1 return number of matches. For
 * nmatch == -2 return the NID of the curve to use for an EC tmp key.
 */
int tls1_shared_curve(SSL *s, int nmatch)
{
    const uint16_t *pref, *supp;
    unsigned long server_pref;
    size_t pref_len, supp_len, i, j;
    int k = 0;

    /* Cannot do anything on the client side. */
    if (s->server == 0)
        return -1;

    if (nmatch == -2) {
        if (tls1_suiteb(s)) {
            /* For Suite B ciphersuite determines curve: we already know these
             * are acceptable due to previous checks.
             */
            unsigned long cid = s->s3->tmp.new_cipher->id;
            if (cid == TLS1_CK_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256)
                return NID_X9_62_prime256v1; /* P-256 */
            if (cid == TLS1_CK_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384)
                return NID_secp384r1; /* P-384 */
            /* Should never happen */
            return NID_undef;
        }
        /* If not Suite B just return first preference shared curve */
        nmatch = 0;
    }

    server_pref = (s->options & SSL_OP_CIPHER_SERVER_PREFERENCE);
    tls1_get_curvelist(s, (server_pref == 0), &pref, &pref_len);
    tls1_get_curvelist(s, (server_pref != 0), &supp, &supp_len);

    for (i = 0; i < pref_len; i++) {
        for (j = 0; j < supp_len; j++) {
            if (pref[i] == supp[j]) {
                if (nmatch == k)
                    return tls1_ec_curve_id2nid(pref[i]);
                k++;
            }
        }
    }
    if (nmatch == -1)
        return k;
    return NID_undef;
}

int tls1_set_curves(uint16_t **pext, size_t *pextlen, int *curves,
                    size_t ncurves)
{
    uint16_t *clist;
    size_t i;
    /*
     * Bitmap of curves included to detect duplicates: only works
     * while curve ids < 32
     */
    unsigned long dup_list = 0;
    clist = reallocarray(NULL, ncurves, 2);
    if (clist == NULL)
        return 0;
    for (i = 0; i < ncurves; i++) {
        unsigned long idmask;
        int id;
        id = tls1_ec_nid2curve_id(curves[i]);
        idmask = 1L << id;
        if (!id || (dup_list & idmask)) {
            free(clist);
            return 0;
        }
        dup_list |= idmask;
    }
    free(*pext);
    *pext = clist;
    *pextlen = ncurves * 2;
    return 1;
}

#define MAX_CURVELIST 25

typedef struct {
    size_t nidcnt;
    int nid_arr[MAX_CURVELIST];
} nid_cb_st;

static int nid_cb(const char *elem, int len, void *arg)
{
    nid_cb_st *narg = arg;
    size_t i;
    int nid;
    char etmp[20];
    if (narg->nidcnt == MAX_CURVELIST)
        return 0;
    if (len > (int)(sizeof(etmp) - 1))
        return 0;
    memcpy(etmp, elem, len);
    etmp[len] = 0;
    nid       = EC_curve_nist2nid(etmp);
    if (nid == NID_undef)
        nid = OBJ_sn2nid(etmp);
    if (nid == NID_undef)
        nid = OBJ_ln2nid(etmp);
    if (nid == NID_undef)
        return 0;
    for (i = 0; i < narg->nidcnt; i++)
        if (narg->nid_arr[i] == nid)
            return 0;
    narg->nid_arr[narg->nidcnt++] = nid;
    return 1;
}
/* Set curves based on a colon separate list */
int tls1_set_curves_list(uint16_t **pext, size_t *pextlen, const char *str)
{
    nid_cb_st ncb;
    ncb.nidcnt = 0;
    if (!CONF_parse_list(str, ':', 1, nid_cb, &ncb))
        return 0;
    if (pext == NULL)
        return 1;
    return tls1_set_curves(pext, pextlen, ncb.nid_arr, ncb.nidcnt);
}

/* For an EC key set TLS ID and required compression based on parameters. */
static int tls1_set_ec_id(uint16_t *curve_id, uint8_t *comp_id, EC_KEY *ec)
{
    const EC_GROUP *grp;
    const EC_METHOD *meth;
    int is_prime = 0;
    int nid, id;

    if (ec == NULL)
        return 0;

    /* Determine if it is a prime field. */
    if ((grp = EC_KEY_get0_group(ec)) == NULL)
        return 0;
    if ((meth = EC_GROUP_method_of(grp)) == NULL)
        return 0;
    if (EC_METHOD_get_field_type(meth) == NID_X9_62_prime_field)
        is_prime = 1;

    /* Determine curve ID. */
    nid = EC_GROUP_get_curve_name(grp);
    id = tls1_ec_nid2curve_id(nid);

    /* If we have an ID set it, otherwise set arbitrary explicit curve. */
    if (id != 0)
        *curve_id = id;
    else
        *curve_id = is_prime ? 0xff01 : 0xff02;

    /* Specify the compression identifier. */
    if (comp_id != NULL) {
        if (EC_KEY_get0_public_key(ec) == NULL)
            return 0;

        if (EC_KEY_get_conv_form(ec) == POINT_CONVERSION_COMPRESSED) {
            *comp_id = is_prime ?
                TLSEXT_ECPOINTFORMAT_ansiX962_compressed_prime :
                TLSEXT_ECPOINTFORMAT_ansiX962_compressed_char2;
        } else {
            *comp_id = TLSEXT_ECPOINTFORMAT_uncompressed;
        }
    }
    return 1;
}

/* Check that an EC key is compatible with extensions. */
static int tls1_check_ec_key(SSL *s, const uint16_t *curve_id,
                             const uint8_t *comp_id)
{
    size_t curves_len, formats_len, i;
    const uint16_t *curves;
    const uint8_t *formats;

    /*
     * Check point formats extension if present, otherwise everything
     * is supported (see RFC4492).
     */
    tls1_get_formatlist(s, 1, &formats, &formats_len);
    if (comp_id != NULL && formats != NULL) {
        for (i = 0; i < formats_len; i++) {
            if (formats[i] == *comp_id)
                break;
        }
        if (i == formats_len)
            return 0;
    }
    if (curve_id == NULL)
        return 1;

    /*
     * Check curve list if present, otherwise everything is supported.
     */
    tls1_get_curvelist(s, 1, &curves, &curves_len);
    if (curve_id != NULL && curves != NULL) {
        for (i = 0; i < curves_len; i++) {
            if (curves[i] == *curve_id)
                break;
        }
        if (i == curves_len)
            return 0;
        /* Clients can only check the sent curve list */
        if (!s->server)
            return 1;
    }

    return (1);
}

/*
 * Check cert parameters compatible with extensions: currently just checks
 * EC certificates have compatible curves and compression.
 */
static int tls1_check_cert_param(SSL *s, X509 *x, int set_ee_md)
{
    uint16_t curve_id;
    uint8_t comp_id;
    EVP_PKEY *pkey;
    int rv;

    pkey = X509_get_pubkey(x);
    if (pkey == NULL)
        return 0;
    /* If not EC nothing to do */
    if (pkey->type != EVP_PKEY_EC) {
        EVP_PKEY_free(pkey);
        return 1;
    }

    rv = tls1_set_ec_id(&curve_id, &comp_id, pkey->pkey.ec);
    EVP_PKEY_free(pkey);
    if (rv != 1)
        return 0;

    /*
     * Can't check curve_id for client certs as we don't have a
     * supported curves extension.
     */
    rv = tls1_check_ec_key(s, s->server ? &curve_id : NULL, &comp_id);
    if (!rv)
        return 0;
    /*
     * Special case for suite B. We *MUST* sign using SHA256+P-256 or
     * SHA384+P-384, adjust digest if necessary.
     */
    if (set_ee_md && tls1_suiteb(s)) {
        int check_md;
        size_t i;
        CERT *c = s->cert;
        /* Check to see we have necessary signing algorithm */
        if (curve_id == TLSEXT_curve_P_256)
            check_md = NID_ecdsa_with_SHA256;
        else if (curve_id == TLSEXT_curve_P_384)
            check_md = NID_ecdsa_with_SHA384;
        else
            return 0; /* Should never happen */
        for (i = 0; i < c->shared_sigalgslen; i++) {
            if (check_md == c->shared_sigalgs[i].signandhash_nid)
                break;
        }
        if (i == c->shared_sigalgslen)
            return 0;
        if (set_ee_md == 2) {
            if (check_md == NID_ecdsa_with_SHA256)
                c->pkeys[SSL_PKEY_ECC].digest = EVP_sha256();
            else
                c->pkeys[SSL_PKEY_ECC].digest = EVP_sha384();
        }
    }
    return rv;
}

/* Check EC temporary key is compatible with client extensions. */
int tls1_check_ec_tmp_key(SSL *s, unsigned long cid)
{
    EC_KEY *ec = s->cert->ecdh_tmp;
    uint16_t curve_id;

    /*
     * If Suite B, AES128 MUST use P-256 and AES256 MUST use P-384,
     * no other curves permitted.
     */
    if (tls1_suiteb(s)) {
        /* Curve to check determined by ciphersuite */
        if (cid == TLS1_CK_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256)
            curve_id = TLSEXT_curve_P_256;
        else if (cid == TLS1_CK_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384)
            curve_id = TLSEXT_curve_P_384;
        else
            return 0;
        /* Check this curve is acceptable */
        if (!tls1_check_ec_key(s, &curve_id, NULL))
            return 0;
        /* If auto or setting curve from callback assume OK */
        if (s->cert->ecdh_tmp_auto || s->cert->ecdh_tmp_cb)
            return 1;
        else { /* Otherwise check curve is acceptable */
            uint16_t curve_tmp;
            if (ec == NULL)
                return 0;
            if (!tls1_set_ec_id(&curve_tmp, NULL, ec))
                return 0;
            if (!curve_tmp || curve_tmp == curve_id)
                return 1;
            return 0;
        }                      
    }

    if (s->cert->ecdh_tmp_auto != 0) {
        /* Need a shared curve. */
        if (tls1_shared_curve(s, 0) != NID_undef)
            return 1;
        return 0;
    }

    if (ec == NULL) {
        if (s->cert->ecdh_tmp_cb != NULL)
            return 1;

        return 0;
    }
    if (tls1_set_ec_id(&curve_id, NULL, ec) != 1)
        return 0;

    return tls1_check_ec_key(s, &curve_id, NULL);
}

/*
 * List of supported signature algorithms and hashes. We should make this
 * customizable at some point, for now include everything we support.
 */

static uint8_t tls12_sigalgs[] = {
    TLSEXT_hash_sha512, TLSEXT_signature_rsa, TLSEXT_hash_sha512,
    TLSEXT_signature_dsa, TLSEXT_hash_sha512, TLSEXT_signature_ecdsa,

    TLSEXT_hash_sha384, TLSEXT_signature_rsa, TLSEXT_hash_sha384,
    TLSEXT_signature_dsa, TLSEXT_hash_sha384, TLSEXT_signature_ecdsa,

    TLSEXT_hash_sha256, TLSEXT_signature_rsa, TLSEXT_hash_sha256,
    TLSEXT_signature_dsa, TLSEXT_hash_sha256, TLSEXT_signature_ecdsa,

    TLSEXT_hash_sha224, TLSEXT_signature_rsa, TLSEXT_hash_sha224,
    TLSEXT_signature_dsa, TLSEXT_hash_sha224, TLSEXT_signature_ecdsa,

    TLSEXT_hash_sha1, TLSEXT_signature_rsa, TLSEXT_hash_sha1,
    TLSEXT_signature_dsa, TLSEXT_hash_sha1, TLSEXT_signature_ecdsa,
};

static uint8_t suiteb_sigalgs[] = {
    TLSEXT_hash_sha256, TLSEXT_signature_dsa,
    TLSEXT_hash_sha384, TLSEXT_signature_dsa,
};

size_t tls12_get_psigalgs(SSL *s, const uint8_t **psigs)
{
    /*
     * If Suite B mode use Suite B sigalgs only, ignore any other
     * preferences.
     */
    switch (tls1_suiteb(s)) {
        case SSL_CERT_FLAG_SUITEB_128_LOS:
            *psigs = suiteb_sigalgs;
            return sizeof(suiteb_sigalgs);

        case SSL_CERT_FLAG_SUITEB_128_LOS_ONLY:
            *psigs = suiteb_sigalgs;
            return 2;

        case SSL_CERT_FLAG_SUITEB_192_LOS:
            *psigs = suiteb_sigalgs + 2;
            return 2;
    }

    /* If server use client authentication sigalgs if not NULL */
    if (s->server && s->cert->client_sigalgs != NULL) {
        *psigs = s->cert->client_sigalgs;
        return s->cert->client_sigalgslen;
    } else if (s->cert->conf_sigalgs != NULL) {
        *psigs = s->cert->conf_sigalgs;
        return s->cert->conf_sigalgslen;
    } else {
        *psigs = tls12_sigalgs;
        return sizeof(tls12_sigalgs);
    }
}

/*
 * Check signature algorithm is consistent with sent supported signature
 * algorithms and if so return relevant digest.
 */
int tls12_check_peer_sigalg(const EVP_MD **pmd, SSL *s, const uint8_t *sig,
                            EVP_PKEY *pkey)
{
    const uint8_t *sent_sigs;
    size_t sent_sigslen, i;
    int sigalg = tls12_get_sigid(pkey);

    /* Should never happen */
    if (sigalg == -1)
        return -1;
    /* Check key type is consistent with signature */
    if (sigalg != (int)sig[1]) {
        SSLerr(SSL_F_TLS12_CHECK_PEER_SIGALG, SSL_R_WRONG_SIGNATURE_TYPE);
        return 0;
    }
    if (pkey->type == EVP_PKEY_EC) {
        uint8_t comp_id;
        uint16_t curve_id;
        /* Check compression and curve matches extensions */
        if (!tls1_set_ec_id(&curve_id, &comp_id, pkey->pkey.ec))
            return 0;
        if (!s->server && !tls1_check_ec_key(s, &curve_id, &comp_id)) {
            SSLerr(SSL_F_TLS12_CHECK_PEER_SIGALG, SSL_R_WRONG_CURVE);
            return 0;
        }
        /* If Suite B only P-384+SHA384 or P-256+SHA-256 allowed */
        if (tls1_suiteb(s)) {
            if (!curve_id)
                return 0;
            if (curve_id == TLSEXT_curve_P_256) {
                if (sig[0] != TLSEXT_hash_sha256) {
                    SSLerr(SSL_F_TLS12_CHECK_PEER_SIGALG,
                           SSL_R_ILLEGAL_SUITEB_DIGEST);
                    return 0;
                }
            } else if (curve_id == TLSEXT_curve_P_384) {
                if (sig[0] != TLSEXT_hash_sha384) {
                    SSLerr(SSL_F_TLS12_CHECK_PEER_SIGALG,
                           SSL_R_ILLEGAL_SUITEB_DIGEST);
                    return 0;
                }
            } else
                return 0;
        }
    } else if (tls1_suiteb(s))
        return 0;

    /* Check signature matches a type we sent */
    sent_sigslen = tls12_get_psigalgs(s, &sent_sigs);
    for (i = 0; i < sent_sigslen; i += 2, sent_sigs += 2) {
        if (sig[0] == sent_sigs[0] && sig[1] == sent_sigs[1])
            break;
    }
    /* Allow fallback to SHA1 if not strict mode */
    if (i == sent_sigslen && (sig[0] != TLSEXT_hash_sha1 ||
        s->cert->cert_flags & SSL_CERT_FLAGS_CHECK_TLS_STRICT))
    {
        SSLerr(SSL_F_TLS12_CHECK_PEER_SIGALG, SSL_R_WRONG_SIGNATURE_TYPE);
        return 0;
    }
    *pmd = tls12_get_hash(sig[0]);
    if (*pmd == NULL) {
        SSLerr(SSL_F_TLS12_CHECK_PEER_SIGALG, SSL_R_UNKNOWN_DIGEST);
        return 0;
    }
    /* Store the digest used so applications can retrieve it if they wish. */
    if (s->session != NULL && s->session->sess_cert != NULL)
        s->session->sess_cert->peer_key->digest = *pmd;

    return 1;
}

/*
 * Get a mask of disabled algorithms: an algorithm is disabled
 * if it isn't supported or doesn't appear in supported signature
 * algorithms. Unlike ssl_cipher_get_disabled this applies to a specific
 * session and not global settings.
 */
void ssl_set_client_disabled(SSL *s)
{
    CERT *c = s->cert;
    const uint8_t *sigalgs;
    size_t i, sigalgslen;
    int have_rsa = 0, have_dsa = 0, have_ecdsa = 0;
    c->mask_a = 0;
    c->mask_k = 0;
    /* Don't allow TLS 1.2 only ciphers if we don't suppport them */
    if (!SSL_CLIENT_USE_TLS1_2_CIPHERS(s))
        c->mask_ssl = SSL_TLSV1_2;
    else
        c->mask_ssl = 0;
    /*
     * Now go through all signature algorithms seeing if we support
     * any for RSA, DSA, ECDSA. Do this for all versions not just
     * TLS 1.2.
     */
    sigalgslen = tls12_get_psigalgs(s, &sigalgs);
    for (i = 0; i < sigalgslen; i += 2, sigalgs += 2) {
        switch (sigalgs[1]) {
            case TLSEXT_signature_rsa:
                have_rsa = 1;
                break;
            case TLSEXT_signature_dsa:
                have_dsa = 1;
                break;
            case TLSEXT_signature_ecdsa:
                have_ecdsa = 1;
                break;
        }
    }
    /*
     * Disable auth and static DH if we don't include any appropriate
     * signature algorithms.
     */
    if (!have_rsa) {
        c->mask_a |= SSL_aRSA;
    }
    if (!have_dsa) {
        c->mask_a |= SSL_aDSS;
    }
    if (!have_ecdsa) {
        c->mask_a |= SSL_aECDSA;
    }
    c->valid = 1;
}

/* byte_compare is a compare function for qsort(3) that compares bytes. */
static int byte_compare(const void *in_a, const void *in_b)
{
    uint8_t a = *((const uint8_t *)in_a);
    uint8_t b = *((const uint8_t *)in_b);

    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    return 0;
}

uint8_t *ssl_add_clienthello_tlsext(SSL *s, uint8_t *p, uint8_t *limit)
{
    int extdatalen = 0;
    int using_ecc = 0;
    uint8_t *ret = p;

    /* See if we support any ECC ciphersuites. */
    if (s->version != DTLS1_VERSION && s->version >= TLS1_VERSION) {
        STACK_OF(SSL_CIPHER) *cipher_stack = SSL_get_ciphers(s);
        unsigned long alg_k, alg_a;
        int i;

        for (i = 0; i < sk_SSL_CIPHER_num(cipher_stack); i++) {
            SSL_CIPHER *c = sk_SSL_CIPHER_value(cipher_stack, i);

            alg_k = c->algorithm_mkey;
            alg_a = c->algorithm_auth;

            if ((alg_k & SSL_kECDHE ||
                (alg_a & SSL_aECDSA))) {
                using_ecc = 1;
                break;
            }
        }
    }

    ret += 2;

    if (ret >= limit)
        return NULL; /* this really never occurs, but ... */

    if (s->tlsext_hostname != NULL) {
        /* Add TLS extension servername to the Client Hello message */
        size_t size_str, lenmax;

        /* check for enough space.
           4 for the servername type and extension length
           2 for servernamelist length
           1 for the hostname type
           2 for hostname length
           + hostname length
        */

        if ((limit - ret) < 9)
            return NULL;

        lenmax = limit - ret - 9;
        if ((size_str = strlen(s->tlsext_hostname)) > lenmax)
            return NULL;

        /* extension type and length */
        s2n(TLSEXT_TYPE_server_name, ret);

        s2n(size_str + 5, ret);

        /* length of servername list */
        s2n(size_str + 3, ret);

        /* hostname type, length and hostname */
        *(ret++) = (uint8_t)TLSEXT_NAMETYPE_host_name;
        s2n(size_str, ret);
        memcpy(ret, s->tlsext_hostname, size_str);
        ret += size_str;
    }

    /* Add RI if renegotiating */
    if (s->renegotiate) {
        int el;

        if (!ssl_add_clienthello_renegotiate_ext(s, 0, &el, 0)) {
            SSLerr(SSL_F_SSL_ADD_CLIENTHELLO_TLSEXT, ERR_R_INTERNAL_ERROR);
            return NULL;
        }

        if ((limit - ret) < 4 + el)
            return NULL;

        s2n(TLSEXT_TYPE_renegotiate, ret);
        s2n(el, ret);

        if (!ssl_add_clienthello_renegotiate_ext(s, ret, &el, el)) {
            SSLerr(SSL_F_SSL_ADD_CLIENTHELLO_TLSEXT, ERR_R_INTERNAL_ERROR);
            return NULL;
        }

        ret += el;
    }

    if (using_ecc) {
        /*
         * Add TLS extension ECPointFormats to the ClientHello message
         */
        size_t curves_len, formats_len, lenmax;
        const uint8_t *formats;
        const uint16_t *curves;
        size_t i;

        tls1_get_formatlist(s, 0, &formats, &formats_len);

        if ((limit - ret) < 5)
            return NULL;

        lenmax = limit - ret - 5;
        if (formats_len > lenmax)
            return NULL;
        if (formats_len > 255) {
            SSLerr(SSL_F_SSL_ADD_CLIENTHELLO_TLSEXT, ERR_R_INTERNAL_ERROR);
            return NULL;
        }

        s2n(TLSEXT_TYPE_ec_point_formats, ret);
        s2n(formats_len + 1, ret);
        *(ret++) = (uint8_t)formats_len;
        memcpy(ret, formats, formats_len);
        ret += formats_len;

        /*
         * Add TLS extension EllipticCurves to the ClientHello message.
         */
        tls1_get_curvelist(s, 0, &curves, &curves_len);

        if ((limit - ret) < 6)
            return NULL;

        lenmax = limit - ret - 6;
        if (curves_len > lenmax)
            return NULL;
        if (curves_len > 65532) {
            SSLerr(SSL_F_SSL_ADD_CLIENTHELLO_TLSEXT, ERR_R_INTERNAL_ERROR);
            return NULL;
        }

        s2n(TLSEXT_TYPE_elliptic_curves, ret);
        s2n((curves_len * 2) + 2, ret);

        s2n(curves_len * 2, ret);
        for (i = 0; i < curves_len; i++)
            s2n(curves[i], ret);
    }

    if (!(SSL_get_options(s) & SSL_OP_NO_TICKET)) {
        int ticklen;
        if (!s->new_session && s->session && s->session->tlsext_tick)
            ticklen = s->session->tlsext_ticklen;
        else if (s->session && s->tlsext_session_ticket && s->tlsext_session_ticket->data) {
            ticklen = s->tlsext_session_ticket->length;
            s->session->tlsext_tick = malloc(ticklen);
            if (!s->session->tlsext_tick)
                return NULL;
            memcpy(s->session->tlsext_tick, s->tlsext_session_ticket->data, ticklen);
            s->session->tlsext_ticklen = ticklen;
        } else
            ticklen = 0;
        if (ticklen == 0 && s->tlsext_session_ticket && s->tlsext_session_ticket->data == NULL)
            goto skip_ext;
        /* Check for enough room 2 for extension type, 2 for len
         * rest for ticket
         */
        if ((limit - ret) < 4 + ticklen)
            return NULL;
        s2n(TLSEXT_TYPE_session_ticket, ret);

        s2n(ticklen, ret);
        if (ticklen) {
            memcpy(ret, s->session->tlsext_tick, ticklen);
            ret += ticklen;
        }
    }
skip_ext:

    if (TLS1_get_client_version(s) >= TLS1_2_VERSION) {
        size_t salglen;
        const uint8_t *salg;
        salglen = tls12_get_psigalgs(s, &salg);
        if ((size_t)(limit - ret) < salglen + 6)
            return NULL;

        s2n(TLSEXT_TYPE_signature_algorithms, ret);
        s2n(salglen + 2, ret);
        s2n(salglen, ret);
        memcpy(ret, salg, salglen);
        ret += salglen;
    }

    if (s->tlsext_status_type == TLSEXT_STATUSTYPE_ocsp && s->version != DTLS1_VERSION) {
        int i;
        long extlen, idlen, itmp;
        OCSP_RESPID *id;

        idlen = 0;
        for (i = 0; i < sk_OCSP_RESPID_num(s->tlsext_ocsp_ids); i++) {
            id = sk_OCSP_RESPID_value(s->tlsext_ocsp_ids, i);
            itmp = i2d_OCSP_RESPID(id, NULL);
            if (itmp <= 0)
                return NULL;
            idlen += itmp + 2;
        }

        if (s->tlsext_ocsp_exts) {
            extlen = i2d_X509_EXTENSIONS(s->tlsext_ocsp_exts, NULL);
            if (extlen < 0)
                return NULL;
        } else
            extlen = 0;

        if ((limit - ret) < 7 + extlen + idlen)
            return NULL;
        s2n(TLSEXT_TYPE_status_request, ret);
        if (extlen + idlen > 0xFFF0)
            return NULL;
        s2n(extlen + idlen + 5, ret);
        *(ret++) = TLSEXT_STATUSTYPE_ocsp;
        s2n(idlen, ret);
        for (i = 0; i < sk_OCSP_RESPID_num(s->tlsext_ocsp_ids); i++) {
            /* save position of id len */
            uint8_t *q = ret;
            id = sk_OCSP_RESPID_value(s->tlsext_ocsp_ids, i);
            /* skip over id len */
            ret += 2;
            itmp = i2d_OCSP_RESPID(id, &ret);
            /* write id len */
            s2n(itmp, q);
        }
        s2n(extlen, ret);
        if (extlen > 0)
            i2d_X509_EXTENSIONS(s->tlsext_ocsp_exts, &ret);
    }

    if (s->ctx->next_proto_select_cb && !s->s3->tmp.finish_md_len) {
        /* The client advertises an emtpy extension to indicate its
         * support for Next Protocol Negotiation */
        if ((limit - ret) < 4)
            return NULL;
        s2n(TLSEXT_TYPE_next_proto_neg, ret);
        s2n(0, ret);
    }

    if (s->alpn_client_proto_list != NULL && s->s3->tmp.finish_md_len == 0) {
        if ((limit - ret) < 6 + s->alpn_client_proto_list_len)
            return (NULL);
        s2n(TLSEXT_TYPE_application_layer_protocol_negotiation, ret);
        s2n(2 + s->alpn_client_proto_list_len, ret);
        s2n(s->alpn_client_proto_list_len, ret);
        memcpy(ret, s->alpn_client_proto_list, s->alpn_client_proto_list_len);
        ret += s->alpn_client_proto_list_len;
    }

#ifndef OPENSSL_NO_SRTP
    if (SSL_get_srtp_profiles(s)) {
        int el;

        ssl_add_clienthello_use_srtp_ext(s, 0, &el, 0);

        if ((limit - ret) < 4 + el)
            return NULL;

        s2n(TLSEXT_TYPE_use_srtp, ret);
        s2n(el, ret);

        if (ssl_add_clienthello_use_srtp_ext(s, ret, &el, el)) {
            SSLerr(SSL_F_SSL_ADD_CLIENTHELLO_TLSEXT, ERR_R_INTERNAL_ERROR);
            return NULL;
        }
        ret += el;
    }
#endif

    /*
     * Add padding to workaround bugs in F5 terminators.
     * See https://tools.ietf.org/html/draft-ietf-tls-padding-01
     *
     * Note that this seems to trigger issues with IronPort SMTP
     * appliances.
     *
     * NB: because this code works out the length of all existing
     * extensions it MUST always appear last.
     */
    if (s->options & SSL_OP_TLSEXT_PADDING) {
        int hlen = ret - (uint8_t *)s->init_buf->data;

        /*
         * The code in s23_clnt.c to build ClientHello messages includes the
         * 5-byte record header in the buffer, while the code in s3_clnt.c does
         * not.
         */
        if (s->state == SSL23_ST_CW_CLNT_HELLO_A)
            hlen -= 5;
        if (hlen > 0xff && hlen < 0x200) {
            hlen = 0x200 - hlen;
            if (hlen >= 4)
                hlen -= 4;
            else
                hlen = 0;

            s2n(TLSEXT_TYPE_padding, ret);
            s2n(hlen, ret);
            memset(ret, 0, hlen);
            ret += hlen;
        }
    }

    /*
     * Add TLS extension Server_Authz_DataFormats to the ClientHello
     *
     * 2 bytes for extension type
     * 2 bytes for extension length
     * 1 byte for the list length
     * 1 byte for the list (we only support audit proofs)
     */
    if (s->ctx->tlsext_authz_server_audit_proof_cb != NULL) {
        const uint16_t ext_len = 2;
        const uint8_t list_len = 1;

        /* UNSAFE EXTENSION TO TO BE REMOVED IN A FUTURE COMMIT */

        s2n(TLSEXT_TYPE_server_authz, ret);
        /* Extension length: 2 bytes */
        s2n(ext_len, ret);
        *(ret++) = list_len;
        *(ret++) = TLSEXT_AUTHZDATAFORMAT_audit_proof;
    }

    /* Add custom TLS Extensions to ClientHello */
    if (s->ctx->custom_cli_ext_records_count) {
        size_t i;
        custom_cli_ext_record *record;

        for (i = 0; i < s->ctx->custom_cli_ext_records_count; i++) {
            const uint8_t *out = NULL;
            uint16_t outlen = 0;

            record = &s->ctx->custom_cli_ext_records[i];
            /* NULL callback sends empty extension */ 
            /* -1 from callback omits extension */
            if (record->fn1) {
                int cb_retval = 0;
                cb_retval = record->fn1(s, record->ext_type, &out, &outlen,
                                        record->arg);
                if (cb_retval == 0)
                    return NULL; /* error */
                if (cb_retval == -1)
                    continue; /* skip this extension */
            }
            if (limit < ret + 4 + outlen)
                return NULL;
            s2n(record->ext_type, ret);
            s2n(outlen, ret);
            memcpy(ret, out, outlen);
            ret += outlen;
        }
    }

    if ((extdatalen = ret - p - 2) == 0)
        return p;

    s2n(extdatalen, p);
    return ret;
}

uint8_t *ssl_add_serverhello_tlsext(SSL *s, uint8_t *p,
                                          uint8_t *limit)
{
    int using_ecc, extdatalen = 0;
    unsigned long alg_a, alg_k;
    uint8_t *ret = p;
    int next_proto_neg_seen;

    alg_a = s->s3->tmp.new_cipher->algorithm_auth;
    alg_k = s->s3->tmp.new_cipher->algorithm_mkey;
    using_ecc = (alg_k & SSL_kECDHE ||
        alg_a & SSL_aECDSA) &&
        s->session->tlsext_ecpointformatlist != NULL;

    ret += 2;
    if (ret >= limit)
        return NULL; /* this really never occurs, but ... */

    if (!s->hit && s->servername_done == 1 && s->session->tlsext_hostname != NULL) {
        if ((limit - ret) < 4)
            return NULL;

        s2n(TLSEXT_TYPE_server_name, ret);
        s2n(0, ret);
    }

    if (s->s3->send_connection_binding) {
        int el;

        if (!ssl_add_serverhello_renegotiate_ext(s, 0, &el, 0)) {
            SSLerr(SSL_F_SSL_ADD_SERVERHELLO_TLSEXT, ERR_R_INTERNAL_ERROR);
            return NULL;
        }

        if ((limit - ret) < 4 + el)
            return NULL;

        s2n(TLSEXT_TYPE_renegotiate, ret);
        s2n(el, ret);

        if (!ssl_add_serverhello_renegotiate_ext(s, ret, &el, el)) {
            SSLerr(SSL_F_SSL_ADD_SERVERHELLO_TLSEXT, ERR_R_INTERNAL_ERROR);
            return NULL;
        }

        ret += el;
    }

    if (using_ecc && s->version != DTLS1_VERSION) {
        const uint8_t *formats;
        size_t formats_len, lenmax;

        /*
         * Add TLS extension ECPointFormats to the ServerHello message.
         */
        tls1_get_formatlist(s, 0, &formats, &formats_len);

        if ((limit - ret) < 5)
            return NULL;

        lenmax = limit - ret - 5;
        if (formats_len > lenmax)
            return NULL;
        if (formats_len > 255) {
            SSLerr(SSL_F_SSL_ADD_SERVERHELLO_TLSEXT, ERR_R_INTERNAL_ERROR);
            return NULL;
        }

        s2n(TLSEXT_TYPE_ec_point_formats, ret);
        s2n(formats_len + 1, ret);
        *(ret++) = (uint8_t)formats_len;
        memcpy(ret, formats, formats_len);
        ret += formats_len;
    }
    /* Currently the server should not respond with a SupportedCurves extension */

    if (s->tlsext_ticket_expected && !(SSL_get_options(s) & SSL_OP_NO_TICKET)) {
        if ((limit - ret) < 4)
            return NULL;

        s2n(TLSEXT_TYPE_session_ticket, ret);
        s2n(0, ret);
    }

    if (s->tlsext_status_expected) {
        if ((limit - ret) < 4)
            return NULL;

        s2n(TLSEXT_TYPE_status_request, ret);
        s2n(0, ret);
    }

#ifndef OPENSSL_NO_SRTP
    if (s->srtp_profile) {
        int el;

        ssl_add_serverhello_use_srtp_ext(s, 0, &el, 0);

        if ((limit - ret) < 4 + el)
            return NULL;

        s2n(TLSEXT_TYPE_use_srtp, ret);
        s2n(el, ret);

        if (ssl_add_serverhello_use_srtp_ext(s, ret, &el, el)) {
            SSLerr(SSL_F_SSL_ADD_SERVERHELLO_TLSEXT, ERR_R_INTERNAL_ERROR);
            return NULL;
        }
        ret += el;
    }
#endif

    if (((s->s3->tmp.new_cipher->id & 0xFFFF) == 0x80 
        || (s->s3->tmp.new_cipher->id & 0xFFFF) == 0x81) 
        && (SSL_get_options(s) & SSL_OP_CRYPTOPRO_TLSEXT_BUG)) {
        static const uint8_t cryptopro_ext[36] = {
            0xfd, 0xe8, /* 65000 */
            0x00, 0x20, /* 32 bytes length */
            0x30, 0x1e, 0x30, 0x08, 0x06, 0x06, 0x2a, 0x85, 0x03, 0x02, 0x02,
            0x09, 0x30, 0x08, 0x06, 0x06, 0x2a, 0x85, 0x03, 0x02, 0x02, 0x16,
            0x30, 0x08, 0x06, 0x06, 0x2a, 0x85, 0x03, 0x02, 0x02, 0x17
        };
        if ((size_t)(limit - ret) < sizeof(cryptopro_ext))
            return NULL;
        memcpy(ret, cryptopro_ext, sizeof(cryptopro_ext));
        ret += sizeof(cryptopro_ext);
    }

    next_proto_neg_seen = s->s3->next_proto_neg_seen;
    s->s3->next_proto_neg_seen = 0;
    if (next_proto_neg_seen && s->ctx->next_protos_advertised_cb) {
        const uint8_t *npa;
        unsigned int npalen;
        int r;

        r = s->ctx->next_protos_advertised_cb(
            s, &npa, &npalen, s->ctx->next_protos_advertised_cb_arg);
        if (r == SSL_TLSEXT_ERR_OK) {
            if ((limit - ret) < 4 + npalen)
                return NULL;
            s2n(TLSEXT_TYPE_next_proto_neg, ret);
            s2n(npalen, ret);
            memcpy(ret, npa, npalen);
            ret += npalen;
            s->s3->next_proto_neg_seen = 1;
        }
    }

    if (s->s3->alpn_selected != NULL) {
        const uint8_t *selected = s->s3->alpn_selected;
        unsigned int len = s->s3->alpn_selected_len;

        if ((long)(limit - ret - 4 - 2 - 1 - len) < 0)
            return (NULL);
        s2n(TLSEXT_TYPE_application_layer_protocol_negotiation, ret);
        s2n(3 + len, ret);
        s2n(1 + len, ret);
        *ret++ = len;
        memcpy(ret, selected, len);
        ret += len;
    }

    /*
     * If the client supports authz then see whether we have any to offer to
     * it.
     */
    if (s->s3->tlsext_authz_client_types_len) {
        size_t authz_length;
        /*
         * By now we already know the new cipher, so we can look ahead
         * to see whether the cert we are going to send
         * has any authz data attached to it.
         */
        const uint8_t *authz = ssl_get_authz_data(s, &authz_length);
        const uint8_t *const orig_authz = authz;
        size_t i;
        unsigned int authz_count = 0;

        /*
         * The authz data contains a number of the following structures:
         *      uint8_t authz_type
         *      uint16_t length
         *      uint8_t data[length]
         *
         * First we walk over it to find the number of authz elements.
         */
        for (i = 0; i < authz_length; i++) {
            uint16_t length;
            uint8_t type;

            type = *(authz++);
            if (memchr(s->s3->tlsext_authz_client_types, type,
                       s->s3->tlsext_authz_client_types_len) != NULL)
                authz_count++;

            n2s(authz, length);
            authz += length;
            i += length;
        }

        if (authz_count) {
            /*
             * Add TLS extension server_authz to the ServerHello message
             * 2 bytes for extension type
             * 2 bytes for extension length
             * 1 byte for the list length
             * n bytes for the list
             */
            const uint16_t ext_len = 1 + authz_count;

            if ((long)(limit - ret - 4 - ext_len) < 0)
                return NULL;
            s2n(TLSEXT_TYPE_server_authz, ret);
            s2n(ext_len, ret);
            *(ret++) = authz_count;
            s->s3->tlsext_authz_promised_to_client = 1;
        }

        authz = orig_authz;
        for (i = 0; i < authz_length; i++) {
            uint16_t length;
            uint8_t type;

            authz_count++;
            type = *(authz++);
            if (memchr(s->s3->tlsext_authz_client_types, type,
                       s->s3->tlsext_authz_client_types_len) != NULL)
                *(ret++) = type;
            n2s(authz, length);
            authz += length;
            i += length;
        }
    }

    /* If custom types were sent in ClientHello, add ServerHello responses */
    if (s->s3->tlsext_custom_types_count) {
        size_t i;

        for (i = 0; i < s->s3->tlsext_custom_types_count; i++) {
            size_t j;
            custom_srv_ext_record *record;

            for (j = 0; j < s->ctx->custom_srv_ext_records_count; j++) {
                record = &s->ctx->custom_srv_ext_records[j];
                if (s->s3->tlsext_custom_types[i] == record->ext_type) {
                    const uint8_t *out = NULL;
                    uint16_t outlen = 0;
                    int cb_retval = 0;

                    /* NULL callback or -1 omits extension */
                    if (!record->fn2)
                        break;
                    cb_retval = record->fn2(s, record->ext_type, &out, &outlen,
                                            record->arg);
                    if (cb_retval == 0)
                        return NULL; /* error */
                    if (cb_retval == -1)
                        break; /* skip this extension */
                    if (limit < ret + 4 + outlen)
                        return NULL;
                    s2n(record->ext_type, ret);
                    s2n(outlen, ret);
                    memcpy(ret, out, outlen);
                    ret += outlen;
                    break;
                }
            }
        }
    }

    if ((extdatalen = ret - p - 2) == 0)
        return p;

    s2n(extdatalen, p);
    return ret;
}

/*
 * tls1_alpn_handle_client_hello is called to process the ALPN extension in a
 * ClientHello.
 *   data: the contents of the extension, not including the type and length.
 *   data_len: the number of bytes in data.
 *   al: a pointer to the alert value to send in the event of a non-zero
 *       return.
 *   returns: 1 on success.
 */
static int tls1_alpn_handle_client_hello(SSL *s, const uint8_t *data,
                                         unsigned int data_len, int *al)
{
    CBS cbs, proto_name_list, alpn;
    const uint8_t *selected;
    uint8_t selected_len;
    int r;

    if (s->ctx->alpn_select_cb == NULL)
        return (1);

    if (data_len < 2)
        goto parse_error;

    CBS_init(&cbs, data, data_len);

    /*
     * data should contain a uint16 length followed by a series of 8-bit,
     * length-prefixed strings.
     */
    if (!CBS_get_u16_length_prefixed(&cbs, &alpn) ||
        CBS_len(&alpn) < 2 ||
        CBS_len(&cbs) != 0)
        goto parse_error;

    /* Validate data before sending to callback. */
    CBS_dup(&alpn, &proto_name_list);
    while (CBS_len(&proto_name_list) > 0) {
        CBS proto_name;

        if (!CBS_get_u8_length_prefixed(&proto_name_list, &proto_name) ||
            CBS_len(&proto_name) == 0)
            goto parse_error;
    }

    r = s->ctx->alpn_select_cb(s, &selected, &selected_len,
                               CBS_data(&alpn), CBS_len(&alpn),
                               s->ctx->alpn_select_cb_arg);
    if (r == SSL_TLSEXT_ERR_OK) {
        free(s->s3->alpn_selected);
        if ((s->s3->alpn_selected = malloc(selected_len)) == NULL) {
            *al = SSL_AD_INTERNAL_ERROR;
            return (-1);
        }
        memcpy(s->s3->alpn_selected, selected, selected_len);
        s->s3->alpn_selected_len = selected_len;
    }

    return (1);

parse_error:
    *al = SSL_AD_DECODE_ERROR;
    return (0);
}

static int ssl_scan_clienthello_tlsext(SSL *s, uint8_t **p, uint8_t *limit,
                                       int *al)
{
    unsigned short type;
    unsigned short size;
    unsigned short len;
    uint8_t *data = *p;
    int renegotiate_seen = 0;

    s->servername_done = 0;
    s->tlsext_status_type = -1;
    s->s3->next_proto_neg_seen = 0;
    s->tlsext_ticket_expected = 0;

    free(s->s3->alpn_selected);
    s->s3->alpn_selected = NULL;

    if (data == limit)
        goto ri_check;

    if (data > (limit - 2))
        goto err;

    n2s(data, len);

    if (data + len != limit)
        goto err;

    while (data <= (limit - 4)) {
        n2s(data, type);
        n2s(data, size);

        if (data + size > (limit))
            goto err;
        if (s->tlsext_debug_cb)
            s->tlsext_debug_cb(s, 0, type, data, size, s->tlsext_debug_arg);
        /* The servername extension is treated as follows:
           - Only the hostname type is supported with a maximum length of 255.
           - The servername is rejected if too long or if it contains zeros,
             in which case an fatal alert is generated.
           - The servername field is maintained together with the session cache.
           - When a session is resumed, the servername call back invoked in order
             to allow the application to position itself to the right context.
           - The servername is acknowledged if it is new for a session or when
             it is identical to a previously used for the same session.
             Applications can control the behaviour.  They can at any time
             set a 'desirable' servername for a new SSL object. This can be the
             case for example with HTTPS when a Host: header field is received and
             a renegotiation is requested. In this case, a possible servername
             presented in the new client hello is only acknowledged if it matches
             the value of the Host: field.
           - Applications must  use SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION
             if they provide for changing an explicit servername context for the
             session, i.e. when the session has been established with a servername extension.
           - On session reconnect, the servername extension may be absent.
        */

        if (type == TLSEXT_TYPE_server_name) {
            uint8_t *sdata;
            int servname_type;
            int dsize;

            if (size < 2)
                goto err;
            n2s(data, dsize);
            size -= 2;
            if (dsize > size)
                goto err;

            sdata = data;
            while (dsize > 3) {
                servname_type = *(sdata++);

                n2s(sdata, len);
                dsize -= 3;

                if (len > dsize)
                    goto err;

                if (s->servername_done == 0)
                    switch (servname_type) {
                        case TLSEXT_NAMETYPE_host_name:
                            if (!s->hit) {
                                if (s->session->tlsext_hostname)
                                    goto err;

                                if (len > TLSEXT_MAXLEN_host_name) {
                                    *al = TLS1_AD_UNRECOGNIZED_NAME;
                                    return 0;
                                }
                                if ((s->session->tlsext_hostname =
                                         malloc(len + 1)) == NULL)
                                {
                                    *al = TLS1_AD_INTERNAL_ERROR;
                                    return 0;
                                }
                                memcpy(s->session->tlsext_hostname, sdata, len);
                                s->session->tlsext_hostname[len] = '\0';
                                if (strlen(s->session->tlsext_hostname) !=
                                    len)
                                {
                                    free(s->session->tlsext_hostname);
                                    s->session->tlsext_hostname = NULL;
                                    *al = TLS1_AD_UNRECOGNIZED_NAME;
                                    return 0;
                                }
                                s->servername_done = 1;

                            } else {
                                s->servername_done =
                                    s->session->tlsext_hostname &&
                                    strlen(s->session->tlsext_hostname) ==
                                        len &&
                                    strncmp(s->session->tlsext_hostname,
                                            (char *)sdata, len) == 0;
                            }
                            break;

                        default:
                            break;
                    }

                dsize -= len;
            }
            if (dsize != 0)
                goto err;

        }

        else if (type == TLSEXT_TYPE_ec_point_formats &&
                 s->version != DTLS1_VERSION) {
            uint8_t *sdata = data;
            size_t formats_len;
            uint8_t *formats;

            if (size < 1) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }
            formats_len = *(sdata++);
            if (formats_len != (size_t)(size - 1)) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }
            if (!s->hit) {
                free(s->session->tlsext_ecpointformatlist);
                s->session->tlsext_ecpointformatlist = NULL;
                s->session->tlsext_ecpointformatlist_length = 0;
                formats = reallocarray(NULL, formats_len, sizeof(uint8_t));
                if (formats == NULL) {
                    *al = TLS1_AD_INTERNAL_ERROR;
                    return 0;
                }
                memcpy(formats, sdata, formats_len);
                s->session->tlsext_ecpointformatlist = formats;
                s->session->tlsext_ecpointformatlist_length = formats_len;
            }
        } else if (type == TLSEXT_TYPE_elliptic_curves &&
                   s->version != DTLS1_VERSION) {
            uint8_t *sdata = data;
            size_t curves_len, i;
            uint16_t *curves;

            if (size < 2) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }
            n2s(sdata, curves_len);
            if (curves_len != (size_t)(size - 2) || curves_len % 2 != 0) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }
            curves_len /= 2;

            if (!s->hit) {
                if (s->session->tlsext_ellipticcurvelist) {
                    *al = TLS1_AD_DECODE_ERROR;
                    return 0;
                }
                s->session->tlsext_ellipticcurvelist_length = 0;
                curves = reallocarray(NULL, curves_len, sizeof(uint16_t));
                if (curves == NULL) {
                    *al = TLS1_AD_INTERNAL_ERROR;
                    return 0;
                }
                for (i = 0; i < curves_len; i++)
                    n2s(sdata, curves[i]);
                s->session->tlsext_ellipticcurvelist = curves;
                s->session->tlsext_ellipticcurvelist_length = curves_len;
            }
        } else if (type == TLSEXT_TYPE_session_ticket) {
            if (s->tls_session_ticket_ext_cb &&
                !s->tls_session_ticket_ext_cb(
                    s, data, size, s->tls_session_ticket_ext_cb_arg)) {
                *al = TLS1_AD_INTERNAL_ERROR;
                return 0;
            }
        } else if (type == TLSEXT_TYPE_renegotiate) {
            if (!ssl_parse_clienthello_renegotiate_ext(s, data, size, al))
                return 0;
            renegotiate_seen = 1;
        } else if (type == TLSEXT_TYPE_signature_algorithms) {
            int dsize;
            if (s->cert->peer_sigalgs || size < 2)
                goto err;
            n2s(data, dsize);
            size -= 2;
            if (dsize != size || dsize & 1 || !dsize)
                goto err;
            if (!tls1_process_sigalgs(s, data, dsize))
                goto err;
            /* If sigalgs received and no shared algorithms fatal error. */
            if (s->cert->peer_sigalgs && !s->cert->shared_sigalgs) {
                SSLerr(SSL_F_SSL_SCAN_CLIENTHELLO_TLSEXT,
                       SSL_R_NO_SHARED_SIGATURE_ALGORITHMS);
                *al = SSL_AD_ILLEGAL_PARAMETER;
                return 0;
            }
        } else if (type == TLSEXT_TYPE_status_request &&
                   s->version != DTLS1_VERSION) {

            if (size < 5)
                goto err;

            s->tlsext_status_type = *data++;
            size--;
            if (s->tlsext_status_type == TLSEXT_STATUSTYPE_ocsp) {
                const uint8_t *sdata;
                int dsize;
                /* Read in responder_id_list */
                n2s(data, dsize);
                size -= 2;
                if (dsize > size)
                    goto err;
                while (dsize > 0) {
                    OCSP_RESPID *id;
                    int idsize;
                    if (dsize < 4)
                        goto err;
                    n2s(data, idsize);
                    dsize -= 2 + idsize;
                    size -= 2 + idsize;
                    if (dsize < 0)
                        goto err;
                    sdata = data;
                    data += idsize;
                    id = d2i_OCSP_RESPID(NULL, &sdata, idsize);
                    if (!id)
                        goto err;
                    if (data != sdata) {
                        OCSP_RESPID_free(id);
                        goto err;
                    }
                    if (!s->tlsext_ocsp_ids &&
                        !(s->tlsext_ocsp_ids = sk_OCSP_RESPID_new_null())) {
                        OCSP_RESPID_free(id);
                        *al = SSL_AD_INTERNAL_ERROR;
                        return 0;
                    }
                    if (!sk_OCSP_RESPID_push(s->tlsext_ocsp_ids, id)) {
                        OCSP_RESPID_free(id);
                        *al = SSL_AD_INTERNAL_ERROR;
                        return 0;
                    }
                }

                /* Read in request_extensions */
                if (size < 2)
                    goto err;
                n2s(data, dsize);
                size -= 2;
                if (dsize != size)
                    goto err;
                sdata = data;
                if (dsize > 0) {
                    if (s->tlsext_ocsp_exts) {
                        sk_X509_EXTENSION_pop_free(s->tlsext_ocsp_exts,
                                                   X509_EXTENSION_free);
                    }

                    s->tlsext_ocsp_exts =
                        d2i_X509_EXTENSIONS(NULL, &sdata, dsize);
                    if (!s->tlsext_ocsp_exts || (data + dsize != sdata))
                        goto err;
                }
            } else {
                /* We don't know what to do with any other type
                 * so ignore it.
                 */
                s->tlsext_status_type = -1;
            }
        } else if (type == TLSEXT_TYPE_next_proto_neg &&
                   s->s3->tmp.finish_md_len == 0 &&
                   s->s3->alpn_selected == NULL) {
            /* We shouldn't accept this extension on a
             * renegotiation.
             *
             * s->new_session will be set on renegotiation, but we
             * probably shouldn't rely that it couldn't be set on
             * the initial renegotiation too in certain cases (when
             * there's some other reason to disallow resuming an
             * earlier session -- the current code won't be doing
             * anything like that, but this might change).

             * A valid sign that there's been a previous handshake
             * in this connection is if s->s3->tmp.finish_md_len >
             * 0.  (We are talking about a check that will happen
             * in the Hello protocol round, well before a new
             * Finished message could have been computed.) */
            s->s3->next_proto_neg_seen = 1;
        } else if (type == TLSEXT_TYPE_application_layer_protocol_negotiation &&
                   s->ctx->alpn_select_cb != NULL &&
                   s->s3->tmp.finish_md_len == 0) {
            if (tls1_alpn_handle_client_hello(s, data, size, al) != 1)
                return (0);
            /* ALPN takes precedence over NPN. */
            s->s3->next_proto_neg_seen = 0;
        }

/* session ticket processed earlier */
#ifndef OPENSSL_NO_SRTP
        else if (type == TLSEXT_TYPE_use_srtp) {
            if (ssl_parse_clienthello_use_srtp_ext(s, data, size, al))
                return 0;
        }
#endif

        else if (type == TLSEXT_TYPE_server_authz) {
            uint8_t *sdata = data;
            uint8_t server_authz_dataformatlist_length;

            if (size == 0) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }

            server_authz_dataformatlist_length = *(sdata++);

            if (server_authz_dataformatlist_length != size - 1) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }

            /*
             * Successful session resumption uses the same authz
             * information as the original session so we ignore this
             * in the case of a session resumption.
             */
            if (!s->hit) {
                size_t i;
                free(s->s3->tlsext_authz_client_types);
                s->s3->tlsext_authz_client_types =
                    malloc(server_authz_dataformatlist_length);
                if (s->s3->tlsext_authz_client_types == NULL) {
                    *al = TLS1_AD_INTERNAL_ERROR;
                    return 0;
                }

                s->s3->tlsext_authz_client_types_len =
                    server_authz_dataformatlist_length;
                memcpy(s->s3->tlsext_authz_client_types, sdata,
                       server_authz_dataformatlist_length);

                /* Sort the types in order to check for duplicates. */
                qsort(s->s3->tlsext_authz_client_types,
                      server_authz_dataformatlist_length, 1 /* element size */,
                      byte_compare);

                for (i = 0; i < server_authz_dataformatlist_length; i++) {
                    if (i > 0 && s->s3->tlsext_authz_client_types[i] ==
                        s->s3->tlsext_authz_client_types[i - 1])
                    {
                        *al = TLS1_AD_DECODE_ERROR;
                        return 0;
                    }
                }
            }
        }
        /*
         * If this ClientHello extension was unhandled and this is
         * a nonresumed connection, check whether the extension is a
         * custom TLS Extension (has a custom_srv_ext_record), and if
         * so call the callback and record the extension number so that
         * an appropriate ServerHello may be later returned.
         */
        else if (!s->hit && s->ctx->custom_srv_ext_records_count) {
            size_t i;
            custom_srv_ext_record *record;

            for (i = 0; i < s->ctx->custom_srv_ext_records_count; i++) {
                record = &s->ctx->custom_srv_ext_records[i];
                if (type == record->ext_type) {
                    /* Error on duplicate TLS Extensions */
                    size_t j;

                    for (j = 0; j < s->s3->tlsext_custom_types_count; j++) {
                        if (s->s3->tlsext_custom_types[j] == type) {
                            *al = TLS1_AD_DECODE_ERROR;
                            return 0;
                        }
                    }

                    /* Callback */
                    if (record->fn1 &&
                        !record->fn1(s, type, data, size, al, record->arg))
                        return 0;

                    /* Add the (non-duplicated) entry */
                    s->s3->tlsext_custom_types_count++;
                    s->s3->tlsext_custom_types =
                        reallocarray(s->s3->tlsext_custom_types,
                                     s->s3->tlsext_custom_types_count, 2);
                    if (s->s3->tlsext_custom_types == NULL) {
                        s->s3->tlsext_custom_types = 0;
                        *al = TLS1_AD_INTERNAL_ERROR;
                        return 0;
                    }
                    s->s3->tlsext_custom_types[
                        s->s3->tlsext_custom_types_count - 1] = type;
                }
            }
        }

        data += size;
    }

    /* Spurious data on the end */
    if (data != limit)
        goto err;

    *p = data;

ri_check:

    /* Need RI if renegotiating */

    if (!renegotiate_seen && s->renegotiate) {
        *al = SSL_AD_HANDSHAKE_FAILURE;
        SSLerr(SSL_F_SSL_SCAN_CLIENTHELLO_TLSEXT,
               SSL_R_UNSAFE_LEGACY_RENEGOTIATION_DISABLED);
        return 0;
    }
    /* If no signature algorithms extension set default values */
    if (s->cert->peer_sigalgs == NULL)
        ssl_cert_set_default_md(s->cert);

    return 1;
err:
    *al = SSL_AD_DECODE_ERROR;
    return 0;
}

int ssl_parse_clienthello_tlsext(SSL *s, uint8_t **p, uint8_t *d)
{
    int al = -1;

    if (ssl_scan_clienthello_tlsext(s, p, d, &al) <= 0) {
        ssl3_send_alert(s, SSL3_AL_FATAL, al); 
        return 0;
    }

    if (ssl_check_clienthello_tlsext_early(s) <= 0) {
        SSLerr(SSL_F_SSL_PARSE_CLIENTHELLO_TLSEXT, SSL_R_CLIENTHELLO_TLSEXT);
        return 0;
    }

    return 1;
}

/*
 * ssl_next_proto_validate validates a Next Protocol Negotiation block. No
 * elements of zero length are allowed and the set of elements must exactly fill
 * the length of the block.
 */
static char ssl_next_proto_validate(const uint8_t *d, unsigned int len)
{
    CBS npn, value;

    CBS_init(&npn, d, len);
    while (CBS_len(&npn) > 0) {
        if (!CBS_get_u8_length_prefixed(&npn, &value) ||
            CBS_len(&value) == 0)
            return 0;
    }

    return 1;
}

static int ssl_scan_serverhello_tlsext(SSL *s, uint8_t **p, uint8_t *d, int n, int *al)
{
    int i;
    unsigned short length;
    unsigned short type;
    unsigned short size;
    uint8_t *data = *p;
    int tlsext_servername = 0;
    int renegotiate_seen = 0;

    s->s3->next_proto_neg_seen = 0;
    free(s->s3->alpn_selected);
    s->s3->alpn_selected = NULL;

    /* Clear observed custom extensions */
    s->s3->tlsext_custom_types_count = 0;
    free(s->s3->tlsext_custom_types);
    s->s3->tlsext_custom_types = NULL;             

    /* Clear any signature algorithms extension received */
    free(s->cert->peer_sigalgs);
    s->cert->peer_sigalgs = NULL;
    /* Clear any shared sigtnature algorithms */
    free(s->cert->shared_sigalgs);
    s->cert->shared_sigalgs = NULL;
    /* Clear certificate digests and validity flags */
    for (i = 0; i < SSL_PKEY_NUM; i++) {
        s->cert->pkeys[i].digest = NULL;
        s->cert->pkeys[i].valid_flags = 0;
    }

    if (data >= (d + n - 2))
        goto ri_check;

    n2s(data, length);
    if (data + length != d + n) {
        *al = SSL_AD_DECODE_ERROR;
        return 0;
    }

    while (data <= (d + n - 4)) {
        n2s(data, type);
        n2s(data, size);

        if (data + size > (d + n))
            goto ri_check;

        if (s->tlsext_debug_cb)
            s->tlsext_debug_cb(s, 1, type, data, size, s->tlsext_debug_arg);

        if (type == TLSEXT_TYPE_server_name) {
            if (s->tlsext_hostname == NULL || size > 0) {
                *al = TLS1_AD_UNRECOGNIZED_NAME;
                return 0;
            }
            tlsext_servername = 1;

        } else if (type == TLSEXT_TYPE_ec_point_formats && s->version != DTLS1_VERSION) {
            uint8_t *sdata = data;
            size_t formats_len;
            uint8_t *formats;

            if (size < 1) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }
            formats_len = *(sdata++);
            if (formats_len != (size_t)(size - 1)) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }

            if (!s->hit) {
                free(s->session->tlsext_ecpointformatlist);
                s->session->tlsext_ecpointformatlist = NULL;
                s->session->tlsext_ecpointformatlist_length = 0;
                formats = reallocarray(NULL, formats_len, sizeof(uint8_t));
                if (formats == NULL) {
                    *al = TLS1_AD_INTERNAL_ERROR;
                    return 0;
                }
                memcpy(formats, sdata, formats_len);
                s->session->tlsext_ecpointformatlist = formats;
                s->session->tlsext_ecpointformatlist_length = formats_len;
            }
        } else if (type == TLSEXT_TYPE_session_ticket) {
            if (s->tls_session_ticket_ext_cb 
                && !s->tls_session_ticket_ext_cb(s, data, size, s->tls_session_ticket_ext_cb_arg)) {
                *al = TLS1_AD_INTERNAL_ERROR;
                return 0;
            }
            if ((SSL_get_options(s) & SSL_OP_NO_TICKET) || (size > 0)) {
                *al = TLS1_AD_UNSUPPORTED_EXTENSION;
                return 0;
            }
            s->tlsext_ticket_expected = 1;
        } else if (type == TLSEXT_TYPE_status_request && s->version != DTLS1_VERSION) {
            /* MUST be empty and only sent if we've requested
             * a status request message.
             */
            if ((s->tlsext_status_type == -1) || (size > 0)) {
                *al = TLS1_AD_UNSUPPORTED_EXTENSION;
                return 0;
            }
            /* Set flag to expect CertificateStatus message */
            s->tlsext_status_expected = 1;
        }
        else if (type == TLSEXT_TYPE_next_proto_neg && s->s3->tmp.finish_md_len == 0) {
            uint8_t *selected;
            uint8_t selected_len;

            /* We must have requested it. */
            if (s->ctx->next_proto_select_cb == NULL) {
                *al = TLS1_AD_UNSUPPORTED_EXTENSION;
                return 0;
            }
            /* The data must be valid */
            if (!ssl_next_proto_validate(data, size)) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }
            if (s->ctx->next_proto_select_cb(s, &selected, &selected_len, data, size,
                                             s->ctx->next_proto_select_cb_arg) != SSL_TLSEXT_ERR_OK) {
                *al = TLS1_AD_INTERNAL_ERROR;
                return 0;
            }
            s->next_proto_negotiated = malloc(selected_len);
            if (!s->next_proto_negotiated) {
                *al = TLS1_AD_INTERNAL_ERROR;
                return 0;
            }
            memcpy(s->next_proto_negotiated, selected, selected_len);
            s->next_proto_negotiated_len = selected_len;
            s->s3->next_proto_neg_seen = 1;
        }
        else if (type == TLSEXT_TYPE_application_layer_protocol_negotiation) {
            unsigned int len;

            /* We must have requested it. */
            if (s->alpn_client_proto_list == NULL) {
                *al = TLS1_AD_UNSUPPORTED_EXTENSION;
                return 0;
            }
            if (size < 4) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }

            /* The extension data consists of:
             *   uint16 list_length
             *   uint8 proto_length;
             *   uint8 proto[proto_length]; */
            len = ((unsigned int)data[0]) << 8 | ((unsigned int)data[1]);
            if (len != (unsigned int)size - 2) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }
            len = data[2];
            if (len != (unsigned int)size - 3) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }
            free(s->s3->alpn_selected);
            s->s3->alpn_selected = malloc(len);
            if (s->s3->alpn_selected == NULL) {
                *al = TLS1_AD_INTERNAL_ERROR;
                return 0;
            }
            memcpy(s->s3->alpn_selected, data + 3, len);
            s->s3->alpn_selected_len = len;

        } else if (type == TLSEXT_TYPE_renegotiate) {
            if (!ssl_parse_serverhello_renegotiate_ext(s, data, size, al))
                return 0;
            renegotiate_seen = 1;
        }
#ifndef OPENSSL_NO_SRTP
        else if (type == TLSEXT_TYPE_use_srtp) {
            if (ssl_parse_serverhello_use_srtp_ext(s, data, size, al))
                return 0;
        }
#endif

        else if (type == TLSEXT_TYPE_server_authz) {
            /*
             * We only support audit proofs. It's an error to send an authz
             * hello extension if the client didn't request a proof.
             */
            uint8_t *sdata = data;
            uint8_t server_authz_dataformatlist_length;

            if (!s->ctx->tlsext_authz_server_audit_proof_cb) {
                *al = TLS1_AD_UNSUPPORTED_EXTENSION;
                return 0;
            }

            if (!size) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }

            server_authz_dataformatlist_length = *(sdata++);
            if (server_authz_dataformatlist_length != size - 1) {
                *al = TLS1_AD_DECODE_ERROR;
                return 0;
            }

            /*
             * We only support audit proofs, so a legal ServerHello
             * authz list contains exactly one entry.
             */
            if (server_authz_dataformatlist_length != 1 ||
                sdata[0] != TLSEXT_AUTHZDATAFORMAT_audit_proof) {
                *al = TLS1_AD_UNSUPPORTED_EXTENSION;
                return 0;
            }

            s->s3->tlsext_authz_server_promised = 1;
        }

        /*
         * If this extension type was not otherwise handled, but 
         * matches a custom_cli_ext_record, then send it to the
         * callback
         */
        else if (s->ctx->custom_cli_ext_records_count) {
            size_t i;
            custom_cli_ext_record *record;

            for (i = 0; i < s->ctx->custom_cli_ext_records_count; i++) {
                record = &s->ctx->custom_cli_ext_records[i];
                if (record->ext_type == type) {
                    if (record->fn2 && !record->fn2(s, type, data, size, al, record->arg))
                        return 0;
                    break;
                }
            }                       
        }

        data += size;
    }

    if (data != d + n) {
        *al = SSL_AD_DECODE_ERROR;
        return 0;
    }

    if (!s->hit && tlsext_servername == 1) {
        if (s->tlsext_hostname) {
            if (s->session->tlsext_hostname == NULL) {
                s->session->tlsext_hostname = strdup(s->tlsext_hostname);

                if (!s->session->tlsext_hostname) {
                    *al = SSL_AD_UNRECOGNIZED_NAME;
                    return 0;
                }
            } else {
                *al = SSL_AD_DECODE_ERROR;
                return 0;
            }
        }
    }

    *p = data;

ri_check:

    /* Determine if we need to see RI. Strictly speaking if we want to
     * avoid an attack we should *always* see RI even on initial server
     * hello because the client doesn't see any renegotiation during an
     * attack. However this would mean we could not connect to any server
     * which doesn't support RI so for the immediate future tolerate RI
     * absence on initial connect only.
     */
    if (!renegotiate_seen && !(s->options & SSL_OP_LEGACY_SERVER_CONNECT)) {
        *al = SSL_AD_HANDSHAKE_FAILURE;
        SSLerr(SSL_F_SSL_SCAN_SERVERHELLO_TLSEXT,
               SSL_R_UNSAFE_LEGACY_RENEGOTIATION_DISABLED);
        return 0;
    }

    return 1;
}

int ssl_prepare_clienthello_tlsext(SSL *s)
{
    return 1;
}

int ssl_prepare_serverhello_tlsext(SSL *s)
{
    return 1;
}

int ssl_check_clienthello_tlsext_early(SSL *s)
{
    int ret = SSL_TLSEXT_ERR_NOACK;
    int al = SSL_AD_UNRECOGNIZED_NAME;

    /* The handling of the ECPointFormats extension is done elsewhere, namely in
     * ssl3_choose_cipher in s3_lib.c.
     */
    /* The handling of the EllipticCurves extension is done elsewhere, namely in
     * ssl3_choose_cipher in s3_lib.c.
     */

    if (s->ctx != NULL && s->ctx->tlsext_servername_callback != 0)
        ret = s->ctx->tlsext_servername_callback(s, &al,
                                                 s->ctx->tlsext_servername_arg);
    else if (s->initial_ctx != NULL && s->initial_ctx->tlsext_servername_callback != 0)
        ret = s->initial_ctx->tlsext_servername_callback(
            s, &al, s->initial_ctx->tlsext_servername_arg);

    switch (ret) {
        case SSL_TLSEXT_ERR_ALERT_FATAL:
            ssl3_send_alert(s, SSL3_AL_FATAL, al);
            return -1;
        case SSL_TLSEXT_ERR_ALERT_WARNING:
            ssl3_send_alert(s, SSL3_AL_WARNING, al);
            return 1;
        case SSL_TLSEXT_ERR_NOACK:
            s->servername_done = 0;
        default:
            return 1;
    }
}

int ssl_check_clienthello_tlsext_late(SSL *s)
{
    int ret = SSL_TLSEXT_ERR_OK;
    int al = 0;

    /* If status request then ask callback what to do.
     * Note: this must be called after servername callbacks in case
     * the certificate has changed, and must be called after the cipher
     * has been chosen because this may influence which certificate is sent
     */
    if ((s->tlsext_status_type != -1) && s->ctx && s->ctx->tlsext_status_cb) {
        int r;
        CERT_PKEY *certpkey;
        certpkey = ssl_get_server_send_pkey(s);
        /* If no certificate can't return certificate status */
        if (certpkey == NULL) {
            s->tlsext_status_expected = 0;
            return 1;
        }
        /* Set current certificate to one we will use so
         * SSL_get_certificate et al can pick it up.
         */
        s->cert->key = certpkey;
        r = s->ctx->tlsext_status_cb(s, s->ctx->tlsext_status_arg);
        switch (r) {
            /* We don't want to send a status request response */
            case SSL_TLSEXT_ERR_NOACK:
                s->tlsext_status_expected = 0;
                break;
            /* status request response should be sent */
            case SSL_TLSEXT_ERR_OK:
                if (s->tlsext_ocsp_resp)
                    s->tlsext_status_expected = 1;
                else
                    s->tlsext_status_expected = 0;
                break;
            /* something bad happened */
            case SSL_TLSEXT_ERR_ALERT_FATAL:
                ret = SSL_TLSEXT_ERR_ALERT_FATAL;
                al = SSL_AD_INTERNAL_ERROR;
                goto err;
        }
    } else
        s->tlsext_status_expected = 0;

err:
    switch (ret) {
        case SSL_TLSEXT_ERR_ALERT_FATAL:
            ssl3_send_alert(s, SSL3_AL_FATAL, al);
            return -1;
        case SSL_TLSEXT_ERR_ALERT_WARNING:
            ssl3_send_alert(s, SSL3_AL_WARNING, al);
            return 1;
        default:
            return 1;
    }
}

int ssl_check_serverhello_tlsext(SSL *s)
{
    int ret = SSL_TLSEXT_ERR_NOACK;
    int al = SSL_AD_UNRECOGNIZED_NAME;

    /* If we are client and using an elliptic curve cryptography cipher
     * suite, then if server returns an EC point formats lists extension
     * it must contain uncompressed.
     */
    unsigned long alg_k = s->s3->tmp.new_cipher->algorithm_mkey;
    unsigned long alg_a = s->s3->tmp.new_cipher->algorithm_auth;
    if ((s->tlsext_ecpointformatlist != NULL) 
        && (s->tlsext_ecpointformatlist_length > 0) 
        && (s->session->tlsext_ecpointformatlist != NULL) 
        && (s->session->tlsext_ecpointformatlist_length > 0) 
        && ((alg_k & SSL_kECDHE)
        || (alg_a & SSL_aECDSA))) {
        /* we are using an ECC cipher */
        size_t i;
        uint8_t *list;
        int found_uncompressed = 0;
        list = s->session->tlsext_ecpointformatlist;
        for (i = 0; i < s->session->tlsext_ecpointformatlist_length; i++) {
            if (*(list++) == TLSEXT_ECPOINTFORMAT_uncompressed) {
                found_uncompressed = 1;
                break;
            }
        }
        if (!found_uncompressed) {
            SSLerr(SSL_F_SSL_CHECK_SERVERHELLO_TLSEXT,
                   SSL_R_TLS_INVALID_ECPOINTFORMAT_LIST);
            return -1;
        }
    }
    ret = SSL_TLSEXT_ERR_OK;

    if (s->ctx != NULL && s->ctx->tlsext_servername_callback != 0)
        ret = s->ctx->tlsext_servername_callback(s, &al,
                                                 s->ctx->tlsext_servername_arg);
    else if (s->initial_ctx != NULL && s->initial_ctx->tlsext_servername_callback != 0)
        ret = s->initial_ctx->tlsext_servername_callback(
            s, &al, s->initial_ctx->tlsext_servername_arg);

    free(s->tlsext_ocsp_resp);
    s->tlsext_ocsp_resp = NULL;
    s->tlsext_ocsp_resplen = -1;
    /*
     * If we've requested certificate status and we wont get one
     * tell the callback
     */
    if ((s->tlsext_status_type != -1) && !(s->tlsext_status_expected) 
        && !(s->hit) && s->ctx && s->ctx->tlsext_status_cb) {
        int r;
        /*
         * Call callback with resp == NULL and resplen == -1 so callback
         * knows there is no response
         */
        r = s->ctx->tlsext_status_cb(s, s->ctx->tlsext_status_arg);
        if (r == 0) {
            al = SSL_AD_BAD_CERTIFICATE_STATUS_RESPONSE;
            ret = SSL_TLSEXT_ERR_ALERT_FATAL;
        }
        if (r < 0) {
            al = SSL_AD_INTERNAL_ERROR;
            ret = SSL_TLSEXT_ERR_ALERT_FATAL;
        }
    }

    switch (ret) {
        case SSL_TLSEXT_ERR_ALERT_FATAL:
            ssl3_send_alert(s, SSL3_AL_FATAL, al);

            return -1;
        case SSL_TLSEXT_ERR_ALERT_WARNING:
            ssl3_send_alert(s, SSL3_AL_WARNING, al);

            return 1;
        case SSL_TLSEXT_ERR_NOACK:
            s->servername_done = 0;
        default:
            return 1;
    }
}

int ssl_parse_serverhello_tlsext(SSL *s, uint8_t **p, uint8_t *d, int n) 
{
    int al = -1;

    if (ssl_scan_serverhello_tlsext(s, p, d, n, &al) <= 0)  {
        ssl3_send_alert(s, SSL3_AL_FATAL, al);
        return 0;
    }

    if (ssl_check_serverhello_tlsext(s) <= 0) {
        SSLerr(SSL_F_SSL_PARSE_SERVERHELLO_TLSEXT, SSL_R_SERVERHELLO_TLSEXT);
        return 0;
    }

    return 1;
}

/* Since the server cache lookup is done early on in the processing of the
 * ClientHello, and other operations depend on the result, we need to handle
 * any TLS session ticket extension at the same time.
 *
 *   session_id: points at the session ID in the ClientHello. This code will
 *       read past the end of this in order to parse out the session ticket
 *       extension, if any.
 *   len: the length of the session ID.
 *   limit: a pointer to the first byte after the ClientHello.
 *   ret: (output) on return, if a ticket was decrypted, then this is set to
 *       point to the resulting session.
 *
 * If s->tls_session_secret_cb is set then we are expecting a pre-shared key
 * ciphersuite, in which case we have no use for session tickets and one will
 * never be decrypted, nor will s->tlsext_ticket_expected be set to 1.
 *
 * Returns:
 *   -1: fatal error, either from parsing or decrypting the ticket.
 *    0: no ticket was found (or was ignored, based on settings).
 *    1: a zero length extension was found, indicating that the client supports
 *       session tickets but doesn't currently have one to offer.
 *    2: either s->tls_session_secret_cb was set, or a ticket was offered but
 *       couldn't be decrypted because of a non-fatal error.
 *    3: a ticket was successfully decrypted and *ret was set.
 *
 * Side effects:
 *   Sets s->tlsext_ticket_expected to 1 if the server will have to issue
 *   a new session ticket to the client because the client indicated support
 *   (and s->tls_session_secret_cb is NULL) but the client either doesn't have
 *   a session ticket or we couldn't use the one it gave us, or if
 *   s->ctx->tlsext_ticket_key_cb asked to renew the client's ticket.
 *   Otherwise, s->tlsext_ticket_expected is set to 0.
 */
int tls1_process_ticket(SSL *s, const uint8_t *session, int session_len,
                        const uint8_t *limit, SSL_SESSION **ret)
{
    /* Point after session ID in client hello */
    CBS session_id, cookie, cipher_list, compression_alg, extensions;

    *ret = NULL;
    s->tlsext_ticket_expected = 0;

    /* If tickets disabled behave as if no ticket present
     * to permit stateful resumption.
     */
    if (SSL_get_options(s) & SSL_OP_NO_TICKET)
        return 0;
    if (!limit)
        return 0;
    if (limit < session)
        return -1;

    CBS_init(&session_id, session, limit - session);

    /* Skip past the session id */
    if (!CBS_skip(&session_id, session_len))
        return -1;

    /* Skip past DTLS cookie */
    if (SSL_IS_DTLS(s)) {
        if (!CBS_get_u8_length_prefixed(&session_id, &cookie))
            return -1;
    }
    /* Skip past cipher list */
    if (!CBS_get_u16_length_prefixed(&session_id, &cipher_list))
        return -1;
    /* Skip past compression algorithm list */
    if (!CBS_get_u8_length_prefixed(&session_id, &compression_alg))
        return -1;
    /* Now at start of extensions */
    if (!CBS_get_u16_length_prefixed(&session_id, &extensions))
        return -1;

    while (CBS_len(&extensions) > 0) {
        CBS ext_data;
        uint16_t ext_type;

        if (!CBS_get_u16(&extensions, &ext_type) ||
            !CBS_get_u16_length_prefixed(&extensions, &ext_data))
            return -1;

        if (ext_type == TLSEXT_TYPE_session_ticket) {
            int r;
            if (CBS_len(&ext_data) == 0) {
                /* The client will accept a ticket but doesn't
                 * currently have one. */
                s->tlsext_ticket_expected = 1;
                return 1;
            }
            if (s->tls_session_secret_cb) {
                /* Indicate that the ticket couldn't be
                 * decrypted rather than generating the session
                 * from ticket now, trigger abbreviated
                 * handshake based on external mechanism to
                 * calculate the master secret later. */
                return 2;
            }
            r = tls_decrypt_ticket(s, CBS_data(&ext_data), CBS_len(&ext_data),
                                   session, session_len, ret);
            switch (r) {
                case 2: /* ticket couldn't be decrypted */
                    s->tlsext_ticket_expected = 1;
                    return 2;
                case 3: /* ticket was decrypted */
                    return r;
                case 4: /* ticket decrypted but need to renew */
                    s->tlsext_ticket_expected = 1;
                    return 3;
                default: /* fatal error */
                    return -1;
            }
        }
    }
    return 0;
}

/* tls_decrypt_ticket attempts to decrypt a session ticket.
 *
 *   etick: points to the body of the session ticket extension.
 *   eticklen: the length of the session tickets extension.
 *   sess_id: points at the session ID.
 *   sesslen: the length of the session ID.
 *   psess: (output) on return, if a ticket was decrypted, then this is set to
 *       point to the resulting session.
 *
 * Returns:
 *   -1: fatal error, either from parsing or decrypting the ticket.
 *    2: the ticket couldn't be decrypted.
 *    3: a ticket was successfully decrypted and *psess was set.
 *    4: same as 3, but the ticket needs to be renewed.
 */
static int tls_decrypt_ticket(SSL *s, const uint8_t *etick, int eticklen,
                              const uint8_t *sess_id, int sesslen,
                              SSL_SESSION **psess)
{
    SSL_SESSION *sess;
    uint8_t *sdec;
    const uint8_t *p;
    int slen, mlen, renew_ticket = 0;
    uint8_t tick_hmac[EVP_MAX_MD_SIZE];
    HMAC_CTX hctx;
    EVP_CIPHER_CTX ctx;
    SSL_CTX *tctx = s->initial_ctx;
    /* Need at least keyname + iv + some encrypted data */
    if (eticklen < 48)
        return 2;
    /* Initialize session ticket encryption and HMAC contexts */
    HMAC_CTX_init(&hctx);
    EVP_CIPHER_CTX_init(&ctx);
    if (tctx->tlsext_ticket_key_cb) {
        uint8_t *nctick = (uint8_t *)etick;
        int rv = tctx->tlsext_ticket_key_cb(s, nctick, nctick + 16, &ctx, &hctx, 0);
        if (rv < 0) {
            EVP_CIPHER_CTX_cleanup(&ctx);
            return -1;
        }
        if (rv == 0) {
            EVP_CIPHER_CTX_cleanup(&ctx);
            return 2;
        }
        if (rv == 2)
            renew_ticket = 1;
    } else {
        /* Check key name matches */
        if (memcmp(etick, tctx->tlsext_tick_key_name, 16))
            return 2;
        HMAC_Init_ex(&hctx, tctx->tlsext_tick_hmac_key, 16, EVP_sha256(), NULL);
        EVP_DecryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, tctx->tlsext_tick_aes_key,
                           etick + 16);
    }
    /* Attempt to process session ticket, first conduct sanity and
     * integrity checks on ticket.
     */
    mlen = HMAC_size(&hctx);
    if (mlen < 0) {
        EVP_CIPHER_CTX_cleanup(&ctx);
        return -1;
    }
    eticklen -= mlen;
    /* Check HMAC of encrypted ticket */
    HMAC_Update(&hctx, etick, eticklen);
    HMAC_Final(&hctx, tick_hmac, NULL);
    HMAC_CTX_cleanup(&hctx);
    if (memcmp(tick_hmac, etick + eticklen, mlen) != 0) {
        EVP_CIPHER_CTX_cleanup(&ctx);
        return 2;
    }
    /* Attempt to decrypt session data */
    /* Move p after IV to start of encrypted ticket, update length */
    p = etick + 16 + EVP_CIPHER_CTX_iv_length(&ctx);
    eticklen -= 16 + EVP_CIPHER_CTX_iv_length(&ctx);
    sdec = malloc(eticklen);
    if (!sdec) {
        EVP_CIPHER_CTX_cleanup(&ctx);
        return -1;
    }
    EVP_DecryptUpdate(&ctx, sdec, &slen, p, eticklen);
    if (EVP_DecryptFinal(&ctx, sdec + slen, &mlen) <= 0) {
        free(sdec);
        EVP_CIPHER_CTX_cleanup(&ctx);
        return 2;
    }
    slen += mlen;
    EVP_CIPHER_CTX_cleanup(&ctx);
    p = sdec;

    sess = d2i_SSL_SESSION(NULL, &p, slen);
    free(sdec);
    if (sess) {
        /* The session ID, if non-empty, is used by some clients to
         * detect that the ticket has been accepted. So we copy it to
         * the session structure. If it is empty set length to zero
         * as required by standard.
         */
        if (sesslen)
            memcpy(sess->session_id, sess_id, sesslen);
        sess->session_id_length = sesslen;
        *psess = sess;
        if (renew_ticket)
            return 4;
        else
            return 3;
    }
    ERR_clear_error();
    /* For session parse failure, indicate that we need to send a new
     * ticket. */
    return 2;
}

/* Tables to translate from NIDs to TLS v1.2 ids */

typedef struct {
    int nid;
    int id;
} tls12_lookup;

static tls12_lookup tls12_md[] = {
    { NID_md5, TLSEXT_hash_md5 },
    { NID_sha1, TLSEXT_hash_sha1 },
    { NID_sha224, TLSEXT_hash_sha224 },
    { NID_sha256, TLSEXT_hash_sha256 },
    { NID_sha384, TLSEXT_hash_sha384 },
    { NID_sha512, TLSEXT_hash_sha512 }
};

static tls12_lookup tls12_sig[] = {
    { EVP_PKEY_RSA, TLSEXT_signature_rsa },
    { EVP_PKEY_DSA, TLSEXT_signature_dsa },
    { EVP_PKEY_EC, TLSEXT_signature_ecdsa }
};

static int tls12_find_id(int nid, tls12_lookup *table, size_t tlen)
{
    size_t i;
    for (i = 0; i < tlen; i++) {
        if (table[i].nid == nid)
            return table[i].id;
    }
    return -1;
}

static int tls12_find_nid(int id, tls12_lookup *table, size_t tlen)
{
    size_t i;
    for (i = 0; i < tlen; i++) {
        if (table[i].id == id)
            return table[i].nid;
    }
    return NID_undef;
}

int tls12_get_sigandhash(uint8_t *p, const EVP_PKEY *pk,
                         const EVP_MD *md)
{
    int sig_id, md_id;
    if (!md)
        return 0;
    md_id = tls12_find_id(EVP_MD_type(md), tls12_md,
                          sizeof(tls12_md) / sizeof(tls12_lookup));
    if (md_id == -1)
        return 0;
    sig_id = tls12_get_sigid(pk);
    if (sig_id == -1)
        return 0;
    p[0] = (uint8_t)md_id;
    p[1] = (uint8_t)sig_id;
    return 1;
}

int tls12_get_sigid(const EVP_PKEY *pk)
{
    return tls12_find_id(pk->type, tls12_sig,
                         sizeof(tls12_sig) / sizeof(tls12_lookup));
}

const EVP_MD *tls12_get_hash(uint8_t hash_alg)
{
    switch (hash_alg) {
        case TLSEXT_hash_sha1:
            return EVP_sha1();
        case TLSEXT_hash_sha224:
            return EVP_sha224();
        case TLSEXT_hash_sha256:
            return EVP_sha256();
        case TLSEXT_hash_sha384:
            return EVP_sha384();
        case TLSEXT_hash_sha512:
            return EVP_sha512();
        default:
            return NULL;
    }
}

static int tls12_get_pkey_idx(uint8_t sig_alg)
{
    switch (sig_alg) {
        case TLSEXT_signature_rsa:
            return SSL_PKEY_RSA_SIGN;
        case TLSEXT_signature_dsa:
            return SSL_PKEY_DSA_SIGN;
        case TLSEXT_signature_ecdsa:
            return SSL_PKEY_ECC;
    }
    return -1;
}

/* Convert TLS 1.2 signature algorithm extension values into NIDs */
static void tls1_lookup_sigalg(int *phash_nid, int *psign_nid,
                               int *psignhash_nid, const uint8_t *data)
{
    int sign_nid, hash_nid;
    if (!phash_nid && !psign_nid && !psignhash_nid)
        return;
    if (phash_nid  != NULL || psignhash_nid != NULL) {
        hash_nid = tls12_find_nid(data[0], tls12_md,
                                  sizeof(tls12_md) / sizeof(tls12_lookup));
        if (phash_nid != NULL)
            *phash_nid = hash_nid;
    }
    if (psign_nid != NULL || psignhash_nid != NULL) {
        sign_nid = tls12_find_nid(data[1], tls12_sig,
                                  sizeof(tls12_sig) / sizeof(tls12_lookup));
        if (psign_nid != NULL)
            *psign_nid = sign_nid;
    }
    if (psignhash_nid != NULL) {
        if (sign_nid && hash_nid)
            OBJ_find_sigid_by_algs(psignhash_nid, hash_nid, sign_nid);
        else
            *psignhash_nid = NID_undef;
    }
}

/* Given preference and allowed sigalgs set shared sigalgs */
static int tls12_do_shared_sigalgs(TLS_SIGALGS *shsig, const uint8_t *pref,
                                   size_t preflen, const uint8_t *allow,
                                   size_t allowlen)
{
    const uint8_t *ptmp, *atmp;
    size_t i, j, nmatch = 0;
    for (i = 0, ptmp = pref; i < preflen; i += 2, ptmp += 2) {
        /* Skip disabled hashes or signature algorithms */
        if (tls12_get_hash(ptmp[0]) == NULL)
            continue;
        if (tls12_get_pkey_idx(ptmp[1]) == -1)
            continue;
        for (j = 0, atmp = allow; j < allowlen; j += 2, atmp += 2) {
            if (ptmp[0] == atmp[0] && ptmp[1] == atmp[1]) {
                nmatch++;
                if (shsig) {
                    shsig->rhash = ptmp[0];
                    shsig->rsign = ptmp[1];
                    tls1_lookup_sigalg(&shsig->hash_nid, &shsig->sign_nid,
                                       &shsig->signandhash_nid, ptmp);
                    shsig++;
                }
                break;
            }
        }
    }
    return nmatch;
}

/* Set shared signature algorithms for SSL structures */
static int tls1_set_shared_sigalgs(SSL *s)
{
    const uint8_t *pref, *allow, *conf;
    size_t preflen, allowlen, conflen;
    size_t nmatch;
    TLS_SIGALGS *salgs = NULL;
    CERT *c = s->cert;
    unsigned int is_suiteb = tls1_suiteb(s);

    /* If client use client signature algorithms if not NULL */
    if (!s->server && c->client_sigalgs != NULL && !is_suiteb) {
        conf = c->client_sigalgs;
        conflen = c->client_sigalgslen;
    } else if (c->conf_sigalgs && !is_suiteb) {
        conf = c->conf_sigalgs;
        conflen = c->conf_sigalgslen;
    } else {
        conflen = tls12_get_psigalgs(s, &conf);
    }
    if (s->options & SSL_OP_CIPHER_SERVER_PREFERENCE || is_suiteb) {
        pref = conf;
        preflen = conflen;
        allow = c->peer_sigalgs;
        allowlen = c->peer_sigalgslen;
    } else {
        allow = conf;
        allowlen = conflen;
        pref = c->peer_sigalgs;
        preflen = c->peer_sigalgslen;
    }
    nmatch = tls12_do_shared_sigalgs(NULL, pref, preflen, allow, allowlen);
    if (!nmatch)
        return 1;
    salgs = reallocarray(NULL, nmatch, sizeof(TLS_SIGALGS));
    if (salgs == NULL)
        return 0;
    nmatch = tls12_do_shared_sigalgs(salgs, pref, preflen, allow, allowlen);
    c->shared_sigalgs = salgs;
    c->shared_sigalgslen = nmatch;
    return 1;
}

/* Set preferred digest for each key type */

int tls1_process_sigalgs(SSL *s, const uint8_t *data, int dsize)
{
    int idx;
    size_t i;
    const EVP_MD *md;
    CERT *c = s->cert;
    TLS_SIGALGS *sigptr;

    /* Extension ignored for inappropriate versions */
    if (!SSL_USE_SIGALGS(s))
        return 1;

    /* Should never happen */
    if (!c || dsize < 0)
        return 0;

    free(c->peer_sigalgs);
    c->peer_sigalgs = malloc(dsize);
    if (c->peer_sigalgs == NULL)
        return 0;
    c->peer_sigalgslen = dsize;
    memcpy(c->peer_sigalgs, data, dsize);

    tls1_set_shared_sigalgs(s);

    for (i = 0, sigptr = c->shared_sigalgs; i < c->shared_sigalgslen;
            i++, sigptr++)
    {
        idx = tls12_get_pkey_idx(sigptr->rsign);
        if (idx > 0 && c->pkeys[idx].digest == NULL) {
            md = tls12_get_hash(sigptr->rhash);
            c->pkeys[idx].digest = md;
            c->pkeys[idx].valid_flags = CERT_PKEY_EXPLICIT_SIGN;
            if (idx == SSL_PKEY_RSA_SIGN) {
                c->pkeys[SSL_PKEY_RSA_ENC].valid_flags = CERT_PKEY_EXPLICIT_SIGN;
                c->pkeys[SSL_PKEY_RSA_ENC].digest = md;
            }
        }
    }

    /*
     * In strict mode leave unset digests as NULL to indicate we can't
     * use the certificate for signing.
     */
    if (!(s->cert->cert_flags & SSL_CERT_FLAGS_CHECK_TLS_STRICT)) {
        if (!c->pkeys[SSL_PKEY_DSA_SIGN].digest)
            c->pkeys[SSL_PKEY_DSA_SIGN].digest = EVP_sha1();
        if (!c->pkeys[SSL_PKEY_RSA_SIGN].digest) {
            c->pkeys[SSL_PKEY_RSA_SIGN].digest = EVP_sha1();
            c->pkeys[SSL_PKEY_RSA_ENC].digest = EVP_sha1();
        }
        if (!c->pkeys[SSL_PKEY_ECC].digest)
            c->pkeys[SSL_PKEY_ECC].digest = EVP_sha1();
    }
    return 1;
}

int SSL_get_sigalgs(SSL *s, int idx, int *psign, int *phash, int *psignhash,
                    uint8_t *rsig, uint8_t *rhash)
{
    const uint8_t *psig = s->cert->peer_sigalgs;
    if (psig == NULL)
        return 0;
    if (idx >= 0) {
        idx <<= 1;
        if (idx >= (int)s->cert->peer_sigalgslen)
            return 0;
        psig += idx;
        if (rhash)
            *rhash = psig[0];
        if (rsig)
            *rsig = psig[1];
        tls1_lookup_sigalg(phash, psign, psignhash, psig);
    }
    return s->cert->peer_sigalgslen / 2;
}

int SSL_get_shared_sigalgs(SSL *s, int idx, int *psign, int *phash,
                           int *psignhash, uint8_t *rsig, uint8_t *rhash)
{
    TLS_SIGALGS *shsigalgs = s->cert->shared_sigalgs;
    if (shsigalgs == NULL || idx >= (int)s->cert->shared_sigalgslen)
        return 0;
    shsigalgs += idx;
    if (phash != NULL)
        *phash = shsigalgs->hash_nid;
    if (psign != NULL)
        *psign = shsigalgs->sign_nid;
    if (psignhash != NULL)
        *psignhash = shsigalgs->signandhash_nid;
    if (rsig != NULL)
        *rsig = shsigalgs->rsign;
    if (rhash != NULL)
        *rhash = shsigalgs->rhash;
    return s->cert->shared_sigalgslen;
 }

#define MAX_SIGALGLEN (TLSEXT_hash_num * TLSEXT_signature_num * 2)

typedef struct {
    size_t sigalgcnt;
    int sigalgs[MAX_SIGALGLEN];
} sig_cb_st;

static int sig_cb(const char *elem, int len, void *arg)
{
    sig_cb_st *sarg = arg;
    size_t i;
    char etmp[20], *p;
    int sig_alg, hash_alg;
    if (sarg->sigalgcnt == MAX_SIGALGLEN)
        return 0;
    if (len > (int)(sizeof(etmp) - 1))
        return 0;
    memcpy(etmp, elem, len);
    etmp[len] = 0;
    p = strchr(etmp, '+');
    if (p == NULL)
        return 0;
    *p = '\0';
    p++;
    if (*p == '\0')
        return 0;

    if (strcmp(etmp, "RSA") == 0)
        sig_alg = EVP_PKEY_RSA;
    else if (strcmp(etmp, "DSA") == 0)
        sig_alg = EVP_PKEY_DSA;
    else if (strcmp(etmp, "ECDSA") == 0)
        sig_alg = EVP_PKEY_EC;
    else
        return 0;

    hash_alg = OBJ_sn2nid(p);
    if (hash_alg == NID_undef)
        hash_alg = OBJ_ln2nid(p);
    if (hash_alg == NID_undef)
        return 0;

    for (i = 0; i < sarg->sigalgcnt; i += 2) {
        if (sarg->sigalgs[i] == sig_alg && sarg->sigalgs[i + 1] == hash_alg)
            return 0;
    }
    sarg->sigalgs[sarg->sigalgcnt++] = hash_alg;
    sarg->sigalgs[sarg->sigalgcnt++] = sig_alg;
    return 1;
}

/* Set suppored signature algorithms based on a colon separated list
 * of the form sig+hash e.g. RSA+SHA512:DSA+SHA512 */
int tls1_set_sigalgs_list(CERT *c, const char *str, int client)
{
    sig_cb_st sig;
    sig.sigalgcnt = 0;
    if (!CONF_parse_list(str, ':', 1, sig_cb, &sig))
        return 0;
    if (c == NULL)
        return 1;
    return tls1_set_sigalgs(c, sig.sigalgs, sig.sigalgcnt, client);
}

int tls1_set_sigalgs(CERT *c, const int *psig_nids, size_t salglen, int client)
{
    uint8_t *sigalgs, *sptr;
    int rhash, rsign;
    size_t i;
    if (salglen & 1)
        return 0;
    sigalgs = malloc(salglen);
    if (sigalgs == NULL)
        return 0;
    for (i = 0, sptr = sigalgs; i < salglen; i += 2) {
        rhash = tls12_find_id(*psig_nids++, tls12_md,
                              sizeof(tls12_md) / sizeof(tls12_lookup));
        rsign = tls12_find_id(*psig_nids++, tls12_sig,
                              sizeof(tls12_sig) / sizeof(tls12_lookup));

        if (rhash == -1 || rsign == -1)
            goto err;

        *sptr++ = rhash;
        *sptr++ = rsign;
    }

    if (client) {
        free(c->client_sigalgs);
        c->client_sigalgs = sigalgs;
        c->client_sigalgslen = salglen;
    } else {
        free(c->conf_sigalgs);
        c->conf_sigalgs = sigalgs;
        c->conf_sigalgslen = salglen;
    }

    return 1;

err:
    free(sigalgs);
    return 0;
}

static int tls1_check_sig_alg(CERT *c, X509 *x, int default_nid)
{
    int sig_nid;
    size_t i;

    if (default_nid == -1)
        return 1;

    sig_nid = X509_get_signature_nid(x);
    if (default_nid)
        return sig_nid == default_nid ? 1 : 0;

    for (i = 0; i < c->shared_sigalgslen; i++) {
        if (sig_nid == c->shared_sigalgs[i].signandhash_nid)
            return 1;
    }

    return 0;
}

/* Check to see if a certificate issuer name matches list of CA names */
static int ssl_check_ca_name(STACK_OF(X509_NAME) *names, X509 *x)
{
    X509_NAME *nm;
    int i;

    nm = X509_get_issuer_name(x);
    for (i = 0; i < sk_X509_NAME_num(names); i++) {
        if (!X509_NAME_cmp(nm, sk_X509_NAME_value(names, i)))
            return 1;
    }

    return 0;
}

/*
 * Check certificate chain is consistent with TLS extensions and is
 * usable by server. This servers two purposes: it allows users to
 * check chains before passing them to the server and it allows the
 * server to check chains before attempting to use them.
 */

/* Flags which need to be set for a certificate when stict mode not set */

#define CERT_PKEY_VALID_FLAGS \
       (CERT_PKEY_EE_SIGNATURE | CERT_PKEY_EE_PARAM)
/* Strict mode flags */
#define CERT_PKEY_STRICT_FLAGS \
        (CERT_PKEY_VALID_FLAGS | CERT_PKEY_CA_SIGNATURE | CERT_PKEY_CA_PARAM \
        | CERT_PKEY_ISSUER_NAME | CERT_PKEY_CERT_TYPE)

int tls1_check_chain(SSL *s, X509 *x, EVP_PKEY *pk, STACK_OF(X509) *chain,
                     int idx)
{
    int i;
    int rv = 0;
    int check_flags = 0, strict_mode;
    CERT_PKEY *cpk = NULL;
    CERT *c = s->cert;
    unsigned int suiteb_flags = tls1_suiteb(s);

    /* idx != -1 means checking server chains */
    if (idx != -1) {
        /* idx == -2 means checking client certificate chains */
        if (idx == -2) {
            cpk = c->key;
            idx = cpk - c->pkeys;
        } else {
            cpk = c->pkeys + idx;
        }
        x = cpk->x509;
        pk = cpk->privatekey;
        chain = cpk->chain;
        strict_mode = c->cert_flags & SSL_CERT_FLAGS_CHECK_TLS_STRICT;
        /* If no cert or key, forget it */
        if (!x || !pk)
            goto end;
    } else {
        if (x == NULL || pk == NULL)
            goto end;
        idx = ssl_cert_type(x, pk);
        if (idx == -1)
            goto end;
        cpk = c->pkeys + idx;
        if (c->cert_flags & SSL_CERT_FLAGS_CHECK_TLS_STRICT)
            check_flags = CERT_PKEY_STRICT_FLAGS;
        else
            check_flags = CERT_PKEY_VALID_FLAGS;
        strict_mode = 1;
    }

    if (suiteb_flags) {
        int ok;
        if (check_flags)
            check_flags |= CERT_PKEY_SUITEB;
        ok = X509_chain_check_suiteb(NULL, x, chain, suiteb_flags);
        if (ok != X509_V_OK) {
            if (check_flags)
                rv |= CERT_PKEY_SUITEB;
            else
                goto end;
        }
    }

    /*
     * Check all signature algorithms are consistent with
     * signature algorithms extension if TLS 1.2 or later
     * and strict mode.
     */
    if (TLS1_get_version(s) >= TLS1_2_VERSION && strict_mode) {
        int default_nid;
        uint8_t rsign = 0;
        if (c->peer_sigalgs)
            default_nid = 0;
        /* If no sigalgs extension use defaults from RFC5246 */
        else {
            switch (idx) {
                case SSL_PKEY_RSA_ENC:
                case SSL_PKEY_RSA_SIGN:
                case SSL_PKEY_DH_RSA:
                    rsign = TLSEXT_signature_rsa;
                    default_nid = NID_sha1WithRSAEncryption;
                    break;

                case SSL_PKEY_DSA_SIGN:
                case SSL_PKEY_DH_DSA:
                    rsign = TLSEXT_signature_dsa;
                    default_nid = NID_dsaWithSHA1;
                    break;

                case SSL_PKEY_ECC:
                    rsign = TLSEXT_signature_ecdsa;
                    default_nid = NID_ecdsa_with_SHA1;
                    break;

                default:
                    default_nid = -1;
                    break;
            }
        }
        /*
         * If peer sent no signature algorithms extension and we
         * have set preferred signature algorithms check we support
         * sha1.
         */
        if (default_nid > 0 && c->conf_sigalgs) {
            size_t j;
            const uint8_t *p = c->conf_sigalgs;
            for (j = 0; j < c->conf_sigalgslen; j += 2, p += 2) {
                if (p[0] == TLSEXT_hash_sha1 && p[1] == rsign)
                    break;
            }
            if (j == c->conf_sigalgslen) {
                if (check_flags)
                    goto skip_sigs;
                else
                    goto end;
            }
        }
        /* Check signature algorithm of each cert in chain */
        if (!tls1_check_sig_alg(c, x, default_nid)) {
            if (!check_flags)
                goto end;
        } else
            rv |= CERT_PKEY_EE_SIGNATURE;
        rv |= CERT_PKEY_CA_SIGNATURE;
        for (i = 0; i < sk_X509_num(chain); i++) {
            if (!tls1_check_sig_alg(c, sk_X509_value(chain, i), default_nid)) {
                if (check_flags) {
                    rv &= ~CERT_PKEY_CA_SIGNATURE;
                    break;
                } else
                    goto end;
            }
        }
    }

    /* Else not TLS 1.2, so mark EE and CA signing algorithms OK */
    else if (check_flags)
        rv |= CERT_PKEY_EE_SIGNATURE | CERT_PKEY_CA_SIGNATURE;
skip_sigs:
    /* Check cert parameters are consistent */
    if (tls1_check_cert_param(s, x, check_flags ? 1 : 2))
        rv |= CERT_PKEY_EE_PARAM;
    else if (!check_flags)
        goto end;
    if (!s->server)
        rv |= CERT_PKEY_CA_PARAM;
    /* In strict mode check rest of chain too */
    else if (strict_mode) {
        rv |= CERT_PKEY_CA_PARAM;
        for (i = 0; i < sk_X509_num(chain); i++) {
            X509 *ca = sk_X509_value(chain, i);
            if (!tls1_check_cert_param(s, ca, 0)) {
                if (check_flags) {
                    rv &= ~CERT_PKEY_CA_PARAM;
                    break;
                } else
                    goto end;
            }
        }
    }
    if (!s->server && strict_mode) {
        STACK_OF(X509_NAME) * ca_dn;
        int check_type = 0;
        switch (pk->type) {
            case EVP_PKEY_RSA:
                check_type = TLS_CT_RSA_SIGN;
                break;
            case EVP_PKEY_DSA:
                check_type = TLS_CT_DSS_SIGN;
                break;
            case EVP_PKEY_EC:
                check_type = TLS_CT_ECDSA_SIGN;
                break;
            case EVP_PKEY_DH:
            case EVP_PKEY_DHX: {
                int cert_type = X509_certificate_type(x, pk);
                if (cert_type & EVP_PKS_RSA)
                    check_type = TLS_CT_RSA_FIXED_DH;
                if (cert_type & EVP_PKS_DSA)
                    check_type = TLS_CT_DSS_FIXED_DH;
            }
        }
        if (check_type) {
            const uint8_t *ctypes;
            int ctypelen;
            if (c->ctypes) {
                ctypes   = c->ctypes;
                ctypelen = (int)c->ctype_num;
            } else {
                ctypes   = (uint8_t *)s->s3->tmp.ctype;
                ctypelen = s->s3->tmp.ctype_num;
            }
            for (i = 0; i < ctypelen; i++) {
                if (ctypes[i] == check_type) {
                    rv |= CERT_PKEY_CERT_TYPE;
                    break;
                }
            }
            if (!(rv & CERT_PKEY_CERT_TYPE) && !check_flags)
                goto end;
        } else
            rv |= CERT_PKEY_CERT_TYPE;

        ca_dn = s->s3->tmp.ca_names;

        if (!sk_X509_NAME_num(ca_dn))
            rv |= CERT_PKEY_ISSUER_NAME;

        if (!(rv & CERT_PKEY_ISSUER_NAME)) {
            if (ssl_check_ca_name(ca_dn, x))
                rv |= CERT_PKEY_ISSUER_NAME;
        }
        if (!(rv & CERT_PKEY_ISSUER_NAME)) {
            for (i = 0; i < sk_X509_num(chain); i++) {
                X509 *xtmp = sk_X509_value(chain, i);
                if (ssl_check_ca_name(ca_dn, xtmp)) {
                    rv |= CERT_PKEY_ISSUER_NAME;
                    break;
                }
            }
        }
        if (!check_flags && !(rv & CERT_PKEY_ISSUER_NAME))
            goto end;
    } else
        rv |= CERT_PKEY_ISSUER_NAME | CERT_PKEY_CERT_TYPE;

    if (!check_flags || (rv & check_flags) == check_flags)
        rv |= CERT_PKEY_VALID;

end:

    if (TLS1_get_version(s) >= TLS1_2_VERSION) {
        if (cpk->valid_flags & CERT_PKEY_EXPLICIT_SIGN)
            rv |= CERT_PKEY_EXPLICIT_SIGN | CERT_PKEY_SIGN;
        else if (cpk->digest)
            rv |= CERT_PKEY_SIGN;
    } else
        rv |= CERT_PKEY_SIGN | CERT_PKEY_EXPLICIT_SIGN;

    /*
     * When checking a CERT_PKEY structure all flags are irrelevant
     * if the chain is invalid.
     */
    if (!check_flags) {
        if (rv & CERT_PKEY_VALID)
            cpk->valid_flags = rv;
        else {
            /* Preserve explicit sign flag, clear rest */
            cpk->valid_flags &= CERT_PKEY_EXPLICIT_SIGN;
            return 0;
        }
    }
    return rv;
}

/* Set validity of certificates in an SSL structure */
void tls1_set_cert_validity(SSL *s)
{
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_RSA_ENC);
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_RSA_SIGN);
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_DSA_SIGN);
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_DH_RSA);
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_DH_DSA);
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_ECC);
}

/* User level utiity function to check a chain is suitable */
int SSL_check_chain(SSL *s, X509 *x, EVP_PKEY *pk, STACK_OF(X509) *chain)
{
    return tls1_check_chain(s, x, pk, chain, -1);
}
