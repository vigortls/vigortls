/*
 * Copyright 2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <openssl/bio.h>
#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "ssltestlib.h"

static char *cert = NULL;
static char *privkey = NULL;


#define DUMMY_CERT_STATUS_LEN  12

uint8_t certstatus[] = {
    SSL3_RT_HANDSHAKE, /* Content type */
    0xfe, 0xfd, /* Record version */
    0, 1, /* Epoch */
    0, 0, 0, 0, 0, 0x0f, /* Record sequence number */
    0, DTLS1_HM_HEADER_LENGTH + DUMMY_CERT_STATUS_LEN - 2,
    SSL3_MT_CERTIFICATE_STATUS, /* Cert Status handshake message type */
    0, 0, DUMMY_CERT_STATUS_LEN, /* Message len */
    0, 5, /* Message sequence */
    0, 0, 0, /* Fragment offset */
    0, 0, DUMMY_CERT_STATUS_LEN - 2, /* Fragment len */
    0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80 /* Dummy data */
};

static int test_dtls_unprocessed(void)
{
    SSL_CTX *sctx = NULL, *cctx = NULL;
    SSL *serverssl1 = NULL, *clientssl1 = NULL;
    BIO *c_to_s_fbio, *c_to_s_mempacket;
    int testresult = 0;

    if (!create_ssl_ctx_pair(DTLS_server_method(), DTLS_client_method(), &sctx,
                             &cctx, cert, privkey)) {
        printf("Unable to create SSL_CTX pair\n");
        return 0;
    }

    if (!SSL_CTX_set_ecdh_auto(sctx, 1)) {
        printf("Failed configuring auto ECDH\n");
    }

    if (!SSL_CTX_set_cipher_list(cctx, "ECDHE-RSA-AES256-SHA384")) {
        printf("Failed setting cipher list\n");
    }

    c_to_s_fbio = BIO_new(bio_f_tls_dump_filter());
    if (c_to_s_fbio == NULL) {
        printf("Failed to create filter BIO\n");
        goto end;
    }

    /* BIO is freed by create_ssl_connection on error */
    if (!create_ssl_objects(sctx, cctx, &serverssl1, &clientssl1, NULL,
                               c_to_s_fbio)) {
        printf("Unable to create SSL objects\n");
        ERR_print_errors_fp(stdout);
        goto end;
    }

    /*
     * Inject a dummy record from the next epoch. This should never get used
     * because the message sequence number is too big
     */
    c_to_s_mempacket = SSL_get_wbio(clientssl1);
    c_to_s_mempacket = BIO_next(c_to_s_mempacket);
    mempacket_test_inject(c_to_s_mempacket, (char *)certstatus,
                          sizeof(certstatus), 1, INJECT_PACKET_IGNORE_REC_SEQ);

    if (!create_ssl_connection(serverssl1, clientssl1)) {
        printf("Unable to create SSL connection\n");
        ERR_print_errors_fp(stdout);
        goto end;
    }

    testresult = 1;
 end:
    SSL_free(serverssl1);
    SSL_free(clientssl1);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return testresult;
}

int main(int argc, char *argv[])
{
    BIO *err = NULL;
    int testresult = 0;

    if (argc != 3) {
        printf("Usage: dtlstest <cert> <key>\n");
        return 1;
    }

    cert = argv[1];
    privkey = argv[2];

    err = BIO_new_fp(stderr, BIO_NOCLOSE | BIO_FP_TEXT);

    SSL_library_init();
    SSL_load_error_strings();

    if (!test_dtls_unprocessed())
        testresult = 1;

    ERR_free_strings();
    ERR_remove_thread_state(NULL);
    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
    BIO_free(err);

    if (!testresult)
        printf("PASS\n");

    return testresult;
}

