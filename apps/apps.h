/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_APPS_H
#define HEADER_APPS_H

#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/lhash.h>
#include <openssl/conf.h>
#include <openssl/txt_db.h>
#ifndef OPENSSL_NO_ENGINE
#include <openssl/engine.h>
#endif
#ifndef OPENSSL_NO_OCSP
#include <openssl/ocsp.h>
#endif
#include <openssl/ossl_typ.h>

extern CONF *config;
extern char *default_config_file;
extern BIO *bio_in;
extern BIO *bio_out;
extern BIO *bio_err;
BIO *dup_bio_in(void);
BIO *dup_bio_out(void);
BIO *bio_open_default(const char *filename, const char *mode);
void unbuffer(FILE *fp);

/* Often used in calls to bio_open_default. */
#define RB(xformat) ((xformat) == FORMAT_ASN1 ? "rb" : "r")
#define WB(xformat) ((xformat) == FORMAT_ASN1 ? "wb" : "w")

/*
 * Common verification options.
 */
#define OPT_V_ENUM                                                                 \
    OPT_V__FIRST = 2000, OPT_V_POLICY, OPT_V_PURPOSE, OPT_V_VERIFY_NAME,           \
    OPT_V_VERIFY_DEPTH, OPT_V_ATTIME,                                              \
    OPT_V_IGNORE_CRITICAL, OPT_V_ISSUER_CHECKS, OPT_V_CRL_CHECK,  \
    OPT_V_CRL_CHECK_ALL, OPT_V_POLICY_CHECK, OPT_V_EXPLICIT_POLICY,                \
    OPT_V_INHIBIT_ANY, OPT_V_INHIBIT_MAP, OPT_V_X509_STRICT, OPT_V_EXTENDED_CRL,   \
    OPT_V_USE_DELTAS, OPT_V_POLICY_PRINT, OPT_V_CHECK_SS_SIG, OPT_V_PARTIAL_CHAIN, \
    OPT_V__LAST

#define OPT_V_OPTIONS                                                              \
        { "policy", OPT_V_POLICY, 's' },                                           \
        { "purpose", OPT_V_PURPOSE, 's' },                                         \
        { "verify_name", OPT_V_VERIFY_NAME, 's' },                                 \
        { "verify_depth", OPT_V_VERIFY_DEPTH, 'p' },                               \
        { "attime", OPT_V_ATTIME, 'p' },                                           \
        { "ignore_critical", OPT_V_IGNORE_CRITICAL, '-' },                         \
        { "issuer_checks", OPT_V_ISSUER_CHECKS, '-' },                             \
        { "crl_check", OPT_V_CRL_CHECK, '-',                                       \
          "Check that peer cert has not been revoked" },                           \
        { "crl_check_all", OPT_V_CRL_CHECK_ALL, '-',                               \
          "Also check all certs in the chain" },                                   \
        { "policy_check", OPT_V_POLICY_CHECK, '-' },                               \
        { "explicit_policy", OPT_V_EXPLICIT_POLICY, '-' },                         \
        { "inhibit_any", OPT_V_INHIBIT_ANY, '-' },                                 \
        { "inhibit_map", OPT_V_INHIBIT_MAP, '-' },                                 \
        { "x509_strict", OPT_V_X509_STRICT, '-' },                                 \
        { "extended_crl", OPT_V_EXTENDED_CRL, '-' },                               \
        { "use_deltas", OPT_V_USE_DELTAS, '-' },                                   \
        { "policy_print", OPT_V_POLICY_PRINT, '-' },                               \
        { "check_ss_sig", OPT_V_CHECK_SS_SIG, '-' },                               \
        { "partial_chain", OPT_V_PARTIAL_CHAIN, '-' }

#define OPT_V_CASES                                                                \
    OPT_V__FIRST:                                                                  \
    case OPT_V__LAST:                                                              \
        break;                                                                     \
    case OPT_V_POLICY:                                                             \
    case OPT_V_PURPOSE:                                                            \
    case OPT_V_VERIFY_NAME:                                                        \
    case OPT_V_VERIFY_DEPTH:                                                       \
    case OPT_V_ATTIME:                                                             \
    case OPT_V_IGNORE_CRITICAL:                                                    \
    case OPT_V_ISSUER_CHECKS:                                                      \
    case OPT_V_CRL_CHECK:                                                          \
    case OPT_V_CRL_CHECK_ALL:                                                      \
    case OPT_V_POLICY_CHECK:                                                       \
    case OPT_V_EXPLICIT_POLICY:                                                    \
    case OPT_V_INHIBIT_ANY:                                                        \
    case OPT_V_INHIBIT_MAP:                                                        \
    case OPT_V_X509_STRICT:                                                        \
    case OPT_V_EXTENDED_CRL:                                                       \
    case OPT_V_USE_DELTAS:                                                         \
    case OPT_V_POLICY_PRINT:                                                       \
    case OPT_V_CHECK_SS_SIG:                                                       \
    case OPT_V_PARTIAL_CHAIN

/*
 * Common SSL options.
 * Any changes here must be coordinated with ../ssl/ssl_conf.c
 */
#define OPT_S_ENUM                                                                 \
    OPT_S__FIRST = 3000, OPT_S_NOSSL3, OPT_S_NOTLS1, OPT_S_NOTLS1_1,               \
    OPT_S_NOTLS1_2, OPT_S_BUGS, OPT_S_NOCOMP, OPT_S_ECDHSINGLE, OPT_S_NOTICKET,    \
    OPT_S_SERVERPREF, OPT_S_LEGACYRENEG, OPT_S_LEGACYCONN, OPT_S_ONRESUMP,         \
    OPT_S_NOLEGACYCONN, OPT_S_STRICT, OPT_S_SIGALGS, OPT_S_CLIENTSIGALGS,          \
    OPT_S_CURVES, OPT_S_NAMEDCURVE, OPT_S_CIPHER, OPT_S_DHPARAM, OPT_S_DEBUGBROKE, \
    OPT_S__LAST

#define OPT_S_OPTIONS                                                              \
    {                                                                              \
        "no_ssl3", OPT_S_NOSSL3, '-'                                               \
    }                                                                              \
    , { "no_tls1", OPT_S_NOTLS1, '-' }, { "no_tls1_1", OPT_S_NOTLS1_1, '-' },      \
        { "no_tls1_2", OPT_S_NOTLS1_2, '-' }, { "bugs", OPT_S_BUGS, '-' },         \
        { "no_comp", OPT_S_NOCOMP, '-' },                                          \
        { "ecdh_single", OPT_S_ECDHSINGLE, '-' },                                  \
        { "no_ticket", OPT_S_NOTICKET, '-' },                                      \
        { "serverpref", OPT_S_SERVERPREF, '-' },                                   \
        { "legacy_renegotiation", OPT_S_LEGACYRENEG, '-' },                        \
        { "legacy_server_connect", OPT_S_LEGACYCONN, '-' },                        \
        { "no_resumption_on_reneg", OPT_S_ONRESUMP, '-' },                         \
        { "no_legacy_server_connect", OPT_S_NOLEGACYCONN, '-' },                   \
        { "strict", OPT_S_STRICT, '-' },                                           \
        {                                                                          \
          "sigalgs", OPT_S_SIGALGS, 's',                                           \
        },                                                                         \
        {                                                                          \
          "client_sigalgs", OPT_S_CLIENTSIGALGS, 's',                              \
        },                                                                         \
        {                                                                          \
          "curves", OPT_S_CURVES, 's',                                             \
        },                                                                         \
        {                                                                          \
          "named_curve", OPT_S_NAMEDCURVE, 's',                                    \
        },                                                                         \
        {                                                                          \
          "cipher", OPT_S_CIPHER, 's',                                             \
        },                                                                         \
        { "dhparam", OPT_S_DHPARAM, '<' },                                         \
    {                                                                              \
        "debug_broken_protocol", OPT_S_DEBUGBROKE, '-'                             \
    }

#define OPT_S_CASES                                                                \
    OPT_S__FIRST:                                                                  \
    case OPT_S__LAST:                                                              \
        break;                                                                     \
    case OPT_S_NOSSL3:                                                             \
    case OPT_S_NOTLS1:                                                             \
    case OPT_S_NOTLS1_1:                                                           \
    case OPT_S_NOTLS1_2:                                                           \
    case OPT_S_BUGS:                                                               \
    case OPT_S_NOCOMP:                                                             \
    case OPT_S_ECDHSINGLE:                                                         \
    case OPT_S_NOTICKET:                                                           \
    case OPT_S_SERVERPREF:                                                         \
    case OPT_S_LEGACYRENEG:                                                        \
    case OPT_S_LEGACYCONN:                                                         \
    case OPT_S_ONRESUMP:                                                           \
    case OPT_S_NOLEGACYCONN:                                                       \
    case OPT_S_STRICT:                                                             \
    case OPT_S_SIGALGS:                                                            \
    case OPT_S_CLIENTSIGALGS:                                                      \
    case OPT_S_CURVES:                                                             \
    case OPT_S_NAMEDCURVE:                                                         \
    case OPT_S_CIPHER:                                                             \
    case OPT_S_DHPARAM:                                                            \
    case OPT_S_DEBUGBROKE

/*
 * Option parsing.
 */
extern const char OPT_HELP_STR[];
extern const char OPT_MORE_STR[];
typedef struct options_st {
    const char *name;
    int retval;
    /*
     * value type: - no value (also the value zero), n number, p positive
     * number, u unsigned, s string, < input file, > output file, f der/pem
     * format, F any format identifier.  n and u include zero; p does not.
     */
    int valtype;
    const char *helpstr;
} OPTIONS;

typedef struct opt_pair_st {
    const char *name;
    int retval;
} OPT_PAIR;

/* Flags to pass into opt_format; see FORMAT_xxx, below. */
#define OPT_FMT_PEMDER (1L << 1)
#define OPT_FMT_PKCS12 (1L << 2)
#define OPT_FMT_SMIME (1L << 3)
#define OPT_FMT_ENGINE (1L << 4)
#define OPT_FMT_MSBLOB (1L << 5)
#define OPT_FMT_NETSCAPE (1L << 6)
#define OPT_FMT_NSS (1L << 7)
#define OPT_FMT_TEXT (1L << 8)
#define OPT_FMT_HTTP (1L << 9)
#define OPT_FMT_PVK (1L << 10)
#define OPT_FMT_ANY                                                                \
    (OPT_FMT_PEMDER | OPT_FMT_PKCS12 | OPT_FMT_SMIME | OPT_FMT_ENGINE              \
     | OPT_FMT_MSBLOB | OPT_FMT_NETSCAPE | OPT_FMT_NSS | OPT_FMT_TEXT              \
     | OPT_FMT_HTTP | OPT_FMT_PVK)

char *opt_progname(char *argv0);
char *opt_getprog(void);
char *opt_init(int ac, char **av, const OPTIONS *o);
int opt_next(void);
int opt_format(const char *s, unsigned long flags, int *result);
int opt_int(const char *arg, int *result);
int opt_ulong(const char *arg, unsigned long *result);
int opt_long(const char *arg, long *result);
int opt_pair(const char *arg, const OPT_PAIR *pairs, int *result);
int opt_cipher(const char *name, const EVP_CIPHER **cipherp);
int opt_md(const char *name, const EVP_MD **mdp);
char *opt_arg(void);
char *opt_flag(void);
char *opt_unknown(void);
char *opt_reset(void);
char **opt_rest(void);
int opt_num_rest(void);
int opt_verify(int i, X509_VERIFY_PARAM *vpm);
void opt_help(const OPTIONS *list);
int opt_format_error(const char *s, unsigned long flags);
int opt_next(void);

typedef struct args_st {
    int size;
    int argc;
    char **argv;
} ARGS;

#define PW_MIN_LENGTH 4
typedef struct pw_cb_data {
    const void *password;
    const char *prompt_info;
} PW_CB_DATA;

int password_callback(char *buf, int bufsiz, int verify,
                      PW_CB_DATA *cb_data);

int setup_ui_method(void);
void destroy_ui_method(void);

int should_retry(int i);
int args_from_file(char *file, int *argc, char **argv[]);
int str2fmt(char *s);
void program_name(char *in, char *out, int size);
int chopup_args(ARGS *arg, char *buf, int *argc, char **argv[]);
#ifdef HEADER_X509_H
int dump_cert_text(BIO *out, X509 *x);
void print_name(BIO *out, const char *title, X509_NAME *nm, unsigned long lflags);
#endif
void print_bignum_var(BIO *, BIGNUM *, const char*, int, uint8_t *);
void print_array(BIO *, const char *, int, const uint8_t *);
int set_cert_ex(unsigned long *flags, const char *arg);
int set_name_ex(unsigned long *flags, const char *arg);
int set_ext_copy(int *copy_type, const char *arg);
int copy_extensions(X509 *x, X509_REQ *req, int copy_type);
int app_passwd(char *arg1, char *arg2, char **pass1, char **pass2);
int add_oid_section(CONF *conf);
X509 *load_cert(const char *file, int format,
                const char *pass, ENGINE *e, const char *cert_descrip);
EVP_PKEY *load_key(const char *file, int format, int maybe_stdin,
                   const char *pass, ENGINE *e, const char *key_descrip);
EVP_PKEY *load_pubkey(const char *file, int format, int maybe_stdin,
                      const char *pass, ENGINE *e, const char *key_descrip);
STACK_OF(X509) *load_certs(const char *file, int format,
                            const char *pass, ENGINE *e, const char *cert_descrip);
STACK_OF(X509_CRL) *load_crls(const char *file, int format,
                               const char *pass, ENGINE *e, const char *cert_descrip);
X509_STORE *setup_verify(char *CAfile, char *CApath);
#ifndef OPENSSL_NO_ENGINE
ENGINE *setup_engine(const char *engine, int debug);
#endif

#ifndef OPENSSL_NO_OCSP
OCSP_RESPONSE *process_responder(OCSP_REQUEST *req,
                                 char *host, char *path, char *port, int use_ssl,
                                 STACK_OF(CONF_VALUE) *headers,
                                 int req_timeout);
#endif

/* Functions defined in ca.c and also used in ocsp.c */
int unpack_revinfo(ASN1_TIME **prevtm, int *preason, ASN1_OBJECT **phold,
                   ASN1_GENERALIZEDTIME **pinvtm, const char *str);

#define DB_type 0
#define DB_exp_date 1
#define DB_rev_date 2
#define DB_serial 3 /* index - unique */
#define DB_file 4
#define DB_name 5 /* index - unique when active and not disabled */
#define DB_NUMBER 6

#define DB_TYPE_REV 'R'
#define DB_TYPE_EXP 'E'
#define DB_TYPE_VAL 'V'

typedef struct db_attr_st {
    int unique_subject;
} DB_ATTR;
typedef struct ca_db_st {
    DB_ATTR attributes;
    TXT_DB *db;
} CA_DB;

BIGNUM *load_serial(char *serialfile, int create, ASN1_INTEGER **retai);
int save_serial(char *serialfile, char *suffix, BIGNUM *serial, ASN1_INTEGER **retai);
int rotate_serial(char *serialfile, char *new_suffix, char *old_suffix);
int rand_serial(BIGNUM *b, ASN1_INTEGER *ai);
CA_DB *load_index(char *dbfile, DB_ATTR *dbattr);
int index_index(CA_DB *db);
int save_index(const char *dbfile, const char *suffix, CA_DB *db);
int rotate_index(const char *dbfile, const char *new_suffix, const char *old_suffix);
void free_index(CA_DB *db);
#define index_name_cmp_noconst(a, b)                                           \
    index_name_cmp((const OPENSSL_CSTRING *)CHECKED_PTR_OF(OPENSSL_STRING, a), \
                   (const OPENSSL_CSTRING *)CHECKED_PTR_OF(OPENSSL_STRING, b))
int index_name_cmp(const OPENSSL_CSTRING *a, const OPENSSL_CSTRING *b);
int parse_yesno(const char *str, int def);

X509_NAME *parse_name(char *str, long chtype, int multirdn);
int args_verify(char ***pargs, int *pargc,
                int *badarg, X509_VERIFY_PARAM **pm);
void policies_print(BIO *out, X509_STORE_CTX *ctx);
int bio_to_mem(uint8_t **out, int maxlen, BIO *in);
int pkey_ctrl_string(EVP_PKEY_CTX *ctx, char *value);
int init_gen_str(EVP_PKEY_CTX **pctx,
                 const char *algname, ENGINE *e, int do_param);
int do_X509_sign(X509 *x, EVP_PKEY *pkey, const EVP_MD *md,
                 STACK_OF(OPENSSL_STRING) *sigopts);
int do_X509_REQ_sign(X509_REQ *x, EVP_PKEY *pkey, const EVP_MD *md,
                     STACK_OF(OPENSSL_STRING) *sigopts);
int do_X509_CRL_sign(X509_CRL *x, EVP_PKEY *pkey, const EVP_MD *md,
                     STACK_OF(OPENSSL_STRING) *sigopts);

#ifndef OPENSSL_NO_NEXTPROTONEG
uint8_t *next_protos_parse(unsigned short *outlen, const char *in);
#endif

#define FORMAT_UNDEF 0
#define FORMAT_ASN1 1
#define FORMAT_TEXT 2
#define FORMAT_PEM 3
#define FORMAT_NETSCAPE 4
#define FORMAT_PKCS12 5
#define FORMAT_SMIME 6
#define FORMAT_ENGINE 7
#define FORMAT_PEMRSA 9   /* PEM RSAPubicKey format */
#define FORMAT_ASN1RSA 10 /* DER RSAPubicKey format */
#define FORMAT_MSBLOB 11  /* MS Key blob format */
#define FORMAT_PVK 12     /* MS PVK file format */

#define EXT_COPY_NONE 0
#define EXT_COPY_ADD 1
#define EXT_COPY_ALL 2

#define NETSCAPE_CERT_HDR "certificate"

#define APP_PASS_LEN 1024

#define SERIAL_RAND_BITS 64

int app_isdir(const char *);

#define TM_START 0
#define TM_STOP 1
double app_tminterval(int stop, int usertime);

#define OPENSSL_NO_SSL_INTERN

void select_symbol(int p, char *c);

#include "progs.h"

#endif
