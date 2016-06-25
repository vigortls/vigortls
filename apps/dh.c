/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include "apps.h"
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/dh.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int dh_main(int argc, char **argv)
{
    DH *dh = NULL;
    int i, badops = 0, text = 0;
    BIO *in = NULL, *out = NULL;
    int informat, outformat, check = 0, noout = 0, C = 0, ret = 1;
    char *infile, *outfile, *prog;
#ifndef OPENSSL_NO_ENGINE
    char *engine;
#endif

    if (bio_err == NULL)
        if ((bio_err = BIO_new(BIO_s_file())) != NULL)
            BIO_set_fp(bio_err, stderr, BIO_NOCLOSE | BIO_FP_TEXT);

    if (!load_config(bio_err, NULL))
        goto end;

#ifndef OPENSSL_NO_ENGINE
    engine = NULL;
#endif
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
        }
#ifndef OPENSSL_NO_ENGINE
        else if (strcmp(*argv, "-engine") == 0) {
            if (--argc < 1)
                goto bad;
            engine = *(++argv);
        }
#endif
        else if (strcmp(*argv, "-check") == 0)
            check = 1;
        else if (strcmp(*argv, "-text") == 0)
            text = 1;
        else if (strcmp(*argv, "-C") == 0)
            C = 1;
        else if (strcmp(*argv, "-noout") == 0)
            noout = 1;
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
        BIO_printf(bio_err, " -inform arg   input format - one of DER PEM\n");
        BIO_printf(bio_err, " -outform arg  output format - one of DER PEM\n");
        BIO_printf(bio_err, " -in arg       input file\n");
        BIO_printf(bio_err, " -out arg      output file\n");
        BIO_printf(bio_err, " -check        check the DH parameters\n");
        BIO_printf(bio_err, " -text         print a text form of the DH parameters\n");
        BIO_printf(bio_err, " -C            Output C code\n");
        BIO_printf(bio_err, " -noout        no output\n");
#ifndef OPENSSL_NO_ENGINE
        BIO_printf(bio_err, " -engine e     use engine e, possibly a hardware device.\n");
#endif
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
            perror(infile);
            goto end;
        }
    }
    if (outfile == NULL) {
        BIO_set_fp(out, stdout, BIO_NOCLOSE);
    } else {
        if (BIO_write_filename(out, outfile) <= 0) {
            perror(outfile);
            goto end;
        }
    }

    if (informat == FORMAT_ASN1)
        dh = d2i_DHparams_bio(in, NULL);
    else if (informat == FORMAT_PEM)
        dh = PEM_read_bio_DHparams(in, NULL, NULL, NULL);
    else {
        BIO_printf(bio_err, "bad input format specified\n");
        goto end;
    }
    if (dh == NULL) {
        BIO_printf(bio_err, "unable to load DH parameters\n");
        ERR_print_errors(bio_err);
        goto end;
    }

    if (text)
        DHparams_print(out, dh);

    if (check) {
        if (!DH_check(dh, &i)) {
            ERR_print_errors(bio_err);
            goto end;
        }
        if (i & DH_CHECK_P_NOT_PRIME)
            printf("p value is not prime\n");
        if (i & DH_CHECK_P_NOT_SAFE_PRIME)
            printf("p value is not a safe prime\n");
        if (i & DH_UNABLE_TO_CHECK_GENERATOR)
            printf("unable to check the generator value\n");
        if (i & DH_NOT_SUITABLE_GENERATOR)
            printf("the g value is not a generator\n");
        if (i == 0)
            printf("DH parameters appear to be OK.\n");
    }
    if (C) {
        uint8_t *data;
        int len, l, bits;

        len = BN_num_bytes(dh->p);
        bits = BN_num_bits(dh->p);
        data = malloc(len);
        if (data == NULL) {
            perror("malloc");
            goto end;
        }
        l = BN_bn2bin(dh->p, data);
        printf("static uint8_t dh%d_p[]={", bits);
        for (i = 0; i < l; i++) {
            if ((i % 12) == 0)
                printf("\n\t");
            printf("0x%02X,", data[i]);
        }
        printf("\n\t};\n");

        l = BN_bn2bin(dh->g, data);
        printf("static uint8_t dh%d_g[]={", bits);
        for (i = 0; i < l; i++) {
            if ((i % 12) == 0)
                printf("\n\t");
            printf("0x%02X,", data[i]);
        }
        printf("\n\t};\n\n");

        printf("DH *get_dh%d()\n\t{\n", bits);
        printf("\tDH *dh;\n\n");
        printf("\tif ((dh=DH_new()) == NULL) return (NULL);\n");
        printf("\tdh->p=BN_bin2bn(dh%d_p,sizeof(dh%d_p),NULL);\n", bits, bits);
        printf("\tdh->g=BN_bin2bn(dh%d_g,sizeof(dh%d_g),NULL);\n", bits, bits);
        printf("\tif ((dh->p == NULL) || (dh->g == NULL))\n");
        printf("\t\treturn (NULL);\n");
        printf("\treturn (dh);\n\t}\n");
        free(data);
    }

    if (!noout) {
        if (outformat == FORMAT_ASN1)
            i = i2d_DHparams_bio(out, dh);
        else if (outformat == FORMAT_PEM)
            i = PEM_write_bio_DHparams(out, dh);
        else {
            BIO_printf(bio_err, "bad output format specified for outfile\n");
            goto end;
        }
        if (!i) {
            BIO_printf(bio_err, "unable to write DH parameters\n");
            ERR_print_errors(bio_err);
            goto end;
        }
    }
    ret = 0;
end:
    if (in != NULL)
        BIO_free(in);
    if (out != NULL)
        BIO_free_all(out);
    if (dh != NULL)
        DH_free(dh);
    return (ret);
}
