/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "apps.h"
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/bn.h>
#include <openssl/dh.h>
#include <openssl/x509.h>
#include <openssl/pem.h>

#ifndef OPENSSL_NO_DSA
#include <openssl/dsa.h>
#endif

#define DEFBITS 2048

typedef enum OPTION_choice {
    OPT_ERR = -1,
    OPT_EOF = 0,
    OPT_HELP,
    OPT_INFORM,
    OPT_OUTFORM,
    OPT_IN,
    OPT_OUT,
    OPT_ENGINE,
    OPT_CHECK,
    OPT_TEXT,
    OPT_NOOUT,
    OPT_DSAPARAM,
    OPT_C,
    OPT_2,
    OPT_5
} OPTION_CHOICE;

OPTIONS dhparam_options[] = {
    { OPT_HELP_STR, 1, '-', "Usage: %s [flags] [numbits]\n" },
    { OPT_HELP_STR, 1, '-', "Valid options are:\n" },
    { "help", OPT_HELP, '-', "Display this summary" },
    { "in", OPT_IN, '<', "Input file" },
    { "inform", OPT_INFORM, 'F', "Input format, DER or PEM" },
    { "outform", OPT_OUTFORM, 'F', "Output format, DER or PEM" },
    { "out", OPT_OUT, '>', "Output file" },
    { "check", OPT_CHECK, '-', "Check the DH parameters" },
    { "text", OPT_TEXT, '-', "Print a text form of the DH parameters" },
    { "noout", OPT_NOOUT, '-' },
    { "C", OPT_C, '-', "Print C code" },
    { "2", OPT_2, '-', "Generate parameters using 2 as the generator value" },
    { "5", OPT_5, '-', "Generate parameters using 5 as the generator value" },
#ifndef OPENSSL_NO_ENGINE
    { "engine", OPT_ENGINE, 's', "Use engine e, possibly a hardware device" },
#endif
#ifndef OPENSSL_NO_DSA
    { "dsaparam", OPT_DSAPARAM, '-', "Read or generate DSA parameters, convert to DH" },
#endif
    { NULL }
};

static int dh_cb(int p, int n, BN_GENCB *cb);

int dhparam_main(int argc, char **argv)
{
    BIO *in = NULL, *out = NULL;
    DH *dh = NULL;
    char *engine = NULL, *infile = NULL, *outfile = NULL, *prog;
    int dsaparam = 0, i, text = 0, C = 0, ret = 1, num = 0, g = 0;
    int informat = FORMAT_PEM, outformat = FORMAT_PEM, check = 0, noout = 0;
    OPTION_CHOICE o;

    prog = opt_init(argc, argv, dhparam_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
            case OPT_EOF:
            case OPT_ERR:
            opthelp:
                BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
                goto end;
            case OPT_HELP:
                opt_help(dhparam_options);
                ret = 0;
                goto end;
            case OPT_INFORM:
                if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &informat))
                    goto opthelp;
                break;
            case OPT_OUTFORM:
                if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &outformat))
                    goto opthelp;
                break;
            case OPT_IN:
                infile = opt_arg();
                break;
            case OPT_OUT:
                outfile = opt_arg();
                break;
            case OPT_ENGINE:
                engine = opt_arg();
                break;
            case OPT_CHECK:
                check = 1;
                break;
            case OPT_TEXT:
                text = 1;
                break;
            case OPT_DSAPARAM:
                dsaparam = 1;
                break;
            case OPT_C:
                C = 1;
                break;
            case OPT_2:
                g = 2;
                break;
            case OPT_5:
                g = 5;
                break;
            case OPT_NOOUT:
                noout = 1;
                break;
        }
    }
    argc = opt_num_rest();
    argv = opt_rest();

    if (argv[0] && (!opt_int(argv[0], &num) || num <= 0))
        goto end;

#ifndef OPENSSL_NO_ENGINE
    setup_engine(engine, 0);
#endif

    if (g && !num)
        num = DEFBITS;

#ifndef OPENSSL_NO_DSA
    if (dsaparam && g) {
        BIO_printf(bio_err, "generator may not be chosen for DSA parameters\n");
        goto end;
    }
#endif
    /* DH parameters */
    if (num && !g)
        g = 2;

    if (num) {

        BN_GENCB cb;
        BN_GENCB_set(&cb, dh_cb, bio_err);

#ifndef OPENSSL_NO_DSA
        if (dsaparam) {
            DSA *dsa = DSA_new();

            BIO_printf(bio_err, "Generating DSA parameters, %d bit long prime\n", num);
            if (!dsa || !DSA_generate_parameters_ex(dsa, num, NULL, 0, NULL, NULL, &cb)) {
                DSA_free(dsa);
                ERR_print_errors(bio_err);
                goto end;
            }

            dh = DSA_dup_DH(dsa);
            DSA_free(dsa);
            if (dh == NULL) {
                ERR_print_errors(bio_err);
                goto end;
            }
        } else
#endif
        {
            dh = DH_new();
            BIO_printf(bio_err,
                       "Generating DH parameters, %d bit long safe prime, generator %d\n",
                       num, g);
            BIO_printf(bio_err, "This is going to take a long time\n");
            if (!dh || !DH_generate_parameters_ex(dh, num, g, &cb)) {
                ERR_print_errors(bio_err);
                goto end;
            }
        }
    } else {

        in = bio_open_default(infile, RB(informat));
        if (in == NULL)
            goto end;

#ifndef OPENSSL_NO_DSA
        if (dsaparam) {
            DSA *dsa;

            if (informat == FORMAT_ASN1)
                dsa = d2i_DSAparams_bio(in, NULL);
            else /* informat == FORMAT_PEM */
                dsa = PEM_read_bio_DSAparams(in, NULL, NULL, NULL);

            if (dsa == NULL) {
                BIO_printf(bio_err, "unable to load DSA parameters\n");
                ERR_print_errors(bio_err);
                goto end;
            }

            dh = DSA_dup_DH(dsa);
            DSA_free(dsa);
            if (dh == NULL) {
                ERR_print_errors(bio_err);
                goto end;
            }
        } else
#endif
        {
            if (informat == FORMAT_ASN1)
                dh = d2i_DHparams_bio(in, NULL);
            else /* informat == FORMAT_PEM */
                dh = PEM_read_bio_DHparams(in, NULL, NULL, NULL);

            if (dh == NULL) {
                BIO_printf(bio_err, "unable to load DH parameters\n");
                ERR_print_errors(bio_err);
                goto end;
            }
        }

        /* dh != NULL */
    }

    out = bio_open_default(outfile, "w");
    if (out == NULL)
        goto end;

    if (text) {
        DHparams_print(out, dh);
    }

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
            printf("DH parameters appear to be ok.\n");
    }
    if (C) {
        uint8_t *data;
        int len, bits;

        len = BN_num_bytes(dh->p);
        bits = BN_num_bits(dh->p);
        data = malloc(len);
        if (data == NULL) {
            perror("malloc failure");
            goto end;
        }
        BIO_printf(out, "#ifndef HEADER_DH_H\n"
                        "# include <openssl/dh.h>\n"
                        "#endif\n"
                        "\n");
        BIO_printf(out, "DH *get_dh%d()\n{\n", bits);
        print_bignum_var(out, dh->p, "dhp", bits, data);
        print_bignum_var(out, dh->g, "dhg", bits, data);
        BIO_printf(out, "    DH *dh = DN_new();\n"
                        "\n"
                        "    if (dh == NULL)\n"
                        "        return NULL;\n");
        BIO_printf(out, "    dh->p = BN_bin2bn(dhp_%d, sizeof (dhp_%d), NULL);\n", bits,
                   bits);
        BIO_printf(out, "    dh->g = BN_bin2bn(dhg_%d, sizeof (dhg_%d), NULL);\n", bits,
                   bits);
        BIO_printf(out, "    if (!dh->p || !dh->g) {\n"
                        "        DH_free(dh);\n"
                        "        return NULL;\n"
                        "    }\n");
        if (dh->length)
            BIO_printf(out, "    dh->length = %ld;\n", dh->length);
        BIO_printf(out, "    return dh;\n}\n");
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
    BIO_free(in);
    BIO_free_all(out);
    DH_free(dh);
    return (ret);
}

static int dh_cb(int p, int n, BN_GENCB *cb)
{
    char c;

    select_symbol(p, &c);
    BIO_write(cb->arg, &c, 1);
    (void)BIO_flush(cb->arg);
    return 1;
}
