/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#define NO_SHUTDOWN

#include <sys/types.h>
#include <sys/socket.h>

#include <stdcompat.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>

#include "apps.h"

#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>

#include "s_apps.h"

#define SSL_CONNECT_NAME "localhost:4433"

#define BUFSIZZ 1024 * 10

#define MYBUFSIZ 1024 * 8

#undef min
#undef max
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

#define SECONDS 30
#define SECONDSSTR "30"
extern int verify_depth;
extern int verify_error;

static SSL *doConnection(SSL *scon, const char *host, SSL_CTX *ctx);

typedef enum OPTION_choice {
    OPT_ERR = -1,
    OPT_EOF = 0,
    OPT_HELP,
    OPT_CONNECT,
    OPT_CIPHER,
    OPT_CERT,
    OPT_KEY,
    OPT_CAPATH,
    OPT_CAFILE,
    OPT_NEW,
    OPT_REUSE,
    OPT_BUGS,
    OPT_VERIFY,
    OPT_TIME,
    OPT_WWW
} OPTION_CHOICE;

OPTIONS s_time_options[] = {
    { "help", OPT_HELP, '-', "Display this summary" },
    { "connect", OPT_CONNECT, 's',
      "Where to connect as post:port (default is " SSL_CONNECT_NAME ")" },
    { "cipher", OPT_CIPHER, 's', "Cipher to use, see 'openssl ciphers'" },
    { "cert", OPT_CERT, '<', "Cert file to use, PEM format assumed" },
    { "key", OPT_KEY, '<', "File with key, PEM; default is -cert file" },
    { "CApath", OPT_CAPATH, '/', "PEM format directory of CA's" },
    { "cafile", OPT_CAFILE, '<', "PEM format file of CA's" },
    { "new", OPT_NEW, '-', "Just time new connections" },
    { "reuse", OPT_REUSE, '-', "Just time connection reuse" },
    { "bugs", OPT_BUGS, '-', "Turn on SSL bug compatibility" },
    { "verify", OPT_VERIFY, 'p', "Turn on peer certificate verification, set depth" },
    { "time", OPT_TIME, 'p', "Sf seconds to collect data, default" SECONDSSTR },
    { "www", OPT_WWW, 's', "Fetch specified page from the site" },
    { NULL }
};

#define START 0
#define STOP 1

static double tm_Time_F(int s)
{
    return app_tminterval(s, 1);
}

int s_time_main(int argc, char **argv)
{
    char buf[1024 * 8];
    SSL *scon = NULL;
    SSL_CTX *ctx = NULL;
    const SSL_METHOD *meth = NULL;
    char *CApath = NULL, *CAfile = NULL, *cipher = NULL, *www_path = NULL;
    char *host = (char *)SSL_CONNECT_NAME, *certfile = NULL, *keyfile = NULL, *prog;
    double totalTime = 0.0;
    int maxtime = SECONDS, nConn = 0, perform = 3, ret = 1, i, st_bugs = 0, ver;
    long bytes_read = 0, finishtime = 0;
    OPTION_CHOICE o;

    meth = SSLv23_client_method();
    verify_depth = 0;
    verify_error = X509_V_OK;

    prog = opt_init(argc, argv, s_time_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
            case OPT_EOF:
            case OPT_ERR:
            opthelp:
                BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
                goto end;
            case OPT_HELP:
                opt_help(s_time_options);
                ret = 0;
                goto end;
            case OPT_CONNECT:
                host = opt_arg();
                break;
            case OPT_REUSE:
                perform = 2;
                break;
            case OPT_NEW:
                perform = 1;
                break;
            case OPT_VERIFY:
                if (!opt_int(opt_arg(), &verify_depth))
                    goto opthelp;
                BIO_printf(bio_err, "%s: verify depth is %d\n", prog, verify_depth);
                break;
            case OPT_CERT:
                certfile = opt_arg();
                break;
            case OPT_KEY:
                keyfile = opt_arg();
                break;
            case OPT_CAPATH:
                CApath = opt_arg();
                break;
            case OPT_CAFILE:
                CAfile = opt_arg();
                break;
            case OPT_CIPHER:
                cipher = opt_arg();
                break;
            case OPT_BUGS:
                st_bugs = 1;
                break;
            case OPT_TIME:
                if (!opt_int(opt_arg(), &maxtime))
                    goto opthelp;
                break;
            case OPT_WWW:
                www_path = opt_arg();
                if (strlen(www_path) > MYBUFSIZ - 100) {
                    BIO_printf(bio_err, "%s: -www option too long\n", prog);
                    goto end;
                }
                break;
        }
    }
    argc = opt_num_rest();
    argv = opt_rest();

    if (cipher == NULL)
        cipher = getenv("SSL_CIPHER");
    if (cipher == NULL) {
        fprintf(stderr, "No CIPHER specified\n");
        goto end;
    }

    if ((ctx = SSL_CTX_new(meth)) == NULL)
        goto end;

    SSL_CTX_set_quiet_shutdown(ctx, 1);

    if (st_bugs)
        SSL_CTX_set_options(ctx, SSL_OP_ALL);
    if (!SSL_CTX_set_cipher_list(ctx, cipher))
        goto end;
    if (!set_cert_stuff(ctx, certfile, keyfile))
        goto end;

    if ((!SSL_CTX_load_verify_locations(ctx, CAfile, CApath)) ||
        (!SSL_CTX_set_default_verify_paths(ctx))) {
        /*
         * BIO_printf(bio_err, "error setting default verify locations\n");
         */
        ERR_print_errors(bio_err);
        /* goto end; */
    }

    if (!(perform & 1))
        goto next;
    printf("Collecting connection statistics for %d seconds\n", maxtime);

    /* Loop and time how long it takes to make connections */

    bytes_read = 0;
    finishtime = (long)time(NULL) + maxtime;
    tm_Time_F(START);
    for (;;) {
        if (finishtime < (long)time(NULL))
            break;

        if ((scon = doConnection(NULL, host, ctx)) == NULL)
            goto end;

        if (www_path != NULL) {
            snprintf(buf, sizeof buf, "GET %s HTTP/1.0\r\n\r\n", www_path);
            if (SSL_write(scon, buf, strlen(buf)) <= 0)
                goto end;
            while ((i = SSL_read(scon, buf, sizeof(buf))) > 0)
                bytes_read += i;
        }
#ifdef NO_SHUTDOWN
        SSL_set_shutdown(scon, SSL_SENT_SHUTDOWN | SSL_RECEIVED_SHUTDOWN);
#else
        SSL_shutdown(scon);
#endif
        shutdown(SSL_get_fd(scon), SHUT_RDWR);
        close(SSL_get_fd(scon));

        nConn += 1;
        if (SSL_session_reused(scon))
            ver = 'r';
        else {
            ver = SSL_version(scon);
            if (ver == TLS1_VERSION)
                ver = 't';
            else if (ver == SSL3_VERSION)
                ver = '3';
            else
                ver = '*';
        }
        fputc(ver, stdout);
        fflush(stdout);

        SSL_free(scon);
        scon = NULL;
    }
    totalTime += tm_Time_F(STOP); /* Add the time for this iteration */

    i = (int)((long)time(NULL) - finishtime + maxtime);
    printf("\n\n%d connections in %.2fs; %.2f connections/user sec, bytes read "
           "%ld\n",
           nConn, totalTime, ((double)nConn / totalTime), bytes_read);
    printf("%d connections in %ld real seconds, %ld bytes read per connection\n", nConn,
           (long)time(NULL) - finishtime + maxtime, bytes_read / nConn);

/*
 * Now loop and time connections using the same session id over and over
 */

next:
    if (!(perform & 2))
        goto end;
    printf("\n\nNow timing with session id reuse.\n");

    /* Get an SSL object so we can reuse the session id */
    if ((scon = doConnection(NULL, host, ctx)) == NULL) {
        fprintf(stderr, "Unable to get connection\n");
        goto end;
    }

    if (www_path != NULL) {
        snprintf(buf, sizeof buf, "GET %s HTTP/1.0\r\n\r\n", www_path);
        if (SSL_write(scon, buf, strlen(buf)) <= 0)
            goto end;
        while (SSL_read(scon, buf, sizeof(buf)) > 0)
            continue;
    }
#ifdef NO_SHUTDOWN
    SSL_set_shutdown(scon, SSL_SENT_SHUTDOWN | SSL_RECEIVED_SHUTDOWN);
#else
    SSL_shutdown(scon);
#endif
    shutdown(SSL_get_fd(scon), SHUT_RDWR);
    close(SSL_get_fd(scon));

    nConn = 0;
    totalTime = 0.0;

    finishtime = (long)time(NULL) + maxtime;

    printf("starting\n");
    bytes_read = 0;
    tm_Time_F(START);

    for (;;) {
        if (finishtime < (long)time(NULL))
            break;

        if ((doConnection(scon, host, ctx)) == NULL)
            goto end;

        if (www_path) {
            snprintf(buf, sizeof buf, "GET %s HTTP/1.0\r\n\r\n", www_path);
            if (SSL_write(scon, buf, strlen(buf)) <= 0)
                goto end;
            while ((i = SSL_read(scon, buf, sizeof(buf))) > 0)
                bytes_read += i;
        }
#ifdef NO_SHUTDOWN
        SSL_set_shutdown(scon, SSL_SENT_SHUTDOWN | SSL_RECEIVED_SHUTDOWN);
#else
        SSL_shutdown(scon);
#endif
        shutdown(SSL_get_fd(scon), SHUT_RDWR);
        close(SSL_get_fd(scon));

        nConn += 1;
        if (SSL_session_reused(scon))
            ver = 'r';
        else {
            ver = SSL_version(scon);
            if (ver == TLS1_VERSION)
                ver = 't';
            else if (ver == SSL3_VERSION)
                ver = '3';
            else
                ver = '*';
        }
        fputc(ver, stdout);
        fflush(stdout);
    }
    totalTime += tm_Time_F(STOP); /* Add the time for this iteration */

    printf("\n\n%d connections in %.2fs; %.2f connections/user sec, bytes read "
           "%ld\n",
           nConn, totalTime, ((double)nConn / totalTime), bytes_read);
    printf("%d connections in %ld real seconds, %ld bytes read per connection\n", nConn,
           (long)time(NULL) - finishtime + maxtime, bytes_read / nConn);

    ret = 0;

end:
    SSL_free(scon);
    SSL_CTX_free(ctx);
    return (ret);
}

/*-
 * doConnection - make a connection
 */
static SSL *doConnection(SSL *scon, const char *host, SSL_CTX *ctx)
{
    struct pollfd pfd[1];
    BIO *conn;
    SSL *serverCon;
    int i;

    if ((conn = BIO_new(BIO_s_connect())) == NULL)
        return (NULL);

    BIO_set_conn_hostname(conn, host);

    if (scon == NULL)
        serverCon = SSL_new(ctx);
    else {
        serverCon = scon;
        SSL_set_connect_state(serverCon);
    }

    SSL_set_bio(serverCon, conn, conn);

    /* ok, lets connect */
    for (;;) {
        i = SSL_connect(serverCon);
        if (BIO_sock_should_retry(i)) {
            BIO_printf(bio_err, "DELAY\n");

            i = SSL_get_fd(serverCon);
            pfd[0].fd = i;
            pfd[0].events = POLLIN;
            poll(pfd, 1, -1);
            continue;
        }
        break;
    }
    if (i <= 0) {
        BIO_printf(bio_err, "ERROR\n");
        if (verify_error != X509_V_OK)
            BIO_printf(bio_err, "verify error:%s\n",
                       X509_verify_cert_error_string(verify_error));
        else
            ERR_print_errors(bio_err);
        if (scon == NULL)
            SSL_free(serverCon);
        return NULL;
    }

    return serverCon;
}
