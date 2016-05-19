/*
 * Copyright 1999-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <openssl/bn.h>
#include <openssl/err.h>
#include <openssl/rsa.h>

int RSA_check_key(const RSA *key)
{
    BIGNUM *i, *j, *k, *l, *m;
    BN_CTX *ctx;
    int r;
    int ret = 1;

    if (!key->p || !key->q || !key->n || !key->e || !key->d) {
        RSAerr(RSA_F_RSA_CHECK_KEY, RSA_R_VALUE_MISSING);
        return 0;
    }

    i = BN_new();
    j = BN_new();
    k = BN_new();
    l = BN_new();
    m = BN_new();
    ctx = BN_CTX_new();
    if (i == NULL || j == NULL || k == NULL || l == NULL || m == NULL || ctx == NULL) {
        ret = -1;
        RSAerr(RSA_F_RSA_CHECK_KEY, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* p prime? */
    r = BN_is_prime_ex(key->p, BN_prime_checks, NULL, NULL);
    if (r != 1) {
        ret = r;
        if (r != 0)
            goto err;
        RSAerr(RSA_F_RSA_CHECK_KEY, RSA_R_P_NOT_PRIME);
    }

    /* q prime? */
    r = BN_is_prime_ex(key->q, BN_prime_checks, NULL, NULL);
    if (r != 1) {
        ret = r;
        if (r != 0)
            goto err;
        RSAerr(RSA_F_RSA_CHECK_KEY, RSA_R_Q_NOT_PRIME);
    }

    /* n = p*q? */
    r = BN_mul(i, key->p, key->q, ctx);
    if (!r) {
        ret = -1;
        goto err;
    }

    if (BN_cmp(i, key->n) != 0) {
        ret = 0;
        RSAerr(RSA_F_RSA_CHECK_KEY, RSA_R_N_DOES_NOT_EQUAL_P_Q);
    }

    /* d*e = 1  mod lcm(p-1,q-1)? */

    r = BN_sub(i, key->p, BN_value_one());
    if (!r) {
        ret = -1;
        goto err;
    }
    r = BN_sub(j, key->q, BN_value_one());
    if (!r) {
        ret = -1;
        goto err;
    }

    /* now compute k = lcm(i,j) */
    r = BN_mul(l, i, j, ctx);
    if (!r) {
        ret = -1;
        goto err;
    }
    r = BN_gcd(m, i, j, ctx);
    if (!r) {
        ret = -1;
        goto err;
    }
    r = BN_div(k, NULL, l, m, ctx); /* remainder is 0 */
    if (!r) {
        ret = -1;
        goto err;
    }

    r = BN_mod_mul(i, key->d, key->e, k, ctx);
    if (!r) {
        ret = -1;
        goto err;
    }

    if (!BN_is_one(i)) {
        ret = 0;
        RSAerr(RSA_F_RSA_CHECK_KEY, RSA_R_D_E_NOT_CONGRUENT_TO_1);
    }

    if (key->dmp1 != NULL && key->dmq1 != NULL && key->iqmp != NULL) {
        /* dmp1 = d mod (p-1)? */
        r = BN_sub(i, key->p, BN_value_one());
        if (!r) {
            ret = -1;
            goto err;
        }

        r = BN_mod(j, key->d, i, ctx);
        if (!r) {
            ret = -1;
            goto err;
        }

        if (BN_cmp(j, key->dmp1) != 0) {
            ret = 0;
            RSAerr(RSA_F_RSA_CHECK_KEY, RSA_R_DMP1_NOT_CONGRUENT_TO_D);
        }

        /* dmq1 = d mod (q-1)? */
        r = BN_sub(i, key->q, BN_value_one());
        if (!r) {
            ret = -1;
            goto err;
        }

        r = BN_mod(j, key->d, i, ctx);
        if (!r) {
            ret = -1;
            goto err;
        }

        if (BN_cmp(j, key->dmq1) != 0) {
            ret = 0;
            RSAerr(RSA_F_RSA_CHECK_KEY, RSA_R_DMQ1_NOT_CONGRUENT_TO_D);
        }

        /* iqmp = q^-1 mod p? */
        if (!BN_mod_inverse(i, key->q, key->p, ctx)) {
            ret = -1;
            goto err;
        }

        if (BN_cmp(i, key->iqmp) != 0) {
            ret = 0;
            RSAerr(RSA_F_RSA_CHECK_KEY, RSA_R_IQMP_NOT_INVERSE_OF_Q);
        }
    }

err:
    BN_free(i);
    BN_free(j);
    BN_free(k);
    BN_free(l);
    BN_free(m);
    BN_CTX_free(ctx);
    return (ret);
}
