/* crypto/store/str_err.c */
/* ====================================================================
 * Copyright (c) 1999-2006 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.OpenSSL.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@OpenSSL.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.OpenSSL.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */

/* NOTE: this file was auto generated by the mkerr.pl script: any changes
 * made to it will be overwritten when the script next updates this file,
 * only reason strings will be preserved.
 */

#include <stdio.h>
#include <openssl/err.h>
#include <openssl/store.h>

/* BEGIN ERROR CODES */
#ifndef OPENSSL_NO_ERR

#define ERR_FUNC(func) ERR_PACK(ERR_LIB_STORE, func, 0)
#define ERR_REASON(reason) ERR_PACK(ERR_LIB_STORE, 0, reason)

static ERR_STRING_DATA STORE_str_functs[] = {
    { ERR_FUNC(STORE_F_MEM_DELETE), "MEM_DELETE" },
    { ERR_FUNC(STORE_F_MEM_GENERATE), "MEM_GENERATE" },
    { ERR_FUNC(STORE_F_MEM_LIST_END), "MEM_LIST_END" },
    { ERR_FUNC(STORE_F_MEM_LIST_NEXT), "MEM_LIST_NEXT" },
    { ERR_FUNC(STORE_F_MEM_LIST_START), "MEM_LIST_START" },
    { ERR_FUNC(STORE_F_MEM_MODIFY), "MEM_MODIFY" },
    { ERR_FUNC(STORE_F_MEM_STORE), "MEM_STORE" },
    { ERR_FUNC(STORE_F_STORE_ATTR_INFO_GET0_CSTR), "STORE_ATTR_INFO_get0_cstr" },
    { ERR_FUNC(STORE_F_STORE_ATTR_INFO_GET0_DN), "STORE_ATTR_INFO_get0_dn" },
    { ERR_FUNC(STORE_F_STORE_ATTR_INFO_GET0_NUMBER), "STORE_ATTR_INFO_get0_number" },
    { ERR_FUNC(STORE_F_STORE_ATTR_INFO_GET0_SHA1STR), "STORE_ATTR_INFO_get0_sha1str" },
    { ERR_FUNC(STORE_F_STORE_ATTR_INFO_MODIFY_CSTR), "STORE_ATTR_INFO_modify_cstr" },
    { ERR_FUNC(STORE_F_STORE_ATTR_INFO_MODIFY_DN), "STORE_ATTR_INFO_modify_dn" },
    { ERR_FUNC(STORE_F_STORE_ATTR_INFO_MODIFY_NUMBER), "STORE_ATTR_INFO_modify_number" },
    { ERR_FUNC(STORE_F_STORE_ATTR_INFO_MODIFY_SHA1STR), "STORE_ATTR_INFO_modify_sha1str" },
    { ERR_FUNC(STORE_F_STORE_ATTR_INFO_SET_CSTR), "STORE_ATTR_INFO_set_cstr" },
    { ERR_FUNC(STORE_F_STORE_ATTR_INFO_SET_DN), "STORE_ATTR_INFO_set_dn" },
    { ERR_FUNC(STORE_F_STORE_ATTR_INFO_SET_NUMBER), "STORE_ATTR_INFO_set_number" },
    { ERR_FUNC(STORE_F_STORE_ATTR_INFO_SET_SHA1STR), "STORE_ATTR_INFO_set_sha1str" },
    { ERR_FUNC(STORE_F_STORE_CERTIFICATE), "STORE_CERTIFICATE" },
    { ERR_FUNC(STORE_F_STORE_CTRL), "STORE_ctrl" },
    { ERR_FUNC(STORE_F_STORE_DELETE_ARBITRARY), "STORE_delete_arbitrary" },
    { ERR_FUNC(STORE_F_STORE_DELETE_CERTIFICATE), "STORE_delete_certificate" },
    { ERR_FUNC(STORE_F_STORE_DELETE_CRL), "STORE_delete_crl" },
    { ERR_FUNC(STORE_F_STORE_DELETE_NUMBER), "STORE_delete_number" },
    { ERR_FUNC(STORE_F_STORE_DELETE_PRIVATE_KEY), "STORE_delete_private_key" },
    { ERR_FUNC(STORE_F_STORE_DELETE_PUBLIC_KEY), "STORE_delete_public_key" },
    { ERR_FUNC(STORE_F_STORE_GENERATE_CRL), "STORE_generate_crl" },
    { ERR_FUNC(STORE_F_STORE_GENERATE_KEY), "STORE_generate_key" },
    { ERR_FUNC(STORE_F_STORE_GET_ARBITRARY), "STORE_get_arbitrary" },
    { ERR_FUNC(STORE_F_STORE_GET_CERTIFICATE), "STORE_get_certificate" },
    { ERR_FUNC(STORE_F_STORE_GET_CRL), "STORE_get_crl" },
    { ERR_FUNC(STORE_F_STORE_GET_NUMBER), "STORE_get_number" },
    { ERR_FUNC(STORE_F_STORE_GET_PRIVATE_KEY), "STORE_get_private_key" },
    { ERR_FUNC(STORE_F_STORE_GET_PUBLIC_KEY), "STORE_get_public_key" },
    { ERR_FUNC(STORE_F_STORE_LIST_CERTIFICATE_END), "STORE_list_certificate_end" },
    { ERR_FUNC(STORE_F_STORE_LIST_CERTIFICATE_ENDP), "STORE_list_certificate_endp" },
    { ERR_FUNC(STORE_F_STORE_LIST_CERTIFICATE_NEXT), "STORE_list_certificate_next" },
    { ERR_FUNC(STORE_F_STORE_LIST_CERTIFICATE_START), "STORE_list_certificate_start" },
    { ERR_FUNC(STORE_F_STORE_LIST_CRL_END), "STORE_list_crl_end" },
    { ERR_FUNC(STORE_F_STORE_LIST_CRL_ENDP), "STORE_list_crl_endp" },
    { ERR_FUNC(STORE_F_STORE_LIST_CRL_NEXT), "STORE_list_crl_next" },
    { ERR_FUNC(STORE_F_STORE_LIST_CRL_START), "STORE_list_crl_start" },
    { ERR_FUNC(STORE_F_STORE_LIST_PRIVATE_KEY_END), "STORE_list_private_key_end" },
    { ERR_FUNC(STORE_F_STORE_LIST_PRIVATE_KEY_ENDP), "STORE_list_private_key_endp" },
    { ERR_FUNC(STORE_F_STORE_LIST_PRIVATE_KEY_NEXT), "STORE_list_private_key_next" },
    { ERR_FUNC(STORE_F_STORE_LIST_PRIVATE_KEY_START), "STORE_list_private_key_start" },
    { ERR_FUNC(STORE_F_STORE_LIST_PUBLIC_KEY_END), "STORE_list_public_key_end" },
    { ERR_FUNC(STORE_F_STORE_LIST_PUBLIC_KEY_ENDP), "STORE_list_public_key_endp" },
    { ERR_FUNC(STORE_F_STORE_LIST_PUBLIC_KEY_NEXT), "STORE_list_public_key_next" },
    { ERR_FUNC(STORE_F_STORE_LIST_PUBLIC_KEY_START), "STORE_list_public_key_start" },
    { ERR_FUNC(STORE_F_STORE_MODIFY_ARBITRARY), "STORE_modify_arbitrary" },
    { ERR_FUNC(STORE_F_STORE_MODIFY_CERTIFICATE), "STORE_modify_certificate" },
    { ERR_FUNC(STORE_F_STORE_MODIFY_CRL), "STORE_modify_crl" },
    { ERR_FUNC(STORE_F_STORE_MODIFY_NUMBER), "STORE_modify_number" },
    { ERR_FUNC(STORE_F_STORE_MODIFY_PRIVATE_KEY), "STORE_modify_private_key" },
    { ERR_FUNC(STORE_F_STORE_MODIFY_PUBLIC_KEY), "STORE_modify_public_key" },
    { ERR_FUNC(STORE_F_STORE_NEW_ENGINE), "STORE_new_engine" },
    { ERR_FUNC(STORE_F_STORE_NEW_METHOD), "STORE_new_method" },
    { ERR_FUNC(STORE_F_STORE_PARSE_ATTRS_END), "STORE_parse_attrs_end" },
    { ERR_FUNC(STORE_F_STORE_PARSE_ATTRS_ENDP), "STORE_parse_attrs_endp" },
    { ERR_FUNC(STORE_F_STORE_PARSE_ATTRS_NEXT), "STORE_parse_attrs_next" },
    { ERR_FUNC(STORE_F_STORE_PARSE_ATTRS_START), "STORE_parse_attrs_start" },
    { ERR_FUNC(STORE_F_STORE_REVOKE_CERTIFICATE), "STORE_revoke_certificate" },
    { ERR_FUNC(STORE_F_STORE_REVOKE_PRIVATE_KEY), "STORE_revoke_private_key" },
    { ERR_FUNC(STORE_F_STORE_REVOKE_PUBLIC_KEY), "STORE_revoke_public_key" },
    { ERR_FUNC(STORE_F_STORE_STORE_ARBITRARY), "STORE_store_arbitrary" },
    { ERR_FUNC(STORE_F_STORE_STORE_CERTIFICATE), "STORE_store_certificate" },
    { ERR_FUNC(STORE_F_STORE_STORE_CRL), "STORE_store_crl" },
    { ERR_FUNC(STORE_F_STORE_STORE_NUMBER), "STORE_store_number" },
    { ERR_FUNC(STORE_F_STORE_STORE_PRIVATE_KEY), "STORE_store_private_key" },
    { ERR_FUNC(STORE_F_STORE_STORE_PUBLIC_KEY), "STORE_store_public_key" },
    { 0, NULL }
};

static ERR_STRING_DATA STORE_str_reasons[] = {
    { ERR_REASON(STORE_R_ALREADY_HAS_A_VALUE), "already has a value" },
    { ERR_REASON(STORE_R_FAILED_DELETING_ARBITRARY), "failed deleting arbitrary" },
    { ERR_REASON(STORE_R_FAILED_DELETING_CERTIFICATE), "failed deleting certificate" },
    { ERR_REASON(STORE_R_FAILED_DELETING_KEY), "failed deleting key" },
    { ERR_REASON(STORE_R_FAILED_DELETING_NUMBER), "failed deleting number" },
    { ERR_REASON(STORE_R_FAILED_GENERATING_CRL), "failed generating crl" },
    { ERR_REASON(STORE_R_FAILED_GENERATING_KEY), "failed generating key" },
    { ERR_REASON(STORE_R_FAILED_GETTING_ARBITRARY), "failed getting arbitrary" },
    { ERR_REASON(STORE_R_FAILED_GETTING_CERTIFICATE), "failed getting certificate" },
    { ERR_REASON(STORE_R_FAILED_GETTING_KEY), "failed getting key" },
    { ERR_REASON(STORE_R_FAILED_GETTING_NUMBER), "failed getting number" },
    { ERR_REASON(STORE_R_FAILED_LISTING_CERTIFICATES), "failed listing certificates" },
    { ERR_REASON(STORE_R_FAILED_LISTING_KEYS), "failed listing keys" },
    { ERR_REASON(STORE_R_FAILED_MODIFYING_ARBITRARY), "failed modifying arbitrary" },
    { ERR_REASON(STORE_R_FAILED_MODIFYING_CERTIFICATE), "failed modifying certificate" },
    { ERR_REASON(STORE_R_FAILED_MODIFYING_CRL), "failed modifying crl" },
    { ERR_REASON(STORE_R_FAILED_MODIFYING_NUMBER), "failed modifying number" },
    { ERR_REASON(STORE_R_FAILED_MODIFYING_PRIVATE_KEY), "failed modifying private key" },
    { ERR_REASON(STORE_R_FAILED_MODIFYING_PUBLIC_KEY), "failed modifying public key" },
    { ERR_REASON(STORE_R_FAILED_REVOKING_CERTIFICATE), "failed revoking certificate" },
    { ERR_REASON(STORE_R_FAILED_REVOKING_KEY), "failed revoking key" },
    { ERR_REASON(STORE_R_FAILED_STORING_ARBITRARY), "failed storing arbitrary" },
    { ERR_REASON(STORE_R_FAILED_STORING_CERTIFICATE), "failed storing certificate" },
    { ERR_REASON(STORE_R_FAILED_STORING_KEY), "failed storing key" },
    { ERR_REASON(STORE_R_FAILED_STORING_NUMBER), "failed storing number" },
    { ERR_REASON(STORE_R_NOT_IMPLEMENTED), "not implemented" },
    { ERR_REASON(STORE_R_NO_CONTROL_FUNCTION), "no control function" },
    { ERR_REASON(STORE_R_NO_DELETE_ARBITRARY_FUNCTION), "no delete arbitrary function" },
    { ERR_REASON(STORE_R_NO_DELETE_NUMBER_FUNCTION), "no delete number function" },
    { ERR_REASON(STORE_R_NO_DELETE_OBJECT_FUNCTION), "no delete object function" },
    { ERR_REASON(STORE_R_NO_GENERATE_CRL_FUNCTION), "no generate crl function" },
    { ERR_REASON(STORE_R_NO_GENERATE_OBJECT_FUNCTION), "no generate object function" },
    { ERR_REASON(STORE_R_NO_GET_OBJECT_ARBITRARY_FUNCTION), "no get object arbitrary function" },
    { ERR_REASON(STORE_R_NO_GET_OBJECT_FUNCTION), "no get object function" },
    { ERR_REASON(STORE_R_NO_GET_OBJECT_NUMBER_FUNCTION), "no get object number function" },
    { ERR_REASON(STORE_R_NO_LIST_OBJECT_ENDP_FUNCTION), "no list object endp function" },
    { ERR_REASON(STORE_R_NO_LIST_OBJECT_END_FUNCTION), "no list object end function" },
    { ERR_REASON(STORE_R_NO_LIST_OBJECT_NEXT_FUNCTION), "no list object next function" },
    { ERR_REASON(STORE_R_NO_LIST_OBJECT_START_FUNCTION), "no list object start function" },
    { ERR_REASON(STORE_R_NO_MODIFY_OBJECT_FUNCTION), "no modify object function" },
    { ERR_REASON(STORE_R_NO_REVOKE_OBJECT_FUNCTION), "no revoke object function" },
    { ERR_REASON(STORE_R_NO_STORE), "no store" },
    { ERR_REASON(STORE_R_NO_STORE_OBJECT_ARBITRARY_FUNCTION), "no store object arbitrary function" },
    { ERR_REASON(STORE_R_NO_STORE_OBJECT_FUNCTION), "no store object function" },
    { ERR_REASON(STORE_R_NO_STORE_OBJECT_NUMBER_FUNCTION), "no store object number function" },
    { ERR_REASON(STORE_R_NO_VALUE), "no value" },
    { 0, NULL }
};

#endif

void ERR_load_STORE_strings(void)
{
#ifndef OPENSSL_NO_ERR

    if (ERR_func_error_string(STORE_str_functs[0].error) == NULL) {
        ERR_load_strings(0, STORE_str_functs);
        ERR_load_strings(0, STORE_str_reasons);
    }
#endif
}
