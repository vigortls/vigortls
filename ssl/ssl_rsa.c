/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdcompat.h>
#include <openssl/bio.h>
#include <openssl/objects.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/pem.h>

#include "ssl_locl.h"

static int ssl_set_cert(CERT *c, X509 *x509);
static int ssl_set_pkey(CERT *c, EVP_PKEY *pkey);

int SSL_use_certificate(SSL *ssl, X509 *x)
{
    if (x == NULL) {
        SSLerr(SSL_F_SSL_USE_CERTIFICATE, ERR_R_PASSED_NULL_PARAMETER);
        return (0);
    }
    if (!ssl_cert_inst(&ssl->cert)) {
        SSLerr(SSL_F_SSL_USE_CERTIFICATE, ERR_R_MALLOC_FAILURE);
        return (0);
    }
    return (ssl_set_cert(ssl->cert, x));
}

int SSL_use_certificate_file(SSL *ssl, const char *file, int type)
{
    int j;
    BIO *in;
    int ret = 0;
    X509 *x = NULL;

    in = BIO_new(BIO_s_file_internal());
    if (in == NULL) {
        SSLerr(SSL_F_SSL_USE_CERTIFICATE_FILE, ERR_R_BUF_LIB);
        goto end;
    }

    if (BIO_read_filename(in, file) <= 0) {
        SSLerr(SSL_F_SSL_USE_CERTIFICATE_FILE, ERR_R_SYS_LIB);
        goto end;
    }
    if (type == SSL_FILETYPE_ASN1) {
        j = ERR_R_ASN1_LIB;
        x = d2i_X509_bio(in, NULL);
    } else if (type == SSL_FILETYPE_PEM) {
        j = ERR_R_PEM_LIB;
        x = PEM_read_bio_X509(in, NULL, ssl->ctx->default_passwd_callback,
                              ssl->ctx->default_passwd_callback_userdata);
    } else {
        SSLerr(SSL_F_SSL_USE_CERTIFICATE_FILE, SSL_R_BAD_SSL_FILETYPE);
        goto end;
    }

    if (x == NULL) {
        SSLerr(SSL_F_SSL_USE_CERTIFICATE_FILE, j);
        goto end;
    }

    ret = SSL_use_certificate(ssl, x);
end:
    X509_free(x);
    BIO_free(in);
    return (ret);
}

int SSL_use_certificate_ASN1(SSL *ssl, const uint8_t *d, int len)
{
    X509 *x;
    int ret;

    x = d2i_X509(NULL, &d, (long)len);
    if (x == NULL) {
        SSLerr(SSL_F_SSL_USE_CERTIFICATE_ASN1, ERR_R_ASN1_LIB);
        return (0);
    }

    ret = SSL_use_certificate(ssl, x);
    X509_free(x);
    return (ret);
}

int SSL_use_RSAPrivateKey(SSL *ssl, RSA *rsa)
{
    EVP_PKEY *pkey;
    int ret;

    if (rsa == NULL) {
        SSLerr(SSL_F_SSL_USE_RSAPRIVATEKEY, ERR_R_PASSED_NULL_PARAMETER);
        return (0);
    }
    if (!ssl_cert_inst(&ssl->cert)) {
        SSLerr(SSL_F_SSL_USE_RSAPRIVATEKEY, ERR_R_MALLOC_FAILURE);
        return (0);
    }
    if ((pkey = EVP_PKEY_new()) == NULL) {
        SSLerr(SSL_F_SSL_USE_RSAPRIVATEKEY, ERR_R_EVP_LIB);
        return (0);
    }

    RSA_up_ref(rsa);
    EVP_PKEY_assign_RSA(pkey, rsa);

    ret = ssl_set_pkey(ssl->cert, pkey);
    EVP_PKEY_free(pkey);
    return (ret);
}

static int ssl_set_pkey(CERT *c, EVP_PKEY *pkey)
{
    int i;

    i = ssl_cert_type(NULL, pkey);
    if (i < 0) {
        SSLerr(SSL_F_SSL_SET_PKEY, SSL_R_UNKNOWN_CERTIFICATE_TYPE);
        return (0);
    }

    if (c->pkeys[i].x509 != NULL) {
        EVP_PKEY *pktmp;
        pktmp = X509_get_pubkey(c->pkeys[i].x509);
        EVP_PKEY_copy_parameters(pktmp, pkey);
        EVP_PKEY_free(pktmp);
        ERR_clear_error();

        /*
         * Don't check the public/private key, this is mostly
         * for smart cards.
         */
        if ((pkey->type == EVP_PKEY_RSA) && (RSA_flags(pkey->pkey.rsa) & RSA_METHOD_FLAG_NO_CHECK))
            ;
        else if (!X509_check_private_key(c->pkeys[i].x509, pkey)) {
            X509_free(c->pkeys[i].x509);
            c->pkeys[i].x509 = NULL;
            return 0;
        }
    }

    EVP_PKEY_free(c->pkeys[i].privatekey);
    EVP_PKEY_up_ref(pkey);
    c->pkeys[i].privatekey = pkey;
    c->key = &(c->pkeys[i]);

    c->valid = 0;
    return (1);
}

int SSL_use_RSAPrivateKey_file(SSL *ssl, const char *file, int type)
{
    int j, ret = 0;
    BIO *in;
    RSA *rsa = NULL;

    in = BIO_new(BIO_s_file_internal());
    if (in == NULL) {
        SSLerr(SSL_F_SSL_USE_RSAPRIVATEKEY_FILE, ERR_R_BUF_LIB);
        goto end;
    }

    if (BIO_read_filename(in, file) <= 0) {
        SSLerr(SSL_F_SSL_USE_RSAPRIVATEKEY_FILE, ERR_R_SYS_LIB);
        goto end;
    }
    if (type == SSL_FILETYPE_ASN1) {
        j = ERR_R_ASN1_LIB;
        rsa = d2i_RSAPrivateKey_bio(in, NULL);
    } else if (type == SSL_FILETYPE_PEM) {
        j = ERR_R_PEM_LIB;
        rsa = PEM_read_bio_RSAPrivateKey(in, NULL, ssl->ctx->default_passwd_callback,
                                         ssl->ctx->default_passwd_callback_userdata);
    } else {
        SSLerr(SSL_F_SSL_USE_RSAPRIVATEKEY_FILE, SSL_R_BAD_SSL_FILETYPE);
        goto end;
    }
    if (rsa == NULL) {
        SSLerr(SSL_F_SSL_USE_RSAPRIVATEKEY_FILE, j);
        goto end;
    }
    ret = SSL_use_RSAPrivateKey(ssl, rsa);
    RSA_free(rsa);
end:
    BIO_free(in);
    return (ret);
}

int SSL_use_RSAPrivateKey_ASN1(SSL *ssl, uint8_t *d, long len)
{
    int ret;
    const uint8_t *p;
    RSA *rsa;

    p = d;
    if ((rsa = d2i_RSAPrivateKey(NULL, &p, (long)len)) == NULL) {
        SSLerr(SSL_F_SSL_USE_RSAPRIVATEKEY_ASN1, ERR_R_ASN1_LIB);
        return (0);
    }

    ret = SSL_use_RSAPrivateKey(ssl, rsa);
    RSA_free(rsa);
    return (ret);
}

int SSL_use_PrivateKey(SSL *ssl, EVP_PKEY *pkey)
{
    int ret;

    if (pkey == NULL) {
        SSLerr(SSL_F_SSL_USE_PRIVATEKEY, ERR_R_PASSED_NULL_PARAMETER);
        return (0);
    }
    if (!ssl_cert_inst(&ssl->cert)) {
        SSLerr(SSL_F_SSL_USE_PRIVATEKEY, ERR_R_MALLOC_FAILURE);
        return (0);
    }
    ret = ssl_set_pkey(ssl->cert, pkey);
    return (ret);
}

int SSL_use_PrivateKey_file(SSL *ssl, const char *file, int type)
{
    int j, ret = 0;
    BIO *in;
    EVP_PKEY *pkey = NULL;

    in = BIO_new(BIO_s_file_internal());
    if (in == NULL) {
        SSLerr(SSL_F_SSL_USE_PRIVATEKEY_FILE, ERR_R_BUF_LIB);
        goto end;
    }

    if (BIO_read_filename(in, file) <= 0) {
        SSLerr(SSL_F_SSL_USE_PRIVATEKEY_FILE, ERR_R_SYS_LIB);
        goto end;
    }
    if (type == SSL_FILETYPE_PEM) {
        j = ERR_R_PEM_LIB;
        pkey = PEM_read_bio_PrivateKey(in, NULL, ssl->ctx->default_passwd_callback,
                                       ssl->ctx->default_passwd_callback_userdata);
    } else if (type == SSL_FILETYPE_ASN1) {
        j = ERR_R_ASN1_LIB;
        pkey = d2i_PrivateKey_bio(in, NULL);
    } else {
        SSLerr(SSL_F_SSL_USE_PRIVATEKEY_FILE, SSL_R_BAD_SSL_FILETYPE);
        goto end;
    }
    if (pkey == NULL) {
        SSLerr(SSL_F_SSL_USE_PRIVATEKEY_FILE, j);
        goto end;
    }
    ret = SSL_use_PrivateKey(ssl, pkey);
    EVP_PKEY_free(pkey);
end:
    BIO_free(in);
    return (ret);
}

int SSL_use_PrivateKey_ASN1(int type, SSL *ssl, const uint8_t *d,
                            long len)
{
    int ret;
    const uint8_t *p;
    EVP_PKEY *pkey;

    p = d;
    if ((pkey = d2i_PrivateKey(type, NULL, &p, (long)len)) == NULL) {
        SSLerr(SSL_F_SSL_USE_PRIVATEKEY_ASN1, ERR_R_ASN1_LIB);
        return (0);
    }

    ret = SSL_use_PrivateKey(ssl, pkey);
    EVP_PKEY_free(pkey);
    return (ret);
}

int SSL_CTX_use_certificate(SSL_CTX *ctx, X509 *x)
{
    if (x == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE, ERR_R_PASSED_NULL_PARAMETER);
        return (0);
    }
    if (!ssl_cert_inst(&ctx->cert)) {
        SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE, ERR_R_MALLOC_FAILURE);
        return (0);
    }
    return (ssl_set_cert(ctx->cert, x));
}

static int ssl_set_cert(CERT *c, X509 *x)
{
    EVP_PKEY *pkey;
    int i;

    pkey = X509_get_pubkey(x);
    if (pkey == NULL) {
        SSLerr(SSL_F_SSL_SET_CERT, SSL_R_X509_LIB);
        return (0);
    }

    i = ssl_cert_type(x, pkey);
    if (i < 0) {
        SSLerr(SSL_F_SSL_SET_CERT, SSL_R_UNKNOWN_CERTIFICATE_TYPE);
        EVP_PKEY_free(pkey);
        return (0);
    }

    if (c->pkeys[i].privatekey != NULL) {
        EVP_PKEY_copy_parameters(pkey, c->pkeys[i].privatekey);
        ERR_clear_error();

        /*
         * Don't check the public/private key, this is mostly
         * for smart cards.
         */
        if ((c->pkeys[i].privatekey->type == EVP_PKEY_RSA) &&
            (RSA_flags(c->pkeys[i].privatekey->pkey.rsa) & RSA_METHOD_FLAG_NO_CHECK))
            ;
        else if (!X509_check_private_key(x, c->pkeys[i].privatekey)) {
            /*
             * don't fail for a cert/key mismatch, just free
             * current private key (when switching to a different
             * cert & key, first this function should be used,
             * then ssl_set_pkey
             */
            EVP_PKEY_free(c->pkeys[i].privatekey);
            c->pkeys[i].privatekey = NULL;
            /* clear error queue */
            ERR_clear_error();
        }
    }

    EVP_PKEY_free(pkey);
    X509_free(c->pkeys[i].x509);
    X509_up_ref(x);
    c->pkeys[i].x509 = x;
    c->key = &(c->pkeys[i]);

    c->valid = 0;

    return (1);
}

int SSL_CTX_use_certificate_file(SSL_CTX *ctx, const char *file, int type)
{
    int j;
    BIO *in;
    int ret = 0;
    X509 *x = NULL;

    in = BIO_new(BIO_s_file_internal());
    if (in == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE_FILE, ERR_R_BUF_LIB);
        goto end;
    }

    if (BIO_read_filename(in, file) <= 0) {
        SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE_FILE, ERR_R_SYS_LIB);
        goto end;
    }
    if (type == SSL_FILETYPE_ASN1) {
        j = ERR_R_ASN1_LIB;
        x = d2i_X509_bio(in, NULL);
    } else if (type == SSL_FILETYPE_PEM) {
        j = ERR_R_PEM_LIB;
        x = PEM_read_bio_X509(in, NULL, ctx->default_passwd_callback,
                              ctx->default_passwd_callback_userdata);
    } else {
        SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE_FILE, SSL_R_BAD_SSL_FILETYPE);
        goto end;
    }

    if (x == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE_FILE, j);
        goto end;
    }

    ret = SSL_CTX_use_certificate(ctx, x);
end:
    X509_free(x);
    BIO_free(in);
    return (ret);
}

int SSL_CTX_use_certificate_ASN1(SSL_CTX *ctx, int len,
                                 const uint8_t *d)
{
    X509 *x;
    int ret;

    x = d2i_X509(NULL, &d, (long)len);
    if (x == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE_ASN1, ERR_R_ASN1_LIB);
        return (0);
    }

    ret = SSL_CTX_use_certificate(ctx, x);
    X509_free(x);
    return (ret);
}

int SSL_CTX_use_RSAPrivateKey(SSL_CTX *ctx, RSA *rsa)
{
    int ret;
    EVP_PKEY *pkey;

    if (rsa == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY, ERR_R_PASSED_NULL_PARAMETER);
        return (0);
    }
    if (!ssl_cert_inst(&ctx->cert)) {
        SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY, ERR_R_MALLOC_FAILURE);
        return (0);
    }
    if ((pkey = EVP_PKEY_new()) == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY, ERR_R_EVP_LIB);
        return (0);
    }

    RSA_up_ref(rsa);
    EVP_PKEY_assign_RSA(pkey, rsa);

    ret = ssl_set_pkey(ctx->cert, pkey);
    EVP_PKEY_free(pkey);
    return (ret);
}

int SSL_CTX_use_RSAPrivateKey_file(SSL_CTX *ctx, const char *file, int type)
{
    int j, ret = 0;
    BIO *in;
    RSA *rsa = NULL;

    in = BIO_new(BIO_s_file_internal());
    if (in == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY_FILE, ERR_R_BUF_LIB);
        goto end;
    }

    if (BIO_read_filename(in, file) <= 0) {
        SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY_FILE, ERR_R_SYS_LIB);
        goto end;
    }
    if (type == SSL_FILETYPE_ASN1) {
        j = ERR_R_ASN1_LIB;
        rsa = d2i_RSAPrivateKey_bio(in, NULL);
    } else if (type == SSL_FILETYPE_PEM) {
        j = ERR_R_PEM_LIB;
        rsa = PEM_read_bio_RSAPrivateKey(in, NULL, ctx->default_passwd_callback,
                                         ctx->default_passwd_callback_userdata);
    } else {
        SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY_FILE, SSL_R_BAD_SSL_FILETYPE);
        goto end;
    }
    if (rsa == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY_FILE, j);
        goto end;
    }
    ret = SSL_CTX_use_RSAPrivateKey(ctx, rsa);
    RSA_free(rsa);
end:
    BIO_free(in);
    return (ret);
}

int SSL_CTX_use_RSAPrivateKey_ASN1(SSL_CTX *ctx, const uint8_t *d,
                                   long len)
{
    int ret;
    const uint8_t *p;
    RSA *rsa;

    p = d;
    if ((rsa = d2i_RSAPrivateKey(NULL, &p, (long)len)) == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY_ASN1, ERR_R_ASN1_LIB);
        return (0);
    }

    ret = SSL_CTX_use_RSAPrivateKey(ctx, rsa);
    RSA_free(rsa);
    return (ret);
}

int SSL_CTX_use_PrivateKey(SSL_CTX *ctx, EVP_PKEY *pkey)
{
    if (pkey == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_PRIVATEKEY, ERR_R_PASSED_NULL_PARAMETER);
        return (0);
    }
    if (!ssl_cert_inst(&ctx->cert)) {
        SSLerr(SSL_F_SSL_CTX_USE_PRIVATEKEY, ERR_R_MALLOC_FAILURE);
        return (0);
    }
    return (ssl_set_pkey(ctx->cert, pkey));
}

int SSL_CTX_use_PrivateKey_file(SSL_CTX *ctx, const char *file, int type)
{
    int j, ret = 0;
    BIO *in;
    EVP_PKEY *pkey = NULL;

    in = BIO_new(BIO_s_file_internal());
    if (in == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_PRIVATEKEY_FILE, ERR_R_BUF_LIB);
        goto end;
    }

    if (BIO_read_filename(in, file) <= 0) {
        SSLerr(SSL_F_SSL_CTX_USE_PRIVATEKEY_FILE, ERR_R_SYS_LIB);
        goto end;
    }
    if (type == SSL_FILETYPE_PEM) {
        j = ERR_R_PEM_LIB;
        pkey = PEM_read_bio_PrivateKey(in, NULL, ctx->default_passwd_callback,
                                       ctx->default_passwd_callback_userdata);
    } else if (type == SSL_FILETYPE_ASN1) {
        j = ERR_R_ASN1_LIB;
        pkey = d2i_PrivateKey_bio(in, NULL);
    } else {
        SSLerr(SSL_F_SSL_CTX_USE_PRIVATEKEY_FILE, SSL_R_BAD_SSL_FILETYPE);
        goto end;
    }
    if (pkey == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_PRIVATEKEY_FILE, j);
        goto end;
    }
    ret = SSL_CTX_use_PrivateKey(ctx, pkey);
    EVP_PKEY_free(pkey);
end:
    BIO_free(in);
    return (ret);
}

int SSL_CTX_use_PrivateKey_ASN1(int type, SSL_CTX *ctx, const uint8_t *d,
                                long len)
{
    int ret;
    const uint8_t *p;
    EVP_PKEY *pkey;

    p = d;
    if ((pkey = d2i_PrivateKey(type, NULL, &p, (long)len)) == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_PRIVATEKEY_ASN1, ERR_R_ASN1_LIB);
        return (0);
    }

    ret = SSL_CTX_use_PrivateKey(ctx, pkey);
    EVP_PKEY_free(pkey);
    return (ret);
}

/*
 * Read a file that contains our certificate in "PEM" format,
 * possibly followed by a sequence of CA certificates that should be
 * sent to the peer in the Certificate message.
 */
int SSL_CTX_use_certificate_chain_file(SSL_CTX *ctx, const char *file)
{
    BIO *in;
    int ret = 0;
    X509 *x = NULL;

    ERR_clear_error(); /* clear error stack for SSL_CTX_use_certificate() */

    in = BIO_new(BIO_s_file_internal());
    if (in == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE_CHAIN_FILE, ERR_R_BUF_LIB);
        goto end;
    }

    if (BIO_read_filename(in, file) <= 0) {
        SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE_CHAIN_FILE, ERR_R_SYS_LIB);
        goto end;
    }

    x = PEM_read_bio_X509_AUX(in, NULL, ctx->default_passwd_callback,
                              ctx->default_passwd_callback_userdata);
    if (x == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE_CHAIN_FILE, ERR_R_PEM_LIB);
        goto end;
    }

    ret = SSL_CTX_use_certificate(ctx, x);

    if (ERR_peek_error() != 0)
        ret = 0;
    /* Key/certificate mismatch doesn't imply ret==0 ... */
    if (ret) {
        /*
         * If we could set up our certificate, now proceed to
         * the CA certificates.
         */
        X509 *ca;
        int r;
        unsigned long err;

        SSL_CTX_clear_chain_certs(ctx);

        while ((ca = PEM_read_bio_X509(in, NULL, ctx->default_passwd_callback,
                                       ctx->default_passwd_callback_userdata)) != NULL) {
            r = SSL_CTX_add0_chain_cert(ctx, ca);
            if (!r) {
                X509_free(ca);
                ret = 0;
                goto end;
            }
            /*
             * Note that we must not free r if it was successfully
             * added to the chain (while we must free the main
             * certificate, since its reference count is increased
             * by SSL_CTX_use_certificate).
             */
        }

        /* When the while loop ends, it's usually just EOF. */
        err = ERR_peek_last_error();
        if (ERR_GET_LIB(err) == ERR_LIB_PEM && ERR_GET_REASON(err) == PEM_R_NO_START_LINE)
            ERR_clear_error();
        else
            ret = 0; /* some real error */
    }

end:
    X509_free(x);
    BIO_free(in);
    return (ret);
}

static int serverinfo_find_extension(const uint8_t *serverinfo,
                                     size_t serverinfo_length,
                                     uint16_t extension_type,
                                     const uint8_t **extension_data,
                                     uint16_t *extension_length)
{
    *extension_data = NULL;
    *extension_length = 0;
    if (serverinfo == NULL || serverinfo_length == 0)
        return 0;
    for (;;) {
        uint16_t type = 0;
        uint16_t len = 0;

        /* end of serverinfo */
        if (serverinfo_length == 0)
            return -1; /* Extension not found */

        /* read 2-byte type field */
        if (serverinfo_length < 2)
            return 0; /* Error */
        type = (serverinfo[0] << 8) + serverinfo[1];
        serverinfo += 2;
        serverinfo_length -= 2;

        /* read 2-byte len field */
        if (serverinfo_length < 2)
            return 0; /* Error */
        len = (serverinfo[0] << 8) + serverinfo[1];
        serverinfo += 2;
        serverinfo_length -= 2;

        if (len > serverinfo_length)
            return 0; /* Error */

        if (type == extension_type) {
            *extension_data = serverinfo;
            *extension_length = len;
            return 1; /* Success */
        }

        serverinfo += len;
        serverinfo_length -= len;
    }
    return 0; /* Error */
}

static int serverinfo_srv_first_cb(SSL *s, uint16_t ext_type, const uint8_t *in,
                                   uint16_t inlen, int *al, void *arg)
{
    if (inlen != 0) {
        *al = SSL_AD_DECODE_ERROR;
        return 0;
    }

    return 1;
}

static int serverinfo_srv_second_cb(SSL *s, uint16_t ext_type,
                                    const uint8_t **out, uint16_t *outlen,
                                    int *al, void *arg)
{
    const uint8_t *serverinfo = NULL;
    size_t serverinfo_length = 0;

    /* Is there serverinfo data for the chosen server cert? */
    if ((ssl_get_server_cert_serverinfo(s, &serverinfo, &serverinfo_length)) !=
        0) {
        /* Find the relevant extension from the serverinfo */
        int retval = serverinfo_find_extension(serverinfo, serverinfo_length,
                                               ext_type, out, outlen);
        if (retval == 0)
            return 0; /* Error */
        if (retval == -1)
            return -1; /* No extension found, don't send extension */
        return 1;      /* Send extension */
    }
    return -1; /* No serverinfo data found, don't send extension */
}

/* With a NULL context, this function just checks that the serverinfo data
   parses correctly.  With a non-NULL context, it registers callbacks for
   the included extensions. */
static int serverinfo_process_buffer(const uint8_t *serverinfo,
                                     size_t serverinfo_length, SSL_CTX *ctx)
{
    if (serverinfo == NULL || serverinfo_length == 0)
        return 0;
    for (;;) {
        uint16_t ext_type = 0;
        uint16_t len = 0;

        /* end of serverinfo */
        if (serverinfo_length == 0)
            return 1;

        /* read 2-byte type field */
        if (serverinfo_length < 2)
            return 0;
        /* FIXME: check for types we understand explicitly? */

        /* Register callbacks for extensions */
        ext_type = (serverinfo[0] << 8) + serverinfo[1];
        if (ctx &&
            !SSL_CTX_set_custom_srv_ext(ctx, ext_type, serverinfo_srv_first_cb,
                                        serverinfo_srv_second_cb, NULL))
            return 0;

        serverinfo += 2;
        serverinfo_length -= 2;

        /* read 2-byte len field */
        if (serverinfo_length < 2)
            return 0;
        len = (serverinfo[0] << 8) + serverinfo[1];
        serverinfo += 2;
        serverinfo_length -= 2;

        if (len > serverinfo_length)
            return 0;

        serverinfo += len;
        serverinfo_length -= len;
    }
}

int SSL_CTX_use_serverinfo(SSL_CTX *ctx, const uint8_t *serverinfo,
                           size_t serverinfo_length)
{
    if (ctx == NULL || serverinfo == NULL || serverinfo_length == 0) {
        SSLerr(SSL_F_SSL_CTX_USE_SERVERINFO, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    if (!serverinfo_process_buffer(serverinfo, serverinfo_length, NULL)) {
        SSLerr(SSL_F_SSL_CTX_USE_SERVERINFO, SSL_R_INVALID_SERVERINFO_DATA);
        return 0;
    }
    if (!ssl_cert_inst(&ctx->cert)) {
        SSLerr(SSL_F_SSL_CTX_USE_SERVERINFO, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    if (ctx->cert->key == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_SERVERINFO, ERR_R_INTERNAL_ERROR);
        return 0;
    }
    ctx->cert->key->serverinfo =
        realloc(ctx->cert->key->serverinfo, serverinfo_length);
    if (ctx->cert->key->serverinfo == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_SERVERINFO, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    memcpy(ctx->cert->key->serverinfo, serverinfo, serverinfo_length);
    ctx->cert->key->serverinfo_length = serverinfo_length;

    /*
     * Now that the serverinfo is validated and stored, go ahead and
     * register callbacks.
     */
    if (!serverinfo_process_buffer(serverinfo, serverinfo_length, ctx)) {
        SSLerr(SSL_F_SSL_CTX_USE_SERVERINFO, SSL_R_INVALID_SERVERINFO_DATA);
        return 0;
    }
    return 1;
}

int SSL_CTX_use_serverinfo_file(SSL_CTX *ctx, const char *file)
{
    uint8_t *serverinfo = NULL;
    size_t serverinfo_length = 0;
    uint8_t *extension = 0;
    long extension_length = 0;
    char *name = NULL;
    char *header = NULL;
    int ret = 0;
    BIO *bin = NULL;
    size_t num_extensions = 0;

    if (ctx == NULL || file == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_SERVERINFO_FILE, ERR_R_PASSED_NULL_PARAMETER);
        goto end;
    }

    bin = BIO_new(BIO_s_file_internal());
    if (bin == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_SERVERINFO_FILE, ERR_R_BUF_LIB);
        goto end;
    }
    if (BIO_read_filename(bin, file) <= 0) {
        SSLerr(SSL_F_SSL_CTX_USE_SERVERINFO_FILE, ERR_R_SYS_LIB);
        goto end;
    }

    for (num_extensions = 0;; num_extensions++) {
        if (PEM_read_bio(bin, &name, &header, &extension, &extension_length) ==
            0) {
            /* There must be at least one extension in this file */
            if (num_extensions == 0) {
                SSLerr(SSL_F_SSL_CTX_USE_SERVERINFO_FILE, ERR_R_PEM_LIB);
                goto end;
            } else /* End of file, we're done */
                break;
        }
        /* Check that the decoded PEM data is plausible (valid length field) */
        if (extension_length < 4 ||
            (extension[2] << 8) + extension[3] != extension_length - 4) {
            SSLerr(SSL_F_SSL_CTX_USE_SERVERINFO_FILE, ERR_R_PEM_LIB);
            goto end;
        }
        /* Append the decoded extension to the serverinfo buffer */
        serverinfo =
            realloc(serverinfo, serverinfo_length + extension_length);
        if (serverinfo == NULL) {
            SSLerr(SSL_F_SSL_CTX_USE_SERVERINFO_FILE, ERR_R_MALLOC_FAILURE);
            goto end;
        }
        memcpy(serverinfo + serverinfo_length, extension, extension_length);
        serverinfo_length += extension_length;

        free(name);
        name = NULL;
        free(header);
        header = NULL;
        free(extension);
        extension = NULL;
    }

    ret = SSL_CTX_use_serverinfo(ctx, serverinfo, serverinfo_length);
end:
    /* SSL_CTX_use_serverinfo makes a local copy of the serverinfo. */
    free(name);
    free(header);
    free(extension);
    free(serverinfo);
    BIO_free(bin);
    return ret;
}
