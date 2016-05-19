/*
 * Copyright 2000-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include <string.h>

#include <openssl/asn1t.h>
#include <openssl/err.h>
#include <openssl/objects.h>
#include <openssl/ocsp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

/* Convert a certificate and its issuer to an OCSP_CERTID */

OCSP_CERTID *OCSP_cert_to_id(const EVP_MD *dgst, X509 *subject, X509 *issuer)
{
    X509_NAME *iname;
    ASN1_INTEGER *serial;
    ASN1_BIT_STRING *ikey;
    if (!dgst)
        dgst = EVP_sha1();
    if (subject) {
        iname = X509_get_issuer_name(subject);
        serial = X509_get_serialNumber(subject);
    } else {
        iname = X509_get_subject_name(issuer);
        serial = NULL;
    }
    ikey = X509_get0_pubkey_bitstr(issuer);
    return OCSP_cert_id_new(dgst, iname, ikey, serial);
}

OCSP_CERTID *OCSP_cert_id_new(const EVP_MD *dgst,
                              X509_NAME *issuerName,
                              ASN1_BIT_STRING *issuerKey,
                              ASN1_INTEGER *serialNumber)
{
    int nid;
    unsigned int i;
    X509_ALGOR *alg;
    OCSP_CERTID *cid = NULL;
    uint8_t md[EVP_MAX_MD_SIZE];

    if (!(cid = OCSP_CERTID_new()))
        goto err;

    alg = cid->hashAlgorithm;
    ASN1_OBJECT_free(alg->algorithm);
    if ((nid = EVP_MD_type(dgst)) == NID_undef) {
        OCSPerr(OCSP_F_OCSP_CERT_ID_NEW, OCSP_R_UNKNOWN_NID);
        goto err;
    }
    if (!(alg->algorithm = OBJ_nid2obj(nid)))
        goto err;
    if ((alg->parameter = ASN1_TYPE_new()) == NULL)
        goto err;
    alg->parameter->type = V_ASN1_NULL;

    if (!X509_NAME_digest(issuerName, dgst, md, &i))
        goto digerr;
    if (!(ASN1_OCTET_STRING_set(cid->issuerNameHash, md, i)))
        goto err;

    /* Calculate the issuerKey hash, excluding tag and length */
    if (!EVP_Digest(issuerKey->data, issuerKey->length, md, &i, dgst, NULL))
        goto err;

    if (!(ASN1_OCTET_STRING_set(cid->issuerKeyHash, md, i)))
        goto err;

    if (serialNumber) {
        ASN1_INTEGER_free(cid->serialNumber);
        if (!(cid->serialNumber = ASN1_INTEGER_dup(serialNumber)))
            goto err;
    }
    return cid;
digerr:
    OCSPerr(OCSP_F_OCSP_CERT_ID_NEW, OCSP_R_DIGEST_ERR);
err:
    if (cid)
        OCSP_CERTID_free(cid);
    return NULL;
}

int OCSP_id_issuer_cmp(OCSP_CERTID *a, OCSP_CERTID *b)
{
    int ret;
    ret = OBJ_cmp(a->hashAlgorithm->algorithm, b->hashAlgorithm->algorithm);
    if (ret)
        return ret;
    ret = ASN1_OCTET_STRING_cmp(a->issuerNameHash, b->issuerNameHash);
    if (ret)
        return ret;
    return ASN1_OCTET_STRING_cmp(a->issuerKeyHash, b->issuerKeyHash);
}

int OCSP_id_cmp(OCSP_CERTID *a, OCSP_CERTID *b)
{
    int ret;
    ret = OCSP_id_issuer_cmp(a, b);
    if (ret)
        return ret;
    return ASN1_INTEGER_cmp(a->serialNumber, b->serialNumber);
}

/* Parse a URL and split it up into host, port and path components and whether
 * it is SSL.
 */

int OCSP_parse_url(char *url, char **phost, char **pport, char **ppath, int *pssl)
{
    char *p, *buf;

    char *host;
    const char *port;

    *phost = NULL;
    *pport = NULL;
    *ppath = NULL;

    /* dup the buffer since we are going to mess with it */
    if ((buf = strdup(url)) == NULL)
        goto mem_err;

    /* Check for initial colon */
    p = strchr(buf, ':');

    if (!p)
        goto parse_err;

    *(p++) = '\0';

    if (strcmp(buf, "http") == 0) {
        *pssl = 0;
        port = "80";
    } else if (strcmp(buf, "https") == 0) {
        *pssl = 1;
        port = "443";
    } else
        goto parse_err;

    /* Check for double slash */
    if ((p[0] != '/') || (p[1] != '/'))
        goto parse_err;

    p += 2;

    host = p;

    /* Check for trailing part of path */

    p = strchr(p, '/');

    if (!p)
        *ppath = strdup("/");
    else {
        *ppath = strdup(p);
        /* Set start of path to 0 so hostname is valid */
        *p = '\0';
    }

    if (!*ppath)
        goto mem_err;

    p = host;
    if (host[0] == '[') {
        /* ipv6 literal */
        host++;
        p = strchr(host, ']');
        if (!p)
            goto parse_err;
        *p = '\0';
        p++;
    }

    /* Look for optional ':' for port number */
    if ((p = strchr(p, ':'))) {
        *p = 0;
        port = p + 1;
    } else {
        /* Not found: set default port */
        if (*pssl)
            port = "443";
        else
            port = "80";
    }

    *pport = strdup(port);
    if (!*pport)
        goto mem_err;

    *phost = strdup(host);

    if (!*phost)
        goto mem_err;

    free(buf);

    return 1;

mem_err:
    OCSPerr(OCSP_F_OCSP_PARSE_URL, ERR_R_MALLOC_FAILURE);
    goto err;

parse_err:
    OCSPerr(OCSP_F_OCSP_PARSE_URL, OCSP_R_ERROR_PARSING_URL);

err:
    free(buf);
    free(*ppath);
    free(*pport);
    free(*phost);
	*phost = NULL;
	*pport = NULL;
	*ppath = NULL;
    return 0;
}

OCSP_CERTID *OCSP_CERTID_dup(OCSP_CERTID *x)
{
    return ASN1_item_dup(&OCSP_CERTID_it, x);
}
