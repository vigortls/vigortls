/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <openssl/opensslconf.h> /* for OPENSSL_NO_DSA */
/* Until the key-gen callbacks are modified to use newer prototypes, we allow
 * deprecated functions for openssl-internal code */
#ifdef OPENSSL_NO_DEPRECATED
#undef OPENSSL_NO_DEPRECATED
#endif

#ifndef OPENSSL_NO_DSA
#include "apps.h"
#include <assert.h>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/dsa.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef GENCB_TEST

static int stop_keygen_flag = 0;

static void timebomb_sigalarm(int foo)
{
    stop_keygen_flag = 1;
}

#endif

static int dsa_cb(int p, int n, BN_GENCB *cb);

int dsaparam_main(int, char **);

int dsaparam_main(int argc, char **argv)
{
    DSA *dsa = NULL;
    int i, badops = 0, text = 0;
    BIO *in = NULL, *out = NULL;
    int informat, outformat, noout = 0, C = 0, ret = 1;
    char *infile, *outfile, *prog;
    int numbits = -1, num, genkey = 0;
#ifndef OPENSSL_NO_ENGINE
    char *engine = NULL;
#endif
#ifdef GENCB_TEST
    int timebomb = 0;
    const char *stnerr = NULL;
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
        }
#ifndef OPENSSL_NO_ENGINE
        else if (strcmp(*argv, "-engine") == 0) {
            if (--argc < 1)
                goto bad;
            engine = *(++argv);
        }
#endif
#ifdef GENCB_TEST
        else if (strcmp(*argv, "-timebomb") == 0) {
            if (--argc < 1)
                goto bad;
            timebomb = strtonum(*(++argv), 0, INT_MAX, &stnerr);
            if (stnerr)
                goto bad;
        }
#endif
        else if (strcmp(*argv, "-text") == 0)
            text = 1;
        else if (strcmp(*argv, "-C") == 0)
            C = 1;
        else if (strcmp(*argv, "-genkey") == 0) {
            genkey = 1;
        } else if (strcmp(*argv, "-noout") == 0)
            noout = 1;
        else if (sscanf(*argv, "%d", &num) == 1) {
            /* generate a key */
            numbits = num;
        } else {
            BIO_printf(bio_err, "unknown option %s\n", *argv);
            badops = 1;
            break;
        }
        argc--;
        argv++;
    }

    if (badops) {
    bad:
        BIO_printf(bio_err, "%s [options] [bits] <infile >outfile\n", prog);
        BIO_printf(bio_err, "where options are\n");
        BIO_printf(bio_err, " -inform arg   input format - DER or PEM\n");
        BIO_printf(bio_err, " -outform arg  output format - DER or PEM\n");
        BIO_printf(bio_err, " -in arg       input file\n");
        BIO_printf(bio_err, " -out arg      output file\n");
        BIO_printf(bio_err, " -text         print as text\n");
        BIO_printf(bio_err, " -C            Output C code\n");
        BIO_printf(bio_err, " -noout        no output\n");
        BIO_printf(bio_err, " -genkey       generate a DSA key\n");
#ifndef OPENSSL_NO_ENGINE
        BIO_printf(bio_err, " -engine e     use engine e, possibly a hardware device.\n");
#endif
#ifdef GENCB_TEST
        BIO_printf(bio_err, " -timebomb n   interrupt keygen after <n> seconds\n");
#endif
        BIO_printf(bio_err, " number        number of bits to use for "
                            "generating private key\n");
        goto end;
    }

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

#ifndef OPENSSL_NO_ENGINE
    setup_engine(bio_err, engine, 0);
#endif

    if (numbits > 0) {
        BN_GENCB cb;
        BN_GENCB_set(&cb, dsa_cb, bio_err);
        dsa = DSA_new();
        if (!dsa) {
            BIO_printf(bio_err, "Error allocating DSA object\n");
            goto end;
        }
        BIO_printf(bio_err, "Generating DSA parameters, %d bit long prime\n",
                   num);
        BIO_printf(bio_err, "This could take some time\n");
#ifdef GENCB_TEST
        if (timebomb > 0) {
            struct sigaction act;
            act.sa_handler = timebomb_sigalarm;
            act.sa_flags = 0;
            BIO_printf(bio_err,
                       "(though I'll stop it if not done within %d secs)\n",
                       timebomb);
            if (sigaction(SIGALRM, &act, NULL) != 0) {
                BIO_printf(bio_err, "Error, couldn't set SIGALRM handler\n");
                goto end;
            }
            alarm(timebomb);
        }
#endif
        if (!DSA_generate_parameters_ex(dsa, num, NULL, 0, NULL, NULL, &cb)) {
#ifdef GENCB_TEST
            if (stop_keygen_flag) {
                BIO_printf(bio_err, "DSA key generation time-stopped\n");
                /* This is an asked-for behavior! */
                ret = 0;
                goto end;
            }
#endif
            ERR_print_errors(bio_err);
            BIO_printf(bio_err, "Error, DSA key generation failed\n");
            goto end;
        }
    } else if (informat == FORMAT_ASN1)
        dsa = d2i_DSAparams_bio(in, NULL);
    else if (informat == FORMAT_PEM)
        dsa = PEM_read_bio_DSAparams(in, NULL, NULL, NULL);
    else {
        BIO_printf(bio_err, "bad input format specified\n");
        goto end;
    }
    if (dsa == NULL) {
        BIO_printf(bio_err, "unable to load DSA parameters\n");
        ERR_print_errors(bio_err);
        goto end;
    }

    if (text) {
        DSAparams_print(out, dsa);
    }

    if (C) {
        uint8_t *data;
        int l, len, bits_p;

        len = BN_num_bytes(dsa->p);
        bits_p = BN_num_bits(dsa->p);
        data = malloc(len + 20);
        if (data == NULL) {
            perror("malloc");
            goto end;
        }
        l = BN_bn2bin(dsa->p, data);
        printf("static uint8_t dsa%d_p[]={", bits_p);
        for (i = 0; i < l; i++) {
            if ((i % 12) == 0)
                printf("\n\t");
            printf("0x%02X,", data[i]);
        }
        printf("\n\t};\n");

        l = BN_bn2bin(dsa->q, data);
        printf("static uint8_t dsa%d_q[]={", bits_p);
        for (i = 0; i < l; i++) {
            if ((i % 12) == 0)
                printf("\n\t");
            printf("0x%02X,", data[i]);
        }
        printf("\n\t};\n");

        l = BN_bn2bin(dsa->g, data);
        printf("static uint8_t dsa%d_g[]={", bits_p);
        for (i = 0; i < l; i++) {
            if ((i % 12) == 0)
                printf("\n\t");
            printf("0x%02X,", data[i]);
        }
        printf("\n\t};\n\n");

        printf("DSA *get_dsa%d()\n\t{\n", bits_p);
        printf("\tDSA *dsa;\n\n");
        printf("\tif ((dsa=DSA_new()) == NULL) return (NULL);\n");
        printf("\tdsa->p=BN_bin2bn(dsa%d_p,sizeof(dsa%d_p),NULL);\n", bits_p,
               bits_p);
        printf("\tdsa->q=BN_bin2bn(dsa%d_q,sizeof(dsa%d_q),NULL);\n", bits_p,
               bits_p);
        printf("\tdsa->g=BN_bin2bn(dsa%d_g,sizeof(dsa%d_g),NULL);\n", bits_p,
               bits_p);
        printf("\tif ((dsa->p == NULL) || (dsa->q == NULL) || (dsa->g == "
               "NULL))\n");
        printf("\t\t{ DSA_free(dsa); return (NULL); }\n");
        printf("\treturn (dsa);\n\t}\n");
        free(data);
    }

    if (!noout) {
        if (outformat == FORMAT_ASN1)
            i = i2d_DSAparams_bio(out, dsa);
        else if (outformat == FORMAT_PEM)
            i = PEM_write_bio_DSAparams(out, dsa);
        else {
            BIO_printf(bio_err, "bad output format specified for outfile\n");
            goto end;
        }
        if (!i) {
            BIO_printf(bio_err, "unable to write DSA parameters\n");
            ERR_print_errors(bio_err);
            goto end;
        }
    }
    if (genkey) {
        DSA *dsakey;

        if ((dsakey = DSAparams_dup(dsa)) == NULL)
            goto end;
        if (!DSA_generate_key(dsakey)) {
            ERR_print_errors(bio_err);
            DSA_free(dsakey);
            goto end;
        }
        if (outformat == FORMAT_ASN1)
            i = i2d_DSAPrivateKey_bio(out, dsakey);
        else if (outformat == FORMAT_PEM)
            i = PEM_write_bio_DSAPrivateKey(out, dsakey, NULL, NULL, 0, NULL,
                                            NULL);
        else {
            BIO_printf(bio_err, "bad output format specified for outfile\n");
            DSA_free(dsakey);
            goto end;
        }
        DSA_free(dsakey);
    }
    ret = 0;
end:
    if (in != NULL)
        BIO_free(in);
    if (out != NULL)
        BIO_free_all(out);
    if (dsa != NULL)
        DSA_free(dsa);
    return (ret);
}

static int dsa_cb(int p, int n, BN_GENCB *cb)
{
    char c = '*';

    if (p == 0)
        c = '.';
    if (p == 1)
        c = '+';
    if (p == 2)
        c = '*';
    if (p == 3)
        c = '\n';
    BIO_write(cb->arg, &c, 1);
    (void)BIO_flush(cb->arg);
#ifdef GENCB_TEST
    if (stop_keygen_flag)
        return 0;
#endif
    return 1;
}
#endif
