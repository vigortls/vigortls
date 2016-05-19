/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/err.h>

static int mem_new(BIO *bi)
{
    BUF_MEM *b;

    if ((b = BUF_MEM_new()) == NULL)
        return (0);
    bi->shutdown = 1;
    bi->init = 1;
    bi->num = -1;
    bi->ptr = (char *)b;
    return (1);
}

static int mem_free(BIO *a)
{
    if (a == NULL)
        return (0);
    if (a->shutdown) {
        if ((a->init) && (a->ptr != NULL)) {
            BUF_MEM *b;
            b = (BUF_MEM *)a->ptr;
            if (a->flags & BIO_FLAGS_MEM_RDONLY)
                b->data = NULL;
            BUF_MEM_free(b);
            a->ptr = NULL;
        }
    }
    return (1);
}

static int mem_read(BIO *b, char *out, int outl)
{
    int ret = -1;
    BUF_MEM *bm;

    bm = (BUF_MEM *)b->ptr;
    BIO_clear_retry_flags(b);
    ret = (outl >= 0 && (size_t)outl > bm->length) ? (int)bm->length : outl;
    if ((out != NULL) && (ret > 0)) {
        memcpy(out, bm->data, ret);
        bm->length -= ret;
        if (b->flags & BIO_FLAGS_MEM_RDONLY)
            bm->data += ret;
        else {
            memmove(&(bm->data[0]), &(bm->data[ret]), bm->length);
        }
    } else if (bm->length == 0) {
        ret = b->num;
        if (ret != 0)
            BIO_set_retry_read(b);
    }
    return (ret);
}

static int mem_write(BIO *b, const char *in, int inl)
{
    int ret = -1;
    int blen;
    BUF_MEM *bm;

    bm = (BUF_MEM *)b->ptr;
    if (in == NULL) {
        BIOerr(BIO_F_MEM_WRITE, BIO_R_NULL_PARAMETER);
        goto end;
    }

    if (b->flags & BIO_FLAGS_MEM_RDONLY) {
        BIOerr(BIO_F_MEM_WRITE, BIO_R_WRITE_TO_READ_ONLY_BIO);
        goto end;
    }

    BIO_clear_retry_flags(b);
    blen = bm->length;
    if (BUF_MEM_grow_clean(bm, blen + inl) != (blen + inl))
        goto end;
    memcpy(&(bm->data[blen]), in, inl);
    ret = inl;
end:
    return (ret);
}

static long mem_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    long ret = 1;
    char **pptr;

    BUF_MEM *bm = (BUF_MEM *)b->ptr;

    switch (cmd) {
        case BIO_CTRL_RESET:
            if (bm->data != NULL) {
                /* For read only case reset to the start again */
                if (b->flags & BIO_FLAGS_MEM_RDONLY) {
                    bm->data -= bm->max - bm->length;
                    bm->length = bm->max;
                } else {
                    memset(bm->data, 0, bm->max);
                    bm->length = 0;
                }
            }
            break;
        case BIO_CTRL_EOF:
            ret = (long)(bm->length == 0);
            break;
        case BIO_C_SET_BUF_MEM_EOF_RETURN:
            b->num = (int)num;
            break;
        case BIO_CTRL_INFO:
            ret = (long)bm->length;
            if (ptr != NULL) {
                pptr = (char **)ptr;
                *pptr = (char *)&(bm->data[0]);
            }
            break;
        case BIO_C_SET_BUF_MEM:
            mem_free(b);
            b->shutdown = (int)num;
            b->ptr = ptr;
            break;
        case BIO_C_GET_BUF_MEM_PTR:
            if (ptr != NULL) {
                pptr = (char **)ptr;
                *pptr = (char *)bm;
            }
            break;
        case BIO_CTRL_GET_CLOSE:
            ret = (long)b->shutdown;
            break;
        case BIO_CTRL_SET_CLOSE:
            b->shutdown = (int)num;
            break;

        case BIO_CTRL_WPENDING:
            ret = 0L;
            break;
        case BIO_CTRL_PENDING:
            ret = (long)bm->length;
            break;
        case BIO_CTRL_DUP:
        case BIO_CTRL_FLUSH:
            ret = 1;
            break;
        case BIO_CTRL_PUSH:
        case BIO_CTRL_POP:
        default:
            ret = 0;
            break;
    }
    return (ret);
}

static int mem_gets(BIO *bp, char *buf, int size)
{
    int i, j;
    int ret = -1;
    char *p;
    BUF_MEM *bm = (BUF_MEM *)bp->ptr;

    BIO_clear_retry_flags(bp);
    j = bm->length;
    if ((size - 1) < j)
        j = size - 1;
    if (j <= 0) {
        *buf = '\0';
        return 0;
    }
    p = bm->data;
    for (i = 0; i < j; i++) {
        if (p[i] == '\n') {
            i++;
            break;
        }
    }

    /*
     * i is now the max num of bytes to copy, either j or up to
     * and including the first newline
     */

    i = mem_read(bp, buf, i);
    if (i > 0)
        buf[i] = '\0';
    ret = i;
    return (ret);
}

static int mem_puts(BIO *bp, const char *str)
{
    int n, ret;

    n = strlen(str);
    ret = mem_write(bp, str, n);
    /* memory semantics is that it will always work */
    return (ret);
}

static BIO_METHOD mem_method = {
    .type    = BIO_TYPE_MEM,
    .name    = "memory buffer",
    .bwrite  = mem_write,
    .bread   = mem_read,
    .bputs   = mem_puts,
    .bgets   = mem_gets,
    .ctrl    = mem_ctrl,
    .create  = mem_new,
    .destroy = mem_free
};

BIO_METHOD *BIO_s_mem(void)
{
    return (&mem_method);
}

BIO *BIO_new_mem_buf(void *buf, int len)
{
    BIO *ret;
    BUF_MEM *b;
    size_t sz;

    if (!buf) {
        BIOerr(BIO_F_BIO_NEW_MEM_BUF, BIO_R_NULL_PARAMETER);
        return NULL;
    }
    sz = (len < 0) ? strlen(buf) : (size_t)len;
    if (!(ret = BIO_new(BIO_s_mem())))
        return NULL;
    b = (BUF_MEM *)ret->ptr;
    b->data = buf;
    b->length = sz;
    b->max = sz;
    ret->flags |= BIO_FLAGS_MEM_RDONLY;
    /* Since this is static data retrying wont help */
    ret->num = 0;
    return ret;
}
