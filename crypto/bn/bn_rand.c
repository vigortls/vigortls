/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include <time.h>

#include <openssl/err.h>
#include <openssl/rand.h>

#include "bn_lcl.h"

static int bnrand(int pseudorand, BIGNUM *rnd, int bits, int top, int bottom)
{
    uint8_t *buf = NULL;
    int ret = 0, bit, bytes, mask;

    if (rnd == NULL) {
        BNerr(BN_F_BNRAND, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }

    if (bits == 0) {
        if (top != -1 || bottom != 0)
            goto toosmall;
        BN_zero(rnd);
        return 1;
    }
    if (bits < 0 || (bits == 1 && top > 0))
        goto toosmall;

    bytes = (bits + 7) / 8;
    bit = (bits - 1) % 8;
    mask = 0xff << (bit + 1);

    buf = malloc(bytes);
    if (buf == NULL) {
        BNerr(BN_F_BNRAND, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* make a random number and set the top and bottom bits */

    if (RAND_bytes(buf, bytes) <= 0)
        goto err;

    if (pseudorand == 2) {
        /* generate patterns that are more likely to trigger BN
           library bugs */
        int i;
        uint8_t c;

        for (i = 0; i < bytes; i++) {
            if (RAND_bytes(&c, 1) <= 0)
                goto err;
            if (c >= 128 && i > 0)
                buf[i] = buf[i - 1];
            else if (c < 42)
                buf[i] = 0;
            else if (c < 84)
                buf[i] = 255;
        }
    }

    if (top >= 0) {
        if (top) {
            if (bit == 0) {
                buf[0] = 1;
                buf[1] |= 0x80;
            } else {
                buf[0] |= (3 << (bit - 1));
            }
        } else {
            buf[0] |= (1 << bit);
        }
    }
    buf[0] &= ~mask;
    if (bottom) /* set bottom bit if requested */
        buf[bytes - 1] |= 1;
    if (BN_bin2bn(buf, bytes, rnd) == NULL)
        goto err;
    ret = 1;
err:
    if (buf != NULL) {
        vigortls_zeroize(buf, bytes);
        free(buf);
    }
    bn_check_top(rnd);
    return ret;

toosmall:
    BNerr(BN_F_BNRAND, BN_R_BITS_TOO_SMALL);
    return 0;
}

int BN_rand(BIGNUM *rnd, int bits, int top, int bottom)
{
    return bnrand(0, rnd, bits, top, bottom);
}

int BN_pseudo_rand(BIGNUM *rnd, int bits, int top, int bottom)
{
    return bnrand(1, rnd, bits, top, bottom);
}

int BN_bntest_rand(BIGNUM *rnd, int bits, int top, int bottom)
{
    return bnrand(2, rnd, bits, top, bottom);
}

/* random number r:  0 <= r < range */
static int bn_rand_range(int pseudo, BIGNUM *r, const BIGNUM *range)
{
    int (*bn_rand)(BIGNUM *, int, int, int) = pseudo ? BN_pseudo_rand : BN_rand;
    int n;
    int count = 100;

    if (range->neg || BN_is_zero(range)) {
        BNerr(BN_F_BN_RAND_RANGE, BN_R_INVALID_RANGE);
        return 0;
    }

    n = BN_num_bits(range); /* n > 0 */

    /* BN_is_bit_set(range, n - 1) always holds */

    if (n == 1)
        BN_zero(r);
    else if (!BN_is_bit_set(range, n - 2) && !BN_is_bit_set(range, n - 3)) {
        /* range = 100..._2,
         * so  3*range (= 11..._2)  is exactly one bit longer than  range */
        do {
            if (!bn_rand(r, n + 1, -1, 0))
                return 0;
            /* If  r < 3*range,  use  r := r MOD range
             * (which is either  r, r - range,  or  r - 2*range).
             * Otherwise, iterate once more.
             * Since  3*range = 11..._2, each iteration succeeds with
             * probability >= .75. */
            if (BN_cmp(r, range) >= 0) {
                if (!BN_sub(r, r, range))
                    return 0;
                if (BN_cmp(r, range) >= 0)
                    if (!BN_sub(r, r, range))
                        return 0;
            }

            if (!--count) {
                BNerr(BN_F_BN_RAND_RANGE, BN_R_TOO_MANY_ITERATIONS);
                return 0;
            }

        } while (BN_cmp(r, range) >= 0);
    } else {
        do {
            /* range = 11..._2  or  range = 101..._2 */
            if (!bn_rand(r, n, -1, 0))
                return 0;

            if (!--count) {
                BNerr(BN_F_BN_RAND_RANGE, BN_R_TOO_MANY_ITERATIONS);
                return 0;
            }
        } while (BN_cmp(r, range) >= 0);
    }

    bn_check_top(r);
    return 1;
}

int BN_rand_range(BIGNUM *r, const BIGNUM *range)
{
    return bn_rand_range(0, r, range);
}

int BN_pseudo_rand_range(BIGNUM *r, const BIGNUM *range)
{
    return bn_rand_range(1, r, range);
}
