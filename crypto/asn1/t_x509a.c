/*
 * Copyright 1999-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <openssl/evp.h>
#include <openssl/asn1.h>
#include <openssl/x509.h>

/* X509_CERT_AUX and string set routines
 */

int X509_CERT_AUX_print(BIO *out, X509_CERT_AUX *aux, int indent)
{
    char oidstr[80], first;
    int i;
    if (!aux)
        return 1;
    if (aux->trust) {
        first = 1;
        BIO_printf(out, "%*sTrusted Uses:\n%*s",
                   indent, "", indent + 2, "");
        for (i = 0; i < sk_ASN1_OBJECT_num(aux->trust); i++) {
            if (!first)
                BIO_puts(out, ", ");
            else
                first = 0;
            OBJ_obj2txt(oidstr, sizeof oidstr,
                        sk_ASN1_OBJECT_value(aux->trust, i), 0);
            BIO_puts(out, oidstr);
        }
        BIO_puts(out, "\n");
    } else
        BIO_printf(out, "%*sNo Trusted Uses.\n", indent, "");
    if (aux->reject) {
        first = 1;
        BIO_printf(out, "%*sRejected Uses:\n%*s",
                   indent, "", indent + 2, "");
        for (i = 0; i < sk_ASN1_OBJECT_num(aux->reject); i++) {
            if (!first)
                BIO_puts(out, ", ");
            else
                first = 0;
            OBJ_obj2txt(oidstr, sizeof oidstr,
                        sk_ASN1_OBJECT_value(aux->reject, i), 0);
            BIO_puts(out, oidstr);
        }
        BIO_puts(out, "\n");
    } else
        BIO_printf(out, "%*sNo Rejected Uses.\n", indent, "");
    if (aux->alias)
        BIO_printf(out, "%*sAlias: %s\n", indent, "",
                   aux->alias->data);
    if (aux->keyid) {
        BIO_printf(out, "%*sKey Id: ", indent, "");
        for (i = 0; i < aux->keyid->length; i++)
            BIO_printf(out, "%s%02X",
                       i ? ":" : "",
                       aux->keyid->data[i]);
        BIO_write(out, "\n", 1);
    }
    return 1;
}
