/*
 * Generated by util/mkerr.pl DO NOT EDIT
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <openssl/err.h>
#include <openssl/bio.h>

/* BEGIN ERROR CODES */
#ifndef OPENSSL_NO_ERR

# define ERR_FUNC(func) ERR_PACK(ERR_LIB_BIO, func, 0)
# define ERR_REASON(reason) ERR_PACK(ERR_LIB_BIO, 0, reason)

static ERR_STRING_DATA BIO_str_functs[] = {
    { ERR_FUNC(BIO_F_ACPT_STATE), "ACPT_STATE" },
    { ERR_FUNC(BIO_F_BIO_ACCEPT), "BIO_ACCEPT" },
    { ERR_FUNC(BIO_F_BIO_BER_GET_HEADER), "BIO_BER_GET_HEADER" },
    { ERR_FUNC(BIO_F_BIO_CALLBACK_CTRL), "BIO_CALLBACK_CTRL" },
    { ERR_FUNC(BIO_F_BIO_CTRL), "BIO_CTRL" },
    { ERR_FUNC(BIO_F_BIO_GETHOSTBYNAME), "BIO_GETHOSTBYNAME" },
    { ERR_FUNC(BIO_F_BIO_GETS), "BIO_GETS" },
    { ERR_FUNC(BIO_F_BIO_GET_ACCEPT_SOCKET), "BIO_GET_ACCEPT_SOCKET" },
    { ERR_FUNC(BIO_F_BIO_GET_HOST_IP), "BIO_GET_HOST_IP" },
    { ERR_FUNC(BIO_F_BIO_GET_PORT), "BIO_GET_PORT" },
    { ERR_FUNC(BIO_F_BIO_MAKE_PAIR), "BIO_MAKE_PAIR" },
    { ERR_FUNC(BIO_F_BIO_NEW), "BIO_NEW" },
    { ERR_FUNC(BIO_F_BIO_NEW_FILE), "BIO_NEW_FILE" },
    { ERR_FUNC(BIO_F_BIO_NEW_MEM_BUF), "BIO_NEW_MEM_BUF" },
    { ERR_FUNC(BIO_F_BIO_NREAD), "BIO_NREAD" },
    { ERR_FUNC(BIO_F_BIO_NREAD0), "BIO_NREAD0" },
    { ERR_FUNC(BIO_F_BIO_NWRITE), "BIO_NWRITE" },
    { ERR_FUNC(BIO_F_BIO_NWRITE0), "BIO_NWRITE0" },
    { ERR_FUNC(BIO_F_BIO_PUTS), "BIO_PUTS" },
    { ERR_FUNC(BIO_F_BIO_READ), "BIO_READ" },
    { ERR_FUNC(BIO_F_BIO_SOCK_INIT), "BIO_SOCK_INIT" },
    { ERR_FUNC(BIO_F_BIO_WRITE), "BIO_WRITE" },
    { ERR_FUNC(BIO_F_BUFFER_CTRL), "BUFFER_CTRL" },
    { ERR_FUNC(BIO_F_CONN_CTRL), "CONN_CTRL" },
    { ERR_FUNC(BIO_F_CONN_STATE), "CONN_STATE" },
    { ERR_FUNC(BIO_F_DGRAM_SCTP_READ), "DGRAM_SCTP_READ" },
    { ERR_FUNC(BIO_F_FILE_CTRL), "FILE_CTRL" },
    { ERR_FUNC(BIO_F_FILE_READ), "FILE_READ" },
    { ERR_FUNC(BIO_F_LINEBUFFER_CTRL), "LINEBUFFER_CTRL" },
    { ERR_FUNC(BIO_F_MEM_READ), "MEM_READ" },
    { ERR_FUNC(BIO_F_MEM_WRITE), "MEM_WRITE" },
    { ERR_FUNC(BIO_F_SSL_NEW), "SSL_NEW" },
    { ERR_FUNC(BIO_F_WSASTARTUP), "WSASTARTUP" },
    { 0, NULL }
};

static ERR_STRING_DATA BIO_str_reasons[] = {
    { ERR_REASON(BIO_R_ACCEPT_ERROR), "accept error" },
    { ERR_REASON(BIO_R_BAD_FOPEN_MODE), "bad fopen mode" },
    { ERR_REASON(BIO_R_BAD_HOSTNAME_LOOKUP), "bad hostname lookup" },
    { ERR_REASON(BIO_R_BROKEN_PIPE), "broken pipe" },
    { ERR_REASON(BIO_R_CONNECT_ERROR), "connect error" },
    { ERR_REASON(BIO_R_EOF_ON_MEMORY_BIO), "eof on memory bio" },
    { ERR_REASON(BIO_R_ERROR_SETTING_NBIO), "error setting nbio" },
    { ERR_REASON(BIO_R_ERROR_SETTING_NBIO_ON_ACCEPTED_SOCKET),
     "error setting nbio on accepted socket" },
    { ERR_REASON(BIO_R_ERROR_SETTING_NBIO_ON_ACCEPT_SOCKET),
     "error setting nbio on accept socket" },
    { ERR_REASON(BIO_R_GETHOSTBYNAME_ADDR_IS_NOT_AF_INET),
     "gethostbyname addr is not af inet" },
    { ERR_REASON(BIO_R_INVALID_ARGUMENT), "invalid argument" },
    { ERR_REASON(BIO_R_INVALID_IP_ADDRESS), "invalid ip address" },
    { ERR_REASON(BIO_R_IN_USE), "in use" },
    { ERR_REASON(BIO_R_KEEPALIVE), "keepalive" },
    { ERR_REASON(BIO_R_NBIO_CONNECT_ERROR), "nbio connect error" },
    { ERR_REASON(BIO_R_NO_ACCEPT_PORT_SPECIFIED), "no accept port specified" },
    { ERR_REASON(BIO_R_NO_HOSTNAME_SPECIFIED), "no hostname specified" },
    { ERR_REASON(BIO_R_NO_PORT_DEFINED), "no port defined" },
    { ERR_REASON(BIO_R_NO_PORT_SPECIFIED), "no port specified" },
    { ERR_REASON(BIO_R_NO_SUCH_FILE), "no such file" },
    { ERR_REASON(BIO_R_NULL_PARAMETER), "null parameter" },
    { ERR_REASON(BIO_R_TAG_MISMATCH), "tag mismatch" },
    { ERR_REASON(BIO_R_UNABLE_TO_BIND_SOCKET), "unable to bind socket" },
    { ERR_REASON(BIO_R_UNABLE_TO_CREATE_SOCKET), "unable to create socket" },
    { ERR_REASON(BIO_R_UNABLE_TO_LISTEN_SOCKET), "unable to listen socket" },
    { ERR_REASON(BIO_R_UNINITIALIZED), "uninitialized" },
    { ERR_REASON(BIO_R_UNSUPPORTED_METHOD), "unsupported method" },
    { ERR_REASON(BIO_R_WRITE_TO_READ_ONLY_BIO), "write to read only bio" },
    { ERR_REASON(BIO_R_WSASTARTUP), "wsastartup" },
    { 0, NULL }
};

#endif

void ERR_load_BIO_strings(void)
{
#ifndef OPENSSL_NO_ERR
    if (ERR_func_error_string(BIO_str_functs[0].error) == NULL) {
        ERR_load_strings(0, BIO_str_functs);
        ERR_load_strings(0, BIO_str_reasons);
    }
#endif
}
