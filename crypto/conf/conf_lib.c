/*
 * Copyright 2000-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include <openssl/crypto.h>
#include <openssl/err.h>
#include <openssl/conf.h>
#include <openssl/conf_api.h>
#include <openssl/lhash.h>

static CONF_METHOD *default_CONF_method = NULL;

/* Init a 'CONF' structure from an old LHASH */

void CONF_set_nconf(CONF *conf, LHASH_OF(CONF_VALUE) *hash)
{
    if (default_CONF_method == NULL)
        default_CONF_method = NCONF_default();

    default_CONF_method->init(conf);
    conf->data = hash;
}

/* The following section contains the "CONF classic" functions,
   rewritten in terms of the new CONF interface. */

int CONF_set_default_method(CONF_METHOD *meth)
{
    default_CONF_method = meth;
    return 1;
}

LHASH_OF(CONF_VALUE) *CONF_load(LHASH_OF(CONF_VALUE) *conf, const char *file,
                                 long *eline)
{
    LHASH_OF(CONF_VALUE) *ltmp;
    BIO *in = NULL;

    in = BIO_new_file(file, "rb");

    if (in == NULL) {
        CONFerr(CONF_F_CONF_LOAD, ERR_R_SYS_LIB);
        return NULL;
    }

    ltmp = CONF_load_bio(conf, in, eline);
    BIO_free(in);

    return ltmp;
}

LHASH_OF(CONF_VALUE) *CONF_load_fp(LHASH_OF(CONF_VALUE) *conf, FILE * fp,
                                    long *eline)
{
    BIO *btmp;
    LHASH_OF(CONF_VALUE) *ltmp;
    if (!(btmp = BIO_new_fp(fp, BIO_NOCLOSE))) {
        CONFerr(CONF_F_CONF_LOAD_FP, ERR_R_BUF_LIB);
        return NULL;
    }
    ltmp = CONF_load_bio(conf, btmp, eline);
    BIO_free(btmp);
    return ltmp;
}

LHASH_OF(CONF_VALUE) *CONF_load_bio(LHASH_OF(CONF_VALUE) *conf, BIO * bp,
                                     long *eline)
{
    CONF ctmp;
    int ret;

    CONF_set_nconf(&ctmp, conf);

    ret = NCONF_load_bio(&ctmp, bp, eline);
    if (ret)
        return ctmp.data;
    return NULL;
}

STACK_OF(CONF_VALUE) *CONF_get_section(LHASH_OF(CONF_VALUE) *conf,
                                        const char *section)
{
    if (conf == NULL) {
        return NULL;
    } else {
        CONF ctmp;
        CONF_set_nconf(&ctmp, conf);
        return NCONF_get_section(&ctmp, section);
    }
}

char *CONF_get_string(LHASH_OF(CONF_VALUE) *conf, const char *group,
                      const char *name)
{
    if (conf == NULL) {
        return NCONF_get_string(NULL, group, name);
    } else {
        CONF ctmp;
        CONF_set_nconf(&ctmp, conf);
        return NCONF_get_string(&ctmp, group, name);
    }
}

long CONF_get_number(LHASH_OF(CONF_VALUE) *conf, const char *group,
                     const char *name)
{
    int status;
    long result = 0;

    if (conf == NULL) {
        status = NCONF_get_number_e(NULL, group, name, &result);
    } else {
        CONF ctmp;
        CONF_set_nconf(&ctmp, conf);
        status = NCONF_get_number_e(&ctmp, group, name, &result);
    }

    if (status == 0) {
        /* This function does not believe in errors... */
        ERR_clear_error();
    }
    return result;
}

void CONF_free(LHASH_OF(CONF_VALUE) *conf)
{
    CONF ctmp;
    CONF_set_nconf(&ctmp, conf);
    NCONF_free_data(&ctmp);
}

int CONF_dump_fp(LHASH_OF(CONF_VALUE) *conf, FILE * out)
{
    BIO *btmp;
    int ret;

    if (!(btmp = BIO_new_fp(out, BIO_NOCLOSE))) {
        CONFerr(CONF_F_CONF_DUMP_FP, ERR_R_BUF_LIB);
        return 0;
    }
    ret = CONF_dump_bio(conf, btmp);
    BIO_free(btmp);
    return ret;
}

int CONF_dump_bio(LHASH_OF(CONF_VALUE) *conf, BIO * out)
{
    CONF ctmp;
    CONF_set_nconf(&ctmp, conf);
    return NCONF_dump_bio(&ctmp, out);
}

/* The following section contains the "New CONF" functions.  They are
   completely centralised around a new CONF structure that may contain
   basically anything, but at least a method pointer and a table of data.
   These functions are also written in terms of the bridge functions used
   by the "CONF classic" functions, for consistency.  */

CONF *NCONF_new(CONF_METHOD *meth)
{
    CONF *ret;

    if (meth == NULL)
        meth = NCONF_default();

    ret = meth->create(meth);
    if (ret == NULL) {
        CONFerr(CONF_F_NCONF_NEW, ERR_R_MALLOC_FAILURE);
        return (NULL);
    }

    return ret;
}

void NCONF_free(CONF *conf)
{
    if (conf == NULL)
        return;
    conf->meth->destroy(conf);
}

void NCONF_free_data(CONF *conf)
{
    if (conf == NULL)
        return;
    conf->meth->destroy_data(conf);
}

int NCONF_load(CONF *conf, const char *file, long *eline)
{
    if (conf == NULL) {
        CONFerr(CONF_F_NCONF_LOAD, CONF_R_NO_CONF);
        return 0;
    }

    return conf->meth->load(conf, file, eline);
}

int NCONF_load_fp(CONF *conf, FILE *fp, long *eline)
{
    BIO *btmp;
    int ret;
    if (!(btmp = BIO_new_fp(fp, BIO_NOCLOSE))) {
        CONFerr(CONF_F_NCONF_LOAD_FP, ERR_R_BUF_LIB);
        return 0;
    }
    ret = NCONF_load_bio(conf, btmp, eline);
    BIO_free(btmp);
    return ret;
}

int NCONF_load_bio(CONF *conf, BIO *bp, long *eline)
{
    if (conf == NULL) {
        CONFerr(CONF_F_NCONF_LOAD_BIO, CONF_R_NO_CONF);
        return 0;
    }

    return conf->meth->load_bio(conf, bp, eline);
}

STACK_OF(CONF_VALUE) *NCONF_get_section(const CONF *conf, const char *section)
{
    if (conf == NULL) {
        CONFerr(CONF_F_NCONF_GET_SECTION, CONF_R_NO_CONF);
        return NULL;
    }

    if (section == NULL) {
        CONFerr(CONF_F_NCONF_GET_SECTION, CONF_R_NO_SECTION);
        return NULL;
    }

    return _CONF_get_section_values(conf, section);
}

char *NCONF_get_string(const CONF *conf, const char *group, const char *name)
{
    char *s = _CONF_get_string(conf, group, name);

    /* Since we may get a value from an environment variable even
           if conf is NULL, let's check the value first */
    if (s)
        return s;

    if (conf == NULL) {
        CONFerr(CONF_F_NCONF_GET_STRING,
                CONF_R_NO_CONF_OR_ENVIRONMENT_VARIABLE);
        return NULL;
    }
    CONFerr(CONF_F_NCONF_GET_STRING,
            CONF_R_NO_VALUE);
    ERR_asprintf_error_data("group=%s name=%s", group, name);
    return NULL;
}

int NCONF_get_number_e(const CONF *conf, const char *group, const char *name,
                       long *result)
{
    char *str;

    if (result == NULL) {
        CONFerr(CONF_F_NCONF_GET_NUMBER_E, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }

    str = NCONF_get_string(conf, group, name);

    if (str == NULL)
        return 0;

    for (*result = 0; conf->meth->is_number(conf, *str);) {
        *result = (*result) * 10 + conf->meth->to_int(conf, *str);
        str++;
    }

    return 1;
}

int NCONF_dump_fp(const CONF *conf, FILE *out)
{
    BIO *btmp;
    int ret;
    if (!(btmp = BIO_new_fp(out, BIO_NOCLOSE))) {
        CONFerr(CONF_F_NCONF_DUMP_FP, ERR_R_BUF_LIB);
        return 0;
    }
    ret = NCONF_dump_bio(conf, btmp);
    BIO_free(btmp);
    return ret;
}

int NCONF_dump_bio(const CONF *conf, BIO *out)
{
    if (conf == NULL) {
        CONFerr(CONF_F_NCONF_DUMP_BIO, CONF_R_NO_CONF);
        return 0;
    }

    return conf->meth->dump(conf, out);
}
