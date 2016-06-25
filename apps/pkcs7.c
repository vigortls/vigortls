/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include "apps.h"
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/objects.h>
#include <openssl/pem.h>
#include <openssl/pkcs7.h>
#include <openssl/x509.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* -inform arg    - input format - default PEM (DER or PEM)
 * -outform arg - output format - default PEM
 * -in arg    - input file - default stdin
 * -out arg    - output file - default stdout
 * -print_certs
 */

int pkcs7_main(int, char **);

int pkcs7_main(int argc, char **argv)
{
    PKCS7 *p7 = NULL;
    int i, badops = 0;
    BIO *in = NULL, *out = NULL;
    int informat, outformat;
    char *infile, *outfile, *prog;
    int print_certs = 0, text = 0, noout = 0, p7_print = 0;
    int ret = 1;
#ifndef OPENSSL_NO_ENGINE
    char *engine = NULL;
#endif

    if (bio_err == NULL)
        if ((bio_err = BIO_new(BIO_s_file())) != NULL)
            BIO_set_fp(bio_err, stderr, BIO_NOCLOSE | BIO_FP_TEXT);

    if (!load_config(bio_err, NULL))
        goto end;

    infile = NULL;
    outfile = NULL;
    informat = FORMAT_PEM;
    outformat = FORMAT_PEM;

    prog = argv[0];
    argc--;
    argv++;
    while (argc >= 1) {
        if (strcmp(*argv, "-inform") == 0) {
            if (--argc < 1)
                goto bad;
            informat = str2fmt(*(++argv));
        } else if (strcmp(*argv, "-outform") == 0) {
            if (--argc < 1)
                goto bad;
            outformat = str2fmt(*(++argv));
        } else if (strcmp(*argv, "-in") == 0) {
            if (--argc < 1)
                goto bad;
            infile = *(++argv);
        } else if (strcmp(*argv, "-out") == 0) {
            if (--argc < 1)
                goto bad;
            outfile = *(++argv);
        } else if (strcmp(*argv, "-noout") == 0)
            noout = 1;
        else if (strcmp(*argv, "-text") == 0)
            text = 1;
        else if (strcmp(*argv, "-print") == 0)
            p7_print = 1;
        else if (strcmp(*argv, "-print_certs") == 0)
            print_certs = 1;
#ifndef OPENSSL_NO_ENGINE
        else if (strcmp(*argv, "-engine") == 0) {
            if (--argc < 1)
                goto bad;
            engine = *(++argv);
        }
#endif
        else {
            BIO_printf(bio_err, "unknown option %s\n", *argv);
            badops = 1;
            break;
        }
        argc--;
        argv++;
    }

    if (badops) {
    bad:
        BIO_printf(bio_err, "%s [options] <infile >outfile\n", prog);
        BIO_printf(bio_err, "where options are\n");
        BIO_printf(bio_err, " -inform arg   input format - DER or PEM\n");
        BIO_printf(bio_err, " -outform arg  output format - DER or PEM\n");
        BIO_printf(bio_err, " -in arg       input file\n");
        BIO_printf(bio_err, " -out arg      output file\n");
        BIO_printf(bio_err, " -print_certs  print any certs or crl in the input\n");
        BIO_printf(bio_err, " -text         print full details of certificates\n");
        BIO_printf(bio_err, " -noout        don't output encoded data\n");
#ifndef OPENSSL_NO_ENGINE
        BIO_printf(bio_err, " -engine e     use engine e, possibly a hardware device.\n");
#endif
        ret = 1;
        goto end;
    }

#ifndef OPENSSL_NO_ENGINE
    setup_engine(bio_err, engine, 0);
#endif

    in = BIO_new(BIO_s_file());
    out = BIO_new(BIO_s_file());
    if ((in == NULL) || (out == NULL)) {
        ERR_print_errors(bio_err);
        goto end;
    }

    if (infile == NULL)
        BIO_set_fp(in, stdin, BIO_NOCLOSE);
    else {
        if (BIO_read_filename(in, infile) <= 0) {
            BIO_printf(bio_err, "unable to load input file\n");
            ERR_print_errors(bio_err);
            goto end;
        }
    }

    if (informat == FORMAT_ASN1)
        p7 = d2i_PKCS7_bio(in, NULL);
    else if (informat == FORMAT_PEM)
        p7 = PEM_read_bio_PKCS7(in, NULL, NULL, NULL);
    else {
        BIO_printf(bio_err, "bad input format specified for pkcs7 object\n");
        goto end;
    }
    if (p7 == NULL) {
        BIO_printf(bio_err, "unable to load PKCS7 object\n");
        ERR_print_errors(bio_err);
        goto end;
    }

    if (outfile == NULL) {
        BIO_set_fp(out, stdout, BIO_NOCLOSE);
    } else {
        if (BIO_write_filename(out, outfile) <= 0) {
            perror(outfile);
            goto end;
        }
    }

    if (p7_print)
        PKCS7_print_ctx(out, p7, 0, NULL);

    if (print_certs) {
        STACK_OF(X509) *certs = NULL;
        STACK_OF(X509_CRL) *crls = NULL;

        i = OBJ_obj2nid(p7->type);
        switch (i) {
            case NID_pkcs7_signed:
                certs = p7->d.sign->cert;
                crls = p7->d.sign->crl;
                break;
            case NID_pkcs7_signedAndEnveloped:
                certs = p7->d.signed_and_enveloped->cert;
                crls = p7->d.signed_and_enveloped->crl;
                break;
            default:
                break;
        }

        if (certs != NULL) {
            X509 *x;

            for (i = 0; i < sk_X509_num(certs); i++) {
                x = sk_X509_value(certs, i);
                if (text)
                    X509_print(out, x);
                else
                    dump_cert_text(out, x);

                if (!noout)
                    PEM_write_bio_X509(out, x);
                BIO_puts(out, "\n");
            }
        }
        if (crls != NULL) {
            X509_CRL *crl;

            for (i = 0; i < sk_X509_CRL_num(crls); i++) {
                crl = sk_X509_CRL_value(crls, i);

                X509_CRL_print(out, crl);

                if (!noout)
                    PEM_write_bio_X509_CRL(out, crl);
                BIO_puts(out, "\n");
            }
        }

        ret = 0;
        goto end;
    }

    if (!noout) {
        if (outformat == FORMAT_ASN1)
            i = i2d_PKCS7_bio(out, p7);
        else if (outformat == FORMAT_PEM)
            i = PEM_write_bio_PKCS7(out, p7);
        else {
            BIO_printf(bio_err, "bad output format specified for outfile\n");
            goto end;
        }

        if (!i) {
            BIO_printf(bio_err, "unable to write pkcs7 object\n");
            ERR_print_errors(bio_err);
            goto end;
        }
    }
    ret = 0;
end:
    if (p7 != NULL)
        PKCS7_free(p7);
    if (in != NULL)
        BIO_free(in);
    if (out != NULL)
        BIO_free_all(out);
    return (ret);
}
