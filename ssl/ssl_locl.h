/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */
/* ====================================================================
 * Copyright 2002 Sun Microsystems, Inc. ALL RIGHTS RESERVED.
 * ECC cipher suite support in OpenSSL originally developed by
 * SUN MICROSYSTEMS, INC., and contributed to the OpenSSL project.
 */

#ifndef HEADER_SSL_LOCL_H
#define HEADER_SSL_LOCL_H

#include <sys/types.h>

#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <openssl/opensslconf.h>
#include <openssl/buffer.h>
#include <openssl/bio.h>
#include <openssl/stack.h>
#include <openssl/rsa.h>
#include <openssl/dsa.h>
#include <openssl/err.h>
#include <openssl/ssl.h>

#define c2l(c, l)                                                              \
    (l = ((unsigned long)(*((c)++))), l |= (((unsigned long)(*((c)++))) << 8), \
     l |= (((unsigned long)(*((c)++))) << 16),                                 \
     l |= (((unsigned long)(*((c)++))) << 24))

/* NOTE - c is not incremented as per c2l */
#define c2ln(c, l1, l2, n)                               \
    {                                                    \
        c += n;                                          \
        l1 = l2 = 0;                                     \
        switch (n) {                                     \
            case 8:                                      \
                l2 = ((unsigned long)(*(--(c)))) << 24;  \
            case 7:                                      \
                l2 |= ((unsigned long)(*(--(c)))) << 16; \
            case 6:                                      \
                l2 |= ((unsigned long)(*(--(c)))) << 8;  \
            case 5:                                      \
                l2 |= ((unsigned long)(*(--(c))));       \
            case 4:                                      \
                l1 = ((unsigned long)(*(--(c)))) << 24;  \
            case 3:                                      \
                l1 |= ((unsigned long)(*(--(c)))) << 16; \
            case 2:                                      \
                l1 |= ((unsigned long)(*(--(c)))) << 8;  \
            case 1:                                      \
                l1 |= ((unsigned long)(*(--(c))));       \
        }                                                \
    }

#define l2c(l, c)                                    \
    (*((c)++) = (uint8_t)(((l)) & 0xff),       \
     *((c)++) = (uint8_t)(((l) >> 8) & 0xff),  \
     *((c)++) = (uint8_t)(((l) >> 16) & 0xff), \
     *((c)++) = (uint8_t)(((l) >> 24) & 0xff))

#define n2l(c, l)                            \
    (l = ((unsigned long)(*((c)++))) << 24,  \
     l |= ((unsigned long)(*((c)++))) << 16, \
     l |= ((unsigned long)(*((c)++))) << 8, l |= ((unsigned long)(*((c)++))))

#define l2n(l, c)                                    \
    (*((c)++) = (uint8_t)(((l) >> 24) & 0xff), \
     *((c)++) = (uint8_t)(((l) >> 16) & 0xff), \
     *((c)++) = (uint8_t)(((l) >> 8) & 0xff),  \
     *((c)++) = (uint8_t)(((l)) & 0xff))

#define l2n8(l, c)                                   \
    (*((c)++) = (uint8_t)(((l) >> 56) & 0xff), \
     *((c)++) = (uint8_t)(((l) >> 48) & 0xff), \
     *((c)++) = (uint8_t)(((l) >> 40) & 0xff), \
     *((c)++) = (uint8_t)(((l) >> 32) & 0xff), \
     *((c)++) = (uint8_t)(((l) >> 24) & 0xff), \
     *((c)++) = (uint8_t)(((l) >> 16) & 0xff), \
     *((c)++) = (uint8_t)(((l) >> 8) & 0xff),  \
     *((c)++) = (uint8_t)(((l)) & 0xff))

/* NOTE - c is not incremented as per l2c */
#define l2cn(l1, l2, c, n)                                       \
    {                                                            \
        c += n;                                                  \
        switch (n) {                                             \
            case 8:                                              \
                *(--(c)) = (uint8_t)(((l2) >> 24) & 0xff); \
            case 7:                                              \
                *(--(c)) = (uint8_t)(((l2) >> 16) & 0xff); \
            case 6:                                              \
                *(--(c)) = (uint8_t)(((l2) >> 8) & 0xff);  \
            case 5:                                              \
                *(--(c)) = (uint8_t)(((l2)) & 0xff);       \
            case 4:                                              \
                *(--(c)) = (uint8_t)(((l1) >> 24) & 0xff); \
            case 3:                                              \
                *(--(c)) = (uint8_t)(((l1) >> 16) & 0xff); \
            case 2:                                              \
                *(--(c)) = (uint8_t)(((l1) >> 8) & 0xff);  \
            case 1:                                              \
                *(--(c)) = (uint8_t)(((l1)) & 0xff);       \
        }                                                        \
    }

#define n2s(c, s) \
    ((s = (((unsigned int)(c[0])) << 8) | (((unsigned int)(c[1])))), c += 2)
#define s2n(s, c)                                \
    ((c[0] = (uint8_t)(((s) >> 8) & 0xff), \
      c[1] = (uint8_t)(((s)) & 0xff)),     \
     c += 2)

#define n2l3(c, l)                                                                                       \
    ((l = (((unsigned long)(c[0])) << 16) | (((unsigned long)(c[1])) << 8) | (((unsigned long)(c[2])))), \
     c += 3)

#define l2n3(l, c)                                \
    ((c[0] = (uint8_t)(((l) >> 16) & 0xff), \
      c[1] = (uint8_t)(((l) >> 8) & 0xff),  \
      c[2] = (uint8_t)(((l)) & 0xff)),      \
     c += 3)

/* LOCAL STUFF */

#define SSL_DECRYPT 0
#define SSL_ENCRYPT 1

/*
 * Define the Bitmasks for SSL_CIPHER.algorithms.
 * This bits are used packed as dense as possible. If new methods/ciphers
 * etc will be added, the bits a likely to change, so this information
 * is for internal library use only, even though SSL_CIPHER.algorithms
 * can be publicly accessed.
 * Use the according functions for cipher management instead.
 *
 * The bit mask handling in the selection and sorting scheme in
 * ssl_create_cipher_list() has only limited capabilities, reflecting
 * that the different entities within are mutually exclusive:
 * ONLY ONE BIT PER MASK CAN BE SET AT A TIME.
 */

/* Bits for algorithm_mkey (key exchange algorithm) */
/* RSA key exchange */
#define SSL_kRSA                0x00000001L
/* tmp DH key no DH cert */
#define SSL_kDHE                0x00000002L
/* ephemeral ECDH */
#define SSL_kECDHE              0x00000004L
/* GOST key exchange */
#define SSL_kGOST               0x00000008L

/* Bits for algorithm_auth (server authentication) */
/* RSA auth */
#define SSL_aRSA                0x00000001L
/* DSS auth */
#define SSL_aDSS                0x00000002L
/* no auth (i.e. use ADH or AECDH) */
#define SSL_aNULL               0x00000004L
/* ECDSA auth */
#define SSL_aECDSA              0x00000008L
/* GOST R 34.10-94 signature auth */
#define SSL_aGOST94             0x00000010L
/* GOST R 34.10-2001 signature auth */
#define SSL_aGOST01             0x00000020L

/* Bits for algorithm_enc (symmetric encryption) */
#define SSL_DES                     0x00000001L
#define SSL_3DES                    0x00000002L
#define SSL_RC4                     0x00000004L
#define SSL_IDEA                    0x00000008L
#define SSL_eNULL                   0x00000010L
#define SSL_AES128                  0x00000020L
#define SSL_AES256                  0x00000040L
#define SSL_CAMELLIA128             0x00000080L
#define SSL_CAMELLIA256             0x00000100L
#define SSL_eGOST2814789CNT         0x00000200L
#define SSL_AES128GCM               0x00000400L
#define SSL_AES256GCM               0x00000800L
#define SSL_CHACHA20POLY1305        0x00001000L
#define SSL_CHACHA20POLY1305_OLD    0x00002000L

#define SSL_AES (SSL_AES128 | SSL_AES256 | SSL_AES128GCM | SSL_AES256GCM)
#define SSL_CAMELLIA (SSL_CAMELLIA128 | SSL_CAMELLIA256)

/* Bits for algorithm_mac (symmetric authentication) */

#define SSL_MD5 0x00000001L
#define SSL_SHA1 0x00000002L
#define SSL_GOST94 0x00000004L
#define SSL_GOST89MAC 0x00000008L
#define SSL_SHA256 0x00000010L
#define SSL_SHA384 0x00000020L
/* Not a real MAC, just an indication it is part of cipher */
#define SSL_AEAD 0x00000040L

/* Bits for algorithm_ssl (protocol version) */
#define SSL_SSLV2 0x00000001L
#define SSL_SSLV3 0x00000002L
#define SSL_TLSV1 SSL_SSLV3 /* for now */
#define SSL_TLSV1_2 0x00000004L

/* Bits for algorithm2 (handshake digests and other extra flags) */

#define SSL_HANDSHAKE_MAC_MD5 0x10
#define SSL_HANDSHAKE_MAC_SHA 0x20
#define SSL_HANDSHAKE_MAC_GOST94 0x40
#define SSL_HANDSHAKE_MAC_SHA256 0x80
#define SSL_HANDSHAKE_MAC_SHA384 0x100
#define SSL_HANDSHAKE_MAC_DEFAULT \
    (SSL_HANDSHAKE_MAC_MD5 | SSL_HANDSHAKE_MAC_SHA)

/* When adding new digest in the ssl_ciph.c and increment SSM_MD_NUM_IDX
 * make sure to update this constant too */
#define SSL_MAX_DIGEST 6

#define SSL3_CK_ID 0x03000000
#define SSL3_CK_VALUE_MASK 0x0000ffff

#define TLS1_PRF_DGST_MASK (0xff << TLS1_PRF_DGST_SHIFT)

#define TLS1_PRF_DGST_SHIFT 10
#define TLS1_PRF_MD5 (SSL_HANDSHAKE_MAC_MD5 << TLS1_PRF_DGST_SHIFT)
#define TLS1_PRF_SHA1 (SSL_HANDSHAKE_MAC_SHA << TLS1_PRF_DGST_SHIFT)
#define TLS1_PRF_SHA256 (SSL_HANDSHAKE_MAC_SHA256 << TLS1_PRF_DGST_SHIFT)
#define TLS1_PRF_SHA384 (SSL_HANDSHAKE_MAC_SHA384 << TLS1_PRF_DGST_SHIFT)
#define TLS1_PRF_GOST94 (SSL_HANDSHAKE_MAC_GOST94 << TLS1_PRF_DGST_SHIFT)
#define TLS1_PRF (TLS1_PRF_MD5 | TLS1_PRF_SHA1)

/* Stream MAC for GOST ciphersuites from cryptopro draft
 * (currently this also goes into algorithm2) */
#define TLS1_STREAM_MAC 0x04

/*
 * SSL_CIPHER_ALGORITHM2_VARIABLE_NONCE_IN_RECORD is an algorithm2 flag that
 * indicates that the variable part of the nonce is included as a prefix of
 * the record (AES-GCM, for example, does this with an 8-byte variable nonce.)
 */
#define SSL_CIPHER_ALGORITHM2_VARIABLE_NONCE_IN_RECORD (1 << 22)

/*
 * SSL_CIPHER_ALGORITHM2_AEAD is an algorithm2 flag that indicates the cipher
 * is implemented via an EVP_AEAD.
 */
#define SSL_CIPHER_ALGORITHM2_AEAD (1 << 23)

/*
 * SSL_CIPHER_AEAD_FIXED_NONCE_LEN returns the number of bytes of fixed nonce
 * for an SSL_CIPHER with the SSL_CIPHER_ALGORITHM2_AEAD flag.
 */
#define SSL_CIPHER_AEAD_FIXED_NONCE_LEN(ssl_cipher) \
    (((ssl_cipher->algorithm2 >> 24) & 0xf) * 2)

/*
 * Cipher strength information.
 */
#define SSL_STRONG_MASK 0x000001fcL
#define SSL_STRONG_NONE 0x00000004L
#define SSL_LOW 0x00000020L
#define SSL_MEDIUM 0x00000040L
#define SSL_HIGH 0x00000080L

/*
 * The keylength (measured in RSA key bits, I guess)  for temporary keys.
 * Cipher argument is so that this can be variable in the future.
 */
#define SSL_C_PKEYLENGTH(c) 1024

/* Check if an SSL structure is using DTLS. */
#define SSL_IS_DTLS(s) (s->method->ssl3_enc->enc_flags & SSL_ENC_FLAG_DTLS)

/* See if we need explicit IV. */
#define SSL_USE_EXPLICIT_IV(s) \
    (s->method->ssl3_enc->enc_flags & SSL_ENC_FLAG_EXPLICIT_IV)

/* See if we use signature algorithms extension. */
#define SSL_USE_SIGALGS(s) \
    (s->method->ssl3_enc->enc_flags & SSL_ENC_FLAG_SIGALGS)

/* Allow TLS 1.2 ciphersuites: applies to DTLS 1.2 as well as TLS 1.2. */
#define SSL_USE_TLS1_2_CIPHERS(s) \
    (s->method->ssl3_enc->enc_flags & SSL_ENC_FLAG_TLS1_2_CIPHERS)

/* Mostly for SSLv3 */
#define SSL_PKEY_RSA_ENC 0
#define SSL_PKEY_RSA_SIGN 1
#define SSL_PKEY_DSA_SIGN 2
#define SSL_PKEY_DH_RSA 3
#define SSL_PKEY_DH_DSA 4
#define SSL_PKEY_ECC 5
#define SSL_PKEY_GOST94 6
#define SSL_PKEY_GOST01 7
#define SSL_PKEY_NUM 8

/* SSL_kRSA <- RSA_ENC | (RSA_TMP & RSA_SIGN) |
 *          <- (EXPORT & (RSA_ENC | RSA_TMP) & RSA_SIGN)
 * SSL_kDH  <- DH_ENC & (RSA_ENC | RSA_SIGN | DSA_SIGN)
 * SSL_kDHE <- RSA_ENC | RSA_SIGN | DSA_SIGN
 * SSL_aRSA <- RSA_ENC | RSA_SIGN
 * SSL_aDSS <- DSA_SIGN
 */

/*
#define CERT_INVALID 0
#define CERT_PUBLIC_KEY 1
#define CERT_PRIVATE_KEY 2
*/

/* From ECC-TLS draft, used in encoding the curve type in
 * ECParameters
 */
#define EXPLICIT_PRIME_CURVE_TYPE 1
#define EXPLICIT_CHAR2_CURVE_TYPE 2
#define NAMED_CURVE_TYPE 3

/* Values for valid_flags in CERT_PKEY structure */
/* Certificate inconsistent with session, key missing etc */
#define CERT_PKEY_INVALID 0x0
/* Certificate can be used with this sesstion */
#define CERT_PKEY_VALID 0x1
/* Certificate can also be used for signing */
#define CERT_PKEY_SIGN 0x2

typedef struct cert_pkey_st {
    X509 *x509;
    EVP_PKEY *privatekey;
    /* Digest to use when signing */
    const EVP_MD *digest;
    /* Chain for this certificate */
    STACK_OF(X509) *chain;
    /*
     * authz/authz_length contain authz data for this certificate. The data
     * is in wire format, specifically it's a series of records like:
     *   uint8_t authz_type;  // (RFC 5878, AuthzDataFormat)
     *   uint16_t length;
     *   uint8_t data[length];
     */
     uint8_t *authz;
     size_t authz_length;

    /*
     * Set if CERT_PKEY can be used with current SSL session: e.g.
     * appropriate curve, signature algorithms etc. If zero it can't be
     * used at all.
     */
    int valid_flags;
} CERT_PKEY;

typedef struct cert_st {
    /* Current active set */
    CERT_PKEY *key; /* ALWAYS points to an element of the pkeys array
                   * Probably it would make more sense to store
                   * an index, not a pointer. */

    /* The following masks are for the key and auth
     * algorithms that are supported by the certs below */
    int valid;
    unsigned long mask_k;
    unsigned long mask_a;

    DH *dh_tmp;
    DH *(*dh_tmp_cb)(SSL *ssl, int is_export, int keysize);
    int dh_tmp_auto;

    EC_KEY *ecdh_tmp;
    EC_KEY *(*ecdh_tmp_cb)(SSL *ssl, int is_export, int keysize);
    /* Select ECDH parameters automatically */
    int ecdh_tmp_auto;

    /* Flags related to certificates */
    unsigned int cert_flags;

    CERT_PKEY pkeys[SSL_PKEY_NUM];

    /*
     * Certificate types (received or sent) in certificate request
     * message. On receive this is only set if number of certificate
     * types exceeds SSL3_CT_NUMBER.
     */
    uint8_t *ctypes;
    size_t ctype_num;

    /*
     * signature algorithms peer reports: e.g. supported signature
     * algorithms extension for server or as part of a certificate
     * request for client.
     */
    uint8_t *peer_sigalgs;
    /* Size of above array */
    size_t peer_sigalgslen;
    /*
     * Suppported signature algorithms
     * When set on a client this is sent in the client hello as the 
     * supported signature algorithms extension. For servers
     * it represents the signature algorithms we are willing to use.
     */
    uint8_t *conf_sigalgs;
    /* Size of above array */
    size_t conf_sigalgslen;
    /*
     * Client authentication signature algorithms, if not set then
     * uses conf_sigalgs. On servers these will be the signature
     * algorithms sent to the client in a cerificate request for TLS 1.2.
     * On a client this represents the signature algortithms we are
     * willing to use for client authentication.
     */
    uint8_t *client_sigalgs;
    /* Size of above array */
    size_t client_sigalgslen;
    /*
     * Signature algorithms shared by client and server: cached because
     * these are used most often.
     */
    TLS_SIGALGS *shared_sigalgs;
    size_t shared_sigalgslen;

    /*
     * Certificate setup callback: if set is called whenever a
     * certificate may be required (client or server). the callback
     * can then examine any appropriate parameters and setup any
     * certificates required. This allows advanced applications
     * to select certificates on the fly: for example based on
     * supported signature algorithms or curves.
     */
    int (*cert_cb)(SSL *ssl, void *arg);
    void *cert_cb_arg;

    int references; /* >1 only if SSL_copy_session_id is used */
    CRYPTO_MUTEX *lock;
} CERT;

typedef struct sess_cert_st {
    STACK_OF(X509) *cert_chain; /* as received from peer */

    /* The 'peer_...' members are used only by clients. */
    int peer_cert_type;

    CERT_PKEY *peer_key; /* points to an element of peer_pkeys (never NULL!) */
    CERT_PKEY peer_pkeys[SSL_PKEY_NUM];
    /* Obviously we don't have the private keys of these,
   * so maybe we shouldn't even use the CERT_PKEY type here. */

    RSA *peer_rsa_tmp;
    DH *peer_dh_tmp;
    EC_KEY *peer_ecdh_tmp;

    int references; /* actually always 1 at the moment */
    CRYPTO_MUTEX *lock;
} SESS_CERT;

/* Structure containing decoded values of signature algorithms extension */
struct tls_sigalgs_st {
    /* NID of hash algorithm */
    int hash_nid;
    /* NID of signature algorithm */
    int sign_nid;
    /* Combined hash and signature NID */
    int signandhash_nid;
    /* Raw values used in extension */
    uint8_t rsign;
    uint8_t rhash;
};

/*#define SSL_DEBUG    */
/*#define RSA_DEBUG    */

/* This is for the SSLv3/TLSv1.0 differences in crypto/hash stuff
 * It is a bit of a mess of functions, but hell, think of it as
 * an opaque structure :-) */
typedef struct ssl3_enc_method {
    int (*enc)(SSL *, int);
    int (*mac)(SSL *, uint8_t *, int);
    int (*setup_key_block)(SSL *);
    int (*generate_master_secret)(SSL *, uint8_t *, uint8_t *, int);
    int (*change_cipher_state)(SSL *, int);
    int (*final_finish_mac)(SSL *, const char *, int, uint8_t *);
    int finish_mac_length;
    int (*cert_verify_mac)(SSL *, int, uint8_t *);
    const char *client_finished_label;
    int client_finished_label_len;
    const char *server_finished_label;
    int server_finished_label_len;
    int (*alert_value)(int);
    int (*export_keying_material)(SSL *, uint8_t *, size_t, const char *,
                                  size_t, const uint8_t *, size_t,
                                  int use_context);
    /* Flags indicating protocol version requirements. */
    unsigned int enc_flags;
    /* Handshake header length */
    unsigned int hhlen;
    /* Set the handshake header */
    void (*set_handshake_header)(SSL *s, int type, unsigned long len);
    /* Write out handshake message */
    int (*do_write)(SSL *s);
} SSL3_ENC_METHOD;

#define SSL_HM_HEADER_LENGTH(s) s->method->ssl3_enc->hhlen
#define ssl_handshake_start(s) \
    (((uint8_t *)s->init_buf->data) + s->method->ssl3_enc->hhlen)
#define ssl_set_handshake_header(s, htype, len) \
    s->method->ssl3_enc->set_handshake_header(s, htype, len)
#define ssl_do_write(s) s->method->ssl3_enc->do_write(s)

/*
 * Flag values for enc_flags.
 */

/* Uses explicit IV. */
#define SSL_ENC_FLAG_EXPLICIT_IV (1 << 0)

/* Uses signature algorithms extension. */
#define SSL_ENC_FLAG_SIGALGS (1 << 1)

/* Uses SHA256 default PRF. */
#define SSL_ENC_FLAG_SHA256_PRF (1 << 2)

/* Is DTLS. */
#define SSL_ENC_FLAG_DTLS (1 << 3)

/* Allow TLS 1.2 ciphersuites: applies to DTLS 1.2 as well as TLS 1.2. */
#define SSL_ENC_FLAG_TLS1_2_CIPHERS (1 << 4)

/*
 * ssl_aead_ctx_st contains information about an AEAD that is being used to
 * encrypt an SSL connection.
 */
struct ssl_aead_ctx_st {
    EVP_AEAD_CTX ctx;
    /*
   * fixed_nonce contains any bytes of the nonce that are fixed for all
   * records.
   */
    uint8_t fixed_nonce[12];
    uint8_t fixed_nonce_len;
    uint8_t variable_nonce_len;
    uint8_t xor_fixed_nonce;
    uint8_t tag_len;
    /*
   * variable_nonce_in_record is non-zero if the variable nonce
   * for a record is included as a prefix before the ciphertext.
   */
    char variable_nonce_in_record;
};

extern SSL3_ENC_METHOD ssl3_undef_enc_method;
extern SSL_CIPHER ssl3_ciphers[];

const char *ssl_version_string(int ver);

extern SSL3_ENC_METHOD DTLSv1_enc_data;
extern SSL3_ENC_METHOD TLSv1_enc_data;
extern SSL3_ENC_METHOD TLSv1_1_enc_data;
extern SSL3_ENC_METHOD TLSv1_2_enc_data;

void ssl_clear_cipher_ctx(SSL *s);
int ssl_clear_bad_session(SSL *s);
CERT *ssl_cert_new(void);
CERT *ssl_cert_dup(CERT *cert);
void ssl_cert_set_default_md(CERT *cert);
int ssl_cert_inst(CERT **o);
void ssl_cert_clear_certs(CERT *c);
void ssl_cert_free(CERT *c);
SESS_CERT *ssl_sess_cert_new(void);
void ssl_sess_cert_free(SESS_CERT *sc);
void SSL_CERT_up_ref(SESS_CERT *sc);
int ssl_get_new_session(SSL *s, int session);
int ssl_get_prev_session(SSL *s, uint8_t *session, int len,
                         const uint8_t *limit);
SSL_SESSION *ssl_session_dup(SSL_SESSION *src, int ticket);
int ssl_cipher_id_cmp(const SSL_CIPHER *a, const SSL_CIPHER *b);
DECLARE_OBJ_BSEARCH_GLOBAL_CMP_FN(SSL_CIPHER, SSL_CIPHER, ssl_cipher_id);
int ssl_cipher_ptr_id_cmp(const SSL_CIPHER *const *ap,
                          const SSL_CIPHER *const *bp);
STACK_OF(SSL_CIPHER) *ssl_bytes_to_cipher_list(SSL *s, const uint8_t *p,
                                               int num);
int ssl_cipher_list_to_bytes(SSL *s, STACK_OF(SSL_CIPHER) *sk,
                             uint8_t *p);
STACK_OF(SSL_CIPHER) *ssl_create_cipher_list(const SSL_METHOD *meth,
                                             STACK_OF(SSL_CIPHER) **pref,
                                             STACK_OF(SSL_CIPHER) **sorted,
                                             const char *rule_str);
void ssl_update_cache(SSL *s, int mode);
int ssl_cipher_get_evp(const SSL_SESSION *s, const EVP_CIPHER **enc,
                       const EVP_MD **md, int *mac_pkey_type,
                       int *mac_secret_size);
int ssl_cipher_get_evp_aead(const SSL_SESSION *s, const EVP_AEAD **aead);
int ssl_get_handshake_digest(int i, long *mask, const EVP_MD **md);
int ssl_cert_set0_chain(CERT *c, STACK_OF(X509) *chain);
int ssl_cert_set1_chain(CERT *c, STACK_OF(X509) *chain);
int ssl_cert_add0_chain_cert(CERT *c, X509 *x);
int ssl_cert_add1_chain_cert(CERT *c, X509 *x);
void ssl_cert_set_cert_cb(CERT *c, int (*cb)(SSL *ssl, void *arg), void *arg);

int ssl_verify_cert_chain(SSL *s, STACK_OF(X509) *sk);
int ssl_add_cert_chain(SSL *s, CERT_PKEY *cpk, unsigned long *l);
int ssl_undefined_function(SSL *s);
int ssl_undefined_void_function(void);
int ssl_undefined_const_function(const SSL *s);
CERT_PKEY *ssl_get_server_send_pkey(const SSL *s);
uint8_t *ssl_get_authz_data(const SSL *s, size_t *authz_length);
EVP_PKEY *ssl_get_sign_pkey(SSL *s, const SSL_CIPHER *c, const EVP_MD **pmd);
DH *ssl_get_auto_dh(SSL *s);
int ssl_cert_type(X509 *x, EVP_PKEY *pkey);
void ssl_set_cert_masks(CERT *c, const SSL_CIPHER *cipher);
STACK_OF(SSL_CIPHER) *ssl_get_ciphers_by_id(SSL *s);
int ssl_verify_alarm_type(long type);
void ssl_load_ciphers(void);

void tls1_init_finished_mac(SSL *s);
int ssl3_send_server_certificate(SSL *s);
int ssl3_send_newsession_ticket(SSL *s);
int ssl3_send_cert_status(SSL *s);
int ssl3_get_finished(SSL *s, int state_a, int state_b);
int ssl3_send_change_cipher_spec(SSL *s, int state_a, int state_b);
void ssl3_cleanup_key_block(SSL *s);
int ssl3_do_write(SSL *s, int type);
int ssl3_send_alert(SSL *s, int level, int desc);
int ssl3_get_req_cert_type(SSL *s, uint8_t *p);
long ssl3_get_message(SSL *s, int st1, int stn, int mt, long max, int *ok);
int ssl3_send_finished(SSL *s, int a, int b, const char *sender, int slen);
int ssl3_num_ciphers(void);
const SSL_CIPHER *ssl3_get_cipher(unsigned int u);
const SSL_CIPHER *ssl3_get_cipher_by_id(unsigned int id);
uint16_t ssl3_cipher_get_value(const SSL_CIPHER *cipher);
int ssl3_renegotiate(SSL *ssl);

int ssl3_renegotiate_check(SSL *ssl);

int ssl3_dispatch_alert(SSL *s);
int ssl3_read_bytes(SSL *s, int type, uint8_t *buf, int len, int peek);
int ssl3_write_bytes(SSL *s, int type, const void *buf, int len);
void tls1_finish_mac(SSL *s, const uint8_t *buf, int len);
void tls1_free_digest_list(SSL *s);
unsigned long ssl3_output_cert_chain(SSL *s, CERT_PKEY *cpk);
SSL_CIPHER *ssl3_choose_cipher(SSL *ssl, STACK_OF(SSL_CIPHER) *clnt,
                               STACK_OF(SSL_CIPHER) *srvr);
int ssl3_setup_buffers(SSL *s);
int ssl3_setup_read_buffer(SSL *s);
int ssl3_setup_write_buffer(SSL *s);
int ssl3_release_read_buffer(SSL *s);
int ssl3_release_write_buffer(SSL *s);
int tls1_digest_cached_records(SSL *s);
int ssl3_new(SSL *s);
void ssl3_free(SSL *s);
int ssl3_accept(SSL *s);
int ssl3_connect(SSL *s);
int ssl3_read(SSL *s, void *buf, int len);
int ssl3_peek(SSL *s, void *buf, int len);
int ssl3_write(SSL *s, const void *buf, int len);
int ssl3_shutdown(SSL *s);
void ssl3_clear(SSL *s);
long ssl3_ctrl(SSL *s, int cmd, long larg, void *parg);
long ssl3_ctx_ctrl(SSL_CTX *s, int cmd, long larg, void *parg);
long ssl3_callback_ctrl(SSL *s, int cmd, void (*fp)(void));
long ssl3_ctx_callback_ctrl(SSL_CTX *s, int cmd, void (*fp)(void));
int ssl3_pending(const SSL *s);

void tls1_record_sequence_increment(uint8_t *seq);
int ssl3_do_change_cipher_spec(SSL *ssl);

void ssl3_set_handshake_header(SSL *s, int htype, unsigned long len);
int ssl3_handshake_write(SSL *s);

int ssl23_read(SSL *s, void *buf, int len);
int ssl23_peek(SSL *s, void *buf, int len);
int ssl23_write(SSL *s, const void *buf, int len);
long ssl23_default_timeout(void);

long tls1_default_timeout(void);
int dtls1_do_write(SSL *s, int type);
int ssl3_read_n(SSL *s, int n, int max, int extend);
int dtls1_read_bytes(SSL *s, int type, uint8_t *buf, int len, int peek);
int ssl3_write_pending(SSL *s, int type, const uint8_t *buf,
                       unsigned int len);
uint8_t *dtls1_set_message_header(SSL *s, uint8_t *p,
                                        uint8_t mt, unsigned long len,
                                        unsigned long frag_off,
                                        unsigned long frag_len);

int dtls1_write_app_data_bytes(SSL *s, int type, const void *buf, int len);
int dtls1_write_bytes(SSL *s, int type, const void *buf, int len);

int dtls1_send_change_cipher_spec(SSL *s, int a, int b);
int dtls1_send_finished(SSL *s, int a, int b, const char *sender, int slen);
int dtls1_read_failed(SSL *s, int code);
int dtls1_buffer_message(SSL *s, int ccs);
int dtls1_retransmit_message(SSL *s, unsigned short seq, unsigned long frag_off,
                             int *found);
int dtls1_get_queue_priority(unsigned short seq, int is_ccs);
int dtls1_retransmit_buffered_messages(SSL *s);
void dtls1_clear_record_buffer(SSL *s);
int dtls1_get_message_header(const uint8_t *data,
                             struct hm_header_st *msg_hdr);
void dtls1_get_ccs_header(uint8_t *data, struct ccs_header_st *ccs_hdr);
void dtls1_reset_seq_numbers(SSL *s, int rw);
void dtls1_build_sequence_number(uint8_t *dst, uint8_t *seq,
                                 unsigned short epoch);
long dtls1_default_timeout(void);
struct timeval *dtls1_get_timeout(SSL *s, struct timeval *timeleft);
int dtls1_check_timeout_num(SSL *s);
int dtls1_handle_timeout(SSL *s);
const SSL_CIPHER *dtls1_get_cipher(unsigned int u);
void dtls1_start_timer(SSL *s);
void dtls1_stop_timer(SSL *s);
int dtls1_is_timer_expired(SSL *s);
void dtls1_double_timeout(SSL *s);
int dtls1_send_newsession_ticket(SSL *s);
unsigned int dtls1_min_mtu(void);
void dtls1_hm_fragment_free(hm_fragment *frag);

/* some client-only functions */
int ssl3_client_hello(SSL *s);
int ssl3_get_server_hello(SSL *s);
int ssl3_get_certificate_request(SSL *s);
int ssl3_get_new_session_ticket(SSL *s);
int ssl3_get_cert_status(SSL *s);
int ssl3_get_server_done(SSL *s);
int ssl3_send_client_verify(SSL *s);
int ssl3_send_client_certificate(SSL *s);
int ssl_do_client_cert_cb(SSL *s, X509 **px509, EVP_PKEY **ppkey);
int ssl3_send_client_key_exchange(SSL *s);
int ssl3_get_key_exchange(SSL *s);
int ssl3_get_server_certificate(SSL *s);
int ssl3_check_cert_and_algorithm(SSL *s);
int ssl3_check_finished(SSL *s);
#ifndef OPENSSL_NO_NEXTPROTONEG
int ssl3_send_next_proto(SSL *s);
#endif

int dtls1_client_hello(SSL *s);

/* some server-only functions */
int ssl3_get_client_hello(SSL *s);
int ssl3_send_server_hello(SSL *s);
int ssl3_send_hello_request(SSL *s);
int ssl3_send_server_key_exchange(SSL *s);
int ssl3_send_certificate_request(SSL *s);
int ssl3_send_server_done(SSL *s);
int ssl3_get_client_certificate(SSL *s);
int ssl3_get_client_key_exchange(SSL *s);
int ssl3_get_cert_verify(SSL *s);
#ifndef OPENSSL_NO_NEXTPROTONEG
int ssl3_get_next_proto(SSL *s);
#endif

int ssl23_accept(SSL *s);
int ssl23_connect(SSL *s);
int ssl23_read_bytes(SSL *s, int n);
int ssl23_write_bytes(SSL *s);

int tls1_new(SSL *s);
void tls1_free(SSL *s);
void tls1_clear(SSL *s);
long tls1_ctrl(SSL *s, int cmd, long larg, void *parg);
long tls1_callback_ctrl(SSL *s, int cmd, void (*fp)(void));

int dtls1_new(SSL *s);
int dtls1_accept(SSL *s);
int dtls1_connect(SSL *s);
void dtls1_free(SSL *s);
void dtls1_clear(SSL *s);
long dtls1_ctrl(SSL *s, int cmd, long larg, void *parg);
int dtls1_shutdown(SSL *s);

long dtls1_get_message(SSL *s, int st1, int stn, int mt, long max, int *ok);
int dtls1_get_record(SSL *s);
int do_dtls1_write(SSL *s, int type, const uint8_t *buf,
                   unsigned int len);
int dtls1_dispatch_alert(SSL *s);
int dtls1_enc(SSL *s, int snd);

int ssl_init_wbio_buffer(SSL *s, int push);
void ssl_free_wbio_buffer(SSL *s);

int tls1_change_cipher_state(SSL *s, int which);
int tls1_setup_key_block(SSL *s);
int tls1_enc(SSL *s, int snd);
int tls1_final_finish_mac(SSL *s, const char *str, int slen, uint8_t *p);
int tls1_cert_verify_mac(SSL *s, int md_nid, uint8_t *p);
int tls1_mac(SSL *ssl, uint8_t *md, int snd);
int tls1_generate_master_secret(SSL *s, uint8_t *out, uint8_t *p,
                                int len);
int tls1_export_keying_material(SSL *s, uint8_t *out, size_t olen,
                                const char *label, size_t llen,
                                const uint8_t *p, size_t plen,
                                int use_context);
int tls1_alert_code(int code);
int ssl_ok(SSL *s);

int ssl_check_srvr_ecc_cert_and_alg(X509 *x, SSL *s);

SSL_COMP *ssl3_comp_find(STACK_OF(SSL_COMP) *sk, int n);

int tls1_ec_curve_id2nid(uint16_t curve_id);
uint16_t tls1_ec_nid2curve_id(int nid);
int tls1_shared_curve(SSL *s, int nmatch);
int tls1_set_curves(uint16_t **pext, size_t *pextlen, int *curves,
                    size_t ncurves);
int tls1_set_curves_list(uint16_t **pext, size_t *pextlen, const char *str);
int tls1_check_curve(SSL *s, const uint8_t *p, size_t len);
int tls1_get_shared_curve(SSL *s);

uint8_t *ssl_add_clienthello_tlsext(SSL *s, uint8_t *p,
                                          uint8_t *limit);

uint8_t *ssl_add_serverhello_tlsext(SSL *s, uint8_t *p,
                                          uint8_t *limit);

int ssl_parse_clienthello_tlsext(SSL *s, uint8_t **data, uint8_t *limit);
int ssl_parse_serverhello_tlsext(SSL *s, uint8_t **data, uint8_t *d, int n);
int ssl_prepare_clienthello_tlsext(SSL *s);
int ssl_prepare_serverhello_tlsext(SSL *s);
int ssl_check_clienthello_tlsext_early(SSL *s);
int ssl_check_clienthello_tlsext_late(SSL *s);

/* server only */
int tls1_send_server_supplemental_data(SSL *s);
/* client only */
int tls1_get_server_supplemental_data(SSL *s);

int tls1_process_ticket(SSL *s, const uint8_t *session, int session_len,
                        const uint8_t *limit, SSL_SESSION **ret);

int tls12_get_sigandhash(uint8_t *p, const EVP_PKEY *pk,
                         const EVP_MD *md);
int tls12_get_sigid(const EVP_PKEY *pk);
const EVP_MD *tls12_get_hash(uint8_t hash_alg);

int tls1_set_sigalgs_list(CERT *c, const char *str, int client);
int tls1_set_sigalgs(CERT *c, const int *salg, size_t salglen, int client);
int tls1_check_chain(SSL *s, X509 *x, EVP_PKEY *pk, STACK_OF(X509) *chain,
                     int idx);
void tls1_set_cert_validity(SSL *s);

void ssl_clear_hash_ctx(EVP_MD_CTX **hash);
int ssl_add_serverhello_renegotiate_ext(SSL *s, uint8_t *p, int *len,
                                        int maxlen);
int ssl_parse_serverhello_renegotiate_ext(SSL *s, const uint8_t *d, int len,
                                          int *al);
int ssl_add_clienthello_renegotiate_ext(SSL *s, uint8_t *p, int *len,
                                        int maxlen);
int ssl_parse_clienthello_renegotiate_ext(SSL *s, const uint8_t *d, int len,
                                          int *al);
long ssl_get_algorithm2(SSL *s);
int tls1_process_sigalgs(SSL *s, const uint8_t *data, int dsize);
size_t tls12_get_sig_algs(SSL *s, uint8_t *p);

int tls1_check_ec_tmp_key(SSL *s);

int ssl_add_clienthello_use_srtp_ext(SSL *s, uint8_t *p, int *len,
                                     int maxlen);
int ssl_parse_clienthello_use_srtp_ext(SSL *s, const uint8_t *d, int len,
                                       int *al);
int ssl_add_serverhello_use_srtp_ext(SSL *s, uint8_t *p, int *len,
                                     int maxlen);
int ssl_parse_serverhello_use_srtp_ext(SSL *s, const uint8_t *d, int len,
                                       int *al);
int ssl_handshake_hash(SSL *s, uint8_t *out, int outlen);

/* s3_cbc.c */
void ssl3_cbc_copy_mac(uint8_t *out, const SSL3_RECORD *rec,
                       unsigned md_size, unsigned orig_len);
int tls1_cbc_remove_padding(const SSL *s, SSL3_RECORD *rec, unsigned block_size,
                            unsigned mac_size);
char ssl3_cbc_record_digest_supported(const EVP_MD_CTX *ctx);
void ssl3_cbc_digest_record(const EVP_MD_CTX *ctx, uint8_t *md_out,
                            size_t *md_out_size, const uint8_t header[13],
                            const uint8_t *data,
                            size_t data_plus_mac_size,
                            size_t data_plus_mac_plus_padding_size,
                            const uint8_t *mac_secret,
                            unsigned mac_secret_length, char is_sslv3);

#endif
