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

#include <unistd.h>

#include <win32netcompat.h>

#include <openssl/bio.h>

int BIO_fd_should_retry(int s);

static int fd_new(BIO *bi)
{
    bi->init = 0;
    bi->num = -1;
    bi->ptr = NULL;
    return (1);
}

static int fd_free(BIO *a)
{
    if (a == NULL)
        return (0);
    if (a->shutdown) {
        if (a->init) {
            close(a->num);
        }
        a->init = 0;
    }
    return (1);
}

static int fd_read(BIO *b, char *out, int outl)
{
    int ret = 0;

    if (out != NULL) {
        errno = 0;
        ret = read(b->num, out, outl);
        BIO_clear_retry_flags(b);
        if (ret <= 0) {
            if (BIO_fd_should_retry(ret))
                BIO_set_retry_read(b);
        }
    }
    return (ret);
}

static int fd_write(BIO *b, const char *in, int inl)
{
    int ret;
    errno = 0;
    ret = write(b->num, in, inl);
    BIO_clear_retry_flags(b);
    if (ret <= 0) {
        if (BIO_fd_should_retry(ret))
            BIO_set_retry_write(b);
    }
    return (ret);
}

static long fd_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    long ret = 1;
    int *ip;

    switch (cmd) {
        case BIO_CTRL_RESET:
            num = 0;
        case BIO_C_FILE_SEEK:
            ret = (long)lseek(b->num, num, 0);
            break;
        case BIO_C_FILE_TELL:
        case BIO_CTRL_INFO:
            ret = (long)lseek(b->num, 0, 1);
            break;
        case BIO_C_SET_FD:
            fd_free(b);
            b->num = *((int *)ptr);
            b->shutdown = (int)num;
            b->init = 1;
            break;
        case BIO_C_GET_FD:
            if (b->init) {
                ip = (int *)ptr;
                if (ip != NULL)
                    *ip = b->num;
                ret = b->num;
            } else
                ret = -1;
            break;
        case BIO_CTRL_GET_CLOSE:
            ret = b->shutdown;
            break;
        case BIO_CTRL_SET_CLOSE:
            b->shutdown = (int)num;
            break;
        case BIO_CTRL_PENDING:
        case BIO_CTRL_WPENDING:
            ret = 0;
            break;
        case BIO_CTRL_DUP:
        case BIO_CTRL_FLUSH:
            ret = 1;
            break;
        default:
            ret = 0;
            break;
    }
    return (ret);
}

static int fd_puts(BIO *bp, const char *str)
{
    int n, ret;

    n = strlen(str);
    ret = fd_write(bp, str, n);
    return (ret);
}

static int fd_gets(BIO *bp, char *buf, int size)
{
    int ret = 0;
    char *ptr = buf;
    char *end = buf + size - 1;

    while ((ptr < end) && (fd_read(bp, ptr, 1) > 0) && (ptr[0] != '\n'))
        ptr++;

    ptr[0] = '\0';

    if (buf[0] != '\0')
        ret = strlen(buf);
    return (ret);
}

int BIO_fd_should_retry(int i)
{
    int err;

    if ((i == 0) || (i == -1)) {
        err = errno;

        return (BIO_fd_non_fatal_error(err));
    }
    return (0);
}

int BIO_fd_non_fatal_error(int err)
{
    switch (err) {

#ifdef EWOULDBLOCK
#ifdef WSAEWOULDBLOCK
#if WSAEWOULDBLOCK != EWOULDBLOCK
        case EWOULDBLOCK:
#endif
#else
        case EWOULDBLOCK:
#endif
#endif

#if defined(ENOTCONN)
        case ENOTCONN:
#endif

#ifdef EINTR
        case EINTR:
#endif

#ifdef EAGAIN
#if EWOULDBLOCK != EAGAIN
        case EAGAIN:
#endif
#endif

#ifdef EPROTO
        case EPROTO:
#endif

#ifdef EINPROGRESS
        case EINPROGRESS:
#endif

#ifdef EALREADY
        case EALREADY:
#endif
            return (1);
        /* break; */
        default:
            break;
    }
    return (0);
}

static BIO_METHOD methods_fdp = {
    .type    = BIO_TYPE_FD,
    .name    = "file descriptor",
    .bwrite  = fd_write,
    .bread   = fd_read,
    .bputs   = fd_puts,
    .bgets   = fd_gets,
    .ctrl    = fd_ctrl,
    .create  = fd_new,
    .destroy = fd_free,
};

BIO_METHOD *BIO_s_fd(void)
{
    return (&methods_fdp);
}

BIO *BIO_new_fd(int fd, int close_flag)
{
    BIO *ret;
    ret = BIO_new(BIO_s_fd());
    if (ret == NULL)
        return (NULL);
    BIO_set_fd(ret, fd, close_flag);
    return (ret);
}
