/* crypto/objects/obj_dat.h */

/* THIS FILE IS GENERATED FROM objects.h by obj_dat.pl via the
 * following command:
 * perl obj_dat.pl obj_mac.h obj_dat.h
 */

/* Copyright (C) 1995-1997 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#define NUM_NID 952
#define NUM_SN 929
#define NUM_LN 929
#define NUM_OBJ 870

static const unsigned char lvalues[6091]={
0x2A,0x86,0x48,0x86,0xF7,0x0D,               /* [  0] OBJ_rsadsi */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,          /* [  6] OBJ_pkcs */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x02,0x05,     /* [ 13] OBJ_md5 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x03,0x04,     /* [ 21] OBJ_rc4 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x01,/* [ 29] OBJ_rsaEncryption */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x04,/* [ 38] OBJ_md5WithRSAEncryption */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x05,0x03,/* [ 47] OBJ_pbeWithMD5AndDES_CBC */
0x55,                                        /* [ 56] OBJ_X500 */
0x55,0x04,                                   /* [ 57] OBJ_X509 */
0x55,0x04,0x03,                              /* [ 59] OBJ_commonName */
0x55,0x04,0x06,                              /* [ 62] OBJ_countryName */
0x55,0x04,0x07,                              /* [ 65] OBJ_localityName */
0x55,0x04,0x08,                              /* [ 68] OBJ_stateOrProvinceName */
0x55,0x04,0x0A,                              /* [ 71] OBJ_organizationName */
0x55,0x04,0x0B,                              /* [ 74] OBJ_organizationalUnitName */
0x55,0x08,0x01,0x01,                         /* [ 77] OBJ_rsa */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x07,     /* [ 81] OBJ_pkcs7 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x07,0x01,/* [ 89] OBJ_pkcs7_data */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x07,0x02,/* [ 98] OBJ_pkcs7_signed */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x07,0x03,/* [107] OBJ_pkcs7_enveloped */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x07,0x04,/* [116] OBJ_pkcs7_signedAndEnveloped */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x07,0x05,/* [125] OBJ_pkcs7_digest */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x07,0x06,/* [134] OBJ_pkcs7_encrypted */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x03,     /* [143] OBJ_pkcs3 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x03,0x01,/* [151] OBJ_dhKeyAgreement */
0x2B,0x0E,0x03,0x02,0x06,                    /* [160] OBJ_des_ecb */
0x2B,0x0E,0x03,0x02,0x07,                    /* [165] OBJ_des_cbc */
0x2B,0x0E,0x03,0x02,0x11,                    /* [170] OBJ_des_ede_ecb */
0x2B,0x06,0x01,0x04,0x01,0x81,0x3C,0x07,0x01,0x01,0x02,/* [175] OBJ_idea_cbc */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x03,0x02,     /* [186] OBJ_rc2_cbc */
0x2B,0x0E,0x03,0x02,0x12,                    /* [194] OBJ_sha */
0x2B,0x0E,0x03,0x02,0x0F,                    /* [199] OBJ_shaWithRSAEncryption */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x03,0x07,     /* [204] OBJ_des_ede3_cbc */
0x2B,0x0E,0x03,0x02,0x08,                    /* [212] OBJ_des_ofb64 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,     /* [217] OBJ_pkcs9 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x01,/* [225] OBJ_pkcs9_emailAddress */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x02,/* [234] OBJ_pkcs9_unstructuredName */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x03,/* [243] OBJ_pkcs9_contentType */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x04,/* [252] OBJ_pkcs9_messageDigest */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x05,/* [261] OBJ_pkcs9_signingTime */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x06,/* [270] OBJ_pkcs9_countersignature */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x07,/* [279] OBJ_pkcs9_challengePassword */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x08,/* [288] OBJ_pkcs9_unstructuredAddress */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x09,/* [297] OBJ_pkcs9_extCertAttributes */
0x60,0x86,0x48,0x01,0x86,0xF8,0x42,          /* [306] OBJ_netscape */
0x60,0x86,0x48,0x01,0x86,0xF8,0x42,0x01,     /* [313] OBJ_netscape_cert_extension */
0x60,0x86,0x48,0x01,0x86,0xF8,0x42,0x02,     /* [321] OBJ_netscape_data_type */
0x2B,0x0E,0x03,0x02,0x1A,                    /* [329] OBJ_sha1 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x05,/* [334] OBJ_sha1WithRSAEncryption */
0x2B,0x0E,0x03,0x02,0x0D,                    /* [343] OBJ_dsaWithSHA */
0x2B,0x0E,0x03,0x02,0x0C,                    /* [348] OBJ_dsa_2 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x05,0x0B,/* [353] OBJ_pbeWithSHA1AndRC2_CBC */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x05,0x0C,/* [362] OBJ_id_pbkdf2 */
0x2B,0x0E,0x03,0x02,0x1B,                    /* [371] OBJ_dsaWithSHA1_2 */
0x60,0x86,0x48,0x01,0x86,0xF8,0x42,0x01,0x01,/* [376] OBJ_netscape_cert_type */
0x60,0x86,0x48,0x01,0x86,0xF8,0x42,0x01,0x02,/* [385] OBJ_netscape_base_url */
0x60,0x86,0x48,0x01,0x86,0xF8,0x42,0x01,0x03,/* [394] OBJ_netscape_revocation_url */
0x60,0x86,0x48,0x01,0x86,0xF8,0x42,0x01,0x04,/* [403] OBJ_netscape_ca_revocation_url */
0x60,0x86,0x48,0x01,0x86,0xF8,0x42,0x01,0x07,/* [412] OBJ_netscape_renewal_url */
0x60,0x86,0x48,0x01,0x86,0xF8,0x42,0x01,0x08,/* [421] OBJ_netscape_ca_policy_url */
0x60,0x86,0x48,0x01,0x86,0xF8,0x42,0x01,0x0C,/* [430] OBJ_netscape_ssl_server_name */
0x60,0x86,0x48,0x01,0x86,0xF8,0x42,0x01,0x0D,/* [439] OBJ_netscape_comment */
0x60,0x86,0x48,0x01,0x86,0xF8,0x42,0x02,0x05,/* [448] OBJ_netscape_cert_sequence */
0x55,0x1D,                                   /* [457] OBJ_id_ce */
0x55,0x1D,0x0E,                              /* [459] OBJ_subject_key_identifier */
0x55,0x1D,0x0F,                              /* [462] OBJ_key_usage */
0x55,0x1D,0x10,                              /* [465] OBJ_private_key_usage_period */
0x55,0x1D,0x11,                              /* [468] OBJ_subject_alt_name */
0x55,0x1D,0x12,                              /* [471] OBJ_issuer_alt_name */
0x55,0x1D,0x13,                              /* [474] OBJ_basic_constraints */
0x55,0x1D,0x14,                              /* [477] OBJ_crl_number */
0x55,0x1D,0x20,                              /* [480] OBJ_certificate_policies */
0x55,0x1D,0x23,                              /* [483] OBJ_authority_key_identifier */
0x2B,0x06,0x01,0x04,0x01,0x97,0x55,0x01,0x02,/* [486] OBJ_bf_cbc */
0x55,0x04,0x2A,                              /* [495] OBJ_givenName */
0x55,0x04,0x04,                              /* [498] OBJ_surname */
0x55,0x04,0x2B,                              /* [501] OBJ_initials */
0x55,0x1D,0x1F,                              /* [504] OBJ_crl_distribution_points */
0x2B,0x0E,0x03,0x02,0x03,                    /* [507] OBJ_md5WithRSA */
0x55,0x04,0x05,                              /* [512] OBJ_serialNumber */
0x55,0x04,0x0C,                              /* [515] OBJ_title */
0x55,0x04,0x0D,                              /* [518] OBJ_description */
0x2A,0x86,0x48,0x86,0xF6,0x7D,0x07,0x42,0x0A,/* [521] OBJ_cast5_cbc */
0x2A,0x86,0x48,0x86,0xF6,0x7D,0x07,0x42,0x0C,/* [530] OBJ_pbeWithMD5AndCast5_CBC */
0x2A,0x86,0x48,0xCE,0x38,0x04,0x03,          /* [539] OBJ_dsaWithSHA1 */
0x2B,0x0E,0x03,0x02,0x1D,                    /* [546] OBJ_sha1WithRSA */
0x2A,0x86,0x48,0xCE,0x38,0x04,0x01,          /* [551] OBJ_dsa */
0x2B,0x24,0x03,0x02,0x01,                    /* [558] OBJ_ripemd160 */
0x2B,0x24,0x03,0x03,0x01,0x02,               /* [563] OBJ_ripemd160WithRSA */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x03,0x08,     /* [569] OBJ_rc5_cbc */
0x29,0x01,0x01,0x85,0x1A,0x01,               /* [577] OBJ_rle_compression */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x03,0x08,/* [583] OBJ_zlib_compression */
0x55,0x1D,0x25,                              /* [594] OBJ_ext_key_usage */
0x2B,0x06,0x01,0x05,0x05,0x07,               /* [597] OBJ_id_pkix */
0x2B,0x06,0x01,0x05,0x05,0x07,0x03,          /* [603] OBJ_id_kp */
0x2B,0x06,0x01,0x05,0x05,0x07,0x03,0x01,     /* [610] OBJ_server_auth */
0x2B,0x06,0x01,0x05,0x05,0x07,0x03,0x02,     /* [618] OBJ_client_auth */
0x2B,0x06,0x01,0x05,0x05,0x07,0x03,0x03,     /* [626] OBJ_code_sign */
0x2B,0x06,0x01,0x05,0x05,0x07,0x03,0x04,     /* [634] OBJ_email_protect */
0x2B,0x06,0x01,0x05,0x05,0x07,0x03,0x08,     /* [642] OBJ_time_stamp */
0x2B,0x06,0x01,0x04,0x01,0x82,0x37,0x02,0x01,0x15,/* [650] OBJ_ms_code_ind */
0x2B,0x06,0x01,0x04,0x01,0x82,0x37,0x02,0x01,0x16,/* [660] OBJ_ms_code_com */
0x2B,0x06,0x01,0x04,0x01,0x82,0x37,0x0A,0x03,0x01,/* [670] OBJ_ms_ctl_sign */
0x2B,0x06,0x01,0x04,0x01,0x82,0x37,0x0A,0x03,0x03,/* [680] OBJ_ms_sgc */
0x2B,0x06,0x01,0x04,0x01,0x82,0x37,0x0A,0x03,0x04,/* [690] OBJ_ms_efs */
0x60,0x86,0x48,0x01,0x86,0xF8,0x42,0x04,0x01,/* [700] OBJ_ns_sgc */
0x55,0x1D,0x1B,                              /* [709] OBJ_delta_crl */
0x55,0x1D,0x15,                              /* [712] OBJ_crl_reason */
0x55,0x1D,0x18,                              /* [715] OBJ_invalidity_date */
0x2B,0x65,0x01,0x04,0x01,                    /* [718] OBJ_sxnet */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x0C,0x01,0x01,/* [723] OBJ_pbe_WithSHA1And128BitRC4 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x0C,0x01,0x02,/* [733] OBJ_pbe_WithSHA1And40BitRC4 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x0C,0x01,0x03,/* [743] OBJ_pbe_WithSHA1And3_Key_TripleDES_CBC */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x0C,0x01,0x04,/* [753] OBJ_pbe_WithSHA1And2_Key_TripleDES_CBC */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x0C,0x01,0x05,/* [763] OBJ_pbe_WithSHA1And128BitRC2_CBC */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x0C,0x01,0x06,/* [773] OBJ_pbe_WithSHA1And40BitRC2_CBC */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x0C,0x0A,0x01,0x01,/* [783] OBJ_keyBag */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x0C,0x0A,0x01,0x02,/* [794] OBJ_pkcs8ShroudedKeyBag */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x0C,0x0A,0x01,0x03,/* [805] OBJ_certBag */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x0C,0x0A,0x01,0x04,/* [816] OBJ_crlBag */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x0C,0x0A,0x01,0x05,/* [827] OBJ_secretBag */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x0C,0x0A,0x01,0x06,/* [838] OBJ_safeContentsBag */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x14,/* [849] OBJ_friendlyName */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x15,/* [858] OBJ_localKeyID */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x16,0x01,/* [867] OBJ_x509Certificate */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x16,0x02,/* [877] OBJ_sdsiCertificate */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x17,0x01,/* [887] OBJ_x509Crl */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x05,0x0D,/* [897] OBJ_pbes2 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x05,0x0E,/* [906] OBJ_pbmac1 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x02,0x07,     /* [915] OBJ_hmacWithSHA1 */
0x2B,0x06,0x01,0x05,0x05,0x07,0x02,0x01,     /* [923] OBJ_id_qt_cps */
0x2B,0x06,0x01,0x05,0x05,0x07,0x02,0x02,     /* [931] OBJ_id_qt_unotice */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x0F,/* [939] OBJ_SMIMECapabilities */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x05,0x06,/* [948] OBJ_pbeWithMD5AndRC2_CBC */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x05,0x0A,/* [957] OBJ_pbeWithSHA1AndDES_CBC */
0x2B,0x06,0x01,0x04,0x01,0x82,0x37,0x02,0x01,0x0E,/* [966] OBJ_ms_ext_req */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x0E,/* [976] OBJ_ext_req */
0x55,0x04,0x29,                              /* [985] OBJ_name */
0x55,0x04,0x2E,                              /* [988] OBJ_dnQualifier */
0x2B,0x06,0x01,0x05,0x05,0x07,0x01,          /* [991] OBJ_id_pe */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,          /* [998] OBJ_id_ad */
0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x01,     /* [1005] OBJ_info_access */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,     /* [1013] OBJ_ad_OCSP */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x02,     /* [1021] OBJ_ad_ca_issuers */
0x2B,0x06,0x01,0x05,0x05,0x07,0x03,0x09,     /* [1029] OBJ_OCSP_sign */
0x2A,                                        /* [1037] OBJ_member_body */
0x2A,0x86,0x48,                              /* [1038] OBJ_ISO_US */
0x2A,0x86,0x48,0xCE,0x38,                    /* [1041] OBJ_X9_57 */
0x2A,0x86,0x48,0xCE,0x38,0x04,               /* [1046] OBJ_X9cm */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,     /* [1052] OBJ_pkcs1 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x05,     /* [1060] OBJ_pkcs5 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,/* [1068] OBJ_SMIME */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x00,/* [1077] OBJ_id_smime_mod */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x01,/* [1087] OBJ_id_smime_ct */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,/* [1097] OBJ_id_smime_aa */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x03,/* [1107] OBJ_id_smime_alg */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x04,/* [1117] OBJ_id_smime_cd */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x05,/* [1127] OBJ_id_smime_spq */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x06,/* [1137] OBJ_id_smime_cti */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x00,0x01,/* [1147] OBJ_id_smime_mod_cms */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x00,0x02,/* [1158] OBJ_id_smime_mod_ess */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x00,0x03,/* [1169] OBJ_id_smime_mod_oid */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x00,0x04,/* [1180] OBJ_id_smime_mod_msg_v3 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x00,0x05,/* [1191] OBJ_id_smime_mod_ets_eSignature_88 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x00,0x06,/* [1202] OBJ_id_smime_mod_ets_eSignature_97 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x00,0x07,/* [1213] OBJ_id_smime_mod_ets_eSigPolicy_88 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x00,0x08,/* [1224] OBJ_id_smime_mod_ets_eSigPolicy_97 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x01,0x01,/* [1235] OBJ_id_smime_ct_receipt */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x01,0x02,/* [1246] OBJ_id_smime_ct_authData */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x01,0x03,/* [1257] OBJ_id_smime_ct_publishCert */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x01,0x04,/* [1268] OBJ_id_smime_ct_TSTInfo */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x01,0x05,/* [1279] OBJ_id_smime_ct_TDTInfo */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x01,0x06,/* [1290] OBJ_id_smime_ct_contentInfo */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x01,0x07,/* [1301] OBJ_id_smime_ct_DVCSRequestData */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x01,0x08,/* [1312] OBJ_id_smime_ct_DVCSResponseData */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x01,/* [1323] OBJ_id_smime_aa_receiptRequest */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x02,/* [1334] OBJ_id_smime_aa_securityLabel */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x03,/* [1345] OBJ_id_smime_aa_mlExpandHistory */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x04,/* [1356] OBJ_id_smime_aa_contentHint */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x05,/* [1367] OBJ_id_smime_aa_msgSigDigest */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x06,/* [1378] OBJ_id_smime_aa_encapContentType */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x07,/* [1389] OBJ_id_smime_aa_contentIdentifier */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x08,/* [1400] OBJ_id_smime_aa_macValue */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x09,/* [1411] OBJ_id_smime_aa_equivalentLabels */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x0A,/* [1422] OBJ_id_smime_aa_contentReference */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x0B,/* [1433] OBJ_id_smime_aa_encrypKeyPref */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x0C,/* [1444] OBJ_id_smime_aa_signingCertificate */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x0D,/* [1455] OBJ_id_smime_aa_smimeEncryptCerts */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x0E,/* [1466] OBJ_id_smime_aa_timeStampToken */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x0F,/* [1477] OBJ_id_smime_aa_ets_sigPolicyId */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x10,/* [1488] OBJ_id_smime_aa_ets_commitmentType */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x11,/* [1499] OBJ_id_smime_aa_ets_signerLocation */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x12,/* [1510] OBJ_id_smime_aa_ets_signerAttr */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x13,/* [1521] OBJ_id_smime_aa_ets_otherSigCert */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x14,/* [1532] OBJ_id_smime_aa_ets_contentTimestamp */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x15,/* [1543] OBJ_id_smime_aa_ets_CertificateRefs */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x16,/* [1554] OBJ_id_smime_aa_ets_RevocationRefs */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x17,/* [1565] OBJ_id_smime_aa_ets_certValues */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x18,/* [1576] OBJ_id_smime_aa_ets_revocationValues */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x19,/* [1587] OBJ_id_smime_aa_ets_escTimeStamp */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x1A,/* [1598] OBJ_id_smime_aa_ets_certCRLTimestamp */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x1B,/* [1609] OBJ_id_smime_aa_ets_archiveTimeStamp */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x1C,/* [1620] OBJ_id_smime_aa_signatureType */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x02,0x1D,/* [1631] OBJ_id_smime_aa_dvcs_dvc */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x03,0x01,/* [1642] OBJ_id_smime_alg_ESDHwith3DES */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x03,0x02,/* [1653] OBJ_id_smime_alg_ESDHwithRC2 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x03,0x03,/* [1664] OBJ_id_smime_alg_3DESwrap */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x03,0x04,/* [1675] OBJ_id_smime_alg_RC2wrap */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x03,0x05,/* [1686] OBJ_id_smime_alg_ESDH */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x03,0x06,/* [1697] OBJ_id_smime_alg_CMS3DESwrap */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x03,0x07,/* [1708] OBJ_id_smime_alg_CMSRC2wrap */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x04,0x01,/* [1719] OBJ_id_smime_cd_ldap */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x05,0x01,/* [1730] OBJ_id_smime_spq_ets_sqt_uri */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x05,0x02,/* [1741] OBJ_id_smime_spq_ets_sqt_unotice */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x06,0x01,/* [1752] OBJ_id_smime_cti_ets_proofOfOrigin */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x06,0x02,/* [1763] OBJ_id_smime_cti_ets_proofOfReceipt */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x06,0x03,/* [1774] OBJ_id_smime_cti_ets_proofOfDelivery */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x06,0x04,/* [1785] OBJ_id_smime_cti_ets_proofOfSender */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x06,0x05,/* [1796] OBJ_id_smime_cti_ets_proofOfApproval */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x06,0x06,/* [1807] OBJ_id_smime_cti_ets_proofOfCreation */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,          /* [1818] OBJ_id_pkix_mod */
0x2B,0x06,0x01,0x05,0x05,0x07,0x02,          /* [1825] OBJ_id_qt */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,          /* [1832] OBJ_id_it */
0x2B,0x06,0x01,0x05,0x05,0x07,0x05,          /* [1839] OBJ_id_pkip */
0x2B,0x06,0x01,0x05,0x05,0x07,0x06,          /* [1846] OBJ_id_alg */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,          /* [1853] OBJ_id_cmc */
0x2B,0x06,0x01,0x05,0x05,0x07,0x08,          /* [1860] OBJ_id_on */
0x2B,0x06,0x01,0x05,0x05,0x07,0x09,          /* [1867] OBJ_id_pda */
0x2B,0x06,0x01,0x05,0x05,0x07,0x0A,          /* [1874] OBJ_id_aca */
0x2B,0x06,0x01,0x05,0x05,0x07,0x0B,          /* [1881] OBJ_id_qcs */
0x2B,0x06,0x01,0x05,0x05,0x07,0x0C,          /* [1888] OBJ_id_cct */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x01,     /* [1895] OBJ_id_pkix1_explicit_88 */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x02,     /* [1903] OBJ_id_pkix1_implicit_88 */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x03,     /* [1911] OBJ_id_pkix1_explicit_93 */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x04,     /* [1919] OBJ_id_pkix1_implicit_93 */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x05,     /* [1927] OBJ_id_mod_crmf */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x06,     /* [1935] OBJ_id_mod_cmc */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x07,     /* [1943] OBJ_id_mod_kea_profile_88 */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x08,     /* [1951] OBJ_id_mod_kea_profile_93 */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x09,     /* [1959] OBJ_id_mod_cmp */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x0A,     /* [1967] OBJ_id_mod_qualified_cert_88 */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x0B,     /* [1975] OBJ_id_mod_qualified_cert_93 */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x0C,     /* [1983] OBJ_id_mod_attribute_cert */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x0D,     /* [1991] OBJ_id_mod_timestamp_protocol */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x0E,     /* [1999] OBJ_id_mod_ocsp */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x0F,     /* [2007] OBJ_id_mod_dvcs */
0x2B,0x06,0x01,0x05,0x05,0x07,0x00,0x10,     /* [2015] OBJ_id_mod_cmp2000 */
0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x02,     /* [2023] OBJ_biometricInfo */
0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x03,     /* [2031] OBJ_qcStatements */
0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x04,     /* [2039] OBJ_ac_auditEntity */
0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x05,     /* [2047] OBJ_ac_targeting */
0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x06,     /* [2055] OBJ_aaControls */
0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x07,     /* [2063] OBJ_sbgp_ipAddrBlock */
0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x08,     /* [2071] OBJ_sbgp_autonomousSysNum */
0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x09,     /* [2079] OBJ_sbgp_routerIdentifier */
0x2B,0x06,0x01,0x05,0x05,0x07,0x02,0x03,     /* [2087] OBJ_textNotice */
0x2B,0x06,0x01,0x05,0x05,0x07,0x03,0x05,     /* [2095] OBJ_ipsecEndSystem */
0x2B,0x06,0x01,0x05,0x05,0x07,0x03,0x06,     /* [2103] OBJ_ipsecTunnel */
0x2B,0x06,0x01,0x05,0x05,0x07,0x03,0x07,     /* [2111] OBJ_ipsecUser */
0x2B,0x06,0x01,0x05,0x05,0x07,0x03,0x0A,     /* [2119] OBJ_dvcs */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x01,     /* [2127] OBJ_id_it_caProtEncCert */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x02,     /* [2135] OBJ_id_it_signKeyPairTypes */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x03,     /* [2143] OBJ_id_it_encKeyPairTypes */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x04,     /* [2151] OBJ_id_it_preferredSymmAlg */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x05,     /* [2159] OBJ_id_it_caKeyUpdateInfo */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x06,     /* [2167] OBJ_id_it_currentCRL */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x07,     /* [2175] OBJ_id_it_unsupportedOIDs */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x08,     /* [2183] OBJ_id_it_subscriptionRequest */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x09,     /* [2191] OBJ_id_it_subscriptionResponse */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x0A,     /* [2199] OBJ_id_it_keyPairParamReq */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x0B,     /* [2207] OBJ_id_it_keyPairParamRep */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x0C,     /* [2215] OBJ_id_it_revPassphrase */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x0D,     /* [2223] OBJ_id_it_implicitConfirm */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x0E,     /* [2231] OBJ_id_it_confirmWaitTime */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x0F,     /* [2239] OBJ_id_it_origPKIMessage */
0x2B,0x06,0x01,0x05,0x05,0x07,0x05,0x01,     /* [2247] OBJ_id_regCtrl */
0x2B,0x06,0x01,0x05,0x05,0x07,0x05,0x02,     /* [2255] OBJ_id_regInfo */
0x2B,0x06,0x01,0x05,0x05,0x07,0x05,0x01,0x01,/* [2263] OBJ_id_regCtrl_regToken */
0x2B,0x06,0x01,0x05,0x05,0x07,0x05,0x01,0x02,/* [2272] OBJ_id_regCtrl_authenticator */
0x2B,0x06,0x01,0x05,0x05,0x07,0x05,0x01,0x03,/* [2281] OBJ_id_regCtrl_pkiPublicationInfo */
0x2B,0x06,0x01,0x05,0x05,0x07,0x05,0x01,0x04,/* [2290] OBJ_id_regCtrl_pkiArchiveOptions */
0x2B,0x06,0x01,0x05,0x05,0x07,0x05,0x01,0x05,/* [2299] OBJ_id_regCtrl_oldCertID */
0x2B,0x06,0x01,0x05,0x05,0x07,0x05,0x01,0x06,/* [2308] OBJ_id_regCtrl_protocolEncrKey */
0x2B,0x06,0x01,0x05,0x05,0x07,0x05,0x02,0x01,/* [2317] OBJ_id_regInfo_utf8Pairs */
0x2B,0x06,0x01,0x05,0x05,0x07,0x05,0x02,0x02,/* [2326] OBJ_id_regInfo_certReq */
0x2B,0x06,0x01,0x05,0x05,0x07,0x06,0x01,     /* [2335] OBJ_id_alg_des40 */
0x2B,0x06,0x01,0x05,0x05,0x07,0x06,0x02,     /* [2343] OBJ_id_alg_noSignature */
0x2B,0x06,0x01,0x05,0x05,0x07,0x06,0x03,     /* [2351] OBJ_id_alg_dh_sig_hmac_sha1 */
0x2B,0x06,0x01,0x05,0x05,0x07,0x06,0x04,     /* [2359] OBJ_id_alg_dh_pop */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x01,     /* [2367] OBJ_id_cmc_statusInfo */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x02,     /* [2375] OBJ_id_cmc_identification */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x03,     /* [2383] OBJ_id_cmc_identityProof */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x04,     /* [2391] OBJ_id_cmc_dataReturn */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x05,     /* [2399] OBJ_id_cmc_transactionId */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x06,     /* [2407] OBJ_id_cmc_senderNonce */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x07,     /* [2415] OBJ_id_cmc_recipientNonce */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x08,     /* [2423] OBJ_id_cmc_addExtensions */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x09,     /* [2431] OBJ_id_cmc_encryptedPOP */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x0A,     /* [2439] OBJ_id_cmc_decryptedPOP */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x0B,     /* [2447] OBJ_id_cmc_lraPOPWitness */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x0F,     /* [2455] OBJ_id_cmc_getCert */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x10,     /* [2463] OBJ_id_cmc_getCRL */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x11,     /* [2471] OBJ_id_cmc_revokeRequest */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x12,     /* [2479] OBJ_id_cmc_regInfo */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x13,     /* [2487] OBJ_id_cmc_responseInfo */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x15,     /* [2495] OBJ_id_cmc_queryPending */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x16,     /* [2503] OBJ_id_cmc_popLinkRandom */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x17,     /* [2511] OBJ_id_cmc_popLinkWitness */
0x2B,0x06,0x01,0x05,0x05,0x07,0x07,0x18,     /* [2519] OBJ_id_cmc_confirmCertAcceptance */
0x2B,0x06,0x01,0x05,0x05,0x07,0x08,0x01,     /* [2527] OBJ_id_on_personalData */
0x2B,0x06,0x01,0x05,0x05,0x07,0x09,0x01,     /* [2535] OBJ_id_pda_dateOfBirth */
0x2B,0x06,0x01,0x05,0x05,0x07,0x09,0x02,     /* [2543] OBJ_id_pda_placeOfBirth */
0x2B,0x06,0x01,0x05,0x05,0x07,0x09,0x03,     /* [2551] OBJ_id_pda_gender */
0x2B,0x06,0x01,0x05,0x05,0x07,0x09,0x04,     /* [2559] OBJ_id_pda_countryOfCitizenship */
0x2B,0x06,0x01,0x05,0x05,0x07,0x09,0x05,     /* [2567] OBJ_id_pda_countryOfResidence */
0x2B,0x06,0x01,0x05,0x05,0x07,0x0A,0x01,     /* [2575] OBJ_id_aca_authenticationInfo */
0x2B,0x06,0x01,0x05,0x05,0x07,0x0A,0x02,     /* [2583] OBJ_id_aca_accessIdentity */
0x2B,0x06,0x01,0x05,0x05,0x07,0x0A,0x03,     /* [2591] OBJ_id_aca_chargingIdentity */
0x2B,0x06,0x01,0x05,0x05,0x07,0x0A,0x04,     /* [2599] OBJ_id_aca_group */
0x2B,0x06,0x01,0x05,0x05,0x07,0x0A,0x05,     /* [2607] OBJ_id_aca_role */
0x2B,0x06,0x01,0x05,0x05,0x07,0x0B,0x01,     /* [2615] OBJ_id_qcs_pkixQCSyntax_v1 */
0x2B,0x06,0x01,0x05,0x05,0x07,0x0C,0x01,     /* [2623] OBJ_id_cct_crs */
0x2B,0x06,0x01,0x05,0x05,0x07,0x0C,0x02,     /* [2631] OBJ_id_cct_PKIData */
0x2B,0x06,0x01,0x05,0x05,0x07,0x0C,0x03,     /* [2639] OBJ_id_cct_PKIResponse */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x03,     /* [2647] OBJ_ad_timeStamping */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x04,     /* [2655] OBJ_ad_dvcs */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,0x01,/* [2663] OBJ_id_pkix_OCSP_basic */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,0x02,/* [2672] OBJ_id_pkix_OCSP_Nonce */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,0x03,/* [2681] OBJ_id_pkix_OCSP_CrlID */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,0x04,/* [2690] OBJ_id_pkix_OCSP_acceptableResponses */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,0x05,/* [2699] OBJ_id_pkix_OCSP_noCheck */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,0x06,/* [2708] OBJ_id_pkix_OCSP_archiveCutoff */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,0x07,/* [2717] OBJ_id_pkix_OCSP_serviceLocator */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,0x08,/* [2726] OBJ_id_pkix_OCSP_extendedStatus */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,0x09,/* [2735] OBJ_id_pkix_OCSP_valid */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,0x0A,/* [2744] OBJ_id_pkix_OCSP_path */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,0x0B,/* [2753] OBJ_id_pkix_OCSP_trustRoot */
0x2B,0x0E,0x03,0x02,                         /* [2762] OBJ_algorithm */
0x2B,0x0E,0x03,0x02,0x0B,                    /* [2766] OBJ_rsaSignature */
0x55,0x08,                                   /* [2771] OBJ_X500algorithms */
0x2B,                                        /* [2773] OBJ_org */
0x2B,0x06,                                   /* [2774] OBJ_dod */
0x2B,0x06,0x01,                              /* [2776] OBJ_iana */
0x2B,0x06,0x01,0x01,                         /* [2779] OBJ_Directory */
0x2B,0x06,0x01,0x02,                         /* [2783] OBJ_Management */
0x2B,0x06,0x01,0x03,                         /* [2787] OBJ_Experimental */
0x2B,0x06,0x01,0x04,                         /* [2791] OBJ_Private */
0x2B,0x06,0x01,0x05,                         /* [2795] OBJ_Security */
0x2B,0x06,0x01,0x06,                         /* [2799] OBJ_SNMPv2 */
0x2B,0x06,0x01,0x07,                         /* [2803] OBJ_Mail */
0x2B,0x06,0x01,0x04,0x01,                    /* [2807] OBJ_Enterprises */
0x2B,0x06,0x01,0x04,0x01,0x8B,0x3A,0x82,0x58,/* [2812] OBJ_dcObject */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x19,/* [2821] OBJ_domainComponent */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x0D,/* [2831] OBJ_Domain */
0x55,0x01,0x05,                              /* [2841] OBJ_selected_attribute_types */
0x55,0x01,0x05,0x37,                         /* [2844] OBJ_clearance */
0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x0A,     /* [2848] OBJ_ac_proxying */
0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x0B,     /* [2856] OBJ_sinfo_access */
0x2B,0x06,0x01,0x05,0x05,0x07,0x0A,0x06,     /* [2864] OBJ_id_aca_encAttrs */
0x55,0x04,0x48,                              /* [2872] OBJ_role */
0x55,0x1D,0x24,                              /* [2875] OBJ_policy_constraints */
0x55,0x1D,0x37,                              /* [2878] OBJ_target_information */
0x55,0x1D,0x38,                              /* [2881] OBJ_no_rev_avail */
0x2A,0x86,0x48,0xCE,0x3D,                    /* [2884] OBJ_ansi_X9_62 */
0x2A,0x86,0x48,0xCE,0x3D,0x01,0x01,          /* [2889] OBJ_X9_62_prime_field */
0x2A,0x86,0x48,0xCE,0x3D,0x01,0x02,          /* [2896] OBJ_X9_62_characteristic_two_field */
0x2A,0x86,0x48,0xCE,0x3D,0x02,0x01,          /* [2903] OBJ_X9_62_id_ecPublicKey */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x01,     /* [2910] OBJ_X9_62_prime192v1 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x02,     /* [2918] OBJ_X9_62_prime192v2 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x03,     /* [2926] OBJ_X9_62_prime192v3 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x04,     /* [2934] OBJ_X9_62_prime239v1 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x05,     /* [2942] OBJ_X9_62_prime239v2 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x06,     /* [2950] OBJ_X9_62_prime239v3 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x07,     /* [2958] OBJ_X9_62_prime256v1 */
0x2A,0x86,0x48,0xCE,0x3D,0x04,0x01,          /* [2966] OBJ_ecdsa_with_SHA1 */
0x2B,0x06,0x01,0x04,0x01,0x82,0x37,0x11,0x01,/* [2973] OBJ_ms_csp_name */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x01,/* [2982] OBJ_aes_128_ecb */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x02,/* [2991] OBJ_aes_128_cbc */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x03,/* [3000] OBJ_aes_128_ofb128 */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x04,/* [3009] OBJ_aes_128_cfb128 */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x15,/* [3018] OBJ_aes_192_ecb */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x16,/* [3027] OBJ_aes_192_cbc */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x17,/* [3036] OBJ_aes_192_ofb128 */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x18,/* [3045] OBJ_aes_192_cfb128 */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x29,/* [3054] OBJ_aes_256_ecb */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x2A,/* [3063] OBJ_aes_256_cbc */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x2B,/* [3072] OBJ_aes_256_ofb128 */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x2C,/* [3081] OBJ_aes_256_cfb128 */
0x55,0x1D,0x17,                              /* [3090] OBJ_hold_instruction_code */
0x2A,0x86,0x48,0xCE,0x38,0x02,0x01,          /* [3093] OBJ_hold_instruction_none */
0x2A,0x86,0x48,0xCE,0x38,0x02,0x02,          /* [3100] OBJ_hold_instruction_call_issuer */
0x2A,0x86,0x48,0xCE,0x38,0x02,0x03,          /* [3107] OBJ_hold_instruction_reject */
0x09,                                        /* [3114] OBJ_data */
0x09,0x92,0x26,                              /* [3115] OBJ_pss */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,          /* [3118] OBJ_ucl */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,     /* [3125] OBJ_pilot */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,/* [3133] OBJ_pilotAttributeType */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x03,/* [3142] OBJ_pilotAttributeSyntax */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,/* [3151] OBJ_pilotObjectClass */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x0A,/* [3160] OBJ_pilotGroups */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x03,0x04,/* [3169] OBJ_iA5StringSyntax */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x03,0x05,/* [3179] OBJ_caseIgnoreIA5StringSyntax */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x03,/* [3189] OBJ_pilotObject */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x04,/* [3199] OBJ_pilotPerson */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x05,/* [3209] OBJ_account */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x06,/* [3219] OBJ_document */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x07,/* [3229] OBJ_room */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x09,/* [3239] OBJ_documentSeries */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x0E,/* [3249] OBJ_rFC822localPart */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x0F,/* [3259] OBJ_dNSDomain */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x11,/* [3269] OBJ_domainRelatedObject */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x12,/* [3279] OBJ_friendlyCountry */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x13,/* [3289] OBJ_simpleSecurityObject */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x14,/* [3299] OBJ_pilotOrganization */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x15,/* [3309] OBJ_pilotDSA */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x04,0x16,/* [3319] OBJ_qualityLabelledData */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x01,/* [3329] OBJ_userId */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x02,/* [3339] OBJ_textEncodedORAddress */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x03,/* [3349] OBJ_rfc822Mailbox */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x04,/* [3359] OBJ_info */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x05,/* [3369] OBJ_favouriteDrink */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x06,/* [3379] OBJ_roomNumber */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x07,/* [3389] OBJ_photo */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x08,/* [3399] OBJ_userClass */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x09,/* [3409] OBJ_host */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x0A,/* [3419] OBJ_manager */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x0B,/* [3429] OBJ_documentIdentifier */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x0C,/* [3439] OBJ_documentTitle */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x0D,/* [3449] OBJ_documentVersion */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x0E,/* [3459] OBJ_documentAuthor */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x0F,/* [3469] OBJ_documentLocation */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x14,/* [3479] OBJ_homeTelephoneNumber */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x15,/* [3489] OBJ_secretary */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x16,/* [3499] OBJ_otherMailbox */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x17,/* [3509] OBJ_lastModifiedTime */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x18,/* [3519] OBJ_lastModifiedBy */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x1A,/* [3529] OBJ_aRecord */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x1B,/* [3539] OBJ_pilotAttributeType27 */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x1C,/* [3549] OBJ_mXRecord */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x1D,/* [3559] OBJ_nSRecord */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x1E,/* [3569] OBJ_sOARecord */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x1F,/* [3579] OBJ_cNAMERecord */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x25,/* [3589] OBJ_associatedDomain */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x26,/* [3599] OBJ_associatedName */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x27,/* [3609] OBJ_homePostalAddress */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x28,/* [3619] OBJ_personalTitle */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x29,/* [3629] OBJ_mobileTelephoneNumber */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x2A,/* [3639] OBJ_pagerTelephoneNumber */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x2B,/* [3649] OBJ_friendlyCountryName */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x2D,/* [3659] OBJ_organizationalStatus */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x2E,/* [3669] OBJ_janetMailbox */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x2F,/* [3679] OBJ_mailPreferenceOption */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x30,/* [3689] OBJ_buildingName */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x31,/* [3699] OBJ_dSAQuality */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x32,/* [3709] OBJ_singleLevelQuality */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x33,/* [3719] OBJ_subtreeMinimumQuality */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x34,/* [3729] OBJ_subtreeMaximumQuality */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x35,/* [3739] OBJ_personalSignature */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x36,/* [3749] OBJ_dITRedirect */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x37,/* [3759] OBJ_audio */
0x09,0x92,0x26,0x89,0x93,0xF2,0x2C,0x64,0x01,0x38,/* [3769] OBJ_documentPublisher */
0x55,0x04,0x2D,                              /* [3779] OBJ_x500UniqueIdentifier */
0x2B,0x06,0x01,0x07,0x01,                    /* [3782] OBJ_mime_mhs */
0x2B,0x06,0x01,0x07,0x01,0x01,               /* [3787] OBJ_mime_mhs_headings */
0x2B,0x06,0x01,0x07,0x01,0x02,               /* [3793] OBJ_mime_mhs_bodies */
0x2B,0x06,0x01,0x07,0x01,0x01,0x01,          /* [3799] OBJ_id_hex_partial_message */
0x2B,0x06,0x01,0x07,0x01,0x01,0x02,          /* [3806] OBJ_id_hex_multipart_message */
0x55,0x04,0x2C,                              /* [3813] OBJ_generationQualifier */
0x55,0x04,0x41,                              /* [3816] OBJ_pseudonym */
0x67,0x2A,                                   /* [3819] OBJ_id_set */
0x67,0x2A,0x00,                              /* [3821] OBJ_set_ctype */
0x67,0x2A,0x01,                              /* [3824] OBJ_set_msgExt */
0x67,0x2A,0x03,                              /* [3827] OBJ_set_attr */
0x67,0x2A,0x05,                              /* [3830] OBJ_set_policy */
0x67,0x2A,0x07,                              /* [3833] OBJ_set_certExt */
0x67,0x2A,0x08,                              /* [3836] OBJ_set_brand */
0x67,0x2A,0x00,0x00,                         /* [3839] OBJ_setct_PANData */
0x67,0x2A,0x00,0x01,                         /* [3843] OBJ_setct_PANToken */
0x67,0x2A,0x00,0x02,                         /* [3847] OBJ_setct_PANOnly */
0x67,0x2A,0x00,0x03,                         /* [3851] OBJ_setct_OIData */
0x67,0x2A,0x00,0x04,                         /* [3855] OBJ_setct_PI */
0x67,0x2A,0x00,0x05,                         /* [3859] OBJ_setct_PIData */
0x67,0x2A,0x00,0x06,                         /* [3863] OBJ_setct_PIDataUnsigned */
0x67,0x2A,0x00,0x07,                         /* [3867] OBJ_setct_HODInput */
0x67,0x2A,0x00,0x08,                         /* [3871] OBJ_setct_AuthResBaggage */
0x67,0x2A,0x00,0x09,                         /* [3875] OBJ_setct_AuthRevReqBaggage */
0x67,0x2A,0x00,0x0A,                         /* [3879] OBJ_setct_AuthRevResBaggage */
0x67,0x2A,0x00,0x0B,                         /* [3883] OBJ_setct_CapTokenSeq */
0x67,0x2A,0x00,0x0C,                         /* [3887] OBJ_setct_PInitResData */
0x67,0x2A,0x00,0x0D,                         /* [3891] OBJ_setct_PI_TBS */
0x67,0x2A,0x00,0x0E,                         /* [3895] OBJ_setct_PResData */
0x67,0x2A,0x00,0x10,                         /* [3899] OBJ_setct_AuthReqTBS */
0x67,0x2A,0x00,0x11,                         /* [3903] OBJ_setct_AuthResTBS */
0x67,0x2A,0x00,0x12,                         /* [3907] OBJ_setct_AuthResTBSX */
0x67,0x2A,0x00,0x13,                         /* [3911] OBJ_setct_AuthTokenTBS */
0x67,0x2A,0x00,0x14,                         /* [3915] OBJ_setct_CapTokenData */
0x67,0x2A,0x00,0x15,                         /* [3919] OBJ_setct_CapTokenTBS */
0x67,0x2A,0x00,0x16,                         /* [3923] OBJ_setct_AcqCardCodeMsg */
0x67,0x2A,0x00,0x17,                         /* [3927] OBJ_setct_AuthRevReqTBS */
0x67,0x2A,0x00,0x18,                         /* [3931] OBJ_setct_AuthRevResData */
0x67,0x2A,0x00,0x19,                         /* [3935] OBJ_setct_AuthRevResTBS */
0x67,0x2A,0x00,0x1A,                         /* [3939] OBJ_setct_CapReqTBS */
0x67,0x2A,0x00,0x1B,                         /* [3943] OBJ_setct_CapReqTBSX */
0x67,0x2A,0x00,0x1C,                         /* [3947] OBJ_setct_CapResData */
0x67,0x2A,0x00,0x1D,                         /* [3951] OBJ_setct_CapRevReqTBS */
0x67,0x2A,0x00,0x1E,                         /* [3955] OBJ_setct_CapRevReqTBSX */
0x67,0x2A,0x00,0x1F,                         /* [3959] OBJ_setct_CapRevResData */
0x67,0x2A,0x00,0x20,                         /* [3963] OBJ_setct_CredReqTBS */
0x67,0x2A,0x00,0x21,                         /* [3967] OBJ_setct_CredReqTBSX */
0x67,0x2A,0x00,0x22,                         /* [3971] OBJ_setct_CredResData */
0x67,0x2A,0x00,0x23,                         /* [3975] OBJ_setct_CredRevReqTBS */
0x67,0x2A,0x00,0x24,                         /* [3979] OBJ_setct_CredRevReqTBSX */
0x67,0x2A,0x00,0x25,                         /* [3983] OBJ_setct_CredRevResData */
0x67,0x2A,0x00,0x26,                         /* [3987] OBJ_setct_PCertReqData */
0x67,0x2A,0x00,0x27,                         /* [3991] OBJ_setct_PCertResTBS */
0x67,0x2A,0x00,0x28,                         /* [3995] OBJ_setct_BatchAdminReqData */
0x67,0x2A,0x00,0x29,                         /* [3999] OBJ_setct_BatchAdminResData */
0x67,0x2A,0x00,0x2A,                         /* [4003] OBJ_setct_CardCInitResTBS */
0x67,0x2A,0x00,0x2B,                         /* [4007] OBJ_setct_MeAqCInitResTBS */
0x67,0x2A,0x00,0x2C,                         /* [4011] OBJ_setct_RegFormResTBS */
0x67,0x2A,0x00,0x2D,                         /* [4015] OBJ_setct_CertReqData */
0x67,0x2A,0x00,0x2E,                         /* [4019] OBJ_setct_CertReqTBS */
0x67,0x2A,0x00,0x2F,                         /* [4023] OBJ_setct_CertResData */
0x67,0x2A,0x00,0x30,                         /* [4027] OBJ_setct_CertInqReqTBS */
0x67,0x2A,0x00,0x31,                         /* [4031] OBJ_setct_ErrorTBS */
0x67,0x2A,0x00,0x32,                         /* [4035] OBJ_setct_PIDualSignedTBE */
0x67,0x2A,0x00,0x33,                         /* [4039] OBJ_setct_PIUnsignedTBE */
0x67,0x2A,0x00,0x34,                         /* [4043] OBJ_setct_AuthReqTBE */
0x67,0x2A,0x00,0x35,                         /* [4047] OBJ_setct_AuthResTBE */
0x67,0x2A,0x00,0x36,                         /* [4051] OBJ_setct_AuthResTBEX */
0x67,0x2A,0x00,0x37,                         /* [4055] OBJ_setct_AuthTokenTBE */
0x67,0x2A,0x00,0x38,                         /* [4059] OBJ_setct_CapTokenTBE */
0x67,0x2A,0x00,0x39,                         /* [4063] OBJ_setct_CapTokenTBEX */
0x67,0x2A,0x00,0x3A,                         /* [4067] OBJ_setct_AcqCardCodeMsgTBE */
0x67,0x2A,0x00,0x3B,                         /* [4071] OBJ_setct_AuthRevReqTBE */
0x67,0x2A,0x00,0x3C,                         /* [4075] OBJ_setct_AuthRevResTBE */
0x67,0x2A,0x00,0x3D,                         /* [4079] OBJ_setct_AuthRevResTBEB */
0x67,0x2A,0x00,0x3E,                         /* [4083] OBJ_setct_CapReqTBE */
0x67,0x2A,0x00,0x3F,                         /* [4087] OBJ_setct_CapReqTBEX */
0x67,0x2A,0x00,0x40,                         /* [4091] OBJ_setct_CapResTBE */
0x67,0x2A,0x00,0x41,                         /* [4095] OBJ_setct_CapRevReqTBE */
0x67,0x2A,0x00,0x42,                         /* [4099] OBJ_setct_CapRevReqTBEX */
0x67,0x2A,0x00,0x43,                         /* [4103] OBJ_setct_CapRevResTBE */
0x67,0x2A,0x00,0x44,                         /* [4107] OBJ_setct_CredReqTBE */
0x67,0x2A,0x00,0x45,                         /* [4111] OBJ_setct_CredReqTBEX */
0x67,0x2A,0x00,0x46,                         /* [4115] OBJ_setct_CredResTBE */
0x67,0x2A,0x00,0x47,                         /* [4119] OBJ_setct_CredRevReqTBE */
0x67,0x2A,0x00,0x48,                         /* [4123] OBJ_setct_CredRevReqTBEX */
0x67,0x2A,0x00,0x49,                         /* [4127] OBJ_setct_CredRevResTBE */
0x67,0x2A,0x00,0x4A,                         /* [4131] OBJ_setct_BatchAdminReqTBE */
0x67,0x2A,0x00,0x4B,                         /* [4135] OBJ_setct_BatchAdminResTBE */
0x67,0x2A,0x00,0x4C,                         /* [4139] OBJ_setct_RegFormReqTBE */
0x67,0x2A,0x00,0x4D,                         /* [4143] OBJ_setct_CertReqTBE */
0x67,0x2A,0x00,0x4E,                         /* [4147] OBJ_setct_CertReqTBEX */
0x67,0x2A,0x00,0x4F,                         /* [4151] OBJ_setct_CertResTBE */
0x67,0x2A,0x00,0x50,                         /* [4155] OBJ_setct_CRLNotificationTBS */
0x67,0x2A,0x00,0x51,                         /* [4159] OBJ_setct_CRLNotificationResTBS */
0x67,0x2A,0x00,0x52,                         /* [4163] OBJ_setct_BCIDistributionTBS */
0x67,0x2A,0x01,0x01,                         /* [4167] OBJ_setext_genCrypt */
0x67,0x2A,0x01,0x03,                         /* [4171] OBJ_setext_miAuth */
0x67,0x2A,0x01,0x04,                         /* [4175] OBJ_setext_pinSecure */
0x67,0x2A,0x01,0x05,                         /* [4179] OBJ_setext_pinAny */
0x67,0x2A,0x01,0x07,                         /* [4183] OBJ_setext_track2 */
0x67,0x2A,0x01,0x08,                         /* [4187] OBJ_setext_cv */
0x67,0x2A,0x05,0x00,                         /* [4191] OBJ_set_policy_root */
0x67,0x2A,0x07,0x00,                         /* [4195] OBJ_setCext_hashedRoot */
0x67,0x2A,0x07,0x01,                         /* [4199] OBJ_setCext_certType */
0x67,0x2A,0x07,0x02,                         /* [4203] OBJ_setCext_merchData */
0x67,0x2A,0x07,0x03,                         /* [4207] OBJ_setCext_cCertRequired */
0x67,0x2A,0x07,0x04,                         /* [4211] OBJ_setCext_tunneling */
0x67,0x2A,0x07,0x05,                         /* [4215] OBJ_setCext_setExt */
0x67,0x2A,0x07,0x06,                         /* [4219] OBJ_setCext_setQualf */
0x67,0x2A,0x07,0x07,                         /* [4223] OBJ_setCext_PGWYcapabilities */
0x67,0x2A,0x07,0x08,                         /* [4227] OBJ_setCext_TokenIdentifier */
0x67,0x2A,0x07,0x09,                         /* [4231] OBJ_setCext_Track2Data */
0x67,0x2A,0x07,0x0A,                         /* [4235] OBJ_setCext_TokenType */
0x67,0x2A,0x07,0x0B,                         /* [4239] OBJ_setCext_IssuerCapabilities */
0x67,0x2A,0x03,0x00,                         /* [4243] OBJ_setAttr_Cert */
0x67,0x2A,0x03,0x01,                         /* [4247] OBJ_setAttr_PGWYcap */
0x67,0x2A,0x03,0x02,                         /* [4251] OBJ_setAttr_TokenType */
0x67,0x2A,0x03,0x03,                         /* [4255] OBJ_setAttr_IssCap */
0x67,0x2A,0x03,0x00,0x00,                    /* [4259] OBJ_set_rootKeyThumb */
0x67,0x2A,0x03,0x00,0x01,                    /* [4264] OBJ_set_addPolicy */
0x67,0x2A,0x03,0x02,0x01,                    /* [4269] OBJ_setAttr_Token_EMV */
0x67,0x2A,0x03,0x02,0x02,                    /* [4274] OBJ_setAttr_Token_B0Prime */
0x67,0x2A,0x03,0x03,0x03,                    /* [4279] OBJ_setAttr_IssCap_CVM */
0x67,0x2A,0x03,0x03,0x04,                    /* [4284] OBJ_setAttr_IssCap_T2 */
0x67,0x2A,0x03,0x03,0x05,                    /* [4289] OBJ_setAttr_IssCap_Sig */
0x67,0x2A,0x03,0x03,0x03,0x01,               /* [4294] OBJ_setAttr_GenCryptgrm */
0x67,0x2A,0x03,0x03,0x04,0x01,               /* [4300] OBJ_setAttr_T2Enc */
0x67,0x2A,0x03,0x03,0x04,0x02,               /* [4306] OBJ_setAttr_T2cleartxt */
0x67,0x2A,0x03,0x03,0x05,0x01,               /* [4312] OBJ_setAttr_TokICCsig */
0x67,0x2A,0x03,0x03,0x05,0x02,               /* [4318] OBJ_setAttr_SecDevSig */
0x67,0x2A,0x08,0x01,                         /* [4324] OBJ_set_brand_IATA_ATA */
0x67,0x2A,0x08,0x1E,                         /* [4328] OBJ_set_brand_Diners */
0x67,0x2A,0x08,0x22,                         /* [4332] OBJ_set_brand_AmericanExpress */
0x67,0x2A,0x08,0x23,                         /* [4336] OBJ_set_brand_JCB */
0x67,0x2A,0x08,0x04,                         /* [4340] OBJ_set_brand_Visa */
0x67,0x2A,0x08,0x05,                         /* [4344] OBJ_set_brand_MasterCard */
0x67,0x2A,0x08,0xAE,0x7B,                    /* [4348] OBJ_set_brand_Novus */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x03,0x0A,     /* [4353] OBJ_des_cdmf */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x06,/* [4361] OBJ_rsaOAEPEncryptionSET */
0x67,                                        /* [4370] OBJ_international_organizations */
0x2B,0x06,0x01,0x04,0x01,0x82,0x37,0x14,0x02,0x02,/* [4371] OBJ_ms_smartcard_login */
0x2B,0x06,0x01,0x04,0x01,0x82,0x37,0x14,0x02,0x03,/* [4381] OBJ_ms_upn */
0x55,0x04,0x09,                              /* [4391] OBJ_streetAddress */
0x55,0x04,0x11,                              /* [4394] OBJ_postalCode */
0x2B,0x06,0x01,0x05,0x05,0x07,0x15,          /* [4397] OBJ_id_ppl */
0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x0E,     /* [4404] OBJ_proxyCertInfo */
0x2B,0x06,0x01,0x05,0x05,0x07,0x15,0x00,     /* [4412] OBJ_id_ppl_anyLanguage */
0x2B,0x06,0x01,0x05,0x05,0x07,0x15,0x01,     /* [4420] OBJ_id_ppl_inheritAll */
0x55,0x1D,0x1E,                              /* [4428] OBJ_name_constraints */
0x2B,0x06,0x01,0x05,0x05,0x07,0x15,0x02,     /* [4431] OBJ_Independent */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x0B,/* [4439] OBJ_sha256WithRSAEncryption */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x0C,/* [4448] OBJ_sha384WithRSAEncryption */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x0D,/* [4457] OBJ_sha512WithRSAEncryption */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x0E,/* [4466] OBJ_sha224WithRSAEncryption */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x02,0x01,/* [4475] OBJ_sha256 */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x02,0x02,/* [4484] OBJ_sha384 */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x02,0x03,/* [4493] OBJ_sha512 */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x02,0x04,/* [4502] OBJ_sha224 */
0x2B,                                        /* [4511] OBJ_identified_organization */
0x2B,0x81,0x04,                              /* [4512] OBJ_certicom_arc */
0x67,0x2B,                                   /* [4515] OBJ_wap */
0x67,0x2B,0x01,                              /* [4517] OBJ_wap_wsg */
0x2A,0x86,0x48,0xCE,0x3D,0x01,0x02,0x03,     /* [4520] OBJ_X9_62_id_characteristic_two_basis */
0x2A,0x86,0x48,0xCE,0x3D,0x01,0x02,0x03,0x01,/* [4528] OBJ_X9_62_onBasis */
0x2A,0x86,0x48,0xCE,0x3D,0x01,0x02,0x03,0x02,/* [4537] OBJ_X9_62_tpBasis */
0x2A,0x86,0x48,0xCE,0x3D,0x01,0x02,0x03,0x03,/* [4546] OBJ_X9_62_ppBasis */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x01,     /* [4555] OBJ_X9_62_c2pnb163v1 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x02,     /* [4563] OBJ_X9_62_c2pnb163v2 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x03,     /* [4571] OBJ_X9_62_c2pnb163v3 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x04,     /* [4579] OBJ_X9_62_c2pnb176v1 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x05,     /* [4587] OBJ_X9_62_c2tnb191v1 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x06,     /* [4595] OBJ_X9_62_c2tnb191v2 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x07,     /* [4603] OBJ_X9_62_c2tnb191v3 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x08,     /* [4611] OBJ_X9_62_c2onb191v4 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x09,     /* [4619] OBJ_X9_62_c2onb191v5 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x0A,     /* [4627] OBJ_X9_62_c2pnb208w1 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x0B,     /* [4635] OBJ_X9_62_c2tnb239v1 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x0C,     /* [4643] OBJ_X9_62_c2tnb239v2 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x0D,     /* [4651] OBJ_X9_62_c2tnb239v3 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x0E,     /* [4659] OBJ_X9_62_c2onb239v4 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x0F,     /* [4667] OBJ_X9_62_c2onb239v5 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x10,     /* [4675] OBJ_X9_62_c2pnb272w1 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x11,     /* [4683] OBJ_X9_62_c2pnb304w1 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x12,     /* [4691] OBJ_X9_62_c2tnb359v1 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x13,     /* [4699] OBJ_X9_62_c2pnb368w1 */
0x2A,0x86,0x48,0xCE,0x3D,0x03,0x00,0x14,     /* [4707] OBJ_X9_62_c2tnb431r1 */
0x2B,0x81,0x04,0x00,0x06,                    /* [4715] OBJ_secp112r1 */
0x2B,0x81,0x04,0x00,0x07,                    /* [4720] OBJ_secp112r2 */
0x2B,0x81,0x04,0x00,0x1C,                    /* [4725] OBJ_secp128r1 */
0x2B,0x81,0x04,0x00,0x1D,                    /* [4730] OBJ_secp128r2 */
0x2B,0x81,0x04,0x00,0x09,                    /* [4735] OBJ_secp160k1 */
0x2B,0x81,0x04,0x00,0x08,                    /* [4740] OBJ_secp160r1 */
0x2B,0x81,0x04,0x00,0x1E,                    /* [4745] OBJ_secp160r2 */
0x2B,0x81,0x04,0x00,0x1F,                    /* [4750] OBJ_secp192k1 */
0x2B,0x81,0x04,0x00,0x20,                    /* [4755] OBJ_secp224k1 */
0x2B,0x81,0x04,0x00,0x21,                    /* [4760] OBJ_secp224r1 */
0x2B,0x81,0x04,0x00,0x0A,                    /* [4765] OBJ_secp256k1 */
0x2B,0x81,0x04,0x00,0x22,                    /* [4770] OBJ_secp384r1 */
0x2B,0x81,0x04,0x00,0x23,                    /* [4775] OBJ_secp521r1 */
0x2B,0x81,0x04,0x00,0x04,                    /* [4780] OBJ_sect113r1 */
0x2B,0x81,0x04,0x00,0x05,                    /* [4785] OBJ_sect113r2 */
0x2B,0x81,0x04,0x00,0x16,                    /* [4790] OBJ_sect131r1 */
0x2B,0x81,0x04,0x00,0x17,                    /* [4795] OBJ_sect131r2 */
0x2B,0x81,0x04,0x00,0x01,                    /* [4800] OBJ_sect163k1 */
0x2B,0x81,0x04,0x00,0x02,                    /* [4805] OBJ_sect163r1 */
0x2B,0x81,0x04,0x00,0x0F,                    /* [4810] OBJ_sect163r2 */
0x2B,0x81,0x04,0x00,0x18,                    /* [4815] OBJ_sect193r1 */
0x2B,0x81,0x04,0x00,0x19,                    /* [4820] OBJ_sect193r2 */
0x2B,0x81,0x04,0x00,0x1A,                    /* [4825] OBJ_sect233k1 */
0x2B,0x81,0x04,0x00,0x1B,                    /* [4830] OBJ_sect233r1 */
0x2B,0x81,0x04,0x00,0x03,                    /* [4835] OBJ_sect239k1 */
0x2B,0x81,0x04,0x00,0x10,                    /* [4840] OBJ_sect283k1 */
0x2B,0x81,0x04,0x00,0x11,                    /* [4845] OBJ_sect283r1 */
0x2B,0x81,0x04,0x00,0x24,                    /* [4850] OBJ_sect409k1 */
0x2B,0x81,0x04,0x00,0x25,                    /* [4855] OBJ_sect409r1 */
0x2B,0x81,0x04,0x00,0x26,                    /* [4860] OBJ_sect571k1 */
0x2B,0x81,0x04,0x00,0x27,                    /* [4865] OBJ_sect571r1 */
0x67,0x2B,0x01,0x04,0x01,                    /* [4870] OBJ_wap_wsg_idm_ecid_wtls1 */
0x67,0x2B,0x01,0x04,0x03,                    /* [4875] OBJ_wap_wsg_idm_ecid_wtls3 */
0x67,0x2B,0x01,0x04,0x04,                    /* [4880] OBJ_wap_wsg_idm_ecid_wtls4 */
0x67,0x2B,0x01,0x04,0x05,                    /* [4885] OBJ_wap_wsg_idm_ecid_wtls5 */
0x67,0x2B,0x01,0x04,0x06,                    /* [4890] OBJ_wap_wsg_idm_ecid_wtls6 */
0x67,0x2B,0x01,0x04,0x07,                    /* [4895] OBJ_wap_wsg_idm_ecid_wtls7 */
0x67,0x2B,0x01,0x04,0x08,                    /* [4900] OBJ_wap_wsg_idm_ecid_wtls8 */
0x67,0x2B,0x01,0x04,0x09,                    /* [4905] OBJ_wap_wsg_idm_ecid_wtls9 */
0x67,0x2B,0x01,0x04,0x0A,                    /* [4910] OBJ_wap_wsg_idm_ecid_wtls10 */
0x67,0x2B,0x01,0x04,0x0B,                    /* [4915] OBJ_wap_wsg_idm_ecid_wtls11 */
0x67,0x2B,0x01,0x04,0x0C,                    /* [4920] OBJ_wap_wsg_idm_ecid_wtls12 */
0x55,0x1D,0x20,0x00,                         /* [4925] OBJ_any_policy */
0x55,0x1D,0x21,                              /* [4929] OBJ_policy_mappings */
0x55,0x1D,0x36,                              /* [4932] OBJ_inhibit_any_policy */
0x2A,0x83,0x08,0x8C,0x9A,0x4B,0x3D,0x01,0x01,0x01,0x02,/* [4935] OBJ_camellia_128_cbc */
0x2A,0x83,0x08,0x8C,0x9A,0x4B,0x3D,0x01,0x01,0x01,0x03,/* [4946] OBJ_camellia_192_cbc */
0x2A,0x83,0x08,0x8C,0x9A,0x4B,0x3D,0x01,0x01,0x01,0x04,/* [4957] OBJ_camellia_256_cbc */
0x03,0xA2,0x31,0x05,0x03,0x01,0x09,0x01,     /* [4968] OBJ_camellia_128_ecb */
0x03,0xA2,0x31,0x05,0x03,0x01,0x09,0x15,     /* [4976] OBJ_camellia_192_ecb */
0x03,0xA2,0x31,0x05,0x03,0x01,0x09,0x29,     /* [4984] OBJ_camellia_256_ecb */
0x03,0xA2,0x31,0x05,0x03,0x01,0x09,0x04,     /* [4992] OBJ_camellia_128_cfb128 */
0x03,0xA2,0x31,0x05,0x03,0x01,0x09,0x18,     /* [5000] OBJ_camellia_192_cfb128 */
0x03,0xA2,0x31,0x05,0x03,0x01,0x09,0x2C,     /* [5008] OBJ_camellia_256_cfb128 */
0x03,0xA2,0x31,0x05,0x03,0x01,0x09,0x03,     /* [5016] OBJ_camellia_128_ofb128 */
0x03,0xA2,0x31,0x05,0x03,0x01,0x09,0x17,     /* [5024] OBJ_camellia_192_ofb128 */
0x03,0xA2,0x31,0x05,0x03,0x01,0x09,0x2B,     /* [5032] OBJ_camellia_256_ofb128 */
0x55,0x1D,0x09,                              /* [5040] OBJ_subject_directory_attributes */
0x55,0x1D,0x1C,                              /* [5043] OBJ_issuing_distribution_point */
0x55,0x1D,0x1D,                              /* [5046] OBJ_certificate_issuer */
0x2B,0x06,0x01,0x05,0x05,0x08,0x01,0x01,     /* [5049] OBJ_hmac_md5 */
0x2B,0x06,0x01,0x05,0x05,0x08,0x01,0x02,     /* [5057] OBJ_hmac_sha1 */
0x2A,0x86,0x48,0x86,0xF6,0x7D,0x07,0x42,0x0D,/* [5065] OBJ_id_PasswordBasedMAC */
0x2A,0x86,0x48,0x86,0xF6,0x7D,0x07,0x42,0x1E,/* [5074] OBJ_id_DHBasedMac */
0x2B,0x06,0x01,0x05,0x05,0x07,0x04,0x10,     /* [5083] OBJ_id_it_suppLangTags */
0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x05,     /* [5091] OBJ_caRepository */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x01,0x09,/* [5099] OBJ_id_smime_ct_compressedData */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x01,0x1B,/* [5110] OBJ_id_ct_asciiTextWithCRLF */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x05,/* [5121] OBJ_id_aes128_wrap */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x19,/* [5130] OBJ_id_aes192_wrap */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x2D,/* [5139] OBJ_id_aes256_wrap */
0x2A,0x86,0x48,0xCE,0x3D,0x04,0x02,          /* [5148] OBJ_ecdsa_with_Recommended */
0x2A,0x86,0x48,0xCE,0x3D,0x04,0x03,          /* [5155] OBJ_ecdsa_with_Specified */
0x2A,0x86,0x48,0xCE,0x3D,0x04,0x03,0x01,     /* [5162] OBJ_ecdsa_with_SHA224 */
0x2A,0x86,0x48,0xCE,0x3D,0x04,0x03,0x02,     /* [5170] OBJ_ecdsa_with_SHA256 */
0x2A,0x86,0x48,0xCE,0x3D,0x04,0x03,0x03,     /* [5178] OBJ_ecdsa_with_SHA384 */
0x2A,0x86,0x48,0xCE,0x3D,0x04,0x03,0x04,     /* [5186] OBJ_ecdsa_with_SHA512 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x02,0x06,     /* [5194] OBJ_hmacWithMD5 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x02,0x08,     /* [5202] OBJ_hmacWithSHA224 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x02,0x09,     /* [5210] OBJ_hmacWithSHA256 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x02,0x0A,     /* [5218] OBJ_hmacWithSHA384 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x02,0x0B,     /* [5226] OBJ_hmacWithSHA512 */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x03,0x01,/* [5234] OBJ_dsa_with_SHA224 */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x03,0x02,/* [5243] OBJ_dsa_with_SHA256 */
0x28,0xCF,0x06,0x03,0x00,0x37,               /* [5252] OBJ_whirlpool */
0x2A,0x85,0x03,0x02,0x02,                    /* [5258] OBJ_cryptopro */
0x2A,0x85,0x03,0x02,0x09,                    /* [5263] OBJ_cryptocom */
0x2A,0x85,0x03,0x02,0x02,0x03,               /* [5268] OBJ_id_GostR3411_94_with_GostR3410_2001 */
0x2A,0x85,0x03,0x02,0x02,0x04,               /* [5274] OBJ_id_GostR3411_94_with_GostR3410_94 */
0x2A,0x85,0x03,0x02,0x02,0x09,               /* [5280] OBJ_id_GostR3411_94 */
0x2A,0x85,0x03,0x02,0x02,0x0A,               /* [5286] OBJ_id_HMACGostR3411_94 */
0x2A,0x85,0x03,0x02,0x02,0x13,               /* [5292] OBJ_id_GostR3410_2001 */
0x2A,0x85,0x03,0x02,0x02,0x14,               /* [5298] OBJ_id_GostR3410_94 */
0x2A,0x85,0x03,0x02,0x02,0x15,               /* [5304] OBJ_id_Gost28147_89 */
0x2A,0x85,0x03,0x02,0x02,0x16,               /* [5310] OBJ_id_Gost28147_89_MAC */
0x2A,0x85,0x03,0x02,0x02,0x17,               /* [5316] OBJ_id_GostR3411_94_prf */
0x2A,0x85,0x03,0x02,0x02,0x62,               /* [5322] OBJ_id_GostR3410_2001DH */
0x2A,0x85,0x03,0x02,0x02,0x63,               /* [5328] OBJ_id_GostR3410_94DH */
0x2A,0x85,0x03,0x02,0x02,0x0E,0x01,          /* [5334] OBJ_id_Gost28147_89_CryptoPro_KeyMeshing */
0x2A,0x85,0x03,0x02,0x02,0x0E,0x00,          /* [5341] OBJ_id_Gost28147_89_None_KeyMeshing */
0x2A,0x85,0x03,0x02,0x02,0x1E,0x00,          /* [5348] OBJ_id_GostR3411_94_TestParamSet */
0x2A,0x85,0x03,0x02,0x02,0x1E,0x01,          /* [5355] OBJ_id_GostR3411_94_CryptoProParamSet */
0x2A,0x85,0x03,0x02,0x02,0x1F,0x00,          /* [5362] OBJ_id_Gost28147_89_TestParamSet */
0x2A,0x85,0x03,0x02,0x02,0x1F,0x01,          /* [5369] OBJ_id_Gost28147_89_CryptoPro_A_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x1F,0x02,          /* [5376] OBJ_id_Gost28147_89_CryptoPro_B_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x1F,0x03,          /* [5383] OBJ_id_Gost28147_89_CryptoPro_C_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x1F,0x04,          /* [5390] OBJ_id_Gost28147_89_CryptoPro_D_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x1F,0x05,          /* [5397] OBJ_id_Gost28147_89_CryptoPro_Oscar_1_1_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x1F,0x06,          /* [5404] OBJ_id_Gost28147_89_CryptoPro_Oscar_1_0_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x1F,0x07,          /* [5411] OBJ_id_Gost28147_89_CryptoPro_RIC_1_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x20,0x00,          /* [5418] OBJ_id_GostR3410_94_TestParamSet */
0x2A,0x85,0x03,0x02,0x02,0x20,0x02,          /* [5425] OBJ_id_GostR3410_94_CryptoPro_A_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x20,0x03,          /* [5432] OBJ_id_GostR3410_94_CryptoPro_B_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x20,0x04,          /* [5439] OBJ_id_GostR3410_94_CryptoPro_C_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x20,0x05,          /* [5446] OBJ_id_GostR3410_94_CryptoPro_D_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x21,0x01,          /* [5453] OBJ_id_GostR3410_94_CryptoPro_XchA_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x21,0x02,          /* [5460] OBJ_id_GostR3410_94_CryptoPro_XchB_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x21,0x03,          /* [5467] OBJ_id_GostR3410_94_CryptoPro_XchC_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x23,0x00,          /* [5474] OBJ_id_GostR3410_2001_TestParamSet */
0x2A,0x85,0x03,0x02,0x02,0x23,0x01,          /* [5481] OBJ_id_GostR3410_2001_CryptoPro_A_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x23,0x02,          /* [5488] OBJ_id_GostR3410_2001_CryptoPro_B_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x23,0x03,          /* [5495] OBJ_id_GostR3410_2001_CryptoPro_C_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x24,0x00,          /* [5502] OBJ_id_GostR3410_2001_CryptoPro_XchA_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x24,0x01,          /* [5509] OBJ_id_GostR3410_2001_CryptoPro_XchB_ParamSet */
0x2A,0x85,0x03,0x02,0x02,0x14,0x01,          /* [5516] OBJ_id_GostR3410_94_a */
0x2A,0x85,0x03,0x02,0x02,0x14,0x02,          /* [5523] OBJ_id_GostR3410_94_aBis */
0x2A,0x85,0x03,0x02,0x02,0x14,0x03,          /* [5530] OBJ_id_GostR3410_94_b */
0x2A,0x85,0x03,0x02,0x02,0x14,0x04,          /* [5537] OBJ_id_GostR3410_94_bBis */
0x2A,0x85,0x03,0x02,0x09,0x01,0x06,0x01,     /* [5544] OBJ_id_Gost28147_89_cc */
0x2A,0x85,0x03,0x02,0x09,0x01,0x05,0x03,     /* [5552] OBJ_id_GostR3410_94_cc */
0x2A,0x85,0x03,0x02,0x09,0x01,0x05,0x04,     /* [5560] OBJ_id_GostR3410_2001_cc */
0x2A,0x85,0x03,0x02,0x09,0x01,0x03,0x03,     /* [5568] OBJ_id_GostR3411_94_with_GostR3410_94_cc */
0x2A,0x85,0x03,0x02,0x09,0x01,0x03,0x04,     /* [5576] OBJ_id_GostR3411_94_with_GostR3410_2001_cc */
0x2A,0x85,0x03,0x02,0x09,0x01,0x08,0x01,     /* [5584] OBJ_id_GostR3410_2001_ParamSet_cc */
0x2B,0x06,0x01,0x04,0x01,0x82,0x37,0x11,0x02,/* [5592] OBJ_LocalKeySet */
0x55,0x1D,0x2E,                              /* [5601] OBJ_freshest_crl */
0x2B,0x06,0x01,0x05,0x05,0x07,0x08,0x03,     /* [5604] OBJ_id_on_permanentIdentifier */
0x55,0x04,0x0E,                              /* [5612] OBJ_searchGuide */
0x55,0x04,0x0F,                              /* [5615] OBJ_businessCategory */
0x55,0x04,0x10,                              /* [5618] OBJ_postalAddress */
0x55,0x04,0x12,                              /* [5621] OBJ_postOfficeBox */
0x55,0x04,0x13,                              /* [5624] OBJ_physicalDeliveryOfficeName */
0x55,0x04,0x14,                              /* [5627] OBJ_telephoneNumber */
0x55,0x04,0x15,                              /* [5630] OBJ_telexNumber */
0x55,0x04,0x16,                              /* [5633] OBJ_teletexTerminalIdentifier */
0x55,0x04,0x17,                              /* [5636] OBJ_facsimileTelephoneNumber */
0x55,0x04,0x18,                              /* [5639] OBJ_x121Address */
0x55,0x04,0x19,                              /* [5642] OBJ_internationaliSDNNumber */
0x55,0x04,0x1A,                              /* [5645] OBJ_registeredAddress */
0x55,0x04,0x1B,                              /* [5648] OBJ_destinationIndicator */
0x55,0x04,0x1C,                              /* [5651] OBJ_preferredDeliveryMethod */
0x55,0x04,0x1D,                              /* [5654] OBJ_presentationAddress */
0x55,0x04,0x1E,                              /* [5657] OBJ_supportedApplicationContext */
0x55,0x04,0x1F,                              /* [5660] OBJ_member */
0x55,0x04,0x20,                              /* [5663] OBJ_owner */
0x55,0x04,0x21,                              /* [5666] OBJ_roleOccupant */
0x55,0x04,0x22,                              /* [5669] OBJ_seeAlso */
0x55,0x04,0x23,                              /* [5672] OBJ_userPassword */
0x55,0x04,0x24,                              /* [5675] OBJ_userCertificate */
0x55,0x04,0x25,                              /* [5678] OBJ_cACertificate */
0x55,0x04,0x26,                              /* [5681] OBJ_authorityRevocationList */
0x55,0x04,0x27,                              /* [5684] OBJ_certificateRevocationList */
0x55,0x04,0x28,                              /* [5687] OBJ_crossCertificatePair */
0x55,0x04,0x2F,                              /* [5690] OBJ_enhancedSearchGuide */
0x55,0x04,0x30,                              /* [5693] OBJ_protocolInformation */
0x55,0x04,0x31,                              /* [5696] OBJ_distinguishedName */
0x55,0x04,0x32,                              /* [5699] OBJ_uniqueMember */
0x55,0x04,0x33,                              /* [5702] OBJ_houseIdentifier */
0x55,0x04,0x34,                              /* [5705] OBJ_supportedAlgorithms */
0x55,0x04,0x35,                              /* [5708] OBJ_deltaRevocationList */
0x55,0x04,0x36,                              /* [5711] OBJ_dmdName */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x10,0x03,0x09,/* [5714] OBJ_id_alg_PWRI_KEK */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x06,/* [5725] OBJ_aes_128_gcm */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x07,/* [5734] OBJ_aes_128_ccm */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x08,/* [5743] OBJ_id_aes128_wrap_pad */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x1A,/* [5752] OBJ_aes_192_gcm */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x1B,/* [5761] OBJ_aes_192_ccm */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x1C,/* [5770] OBJ_id_aes192_wrap_pad */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x2E,/* [5779] OBJ_aes_256_gcm */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x2F,/* [5788] OBJ_aes_256_ccm */
0x60,0x86,0x48,0x01,0x65,0x03,0x04,0x01,0x30,/* [5797] OBJ_id_aes256_wrap_pad */
0x2A,0x83,0x08,0x8C,0x9A,0x4B,0x3D,0x01,0x01,0x03,0x02,/* [5806] OBJ_id_camellia128_wrap */
0x2A,0x83,0x08,0x8C,0x9A,0x4B,0x3D,0x01,0x01,0x03,0x03,/* [5817] OBJ_id_camellia192_wrap */
0x2A,0x83,0x08,0x8C,0x9A,0x4B,0x3D,0x01,0x01,0x03,0x04,/* [5828] OBJ_id_camellia256_wrap */
0x55,0x1D,0x25,0x00,                         /* [5839] OBJ_anyExtendedKeyUsage */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x08,/* [5843] OBJ_mgf1 */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x0A,/* [5852] OBJ_rsassaPss */
0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x07,/* [5861] OBJ_rsaesOaep */
0x2B,0x24,                                   /* [5870] OBJ_teletrust */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,          /* [5872] OBJ_brainpool */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x01,/* [5879] OBJ_brainpoolP160r1 */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x02,/* [5888] OBJ_brainpoolP160t1 */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x03,/* [5897] OBJ_brainpoolP192r1 */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x04,/* [5906] OBJ_brainpoolP192t1 */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x05,/* [5915] OBJ_brainpoolP224r1 */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x06,/* [5924] OBJ_brainpoolP224t1 */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x07,/* [5933] OBJ_brainpoolP256r1 */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x08,/* [5942] OBJ_brainpoolP256t1 */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x09,/* [5951] OBJ_brainpoolP320r1 */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x0A,/* [5960] OBJ_brainpoolP320t1 */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x0B,/* [5969] OBJ_brainpoolP384r1 */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x0C,/* [5978] OBJ_brainpoolP384t1 */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x0D,/* [5987] OBJ_brainpoolP512r1 */
0x2B,0x24,0x03,0x03,0x02,0x08,0x01,0x01,0x0E,/* [5996] OBJ_brainpoolP512t1 */
0x2A,0x85,0x03,0x07,0x01,                    /* [6005] OBJ_tc26 */
0x2A,0x85,0x03,0x07,0x01,0x01,0x02,0x02,     /* [6010] OBJ_id_tc26_gost3411_2012_256 */
0x2A,0x85,0x03,0x07,0x01,0x01,0x02,0x03,     /* [6018] OBJ_id_tc26_gost3411_2012_512 */
0x2A,0x85,0x03,0x07,0x01,0x02,0x01,0x02,0x01,/* [6026] OBJ_id_tc26_gost_3410_2012_512_paramSetA */
0x2A,0x85,0x03,0x07,0x01,0x02,0x01,0x02,0x02,/* [6035] OBJ_id_tc26_gost_3410_2012_512_paramSetB */
0x2A,0x85,0x03,0x07,0x01,0x02,0x05,0x01,0x01,/* [6044] OBJ_id_tc26_gost_28147_param_Z */
0x2A,0x85,0x03,0x07,0x01,0x01,0x01,0x01,     /* [6053] OBJ_id_tc26_gost3410_2012_256 */
0x2A,0x85,0x03,0x07,0x01,0x01,0x01,0x02,     /* [6061] OBJ_id_tc26_gost3410_2012_512 */
0x2A,0x85,0x03,0x07,0x01,0x01,0x03,0x02,     /* [6069] OBJ_id_tc26_signwithdigest_gost3410_2012_256 */
0x2A,0x85,0x03,0x07,0x01,0x01,0x03,0x03,     /* [6077] OBJ_id_tc26_signwithdigest_gost3410_2012_512 */
0x2B,0x0E,0x03,0x02,0x09,                    /* [6085] OBJ_des_cfb64 */
};

static const ASN1_OBJECT nid_objs[NUM_NID]={
{"UNDEF","undefined",NID_undef,0,NULL,0},
{"rsadsi","RSA Data Security, Inc.",NID_rsadsi,6,&(lvalues[0]),0},
{"pkcs","RSA Data Security, Inc. PKCS",NID_pkcs,7,&(lvalues[6]),0},
{NULL,NULL,NID_undef,0,NULL,0},
{"MD5","md5",NID_md5,8,&(lvalues[13]),0},
{"RC4","rc4",NID_rc4,8,&(lvalues[21]),0},
{"rsaEncryption","rsaEncryption",NID_rsaEncryption,9,&(lvalues[29]),0},
{NULL,NULL,NID_undef,0,NULL,0},
{"RSA-MD5","md5WithRSAEncryption",NID_md5WithRSAEncryption,9,
	&(lvalues[38]),0},
{NULL,NULL,NID_undef,0,NULL,0},
{"PBE-MD5-DES","pbeWithMD5AndDES-CBC",NID_pbeWithMD5AndDES_CBC,9,
	&(lvalues[47]),0},
{"X500","directory services (X.500)",NID_X500,1,&(lvalues[56]),0},
{"X509","X509",NID_X509,2,&(lvalues[57]),0},
{"CN","commonName",NID_commonName,3,&(lvalues[59]),0},
{"C","countryName",NID_countryName,3,&(lvalues[62]),0},
{"L","localityName",NID_localityName,3,&(lvalues[65]),0},
{"ST","stateOrProvinceName",NID_stateOrProvinceName,3,&(lvalues[68]),0},
{"O","organizationName",NID_organizationName,3,&(lvalues[71]),0},
{"OU","organizationalUnitName",NID_organizationalUnitName,3,
	&(lvalues[74]),0},
{"RSA","rsa",NID_rsa,4,&(lvalues[77]),0},
{"pkcs7","pkcs7",NID_pkcs7,8,&(lvalues[81]),0},
{"pkcs7-data","pkcs7-data",NID_pkcs7_data,9,&(lvalues[89]),0},
{"pkcs7-signedData","pkcs7-signedData",NID_pkcs7_signed,9,
	&(lvalues[98]),0},
{"pkcs7-envelopedData","pkcs7-envelopedData",NID_pkcs7_enveloped,9,
	&(lvalues[107]),0},
{"pkcs7-signedAndEnvelopedData","pkcs7-signedAndEnvelopedData",
	NID_pkcs7_signedAndEnveloped,9,&(lvalues[116]),0},
{"pkcs7-digestData","pkcs7-digestData",NID_pkcs7_digest,9,
	&(lvalues[125]),0},
{"pkcs7-encryptedData","pkcs7-encryptedData",NID_pkcs7_encrypted,9,
	&(lvalues[134]),0},
{"pkcs3","pkcs3",NID_pkcs3,8,&(lvalues[143]),0},
{"dhKeyAgreement","dhKeyAgreement",NID_dhKeyAgreement,9,
	&(lvalues[151]),0},
{"DES-ECB","des-ecb",NID_des_ecb,5,&(lvalues[160]),0},
{NULL,NULL,NID_undef,0,NULL,0},
{"DES-CBC","des-cbc",NID_des_cbc,5,&(lvalues[165]),0},
{"DES-EDE","des-ede",NID_des_ede_ecb,5,&(lvalues[170]),0},
{"DES-EDE3","des-ede3",NID_des_ede3_ecb,0,NULL,0},
{"IDEA-CBC","idea-cbc",NID_idea_cbc,11,&(lvalues[175]),0},
{"IDEA-CFB","idea-cfb",NID_idea_cfb64,0,NULL,0},
{"IDEA-ECB","idea-ecb",NID_idea_ecb,0,NULL,0},
{"RC2-CBC","rc2-cbc",NID_rc2_cbc,8,&(lvalues[186]),0},
{"RC2-ECB","rc2-ecb",NID_rc2_ecb,0,NULL,0},
{"RC2-CFB","rc2-cfb",NID_rc2_cfb64,0,NULL,0},
{"RC2-OFB","rc2-ofb",NID_rc2_ofb64,0,NULL,0},
{"SHA","sha",NID_sha,5,&(lvalues[194]),0},
{"RSA-SHA","shaWithRSAEncryption",NID_shaWithRSAEncryption,5,
	&(lvalues[199]),0},
{"DES-EDE-CBC","des-ede-cbc",NID_des_ede_cbc,0,NULL,0},
{"DES-EDE3-CBC","des-ede3-cbc",NID_des_ede3_cbc,8,&(lvalues[204]),0},
{"DES-OFB","des-ofb",NID_des_ofb64,5,&(lvalues[212]),0},
{"IDEA-OFB","idea-ofb",NID_idea_ofb64,0,NULL,0},
{"pkcs9","pkcs9",NID_pkcs9,8,&(lvalues[217]),0},
{"emailAddress","emailAddress",NID_pkcs9_emailAddress,9,
	&(lvalues[225]),0},
{"unstructuredName","unstructuredName",NID_pkcs9_unstructuredName,9,
	&(lvalues[234]),0},
{"contentType","contentType",NID_pkcs9_contentType,9,&(lvalues[243]),0},
{"messageDigest","messageDigest",NID_pkcs9_messageDigest,9,
	&(lvalues[252]),0},
{"signingTime","signingTime",NID_pkcs9_signingTime,9,&(lvalues[261]),0},
{"countersignature","countersignature",NID_pkcs9_countersignature,9,
	&(lvalues[270]),0},
{"challengePassword","challengePassword",NID_pkcs9_challengePassword,
	9,&(lvalues[279]),0},
{"unstructuredAddress","unstructuredAddress",
	NID_pkcs9_unstructuredAddress,9,&(lvalues[288]),0},
{"extendedCertificateAttributes","extendedCertificateAttributes",
	NID_pkcs9_extCertAttributes,9,&(lvalues[297]),0},
{"Netscape","Netscape Communications Corp.",NID_netscape,7,
	&(lvalues[306]),0},
{"nsCertExt","Netscape Certificate Extension",
	NID_netscape_cert_extension,8,&(lvalues[313]),0},
{"nsDataType","Netscape Data Type",NID_netscape_data_type,8,
	&(lvalues[321]),0},
{"DES-EDE-CFB","des-ede-cfb",NID_des_ede_cfb64,0,NULL,0},
{"DES-EDE3-CFB","des-ede3-cfb",NID_des_ede3_cfb64,0,NULL,0},
{"DES-EDE-OFB","des-ede-ofb",NID_des_ede_ofb64,0,NULL,0},
{"DES-EDE3-OFB","des-ede3-ofb",NID_des_ede3_ofb64,0,NULL,0},
{"SHA1","sha1",NID_sha1,5,&(lvalues[329]),0},
{"RSA-SHA1","sha1WithRSAEncryption",NID_sha1WithRSAEncryption,9,
	&(lvalues[334]),0},
{"DSA-SHA","dsaWithSHA",NID_dsaWithSHA,5,&(lvalues[343]),0},
{"DSA-old","dsaEncryption-old",NID_dsa_2,5,&(lvalues[348]),0},
{"PBE-SHA1-RC2-64","pbeWithSHA1AndRC2-CBC",NID_pbeWithSHA1AndRC2_CBC,
	9,&(lvalues[353]),0},
{"PBKDF2","PBKDF2",NID_id_pbkdf2,9,&(lvalues[362]),0},
{"DSA-SHA1-old","dsaWithSHA1-old",NID_dsaWithSHA1_2,5,&(lvalues[371]),0},
{"nsCertType","Netscape Cert Type",NID_netscape_cert_type,9,
	&(lvalues[376]),0},
{"nsBaseUrl","Netscape Base Url",NID_netscape_base_url,9,
	&(lvalues[385]),0},
{"nsRevocationUrl","Netscape Revocation Url",
	NID_netscape_revocation_url,9,&(lvalues[394]),0},
{"nsCaRevocationUrl","Netscape CA Revocation Url",
	NID_netscape_ca_revocation_url,9,&(lvalues[403]),0},
{"nsRenewalUrl","Netscape Renewal Url",NID_netscape_renewal_url,9,
	&(lvalues[412]),0},
{"nsCaPolicyUrl","Netscape CA Policy Url",NID_netscape_ca_policy_url,
	9,&(lvalues[421]),0},
{"nsSslServerName","Netscape SSL Server Name",
	NID_netscape_ssl_server_name,9,&(lvalues[430]),0},
{"nsComment","Netscape Comment",NID_netscape_comment,9,&(lvalues[439]),0},
{"nsCertSequence","Netscape Certificate Sequence",
	NID_netscape_cert_sequence,9,&(lvalues[448]),0},
{"DESX-CBC","desx-cbc",NID_desx_cbc,0,NULL,0},
{"id-ce","id-ce",NID_id_ce,2,&(lvalues[457]),0},
{"subjectKeyIdentifier","X509v3 Subject Key Identifier",
	NID_subject_key_identifier,3,&(lvalues[459]),0},
{"keyUsage","X509v3 Key Usage",NID_key_usage,3,&(lvalues[462]),0},
{"privateKeyUsagePeriod","X509v3 Private Key Usage Period",
	NID_private_key_usage_period,3,&(lvalues[465]),0},
{"subjectAltName","X509v3 Subject Alternative Name",
	NID_subject_alt_name,3,&(lvalues[468]),0},
{"issuerAltName","X509v3 Issuer Alternative Name",NID_issuer_alt_name,
	3,&(lvalues[471]),0},
{"basicConstraints","X509v3 Basic Constraints",NID_basic_constraints,
	3,&(lvalues[474]),0},
{"crlNumber","X509v3 CRL Number",NID_crl_number,3,&(lvalues[477]),0},
{"certificatePolicies","X509v3 Certificate Policies",
	NID_certificate_policies,3,&(lvalues[480]),0},
{"authorityKeyIdentifier","X509v3 Authority Key Identifier",
	NID_authority_key_identifier,3,&(lvalues[483]),0},
{"BF-CBC","bf-cbc",NID_bf_cbc,9,&(lvalues[486]),0},
{"BF-ECB","bf-ecb",NID_bf_ecb,0,NULL,0},
{"BF-CFB","bf-cfb",NID_bf_cfb64,0,NULL,0},
{"BF-OFB","bf-ofb",NID_bf_ofb64,0,NULL,0},
{NULL,NULL,NID_undef,0,NULL,0},
{NULL,NULL,NID_undef,0,NULL,0},
{"RC4-40","rc4-40",NID_rc4_40,0,NULL,0},
{"RC2-40-CBC","rc2-40-cbc",NID_rc2_40_cbc,0,NULL,0},
{"GN","givenName",NID_givenName,3,&(lvalues[495]),0},
{"SN","surname",NID_surname,3,&(lvalues[498]),0},
{"initials","initials",NID_initials,3,&(lvalues[501]),0},
{NULL,NULL,NID_undef,0,NULL,0},
{"crlDistributionPoints","X509v3 CRL Distribution Points",
	NID_crl_distribution_points,3,&(lvalues[504]),0},
{"RSA-NP-MD5","md5WithRSA",NID_md5WithRSA,5,&(lvalues[507]),0},
{"serialNumber","serialNumber",NID_serialNumber,3,&(lvalues[512]),0},
{"title","title",NID_title,3,&(lvalues[515]),0},
{"description","description",NID_description,3,&(lvalues[518]),0},
{"CAST5-CBC","cast5-cbc",NID_cast5_cbc,9,&(lvalues[521]),0},
{"CAST5-ECB","cast5-ecb",NID_cast5_ecb,0,NULL,0},
{"CAST5-CFB","cast5-cfb",NID_cast5_cfb64,0,NULL,0},
{"CAST5-OFB","cast5-ofb",NID_cast5_ofb64,0,NULL,0},
{"pbeWithMD5AndCast5CBC","pbeWithMD5AndCast5CBC",
	NID_pbeWithMD5AndCast5_CBC,9,&(lvalues[530]),0},
{"DSA-SHA1","dsaWithSHA1",NID_dsaWithSHA1,7,&(lvalues[539]),0},
{"MD5-SHA1","md5-sha1",NID_md5_sha1,0,NULL,0},
{"RSA-SHA1-2","sha1WithRSA",NID_sha1WithRSA,5,&(lvalues[546]),0},
{"DSA","dsaEncryption",NID_dsa,7,&(lvalues[551]),0},
{"RIPEMD160","ripemd160",NID_ripemd160,5,&(lvalues[558]),0},
{NULL,NULL,NID_undef,0,NULL,0},
{"RSA-RIPEMD160","ripemd160WithRSA",NID_ripemd160WithRSA,6,
	&(lvalues[563]),0},
{"RC5-CBC","rc5-cbc",NID_rc5_cbc,8,&(lvalues[569]),0},
{"RC5-ECB","rc5-ecb",NID_rc5_ecb,0,NULL,0},
{"RC5-CFB","rc5-cfb",NID_rc5_cfb64,0,NULL,0},
{"RC5-OFB","rc5-ofb",NID_rc5_ofb64,0,NULL,0},
{"RLE","run length compression",NID_rle_compression,6,&(lvalues[577]),0},
{"ZLIB","zlib compression",NID_zlib_compression,11,&(lvalues[583]),0},
{"extendedKeyUsage","X509v3 Extended Key Usage",NID_ext_key_usage,3,
	&(lvalues[594]),0},
{"PKIX","PKIX",NID_id_pkix,6,&(lvalues[597]),0},
{"id-kp","id-kp",NID_id_kp,7,&(lvalues[603]),0},
{"serverAuth","TLS Web Server Authentication",NID_server_auth,8,
	&(lvalues[610]),0},
{"clientAuth","TLS Web Client Authentication",NID_client_auth,8,
	&(lvalues[618]),0},
{"codeSigning","Code Signing",NID_code_sign,8,&(lvalues[626]),0},
{"emailProtection","E-mail Protection",NID_email_protect,8,
	&(lvalues[634]),0},
{"timeStamping","Time Stamping",NID_time_stamp,8,&(lvalues[642]),0},
{"msCodeInd","Microsoft Individual Code Signing",NID_ms_code_ind,10,
	&(lvalues[650]),0},
{"msCodeCom","Microsoft Commercial Code Signing",NID_ms_code_com,10,
	&(lvalues[660]),0},
{"msCTLSign","Microsoft Trust List Signing",NID_ms_ctl_sign,10,
	&(lvalues[670]),0},
{"msSGC","Microsoft Server Gated Crypto",NID_ms_sgc,10,&(lvalues[680]),0},
{"msEFS","Microsoft Encrypted File System",NID_ms_efs,10,
	&(lvalues[690]),0},
{"nsSGC","Netscape Server Gated Crypto",NID_ns_sgc,9,&(lvalues[700]),0},
{"deltaCRL","X509v3 Delta CRL Indicator",NID_delta_crl,3,
	&(lvalues[709]),0},
{"CRLReason","X509v3 CRL Reason Code",NID_crl_reason,3,&(lvalues[712]),0},
{"invalidityDate","Invalidity Date",NID_invalidity_date,3,
	&(lvalues[715]),0},
{"SXNetID","Strong Extranet ID",NID_sxnet,5,&(lvalues[718]),0},
{"PBE-SHA1-RC4-128","pbeWithSHA1And128BitRC4",
	NID_pbe_WithSHA1And128BitRC4,10,&(lvalues[723]),0},
{"PBE-SHA1-RC4-40","pbeWithSHA1And40BitRC4",
	NID_pbe_WithSHA1And40BitRC4,10,&(lvalues[733]),0},
{"PBE-SHA1-3DES","pbeWithSHA1And3-KeyTripleDES-CBC",
	NID_pbe_WithSHA1And3_Key_TripleDES_CBC,10,&(lvalues[743]),0},
{"PBE-SHA1-2DES","pbeWithSHA1And2-KeyTripleDES-CBC",
	NID_pbe_WithSHA1And2_Key_TripleDES_CBC,10,&(lvalues[753]),0},
{"PBE-SHA1-RC2-128","pbeWithSHA1And128BitRC2-CBC",
	NID_pbe_WithSHA1And128BitRC2_CBC,10,&(lvalues[763]),0},
{"PBE-SHA1-RC2-40","pbeWithSHA1And40BitRC2-CBC",
	NID_pbe_WithSHA1And40BitRC2_CBC,10,&(lvalues[773]),0},
{"keyBag","keyBag",NID_keyBag,11,&(lvalues[783]),0},
{"pkcs8ShroudedKeyBag","pkcs8ShroudedKeyBag",NID_pkcs8ShroudedKeyBag,
	11,&(lvalues[794]),0},
{"certBag","certBag",NID_certBag,11,&(lvalues[805]),0},
{"crlBag","crlBag",NID_crlBag,11,&(lvalues[816]),0},
{"secretBag","secretBag",NID_secretBag,11,&(lvalues[827]),0},
{"safeContentsBag","safeContentsBag",NID_safeContentsBag,11,
	&(lvalues[838]),0},
{"friendlyName","friendlyName",NID_friendlyName,9,&(lvalues[849]),0},
{"localKeyID","localKeyID",NID_localKeyID,9,&(lvalues[858]),0},
{"x509Certificate","x509Certificate",NID_x509Certificate,10,
	&(lvalues[867]),0},
{"sdsiCertificate","sdsiCertificate",NID_sdsiCertificate,10,
	&(lvalues[877]),0},
{"x509Crl","x509Crl",NID_x509Crl,10,&(lvalues[887]),0},
{"PBES2","PBES2",NID_pbes2,9,&(lvalues[897]),0},
{"PBMAC1","PBMAC1",NID_pbmac1,9,&(lvalues[906]),0},
{"hmacWithSHA1","hmacWithSHA1",NID_hmacWithSHA1,8,&(lvalues[915]),0},
{"id-qt-cps","Policy Qualifier CPS",NID_id_qt_cps,8,&(lvalues[923]),0},
{"id-qt-unotice","Policy Qualifier User Notice",NID_id_qt_unotice,8,
	&(lvalues[931]),0},
{"RC2-64-CBC","rc2-64-cbc",NID_rc2_64_cbc,0,NULL,0},
{"SMIME-CAPS","S/MIME Capabilities",NID_SMIMECapabilities,9,
	&(lvalues[939]),0},
{NULL,NULL,NID_undef,0,NULL,0},
{"PBE-MD5-RC2-64","pbeWithMD5AndRC2-CBC",NID_pbeWithMD5AndRC2_CBC,9,
	&(lvalues[948]),0},
{"PBE-SHA1-DES","pbeWithSHA1AndDES-CBC",NID_pbeWithSHA1AndDES_CBC,9,
	&(lvalues[957]),0},
{"msExtReq","Microsoft Extension Request",NID_ms_ext_req,10,
	&(lvalues[966]),0},
{"extReq","Extension Request",NID_ext_req,9,&(lvalues[976]),0},
{"name","name",NID_name,3,&(lvalues[985]),0},
{"dnQualifier","dnQualifier",NID_dnQualifier,3,&(lvalues[988]),0},
{"id-pe","id-pe",NID_id_pe,7,&(lvalues[991]),0},
{"id-ad","id-ad",NID_id_ad,7,&(lvalues[998]),0},
{"authorityInfoAccess","Authority Information Access",NID_info_access,
	8,&(lvalues[1005]),0},
{"OCSP","OCSP",NID_ad_OCSP,8,&(lvalues[1013]),0},
{"caIssuers","CA Issuers",NID_ad_ca_issuers,8,&(lvalues[1021]),0},
{"OCSPSigning","OCSP Signing",NID_OCSP_sign,8,&(lvalues[1029]),0},
{"ISO","iso",NID_iso,0,NULL,0},
{"member-body","ISO Member Body",NID_member_body,1,&(lvalues[1037]),0},
{"ISO-US","ISO US Member Body",NID_ISO_US,3,&(lvalues[1038]),0},
{"X9-57","X9.57",NID_X9_57,5,&(lvalues[1041]),0},
{"X9cm","X9.57 CM ?",NID_X9cm,6,&(lvalues[1046]),0},
{"pkcs1","pkcs1",NID_pkcs1,8,&(lvalues[1052]),0},
{"pkcs5","pkcs5",NID_pkcs5,8,&(lvalues[1060]),0},
{"SMIME","S/MIME",NID_SMIME,9,&(lvalues[1068]),0},
{"id-smime-mod","id-smime-mod",NID_id_smime_mod,10,&(lvalues[1077]),0},
{"id-smime-ct","id-smime-ct",NID_id_smime_ct,10,&(lvalues[1087]),0},
{"id-smime-aa","id-smime-aa",NID_id_smime_aa,10,&(lvalues[1097]),0},
{"id-smime-alg","id-smime-alg",NID_id_smime_alg,10,&(lvalues[1107]),0},
{"id-smime-cd","id-smime-cd",NID_id_smime_cd,10,&(lvalues[1117]),0},
{"id-smime-spq","id-smime-spq",NID_id_smime_spq,10,&(lvalues[1127]),0},
{"id-smime-cti","id-smime-cti",NID_id_smime_cti,10,&(lvalues[1137]),0},
{"id-smime-mod-cms","id-smime-mod-cms",NID_id_smime_mod_cms,11,
	&(lvalues[1147]),0},
{"id-smime-mod-ess","id-smime-mod-ess",NID_id_smime_mod_ess,11,
	&(lvalues[1158]),0},
{"id-smime-mod-oid","id-smime-mod-oid",NID_id_smime_mod_oid,11,
	&(lvalues[1169]),0},
{"id-smime-mod-msg-v3","id-smime-mod-msg-v3",NID_id_smime_mod_msg_v3,
	11,&(lvalues[1180]),0},
{"id-smime-mod-ets-eSignature-88","id-smime-mod-ets-eSignature-88",
	NID_id_smime_mod_ets_eSignature_88,11,&(lvalues[1191]),0},
{"id-smime-mod-ets-eSignature-97","id-smime-mod-ets-eSignature-97",
	NID_id_smime_mod_ets_eSignature_97,11,&(lvalues[1202]),0},
{"id-smime-mod-ets-eSigPolicy-88","id-smime-mod-ets-eSigPolicy-88",
	NID_id_smime_mod_ets_eSigPolicy_88,11,&(lvalues[1213]),0},
{"id-smime-mod-ets-eSigPolicy-97","id-smime-mod-ets-eSigPolicy-97",
	NID_id_smime_mod_ets_eSigPolicy_97,11,&(lvalues[1224]),0},
{"id-smime-ct-receipt","id-smime-ct-receipt",NID_id_smime_ct_receipt,
	11,&(lvalues[1235]),0},
{"id-smime-ct-authData","id-smime-ct-authData",
	NID_id_smime_ct_authData,11,&(lvalues[1246]),0},
{"id-smime-ct-publishCert","id-smime-ct-publishCert",
	NID_id_smime_ct_publishCert,11,&(lvalues[1257]),0},
{"id-smime-ct-TSTInfo","id-smime-ct-TSTInfo",NID_id_smime_ct_TSTInfo,
	11,&(lvalues[1268]),0},
{"id-smime-ct-TDTInfo","id-smime-ct-TDTInfo",NID_id_smime_ct_TDTInfo,
	11,&(lvalues[1279]),0},
{"id-smime-ct-contentInfo","id-smime-ct-contentInfo",
	NID_id_smime_ct_contentInfo,11,&(lvalues[1290]),0},
{"id-smime-ct-DVCSRequestData","id-smime-ct-DVCSRequestData",
	NID_id_smime_ct_DVCSRequestData,11,&(lvalues[1301]),0},
{"id-smime-ct-DVCSResponseData","id-smime-ct-DVCSResponseData",
	NID_id_smime_ct_DVCSResponseData,11,&(lvalues[1312]),0},
{"id-smime-aa-receiptRequest","id-smime-aa-receiptRequest",
	NID_id_smime_aa_receiptRequest,11,&(lvalues[1323]),0},
{"id-smime-aa-securityLabel","id-smime-aa-securityLabel",
	NID_id_smime_aa_securityLabel,11,&(lvalues[1334]),0},
{"id-smime-aa-mlExpandHistory","id-smime-aa-mlExpandHistory",
	NID_id_smime_aa_mlExpandHistory,11,&(lvalues[1345]),0},
{"id-smime-aa-contentHint","id-smime-aa-contentHint",
	NID_id_smime_aa_contentHint,11,&(lvalues[1356]),0},
{"id-smime-aa-msgSigDigest","id-smime-aa-msgSigDigest",
	NID_id_smime_aa_msgSigDigest,11,&(lvalues[1367]),0},
{"id-smime-aa-encapContentType","id-smime-aa-encapContentType",
	NID_id_smime_aa_encapContentType,11,&(lvalues[1378]),0},
{"id-smime-aa-contentIdentifier","id-smime-aa-contentIdentifier",
	NID_id_smime_aa_contentIdentifier,11,&(lvalues[1389]),0},
{"id-smime-aa-macValue","id-smime-aa-macValue",
	NID_id_smime_aa_macValue,11,&(lvalues[1400]),0},
{"id-smime-aa-equivalentLabels","id-smime-aa-equivalentLabels",
	NID_id_smime_aa_equivalentLabels,11,&(lvalues[1411]),0},
{"id-smime-aa-contentReference","id-smime-aa-contentReference",
	NID_id_smime_aa_contentReference,11,&(lvalues[1422]),0},
{"id-smime-aa-encrypKeyPref","id-smime-aa-encrypKeyPref",
	NID_id_smime_aa_encrypKeyPref,11,&(lvalues[1433]),0},
{"id-smime-aa-signingCertificate","id-smime-aa-signingCertificate",
	NID_id_smime_aa_signingCertificate,11,&(lvalues[1444]),0},
{"id-smime-aa-smimeEncryptCerts","id-smime-aa-smimeEncryptCerts",
	NID_id_smime_aa_smimeEncryptCerts,11,&(lvalues[1455]),0},
{"id-smime-aa-timeStampToken","id-smime-aa-timeStampToken",
	NID_id_smime_aa_timeStampToken,11,&(lvalues[1466]),0},
{"id-smime-aa-ets-sigPolicyId","id-smime-aa-ets-sigPolicyId",
	NID_id_smime_aa_ets_sigPolicyId,11,&(lvalues[1477]),0},
{"id-smime-aa-ets-commitmentType","id-smime-aa-ets-commitmentType",
	NID_id_smime_aa_ets_commitmentType,11,&(lvalues[1488]),0},
{"id-smime-aa-ets-signerLocation","id-smime-aa-ets-signerLocation",
	NID_id_smime_aa_ets_signerLocation,11,&(lvalues[1499]),0},
{"id-smime-aa-ets-signerAttr","id-smime-aa-ets-signerAttr",
	NID_id_smime_aa_ets_signerAttr,11,&(lvalues[1510]),0},
{"id-smime-aa-ets-otherSigCert","id-smime-aa-ets-otherSigCert",
	NID_id_smime_aa_ets_otherSigCert,11,&(lvalues[1521]),0},
{"id-smime-aa-ets-contentTimestamp",
	"id-smime-aa-ets-contentTimestamp",
	NID_id_smime_aa_ets_contentTimestamp,11,&(lvalues[1532]),0},
{"id-smime-aa-ets-CertificateRefs","id-smime-aa-ets-CertificateRefs",
	NID_id_smime_aa_ets_CertificateRefs,11,&(lvalues[1543]),0},
{"id-smime-aa-ets-RevocationRefs","id-smime-aa-ets-RevocationRefs",
	NID_id_smime_aa_ets_RevocationRefs,11,&(lvalues[1554]),0},
{"id-smime-aa-ets-certValues","id-smime-aa-ets-certValues",
	NID_id_smime_aa_ets_certValues,11,&(lvalues[1565]),0},
{"id-smime-aa-ets-revocationValues",
	"id-smime-aa-ets-revocationValues",
	NID_id_smime_aa_ets_revocationValues,11,&(lvalues[1576]),0},
{"id-smime-aa-ets-escTimeStamp","id-smime-aa-ets-escTimeStamp",
	NID_id_smime_aa_ets_escTimeStamp,11,&(lvalues[1587]),0},
{"id-smime-aa-ets-certCRLTimestamp",
	"id-smime-aa-ets-certCRLTimestamp",
	NID_id_smime_aa_ets_certCRLTimestamp,11,&(lvalues[1598]),0},
{"id-smime-aa-ets-archiveTimeStamp",
	"id-smime-aa-ets-archiveTimeStamp",
	NID_id_smime_aa_ets_archiveTimeStamp,11,&(lvalues[1609]),0},
{"id-smime-aa-signatureType","id-smime-aa-signatureType",
	NID_id_smime_aa_signatureType,11,&(lvalues[1620]),0},
{"id-smime-aa-dvcs-dvc","id-smime-aa-dvcs-dvc",
	NID_id_smime_aa_dvcs_dvc,11,&(lvalues[1631]),0},
{"id-smime-alg-ESDHwith3DES","id-smime-alg-ESDHwith3DES",
	NID_id_smime_alg_ESDHwith3DES,11,&(lvalues[1642]),0},
{"id-smime-alg-ESDHwithRC2","id-smime-alg-ESDHwithRC2",
	NID_id_smime_alg_ESDHwithRC2,11,&(lvalues[1653]),0},
{"id-smime-alg-3DESwrap","id-smime-alg-3DESwrap",
	NID_id_smime_alg_3DESwrap,11,&(lvalues[1664]),0},
{"id-smime-alg-RC2wrap","id-smime-alg-RC2wrap",
	NID_id_smime_alg_RC2wrap,11,&(lvalues[1675]),0},
{"id-smime-alg-ESDH","id-smime-alg-ESDH",NID_id_smime_alg_ESDH,11,
	&(lvalues[1686]),0},
{"id-smime-alg-CMS3DESwrap","id-smime-alg-CMS3DESwrap",
	NID_id_smime_alg_CMS3DESwrap,11,&(lvalues[1697]),0},
{"id-smime-alg-CMSRC2wrap","id-smime-alg-CMSRC2wrap",
	NID_id_smime_alg_CMSRC2wrap,11,&(lvalues[1708]),0},
{"id-smime-cd-ldap","id-smime-cd-ldap",NID_id_smime_cd_ldap,11,
	&(lvalues[1719]),0},
{"id-smime-spq-ets-sqt-uri","id-smime-spq-ets-sqt-uri",
	NID_id_smime_spq_ets_sqt_uri,11,&(lvalues[1730]),0},
{"id-smime-spq-ets-sqt-unotice","id-smime-spq-ets-sqt-unotice",
	NID_id_smime_spq_ets_sqt_unotice,11,&(lvalues[1741]),0},
{"id-smime-cti-ets-proofOfOrigin","id-smime-cti-ets-proofOfOrigin",
	NID_id_smime_cti_ets_proofOfOrigin,11,&(lvalues[1752]),0},
{"id-smime-cti-ets-proofOfReceipt","id-smime-cti-ets-proofOfReceipt",
	NID_id_smime_cti_ets_proofOfReceipt,11,&(lvalues[1763]),0},
{"id-smime-cti-ets-proofOfDelivery",
	"id-smime-cti-ets-proofOfDelivery",
	NID_id_smime_cti_ets_proofOfDelivery,11,&(lvalues[1774]),0},
{"id-smime-cti-ets-proofOfSender","id-smime-cti-ets-proofOfSender",
	NID_id_smime_cti_ets_proofOfSender,11,&(lvalues[1785]),0},
{"id-smime-cti-ets-proofOfApproval",
	"id-smime-cti-ets-proofOfApproval",
	NID_id_smime_cti_ets_proofOfApproval,11,&(lvalues[1796]),0},
{"id-smime-cti-ets-proofOfCreation",
	"id-smime-cti-ets-proofOfCreation",
	NID_id_smime_cti_ets_proofOfCreation,11,&(lvalues[1807]),0},
{NULL,NULL,NID_undef,0,NULL,0},
{"id-pkix-mod","id-pkix-mod",NID_id_pkix_mod,7,&(lvalues[1818]),0},
{"id-qt","id-qt",NID_id_qt,7,&(lvalues[1825]),0},
{"id-it","id-it",NID_id_it,7,&(lvalues[1832]),0},
{"id-pkip","id-pkip",NID_id_pkip,7,&(lvalues[1839]),0},
{"id-alg","id-alg",NID_id_alg,7,&(lvalues[1846]),0},
{"id-cmc","id-cmc",NID_id_cmc,7,&(lvalues[1853]),0},
{"id-on","id-on",NID_id_on,7,&(lvalues[1860]),0},
{"id-pda","id-pda",NID_id_pda,7,&(lvalues[1867]),0},
{"id-aca","id-aca",NID_id_aca,7,&(lvalues[1874]),0},
{"id-qcs","id-qcs",NID_id_qcs,7,&(lvalues[1881]),0},
{"id-cct","id-cct",NID_id_cct,7,&(lvalues[1888]),0},
{"id-pkix1-explicit-88","id-pkix1-explicit-88",
	NID_id_pkix1_explicit_88,8,&(lvalues[1895]),0},
{"id-pkix1-implicit-88","id-pkix1-implicit-88",
	NID_id_pkix1_implicit_88,8,&(lvalues[1903]),0},
{"id-pkix1-explicit-93","id-pkix1-explicit-93",
	NID_id_pkix1_explicit_93,8,&(lvalues[1911]),0},
{"id-pkix1-implicit-93","id-pkix1-implicit-93",
	NID_id_pkix1_implicit_93,8,&(lvalues[1919]),0},
{"id-mod-crmf","id-mod-crmf",NID_id_mod_crmf,8,&(lvalues[1927]),0},
{"id-mod-cmc","id-mod-cmc",NID_id_mod_cmc,8,&(lvalues[1935]),0},
{"id-mod-kea-profile-88","id-mod-kea-profile-88",
	NID_id_mod_kea_profile_88,8,&(lvalues[1943]),0},
{"id-mod-kea-profile-93","id-mod-kea-profile-93",
	NID_id_mod_kea_profile_93,8,&(lvalues[1951]),0},
{"id-mod-cmp","id-mod-cmp",NID_id_mod_cmp,8,&(lvalues[1959]),0},
{"id-mod-qualified-cert-88","id-mod-qualified-cert-88",
	NID_id_mod_qualified_cert_88,8,&(lvalues[1967]),0},
{"id-mod-qualified-cert-93","id-mod-qualified-cert-93",
	NID_id_mod_qualified_cert_93,8,&(lvalues[1975]),0},
{"id-mod-attribute-cert","id-mod-attribute-cert",
	NID_id_mod_attribute_cert,8,&(lvalues[1983]),0},
{"id-mod-timestamp-protocol","id-mod-timestamp-protocol",
	NID_id_mod_timestamp_protocol,8,&(lvalues[1991]),0},
{"id-mod-ocsp","id-mod-ocsp",NID_id_mod_ocsp,8,&(lvalues[1999]),0},
{"id-mod-dvcs","id-mod-dvcs",NID_id_mod_dvcs,8,&(lvalues[2007]),0},
{"id-mod-cmp2000","id-mod-cmp2000",NID_id_mod_cmp2000,8,
	&(lvalues[2015]),0},
{"biometricInfo","Biometric Info",NID_biometricInfo,8,&(lvalues[2023]),0},
{"qcStatements","qcStatements",NID_qcStatements,8,&(lvalues[2031]),0},
{"ac-auditEntity","ac-auditEntity",NID_ac_auditEntity,8,
	&(lvalues[2039]),0},
{"ac-targeting","ac-targeting",NID_ac_targeting,8,&(lvalues[2047]),0},
{"aaControls","aaControls",NID_aaControls,8,&(lvalues[2055]),0},
{"sbgp-ipAddrBlock","sbgp-ipAddrBlock",NID_sbgp_ipAddrBlock,8,
	&(lvalues[2063]),0},
{"sbgp-autonomousSysNum","sbgp-autonomousSysNum",
	NID_sbgp_autonomousSysNum,8,&(lvalues[2071]),0},
{"sbgp-routerIdentifier","sbgp-routerIdentifier",
	NID_sbgp_routerIdentifier,8,&(lvalues[2079]),0},
{"textNotice","textNotice",NID_textNotice,8,&(lvalues[2087]),0},
{"ipsecEndSystem","IPSec End System",NID_ipsecEndSystem,8,
	&(lvalues[2095]),0},
{"ipsecTunnel","IPSec Tunnel",NID_ipsecTunnel,8,&(lvalues[2103]),0},
{"ipsecUser","IPSec User",NID_ipsecUser,8,&(lvalues[2111]),0},
{"DVCS","dvcs",NID_dvcs,8,&(lvalues[2119]),0},
{"id-it-caProtEncCert","id-it-caProtEncCert",NID_id_it_caProtEncCert,
	8,&(lvalues[2127]),0},
{"id-it-signKeyPairTypes","id-it-signKeyPairTypes",
	NID_id_it_signKeyPairTypes,8,&(lvalues[2135]),0},
{"id-it-encKeyPairTypes","id-it-encKeyPairTypes",
	NID_id_it_encKeyPairTypes,8,&(lvalues[2143]),0},
{"id-it-preferredSymmAlg","id-it-preferredSymmAlg",
	NID_id_it_preferredSymmAlg,8,&(lvalues[2151]),0},
{"id-it-caKeyUpdateInfo","id-it-caKeyUpdateInfo",
	NID_id_it_caKeyUpdateInfo,8,&(lvalues[2159]),0},
{"id-it-currentCRL","id-it-currentCRL",NID_id_it_currentCRL,8,
	&(lvalues[2167]),0},
{"id-it-unsupportedOIDs","id-it-unsupportedOIDs",
	NID_id_it_unsupportedOIDs,8,&(lvalues[2175]),0},
{"id-it-subscriptionRequest","id-it-subscriptionRequest",
	NID_id_it_subscriptionRequest,8,&(lvalues[2183]),0},
{"id-it-subscriptionResponse","id-it-subscriptionResponse",
	NID_id_it_subscriptionResponse,8,&(lvalues[2191]),0},
{"id-it-keyPairParamReq","id-it-keyPairParamReq",
	NID_id_it_keyPairParamReq,8,&(lvalues[2199]),0},
{"id-it-keyPairParamRep","id-it-keyPairParamRep",
	NID_id_it_keyPairParamRep,8,&(lvalues[2207]),0},
{"id-it-revPassphrase","id-it-revPassphrase",NID_id_it_revPassphrase,
	8,&(lvalues[2215]),0},
{"id-it-implicitConfirm","id-it-implicitConfirm",
	NID_id_it_implicitConfirm,8,&(lvalues[2223]),0},
{"id-it-confirmWaitTime","id-it-confirmWaitTime",
	NID_id_it_confirmWaitTime,8,&(lvalues[2231]),0},
{"id-it-origPKIMessage","id-it-origPKIMessage",
	NID_id_it_origPKIMessage,8,&(lvalues[2239]),0},
{"id-regCtrl","id-regCtrl",NID_id_regCtrl,8,&(lvalues[2247]),0},
{"id-regInfo","id-regInfo",NID_id_regInfo,8,&(lvalues[2255]),0},
{"id-regCtrl-regToken","id-regCtrl-regToken",NID_id_regCtrl_regToken,
	9,&(lvalues[2263]),0},
{"id-regCtrl-authenticator","id-regCtrl-authenticator",
	NID_id_regCtrl_authenticator,9,&(lvalues[2272]),0},
{"id-regCtrl-pkiPublicationInfo","id-regCtrl-pkiPublicationInfo",
	NID_id_regCtrl_pkiPublicationInfo,9,&(lvalues[2281]),0},
{"id-regCtrl-pkiArchiveOptions","id-regCtrl-pkiArchiveOptions",
	NID_id_regCtrl_pkiArchiveOptions,9,&(lvalues[2290]),0},
{"id-regCtrl-oldCertID","id-regCtrl-oldCertID",
	NID_id_regCtrl_oldCertID,9,&(lvalues[2299]),0},
{"id-regCtrl-protocolEncrKey","id-regCtrl-protocolEncrKey",
	NID_id_regCtrl_protocolEncrKey,9,&(lvalues[2308]),0},
{"id-regInfo-utf8Pairs","id-regInfo-utf8Pairs",
	NID_id_regInfo_utf8Pairs,9,&(lvalues[2317]),0},
{"id-regInfo-certReq","id-regInfo-certReq",NID_id_regInfo_certReq,9,
	&(lvalues[2326]),0},
{"id-alg-des40","id-alg-des40",NID_id_alg_des40,8,&(lvalues[2335]),0},
{"id-alg-noSignature","id-alg-noSignature",NID_id_alg_noSignature,8,
	&(lvalues[2343]),0},
{"id-alg-dh-sig-hmac-sha1","id-alg-dh-sig-hmac-sha1",
	NID_id_alg_dh_sig_hmac_sha1,8,&(lvalues[2351]),0},
{"id-alg-dh-pop","id-alg-dh-pop",NID_id_alg_dh_pop,8,&(lvalues[2359]),0},
{"id-cmc-statusInfo","id-cmc-statusInfo",NID_id_cmc_statusInfo,8,
	&(lvalues[2367]),0},
{"id-cmc-identification","id-cmc-identification",
	NID_id_cmc_identification,8,&(lvalues[2375]),0},
{"id-cmc-identityProof","id-cmc-identityProof",
	NID_id_cmc_identityProof,8,&(lvalues[2383]),0},
{"id-cmc-dataReturn","id-cmc-dataReturn",NID_id_cmc_dataReturn,8,
	&(lvalues[2391]),0},
{"id-cmc-transactionId","id-cmc-transactionId",
	NID_id_cmc_transactionId,8,&(lvalues[2399]),0},
{"id-cmc-senderNonce","id-cmc-senderNonce",NID_id_cmc_senderNonce,8,
	&(lvalues[2407]),0},
{"id-cmc-recipientNonce","id-cmc-recipientNonce",
	NID_id_cmc_recipientNonce,8,&(lvalues[2415]),0},
{"id-cmc-addExtensions","id-cmc-addExtensions",
	NID_id_cmc_addExtensions,8,&(lvalues[2423]),0},
{"id-cmc-encryptedPOP","id-cmc-encryptedPOP",NID_id_cmc_encryptedPOP,
	8,&(lvalues[2431]),0},
{"id-cmc-decryptedPOP","id-cmc-decryptedPOP",NID_id_cmc_decryptedPOP,
	8,&(lvalues[2439]),0},
{"id-cmc-lraPOPWitness","id-cmc-lraPOPWitness",
	NID_id_cmc_lraPOPWitness,8,&(lvalues[2447]),0},
{"id-cmc-getCert","id-cmc-getCert",NID_id_cmc_getCert,8,
	&(lvalues[2455]),0},
{"id-cmc-getCRL","id-cmc-getCRL",NID_id_cmc_getCRL,8,&(lvalues[2463]),0},
{"id-cmc-revokeRequest","id-cmc-revokeRequest",
	NID_id_cmc_revokeRequest,8,&(lvalues[2471]),0},
{"id-cmc-regInfo","id-cmc-regInfo",NID_id_cmc_regInfo,8,
	&(lvalues[2479]),0},
{"id-cmc-responseInfo","id-cmc-responseInfo",NID_id_cmc_responseInfo,
	8,&(lvalues[2487]),0},
{"id-cmc-queryPending","id-cmc-queryPending",NID_id_cmc_queryPending,
	8,&(lvalues[2495]),0},
{"id-cmc-popLinkRandom","id-cmc-popLinkRandom",
	NID_id_cmc_popLinkRandom,8,&(lvalues[2503]),0},
{"id-cmc-popLinkWitness","id-cmc-popLinkWitness",
	NID_id_cmc_popLinkWitness,8,&(lvalues[2511]),0},
{"id-cmc-confirmCertAcceptance","id-cmc-confirmCertAcceptance",
	NID_id_cmc_confirmCertAcceptance,8,&(lvalues[2519]),0},
{"id-on-personalData","id-on-personalData",NID_id_on_personalData,8,
	&(lvalues[2527]),0},
{"id-pda-dateOfBirth","id-pda-dateOfBirth",NID_id_pda_dateOfBirth,8,
	&(lvalues[2535]),0},
{"id-pda-placeOfBirth","id-pda-placeOfBirth",NID_id_pda_placeOfBirth,
	8,&(lvalues[2543]),0},
{NULL,NULL,NID_undef,0,NULL,0},
{"id-pda-gender","id-pda-gender",NID_id_pda_gender,8,&(lvalues[2551]),0},
{"id-pda-countryOfCitizenship","id-pda-countryOfCitizenship",
	NID_id_pda_countryOfCitizenship,8,&(lvalues[2559]),0},
{"id-pda-countryOfResidence","id-pda-countryOfResidence",
	NID_id_pda_countryOfResidence,8,&(lvalues[2567]),0},
{"id-aca-authenticationInfo","id-aca-authenticationInfo",
	NID_id_aca_authenticationInfo,8,&(lvalues[2575]),0},
{"id-aca-accessIdentity","id-aca-accessIdentity",
	NID_id_aca_accessIdentity,8,&(lvalues[2583]),0},
{"id-aca-chargingIdentity","id-aca-chargingIdentity",
	NID_id_aca_chargingIdentity,8,&(lvalues[2591]),0},
{"id-aca-group","id-aca-group",NID_id_aca_group,8,&(lvalues[2599]),0},
{"id-aca-role","id-aca-role",NID_id_aca_role,8,&(lvalues[2607]),0},
{"id-qcs-pkixQCSyntax-v1","id-qcs-pkixQCSyntax-v1",
	NID_id_qcs_pkixQCSyntax_v1,8,&(lvalues[2615]),0},
{"id-cct-crs","id-cct-crs",NID_id_cct_crs,8,&(lvalues[2623]),0},
{"id-cct-PKIData","id-cct-PKIData",NID_id_cct_PKIData,8,
	&(lvalues[2631]),0},
{"id-cct-PKIResponse","id-cct-PKIResponse",NID_id_cct_PKIResponse,8,
	&(lvalues[2639]),0},
{"ad_timestamping","AD Time Stamping",NID_ad_timeStamping,8,
	&(lvalues[2647]),0},
{"AD_DVCS","ad dvcs",NID_ad_dvcs,8,&(lvalues[2655]),0},
{"basicOCSPResponse","Basic OCSP Response",NID_id_pkix_OCSP_basic,9,
	&(lvalues[2663]),0},
{"Nonce","OCSP Nonce",NID_id_pkix_OCSP_Nonce,9,&(lvalues[2672]),0},
{"CrlID","OCSP CRL ID",NID_id_pkix_OCSP_CrlID,9,&(lvalues[2681]),0},
{"acceptableResponses","Acceptable OCSP Responses",
	NID_id_pkix_OCSP_acceptableResponses,9,&(lvalues[2690]),0},
{"noCheck","OCSP No Check",NID_id_pkix_OCSP_noCheck,9,&(lvalues[2699]),0},
{"archiveCutoff","OCSP Archive Cutoff",NID_id_pkix_OCSP_archiveCutoff,
	9,&(lvalues[2708]),0},
{"serviceLocator","OCSP Service Locator",
	NID_id_pkix_OCSP_serviceLocator,9,&(lvalues[2717]),0},
{"extendedStatus","Extended OCSP Status",
	NID_id_pkix_OCSP_extendedStatus,9,&(lvalues[2726]),0},
{"valid","valid",NID_id_pkix_OCSP_valid,9,&(lvalues[2735]),0},
{"path","path",NID_id_pkix_OCSP_path,9,&(lvalues[2744]),0},
{"trustRoot","Trust Root",NID_id_pkix_OCSP_trustRoot,9,
	&(lvalues[2753]),0},
{"algorithm","algorithm",NID_algorithm,4,&(lvalues[2762]),0},
{"rsaSignature","rsaSignature",NID_rsaSignature,5,&(lvalues[2766]),0},
{"X500algorithms","directory services - algorithms",
	NID_X500algorithms,2,&(lvalues[2771]),0},
{"ORG","org",NID_org,1,&(lvalues[2773]),0},
{"DOD","dod",NID_dod,2,&(lvalues[2774]),0},
{"IANA","iana",NID_iana,3,&(lvalues[2776]),0},
{"directory","Directory",NID_Directory,4,&(lvalues[2779]),0},
{"mgmt","Management",NID_Management,4,&(lvalues[2783]),0},
{"experimental","Experimental",NID_Experimental,4,&(lvalues[2787]),0},
{"private","Private",NID_Private,4,&(lvalues[2791]),0},
{"security","Security",NID_Security,4,&(lvalues[2795]),0},
{"snmpv2","SNMPv2",NID_SNMPv2,4,&(lvalues[2799]),0},
{"Mail","Mail",NID_Mail,4,&(lvalues[2803]),0},
{"enterprises","Enterprises",NID_Enterprises,5,&(lvalues[2807]),0},
{"dcobject","dcObject",NID_dcObject,9,&(lvalues[2812]),0},
{"DC","domainComponent",NID_domainComponent,10,&(lvalues[2821]),0},
{"domain","Domain",NID_Domain,10,&(lvalues[2831]),0},
{"NULL","NULL",NID_joint_iso_ccitt,0,NULL,0},
{"selected-attribute-types","Selected Attribute Types",
	NID_selected_attribute_types,3,&(lvalues[2841]),0},
{"clearance","clearance",NID_clearance,4,&(lvalues[2844]),0},
{NULL,NULL,NID_undef,0,NULL,0},
{"ac-proxying","ac-proxying",NID_ac_proxying,8,&(lvalues[2848]),0},
{"subjectInfoAccess","Subject Information Access",NID_sinfo_access,8,
	&(lvalues[2856]),0},
{"id-aca-encAttrs","id-aca-encAttrs",NID_id_aca_encAttrs,8,
	&(lvalues[2864]),0},
{"role","role",NID_role,3,&(lvalues[2872]),0},
{"policyConstraints","X509v3 Policy Constraints",
	NID_policy_constraints,3,&(lvalues[2875]),0},
{"targetInformation","X509v3 AC Targeting",NID_target_information,3,
	&(lvalues[2878]),0},
{"noRevAvail","X509v3 No Revocation Available",NID_no_rev_avail,3,
	&(lvalues[2881]),0},
{"NULL","NULL",NID_ccitt,0,NULL,0},
{"ansi-X9-62","ANSI X9.62",NID_ansi_X9_62,5,&(lvalues[2884]),0},
{"prime-field","prime-field",NID_X9_62_prime_field,7,&(lvalues[2889]),0},
{"characteristic-two-field","characteristic-two-field",
	NID_X9_62_characteristic_two_field,7,&(lvalues[2896]),0},
{"id-ecPublicKey","id-ecPublicKey",NID_X9_62_id_ecPublicKey,7,
	&(lvalues[2903]),0},
{"prime192v1","prime192v1",NID_X9_62_prime192v1,8,&(lvalues[2910]),0},
{"prime192v2","prime192v2",NID_X9_62_prime192v2,8,&(lvalues[2918]),0},
{"prime192v3","prime192v3",NID_X9_62_prime192v3,8,&(lvalues[2926]),0},
{"prime239v1","prime239v1",NID_X9_62_prime239v1,8,&(lvalues[2934]),0},
{"prime239v2","prime239v2",NID_X9_62_prime239v2,8,&(lvalues[2942]),0},
{"prime239v3","prime239v3",NID_X9_62_prime239v3,8,&(lvalues[2950]),0},
{"prime256v1","prime256v1",NID_X9_62_prime256v1,8,&(lvalues[2958]),0},
{"ecdsa-with-SHA1","ecdsa-with-SHA1",NID_ecdsa_with_SHA1,7,
	&(lvalues[2966]),0},
{"CSPName","Microsoft CSP Name",NID_ms_csp_name,9,&(lvalues[2973]),0},
{"AES-128-ECB","aes-128-ecb",NID_aes_128_ecb,9,&(lvalues[2982]),0},
{"AES-128-CBC","aes-128-cbc",NID_aes_128_cbc,9,&(lvalues[2991]),0},
{"AES-128-OFB","aes-128-ofb",NID_aes_128_ofb128,9,&(lvalues[3000]),0},
{"AES-128-CFB","aes-128-cfb",NID_aes_128_cfb128,9,&(lvalues[3009]),0},
{"AES-192-ECB","aes-192-ecb",NID_aes_192_ecb,9,&(lvalues[3018]),0},
{"AES-192-CBC","aes-192-cbc",NID_aes_192_cbc,9,&(lvalues[3027]),0},
{"AES-192-OFB","aes-192-ofb",NID_aes_192_ofb128,9,&(lvalues[3036]),0},
{"AES-192-CFB","aes-192-cfb",NID_aes_192_cfb128,9,&(lvalues[3045]),0},
{"AES-256-ECB","aes-256-ecb",NID_aes_256_ecb,9,&(lvalues[3054]),0},
{"AES-256-CBC","aes-256-cbc",NID_aes_256_cbc,9,&(lvalues[3063]),0},
{"AES-256-OFB","aes-256-ofb",NID_aes_256_ofb128,9,&(lvalues[3072]),0},
{"AES-256-CFB","aes-256-cfb",NID_aes_256_cfb128,9,&(lvalues[3081]),0},
{"holdInstructionCode","Hold Instruction Code",
	NID_hold_instruction_code,3,&(lvalues[3090]),0},
{"holdInstructionNone","Hold Instruction None",
	NID_hold_instruction_none,7,&(lvalues[3093]),0},
{"holdInstructionCallIssuer","Hold Instruction Call Issuer",
	NID_hold_instruction_call_issuer,7,&(lvalues[3100]),0},
{"holdInstructionReject","Hold Instruction Reject",
	NID_hold_instruction_reject,7,&(lvalues[3107]),0},
{"data","data",NID_data,1,&(lvalues[3114]),0},
{"pss","pss",NID_pss,3,&(lvalues[3115]),0},
{"ucl","ucl",NID_ucl,7,&(lvalues[3118]),0},
{"pilot","pilot",NID_pilot,8,&(lvalues[3125]),0},
{"pilotAttributeType","pilotAttributeType",NID_pilotAttributeType,9,
	&(lvalues[3133]),0},
{"pilotAttributeSyntax","pilotAttributeSyntax",
	NID_pilotAttributeSyntax,9,&(lvalues[3142]),0},
{"pilotObjectClass","pilotObjectClass",NID_pilotObjectClass,9,
	&(lvalues[3151]),0},
{"pilotGroups","pilotGroups",NID_pilotGroups,9,&(lvalues[3160]),0},
{"iA5StringSyntax","iA5StringSyntax",NID_iA5StringSyntax,10,
	&(lvalues[3169]),0},
{"caseIgnoreIA5StringSyntax","caseIgnoreIA5StringSyntax",
	NID_caseIgnoreIA5StringSyntax,10,&(lvalues[3179]),0},
{"pilotObject","pilotObject",NID_pilotObject,10,&(lvalues[3189]),0},
{"pilotPerson","pilotPerson",NID_pilotPerson,10,&(lvalues[3199]),0},
{"account","account",NID_account,10,&(lvalues[3209]),0},
{"document","document",NID_document,10,&(lvalues[3219]),0},
{"room","room",NID_room,10,&(lvalues[3229]),0},
{"documentSeries","documentSeries",NID_documentSeries,10,
	&(lvalues[3239]),0},
{"rFC822localPart","rFC822localPart",NID_rFC822localPart,10,
	&(lvalues[3249]),0},
{"dNSDomain","dNSDomain",NID_dNSDomain,10,&(lvalues[3259]),0},
{"domainRelatedObject","domainRelatedObject",NID_domainRelatedObject,
	10,&(lvalues[3269]),0},
{"friendlyCountry","friendlyCountry",NID_friendlyCountry,10,
	&(lvalues[3279]),0},
{"simpleSecurityObject","simpleSecurityObject",
	NID_simpleSecurityObject,10,&(lvalues[3289]),0},
{"pilotOrganization","pilotOrganization",NID_pilotOrganization,10,
	&(lvalues[3299]),0},
{"pilotDSA","pilotDSA",NID_pilotDSA,10,&(lvalues[3309]),0},
{"qualityLabelledData","qualityLabelledData",NID_qualityLabelledData,
	10,&(lvalues[3319]),0},
{"UID","userId",NID_userId,10,&(lvalues[3329]),0},
{"textEncodedORAddress","textEncodedORAddress",
	NID_textEncodedORAddress,10,&(lvalues[3339]),0},
{"mail","rfc822Mailbox",NID_rfc822Mailbox,10,&(lvalues[3349]),0},
{"info","info",NID_info,10,&(lvalues[3359]),0},
{"favouriteDrink","favouriteDrink",NID_favouriteDrink,10,
	&(lvalues[3369]),0},
{"roomNumber","roomNumber",NID_roomNumber,10,&(lvalues[3379]),0},
{"photo","photo",NID_photo,10,&(lvalues[3389]),0},
{"userClass","userClass",NID_userClass,10,&(lvalues[3399]),0},
{"host","host",NID_host,10,&(lvalues[3409]),0},
{"manager","manager",NID_manager,10,&(lvalues[3419]),0},
{"documentIdentifier","documentIdentifier",NID_documentIdentifier,10,
	&(lvalues[3429]),0},
{"documentTitle","documentTitle",NID_documentTitle,10,&(lvalues[3439]),0},
{"documentVersion","documentVersion",NID_documentVersion,10,
	&(lvalues[3449]),0},
{"documentAuthor","documentAuthor",NID_documentAuthor,10,
	&(lvalues[3459]),0},
{"documentLocation","documentLocation",NID_documentLocation,10,
	&(lvalues[3469]),0},
{"homeTelephoneNumber","homeTelephoneNumber",NID_homeTelephoneNumber,
	10,&(lvalues[3479]),0},
{"secretary","secretary",NID_secretary,10,&(lvalues[3489]),0},
{"otherMailbox","otherMailbox",NID_otherMailbox,10,&(lvalues[3499]),0},
{"lastModifiedTime","lastModifiedTime",NID_lastModifiedTime,10,
	&(lvalues[3509]),0},
{"lastModifiedBy","lastModifiedBy",NID_lastModifiedBy,10,
	&(lvalues[3519]),0},
{"aRecord","aRecord",NID_aRecord,10,&(lvalues[3529]),0},
{"pilotAttributeType27","pilotAttributeType27",
	NID_pilotAttributeType27,10,&(lvalues[3539]),0},
{"mXRecord","mXRecord",NID_mXRecord,10,&(lvalues[3549]),0},
{"nSRecord","nSRecord",NID_nSRecord,10,&(lvalues[3559]),0},
{"sOARecord","sOARecord",NID_sOARecord,10,&(lvalues[3569]),0},
{"cNAMERecord","cNAMERecord",NID_cNAMERecord,10,&(lvalues[3579]),0},
{"associatedDomain","associatedDomain",NID_associatedDomain,10,
	&(lvalues[3589]),0},
{"associatedName","associatedName",NID_associatedName,10,
	&(lvalues[3599]),0},
{"homePostalAddress","homePostalAddress",NID_homePostalAddress,10,
	&(lvalues[3609]),0},
{"personalTitle","personalTitle",NID_personalTitle,10,&(lvalues[3619]),0},
{"mobileTelephoneNumber","mobileTelephoneNumber",
	NID_mobileTelephoneNumber,10,&(lvalues[3629]),0},
{"pagerTelephoneNumber","pagerTelephoneNumber",
	NID_pagerTelephoneNumber,10,&(lvalues[3639]),0},
{"friendlyCountryName","friendlyCountryName",NID_friendlyCountryName,
	10,&(lvalues[3649]),0},
{"organizationalStatus","organizationalStatus",
	NID_organizationalStatus,10,&(lvalues[3659]),0},
{"janetMailbox","janetMailbox",NID_janetMailbox,10,&(lvalues[3669]),0},
{"mailPreferenceOption","mailPreferenceOption",
	NID_mailPreferenceOption,10,&(lvalues[3679]),0},
{"buildingName","buildingName",NID_buildingName,10,&(lvalues[3689]),0},
{"dSAQuality","dSAQuality",NID_dSAQuality,10,&(lvalues[3699]),0},
{"singleLevelQuality","singleLevelQuality",NID_singleLevelQuality,10,
	&(lvalues[3709]),0},
{"subtreeMinimumQuality","subtreeMinimumQuality",
	NID_subtreeMinimumQuality,10,&(lvalues[3719]),0},
{"subtreeMaximumQuality","subtreeMaximumQuality",
	NID_subtreeMaximumQuality,10,&(lvalues[3729]),0},
{"personalSignature","personalSignature",NID_personalSignature,10,
	&(lvalues[3739]),0},
{"dITRedirect","dITRedirect",NID_dITRedirect,10,&(lvalues[3749]),0},
{"audio","audio",NID_audio,10,&(lvalues[3759]),0},
{"documentPublisher","documentPublisher",NID_documentPublisher,10,
	&(lvalues[3769]),0},
{"x500UniqueIdentifier","x500UniqueIdentifier",
	NID_x500UniqueIdentifier,3,&(lvalues[3779]),0},
{"mime-mhs","MIME MHS",NID_mime_mhs,5,&(lvalues[3782]),0},
{"mime-mhs-headings","mime-mhs-headings",NID_mime_mhs_headings,6,
	&(lvalues[3787]),0},
{"mime-mhs-bodies","mime-mhs-bodies",NID_mime_mhs_bodies,6,
	&(lvalues[3793]),0},
{"id-hex-partial-message","id-hex-partial-message",
	NID_id_hex_partial_message,7,&(lvalues[3799]),0},
{"id-hex-multipart-message","id-hex-multipart-message",
	NID_id_hex_multipart_message,7,&(lvalues[3806]),0},
{"generationQualifier","generationQualifier",NID_generationQualifier,
	3,&(lvalues[3813]),0},
{"pseudonym","pseudonym",NID_pseudonym,3,&(lvalues[3816]),0},
{NULL,NULL,NID_undef,0,NULL,0},
{"id-set","Secure Electronic Transactions",NID_id_set,2,
	&(lvalues[3819]),0},
{"set-ctype","content types",NID_set_ctype,3,&(lvalues[3821]),0},
{"set-msgExt","message extensions",NID_set_msgExt,3,&(lvalues[3824]),0},
{"set-attr","set-attr",NID_set_attr,3,&(lvalues[3827]),0},
{"set-policy","set-policy",NID_set_policy,3,&(lvalues[3830]),0},
{"set-certExt","certificate extensions",NID_set_certExt,3,
	&(lvalues[3833]),0},
{"set-brand","set-brand",NID_set_brand,3,&(lvalues[3836]),0},
{"setct-PANData","setct-PANData",NID_setct_PANData,4,&(lvalues[3839]),0},
{"setct-PANToken","setct-PANToken",NID_setct_PANToken,4,
	&(lvalues[3843]),0},
{"setct-PANOnly","setct-PANOnly",NID_setct_PANOnly,4,&(lvalues[3847]),0},
{"setct-OIData","setct-OIData",NID_setct_OIData,4,&(lvalues[3851]),0},
{"setct-PI","setct-PI",NID_setct_PI,4,&(lvalues[3855]),0},
{"setct-PIData","setct-PIData",NID_setct_PIData,4,&(lvalues[3859]),0},
{"setct-PIDataUnsigned","setct-PIDataUnsigned",
	NID_setct_PIDataUnsigned,4,&(lvalues[3863]),0},
{"setct-HODInput","setct-HODInput",NID_setct_HODInput,4,
	&(lvalues[3867]),0},
{"setct-AuthResBaggage","setct-AuthResBaggage",
	NID_setct_AuthResBaggage,4,&(lvalues[3871]),0},
{"setct-AuthRevReqBaggage","setct-AuthRevReqBaggage",
	NID_setct_AuthRevReqBaggage,4,&(lvalues[3875]),0},
{"setct-AuthRevResBaggage","setct-AuthRevResBaggage",
	NID_setct_AuthRevResBaggage,4,&(lvalues[3879]),0},
{"setct-CapTokenSeq","setct-CapTokenSeq",NID_setct_CapTokenSeq,4,
	&(lvalues[3883]),0},
{"setct-PInitResData","setct-PInitResData",NID_setct_PInitResData,4,
	&(lvalues[3887]),0},
{"setct-PI-TBS","setct-PI-TBS",NID_setct_PI_TBS,4,&(lvalues[3891]),0},
{"setct-PResData","setct-PResData",NID_setct_PResData,4,
	&(lvalues[3895]),0},
{"setct-AuthReqTBS","setct-AuthReqTBS",NID_setct_AuthReqTBS,4,
	&(lvalues[3899]),0},
{"setct-AuthResTBS","setct-AuthResTBS",NID_setct_AuthResTBS,4,
	&(lvalues[3903]),0},
{"setct-AuthResTBSX","setct-AuthResTBSX",NID_setct_AuthResTBSX,4,
	&(lvalues[3907]),0},
{"setct-AuthTokenTBS","setct-AuthTokenTBS",NID_setct_AuthTokenTBS,4,
	&(lvalues[3911]),0},
{"setct-CapTokenData","setct-CapTokenData",NID_setct_CapTokenData,4,
	&(lvalues[3915]),0},
{"setct-CapTokenTBS","setct-CapTokenTBS",NID_setct_CapTokenTBS,4,
	&(lvalues[3919]),0},
{"setct-AcqCardCodeMsg","setct-AcqCardCodeMsg",
	NID_setct_AcqCardCodeMsg,4,&(lvalues[3923]),0},
{"setct-AuthRevReqTBS","setct-AuthRevReqTBS",NID_setct_AuthRevReqTBS,
	4,&(lvalues[3927]),0},
{"setct-AuthRevResData","setct-AuthRevResData",
	NID_setct_AuthRevResData,4,&(lvalues[3931]),0},
{"setct-AuthRevResTBS","setct-AuthRevResTBS",NID_setct_AuthRevResTBS,
	4,&(lvalues[3935]),0},
{"setct-CapReqTBS","setct-CapReqTBS",NID_setct_CapReqTBS,4,
	&(lvalues[3939]),0},
{"setct-CapReqTBSX","setct-CapReqTBSX",NID_setct_CapReqTBSX,4,
	&(lvalues[3943]),0},
{"setct-CapResData","setct-CapResData",NID_setct_CapResData,4,
	&(lvalues[3947]),0},
{"setct-CapRevReqTBS","setct-CapRevReqTBS",NID_setct_CapRevReqTBS,4,
	&(lvalues[3951]),0},
{"setct-CapRevReqTBSX","setct-CapRevReqTBSX",NID_setct_CapRevReqTBSX,
	4,&(lvalues[3955]),0},
{"setct-CapRevResData","setct-CapRevResData",NID_setct_CapRevResData,
	4,&(lvalues[3959]),0},
{"setct-CredReqTBS","setct-CredReqTBS",NID_setct_CredReqTBS,4,
	&(lvalues[3963]),0},
{"setct-CredReqTBSX","setct-CredReqTBSX",NID_setct_CredReqTBSX,4,
	&(lvalues[3967]),0},
{"setct-CredResData","setct-CredResData",NID_setct_CredResData,4,
	&(lvalues[3971]),0},
{"setct-CredRevReqTBS","setct-CredRevReqTBS",NID_setct_CredRevReqTBS,
	4,&(lvalues[3975]),0},
{"setct-CredRevReqTBSX","setct-CredRevReqTBSX",
	NID_setct_CredRevReqTBSX,4,&(lvalues[3979]),0},
{"setct-CredRevResData","setct-CredRevResData",
	NID_setct_CredRevResData,4,&(lvalues[3983]),0},
{"setct-PCertReqData","setct-PCertReqData",NID_setct_PCertReqData,4,
	&(lvalues[3987]),0},
{"setct-PCertResTBS","setct-PCertResTBS",NID_setct_PCertResTBS,4,
	&(lvalues[3991]),0},
{"setct-BatchAdminReqData","setct-BatchAdminReqData",
	NID_setct_BatchAdminReqData,4,&(lvalues[3995]),0},
{"setct-BatchAdminResData","setct-BatchAdminResData",
	NID_setct_BatchAdminResData,4,&(lvalues[3999]),0},
{"setct-CardCInitResTBS","setct-CardCInitResTBS",
	NID_setct_CardCInitResTBS,4,&(lvalues[4003]),0},
{"setct-MeAqCInitResTBS","setct-MeAqCInitResTBS",
	NID_setct_MeAqCInitResTBS,4,&(lvalues[4007]),0},
{"setct-RegFormResTBS","setct-RegFormResTBS",NID_setct_RegFormResTBS,
	4,&(lvalues[4011]),0},
{"setct-CertReqData","setct-CertReqData",NID_setct_CertReqData,4,
	&(lvalues[4015]),0},
{"setct-CertReqTBS","setct-CertReqTBS",NID_setct_CertReqTBS,4,
	&(lvalues[4019]),0},
{"setct-CertResData","setct-CertResData",NID_setct_CertResData,4,
	&(lvalues[4023]),0},
{"setct-CertInqReqTBS","setct-CertInqReqTBS",NID_setct_CertInqReqTBS,
	4,&(lvalues[4027]),0},
{"setct-ErrorTBS","setct-ErrorTBS",NID_setct_ErrorTBS,4,
	&(lvalues[4031]),0},
{"setct-PIDualSignedTBE","setct-PIDualSignedTBE",
	NID_setct_PIDualSignedTBE,4,&(lvalues[4035]),0},
{"setct-PIUnsignedTBE","setct-PIUnsignedTBE",NID_setct_PIUnsignedTBE,
	4,&(lvalues[4039]),0},
{"setct-AuthReqTBE","setct-AuthReqTBE",NID_setct_AuthReqTBE,4,
	&(lvalues[4043]),0},
{"setct-AuthResTBE","setct-AuthResTBE",NID_setct_AuthResTBE,4,
	&(lvalues[4047]),0},
{"setct-AuthResTBEX","setct-AuthResTBEX",NID_setct_AuthResTBEX,4,
	&(lvalues[4051]),0},
{"setct-AuthTokenTBE","setct-AuthTokenTBE",NID_setct_AuthTokenTBE,4,
	&(lvalues[4055]),0},
{"setct-CapTokenTBE","setct-CapTokenTBE",NID_setct_CapTokenTBE,4,
	&(lvalues[4059]),0},
{"setct-CapTokenTBEX","setct-CapTokenTBEX",NID_setct_CapTokenTBEX,4,
	&(lvalues[4063]),0},
{"setct-AcqCardCodeMsgTBE","setct-AcqCardCodeMsgTBE",
	NID_setct_AcqCardCodeMsgTBE,4,&(lvalues[4067]),0},
{"setct-AuthRevReqTBE","setct-AuthRevReqTBE",NID_setct_AuthRevReqTBE,
	4,&(lvalues[4071]),0},
{"setct-AuthRevResTBE","setct-AuthRevResTBE",NID_setct_AuthRevResTBE,
	4,&(lvalues[4075]),0},
{"setct-AuthRevResTBEB","setct-AuthRevResTBEB",
	NID_setct_AuthRevResTBEB,4,&(lvalues[4079]),0},
{"setct-CapReqTBE","setct-CapReqTBE",NID_setct_CapReqTBE,4,
	&(lvalues[4083]),0},
{"setct-CapReqTBEX","setct-CapReqTBEX",NID_setct_CapReqTBEX,4,
	&(lvalues[4087]),0},
{"setct-CapResTBE","setct-CapResTBE",NID_setct_CapResTBE,4,
	&(lvalues[4091]),0},
{"setct-CapRevReqTBE","setct-CapRevReqTBE",NID_setct_CapRevReqTBE,4,
	&(lvalues[4095]),0},
{"setct-CapRevReqTBEX","setct-CapRevReqTBEX",NID_setct_CapRevReqTBEX,
	4,&(lvalues[4099]),0},
{"setct-CapRevResTBE","setct-CapRevResTBE",NID_setct_CapRevResTBE,4,
	&(lvalues[4103]),0},
{"setct-CredReqTBE","setct-CredReqTBE",NID_setct_CredReqTBE,4,
	&(lvalues[4107]),0},
{"setct-CredReqTBEX","setct-CredReqTBEX",NID_setct_CredReqTBEX,4,
	&(lvalues[4111]),0},
{"setct-CredResTBE","setct-CredResTBE",NID_setct_CredResTBE,4,
	&(lvalues[4115]),0},
{"setct-CredRevReqTBE","setct-CredRevReqTBE",NID_setct_CredRevReqTBE,
	4,&(lvalues[4119]),0},
{"setct-CredRevReqTBEX","setct-CredRevReqTBEX",
	NID_setct_CredRevReqTBEX,4,&(lvalues[4123]),0},
{"setct-CredRevResTBE","setct-CredRevResTBE",NID_setct_CredRevResTBE,
	4,&(lvalues[4127]),0},
{"setct-BatchAdminReqTBE","setct-BatchAdminReqTBE",
	NID_setct_BatchAdminReqTBE,4,&(lvalues[4131]),0},
{"setct-BatchAdminResTBE","setct-BatchAdminResTBE",
	NID_setct_BatchAdminResTBE,4,&(lvalues[4135]),0},
{"setct-RegFormReqTBE","setct-RegFormReqTBE",NID_setct_RegFormReqTBE,
	4,&(lvalues[4139]),0},
{"setct-CertReqTBE","setct-CertReqTBE",NID_setct_CertReqTBE,4,
	&(lvalues[4143]),0},
{"setct-CertReqTBEX","setct-CertReqTBEX",NID_setct_CertReqTBEX,4,
	&(lvalues[4147]),0},
{"setct-CertResTBE","setct-CertResTBE",NID_setct_CertResTBE,4,
	&(lvalues[4151]),0},
{"setct-CRLNotificationTBS","setct-CRLNotificationTBS",
	NID_setct_CRLNotificationTBS,4,&(lvalues[4155]),0},
{"setct-CRLNotificationResTBS","setct-CRLNotificationResTBS",
	NID_setct_CRLNotificationResTBS,4,&(lvalues[4159]),0},
{"setct-BCIDistributionTBS","setct-BCIDistributionTBS",
	NID_setct_BCIDistributionTBS,4,&(lvalues[4163]),0},
{"setext-genCrypt","generic cryptogram",NID_setext_genCrypt,4,
	&(lvalues[4167]),0},
{"setext-miAuth","merchant initiated auth",NID_setext_miAuth,4,
	&(lvalues[4171]),0},
{"setext-pinSecure","setext-pinSecure",NID_setext_pinSecure,4,
	&(lvalues[4175]),0},
{"setext-pinAny","setext-pinAny",NID_setext_pinAny,4,&(lvalues[4179]),0},
{"setext-track2","setext-track2",NID_setext_track2,4,&(lvalues[4183]),0},
{"setext-cv","additional verification",NID_setext_cv,4,
	&(lvalues[4187]),0},
{"set-policy-root","set-policy-root",NID_set_policy_root,4,
	&(lvalues[4191]),0},
{"setCext-hashedRoot","setCext-hashedRoot",NID_setCext_hashedRoot,4,
	&(lvalues[4195]),0},
{"setCext-certType","setCext-certType",NID_setCext_certType,4,
	&(lvalues[4199]),0},
{"setCext-merchData","setCext-merchData",NID_setCext_merchData,4,
	&(lvalues[4203]),0},
{"setCext-cCertRequired","setCext-cCertRequired",
	NID_setCext_cCertRequired,4,&(lvalues[4207]),0},
{"setCext-tunneling","setCext-tunneling",NID_setCext_tunneling,4,
	&(lvalues[4211]),0},
{"setCext-setExt","setCext-setExt",NID_setCext_setExt,4,
	&(lvalues[4215]),0},
{"setCext-setQualf","setCext-setQualf",NID_setCext_setQualf,4,
	&(lvalues[4219]),0},
{"setCext-PGWYcapabilities","setCext-PGWYcapabilities",
	NID_setCext_PGWYcapabilities,4,&(lvalues[4223]),0},
{"setCext-TokenIdentifier","setCext-TokenIdentifier",
	NID_setCext_TokenIdentifier,4,&(lvalues[4227]),0},
{"setCext-Track2Data","setCext-Track2Data",NID_setCext_Track2Data,4,
	&(lvalues[4231]),0},
{"setCext-TokenType","setCext-TokenType",NID_setCext_TokenType,4,
	&(lvalues[4235]),0},
{"setCext-IssuerCapabilities","setCext-IssuerCapabilities",
	NID_setCext_IssuerCapabilities,4,&(lvalues[4239]),0},
{"setAttr-Cert","setAttr-Cert",NID_setAttr_Cert,4,&(lvalues[4243]),0},
{"setAttr-PGWYcap","payment gateway capabilities",NID_setAttr_PGWYcap,
	4,&(lvalues[4247]),0},
{"setAttr-TokenType","setAttr-TokenType",NID_setAttr_TokenType,4,
	&(lvalues[4251]),0},
{"setAttr-IssCap","issuer capabilities",NID_setAttr_IssCap,4,
	&(lvalues[4255]),0},
{"set-rootKeyThumb","set-rootKeyThumb",NID_set_rootKeyThumb,5,
	&(lvalues[4259]),0},
{"set-addPolicy","set-addPolicy",NID_set_addPolicy,5,&(lvalues[4264]),0},
{"setAttr-Token-EMV","setAttr-Token-EMV",NID_setAttr_Token_EMV,5,
	&(lvalues[4269]),0},
{"setAttr-Token-B0Prime","setAttr-Token-B0Prime",
	NID_setAttr_Token_B0Prime,5,&(lvalues[4274]),0},
{"setAttr-IssCap-CVM","setAttr-IssCap-CVM",NID_setAttr_IssCap_CVM,5,
	&(lvalues[4279]),0},
{"setAttr-IssCap-T2","setAttr-IssCap-T2",NID_setAttr_IssCap_T2,5,
	&(lvalues[4284]),0},
{"setAttr-IssCap-Sig","setAttr-IssCap-Sig",NID_setAttr_IssCap_Sig,5,
	&(lvalues[4289]),0},
{"setAttr-GenCryptgrm","generate cryptogram",NID_setAttr_GenCryptgrm,
	6,&(lvalues[4294]),0},
{"setAttr-T2Enc","encrypted track 2",NID_setAttr_T2Enc,6,
	&(lvalues[4300]),0},
{"setAttr-T2cleartxt","cleartext track 2",NID_setAttr_T2cleartxt,6,
	&(lvalues[4306]),0},
{"setAttr-TokICCsig","ICC or token signature",NID_setAttr_TokICCsig,6,
	&(lvalues[4312]),0},
{"setAttr-SecDevSig","secure device signature",NID_setAttr_SecDevSig,
	6,&(lvalues[4318]),0},
{"set-brand-IATA-ATA","set-brand-IATA-ATA",NID_set_brand_IATA_ATA,4,
	&(lvalues[4324]),0},
{"set-brand-Diners","set-brand-Diners",NID_set_brand_Diners,4,
	&(lvalues[4328]),0},
{"set-brand-AmericanExpress","set-brand-AmericanExpress",
	NID_set_brand_AmericanExpress,4,&(lvalues[4332]),0},
{"set-brand-JCB","set-brand-JCB",NID_set_brand_JCB,4,&(lvalues[4336]),0},
{"set-brand-Visa","set-brand-Visa",NID_set_brand_Visa,4,
	&(lvalues[4340]),0},
{"set-brand-MasterCard","set-brand-MasterCard",
	NID_set_brand_MasterCard,4,&(lvalues[4344]),0},
{"set-brand-Novus","set-brand-Novus",NID_set_brand_Novus,5,
	&(lvalues[4348]),0},
{"DES-CDMF","des-cdmf",NID_des_cdmf,8,&(lvalues[4353]),0},
{"rsaOAEPEncryptionSET","rsaOAEPEncryptionSET",
	NID_rsaOAEPEncryptionSET,9,&(lvalues[4361]),0},
{"ITU-T","itu-t",NID_itu_t,0,NULL,0},
{"JOINT-ISO-ITU-T","joint-iso-itu-t",NID_joint_iso_itu_t,0,NULL,0},
{"international-organizations","International Organizations",
	NID_international_organizations,1,&(lvalues[4370]),0},
{"msSmartcardLogin","Microsoft Smartcardlogin",NID_ms_smartcard_login,
	10,&(lvalues[4371]),0},
{"msUPN","Microsoft Universal Principal Name",NID_ms_upn,10,
	&(lvalues[4381]),0},
{"AES-128-CFB1","aes-128-cfb1",NID_aes_128_cfb1,0,NULL,0},
{"AES-192-CFB1","aes-192-cfb1",NID_aes_192_cfb1,0,NULL,0},
{"AES-256-CFB1","aes-256-cfb1",NID_aes_256_cfb1,0,NULL,0},
{"AES-128-CFB8","aes-128-cfb8",NID_aes_128_cfb8,0,NULL,0},
{"AES-192-CFB8","aes-192-cfb8",NID_aes_192_cfb8,0,NULL,0},
{"AES-256-CFB8","aes-256-cfb8",NID_aes_256_cfb8,0,NULL,0},
{NULL,NULL,NID_undef,0,NULL,0},
{NULL,NULL,NID_undef,0,NULL,0},
{"DES-EDE3-CFB1","des-ede3-cfb1",NID_des_ede3_cfb1,0,NULL,0},
{"DES-EDE3-CFB8","des-ede3-cfb8",NID_des_ede3_cfb8,0,NULL,0},
{"street","streetAddress",NID_streetAddress,3,&(lvalues[4391]),0},
{"postalCode","postalCode",NID_postalCode,3,&(lvalues[4394]),0},
{"id-ppl","id-ppl",NID_id_ppl,7,&(lvalues[4397]),0},
{"proxyCertInfo","Proxy Certificate Information",NID_proxyCertInfo,8,
	&(lvalues[4404]),0},
{"id-ppl-anyLanguage","Any language",NID_id_ppl_anyLanguage,8,
	&(lvalues[4412]),0},
{"id-ppl-inheritAll","Inherit all",NID_id_ppl_inheritAll,8,
	&(lvalues[4420]),0},
{"nameConstraints","X509v3 Name Constraints",NID_name_constraints,3,
	&(lvalues[4428]),0},
{"id-ppl-independent","Independent",NID_Independent,8,&(lvalues[4431]),0},
{"RSA-SHA256","sha256WithRSAEncryption",NID_sha256WithRSAEncryption,9,
	&(lvalues[4439]),0},
{"RSA-SHA384","sha384WithRSAEncryption",NID_sha384WithRSAEncryption,9,
	&(lvalues[4448]),0},
{"RSA-SHA512","sha512WithRSAEncryption",NID_sha512WithRSAEncryption,9,
	&(lvalues[4457]),0},
{"RSA-SHA224","sha224WithRSAEncryption",NID_sha224WithRSAEncryption,9,
	&(lvalues[4466]),0},
{"SHA256","sha256",NID_sha256,9,&(lvalues[4475]),0},
{"SHA384","sha384",NID_sha384,9,&(lvalues[4484]),0},
{"SHA512","sha512",NID_sha512,9,&(lvalues[4493]),0},
{"SHA224","sha224",NID_sha224,9,&(lvalues[4502]),0},
{"identified-organization","identified-organization",
	NID_identified_organization,1,&(lvalues[4511]),0},
{"certicom-arc","certicom-arc",NID_certicom_arc,3,&(lvalues[4512]),0},
{"wap","wap",NID_wap,2,&(lvalues[4515]),0},
{"wap-wsg","wap-wsg",NID_wap_wsg,3,&(lvalues[4517]),0},
{"id-characteristic-two-basis","id-characteristic-two-basis",
	NID_X9_62_id_characteristic_two_basis,8,&(lvalues[4520]),0},
{"onBasis","onBasis",NID_X9_62_onBasis,9,&(lvalues[4528]),0},
{"tpBasis","tpBasis",NID_X9_62_tpBasis,9,&(lvalues[4537]),0},
{"ppBasis","ppBasis",NID_X9_62_ppBasis,9,&(lvalues[4546]),0},
{"c2pnb163v1","c2pnb163v1",NID_X9_62_c2pnb163v1,8,&(lvalues[4555]),0},
{"c2pnb163v2","c2pnb163v2",NID_X9_62_c2pnb163v2,8,&(lvalues[4563]),0},
{"c2pnb163v3","c2pnb163v3",NID_X9_62_c2pnb163v3,8,&(lvalues[4571]),0},
{"c2pnb176v1","c2pnb176v1",NID_X9_62_c2pnb176v1,8,&(lvalues[4579]),0},
{"c2tnb191v1","c2tnb191v1",NID_X9_62_c2tnb191v1,8,&(lvalues[4587]),0},
{"c2tnb191v2","c2tnb191v2",NID_X9_62_c2tnb191v2,8,&(lvalues[4595]),0},
{"c2tnb191v3","c2tnb191v3",NID_X9_62_c2tnb191v3,8,&(lvalues[4603]),0},
{"c2onb191v4","c2onb191v4",NID_X9_62_c2onb191v4,8,&(lvalues[4611]),0},
{"c2onb191v5","c2onb191v5",NID_X9_62_c2onb191v5,8,&(lvalues[4619]),0},
{"c2pnb208w1","c2pnb208w1",NID_X9_62_c2pnb208w1,8,&(lvalues[4627]),0},
{"c2tnb239v1","c2tnb239v1",NID_X9_62_c2tnb239v1,8,&(lvalues[4635]),0},
{"c2tnb239v2","c2tnb239v2",NID_X9_62_c2tnb239v2,8,&(lvalues[4643]),0},
{"c2tnb239v3","c2tnb239v3",NID_X9_62_c2tnb239v3,8,&(lvalues[4651]),0},
{"c2onb239v4","c2onb239v4",NID_X9_62_c2onb239v4,8,&(lvalues[4659]),0},
{"c2onb239v5","c2onb239v5",NID_X9_62_c2onb239v5,8,&(lvalues[4667]),0},
{"c2pnb272w1","c2pnb272w1",NID_X9_62_c2pnb272w1,8,&(lvalues[4675]),0},
{"c2pnb304w1","c2pnb304w1",NID_X9_62_c2pnb304w1,8,&(lvalues[4683]),0},
{"c2tnb359v1","c2tnb359v1",NID_X9_62_c2tnb359v1,8,&(lvalues[4691]),0},
{"c2pnb368w1","c2pnb368w1",NID_X9_62_c2pnb368w1,8,&(lvalues[4699]),0},
{"c2tnb431r1","c2tnb431r1",NID_X9_62_c2tnb431r1,8,&(lvalues[4707]),0},
{"secp112r1","secp112r1",NID_secp112r1,5,&(lvalues[4715]),0},
{"secp112r2","secp112r2",NID_secp112r2,5,&(lvalues[4720]),0},
{"secp128r1","secp128r1",NID_secp128r1,5,&(lvalues[4725]),0},
{"secp128r2","secp128r2",NID_secp128r2,5,&(lvalues[4730]),0},
{"secp160k1","secp160k1",NID_secp160k1,5,&(lvalues[4735]),0},
{"secp160r1","secp160r1",NID_secp160r1,5,&(lvalues[4740]),0},
{"secp160r2","secp160r2",NID_secp160r2,5,&(lvalues[4745]),0},
{"secp192k1","secp192k1",NID_secp192k1,5,&(lvalues[4750]),0},
{"secp224k1","secp224k1",NID_secp224k1,5,&(lvalues[4755]),0},
{"secp224r1","secp224r1",NID_secp224r1,5,&(lvalues[4760]),0},
{"secp256k1","secp256k1",NID_secp256k1,5,&(lvalues[4765]),0},
{"secp384r1","secp384r1",NID_secp384r1,5,&(lvalues[4770]),0},
{"secp521r1","secp521r1",NID_secp521r1,5,&(lvalues[4775]),0},
{"sect113r1","sect113r1",NID_sect113r1,5,&(lvalues[4780]),0},
{"sect113r2","sect113r2",NID_sect113r2,5,&(lvalues[4785]),0},
{"sect131r1","sect131r1",NID_sect131r1,5,&(lvalues[4790]),0},
{"sect131r2","sect131r2",NID_sect131r2,5,&(lvalues[4795]),0},
{"sect163k1","sect163k1",NID_sect163k1,5,&(lvalues[4800]),0},
{"sect163r1","sect163r1",NID_sect163r1,5,&(lvalues[4805]),0},
{"sect163r2","sect163r2",NID_sect163r2,5,&(lvalues[4810]),0},
{"sect193r1","sect193r1",NID_sect193r1,5,&(lvalues[4815]),0},
{"sect193r2","sect193r2",NID_sect193r2,5,&(lvalues[4820]),0},
{"sect233k1","sect233k1",NID_sect233k1,5,&(lvalues[4825]),0},
{"sect233r1","sect233r1",NID_sect233r1,5,&(lvalues[4830]),0},
{"sect239k1","sect239k1",NID_sect239k1,5,&(lvalues[4835]),0},
{"sect283k1","sect283k1",NID_sect283k1,5,&(lvalues[4840]),0},
{"sect283r1","sect283r1",NID_sect283r1,5,&(lvalues[4845]),0},
{"sect409k1","sect409k1",NID_sect409k1,5,&(lvalues[4850]),0},
{"sect409r1","sect409r1",NID_sect409r1,5,&(lvalues[4855]),0},
{"sect571k1","sect571k1",NID_sect571k1,5,&(lvalues[4860]),0},
{"sect571r1","sect571r1",NID_sect571r1,5,&(lvalues[4865]),0},
{"wap-wsg-idm-ecid-wtls1","wap-wsg-idm-ecid-wtls1",
	NID_wap_wsg_idm_ecid_wtls1,5,&(lvalues[4870]),0},
{"wap-wsg-idm-ecid-wtls3","wap-wsg-idm-ecid-wtls3",
	NID_wap_wsg_idm_ecid_wtls3,5,&(lvalues[4875]),0},
{"wap-wsg-idm-ecid-wtls4","wap-wsg-idm-ecid-wtls4",
	NID_wap_wsg_idm_ecid_wtls4,5,&(lvalues[4880]),0},
{"wap-wsg-idm-ecid-wtls5","wap-wsg-idm-ecid-wtls5",
	NID_wap_wsg_idm_ecid_wtls5,5,&(lvalues[4885]),0},
{"wap-wsg-idm-ecid-wtls6","wap-wsg-idm-ecid-wtls6",
	NID_wap_wsg_idm_ecid_wtls6,5,&(lvalues[4890]),0},
{"wap-wsg-idm-ecid-wtls7","wap-wsg-idm-ecid-wtls7",
	NID_wap_wsg_idm_ecid_wtls7,5,&(lvalues[4895]),0},
{"wap-wsg-idm-ecid-wtls8","wap-wsg-idm-ecid-wtls8",
	NID_wap_wsg_idm_ecid_wtls8,5,&(lvalues[4900]),0},
{"wap-wsg-idm-ecid-wtls9","wap-wsg-idm-ecid-wtls9",
	NID_wap_wsg_idm_ecid_wtls9,5,&(lvalues[4905]),0},
{"wap-wsg-idm-ecid-wtls10","wap-wsg-idm-ecid-wtls10",
	NID_wap_wsg_idm_ecid_wtls10,5,&(lvalues[4910]),0},
{"wap-wsg-idm-ecid-wtls11","wap-wsg-idm-ecid-wtls11",
	NID_wap_wsg_idm_ecid_wtls11,5,&(lvalues[4915]),0},
{"wap-wsg-idm-ecid-wtls12","wap-wsg-idm-ecid-wtls12",
	NID_wap_wsg_idm_ecid_wtls12,5,&(lvalues[4920]),0},
{"anyPolicy","X509v3 Any Policy",NID_any_policy,4,&(lvalues[4925]),0},
{"policyMappings","X509v3 Policy Mappings",NID_policy_mappings,3,
	&(lvalues[4929]),0},
{"inhibitAnyPolicy","X509v3 Inhibit Any Policy",
	NID_inhibit_any_policy,3,&(lvalues[4932]),0},
{"Oakley-EC2N-3","ipsec3",NID_ipsec3,0,NULL,0},
{"Oakley-EC2N-4","ipsec4",NID_ipsec4,0,NULL,0},
{"CAMELLIA-128-CBC","camellia-128-cbc",NID_camellia_128_cbc,11,
	&(lvalues[4935]),0},
{"CAMELLIA-192-CBC","camellia-192-cbc",NID_camellia_192_cbc,11,
	&(lvalues[4946]),0},
{"CAMELLIA-256-CBC","camellia-256-cbc",NID_camellia_256_cbc,11,
	&(lvalues[4957]),0},
{"CAMELLIA-128-ECB","camellia-128-ecb",NID_camellia_128_ecb,8,
	&(lvalues[4968]),0},
{"CAMELLIA-192-ECB","camellia-192-ecb",NID_camellia_192_ecb,8,
	&(lvalues[4976]),0},
{"CAMELLIA-256-ECB","camellia-256-ecb",NID_camellia_256_ecb,8,
	&(lvalues[4984]),0},
{"CAMELLIA-128-CFB","camellia-128-cfb",NID_camellia_128_cfb128,8,
	&(lvalues[4992]),0},
{"CAMELLIA-192-CFB","camellia-192-cfb",NID_camellia_192_cfb128,8,
	&(lvalues[5000]),0},
{"CAMELLIA-256-CFB","camellia-256-cfb",NID_camellia_256_cfb128,8,
	&(lvalues[5008]),0},
{"CAMELLIA-128-CFB1","camellia-128-cfb1",NID_camellia_128_cfb1,0,NULL,0},
{"CAMELLIA-192-CFB1","camellia-192-cfb1",NID_camellia_192_cfb1,0,NULL,0},
{"CAMELLIA-256-CFB1","camellia-256-cfb1",NID_camellia_256_cfb1,0,NULL,0},
{"CAMELLIA-128-CFB8","camellia-128-cfb8",NID_camellia_128_cfb8,0,NULL,0},
{"CAMELLIA-192-CFB8","camellia-192-cfb8",NID_camellia_192_cfb8,0,NULL,0},
{"CAMELLIA-256-CFB8","camellia-256-cfb8",NID_camellia_256_cfb8,0,NULL,0},
{"CAMELLIA-128-OFB","camellia-128-ofb",NID_camellia_128_ofb128,8,
	&(lvalues[5016]),0},
{"CAMELLIA-192-OFB","camellia-192-ofb",NID_camellia_192_ofb128,8,
	&(lvalues[5024]),0},
{"CAMELLIA-256-OFB","camellia-256-ofb",NID_camellia_256_ofb128,8,
	&(lvalues[5032]),0},
{"subjectDirectoryAttributes","X509v3 Subject Directory Attributes",
	NID_subject_directory_attributes,3,&(lvalues[5040]),0},
{"issuingDistributionPoint","X509v3 Issuing Distrubution Point",
	NID_issuing_distribution_point,3,&(lvalues[5043]),0},
{"certificateIssuer","X509v3 Certificate Issuer",
	NID_certificate_issuer,3,&(lvalues[5046]),0},
{NULL,NULL,NID_undef,0,NULL,0},
{NULL,NULL,NID_undef,0,NULL,0},
{NULL,NULL,NID_undef,0,NULL,0},
{NULL,NULL,NID_undef,0,NULL,0},
{NULL,NULL,NID_undef,0,NULL,0},
{NULL,NULL,NID_undef,0,NULL,0},
{NULL,NULL,NID_undef,0,NULL,0},
{NULL,NULL,NID_undef,0,NULL,0},
{"HMAC-MD5","hmac-md5",NID_hmac_md5,8,&(lvalues[5049]),0},
{"HMAC-SHA1","hmac-sha1",NID_hmac_sha1,8,&(lvalues[5057]),0},
{"id-PasswordBasedMAC","password based MAC",NID_id_PasswordBasedMAC,9,
	&(lvalues[5065]),0},
{"id-DHBasedMac","Diffie-Hellman based MAC",NID_id_DHBasedMac,9,
	&(lvalues[5074]),0},
{"id-it-suppLangTags","id-it-suppLangTags",NID_id_it_suppLangTags,8,
	&(lvalues[5083]),0},
{"caRepository","CA Repository",NID_caRepository,8,&(lvalues[5091]),0},
{"id-smime-ct-compressedData","id-smime-ct-compressedData",
	NID_id_smime_ct_compressedData,11,&(lvalues[5099]),0},
{"id-ct-asciiTextWithCRLF","id-ct-asciiTextWithCRLF",
	NID_id_ct_asciiTextWithCRLF,11,&(lvalues[5110]),0},
{"id-aes128-wrap","id-aes128-wrap",NID_id_aes128_wrap,9,
	&(lvalues[5121]),0},
{"id-aes192-wrap","id-aes192-wrap",NID_id_aes192_wrap,9,
	&(lvalues[5130]),0},
{"id-aes256-wrap","id-aes256-wrap",NID_id_aes256_wrap,9,
	&(lvalues[5139]),0},
{"ecdsa-with-Recommended","ecdsa-with-Recommended",
	NID_ecdsa_with_Recommended,7,&(lvalues[5148]),0},
{"ecdsa-with-Specified","ecdsa-with-Specified",
	NID_ecdsa_with_Specified,7,&(lvalues[5155]),0},
{"ecdsa-with-SHA224","ecdsa-with-SHA224",NID_ecdsa_with_SHA224,8,
	&(lvalues[5162]),0},
{"ecdsa-with-SHA256","ecdsa-with-SHA256",NID_ecdsa_with_SHA256,8,
	&(lvalues[5170]),0},
{"ecdsa-with-SHA384","ecdsa-with-SHA384",NID_ecdsa_with_SHA384,8,
	&(lvalues[5178]),0},
{"ecdsa-with-SHA512","ecdsa-with-SHA512",NID_ecdsa_with_SHA512,8,
	&(lvalues[5186]),0},
{"hmacWithMD5","hmacWithMD5",NID_hmacWithMD5,8,&(lvalues[5194]),0},
{"hmacWithSHA224","hmacWithSHA224",NID_hmacWithSHA224,8,
	&(lvalues[5202]),0},
{"hmacWithSHA256","hmacWithSHA256",NID_hmacWithSHA256,8,
	&(lvalues[5210]),0},
{"hmacWithSHA384","hmacWithSHA384",NID_hmacWithSHA384,8,
	&(lvalues[5218]),0},
{"hmacWithSHA512","hmacWithSHA512",NID_hmacWithSHA512,8,
	&(lvalues[5226]),0},
{"dsa_with_SHA224","dsa_with_SHA224",NID_dsa_with_SHA224,9,
	&(lvalues[5234]),0},
{"dsa_with_SHA256","dsa_with_SHA256",NID_dsa_with_SHA256,9,
	&(lvalues[5243]),0},
{"whirlpool","whirlpool",NID_whirlpool,6,&(lvalues[5252]),0},
{"cryptopro","cryptopro",NID_cryptopro,5,&(lvalues[5258]),0},
{"cryptocom","cryptocom",NID_cryptocom,5,&(lvalues[5263]),0},
{"id-GostR3411-94-with-GostR3410-2001",
	"GOST R 34.11-94 with GOST R 34.10-2001",
	NID_id_GostR3411_94_with_GostR3410_2001,6,&(lvalues[5268]),0},
{"id-GostR3411-94-with-GostR3410-94",
	"GOST R 34.11-94 with GOST R 34.10-94",
	NID_id_GostR3411_94_with_GostR3410_94,6,&(lvalues[5274]),0},
{"md_gost94","GOST R 34.11-94",NID_id_GostR3411_94,6,&(lvalues[5280]),0},
{"id-HMACGostR3411-94","HMAC GOST 34.11-94",NID_id_HMACGostR3411_94,6,
	&(lvalues[5286]),0},
{"gost2001","GOST R 34.10-2001",NID_id_GostR3410_2001,6,
	&(lvalues[5292]),0},
{"gost94","GOST R 34.10-94",NID_id_GostR3410_94,6,&(lvalues[5298]),0},
{"gost89","GOST 28147-89",NID_id_Gost28147_89,6,&(lvalues[5304]),0},
{"gost89-cnt","gost89-cnt",NID_gost89_cnt,0,NULL,0},
{"gost-mac","GOST 28147-89 MAC",NID_id_Gost28147_89_MAC,6,
	&(lvalues[5310]),0},
{"prf-gostr3411-94","GOST R 34.11-94 PRF",NID_id_GostR3411_94_prf,6,
	&(lvalues[5316]),0},
{"id-GostR3410-2001DH","GOST R 34.10-2001 DH",NID_id_GostR3410_2001DH,
	6,&(lvalues[5322]),0},
{"id-GostR3410-94DH","GOST R 34.10-94 DH",NID_id_GostR3410_94DH,6,
	&(lvalues[5328]),0},
{"id-Gost28147-89-CryptoPro-KeyMeshing",
	"id-Gost28147-89-CryptoPro-KeyMeshing",
	NID_id_Gost28147_89_CryptoPro_KeyMeshing,7,&(lvalues[5334]),0},
{"id-Gost28147-89-None-KeyMeshing","id-Gost28147-89-None-KeyMeshing",
	NID_id_Gost28147_89_None_KeyMeshing,7,&(lvalues[5341]),0},
{"id-GostR3411-94-TestParamSet","id-GostR3411-94-TestParamSet",
	NID_id_GostR3411_94_TestParamSet,7,&(lvalues[5348]),0},
{"id-GostR3411-94-CryptoProParamSet",
	"id-GostR3411-94-CryptoProParamSet",
	NID_id_GostR3411_94_CryptoProParamSet,7,&(lvalues[5355]),0},
{"id-Gost28147-89-TestParamSet","id-Gost28147-89-TestParamSet",
	NID_id_Gost28147_89_TestParamSet,7,&(lvalues[5362]),0},
{"id-Gost28147-89-CryptoPro-A-ParamSet",
	"id-Gost28147-89-CryptoPro-A-ParamSet",
	NID_id_Gost28147_89_CryptoPro_A_ParamSet,7,&(lvalues[5369]),0},
{"id-Gost28147-89-CryptoPro-B-ParamSet",
	"id-Gost28147-89-CryptoPro-B-ParamSet",
	NID_id_Gost28147_89_CryptoPro_B_ParamSet,7,&(lvalues[5376]),0},
{"id-Gost28147-89-CryptoPro-C-ParamSet",
	"id-Gost28147-89-CryptoPro-C-ParamSet",
	NID_id_Gost28147_89_CryptoPro_C_ParamSet,7,&(lvalues[5383]),0},
{"id-Gost28147-89-CryptoPro-D-ParamSet",
	"id-Gost28147-89-CryptoPro-D-ParamSet",
	NID_id_Gost28147_89_CryptoPro_D_ParamSet,7,&(lvalues[5390]),0},
{"id-Gost28147-89-CryptoPro-Oscar-1-1-ParamSet",
	"id-Gost28147-89-CryptoPro-Oscar-1-1-ParamSet",
	NID_id_Gost28147_89_CryptoPro_Oscar_1_1_ParamSet,7,&(lvalues[5397]),
	0},
{"id-Gost28147-89-CryptoPro-Oscar-1-0-ParamSet",
	"id-Gost28147-89-CryptoPro-Oscar-1-0-ParamSet",
	NID_id_Gost28147_89_CryptoPro_Oscar_1_0_ParamSet,7,&(lvalues[5404]),
	0},
{"id-Gost28147-89-CryptoPro-RIC-1-ParamSet",
	"id-Gost28147-89-CryptoPro-RIC-1-ParamSet",
	NID_id_Gost28147_89_CryptoPro_RIC_1_ParamSet,7,&(lvalues[5411]),0},
{"id-GostR3410-94-TestParamSet","id-GostR3410-94-TestParamSet",
	NID_id_GostR3410_94_TestParamSet,7,&(lvalues[5418]),0},
{"id-GostR3410-94-CryptoPro-A-ParamSet",
	"id-GostR3410-94-CryptoPro-A-ParamSet",
	NID_id_GostR3410_94_CryptoPro_A_ParamSet,7,&(lvalues[5425]),0},
{"id-GostR3410-94-CryptoPro-B-ParamSet",
	"id-GostR3410-94-CryptoPro-B-ParamSet",
	NID_id_GostR3410_94_CryptoPro_B_ParamSet,7,&(lvalues[5432]),0},
{"id-GostR3410-94-CryptoPro-C-ParamSet",
	"id-GostR3410-94-CryptoPro-C-ParamSet",
	NID_id_GostR3410_94_CryptoPro_C_ParamSet,7,&(lvalues[5439]),0},
{"id-GostR3410-94-CryptoPro-D-ParamSet",
	"id-GostR3410-94-CryptoPro-D-ParamSet",
	NID_id_GostR3410_94_CryptoPro_D_ParamSet,7,&(lvalues[5446]),0},
{"id-GostR3410-94-CryptoPro-XchA-ParamSet",
	"id-GostR3410-94-CryptoPro-XchA-ParamSet",
	NID_id_GostR3410_94_CryptoPro_XchA_ParamSet,7,&(lvalues[5453]),0},
{"id-GostR3410-94-CryptoPro-XchB-ParamSet",
	"id-GostR3410-94-CryptoPro-XchB-ParamSet",
	NID_id_GostR3410_94_CryptoPro_XchB_ParamSet,7,&(lvalues[5460]),0},
{"id-GostR3410-94-CryptoPro-XchC-ParamSet",
	"id-GostR3410-94-CryptoPro-XchC-ParamSet",
	NID_id_GostR3410_94_CryptoPro_XchC_ParamSet,7,&(lvalues[5467]),0},
{"id-GostR3410-2001-TestParamSet","id-GostR3410-2001-TestParamSet",
	NID_id_GostR3410_2001_TestParamSet,7,&(lvalues[5474]),0},
{"id-GostR3410-2001-CryptoPro-A-ParamSet",
	"id-GostR3410-2001-CryptoPro-A-ParamSet",
	NID_id_GostR3410_2001_CryptoPro_A_ParamSet,7,&(lvalues[5481]),0},
{"id-GostR3410-2001-CryptoPro-B-ParamSet",
	"id-GostR3410-2001-CryptoPro-B-ParamSet",
	NID_id_GostR3410_2001_CryptoPro_B_ParamSet,7,&(lvalues[5488]),0},
{"id-GostR3410-2001-CryptoPro-C-ParamSet",
	"id-GostR3410-2001-CryptoPro-C-ParamSet",
	NID_id_GostR3410_2001_CryptoPro_C_ParamSet,7,&(lvalues[5495]),0},
{"id-GostR3410-2001-CryptoPro-XchA-ParamSet",
	"id-GostR3410-2001-CryptoPro-XchA-ParamSet",
	NID_id_GostR3410_2001_CryptoPro_XchA_ParamSet,7,&(lvalues[5502]),0},
	
{"id-GostR3410-2001-CryptoPro-XchB-ParamSet",
	"id-GostR3410-2001-CryptoPro-XchB-ParamSet",
	NID_id_GostR3410_2001_CryptoPro_XchB_ParamSet,7,&(lvalues[5509]),0},
	
{"id-GostR3410-94-a","id-GostR3410-94-a",NID_id_GostR3410_94_a,7,
	&(lvalues[5516]),0},
{"id-GostR3410-94-aBis","id-GostR3410-94-aBis",
	NID_id_GostR3410_94_aBis,7,&(lvalues[5523]),0},
{"id-GostR3410-94-b","id-GostR3410-94-b",NID_id_GostR3410_94_b,7,
	&(lvalues[5530]),0},
{"id-GostR3410-94-bBis","id-GostR3410-94-bBis",
	NID_id_GostR3410_94_bBis,7,&(lvalues[5537]),0},
{"id-Gost28147-89-cc","GOST 28147-89 Cryptocom ParamSet",
	NID_id_Gost28147_89_cc,8,&(lvalues[5544]),0},
{"gost94cc","GOST 34.10-94 Cryptocom",NID_id_GostR3410_94_cc,8,
	&(lvalues[5552]),0},
{"gost2001cc","GOST 34.10-2001 Cryptocom",NID_id_GostR3410_2001_cc,8,
	&(lvalues[5560]),0},
{"id-GostR3411-94-with-GostR3410-94-cc",
	"GOST R 34.11-94 with GOST R 34.10-94 Cryptocom",
	NID_id_GostR3411_94_with_GostR3410_94_cc,8,&(lvalues[5568]),0},
{"id-GostR3411-94-with-GostR3410-2001-cc",
	"GOST R 34.11-94 with GOST R 34.10-2001 Cryptocom",
	NID_id_GostR3411_94_with_GostR3410_2001_cc,8,&(lvalues[5576]),0},
{"id-GostR3410-2001-ParamSet-cc",
	"GOST R 3410-2001 Parameter Set Cryptocom",
	NID_id_GostR3410_2001_ParamSet_cc,8,&(lvalues[5584]),0},
{"HMAC","hmac",NID_hmac,0,NULL,0},
{"LocalKeySet","Microsoft Local Key set",NID_LocalKeySet,9,
	&(lvalues[5592]),0},
{"freshestCRL","X509v3 Freshest CRL",NID_freshest_crl,3,
	&(lvalues[5601]),0},
{"id-on-permanentIdentifier","Permanent Identifier",
	NID_id_on_permanentIdentifier,8,&(lvalues[5604]),0},
{"searchGuide","searchGuide",NID_searchGuide,3,&(lvalues[5612]),0},
{"businessCategory","businessCategory",NID_businessCategory,3,
	&(lvalues[5615]),0},
{"postalAddress","postalAddress",NID_postalAddress,3,&(lvalues[5618]),0},
{"postOfficeBox","postOfficeBox",NID_postOfficeBox,3,&(lvalues[5621]),0},
{"physicalDeliveryOfficeName","physicalDeliveryOfficeName",
	NID_physicalDeliveryOfficeName,3,&(lvalues[5624]),0},
{"telephoneNumber","telephoneNumber",NID_telephoneNumber,3,
	&(lvalues[5627]),0},
{"telexNumber","telexNumber",NID_telexNumber,3,&(lvalues[5630]),0},
{"teletexTerminalIdentifier","teletexTerminalIdentifier",
	NID_teletexTerminalIdentifier,3,&(lvalues[5633]),0},
{"facsimileTelephoneNumber","facsimileTelephoneNumber",
	NID_facsimileTelephoneNumber,3,&(lvalues[5636]),0},
{"x121Address","x121Address",NID_x121Address,3,&(lvalues[5639]),0},
{"internationaliSDNNumber","internationaliSDNNumber",
	NID_internationaliSDNNumber,3,&(lvalues[5642]),0},
{"registeredAddress","registeredAddress",NID_registeredAddress,3,
	&(lvalues[5645]),0},
{"destinationIndicator","destinationIndicator",
	NID_destinationIndicator,3,&(lvalues[5648]),0},
{"preferredDeliveryMethod","preferredDeliveryMethod",
	NID_preferredDeliveryMethod,3,&(lvalues[5651]),0},
{"presentationAddress","presentationAddress",NID_presentationAddress,
	3,&(lvalues[5654]),0},
{"supportedApplicationContext","supportedApplicationContext",
	NID_supportedApplicationContext,3,&(lvalues[5657]),0},
{"member","member",NID_member,3,&(lvalues[5660]),0},
{"owner","owner",NID_owner,3,&(lvalues[5663]),0},
{"roleOccupant","roleOccupant",NID_roleOccupant,3,&(lvalues[5666]),0},
{"seeAlso","seeAlso",NID_seeAlso,3,&(lvalues[5669]),0},
{"userPassword","userPassword",NID_userPassword,3,&(lvalues[5672]),0},
{"userCertificate","userCertificate",NID_userCertificate,3,
	&(lvalues[5675]),0},
{"cACertificate","cACertificate",NID_cACertificate,3,&(lvalues[5678]),0},
{"authorityRevocationList","authorityRevocationList",
	NID_authorityRevocationList,3,&(lvalues[5681]),0},
{"certificateRevocationList","certificateRevocationList",
	NID_certificateRevocationList,3,&(lvalues[5684]),0},
{"crossCertificatePair","crossCertificatePair",
	NID_crossCertificatePair,3,&(lvalues[5687]),0},
{"enhancedSearchGuide","enhancedSearchGuide",NID_enhancedSearchGuide,
	3,&(lvalues[5690]),0},
{"protocolInformation","protocolInformation",NID_protocolInformation,
	3,&(lvalues[5693]),0},
{"distinguishedName","distinguishedName",NID_distinguishedName,3,
	&(lvalues[5696]),0},
{"uniqueMember","uniqueMember",NID_uniqueMember,3,&(lvalues[5699]),0},
{"houseIdentifier","houseIdentifier",NID_houseIdentifier,3,
	&(lvalues[5702]),0},
{"supportedAlgorithms","supportedAlgorithms",NID_supportedAlgorithms,
	3,&(lvalues[5705]),0},
{"deltaRevocationList","deltaRevocationList",NID_deltaRevocationList,
	3,&(lvalues[5708]),0},
{"dmdName","dmdName",NID_dmdName,3,&(lvalues[5711]),0},
{"id-alg-PWRI-KEK","id-alg-PWRI-KEK",NID_id_alg_PWRI_KEK,11,
	&(lvalues[5714]),0},
{"CMAC","cmac",NID_cmac,0,NULL,0},
{"id-aes128-GCM","aes-128-gcm",NID_aes_128_gcm,9,&(lvalues[5725]),0},
{"id-aes128-CCM","aes-128-ccm",NID_aes_128_ccm,9,&(lvalues[5734]),0},
{"id-aes128-wrap-pad","id-aes128-wrap-pad",NID_id_aes128_wrap_pad,9,
	&(lvalues[5743]),0},
{"id-aes192-GCM","aes-192-gcm",NID_aes_192_gcm,9,&(lvalues[5752]),0},
{"id-aes192-CCM","aes-192-ccm",NID_aes_192_ccm,9,&(lvalues[5761]),0},
{"id-aes192-wrap-pad","id-aes192-wrap-pad",NID_id_aes192_wrap_pad,9,
	&(lvalues[5770]),0},
{"id-aes256-GCM","aes-256-gcm",NID_aes_256_gcm,9,&(lvalues[5779]),0},
{"id-aes256-CCM","aes-256-ccm",NID_aes_256_ccm,9,&(lvalues[5788]),0},
{"id-aes256-wrap-pad","id-aes256-wrap-pad",NID_id_aes256_wrap_pad,9,
	&(lvalues[5797]),0},
{"AES-128-CTR","aes-128-ctr",NID_aes_128_ctr,0,NULL,0},
{"AES-192-CTR","aes-192-ctr",NID_aes_192_ctr,0,NULL,0},
{"AES-256-CTR","aes-256-ctr",NID_aes_256_ctr,0,NULL,0},
{"id-camellia128-wrap","id-camellia128-wrap",NID_id_camellia128_wrap,
	11,&(lvalues[5806]),0},
{"id-camellia192-wrap","id-camellia192-wrap",NID_id_camellia192_wrap,
	11,&(lvalues[5817]),0},
{"id-camellia256-wrap","id-camellia256-wrap",NID_id_camellia256_wrap,
	11,&(lvalues[5828]),0},
{"anyExtendedKeyUsage","Any Extended Key Usage",
	NID_anyExtendedKeyUsage,4,&(lvalues[5839]),0},
{"MGF1","mgf1",NID_mgf1,9,&(lvalues[5843]),0},
{"RSASSA-PSS","rsassaPss",NID_rsassaPss,9,&(lvalues[5852]),0},
{"AES-128-XTS","aes-128-xts",NID_aes_128_xts,0,NULL,0},
{"AES-256-XTS","aes-256-xts",NID_aes_256_xts,0,NULL,0},
{"RC4-HMAC-MD5","rc4-hmac-md5",NID_rc4_hmac_md5,0,NULL,0},
{"AES-128-CBC-HMAC-SHA1","aes-128-cbc-hmac-sha1",
	NID_aes_128_cbc_hmac_sha1,0,NULL,0},
{"AES-192-CBC-HMAC-SHA1","aes-192-cbc-hmac-sha1",
	NID_aes_192_cbc_hmac_sha1,0,NULL,0},
{"AES-256-CBC-HMAC-SHA1","aes-256-cbc-hmac-sha1",
	NID_aes_256_cbc_hmac_sha1,0,NULL,0},
{"RSAES-OAEP","rsaesOaep",NID_rsaesOaep,9,&(lvalues[5861]),0},
{"ChaCha","chacha",NID_chacha20,0,NULL,0},
{"teletrust","teletrust",NID_teletrust,2,&(lvalues[5870]),0},
{"brainpool","brainpool",NID_brainpool,7,&(lvalues[5872]),0},
{"brainpoolP160r1","brainpoolP160r1",NID_brainpoolP160r1,9,
	&(lvalues[5879]),0},
{"brainpoolP160t1","brainpoolP160t1",NID_brainpoolP160t1,9,
	&(lvalues[5888]),0},
{"brainpoolP192r1","brainpoolP192r1",NID_brainpoolP192r1,9,
	&(lvalues[5897]),0},
{"brainpoolP192t1","brainpoolP192t1",NID_brainpoolP192t1,9,
	&(lvalues[5906]),0},
{"brainpoolP224r1","brainpoolP224r1",NID_brainpoolP224r1,9,
	&(lvalues[5915]),0},
{"brainpoolP224t1","brainpoolP224t1",NID_brainpoolP224t1,9,
	&(lvalues[5924]),0},
{"brainpoolP256r1","brainpoolP256r1",NID_brainpoolP256r1,9,
	&(lvalues[5933]),0},
{"brainpoolP256t1","brainpoolP256t1",NID_brainpoolP256t1,9,
	&(lvalues[5942]),0},
{"brainpoolP320r1","brainpoolP320r1",NID_brainpoolP320r1,9,
	&(lvalues[5951]),0},
{"brainpoolP320t1","brainpoolP320t1",NID_brainpoolP320t1,9,
	&(lvalues[5960]),0},
{"brainpoolP384r1","brainpoolP384r1",NID_brainpoolP384r1,9,
	&(lvalues[5969]),0},
{"brainpoolP384t1","brainpoolP384t1",NID_brainpoolP384t1,9,
	&(lvalues[5978]),0},
{"brainpoolP512r1","brainpoolP512r1",NID_brainpoolP512r1,9,
	&(lvalues[5987]),0},
{"brainpoolP512t1","brainpoolP512t1",NID_brainpoolP512t1,9,
	&(lvalues[5996]),0},
{"gost89-ecb","gost89-ecb",NID_gost89_ecb,0,NULL,0},
{"gost89-cbc","gost89-cbc",NID_gost89_cbc,0,NULL,0},
{"tc26","tc26",NID_tc26,5,&(lvalues[6005]),0},
{"streebog256","GOST R 34.11-2012 (256 bit)",
	NID_id_tc26_gost3411_2012_256,8,&(lvalues[6010]),0},
{"streebog512","GOST R 34-11-2012 (512 bit)",
	NID_id_tc26_gost3411_2012_512,8,&(lvalues[6018]),0},
{"id-tc26-gost-3410-2012-512-paramSetA",
	"id-tc26-gost-3410-2012-512-paramSetA",
	NID_id_tc26_gost_3410_2012_512_paramSetA,9,&(lvalues[6026]),0},
{"id-tc26-gost-3410-2012-512-paramSetB",
	"id-tc26-gost-3410-2012-512-paramSetB",
	NID_id_tc26_gost_3410_2012_512_paramSetB,9,&(lvalues[6035]),0},
{"id-tc26-gost-28147-param-Z","id-tc26-gost-28147-param-Z",
	NID_id_tc26_gost_28147_param_Z,9,&(lvalues[6044]),0},
{"id-tc26-gost3410-2012-256","GOST R 34.10-2012 (256 bit)",
	NID_id_tc26_gost3410_2012_256,8,&(lvalues[6053]),0},
{"id-tc26-gost3410-2012-512","GOST R 34.10-2012 (512 bit)",
	NID_id_tc26_gost3410_2012_512,8,&(lvalues[6061]),0},
{"id-tc26-signwithdigest-gost3410-2012-256",
	"GOST R 34.11-2012 with GOST R 34.10-2012 (256 bit)",
	NID_id_tc26_signwithdigest_gost3410_2012_256,8,&(lvalues[6069]),0},
{"id-tc26-signwithdigest-gost3410-2012-512",
	"GOST R 34.11-2012 with GOST R 34.10-2012 (512 bit)",
	NID_id_tc26_signwithdigest_gost3410_2012_512,8,&(lvalues[6077]),0},
{"DES-CFB","des-cfb",NID_des_cfb64,5,&(lvalues[6085]),0},
{"DES-CFB1","des-cfb1",NID_des_cfb1,0,NULL,0},
{"DES-CFB8","des-cfb8",NID_des_cfb8,0,NULL,0},
};

static const unsigned int sn_objs[NUM_SN]={
364,	/* "AD_DVCS" */
419,	/* "AES-128-CBC" */
916,	/* "AES-128-CBC-HMAC-SHA1" */
421,	/* "AES-128-CFB" */
650,	/* "AES-128-CFB1" */
653,	/* "AES-128-CFB8" */
904,	/* "AES-128-CTR" */
418,	/* "AES-128-ECB" */
420,	/* "AES-128-OFB" */
913,	/* "AES-128-XTS" */
423,	/* "AES-192-CBC" */
917,	/* "AES-192-CBC-HMAC-SHA1" */
425,	/* "AES-192-CFB" */
651,	/* "AES-192-CFB1" */
654,	/* "AES-192-CFB8" */
905,	/* "AES-192-CTR" */
422,	/* "AES-192-ECB" */
424,	/* "AES-192-OFB" */
427,	/* "AES-256-CBC" */
918,	/* "AES-256-CBC-HMAC-SHA1" */
429,	/* "AES-256-CFB" */
652,	/* "AES-256-CFB1" */
655,	/* "AES-256-CFB8" */
906,	/* "AES-256-CTR" */
426,	/* "AES-256-ECB" */
428,	/* "AES-256-OFB" */
914,	/* "AES-256-XTS" */
91,	/* "BF-CBC" */
93,	/* "BF-CFB" */
92,	/* "BF-ECB" */
94,	/* "BF-OFB" */
14,	/* "C" */
751,	/* "CAMELLIA-128-CBC" */
757,	/* "CAMELLIA-128-CFB" */
760,	/* "CAMELLIA-128-CFB1" */
763,	/* "CAMELLIA-128-CFB8" */
754,	/* "CAMELLIA-128-ECB" */
766,	/* "CAMELLIA-128-OFB" */
752,	/* "CAMELLIA-192-CBC" */
758,	/* "CAMELLIA-192-CFB" */
761,	/* "CAMELLIA-192-CFB1" */
764,	/* "CAMELLIA-192-CFB8" */
755,	/* "CAMELLIA-192-ECB" */
767,	/* "CAMELLIA-192-OFB" */
753,	/* "CAMELLIA-256-CBC" */
759,	/* "CAMELLIA-256-CFB" */
762,	/* "CAMELLIA-256-CFB1" */
765,	/* "CAMELLIA-256-CFB8" */
756,	/* "CAMELLIA-256-ECB" */
768,	/* "CAMELLIA-256-OFB" */
108,	/* "CAST5-CBC" */
110,	/* "CAST5-CFB" */
109,	/* "CAST5-ECB" */
111,	/* "CAST5-OFB" */
894,	/* "CMAC" */
13,	/* "CN" */
141,	/* "CRLReason" */
417,	/* "CSPName" */
920,	/* "ChaCha" */
367,	/* "CrlID" */
391,	/* "DC" */
31,	/* "DES-CBC" */
643,	/* "DES-CDMF" */
949,	/* "DES-CFB" */
950,	/* "DES-CFB1" */
951,	/* "DES-CFB8" */
29,	/* "DES-ECB" */
32,	/* "DES-EDE" */
43,	/* "DES-EDE-CBC" */
60,	/* "DES-EDE-CFB" */
62,	/* "DES-EDE-OFB" */
33,	/* "DES-EDE3" */
44,	/* "DES-EDE3-CBC" */
61,	/* "DES-EDE3-CFB" */
658,	/* "DES-EDE3-CFB1" */
659,	/* "DES-EDE3-CFB8" */
63,	/* "DES-EDE3-OFB" */
45,	/* "DES-OFB" */
80,	/* "DESX-CBC" */
380,	/* "DOD" */
116,	/* "DSA" */
66,	/* "DSA-SHA" */
113,	/* "DSA-SHA1" */
70,	/* "DSA-SHA1-old" */
67,	/* "DSA-old" */
297,	/* "DVCS" */
99,	/* "GN" */
855,	/* "HMAC" */
780,	/* "HMAC-MD5" */
781,	/* "HMAC-SHA1" */
381,	/* "IANA" */
34,	/* "IDEA-CBC" */
35,	/* "IDEA-CFB" */
36,	/* "IDEA-ECB" */
46,	/* "IDEA-OFB" */
181,	/* "ISO" */
183,	/* "ISO-US" */
645,	/* "ITU-T" */
646,	/* "JOINT-ISO-ITU-T" */
15,	/* "L" */
856,	/* "LocalKeySet" */
 4,	/* "MD5" */
114,	/* "MD5-SHA1" */
911,	/* "MGF1" */
388,	/* "Mail" */
393,	/* "NULL" */
404,	/* "NULL" */
57,	/* "Netscape" */
366,	/* "Nonce" */
17,	/* "O" */
178,	/* "OCSP" */
180,	/* "OCSPSigning" */
379,	/* "ORG" */
18,	/* "OU" */
749,	/* "Oakley-EC2N-3" */
750,	/* "Oakley-EC2N-4" */
10,	/* "PBE-MD5-DES" */
169,	/* "PBE-MD5-RC2-64" */
147,	/* "PBE-SHA1-2DES" */
146,	/* "PBE-SHA1-3DES" */
170,	/* "PBE-SHA1-DES" */
148,	/* "PBE-SHA1-RC2-128" */
149,	/* "PBE-SHA1-RC2-40" */
68,	/* "PBE-SHA1-RC2-64" */
144,	/* "PBE-SHA1-RC4-128" */
145,	/* "PBE-SHA1-RC4-40" */
161,	/* "PBES2" */
69,	/* "PBKDF2" */
162,	/* "PBMAC1" */
127,	/* "PKIX" */
98,	/* "RC2-40-CBC" */
166,	/* "RC2-64-CBC" */
37,	/* "RC2-CBC" */
39,	/* "RC2-CFB" */
38,	/* "RC2-ECB" */
40,	/* "RC2-OFB" */
 5,	/* "RC4" */
97,	/* "RC4-40" */
915,	/* "RC4-HMAC-MD5" */
120,	/* "RC5-CBC" */
122,	/* "RC5-CFB" */
121,	/* "RC5-ECB" */
123,	/* "RC5-OFB" */
117,	/* "RIPEMD160" */
124,	/* "RLE" */
19,	/* "RSA" */
 8,	/* "RSA-MD5" */
104,	/* "RSA-NP-MD5" */
119,	/* "RSA-RIPEMD160" */
42,	/* "RSA-SHA" */
65,	/* "RSA-SHA1" */
115,	/* "RSA-SHA1-2" */
671,	/* "RSA-SHA224" */
668,	/* "RSA-SHA256" */
669,	/* "RSA-SHA384" */
670,	/* "RSA-SHA512" */
919,	/* "RSAES-OAEP" */
912,	/* "RSASSA-PSS" */
41,	/* "SHA" */
64,	/* "SHA1" */
675,	/* "SHA224" */
672,	/* "SHA256" */
673,	/* "SHA384" */
674,	/* "SHA512" */
188,	/* "SMIME" */
167,	/* "SMIME-CAPS" */
100,	/* "SN" */
16,	/* "ST" */
143,	/* "SXNetID" */
458,	/* "UID" */
 0,	/* "UNDEF" */
11,	/* "X500" */
378,	/* "X500algorithms" */
12,	/* "X509" */
184,	/* "X9-57" */
185,	/* "X9cm" */
125,	/* "ZLIB" */
478,	/* "aRecord" */
289,	/* "aaControls" */
287,	/* "ac-auditEntity" */
397,	/* "ac-proxying" */
288,	/* "ac-targeting" */
368,	/* "acceptableResponses" */
446,	/* "account" */
363,	/* "ad_timestamping" */
376,	/* "algorithm" */
405,	/* "ansi-X9-62" */
910,	/* "anyExtendedKeyUsage" */
746,	/* "anyPolicy" */
370,	/* "archiveCutoff" */
484,	/* "associatedDomain" */
485,	/* "associatedName" */
501,	/* "audio" */
177,	/* "authorityInfoAccess" */
90,	/* "authorityKeyIdentifier" */
882,	/* "authorityRevocationList" */
87,	/* "basicConstraints" */
365,	/* "basicOCSPResponse" */
285,	/* "biometricInfo" */
922,	/* "brainpool" */
923,	/* "brainpoolP160r1" */
924,	/* "brainpoolP160t1" */
925,	/* "brainpoolP192r1" */
926,	/* "brainpoolP192t1" */
927,	/* "brainpoolP224r1" */
928,	/* "brainpoolP224t1" */
929,	/* "brainpoolP256r1" */
930,	/* "brainpoolP256t1" */
931,	/* "brainpoolP320r1" */
932,	/* "brainpoolP320t1" */
933,	/* "brainpoolP384r1" */
934,	/* "brainpoolP384t1" */
935,	/* "brainpoolP512r1" */
936,	/* "brainpoolP512t1" */
494,	/* "buildingName" */
860,	/* "businessCategory" */
691,	/* "c2onb191v4" */
692,	/* "c2onb191v5" */
697,	/* "c2onb239v4" */
698,	/* "c2onb239v5" */
684,	/* "c2pnb163v1" */
685,	/* "c2pnb163v2" */
686,	/* "c2pnb163v3" */
687,	/* "c2pnb176v1" */
693,	/* "c2pnb208w1" */
699,	/* "c2pnb272w1" */
700,	/* "c2pnb304w1" */
702,	/* "c2pnb368w1" */
688,	/* "c2tnb191v1" */
689,	/* "c2tnb191v2" */
690,	/* "c2tnb191v3" */
694,	/* "c2tnb239v1" */
695,	/* "c2tnb239v2" */
696,	/* "c2tnb239v3" */
701,	/* "c2tnb359v1" */
703,	/* "c2tnb431r1" */
881,	/* "cACertificate" */
483,	/* "cNAMERecord" */
179,	/* "caIssuers" */
785,	/* "caRepository" */
443,	/* "caseIgnoreIA5StringSyntax" */
152,	/* "certBag" */
677,	/* "certicom-arc" */
771,	/* "certificateIssuer" */
89,	/* "certificatePolicies" */
883,	/* "certificateRevocationList" */
54,	/* "challengePassword" */
407,	/* "characteristic-two-field" */
395,	/* "clearance" */
130,	/* "clientAuth" */
131,	/* "codeSigning" */
50,	/* "contentType" */
53,	/* "countersignature" */
153,	/* "crlBag" */
103,	/* "crlDistributionPoints" */
88,	/* "crlNumber" */
884,	/* "crossCertificatePair" */
806,	/* "cryptocom" */
805,	/* "cryptopro" */
500,	/* "dITRedirect" */
451,	/* "dNSDomain" */
495,	/* "dSAQuality" */
434,	/* "data" */
390,	/* "dcobject" */
140,	/* "deltaCRL" */
891,	/* "deltaRevocationList" */
107,	/* "description" */
871,	/* "destinationIndicator" */
28,	/* "dhKeyAgreement" */
382,	/* "directory" */
887,	/* "distinguishedName" */
892,	/* "dmdName" */
174,	/* "dnQualifier" */
447,	/* "document" */
471,	/* "documentAuthor" */
468,	/* "documentIdentifier" */
472,	/* "documentLocation" */
502,	/* "documentPublisher" */
449,	/* "documentSeries" */
469,	/* "documentTitle" */
470,	/* "documentVersion" */
392,	/* "domain" */
452,	/* "domainRelatedObject" */
802,	/* "dsa_with_SHA224" */
803,	/* "dsa_with_SHA256" */
791,	/* "ecdsa-with-Recommended" */
416,	/* "ecdsa-with-SHA1" */
793,	/* "ecdsa-with-SHA224" */
794,	/* "ecdsa-with-SHA256" */
795,	/* "ecdsa-with-SHA384" */
796,	/* "ecdsa-with-SHA512" */
792,	/* "ecdsa-with-Specified" */
48,	/* "emailAddress" */
132,	/* "emailProtection" */
885,	/* "enhancedSearchGuide" */
389,	/* "enterprises" */
384,	/* "experimental" */
172,	/* "extReq" */
56,	/* "extendedCertificateAttributes" */
126,	/* "extendedKeyUsage" */
372,	/* "extendedStatus" */
867,	/* "facsimileTelephoneNumber" */
462,	/* "favouriteDrink" */
857,	/* "freshestCRL" */
453,	/* "friendlyCountry" */
490,	/* "friendlyCountryName" */
156,	/* "friendlyName" */
509,	/* "generationQualifier" */
815,	/* "gost-mac" */
811,	/* "gost2001" */
851,	/* "gost2001cc" */
813,	/* "gost89" */
938,	/* "gost89-cbc" */
814,	/* "gost89-cnt" */
937,	/* "gost89-ecb" */
812,	/* "gost94" */
850,	/* "gost94cc" */
797,	/* "hmacWithMD5" */
163,	/* "hmacWithSHA1" */
798,	/* "hmacWithSHA224" */
799,	/* "hmacWithSHA256" */
800,	/* "hmacWithSHA384" */
801,	/* "hmacWithSHA512" */
432,	/* "holdInstructionCallIssuer" */
430,	/* "holdInstructionCode" */
431,	/* "holdInstructionNone" */
433,	/* "holdInstructionReject" */
486,	/* "homePostalAddress" */
473,	/* "homeTelephoneNumber" */
466,	/* "host" */
889,	/* "houseIdentifier" */
442,	/* "iA5StringSyntax" */
783,	/* "id-DHBasedMac" */
824,	/* "id-Gost28147-89-CryptoPro-A-ParamSet" */
825,	/* "id-Gost28147-89-CryptoPro-B-ParamSet" */
826,	/* "id-Gost28147-89-CryptoPro-C-ParamSet" */
827,	/* "id-Gost28147-89-CryptoPro-D-ParamSet" */
819,	/* "id-Gost28147-89-CryptoPro-KeyMeshing" */
829,	/* "id-Gost28147-89-CryptoPro-Oscar-1-0-ParamSet" */
828,	/* "id-Gost28147-89-CryptoPro-Oscar-1-1-ParamSet" */
830,	/* "id-Gost28147-89-CryptoPro-RIC-1-ParamSet" */
820,	/* "id-Gost28147-89-None-KeyMeshing" */
823,	/* "id-Gost28147-89-TestParamSet" */
849,	/* "id-Gost28147-89-cc" */
840,	/* "id-GostR3410-2001-CryptoPro-A-ParamSet" */
841,	/* "id-GostR3410-2001-CryptoPro-B-ParamSet" */
842,	/* "id-GostR3410-2001-CryptoPro-C-ParamSet" */
843,	/* "id-GostR3410-2001-CryptoPro-XchA-ParamSet" */
844,	/* "id-GostR3410-2001-CryptoPro-XchB-ParamSet" */
854,	/* "id-GostR3410-2001-ParamSet-cc" */
839,	/* "id-GostR3410-2001-TestParamSet" */
817,	/* "id-GostR3410-2001DH" */
832,	/* "id-GostR3410-94-CryptoPro-A-ParamSet" */
833,	/* "id-GostR3410-94-CryptoPro-B-ParamSet" */
834,	/* "id-GostR3410-94-CryptoPro-C-ParamSet" */
835,	/* "id-GostR3410-94-CryptoPro-D-ParamSet" */
836,	/* "id-GostR3410-94-CryptoPro-XchA-ParamSet" */
837,	/* "id-GostR3410-94-CryptoPro-XchB-ParamSet" */
838,	/* "id-GostR3410-94-CryptoPro-XchC-ParamSet" */
831,	/* "id-GostR3410-94-TestParamSet" */
845,	/* "id-GostR3410-94-a" */
846,	/* "id-GostR3410-94-aBis" */
847,	/* "id-GostR3410-94-b" */
848,	/* "id-GostR3410-94-bBis" */
818,	/* "id-GostR3410-94DH" */
822,	/* "id-GostR3411-94-CryptoProParamSet" */
821,	/* "id-GostR3411-94-TestParamSet" */
807,	/* "id-GostR3411-94-with-GostR3410-2001" */
853,	/* "id-GostR3411-94-with-GostR3410-2001-cc" */
808,	/* "id-GostR3411-94-with-GostR3410-94" */
852,	/* "id-GostR3411-94-with-GostR3410-94-cc" */
810,	/* "id-HMACGostR3411-94" */
782,	/* "id-PasswordBasedMAC" */
266,	/* "id-aca" */
355,	/* "id-aca-accessIdentity" */
354,	/* "id-aca-authenticationInfo" */
356,	/* "id-aca-chargingIdentity" */
399,	/* "id-aca-encAttrs" */
357,	/* "id-aca-group" */
358,	/* "id-aca-role" */
176,	/* "id-ad" */
896,	/* "id-aes128-CCM" */
895,	/* "id-aes128-GCM" */
788,	/* "id-aes128-wrap" */
897,	/* "id-aes128-wrap-pad" */
899,	/* "id-aes192-CCM" */
898,	/* "id-aes192-GCM" */
789,	/* "id-aes192-wrap" */
900,	/* "id-aes192-wrap-pad" */
902,	/* "id-aes256-CCM" */
901,	/* "id-aes256-GCM" */
790,	/* "id-aes256-wrap" */
903,	/* "id-aes256-wrap-pad" */
262,	/* "id-alg" */
893,	/* "id-alg-PWRI-KEK" */
323,	/* "id-alg-des40" */
326,	/* "id-alg-dh-pop" */
325,	/* "id-alg-dh-sig-hmac-sha1" */
324,	/* "id-alg-noSignature" */
907,	/* "id-camellia128-wrap" */
908,	/* "id-camellia192-wrap" */
909,	/* "id-camellia256-wrap" */
268,	/* "id-cct" */
361,	/* "id-cct-PKIData" */
362,	/* "id-cct-PKIResponse" */
360,	/* "id-cct-crs" */
81,	/* "id-ce" */
680,	/* "id-characteristic-two-basis" */
263,	/* "id-cmc" */
334,	/* "id-cmc-addExtensions" */
346,	/* "id-cmc-confirmCertAcceptance" */
330,	/* "id-cmc-dataReturn" */
336,	/* "id-cmc-decryptedPOP" */
335,	/* "id-cmc-encryptedPOP" */
339,	/* "id-cmc-getCRL" */
338,	/* "id-cmc-getCert" */
328,	/* "id-cmc-identification" */
329,	/* "id-cmc-identityProof" */
337,	/* "id-cmc-lraPOPWitness" */
344,	/* "id-cmc-popLinkRandom" */
345,	/* "id-cmc-popLinkWitness" */
343,	/* "id-cmc-queryPending" */
333,	/* "id-cmc-recipientNonce" */
341,	/* "id-cmc-regInfo" */
342,	/* "id-cmc-responseInfo" */
340,	/* "id-cmc-revokeRequest" */
332,	/* "id-cmc-senderNonce" */
327,	/* "id-cmc-statusInfo" */
331,	/* "id-cmc-transactionId" */
787,	/* "id-ct-asciiTextWithCRLF" */
408,	/* "id-ecPublicKey" */
508,	/* "id-hex-multipart-message" */
507,	/* "id-hex-partial-message" */
260,	/* "id-it" */
302,	/* "id-it-caKeyUpdateInfo" */
298,	/* "id-it-caProtEncCert" */
311,	/* "id-it-confirmWaitTime" */
303,	/* "id-it-currentCRL" */
300,	/* "id-it-encKeyPairTypes" */
310,	/* "id-it-implicitConfirm" */
308,	/* "id-it-keyPairParamRep" */
307,	/* "id-it-keyPairParamReq" */
312,	/* "id-it-origPKIMessage" */
301,	/* "id-it-preferredSymmAlg" */
309,	/* "id-it-revPassphrase" */
299,	/* "id-it-signKeyPairTypes" */
305,	/* "id-it-subscriptionRequest" */
306,	/* "id-it-subscriptionResponse" */
784,	/* "id-it-suppLangTags" */
304,	/* "id-it-unsupportedOIDs" */
128,	/* "id-kp" */
280,	/* "id-mod-attribute-cert" */
274,	/* "id-mod-cmc" */
277,	/* "id-mod-cmp" */
284,	/* "id-mod-cmp2000" */
273,	/* "id-mod-crmf" */
283,	/* "id-mod-dvcs" */
275,	/* "id-mod-kea-profile-88" */
276,	/* "id-mod-kea-profile-93" */
282,	/* "id-mod-ocsp" */
278,	/* "id-mod-qualified-cert-88" */
279,	/* "id-mod-qualified-cert-93" */
281,	/* "id-mod-timestamp-protocol" */
264,	/* "id-on" */
858,	/* "id-on-permanentIdentifier" */
347,	/* "id-on-personalData" */
265,	/* "id-pda" */
352,	/* "id-pda-countryOfCitizenship" */
353,	/* "id-pda-countryOfResidence" */
348,	/* "id-pda-dateOfBirth" */
351,	/* "id-pda-gender" */
349,	/* "id-pda-placeOfBirth" */
175,	/* "id-pe" */
261,	/* "id-pkip" */
258,	/* "id-pkix-mod" */
269,	/* "id-pkix1-explicit-88" */
271,	/* "id-pkix1-explicit-93" */
270,	/* "id-pkix1-implicit-88" */
272,	/* "id-pkix1-implicit-93" */
662,	/* "id-ppl" */
664,	/* "id-ppl-anyLanguage" */
667,	/* "id-ppl-independent" */
665,	/* "id-ppl-inheritAll" */
267,	/* "id-qcs" */
359,	/* "id-qcs-pkixQCSyntax-v1" */
259,	/* "id-qt" */
164,	/* "id-qt-cps" */
165,	/* "id-qt-unotice" */
313,	/* "id-regCtrl" */
316,	/* "id-regCtrl-authenticator" */
319,	/* "id-regCtrl-oldCertID" */
318,	/* "id-regCtrl-pkiArchiveOptions" */
317,	/* "id-regCtrl-pkiPublicationInfo" */
320,	/* "id-regCtrl-protocolEncrKey" */
315,	/* "id-regCtrl-regToken" */
314,	/* "id-regInfo" */
322,	/* "id-regInfo-certReq" */
321,	/* "id-regInfo-utf8Pairs" */
512,	/* "id-set" */
191,	/* "id-smime-aa" */
215,	/* "id-smime-aa-contentHint" */
218,	/* "id-smime-aa-contentIdentifier" */
221,	/* "id-smime-aa-contentReference" */
240,	/* "id-smime-aa-dvcs-dvc" */
217,	/* "id-smime-aa-encapContentType" */
222,	/* "id-smime-aa-encrypKeyPref" */
220,	/* "id-smime-aa-equivalentLabels" */
232,	/* "id-smime-aa-ets-CertificateRefs" */
233,	/* "id-smime-aa-ets-RevocationRefs" */
238,	/* "id-smime-aa-ets-archiveTimeStamp" */
237,	/* "id-smime-aa-ets-certCRLTimestamp" */
234,	/* "id-smime-aa-ets-certValues" */
227,	/* "id-smime-aa-ets-commitmentType" */
231,	/* "id-smime-aa-ets-contentTimestamp" */
236,	/* "id-smime-aa-ets-escTimeStamp" */
230,	/* "id-smime-aa-ets-otherSigCert" */
235,	/* "id-smime-aa-ets-revocationValues" */
226,	/* "id-smime-aa-ets-sigPolicyId" */
229,	/* "id-smime-aa-ets-signerAttr" */
228,	/* "id-smime-aa-ets-signerLocation" */
219,	/* "id-smime-aa-macValue" */
214,	/* "id-smime-aa-mlExpandHistory" */
216,	/* "id-smime-aa-msgSigDigest" */
212,	/* "id-smime-aa-receiptRequest" */
213,	/* "id-smime-aa-securityLabel" */
239,	/* "id-smime-aa-signatureType" */
223,	/* "id-smime-aa-signingCertificate" */
224,	/* "id-smime-aa-smimeEncryptCerts" */
225,	/* "id-smime-aa-timeStampToken" */
192,	/* "id-smime-alg" */
243,	/* "id-smime-alg-3DESwrap" */
246,	/* "id-smime-alg-CMS3DESwrap" */
247,	/* "id-smime-alg-CMSRC2wrap" */
245,	/* "id-smime-alg-ESDH" */
241,	/* "id-smime-alg-ESDHwith3DES" */
242,	/* "id-smime-alg-ESDHwithRC2" */
244,	/* "id-smime-alg-RC2wrap" */
193,	/* "id-smime-cd" */
248,	/* "id-smime-cd-ldap" */
190,	/* "id-smime-ct" */
210,	/* "id-smime-ct-DVCSRequestData" */
211,	/* "id-smime-ct-DVCSResponseData" */
208,	/* "id-smime-ct-TDTInfo" */
207,	/* "id-smime-ct-TSTInfo" */
205,	/* "id-smime-ct-authData" */
786,	/* "id-smime-ct-compressedData" */
209,	/* "id-smime-ct-contentInfo" */
206,	/* "id-smime-ct-publishCert" */
204,	/* "id-smime-ct-receipt" */
195,	/* "id-smime-cti" */
255,	/* "id-smime-cti-ets-proofOfApproval" */
256,	/* "id-smime-cti-ets-proofOfCreation" */
253,	/* "id-smime-cti-ets-proofOfDelivery" */
251,	/* "id-smime-cti-ets-proofOfOrigin" */
252,	/* "id-smime-cti-ets-proofOfReceipt" */
254,	/* "id-smime-cti-ets-proofOfSender" */
189,	/* "id-smime-mod" */
196,	/* "id-smime-mod-cms" */
197,	/* "id-smime-mod-ess" */
202,	/* "id-smime-mod-ets-eSigPolicy-88" */
203,	/* "id-smime-mod-ets-eSigPolicy-97" */
200,	/* "id-smime-mod-ets-eSignature-88" */
201,	/* "id-smime-mod-ets-eSignature-97" */
199,	/* "id-smime-mod-msg-v3" */
198,	/* "id-smime-mod-oid" */
194,	/* "id-smime-spq" */
250,	/* "id-smime-spq-ets-sqt-unotice" */
249,	/* "id-smime-spq-ets-sqt-uri" */
944,	/* "id-tc26-gost-28147-param-Z" */
942,	/* "id-tc26-gost-3410-2012-512-paramSetA" */
943,	/* "id-tc26-gost-3410-2012-512-paramSetB" */
945,	/* "id-tc26-gost3410-2012-256" */
946,	/* "id-tc26-gost3410-2012-512" */
947,	/* "id-tc26-signwithdigest-gost3410-2012-256" */
948,	/* "id-tc26-signwithdigest-gost3410-2012-512" */
676,	/* "identified-organization" */
461,	/* "info" */
748,	/* "inhibitAnyPolicy" */
101,	/* "initials" */
647,	/* "international-organizations" */
869,	/* "internationaliSDNNumber" */
142,	/* "invalidityDate" */
294,	/* "ipsecEndSystem" */
295,	/* "ipsecTunnel" */
296,	/* "ipsecUser" */
86,	/* "issuerAltName" */
770,	/* "issuingDistributionPoint" */
492,	/* "janetMailbox" */
150,	/* "keyBag" */
83,	/* "keyUsage" */
477,	/* "lastModifiedBy" */
476,	/* "lastModifiedTime" */
157,	/* "localKeyID" */
480,	/* "mXRecord" */
460,	/* "mail" */
493,	/* "mailPreferenceOption" */
467,	/* "manager" */
809,	/* "md_gost94" */
875,	/* "member" */
182,	/* "member-body" */
51,	/* "messageDigest" */
383,	/* "mgmt" */
504,	/* "mime-mhs" */
506,	/* "mime-mhs-bodies" */
505,	/* "mime-mhs-headings" */
488,	/* "mobileTelephoneNumber" */
136,	/* "msCTLSign" */
135,	/* "msCodeCom" */
134,	/* "msCodeInd" */
138,	/* "msEFS" */
171,	/* "msExtReq" */
137,	/* "msSGC" */
648,	/* "msSmartcardLogin" */
649,	/* "msUPN" */
481,	/* "nSRecord" */
173,	/* "name" */
666,	/* "nameConstraints" */
369,	/* "noCheck" */
403,	/* "noRevAvail" */
72,	/* "nsBaseUrl" */
76,	/* "nsCaPolicyUrl" */
74,	/* "nsCaRevocationUrl" */
58,	/* "nsCertExt" */
79,	/* "nsCertSequence" */
71,	/* "nsCertType" */
78,	/* "nsComment" */
59,	/* "nsDataType" */
75,	/* "nsRenewalUrl" */
73,	/* "nsRevocationUrl" */
139,	/* "nsSGC" */
77,	/* "nsSslServerName" */
681,	/* "onBasis" */
491,	/* "organizationalStatus" */
475,	/* "otherMailbox" */
876,	/* "owner" */
489,	/* "pagerTelephoneNumber" */
374,	/* "path" */
112,	/* "pbeWithMD5AndCast5CBC" */
499,	/* "personalSignature" */
487,	/* "personalTitle" */
464,	/* "photo" */
863,	/* "physicalDeliveryOfficeName" */
437,	/* "pilot" */
439,	/* "pilotAttributeSyntax" */
438,	/* "pilotAttributeType" */
479,	/* "pilotAttributeType27" */
456,	/* "pilotDSA" */
441,	/* "pilotGroups" */
444,	/* "pilotObject" */
440,	/* "pilotObjectClass" */
455,	/* "pilotOrganization" */
445,	/* "pilotPerson" */
 2,	/* "pkcs" */
186,	/* "pkcs1" */
27,	/* "pkcs3" */
187,	/* "pkcs5" */
20,	/* "pkcs7" */
21,	/* "pkcs7-data" */
25,	/* "pkcs7-digestData" */
26,	/* "pkcs7-encryptedData" */
23,	/* "pkcs7-envelopedData" */
24,	/* "pkcs7-signedAndEnvelopedData" */
22,	/* "pkcs7-signedData" */
151,	/* "pkcs8ShroudedKeyBag" */
47,	/* "pkcs9" */
401,	/* "policyConstraints" */
747,	/* "policyMappings" */
862,	/* "postOfficeBox" */
861,	/* "postalAddress" */
661,	/* "postalCode" */
683,	/* "ppBasis" */
872,	/* "preferredDeliveryMethod" */
873,	/* "presentationAddress" */
816,	/* "prf-gostr3411-94" */
406,	/* "prime-field" */
409,	/* "prime192v1" */
410,	/* "prime192v2" */
411,	/* "prime192v3" */
412,	/* "prime239v1" */
413,	/* "prime239v2" */
414,	/* "prime239v3" */
415,	/* "prime256v1" */
385,	/* "private" */
84,	/* "privateKeyUsagePeriod" */
886,	/* "protocolInformation" */
663,	/* "proxyCertInfo" */
510,	/* "pseudonym" */
435,	/* "pss" */
286,	/* "qcStatements" */
457,	/* "qualityLabelledData" */
450,	/* "rFC822localPart" */
870,	/* "registeredAddress" */
400,	/* "role" */
877,	/* "roleOccupant" */
448,	/* "room" */
463,	/* "roomNumber" */
 6,	/* "rsaEncryption" */
644,	/* "rsaOAEPEncryptionSET" */
377,	/* "rsaSignature" */
 1,	/* "rsadsi" */
482,	/* "sOARecord" */
155,	/* "safeContentsBag" */
291,	/* "sbgp-autonomousSysNum" */
290,	/* "sbgp-ipAddrBlock" */
292,	/* "sbgp-routerIdentifier" */
159,	/* "sdsiCertificate" */
859,	/* "searchGuide" */
704,	/* "secp112r1" */
705,	/* "secp112r2" */
706,	/* "secp128r1" */
707,	/* "secp128r2" */
708,	/* "secp160k1" */
709,	/* "secp160r1" */
710,	/* "secp160r2" */
711,	/* "secp192k1" */
712,	/* "secp224k1" */
713,	/* "secp224r1" */
714,	/* "secp256k1" */
715,	/* "secp384r1" */
716,	/* "secp521r1" */
154,	/* "secretBag" */
474,	/* "secretary" */
717,	/* "sect113r1" */
718,	/* "sect113r2" */
719,	/* "sect131r1" */
720,	/* "sect131r2" */
721,	/* "sect163k1" */
722,	/* "sect163r1" */
723,	/* "sect163r2" */
724,	/* "sect193r1" */
725,	/* "sect193r2" */
726,	/* "sect233k1" */
727,	/* "sect233r1" */
728,	/* "sect239k1" */
729,	/* "sect283k1" */
730,	/* "sect283r1" */
731,	/* "sect409k1" */
732,	/* "sect409r1" */
733,	/* "sect571k1" */
734,	/* "sect571r1" */
386,	/* "security" */
878,	/* "seeAlso" */
394,	/* "selected-attribute-types" */
105,	/* "serialNumber" */
129,	/* "serverAuth" */
371,	/* "serviceLocator" */
625,	/* "set-addPolicy" */
515,	/* "set-attr" */
518,	/* "set-brand" */
638,	/* "set-brand-AmericanExpress" */
637,	/* "set-brand-Diners" */
636,	/* "set-brand-IATA-ATA" */
639,	/* "set-brand-JCB" */
641,	/* "set-brand-MasterCard" */
642,	/* "set-brand-Novus" */
640,	/* "set-brand-Visa" */
517,	/* "set-certExt" */
513,	/* "set-ctype" */
514,	/* "set-msgExt" */
516,	/* "set-policy" */
607,	/* "set-policy-root" */
624,	/* "set-rootKeyThumb" */
620,	/* "setAttr-Cert" */
631,	/* "setAttr-GenCryptgrm" */
623,	/* "setAttr-IssCap" */
628,	/* "setAttr-IssCap-CVM" */
630,	/* "setAttr-IssCap-Sig" */
629,	/* "setAttr-IssCap-T2" */
621,	/* "setAttr-PGWYcap" */
635,	/* "setAttr-SecDevSig" */
632,	/* "setAttr-T2Enc" */
633,	/* "setAttr-T2cleartxt" */
634,	/* "setAttr-TokICCsig" */
627,	/* "setAttr-Token-B0Prime" */
626,	/* "setAttr-Token-EMV" */
622,	/* "setAttr-TokenType" */
619,	/* "setCext-IssuerCapabilities" */
615,	/* "setCext-PGWYcapabilities" */
616,	/* "setCext-TokenIdentifier" */
618,	/* "setCext-TokenType" */
617,	/* "setCext-Track2Data" */
611,	/* "setCext-cCertRequired" */
609,	/* "setCext-certType" */
608,	/* "setCext-hashedRoot" */
610,	/* "setCext-merchData" */
613,	/* "setCext-setExt" */
614,	/* "setCext-setQualf" */
612,	/* "setCext-tunneling" */
540,	/* "setct-AcqCardCodeMsg" */
576,	/* "setct-AcqCardCodeMsgTBE" */
570,	/* "setct-AuthReqTBE" */
534,	/* "setct-AuthReqTBS" */
527,	/* "setct-AuthResBaggage" */
571,	/* "setct-AuthResTBE" */
572,	/* "setct-AuthResTBEX" */
535,	/* "setct-AuthResTBS" */
536,	/* "setct-AuthResTBSX" */
528,	/* "setct-AuthRevReqBaggage" */
577,	/* "setct-AuthRevReqTBE" */
541,	/* "setct-AuthRevReqTBS" */
529,	/* "setct-AuthRevResBaggage" */
542,	/* "setct-AuthRevResData" */
578,	/* "setct-AuthRevResTBE" */
579,	/* "setct-AuthRevResTBEB" */
543,	/* "setct-AuthRevResTBS" */
573,	/* "setct-AuthTokenTBE" */
537,	/* "setct-AuthTokenTBS" */
600,	/* "setct-BCIDistributionTBS" */
558,	/* "setct-BatchAdminReqData" */
592,	/* "setct-BatchAdminReqTBE" */
559,	/* "setct-BatchAdminResData" */
593,	/* "setct-BatchAdminResTBE" */
599,	/* "setct-CRLNotificationResTBS" */
598,	/* "setct-CRLNotificationTBS" */
580,	/* "setct-CapReqTBE" */
581,	/* "setct-CapReqTBEX" */
544,	/* "setct-CapReqTBS" */
545,	/* "setct-CapReqTBSX" */
546,	/* "setct-CapResData" */
582,	/* "setct-CapResTBE" */
583,	/* "setct-CapRevReqTBE" */
584,	/* "setct-CapRevReqTBEX" */
547,	/* "setct-CapRevReqTBS" */
548,	/* "setct-CapRevReqTBSX" */
549,	/* "setct-CapRevResData" */
585,	/* "setct-CapRevResTBE" */
538,	/* "setct-CapTokenData" */
530,	/* "setct-CapTokenSeq" */
574,	/* "setct-CapTokenTBE" */
575,	/* "setct-CapTokenTBEX" */
539,	/* "setct-CapTokenTBS" */
560,	/* "setct-CardCInitResTBS" */
566,	/* "setct-CertInqReqTBS" */
563,	/* "setct-CertReqData" */
595,	/* "setct-CertReqTBE" */
596,	/* "setct-CertReqTBEX" */
564,	/* "setct-CertReqTBS" */
565,	/* "setct-CertResData" */
597,	/* "setct-CertResTBE" */
586,	/* "setct-CredReqTBE" */
587,	/* "setct-CredReqTBEX" */
550,	/* "setct-CredReqTBS" */
551,	/* "setct-CredReqTBSX" */
552,	/* "setct-CredResData" */
588,	/* "setct-CredResTBE" */
589,	/* "setct-CredRevReqTBE" */
590,	/* "setct-CredRevReqTBEX" */
553,	/* "setct-CredRevReqTBS" */
554,	/* "setct-CredRevReqTBSX" */
555,	/* "setct-CredRevResData" */
591,	/* "setct-CredRevResTBE" */
567,	/* "setct-ErrorTBS" */
526,	/* "setct-HODInput" */
561,	/* "setct-MeAqCInitResTBS" */
522,	/* "setct-OIData" */
519,	/* "setct-PANData" */
521,	/* "setct-PANOnly" */
520,	/* "setct-PANToken" */
556,	/* "setct-PCertReqData" */
557,	/* "setct-PCertResTBS" */
523,	/* "setct-PI" */
532,	/* "setct-PI-TBS" */
524,	/* "setct-PIData" */
525,	/* "setct-PIDataUnsigned" */
568,	/* "setct-PIDualSignedTBE" */
569,	/* "setct-PIUnsignedTBE" */
531,	/* "setct-PInitResData" */
533,	/* "setct-PResData" */
594,	/* "setct-RegFormReqTBE" */
562,	/* "setct-RegFormResTBS" */
606,	/* "setext-cv" */
601,	/* "setext-genCrypt" */
602,	/* "setext-miAuth" */
604,	/* "setext-pinAny" */
603,	/* "setext-pinSecure" */
605,	/* "setext-track2" */
52,	/* "signingTime" */
454,	/* "simpleSecurityObject" */
496,	/* "singleLevelQuality" */
387,	/* "snmpv2" */
940,	/* "streebog256" */
941,	/* "streebog512" */
660,	/* "street" */
85,	/* "subjectAltName" */
769,	/* "subjectDirectoryAttributes" */
398,	/* "subjectInfoAccess" */
82,	/* "subjectKeyIdentifier" */
498,	/* "subtreeMaximumQuality" */
497,	/* "subtreeMinimumQuality" */
890,	/* "supportedAlgorithms" */
874,	/* "supportedApplicationContext" */
402,	/* "targetInformation" */
939,	/* "tc26" */
864,	/* "telephoneNumber" */
866,	/* "teletexTerminalIdentifier" */
921,	/* "teletrust" */
865,	/* "telexNumber" */
459,	/* "textEncodedORAddress" */
293,	/* "textNotice" */
133,	/* "timeStamping" */
106,	/* "title" */
682,	/* "tpBasis" */
375,	/* "trustRoot" */
436,	/* "ucl" */
888,	/* "uniqueMember" */
55,	/* "unstructuredAddress" */
49,	/* "unstructuredName" */
880,	/* "userCertificate" */
465,	/* "userClass" */
879,	/* "userPassword" */
373,	/* "valid" */
678,	/* "wap" */
679,	/* "wap-wsg" */
735,	/* "wap-wsg-idm-ecid-wtls1" */
743,	/* "wap-wsg-idm-ecid-wtls10" */
744,	/* "wap-wsg-idm-ecid-wtls11" */
745,	/* "wap-wsg-idm-ecid-wtls12" */
736,	/* "wap-wsg-idm-ecid-wtls3" */
737,	/* "wap-wsg-idm-ecid-wtls4" */
738,	/* "wap-wsg-idm-ecid-wtls5" */
739,	/* "wap-wsg-idm-ecid-wtls6" */
740,	/* "wap-wsg-idm-ecid-wtls7" */
741,	/* "wap-wsg-idm-ecid-wtls8" */
742,	/* "wap-wsg-idm-ecid-wtls9" */
804,	/* "whirlpool" */
868,	/* "x121Address" */
503,	/* "x500UniqueIdentifier" */
158,	/* "x509Certificate" */
160,	/* "x509Crl" */
};

static const unsigned int ln_objs[NUM_LN]={
363,	/* "AD Time Stamping" */
405,	/* "ANSI X9.62" */
368,	/* "Acceptable OCSP Responses" */
910,	/* "Any Extended Key Usage" */
664,	/* "Any language" */
177,	/* "Authority Information Access" */
365,	/* "Basic OCSP Response" */
285,	/* "Biometric Info" */
179,	/* "CA Issuers" */
785,	/* "CA Repository" */
131,	/* "Code Signing" */
783,	/* "Diffie-Hellman based MAC" */
382,	/* "Directory" */
392,	/* "Domain" */
132,	/* "E-mail Protection" */
389,	/* "Enterprises" */
384,	/* "Experimental" */
372,	/* "Extended OCSP Status" */
172,	/* "Extension Request" */
813,	/* "GOST 28147-89" */
849,	/* "GOST 28147-89 Cryptocom ParamSet" */
815,	/* "GOST 28147-89 MAC" */
851,	/* "GOST 34.10-2001 Cryptocom" */
850,	/* "GOST 34.10-94 Cryptocom" */
941,	/* "GOST R 34-11-2012 (512 bit)" */
811,	/* "GOST R 34.10-2001" */
817,	/* "GOST R 34.10-2001 DH" */
945,	/* "GOST R 34.10-2012 (256 bit)" */
946,	/* "GOST R 34.10-2012 (512 bit)" */
812,	/* "GOST R 34.10-94" */
818,	/* "GOST R 34.10-94 DH" */
940,	/* "GOST R 34.11-2012 (256 bit)" */
947,	/* "GOST R 34.11-2012 with GOST R 34.10-2012 (256 bit)" */
948,	/* "GOST R 34.11-2012 with GOST R 34.10-2012 (512 bit)" */
809,	/* "GOST R 34.11-94" */
816,	/* "GOST R 34.11-94 PRF" */
807,	/* "GOST R 34.11-94 with GOST R 34.10-2001" */
853,	/* "GOST R 34.11-94 with GOST R 34.10-2001 Cryptocom" */
808,	/* "GOST R 34.11-94 with GOST R 34.10-94" */
852,	/* "GOST R 34.11-94 with GOST R 34.10-94 Cryptocom" */
854,	/* "GOST R 3410-2001 Parameter Set Cryptocom" */
810,	/* "HMAC GOST 34.11-94" */
432,	/* "Hold Instruction Call Issuer" */
430,	/* "Hold Instruction Code" */
431,	/* "Hold Instruction None" */
433,	/* "Hold Instruction Reject" */
634,	/* "ICC or token signature" */
294,	/* "IPSec End System" */
295,	/* "IPSec Tunnel" */
296,	/* "IPSec User" */
182,	/* "ISO Member Body" */
183,	/* "ISO US Member Body" */
667,	/* "Independent" */
665,	/* "Inherit all" */
647,	/* "International Organizations" */
142,	/* "Invalidity Date" */
504,	/* "MIME MHS" */
388,	/* "Mail" */
383,	/* "Management" */
417,	/* "Microsoft CSP Name" */
135,	/* "Microsoft Commercial Code Signing" */
138,	/* "Microsoft Encrypted File System" */
171,	/* "Microsoft Extension Request" */
134,	/* "Microsoft Individual Code Signing" */
856,	/* "Microsoft Local Key set" */
137,	/* "Microsoft Server Gated Crypto" */
648,	/* "Microsoft Smartcardlogin" */
136,	/* "Microsoft Trust List Signing" */
649,	/* "Microsoft Universal Principal Name" */
393,	/* "NULL" */
404,	/* "NULL" */
72,	/* "Netscape Base Url" */
76,	/* "Netscape CA Policy Url" */
74,	/* "Netscape CA Revocation Url" */
71,	/* "Netscape Cert Type" */
58,	/* "Netscape Certificate Extension" */
79,	/* "Netscape Certificate Sequence" */
78,	/* "Netscape Comment" */
57,	/* "Netscape Communications Corp." */
59,	/* "Netscape Data Type" */
75,	/* "Netscape Renewal Url" */
73,	/* "Netscape Revocation Url" */
77,	/* "Netscape SSL Server Name" */
139,	/* "Netscape Server Gated Crypto" */
178,	/* "OCSP" */
370,	/* "OCSP Archive Cutoff" */
367,	/* "OCSP CRL ID" */
369,	/* "OCSP No Check" */
366,	/* "OCSP Nonce" */
371,	/* "OCSP Service Locator" */
180,	/* "OCSP Signing" */
161,	/* "PBES2" */
69,	/* "PBKDF2" */
162,	/* "PBMAC1" */
127,	/* "PKIX" */
858,	/* "Permanent Identifier" */
164,	/* "Policy Qualifier CPS" */
165,	/* "Policy Qualifier User Notice" */
385,	/* "Private" */
663,	/* "Proxy Certificate Information" */
 1,	/* "RSA Data Security, Inc." */
 2,	/* "RSA Data Security, Inc. PKCS" */
188,	/* "S/MIME" */
167,	/* "S/MIME Capabilities" */
387,	/* "SNMPv2" */
512,	/* "Secure Electronic Transactions" */
386,	/* "Security" */
394,	/* "Selected Attribute Types" */
143,	/* "Strong Extranet ID" */
398,	/* "Subject Information Access" */
130,	/* "TLS Web Client Authentication" */
129,	/* "TLS Web Server Authentication" */
133,	/* "Time Stamping" */
375,	/* "Trust Root" */
12,	/* "X509" */
402,	/* "X509v3 AC Targeting" */
746,	/* "X509v3 Any Policy" */
90,	/* "X509v3 Authority Key Identifier" */
87,	/* "X509v3 Basic Constraints" */
103,	/* "X509v3 CRL Distribution Points" */
88,	/* "X509v3 CRL Number" */
141,	/* "X509v3 CRL Reason Code" */
771,	/* "X509v3 Certificate Issuer" */
89,	/* "X509v3 Certificate Policies" */
140,	/* "X509v3 Delta CRL Indicator" */
126,	/* "X509v3 Extended Key Usage" */
857,	/* "X509v3 Freshest CRL" */
748,	/* "X509v3 Inhibit Any Policy" */
86,	/* "X509v3 Issuer Alternative Name" */
770,	/* "X509v3 Issuing Distrubution Point" */
83,	/* "X509v3 Key Usage" */
666,	/* "X509v3 Name Constraints" */
403,	/* "X509v3 No Revocation Available" */
401,	/* "X509v3 Policy Constraints" */
747,	/* "X509v3 Policy Mappings" */
84,	/* "X509v3 Private Key Usage Period" */
85,	/* "X509v3 Subject Alternative Name" */
769,	/* "X509v3 Subject Directory Attributes" */
82,	/* "X509v3 Subject Key Identifier" */
184,	/* "X9.57" */
185,	/* "X9.57 CM ?" */
478,	/* "aRecord" */
289,	/* "aaControls" */
287,	/* "ac-auditEntity" */
397,	/* "ac-proxying" */
288,	/* "ac-targeting" */
446,	/* "account" */
364,	/* "ad dvcs" */
606,	/* "additional verification" */
419,	/* "aes-128-cbc" */
916,	/* "aes-128-cbc-hmac-sha1" */
896,	/* "aes-128-ccm" */
421,	/* "aes-128-cfb" */
650,	/* "aes-128-cfb1" */
653,	/* "aes-128-cfb8" */
904,	/* "aes-128-ctr" */
418,	/* "aes-128-ecb" */
895,	/* "aes-128-gcm" */
420,	/* "aes-128-ofb" */
913,	/* "aes-128-xts" */
423,	/* "aes-192-cbc" */
917,	/* "aes-192-cbc-hmac-sha1" */
899,	/* "aes-192-ccm" */
425,	/* "aes-192-cfb" */
651,	/* "aes-192-cfb1" */
654,	/* "aes-192-cfb8" */
905,	/* "aes-192-ctr" */
422,	/* "aes-192-ecb" */
898,	/* "aes-192-gcm" */
424,	/* "aes-192-ofb" */
427,	/* "aes-256-cbc" */
918,	/* "aes-256-cbc-hmac-sha1" */
902,	/* "aes-256-ccm" */
429,	/* "aes-256-cfb" */
652,	/* "aes-256-cfb1" */
655,	/* "aes-256-cfb8" */
906,	/* "aes-256-ctr" */
426,	/* "aes-256-ecb" */
901,	/* "aes-256-gcm" */
428,	/* "aes-256-ofb" */
914,	/* "aes-256-xts" */
376,	/* "algorithm" */
484,	/* "associatedDomain" */
485,	/* "associatedName" */
501,	/* "audio" */
882,	/* "authorityRevocationList" */
91,	/* "bf-cbc" */
93,	/* "bf-cfb" */
92,	/* "bf-ecb" */
94,	/* "bf-ofb" */
922,	/* "brainpool" */
923,	/* "brainpoolP160r1" */
924,	/* "brainpoolP160t1" */
925,	/* "brainpoolP192r1" */
926,	/* "brainpoolP192t1" */
927,	/* "brainpoolP224r1" */
928,	/* "brainpoolP224t1" */
929,	/* "brainpoolP256r1" */
930,	/* "brainpoolP256t1" */
931,	/* "brainpoolP320r1" */
932,	/* "brainpoolP320t1" */
933,	/* "brainpoolP384r1" */
934,	/* "brainpoolP384t1" */
935,	/* "brainpoolP512r1" */
936,	/* "brainpoolP512t1" */
494,	/* "buildingName" */
860,	/* "businessCategory" */
691,	/* "c2onb191v4" */
692,	/* "c2onb191v5" */
697,	/* "c2onb239v4" */
698,	/* "c2onb239v5" */
684,	/* "c2pnb163v1" */
685,	/* "c2pnb163v2" */
686,	/* "c2pnb163v3" */
687,	/* "c2pnb176v1" */
693,	/* "c2pnb208w1" */
699,	/* "c2pnb272w1" */
700,	/* "c2pnb304w1" */
702,	/* "c2pnb368w1" */
688,	/* "c2tnb191v1" */
689,	/* "c2tnb191v2" */
690,	/* "c2tnb191v3" */
694,	/* "c2tnb239v1" */
695,	/* "c2tnb239v2" */
696,	/* "c2tnb239v3" */
701,	/* "c2tnb359v1" */
703,	/* "c2tnb431r1" */
881,	/* "cACertificate" */
483,	/* "cNAMERecord" */
751,	/* "camellia-128-cbc" */
757,	/* "camellia-128-cfb" */
760,	/* "camellia-128-cfb1" */
763,	/* "camellia-128-cfb8" */
754,	/* "camellia-128-ecb" */
766,	/* "camellia-128-ofb" */
752,	/* "camellia-192-cbc" */
758,	/* "camellia-192-cfb" */
761,	/* "camellia-192-cfb1" */
764,	/* "camellia-192-cfb8" */
755,	/* "camellia-192-ecb" */
767,	/* "camellia-192-ofb" */
753,	/* "camellia-256-cbc" */
759,	/* "camellia-256-cfb" */
762,	/* "camellia-256-cfb1" */
765,	/* "camellia-256-cfb8" */
756,	/* "camellia-256-ecb" */
768,	/* "camellia-256-ofb" */
443,	/* "caseIgnoreIA5StringSyntax" */
108,	/* "cast5-cbc" */
110,	/* "cast5-cfb" */
109,	/* "cast5-ecb" */
111,	/* "cast5-ofb" */
152,	/* "certBag" */
677,	/* "certicom-arc" */
517,	/* "certificate extensions" */
883,	/* "certificateRevocationList" */
920,	/* "chacha" */
54,	/* "challengePassword" */
407,	/* "characteristic-two-field" */
395,	/* "clearance" */
633,	/* "cleartext track 2" */
894,	/* "cmac" */
13,	/* "commonName" */
513,	/* "content types" */
50,	/* "contentType" */
53,	/* "countersignature" */
14,	/* "countryName" */
153,	/* "crlBag" */
884,	/* "crossCertificatePair" */
806,	/* "cryptocom" */
805,	/* "cryptopro" */
500,	/* "dITRedirect" */
451,	/* "dNSDomain" */
495,	/* "dSAQuality" */
434,	/* "data" */
390,	/* "dcObject" */
891,	/* "deltaRevocationList" */
31,	/* "des-cbc" */
643,	/* "des-cdmf" */
949,	/* "des-cfb" */
950,	/* "des-cfb1" */
951,	/* "des-cfb8" */
29,	/* "des-ecb" */
32,	/* "des-ede" */
43,	/* "des-ede-cbc" */
60,	/* "des-ede-cfb" */
62,	/* "des-ede-ofb" */
33,	/* "des-ede3" */
44,	/* "des-ede3-cbc" */
61,	/* "des-ede3-cfb" */
658,	/* "des-ede3-cfb1" */
659,	/* "des-ede3-cfb8" */
63,	/* "des-ede3-ofb" */
45,	/* "des-ofb" */
107,	/* "description" */
871,	/* "destinationIndicator" */
80,	/* "desx-cbc" */
28,	/* "dhKeyAgreement" */
11,	/* "directory services (X.500)" */
378,	/* "directory services - algorithms" */
887,	/* "distinguishedName" */
892,	/* "dmdName" */
174,	/* "dnQualifier" */
447,	/* "document" */
471,	/* "documentAuthor" */
468,	/* "documentIdentifier" */
472,	/* "documentLocation" */
502,	/* "documentPublisher" */
449,	/* "documentSeries" */
469,	/* "documentTitle" */
470,	/* "documentVersion" */
380,	/* "dod" */
391,	/* "domainComponent" */
452,	/* "domainRelatedObject" */
116,	/* "dsaEncryption" */
67,	/* "dsaEncryption-old" */
66,	/* "dsaWithSHA" */
113,	/* "dsaWithSHA1" */
70,	/* "dsaWithSHA1-old" */
802,	/* "dsa_with_SHA224" */
803,	/* "dsa_with_SHA256" */
297,	/* "dvcs" */
791,	/* "ecdsa-with-Recommended" */
416,	/* "ecdsa-with-SHA1" */
793,	/* "ecdsa-with-SHA224" */
794,	/* "ecdsa-with-SHA256" */
795,	/* "ecdsa-with-SHA384" */
796,	/* "ecdsa-with-SHA512" */
792,	/* "ecdsa-with-Specified" */
48,	/* "emailAddress" */
632,	/* "encrypted track 2" */
885,	/* "enhancedSearchGuide" */
56,	/* "extendedCertificateAttributes" */
867,	/* "facsimileTelephoneNumber" */
462,	/* "favouriteDrink" */
453,	/* "friendlyCountry" */
490,	/* "friendlyCountryName" */
156,	/* "friendlyName" */
631,	/* "generate cryptogram" */
509,	/* "generationQualifier" */
601,	/* "generic cryptogram" */
99,	/* "givenName" */
938,	/* "gost89-cbc" */
814,	/* "gost89-cnt" */
937,	/* "gost89-ecb" */
855,	/* "hmac" */
780,	/* "hmac-md5" */
781,	/* "hmac-sha1" */
797,	/* "hmacWithMD5" */
163,	/* "hmacWithSHA1" */
798,	/* "hmacWithSHA224" */
799,	/* "hmacWithSHA256" */
800,	/* "hmacWithSHA384" */
801,	/* "hmacWithSHA512" */
486,	/* "homePostalAddress" */
473,	/* "homeTelephoneNumber" */
466,	/* "host" */
889,	/* "houseIdentifier" */
442,	/* "iA5StringSyntax" */
381,	/* "iana" */
824,	/* "id-Gost28147-89-CryptoPro-A-ParamSet" */
825,	/* "id-Gost28147-89-CryptoPro-B-ParamSet" */
826,	/* "id-Gost28147-89-CryptoPro-C-ParamSet" */
827,	/* "id-Gost28147-89-CryptoPro-D-ParamSet" */
819,	/* "id-Gost28147-89-CryptoPro-KeyMeshing" */
829,	/* "id-Gost28147-89-CryptoPro-Oscar-1-0-ParamSet" */
828,	/* "id-Gost28147-89-CryptoPro-Oscar-1-1-ParamSet" */
830,	/* "id-Gost28147-89-CryptoPro-RIC-1-ParamSet" */
820,	/* "id-Gost28147-89-None-KeyMeshing" */
823,	/* "id-Gost28147-89-TestParamSet" */
840,	/* "id-GostR3410-2001-CryptoPro-A-ParamSet" */
841,	/* "id-GostR3410-2001-CryptoPro-B-ParamSet" */
842,	/* "id-GostR3410-2001-CryptoPro-C-ParamSet" */
843,	/* "id-GostR3410-2001-CryptoPro-XchA-ParamSet" */
844,	/* "id-GostR3410-2001-CryptoPro-XchB-ParamSet" */
839,	/* "id-GostR3410-2001-TestParamSet" */
832,	/* "id-GostR3410-94-CryptoPro-A-ParamSet" */
833,	/* "id-GostR3410-94-CryptoPro-B-ParamSet" */
834,	/* "id-GostR3410-94-CryptoPro-C-ParamSet" */
835,	/* "id-GostR3410-94-CryptoPro-D-ParamSet" */
836,	/* "id-GostR3410-94-CryptoPro-XchA-ParamSet" */
837,	/* "id-GostR3410-94-CryptoPro-XchB-ParamSet" */
838,	/* "id-GostR3410-94-CryptoPro-XchC-ParamSet" */
831,	/* "id-GostR3410-94-TestParamSet" */
845,	/* "id-GostR3410-94-a" */
846,	/* "id-GostR3410-94-aBis" */
847,	/* "id-GostR3410-94-b" */
848,	/* "id-GostR3410-94-bBis" */
822,	/* "id-GostR3411-94-CryptoProParamSet" */
821,	/* "id-GostR3411-94-TestParamSet" */
266,	/* "id-aca" */
355,	/* "id-aca-accessIdentity" */
354,	/* "id-aca-authenticationInfo" */
356,	/* "id-aca-chargingIdentity" */
399,	/* "id-aca-encAttrs" */
357,	/* "id-aca-group" */
358,	/* "id-aca-role" */
176,	/* "id-ad" */
788,	/* "id-aes128-wrap" */
897,	/* "id-aes128-wrap-pad" */
789,	/* "id-aes192-wrap" */
900,	/* "id-aes192-wrap-pad" */
790,	/* "id-aes256-wrap" */
903,	/* "id-aes256-wrap-pad" */
262,	/* "id-alg" */
893,	/* "id-alg-PWRI-KEK" */
323,	/* "id-alg-des40" */
326,	/* "id-alg-dh-pop" */
325,	/* "id-alg-dh-sig-hmac-sha1" */
324,	/* "id-alg-noSignature" */
907,	/* "id-camellia128-wrap" */
908,	/* "id-camellia192-wrap" */
909,	/* "id-camellia256-wrap" */
268,	/* "id-cct" */
361,	/* "id-cct-PKIData" */
362,	/* "id-cct-PKIResponse" */
360,	/* "id-cct-crs" */
81,	/* "id-ce" */
680,	/* "id-characteristic-two-basis" */
263,	/* "id-cmc" */
334,	/* "id-cmc-addExtensions" */
346,	/* "id-cmc-confirmCertAcceptance" */
330,	/* "id-cmc-dataReturn" */
336,	/* "id-cmc-decryptedPOP" */
335,	/* "id-cmc-encryptedPOP" */
339,	/* "id-cmc-getCRL" */
338,	/* "id-cmc-getCert" */
328,	/* "id-cmc-identification" */
329,	/* "id-cmc-identityProof" */
337,	/* "id-cmc-lraPOPWitness" */
344,	/* "id-cmc-popLinkRandom" */
345,	/* "id-cmc-popLinkWitness" */
343,	/* "id-cmc-queryPending" */
333,	/* "id-cmc-recipientNonce" */
341,	/* "id-cmc-regInfo" */
342,	/* "id-cmc-responseInfo" */
340,	/* "id-cmc-revokeRequest" */
332,	/* "id-cmc-senderNonce" */
327,	/* "id-cmc-statusInfo" */
331,	/* "id-cmc-transactionId" */
787,	/* "id-ct-asciiTextWithCRLF" */
408,	/* "id-ecPublicKey" */
508,	/* "id-hex-multipart-message" */
507,	/* "id-hex-partial-message" */
260,	/* "id-it" */
302,	/* "id-it-caKeyUpdateInfo" */
298,	/* "id-it-caProtEncCert" */
311,	/* "id-it-confirmWaitTime" */
303,	/* "id-it-currentCRL" */
300,	/* "id-it-encKeyPairTypes" */
310,	/* "id-it-implicitConfirm" */
308,	/* "id-it-keyPairParamRep" */
307,	/* "id-it-keyPairParamReq" */
312,	/* "id-it-origPKIMessage" */
301,	/* "id-it-preferredSymmAlg" */
309,	/* "id-it-revPassphrase" */
299,	/* "id-it-signKeyPairTypes" */
305,	/* "id-it-subscriptionRequest" */
306,	/* "id-it-subscriptionResponse" */
784,	/* "id-it-suppLangTags" */
304,	/* "id-it-unsupportedOIDs" */
128,	/* "id-kp" */
280,	/* "id-mod-attribute-cert" */
274,	/* "id-mod-cmc" */
277,	/* "id-mod-cmp" */
284,	/* "id-mod-cmp2000" */
273,	/* "id-mod-crmf" */
283,	/* "id-mod-dvcs" */
275,	/* "id-mod-kea-profile-88" */
276,	/* "id-mod-kea-profile-93" */
282,	/* "id-mod-ocsp" */
278,	/* "id-mod-qualified-cert-88" */
279,	/* "id-mod-qualified-cert-93" */
281,	/* "id-mod-timestamp-protocol" */
264,	/* "id-on" */
347,	/* "id-on-personalData" */
265,	/* "id-pda" */
352,	/* "id-pda-countryOfCitizenship" */
353,	/* "id-pda-countryOfResidence" */
348,	/* "id-pda-dateOfBirth" */
351,	/* "id-pda-gender" */
349,	/* "id-pda-placeOfBirth" */
175,	/* "id-pe" */
261,	/* "id-pkip" */
258,	/* "id-pkix-mod" */
269,	/* "id-pkix1-explicit-88" */
271,	/* "id-pkix1-explicit-93" */
270,	/* "id-pkix1-implicit-88" */
272,	/* "id-pkix1-implicit-93" */
662,	/* "id-ppl" */
267,	/* "id-qcs" */
359,	/* "id-qcs-pkixQCSyntax-v1" */
259,	/* "id-qt" */
313,	/* "id-regCtrl" */
316,	/* "id-regCtrl-authenticator" */
319,	/* "id-regCtrl-oldCertID" */
318,	/* "id-regCtrl-pkiArchiveOptions" */
317,	/* "id-regCtrl-pkiPublicationInfo" */
320,	/* "id-regCtrl-protocolEncrKey" */
315,	/* "id-regCtrl-regToken" */
314,	/* "id-regInfo" */
322,	/* "id-regInfo-certReq" */
321,	/* "id-regInfo-utf8Pairs" */
191,	/* "id-smime-aa" */
215,	/* "id-smime-aa-contentHint" */
218,	/* "id-smime-aa-contentIdentifier" */
221,	/* "id-smime-aa-contentReference" */
240,	/* "id-smime-aa-dvcs-dvc" */
217,	/* "id-smime-aa-encapContentType" */
222,	/* "id-smime-aa-encrypKeyPref" */
220,	/* "id-smime-aa-equivalentLabels" */
232,	/* "id-smime-aa-ets-CertificateRefs" */
233,	/* "id-smime-aa-ets-RevocationRefs" */
238,	/* "id-smime-aa-ets-archiveTimeStamp" */
237,	/* "id-smime-aa-ets-certCRLTimestamp" */
234,	/* "id-smime-aa-ets-certValues" */
227,	/* "id-smime-aa-ets-commitmentType" */
231,	/* "id-smime-aa-ets-contentTimestamp" */
236,	/* "id-smime-aa-ets-escTimeStamp" */
230,	/* "id-smime-aa-ets-otherSigCert" */
235,	/* "id-smime-aa-ets-revocationValues" */
226,	/* "id-smime-aa-ets-sigPolicyId" */
229,	/* "id-smime-aa-ets-signerAttr" */
228,	/* "id-smime-aa-ets-signerLocation" */
219,	/* "id-smime-aa-macValue" */
214,	/* "id-smime-aa-mlExpandHistory" */
216,	/* "id-smime-aa-msgSigDigest" */
212,	/* "id-smime-aa-receiptRequest" */
213,	/* "id-smime-aa-securityLabel" */
239,	/* "id-smime-aa-signatureType" */
223,	/* "id-smime-aa-signingCertificate" */
224,	/* "id-smime-aa-smimeEncryptCerts" */
225,	/* "id-smime-aa-timeStampToken" */
192,	/* "id-smime-alg" */
243,	/* "id-smime-alg-3DESwrap" */
246,	/* "id-smime-alg-CMS3DESwrap" */
247,	/* "id-smime-alg-CMSRC2wrap" */
245,	/* "id-smime-alg-ESDH" */
241,	/* "id-smime-alg-ESDHwith3DES" */
242,	/* "id-smime-alg-ESDHwithRC2" */
244,	/* "id-smime-alg-RC2wrap" */
193,	/* "id-smime-cd" */
248,	/* "id-smime-cd-ldap" */
190,	/* "id-smime-ct" */
210,	/* "id-smime-ct-DVCSRequestData" */
211,	/* "id-smime-ct-DVCSResponseData" */
208,	/* "id-smime-ct-TDTInfo" */
207,	/* "id-smime-ct-TSTInfo" */
205,	/* "id-smime-ct-authData" */
786,	/* "id-smime-ct-compressedData" */
209,	/* "id-smime-ct-contentInfo" */
206,	/* "id-smime-ct-publishCert" */
204,	/* "id-smime-ct-receipt" */
195,	/* "id-smime-cti" */
255,	/* "id-smime-cti-ets-proofOfApproval" */
256,	/* "id-smime-cti-ets-proofOfCreation" */
253,	/* "id-smime-cti-ets-proofOfDelivery" */
251,	/* "id-smime-cti-ets-proofOfOrigin" */
252,	/* "id-smime-cti-ets-proofOfReceipt" */
254,	/* "id-smime-cti-ets-proofOfSender" */
189,	/* "id-smime-mod" */
196,	/* "id-smime-mod-cms" */
197,	/* "id-smime-mod-ess" */
202,	/* "id-smime-mod-ets-eSigPolicy-88" */
203,	/* "id-smime-mod-ets-eSigPolicy-97" */
200,	/* "id-smime-mod-ets-eSignature-88" */
201,	/* "id-smime-mod-ets-eSignature-97" */
199,	/* "id-smime-mod-msg-v3" */
198,	/* "id-smime-mod-oid" */
194,	/* "id-smime-spq" */
250,	/* "id-smime-spq-ets-sqt-unotice" */
249,	/* "id-smime-spq-ets-sqt-uri" */
944,	/* "id-tc26-gost-28147-param-Z" */
942,	/* "id-tc26-gost-3410-2012-512-paramSetA" */
943,	/* "id-tc26-gost-3410-2012-512-paramSetB" */
34,	/* "idea-cbc" */
35,	/* "idea-cfb" */
36,	/* "idea-ecb" */
46,	/* "idea-ofb" */
676,	/* "identified-organization" */
461,	/* "info" */
101,	/* "initials" */
869,	/* "internationaliSDNNumber" */
749,	/* "ipsec3" */
750,	/* "ipsec4" */
181,	/* "iso" */
623,	/* "issuer capabilities" */
645,	/* "itu-t" */
492,	/* "janetMailbox" */
646,	/* "joint-iso-itu-t" */
150,	/* "keyBag" */
477,	/* "lastModifiedBy" */
476,	/* "lastModifiedTime" */
157,	/* "localKeyID" */
15,	/* "localityName" */
480,	/* "mXRecord" */
493,	/* "mailPreferenceOption" */
467,	/* "manager" */
 4,	/* "md5" */
114,	/* "md5-sha1" */
104,	/* "md5WithRSA" */
 8,	/* "md5WithRSAEncryption" */
875,	/* "member" */
602,	/* "merchant initiated auth" */
514,	/* "message extensions" */
51,	/* "messageDigest" */
911,	/* "mgf1" */
506,	/* "mime-mhs-bodies" */
505,	/* "mime-mhs-headings" */
488,	/* "mobileTelephoneNumber" */
481,	/* "nSRecord" */
173,	/* "name" */
681,	/* "onBasis" */
379,	/* "org" */
17,	/* "organizationName" */
491,	/* "organizationalStatus" */
18,	/* "organizationalUnitName" */
475,	/* "otherMailbox" */
876,	/* "owner" */
489,	/* "pagerTelephoneNumber" */
782,	/* "password based MAC" */
374,	/* "path" */
621,	/* "payment gateway capabilities" */
112,	/* "pbeWithMD5AndCast5CBC" */
10,	/* "pbeWithMD5AndDES-CBC" */
169,	/* "pbeWithMD5AndRC2-CBC" */
148,	/* "pbeWithSHA1And128BitRC2-CBC" */
144,	/* "pbeWithSHA1And128BitRC4" */
147,	/* "pbeWithSHA1And2-KeyTripleDES-CBC" */
146,	/* "pbeWithSHA1And3-KeyTripleDES-CBC" */
149,	/* "pbeWithSHA1And40BitRC2-CBC" */
145,	/* "pbeWithSHA1And40BitRC4" */
170,	/* "pbeWithSHA1AndDES-CBC" */
68,	/* "pbeWithSHA1AndRC2-CBC" */
499,	/* "personalSignature" */
487,	/* "personalTitle" */
464,	/* "photo" */
863,	/* "physicalDeliveryOfficeName" */
437,	/* "pilot" */
439,	/* "pilotAttributeSyntax" */
438,	/* "pilotAttributeType" */
479,	/* "pilotAttributeType27" */
456,	/* "pilotDSA" */
441,	/* "pilotGroups" */
444,	/* "pilotObject" */
440,	/* "pilotObjectClass" */
455,	/* "pilotOrganization" */
445,	/* "pilotPerson" */
186,	/* "pkcs1" */
27,	/* "pkcs3" */
187,	/* "pkcs5" */
20,	/* "pkcs7" */
21,	/* "pkcs7-data" */
25,	/* "pkcs7-digestData" */
26,	/* "pkcs7-encryptedData" */
23,	/* "pkcs7-envelopedData" */
24,	/* "pkcs7-signedAndEnvelopedData" */
22,	/* "pkcs7-signedData" */
151,	/* "pkcs8ShroudedKeyBag" */
47,	/* "pkcs9" */
862,	/* "postOfficeBox" */
861,	/* "postalAddress" */
661,	/* "postalCode" */
683,	/* "ppBasis" */
872,	/* "preferredDeliveryMethod" */
873,	/* "presentationAddress" */
406,	/* "prime-field" */
409,	/* "prime192v1" */
410,	/* "prime192v2" */
411,	/* "prime192v3" */
412,	/* "prime239v1" */
413,	/* "prime239v2" */
414,	/* "prime239v3" */
415,	/* "prime256v1" */
886,	/* "protocolInformation" */
510,	/* "pseudonym" */
435,	/* "pss" */
286,	/* "qcStatements" */
457,	/* "qualityLabelledData" */
450,	/* "rFC822localPart" */
98,	/* "rc2-40-cbc" */
166,	/* "rc2-64-cbc" */
37,	/* "rc2-cbc" */
39,	/* "rc2-cfb" */
38,	/* "rc2-ecb" */
40,	/* "rc2-ofb" */
 5,	/* "rc4" */
97,	/* "rc4-40" */
915,	/* "rc4-hmac-md5" */
120,	/* "rc5-cbc" */
122,	/* "rc5-cfb" */
121,	/* "rc5-ecb" */
123,	/* "rc5-ofb" */
870,	/* "registeredAddress" */
460,	/* "rfc822Mailbox" */
117,	/* "ripemd160" */
119,	/* "ripemd160WithRSA" */
400,	/* "role" */
877,	/* "roleOccupant" */
448,	/* "room" */
463,	/* "roomNumber" */
19,	/* "rsa" */
 6,	/* "rsaEncryption" */
644,	/* "rsaOAEPEncryptionSET" */
377,	/* "rsaSignature" */
919,	/* "rsaesOaep" */
912,	/* "rsassaPss" */
124,	/* "run length compression" */
482,	/* "sOARecord" */
155,	/* "safeContentsBag" */
291,	/* "sbgp-autonomousSysNum" */
290,	/* "sbgp-ipAddrBlock" */
292,	/* "sbgp-routerIdentifier" */
159,	/* "sdsiCertificate" */
859,	/* "searchGuide" */
704,	/* "secp112r1" */
705,	/* "secp112r2" */
706,	/* "secp128r1" */
707,	/* "secp128r2" */
708,	/* "secp160k1" */
709,	/* "secp160r1" */
710,	/* "secp160r2" */
711,	/* "secp192k1" */
712,	/* "secp224k1" */
713,	/* "secp224r1" */
714,	/* "secp256k1" */
715,	/* "secp384r1" */
716,	/* "secp521r1" */
154,	/* "secretBag" */
474,	/* "secretary" */
717,	/* "sect113r1" */
718,	/* "sect113r2" */
719,	/* "sect131r1" */
720,	/* "sect131r2" */
721,	/* "sect163k1" */
722,	/* "sect163r1" */
723,	/* "sect163r2" */
724,	/* "sect193r1" */
725,	/* "sect193r2" */
726,	/* "sect233k1" */
727,	/* "sect233r1" */
728,	/* "sect239k1" */
729,	/* "sect283k1" */
730,	/* "sect283r1" */
731,	/* "sect409k1" */
732,	/* "sect409r1" */
733,	/* "sect571k1" */
734,	/* "sect571r1" */
635,	/* "secure device signature" */
878,	/* "seeAlso" */
105,	/* "serialNumber" */
625,	/* "set-addPolicy" */
515,	/* "set-attr" */
518,	/* "set-brand" */
638,	/* "set-brand-AmericanExpress" */
637,	/* "set-brand-Diners" */
636,	/* "set-brand-IATA-ATA" */
639,	/* "set-brand-JCB" */
641,	/* "set-brand-MasterCard" */
642,	/* "set-brand-Novus" */
640,	/* "set-brand-Visa" */
516,	/* "set-policy" */
607,	/* "set-policy-root" */
624,	/* "set-rootKeyThumb" */
620,	/* "setAttr-Cert" */
628,	/* "setAttr-IssCap-CVM" */
630,	/* "setAttr-IssCap-Sig" */
629,	/* "setAttr-IssCap-T2" */
627,	/* "setAttr-Token-B0Prime" */
626,	/* "setAttr-Token-EMV" */
622,	/* "setAttr-TokenType" */
619,	/* "setCext-IssuerCapabilities" */
615,	/* "setCext-PGWYcapabilities" */
616,	/* "setCext-TokenIdentifier" */
618,	/* "setCext-TokenType" */
617,	/* "setCext-Track2Data" */
611,	/* "setCext-cCertRequired" */
609,	/* "setCext-certType" */
608,	/* "setCext-hashedRoot" */
610,	/* "setCext-merchData" */
613,	/* "setCext-setExt" */
614,	/* "setCext-setQualf" */
612,	/* "setCext-tunneling" */
540,	/* "setct-AcqCardCodeMsg" */
576,	/* "setct-AcqCardCodeMsgTBE" */
570,	/* "setct-AuthReqTBE" */
534,	/* "setct-AuthReqTBS" */
527,	/* "setct-AuthResBaggage" */
571,	/* "setct-AuthResTBE" */
572,	/* "setct-AuthResTBEX" */
535,	/* "setct-AuthResTBS" */
536,	/* "setct-AuthResTBSX" */
528,	/* "setct-AuthRevReqBaggage" */
577,	/* "setct-AuthRevReqTBE" */
541,	/* "setct-AuthRevReqTBS" */
529,	/* "setct-AuthRevResBaggage" */
542,	/* "setct-AuthRevResData" */
578,	/* "setct-AuthRevResTBE" */
579,	/* "setct-AuthRevResTBEB" */
543,	/* "setct-AuthRevResTBS" */
573,	/* "setct-AuthTokenTBE" */
537,	/* "setct-AuthTokenTBS" */
600,	/* "setct-BCIDistributionTBS" */
558,	/* "setct-BatchAdminReqData" */
592,	/* "setct-BatchAdminReqTBE" */
559,	/* "setct-BatchAdminResData" */
593,	/* "setct-BatchAdminResTBE" */
599,	/* "setct-CRLNotificationResTBS" */
598,	/* "setct-CRLNotificationTBS" */
580,	/* "setct-CapReqTBE" */
581,	/* "setct-CapReqTBEX" */
544,	/* "setct-CapReqTBS" */
545,	/* "setct-CapReqTBSX" */
546,	/* "setct-CapResData" */
582,	/* "setct-CapResTBE" */
583,	/* "setct-CapRevReqTBE" */
584,	/* "setct-CapRevReqTBEX" */
547,	/* "setct-CapRevReqTBS" */
548,	/* "setct-CapRevReqTBSX" */
549,	/* "setct-CapRevResData" */
585,	/* "setct-CapRevResTBE" */
538,	/* "setct-CapTokenData" */
530,	/* "setct-CapTokenSeq" */
574,	/* "setct-CapTokenTBE" */
575,	/* "setct-CapTokenTBEX" */
539,	/* "setct-CapTokenTBS" */
560,	/* "setct-CardCInitResTBS" */
566,	/* "setct-CertInqReqTBS" */
563,	/* "setct-CertReqData" */
595,	/* "setct-CertReqTBE" */
596,	/* "setct-CertReqTBEX" */
564,	/* "setct-CertReqTBS" */
565,	/* "setct-CertResData" */
597,	/* "setct-CertResTBE" */
586,	/* "setct-CredReqTBE" */
587,	/* "setct-CredReqTBEX" */
550,	/* "setct-CredReqTBS" */
551,	/* "setct-CredReqTBSX" */
552,	/* "setct-CredResData" */
588,	/* "setct-CredResTBE" */
589,	/* "setct-CredRevReqTBE" */
590,	/* "setct-CredRevReqTBEX" */
553,	/* "setct-CredRevReqTBS" */
554,	/* "setct-CredRevReqTBSX" */
555,	/* "setct-CredRevResData" */
591,	/* "setct-CredRevResTBE" */
567,	/* "setct-ErrorTBS" */
526,	/* "setct-HODInput" */
561,	/* "setct-MeAqCInitResTBS" */
522,	/* "setct-OIData" */
519,	/* "setct-PANData" */
521,	/* "setct-PANOnly" */
520,	/* "setct-PANToken" */
556,	/* "setct-PCertReqData" */
557,	/* "setct-PCertResTBS" */
523,	/* "setct-PI" */
532,	/* "setct-PI-TBS" */
524,	/* "setct-PIData" */
525,	/* "setct-PIDataUnsigned" */
568,	/* "setct-PIDualSignedTBE" */
569,	/* "setct-PIUnsignedTBE" */
531,	/* "setct-PInitResData" */
533,	/* "setct-PResData" */
594,	/* "setct-RegFormReqTBE" */
562,	/* "setct-RegFormResTBS" */
604,	/* "setext-pinAny" */
603,	/* "setext-pinSecure" */
605,	/* "setext-track2" */
41,	/* "sha" */
64,	/* "sha1" */
115,	/* "sha1WithRSA" */
65,	/* "sha1WithRSAEncryption" */
675,	/* "sha224" */
671,	/* "sha224WithRSAEncryption" */
672,	/* "sha256" */
668,	/* "sha256WithRSAEncryption" */
673,	/* "sha384" */
669,	/* "sha384WithRSAEncryption" */
674,	/* "sha512" */
670,	/* "sha512WithRSAEncryption" */
42,	/* "shaWithRSAEncryption" */
52,	/* "signingTime" */
454,	/* "simpleSecurityObject" */
496,	/* "singleLevelQuality" */
16,	/* "stateOrProvinceName" */
660,	/* "streetAddress" */
498,	/* "subtreeMaximumQuality" */
497,	/* "subtreeMinimumQuality" */
890,	/* "supportedAlgorithms" */
874,	/* "supportedApplicationContext" */
100,	/* "surname" */
939,	/* "tc26" */
864,	/* "telephoneNumber" */
866,	/* "teletexTerminalIdentifier" */
921,	/* "teletrust" */
865,	/* "telexNumber" */
459,	/* "textEncodedORAddress" */
293,	/* "textNotice" */
106,	/* "title" */
682,	/* "tpBasis" */
436,	/* "ucl" */
 0,	/* "undefined" */
888,	/* "uniqueMember" */
55,	/* "unstructuredAddress" */
49,	/* "unstructuredName" */
880,	/* "userCertificate" */
465,	/* "userClass" */
458,	/* "userId" */
879,	/* "userPassword" */
373,	/* "valid" */
678,	/* "wap" */
679,	/* "wap-wsg" */
735,	/* "wap-wsg-idm-ecid-wtls1" */
743,	/* "wap-wsg-idm-ecid-wtls10" */
744,	/* "wap-wsg-idm-ecid-wtls11" */
745,	/* "wap-wsg-idm-ecid-wtls12" */
736,	/* "wap-wsg-idm-ecid-wtls3" */
737,	/* "wap-wsg-idm-ecid-wtls4" */
738,	/* "wap-wsg-idm-ecid-wtls5" */
739,	/* "wap-wsg-idm-ecid-wtls6" */
740,	/* "wap-wsg-idm-ecid-wtls7" */
741,	/* "wap-wsg-idm-ecid-wtls8" */
742,	/* "wap-wsg-idm-ecid-wtls9" */
804,	/* "whirlpool" */
868,	/* "x121Address" */
503,	/* "x500UniqueIdentifier" */
158,	/* "x509Certificate" */
160,	/* "x509Crl" */
125,	/* "zlib compression" */
};

static const unsigned int obj_objs[NUM_OBJ]={
 0,	/* OBJ_undef                        0 */
181,	/* OBJ_iso                          1 */
393,	/* OBJ_joint_iso_ccitt              OBJ_joint_iso_itu_t */
404,	/* OBJ_ccitt                        OBJ_itu_t */
645,	/* OBJ_itu_t                        0 */
646,	/* OBJ_joint_iso_itu_t              2 */
434,	/* OBJ_data                         0 9 */
182,	/* OBJ_member_body                  1 2 */
379,	/* OBJ_org                          1 3 */
676,	/* OBJ_identified_organization      1 3 */
11,	/* OBJ_X500                         2 5 */
647,	/* OBJ_international_organizations  2 23 */
380,	/* OBJ_dod                          1 3 6 */
921,	/* OBJ_teletrust                    1 3 36 */
12,	/* OBJ_X509                         2 5 4 */
378,	/* OBJ_X500algorithms               2 5 8 */
81,	/* OBJ_id_ce                        2 5 29 */
512,	/* OBJ_id_set                       2 23 42 */
678,	/* OBJ_wap                          2 23 43 */
435,	/* OBJ_pss                          0 9 2342 */
183,	/* OBJ_ISO_US                       1 2 840 */
381,	/* OBJ_iana                         1 3 6 1 */
677,	/* OBJ_certicom_arc                 1 3 132 */
394,	/* OBJ_selected_attribute_types     2 5 1 5 */
13,	/* OBJ_commonName                   2 5 4 3 */
100,	/* OBJ_surname                      2 5 4 4 */
105,	/* OBJ_serialNumber                 2 5 4 5 */
14,	/* OBJ_countryName                  2 5 4 6 */
15,	/* OBJ_localityName                 2 5 4 7 */
16,	/* OBJ_stateOrProvinceName          2 5 4 8 */
660,	/* OBJ_streetAddress                2 5 4 9 */
17,	/* OBJ_organizationName             2 5 4 10 */
18,	/* OBJ_organizationalUnitName       2 5 4 11 */
106,	/* OBJ_title                        2 5 4 12 */
107,	/* OBJ_description                  2 5 4 13 */
859,	/* OBJ_searchGuide                  2 5 4 14 */
860,	/* OBJ_businessCategory             2 5 4 15 */
861,	/* OBJ_postalAddress                2 5 4 16 */
661,	/* OBJ_postalCode                   2 5 4 17 */
862,	/* OBJ_postOfficeBox                2 5 4 18 */
863,	/* OBJ_physicalDeliveryOfficeName   2 5 4 19 */
864,	/* OBJ_telephoneNumber              2 5 4 20 */
865,	/* OBJ_telexNumber                  2 5 4 21 */
866,	/* OBJ_teletexTerminalIdentifier    2 5 4 22 */
867,	/* OBJ_facsimileTelephoneNumber     2 5 4 23 */
868,	/* OBJ_x121Address                  2 5 4 24 */
869,	/* OBJ_internationaliSDNNumber      2 5 4 25 */
870,	/* OBJ_registeredAddress            2 5 4 26 */
871,	/* OBJ_destinationIndicator         2 5 4 27 */
872,	/* OBJ_preferredDeliveryMethod      2 5 4 28 */
873,	/* OBJ_presentationAddress          2 5 4 29 */
874,	/* OBJ_supportedApplicationContext  2 5 4 30 */
875,	/* OBJ_member                       2 5 4 31 */
876,	/* OBJ_owner                        2 5 4 32 */
877,	/* OBJ_roleOccupant                 2 5 4 33 */
878,	/* OBJ_seeAlso                      2 5 4 34 */
879,	/* OBJ_userPassword                 2 5 4 35 */
880,	/* OBJ_userCertificate              2 5 4 36 */
881,	/* OBJ_cACertificate                2 5 4 37 */
882,	/* OBJ_authorityRevocationList      2 5 4 38 */
883,	/* OBJ_certificateRevocationList    2 5 4 39 */
884,	/* OBJ_crossCertificatePair         2 5 4 40 */
173,	/* OBJ_name                         2 5 4 41 */
99,	/* OBJ_givenName                    2 5 4 42 */
101,	/* OBJ_initials                     2 5 4 43 */
509,	/* OBJ_generationQualifier          2 5 4 44 */
503,	/* OBJ_x500UniqueIdentifier         2 5 4 45 */
174,	/* OBJ_dnQualifier                  2 5 4 46 */
885,	/* OBJ_enhancedSearchGuide          2 5 4 47 */
886,	/* OBJ_protocolInformation          2 5 4 48 */
887,	/* OBJ_distinguishedName            2 5 4 49 */
888,	/* OBJ_uniqueMember                 2 5 4 50 */
889,	/* OBJ_houseIdentifier              2 5 4 51 */
890,	/* OBJ_supportedAlgorithms          2 5 4 52 */
891,	/* OBJ_deltaRevocationList          2 5 4 53 */
892,	/* OBJ_dmdName                      2 5 4 54 */
510,	/* OBJ_pseudonym                    2 5 4 65 */
400,	/* OBJ_role                         2 5 4 72 */
769,	/* OBJ_subject_directory_attributes 2 5 29 9 */
82,	/* OBJ_subject_key_identifier       2 5 29 14 */
83,	/* OBJ_key_usage                    2 5 29 15 */
84,	/* OBJ_private_key_usage_period     2 5 29 16 */
85,	/* OBJ_subject_alt_name             2 5 29 17 */
86,	/* OBJ_issuer_alt_name              2 5 29 18 */
87,	/* OBJ_basic_constraints            2 5 29 19 */
88,	/* OBJ_crl_number                   2 5 29 20 */
141,	/* OBJ_crl_reason                   2 5 29 21 */
430,	/* OBJ_hold_instruction_code        2 5 29 23 */
142,	/* OBJ_invalidity_date              2 5 29 24 */
140,	/* OBJ_delta_crl                    2 5 29 27 */
770,	/* OBJ_issuing_distribution_point   2 5 29 28 */
771,	/* OBJ_certificate_issuer           2 5 29 29 */
666,	/* OBJ_name_constraints             2 5 29 30 */
103,	/* OBJ_crl_distribution_points      2 5 29 31 */
89,	/* OBJ_certificate_policies         2 5 29 32 */
747,	/* OBJ_policy_mappings              2 5 29 33 */
90,	/* OBJ_authority_key_identifier     2 5 29 35 */
401,	/* OBJ_policy_constraints           2 5 29 36 */
126,	/* OBJ_ext_key_usage                2 5 29 37 */
857,	/* OBJ_freshest_crl                 2 5 29 46 */
748,	/* OBJ_inhibit_any_policy           2 5 29 54 */
402,	/* OBJ_target_information           2 5 29 55 */
403,	/* OBJ_no_rev_avail                 2 5 29 56 */
513,	/* OBJ_set_ctype                    2 23 42 0 */
514,	/* OBJ_set_msgExt                   2 23 42 1 */
515,	/* OBJ_set_attr                     2 23 42 3 */
516,	/* OBJ_set_policy                   2 23 42 5 */
517,	/* OBJ_set_certExt                  2 23 42 7 */
518,	/* OBJ_set_brand                    2 23 42 8 */
679,	/* OBJ_wap_wsg                      2 23 43 1 */
382,	/* OBJ_Directory                    1 3 6 1 1 */
383,	/* OBJ_Management                   1 3 6 1 2 */
384,	/* OBJ_Experimental                 1 3 6 1 3 */
385,	/* OBJ_Private                      1 3 6 1 4 */
386,	/* OBJ_Security                     1 3 6 1 5 */
387,	/* OBJ_SNMPv2                       1 3 6 1 6 */
388,	/* OBJ_Mail                         1 3 6 1 7 */
376,	/* OBJ_algorithm                    1 3 14 3 2 */
395,	/* OBJ_clearance                    2 5 1 5 55 */
19,	/* OBJ_rsa                          2 5 8 1 1 */
746,	/* OBJ_any_policy                   2 5 29 32 0 */
910,	/* OBJ_anyExtendedKeyUsage          2 5 29 37 0 */
519,	/* OBJ_setct_PANData                2 23 42 0 0 */
520,	/* OBJ_setct_PANToken               2 23 42 0 1 */
521,	/* OBJ_setct_PANOnly                2 23 42 0 2 */
522,	/* OBJ_setct_OIData                 2 23 42 0 3 */
523,	/* OBJ_setct_PI                     2 23 42 0 4 */
524,	/* OBJ_setct_PIData                 2 23 42 0 5 */
525,	/* OBJ_setct_PIDataUnsigned         2 23 42 0 6 */
526,	/* OBJ_setct_HODInput               2 23 42 0 7 */
527,	/* OBJ_setct_AuthResBaggage         2 23 42 0 8 */
528,	/* OBJ_setct_AuthRevReqBaggage      2 23 42 0 9 */
529,	/* OBJ_setct_AuthRevResBaggage      2 23 42 0 10 */
530,	/* OBJ_setct_CapTokenSeq            2 23 42 0 11 */
531,	/* OBJ_setct_PInitResData           2 23 42 0 12 */
532,	/* OBJ_setct_PI_TBS                 2 23 42 0 13 */
533,	/* OBJ_setct_PResData               2 23 42 0 14 */
534,	/* OBJ_setct_AuthReqTBS             2 23 42 0 16 */
535,	/* OBJ_setct_AuthResTBS             2 23 42 0 17 */
536,	/* OBJ_setct_AuthResTBSX            2 23 42 0 18 */
537,	/* OBJ_setct_AuthTokenTBS           2 23 42 0 19 */
538,	/* OBJ_setct_CapTokenData           2 23 42 0 20 */
539,	/* OBJ_setct_CapTokenTBS            2 23 42 0 21 */
540,	/* OBJ_setct_AcqCardCodeMsg         2 23 42 0 22 */
541,	/* OBJ_setct_AuthRevReqTBS          2 23 42 0 23 */
542,	/* OBJ_setct_AuthRevResData         2 23 42 0 24 */
543,	/* OBJ_setct_AuthRevResTBS          2 23 42 0 25 */
544,	/* OBJ_setct_CapReqTBS              2 23 42 0 26 */
545,	/* OBJ_setct_CapReqTBSX             2 23 42 0 27 */
546,	/* OBJ_setct_CapResData             2 23 42 0 28 */
547,	/* OBJ_setct_CapRevReqTBS           2 23 42 0 29 */
548,	/* OBJ_setct_CapRevReqTBSX          2 23 42 0 30 */
549,	/* OBJ_setct_CapRevResData          2 23 42 0 31 */
550,	/* OBJ_setct_CredReqTBS             2 23 42 0 32 */
551,	/* OBJ_setct_CredReqTBSX            2 23 42 0 33 */
552,	/* OBJ_setct_CredResData            2 23 42 0 34 */
553,	/* OBJ_setct_CredRevReqTBS          2 23 42 0 35 */
554,	/* OBJ_setct_CredRevReqTBSX         2 23 42 0 36 */
555,	/* OBJ_setct_CredRevResData         2 23 42 0 37 */
556,	/* OBJ_setct_PCertReqData           2 23 42 0 38 */
557,	/* OBJ_setct_PCertResTBS            2 23 42 0 39 */
558,	/* OBJ_setct_BatchAdminReqData      2 23 42 0 40 */
559,	/* OBJ_setct_BatchAdminResData      2 23 42 0 41 */
560,	/* OBJ_setct_CardCInitResTBS        2 23 42 0 42 */
561,	/* OBJ_setct_MeAqCInitResTBS        2 23 42 0 43 */
562,	/* OBJ_setct_RegFormResTBS          2 23 42 0 44 */
563,	/* OBJ_setct_CertReqData            2 23 42 0 45 */
564,	/* OBJ_setct_CertReqTBS             2 23 42 0 46 */
565,	/* OBJ_setct_CertResData            2 23 42 0 47 */
566,	/* OBJ_setct_CertInqReqTBS          2 23 42 0 48 */
567,	/* OBJ_setct_ErrorTBS               2 23 42 0 49 */
568,	/* OBJ_setct_PIDualSignedTBE        2 23 42 0 50 */
569,	/* OBJ_setct_PIUnsignedTBE          2 23 42 0 51 */
570,	/* OBJ_setct_AuthReqTBE             2 23 42 0 52 */
571,	/* OBJ_setct_AuthResTBE             2 23 42 0 53 */
572,	/* OBJ_setct_AuthResTBEX            2 23 42 0 54 */
573,	/* OBJ_setct_AuthTokenTBE           2 23 42 0 55 */
574,	/* OBJ_setct_CapTokenTBE            2 23 42 0 56 */
575,	/* OBJ_setct_CapTokenTBEX           2 23 42 0 57 */
576,	/* OBJ_setct_AcqCardCodeMsgTBE      2 23 42 0 58 */
577,	/* OBJ_setct_AuthRevReqTBE          2 23 42 0 59 */
578,	/* OBJ_setct_AuthRevResTBE          2 23 42 0 60 */
579,	/* OBJ_setct_AuthRevResTBEB         2 23 42 0 61 */
580,	/* OBJ_setct_CapReqTBE              2 23 42 0 62 */
581,	/* OBJ_setct_CapReqTBEX             2 23 42 0 63 */
582,	/* OBJ_setct_CapResTBE              2 23 42 0 64 */
583,	/* OBJ_setct_CapRevReqTBE           2 23 42 0 65 */
584,	/* OBJ_setct_CapRevReqTBEX          2 23 42 0 66 */
585,	/* OBJ_setct_CapRevResTBE           2 23 42 0 67 */
586,	/* OBJ_setct_CredReqTBE             2 23 42 0 68 */
587,	/* OBJ_setct_CredReqTBEX            2 23 42 0 69 */
588,	/* OBJ_setct_CredResTBE             2 23 42 0 70 */
589,	/* OBJ_setct_CredRevReqTBE          2 23 42 0 71 */
590,	/* OBJ_setct_CredRevReqTBEX         2 23 42 0 72 */
591,	/* OBJ_setct_CredRevResTBE          2 23 42 0 73 */
592,	/* OBJ_setct_BatchAdminReqTBE       2 23 42 0 74 */
593,	/* OBJ_setct_BatchAdminResTBE       2 23 42 0 75 */
594,	/* OBJ_setct_RegFormReqTBE          2 23 42 0 76 */
595,	/* OBJ_setct_CertReqTBE             2 23 42 0 77 */
596,	/* OBJ_setct_CertReqTBEX            2 23 42 0 78 */
597,	/* OBJ_setct_CertResTBE             2 23 42 0 79 */
598,	/* OBJ_setct_CRLNotificationTBS     2 23 42 0 80 */
599,	/* OBJ_setct_CRLNotificationResTBS  2 23 42 0 81 */
600,	/* OBJ_setct_BCIDistributionTBS     2 23 42 0 82 */
601,	/* OBJ_setext_genCrypt              2 23 42 1 1 */
602,	/* OBJ_setext_miAuth                2 23 42 1 3 */
603,	/* OBJ_setext_pinSecure             2 23 42 1 4 */
604,	/* OBJ_setext_pinAny                2 23 42 1 5 */
605,	/* OBJ_setext_track2                2 23 42 1 7 */
606,	/* OBJ_setext_cv                    2 23 42 1 8 */
620,	/* OBJ_setAttr_Cert                 2 23 42 3 0 */
621,	/* OBJ_setAttr_PGWYcap              2 23 42 3 1 */
622,	/* OBJ_setAttr_TokenType            2 23 42 3 2 */
623,	/* OBJ_setAttr_IssCap               2 23 42 3 3 */
607,	/* OBJ_set_policy_root              2 23 42 5 0 */
608,	/* OBJ_setCext_hashedRoot           2 23 42 7 0 */
609,	/* OBJ_setCext_certType             2 23 42 7 1 */
610,	/* OBJ_setCext_merchData            2 23 42 7 2 */
611,	/* OBJ_setCext_cCertRequired        2 23 42 7 3 */
612,	/* OBJ_setCext_tunneling            2 23 42 7 4 */
613,	/* OBJ_setCext_setExt               2 23 42 7 5 */
614,	/* OBJ_setCext_setQualf             2 23 42 7 6 */
615,	/* OBJ_setCext_PGWYcapabilities     2 23 42 7 7 */
616,	/* OBJ_setCext_TokenIdentifier      2 23 42 7 8 */
617,	/* OBJ_setCext_Track2Data           2 23 42 7 9 */
618,	/* OBJ_setCext_TokenType            2 23 42 7 10 */
619,	/* OBJ_setCext_IssuerCapabilities   2 23 42 7 11 */
636,	/* OBJ_set_brand_IATA_ATA           2 23 42 8 1 */
640,	/* OBJ_set_brand_Visa               2 23 42 8 4 */
641,	/* OBJ_set_brand_MasterCard         2 23 42 8 5 */
637,	/* OBJ_set_brand_Diners             2 23 42 8 30 */
638,	/* OBJ_set_brand_AmericanExpress    2 23 42 8 34 */
639,	/* OBJ_set_brand_JCB                2 23 42 8 35 */
805,	/* OBJ_cryptopro                    1 2 643 2 2 */
806,	/* OBJ_cryptocom                    1 2 643 2 9 */
939,	/* OBJ_tc26                         1 2 643 7 1 */
184,	/* OBJ_X9_57                        1 2 840 10040 */
405,	/* OBJ_ansi_X9_62                   1 2 840 10045 */
389,	/* OBJ_Enterprises                  1 3 6 1 4 1 */
504,	/* OBJ_mime_mhs                     1 3 6 1 7 1 */
104,	/* OBJ_md5WithRSA                   1 3 14 3 2 3 */
29,	/* OBJ_des_ecb                      1 3 14 3 2 6 */
31,	/* OBJ_des_cbc                      1 3 14 3 2 7 */
45,	/* OBJ_des_ofb64                    1 3 14 3 2 8 */
949,	/* OBJ_des_cfb64                    1 3 14 3 2 9 */
377,	/* OBJ_rsaSignature                 1 3 14 3 2 11 */
67,	/* OBJ_dsa_2                        1 3 14 3 2 12 */
66,	/* OBJ_dsaWithSHA                   1 3 14 3 2 13 */
42,	/* OBJ_shaWithRSAEncryption         1 3 14 3 2 15 */
32,	/* OBJ_des_ede_ecb                  1 3 14 3 2 17 */
41,	/* OBJ_sha                          1 3 14 3 2 18 */
64,	/* OBJ_sha1                         1 3 14 3 2 26 */
70,	/* OBJ_dsaWithSHA1_2                1 3 14 3 2 27 */
115,	/* OBJ_sha1WithRSA                  1 3 14 3 2 29 */
117,	/* OBJ_ripemd160                    1 3 36 3 2 1 */
143,	/* OBJ_sxnet                        1 3 101 1 4 1 */
721,	/* OBJ_sect163k1                    1 3 132 0 1 */
722,	/* OBJ_sect163r1                    1 3 132 0 2 */
728,	/* OBJ_sect239k1                    1 3 132 0 3 */
717,	/* OBJ_sect113r1                    1 3 132 0 4 */
718,	/* OBJ_sect113r2                    1 3 132 0 5 */
704,	/* OBJ_secp112r1                    1 3 132 0 6 */
705,	/* OBJ_secp112r2                    1 3 132 0 7 */
709,	/* OBJ_secp160r1                    1 3 132 0 8 */
708,	/* OBJ_secp160k1                    1 3 132 0 9 */
714,	/* OBJ_secp256k1                    1 3 132 0 10 */
723,	/* OBJ_sect163r2                    1 3 132 0 15 */
729,	/* OBJ_sect283k1                    1 3 132 0 16 */
730,	/* OBJ_sect283r1                    1 3 132 0 17 */
719,	/* OBJ_sect131r1                    1 3 132 0 22 */
720,	/* OBJ_sect131r2                    1 3 132 0 23 */
724,	/* OBJ_sect193r1                    1 3 132 0 24 */
725,	/* OBJ_sect193r2                    1 3 132 0 25 */
726,	/* OBJ_sect233k1                    1 3 132 0 26 */
727,	/* OBJ_sect233r1                    1 3 132 0 27 */
706,	/* OBJ_secp128r1                    1 3 132 0 28 */
707,	/* OBJ_secp128r2                    1 3 132 0 29 */
710,	/* OBJ_secp160r2                    1 3 132 0 30 */
711,	/* OBJ_secp192k1                    1 3 132 0 31 */
712,	/* OBJ_secp224k1                    1 3 132 0 32 */
713,	/* OBJ_secp224r1                    1 3 132 0 33 */
715,	/* OBJ_secp384r1                    1 3 132 0 34 */
716,	/* OBJ_secp521r1                    1 3 132 0 35 */
731,	/* OBJ_sect409k1                    1 3 132 0 36 */
732,	/* OBJ_sect409r1                    1 3 132 0 37 */
733,	/* OBJ_sect571k1                    1 3 132 0 38 */
734,	/* OBJ_sect571r1                    1 3 132 0 39 */
624,	/* OBJ_set_rootKeyThumb             2 23 42 3 0 0 */
625,	/* OBJ_set_addPolicy                2 23 42 3 0 1 */
626,	/* OBJ_setAttr_Token_EMV            2 23 42 3 2 1 */
627,	/* OBJ_setAttr_Token_B0Prime        2 23 42 3 2 2 */
628,	/* OBJ_setAttr_IssCap_CVM           2 23 42 3 3 3 */
629,	/* OBJ_setAttr_IssCap_T2            2 23 42 3 3 4 */
630,	/* OBJ_setAttr_IssCap_Sig           2 23 42 3 3 5 */
642,	/* OBJ_set_brand_Novus              2 23 42 8 6011 */
735,	/* OBJ_wap_wsg_idm_ecid_wtls1       2 23 43 1 4 1 */
736,	/* OBJ_wap_wsg_idm_ecid_wtls3       2 23 43 1 4 3 */
737,	/* OBJ_wap_wsg_idm_ecid_wtls4       2 23 43 1 4 4 */
738,	/* OBJ_wap_wsg_idm_ecid_wtls5       2 23 43 1 4 5 */
739,	/* OBJ_wap_wsg_idm_ecid_wtls6       2 23 43 1 4 6 */
740,	/* OBJ_wap_wsg_idm_ecid_wtls7       2 23 43 1 4 7 */
741,	/* OBJ_wap_wsg_idm_ecid_wtls8       2 23 43 1 4 8 */
742,	/* OBJ_wap_wsg_idm_ecid_wtls9       2 23 43 1 4 9 */
743,	/* OBJ_wap_wsg_idm_ecid_wtls10      2 23 43 1 4 10 */
744,	/* OBJ_wap_wsg_idm_ecid_wtls11      2 23 43 1 4 11 */
745,	/* OBJ_wap_wsg_idm_ecid_wtls12      2 23 43 1 4 12 */
804,	/* OBJ_whirlpool                    1 0 10118 3 0 55 */
124,	/* OBJ_rle_compression              1 1 1 1 666 1 */
807,	/* OBJ_id_GostR3411_94_with_GostR3410_2001 1 2 643 2 2 3 */
808,	/* OBJ_id_GostR3411_94_with_GostR3410_94 1 2 643 2 2 4 */
809,	/* OBJ_id_GostR3411_94              1 2 643 2 2 9 */
810,	/* OBJ_id_HMACGostR3411_94          1 2 643 2 2 10 */
811,	/* OBJ_id_GostR3410_2001            1 2 643 2 2 19 */
812,	/* OBJ_id_GostR3410_94              1 2 643 2 2 20 */
813,	/* OBJ_id_Gost28147_89              1 2 643 2 2 21 */
815,	/* OBJ_id_Gost28147_89_MAC          1 2 643 2 2 22 */
816,	/* OBJ_id_GostR3411_94_prf          1 2 643 2 2 23 */
817,	/* OBJ_id_GostR3410_2001DH          1 2 643 2 2 98 */
818,	/* OBJ_id_GostR3410_94DH            1 2 643 2 2 99 */
 1,	/* OBJ_rsadsi                       1 2 840 113549 */
185,	/* OBJ_X9cm                         1 2 840 10040 4 */
127,	/* OBJ_id_pkix                      1 3 6 1 5 5 7 */
505,	/* OBJ_mime_mhs_headings            1 3 6 1 7 1 1 */
506,	/* OBJ_mime_mhs_bodies              1 3 6 1 7 1 2 */
119,	/* OBJ_ripemd160WithRSA             1 3 36 3 3 1 2 */
631,	/* OBJ_setAttr_GenCryptgrm          2 23 42 3 3 3 1 */
632,	/* OBJ_setAttr_T2Enc                2 23 42 3 3 4 1 */
633,	/* OBJ_setAttr_T2cleartxt           2 23 42 3 3 4 2 */
634,	/* OBJ_setAttr_TokICCsig            2 23 42 3 3 5 1 */
635,	/* OBJ_setAttr_SecDevSig            2 23 42 3 3 5 2 */
436,	/* OBJ_ucl                          0 9 2342 19200300 */
820,	/* OBJ_id_Gost28147_89_None_KeyMeshing 1 2 643 2 2 14 0 */
819,	/* OBJ_id_Gost28147_89_CryptoPro_KeyMeshing 1 2 643 2 2 14 1 */
845,	/* OBJ_id_GostR3410_94_a            1 2 643 2 2 20 1 */
846,	/* OBJ_id_GostR3410_94_aBis         1 2 643 2 2 20 2 */
847,	/* OBJ_id_GostR3410_94_b            1 2 643 2 2 20 3 */
848,	/* OBJ_id_GostR3410_94_bBis         1 2 643 2 2 20 4 */
821,	/* OBJ_id_GostR3411_94_TestParamSet 1 2 643 2 2 30 0 */
822,	/* OBJ_id_GostR3411_94_CryptoProParamSet 1 2 643 2 2 30 1 */
823,	/* OBJ_id_Gost28147_89_TestParamSet 1 2 643 2 2 31 0 */
824,	/* OBJ_id_Gost28147_89_CryptoPro_A_ParamSet 1 2 643 2 2 31 1 */
825,	/* OBJ_id_Gost28147_89_CryptoPro_B_ParamSet 1 2 643 2 2 31 2 */
826,	/* OBJ_id_Gost28147_89_CryptoPro_C_ParamSet 1 2 643 2 2 31 3 */
827,	/* OBJ_id_Gost28147_89_CryptoPro_D_ParamSet 1 2 643 2 2 31 4 */
828,	/* OBJ_id_Gost28147_89_CryptoPro_Oscar_1_1_ParamSet 1 2 643 2 2 31 5 */
829,	/* OBJ_id_Gost28147_89_CryptoPro_Oscar_1_0_ParamSet 1 2 643 2 2 31 6 */
830,	/* OBJ_id_Gost28147_89_CryptoPro_RIC_1_ParamSet 1 2 643 2 2 31 7 */
831,	/* OBJ_id_GostR3410_94_TestParamSet 1 2 643 2 2 32 0 */
832,	/* OBJ_id_GostR3410_94_CryptoPro_A_ParamSet 1 2 643 2 2 32 2 */
833,	/* OBJ_id_GostR3410_94_CryptoPro_B_ParamSet 1 2 643 2 2 32 3 */
834,	/* OBJ_id_GostR3410_94_CryptoPro_C_ParamSet 1 2 643 2 2 32 4 */
835,	/* OBJ_id_GostR3410_94_CryptoPro_D_ParamSet 1 2 643 2 2 32 5 */
836,	/* OBJ_id_GostR3410_94_CryptoPro_XchA_ParamSet 1 2 643 2 2 33 1 */
837,	/* OBJ_id_GostR3410_94_CryptoPro_XchB_ParamSet 1 2 643 2 2 33 2 */
838,	/* OBJ_id_GostR3410_94_CryptoPro_XchC_ParamSet 1 2 643 2 2 33 3 */
839,	/* OBJ_id_GostR3410_2001_TestParamSet 1 2 643 2 2 35 0 */
840,	/* OBJ_id_GostR3410_2001_CryptoPro_A_ParamSet 1 2 643 2 2 35 1 */
841,	/* OBJ_id_GostR3410_2001_CryptoPro_B_ParamSet 1 2 643 2 2 35 2 */
842,	/* OBJ_id_GostR3410_2001_CryptoPro_C_ParamSet 1 2 643 2 2 35 3 */
843,	/* OBJ_id_GostR3410_2001_CryptoPro_XchA_ParamSet 1 2 643 2 2 36 0 */
844,	/* OBJ_id_GostR3410_2001_CryptoPro_XchB_ParamSet 1 2 643 2 2 36 1 */
 2,	/* OBJ_pkcs                         1 2 840 113549 1 */
431,	/* OBJ_hold_instruction_none        1 2 840 10040 2 1 */
432,	/* OBJ_hold_instruction_call_issuer 1 2 840 10040 2 2 */
433,	/* OBJ_hold_instruction_reject      1 2 840 10040 2 3 */
116,	/* OBJ_dsa                          1 2 840 10040 4 1 */
113,	/* OBJ_dsaWithSHA1                  1 2 840 10040 4 3 */
406,	/* OBJ_X9_62_prime_field            1 2 840 10045 1 1 */
407,	/* OBJ_X9_62_characteristic_two_field 1 2 840 10045 1 2 */
408,	/* OBJ_X9_62_id_ecPublicKey         1 2 840 10045 2 1 */
416,	/* OBJ_ecdsa_with_SHA1              1 2 840 10045 4 1 */
791,	/* OBJ_ecdsa_with_Recommended       1 2 840 10045 4 2 */
792,	/* OBJ_ecdsa_with_Specified         1 2 840 10045 4 3 */
258,	/* OBJ_id_pkix_mod                  1 3 6 1 5 5 7 0 */
175,	/* OBJ_id_pe                        1 3 6 1 5 5 7 1 */
259,	/* OBJ_id_qt                        1 3 6 1 5 5 7 2 */
128,	/* OBJ_id_kp                        1 3 6 1 5 5 7 3 */
260,	/* OBJ_id_it                        1 3 6 1 5 5 7 4 */
261,	/* OBJ_id_pkip                      1 3 6 1 5 5 7 5 */
262,	/* OBJ_id_alg                       1 3 6 1 5 5 7 6 */
263,	/* OBJ_id_cmc                       1 3 6 1 5 5 7 7 */
264,	/* OBJ_id_on                        1 3 6 1 5 5 7 8 */
265,	/* OBJ_id_pda                       1 3 6 1 5 5 7 9 */
266,	/* OBJ_id_aca                       1 3 6 1 5 5 7 10 */
267,	/* OBJ_id_qcs                       1 3 6 1 5 5 7 11 */
268,	/* OBJ_id_cct                       1 3 6 1 5 5 7 12 */
662,	/* OBJ_id_ppl                       1 3 6 1 5 5 7 21 */
176,	/* OBJ_id_ad                        1 3 6 1 5 5 7 48 */
507,	/* OBJ_id_hex_partial_message       1 3 6 1 7 1 1 1 */
508,	/* OBJ_id_hex_multipart_message     1 3 6 1 7 1 1 2 */
922,	/* OBJ_brainpool                    1 3 36 3 3 2 8 1 */
57,	/* OBJ_netscape                     2 16 840 1 113730 */
754,	/* OBJ_camellia_128_ecb             0 3 4401 5 3 1 9 1 */
766,	/* OBJ_camellia_128_ofb128          0 3 4401 5 3 1 9 3 */
757,	/* OBJ_camellia_128_cfb128          0 3 4401 5 3 1 9 4 */
755,	/* OBJ_camellia_192_ecb             0 3 4401 5 3 1 9 21 */
767,	/* OBJ_camellia_192_ofb128          0 3 4401 5 3 1 9 23 */
758,	/* OBJ_camellia_192_cfb128          0 3 4401 5 3 1 9 24 */
756,	/* OBJ_camellia_256_ecb             0 3 4401 5 3 1 9 41 */
768,	/* OBJ_camellia_256_ofb128          0 3 4401 5 3 1 9 43 */
759,	/* OBJ_camellia_256_cfb128          0 3 4401 5 3 1 9 44 */
437,	/* OBJ_pilot                        0 9 2342 19200300 100 */
852,	/* OBJ_id_GostR3411_94_with_GostR3410_94_cc 1 2 643 2 9 1 3 3 */
853,	/* OBJ_id_GostR3411_94_with_GostR3410_2001_cc 1 2 643 2 9 1 3 4 */
850,	/* OBJ_id_GostR3410_94_cc           1 2 643 2 9 1 5 3 */
851,	/* OBJ_id_GostR3410_2001_cc         1 2 643 2 9 1 5 4 */
849,	/* OBJ_id_Gost28147_89_cc           1 2 643 2 9 1 6 1 */
854,	/* OBJ_id_GostR3410_2001_ParamSet_cc 1 2 643 2 9 1 8 1 */
945,	/* OBJ_id_tc26_gost3410_2012_256    1 2 643 7 1 1 1 1 */
946,	/* OBJ_id_tc26_gost3410_2012_512    1 2 643 7 1 1 1 2 */
940,	/* OBJ_id_tc26_gost3411_2012_256    1 2 643 7 1 1 2 2 */
941,	/* OBJ_id_tc26_gost3411_2012_512    1 2 643 7 1 1 2 3 */
947,	/* OBJ_id_tc26_signwithdigest_gost3410_2012_256 1 2 643 7 1 1 3 2 */
948,	/* OBJ_id_tc26_signwithdigest_gost3410_2012_512 1 2 643 7 1 1 3 3 */
186,	/* OBJ_pkcs1                        1 2 840 113549 1 1 */
27,	/* OBJ_pkcs3                        1 2 840 113549 1 3 */
187,	/* OBJ_pkcs5                        1 2 840 113549 1 5 */
20,	/* OBJ_pkcs7                        1 2 840 113549 1 7 */
47,	/* OBJ_pkcs9                        1 2 840 113549 1 9 */
 4,	/* OBJ_md5                          1 2 840 113549 2 5 */
797,	/* OBJ_hmacWithMD5                  1 2 840 113549 2 6 */
163,	/* OBJ_hmacWithSHA1                 1 2 840 113549 2 7 */
798,	/* OBJ_hmacWithSHA224               1 2 840 113549 2 8 */
799,	/* OBJ_hmacWithSHA256               1 2 840 113549 2 9 */
800,	/* OBJ_hmacWithSHA384               1 2 840 113549 2 10 */
801,	/* OBJ_hmacWithSHA512               1 2 840 113549 2 11 */
37,	/* OBJ_rc2_cbc                      1 2 840 113549 3 2 */
 5,	/* OBJ_rc4                          1 2 840 113549 3 4 */
44,	/* OBJ_des_ede3_cbc                 1 2 840 113549 3 7 */
120,	/* OBJ_rc5_cbc                      1 2 840 113549 3 8 */
643,	/* OBJ_des_cdmf                     1 2 840 113549 3 10 */
680,	/* OBJ_X9_62_id_characteristic_two_basis 1 2 840 10045 1 2 3 */
684,	/* OBJ_X9_62_c2pnb163v1             1 2 840 10045 3 0 1 */
685,	/* OBJ_X9_62_c2pnb163v2             1 2 840 10045 3 0 2 */
686,	/* OBJ_X9_62_c2pnb163v3             1 2 840 10045 3 0 3 */
687,	/* OBJ_X9_62_c2pnb176v1             1 2 840 10045 3 0 4 */
688,	/* OBJ_X9_62_c2tnb191v1             1 2 840 10045 3 0 5 */
689,	/* OBJ_X9_62_c2tnb191v2             1 2 840 10045 3 0 6 */
690,	/* OBJ_X9_62_c2tnb191v3             1 2 840 10045 3 0 7 */
691,	/* OBJ_X9_62_c2onb191v4             1 2 840 10045 3 0 8 */
692,	/* OBJ_X9_62_c2onb191v5             1 2 840 10045 3 0 9 */
693,	/* OBJ_X9_62_c2pnb208w1             1 2 840 10045 3 0 10 */
694,	/* OBJ_X9_62_c2tnb239v1             1 2 840 10045 3 0 11 */
695,	/* OBJ_X9_62_c2tnb239v2             1 2 840 10045 3 0 12 */
696,	/* OBJ_X9_62_c2tnb239v3             1 2 840 10045 3 0 13 */
697,	/* OBJ_X9_62_c2onb239v4             1 2 840 10045 3 0 14 */
698,	/* OBJ_X9_62_c2onb239v5             1 2 840 10045 3 0 15 */
699,	/* OBJ_X9_62_c2pnb272w1             1 2 840 10045 3 0 16 */
700,	/* OBJ_X9_62_c2pnb304w1             1 2 840 10045 3 0 17 */
701,	/* OBJ_X9_62_c2tnb359v1             1 2 840 10045 3 0 18 */
702,	/* OBJ_X9_62_c2pnb368w1             1 2 840 10045 3 0 19 */
703,	/* OBJ_X9_62_c2tnb431r1             1 2 840 10045 3 0 20 */
409,	/* OBJ_X9_62_prime192v1             1 2 840 10045 3 1 1 */
410,	/* OBJ_X9_62_prime192v2             1 2 840 10045 3 1 2 */
411,	/* OBJ_X9_62_prime192v3             1 2 840 10045 3 1 3 */
412,	/* OBJ_X9_62_prime239v1             1 2 840 10045 3 1 4 */
413,	/* OBJ_X9_62_prime239v2             1 2 840 10045 3 1 5 */
414,	/* OBJ_X9_62_prime239v3             1 2 840 10045 3 1 6 */
415,	/* OBJ_X9_62_prime256v1             1 2 840 10045 3 1 7 */
793,	/* OBJ_ecdsa_with_SHA224            1 2 840 10045 4 3 1 */
794,	/* OBJ_ecdsa_with_SHA256            1 2 840 10045 4 3 2 */
795,	/* OBJ_ecdsa_with_SHA384            1 2 840 10045 4 3 3 */
796,	/* OBJ_ecdsa_with_SHA512            1 2 840 10045 4 3 4 */
269,	/* OBJ_id_pkix1_explicit_88         1 3 6 1 5 5 7 0 1 */
270,	/* OBJ_id_pkix1_implicit_88         1 3 6 1 5 5 7 0 2 */
271,	/* OBJ_id_pkix1_explicit_93         1 3 6 1 5 5 7 0 3 */
272,	/* OBJ_id_pkix1_implicit_93         1 3 6 1 5 5 7 0 4 */
273,	/* OBJ_id_mod_crmf                  1 3 6 1 5 5 7 0 5 */
274,	/* OBJ_id_mod_cmc                   1 3 6 1 5 5 7 0 6 */
275,	/* OBJ_id_mod_kea_profile_88        1 3 6 1 5 5 7 0 7 */
276,	/* OBJ_id_mod_kea_profile_93        1 3 6 1 5 5 7 0 8 */
277,	/* OBJ_id_mod_cmp                   1 3 6 1 5 5 7 0 9 */
278,	/* OBJ_id_mod_qualified_cert_88     1 3 6 1 5 5 7 0 10 */
279,	/* OBJ_id_mod_qualified_cert_93     1 3 6 1 5 5 7 0 11 */
280,	/* OBJ_id_mod_attribute_cert        1 3 6 1 5 5 7 0 12 */
281,	/* OBJ_id_mod_timestamp_protocol    1 3 6 1 5 5 7 0 13 */
282,	/* OBJ_id_mod_ocsp                  1 3 6 1 5 5 7 0 14 */
283,	/* OBJ_id_mod_dvcs                  1 3 6 1 5 5 7 0 15 */
284,	/* OBJ_id_mod_cmp2000               1 3 6 1 5 5 7 0 16 */
177,	/* OBJ_info_access                  1 3 6 1 5 5 7 1 1 */
285,	/* OBJ_biometricInfo                1 3 6 1 5 5 7 1 2 */
286,	/* OBJ_qcStatements                 1 3 6 1 5 5 7 1 3 */
287,	/* OBJ_ac_auditEntity               1 3 6 1 5 5 7 1 4 */
288,	/* OBJ_ac_targeting                 1 3 6 1 5 5 7 1 5 */
289,	/* OBJ_aaControls                   1 3 6 1 5 5 7 1 6 */
290,	/* OBJ_sbgp_ipAddrBlock             1 3 6 1 5 5 7 1 7 */
291,	/* OBJ_sbgp_autonomousSysNum        1 3 6 1 5 5 7 1 8 */
292,	/* OBJ_sbgp_routerIdentifier        1 3 6 1 5 5 7 1 9 */
397,	/* OBJ_ac_proxying                  1 3 6 1 5 5 7 1 10 */
398,	/* OBJ_sinfo_access                 1 3 6 1 5 5 7 1 11 */
663,	/* OBJ_proxyCertInfo                1 3 6 1 5 5 7 1 14 */
164,	/* OBJ_id_qt_cps                    1 3 6 1 5 5 7 2 1 */
165,	/* OBJ_id_qt_unotice                1 3 6 1 5 5 7 2 2 */
293,	/* OBJ_textNotice                   1 3 6 1 5 5 7 2 3 */
129,	/* OBJ_server_auth                  1 3 6 1 5 5 7 3 1 */
130,	/* OBJ_client_auth                  1 3 6 1 5 5 7 3 2 */
131,	/* OBJ_code_sign                    1 3 6 1 5 5 7 3 3 */
132,	/* OBJ_email_protect                1 3 6 1 5 5 7 3 4 */
294,	/* OBJ_ipsecEndSystem               1 3 6 1 5 5 7 3 5 */
295,	/* OBJ_ipsecTunnel                  1 3 6 1 5 5 7 3 6 */
296,	/* OBJ_ipsecUser                    1 3 6 1 5 5 7 3 7 */
133,	/* OBJ_time_stamp                   1 3 6 1 5 5 7 3 8 */
180,	/* OBJ_OCSP_sign                    1 3 6 1 5 5 7 3 9 */
297,	/* OBJ_dvcs                         1 3 6 1 5 5 7 3 10 */
298,	/* OBJ_id_it_caProtEncCert          1 3 6 1 5 5 7 4 1 */
299,	/* OBJ_id_it_signKeyPairTypes       1 3 6 1 5 5 7 4 2 */
300,	/* OBJ_id_it_encKeyPairTypes        1 3 6 1 5 5 7 4 3 */
301,	/* OBJ_id_it_preferredSymmAlg       1 3 6 1 5 5 7 4 4 */
302,	/* OBJ_id_it_caKeyUpdateInfo        1 3 6 1 5 5 7 4 5 */
303,	/* OBJ_id_it_currentCRL             1 3 6 1 5 5 7 4 6 */
304,	/* OBJ_id_it_unsupportedOIDs        1 3 6 1 5 5 7 4 7 */
305,	/* OBJ_id_it_subscriptionRequest    1 3 6 1 5 5 7 4 8 */
306,	/* OBJ_id_it_subscriptionResponse   1 3 6 1 5 5 7 4 9 */
307,	/* OBJ_id_it_keyPairParamReq        1 3 6 1 5 5 7 4 10 */
308,	/* OBJ_id_it_keyPairParamRep        1 3 6 1 5 5 7 4 11 */
309,	/* OBJ_id_it_revPassphrase          1 3 6 1 5 5 7 4 12 */
310,	/* OBJ_id_it_implicitConfirm        1 3 6 1 5 5 7 4 13 */
311,	/* OBJ_id_it_confirmWaitTime        1 3 6 1 5 5 7 4 14 */
312,	/* OBJ_id_it_origPKIMessage         1 3 6 1 5 5 7 4 15 */
784,	/* OBJ_id_it_suppLangTags           1 3 6 1 5 5 7 4 16 */
313,	/* OBJ_id_regCtrl                   1 3 6 1 5 5 7 5 1 */
314,	/* OBJ_id_regInfo                   1 3 6 1 5 5 7 5 2 */
323,	/* OBJ_id_alg_des40                 1 3 6 1 5 5 7 6 1 */
324,	/* OBJ_id_alg_noSignature           1 3 6 1 5 5 7 6 2 */
325,	/* OBJ_id_alg_dh_sig_hmac_sha1      1 3 6 1 5 5 7 6 3 */
326,	/* OBJ_id_alg_dh_pop                1 3 6 1 5 5 7 6 4 */
327,	/* OBJ_id_cmc_statusInfo            1 3 6 1 5 5 7 7 1 */
328,	/* OBJ_id_cmc_identification        1 3 6 1 5 5 7 7 2 */
329,	/* OBJ_id_cmc_identityProof         1 3 6 1 5 5 7 7 3 */
330,	/* OBJ_id_cmc_dataReturn            1 3 6 1 5 5 7 7 4 */
331,	/* OBJ_id_cmc_transactionId         1 3 6 1 5 5 7 7 5 */
332,	/* OBJ_id_cmc_senderNonce           1 3 6 1 5 5 7 7 6 */
333,	/* OBJ_id_cmc_recipientNonce        1 3 6 1 5 5 7 7 7 */
334,	/* OBJ_id_cmc_addExtensions         1 3 6 1 5 5 7 7 8 */
335,	/* OBJ_id_cmc_encryptedPOP          1 3 6 1 5 5 7 7 9 */
336,	/* OBJ_id_cmc_decryptedPOP          1 3 6 1 5 5 7 7 10 */
337,	/* OBJ_id_cmc_lraPOPWitness         1 3 6 1 5 5 7 7 11 */
338,	/* OBJ_id_cmc_getCert               1 3 6 1 5 5 7 7 15 */
339,	/* OBJ_id_cmc_getCRL                1 3 6 1 5 5 7 7 16 */
340,	/* OBJ_id_cmc_revokeRequest         1 3 6 1 5 5 7 7 17 */
341,	/* OBJ_id_cmc_regInfo               1 3 6 1 5 5 7 7 18 */
342,	/* OBJ_id_cmc_responseInfo          1 3 6 1 5 5 7 7 19 */
343,	/* OBJ_id_cmc_queryPending          1 3 6 1 5 5 7 7 21 */
344,	/* OBJ_id_cmc_popLinkRandom         1 3 6 1 5 5 7 7 22 */
345,	/* OBJ_id_cmc_popLinkWitness        1 3 6 1 5 5 7 7 23 */
346,	/* OBJ_id_cmc_confirmCertAcceptance 1 3 6 1 5 5 7 7 24 */
347,	/* OBJ_id_on_personalData           1 3 6 1 5 5 7 8 1 */
858,	/* OBJ_id_on_permanentIdentifier    1 3 6 1 5 5 7 8 3 */
348,	/* OBJ_id_pda_dateOfBirth           1 3 6 1 5 5 7 9 1 */
349,	/* OBJ_id_pda_placeOfBirth          1 3 6 1 5 5 7 9 2 */
351,	/* OBJ_id_pda_gender                1 3 6 1 5 5 7 9 3 */
352,	/* OBJ_id_pda_countryOfCitizenship  1 3 6 1 5 5 7 9 4 */
353,	/* OBJ_id_pda_countryOfResidence    1 3 6 1 5 5 7 9 5 */
354,	/* OBJ_id_aca_authenticationInfo    1 3 6 1 5 5 7 10 1 */
355,	/* OBJ_id_aca_accessIdentity        1 3 6 1 5 5 7 10 2 */
356,	/* OBJ_id_aca_chargingIdentity      1 3 6 1 5 5 7 10 3 */
357,	/* OBJ_id_aca_group                 1 3 6 1 5 5 7 10 4 */
358,	/* OBJ_id_aca_role                  1 3 6 1 5 5 7 10 5 */
399,	/* OBJ_id_aca_encAttrs              1 3 6 1 5 5 7 10 6 */
359,	/* OBJ_id_qcs_pkixQCSyntax_v1       1 3 6 1 5 5 7 11 1 */
360,	/* OBJ_id_cct_crs                   1 3 6 1 5 5 7 12 1 */
361,	/* OBJ_id_cct_PKIData               1 3 6 1 5 5 7 12 2 */
362,	/* OBJ_id_cct_PKIResponse           1 3 6 1 5 5 7 12 3 */
664,	/* OBJ_id_ppl_anyLanguage           1 3 6 1 5 5 7 21 0 */
665,	/* OBJ_id_ppl_inheritAll            1 3 6 1 5 5 7 21 1 */
667,	/* OBJ_Independent                  1 3 6 1 5 5 7 21 2 */
178,	/* OBJ_ad_OCSP                      1 3 6 1 5 5 7 48 1 */
179,	/* OBJ_ad_ca_issuers                1 3 6 1 5 5 7 48 2 */
363,	/* OBJ_ad_timeStamping              1 3 6 1 5 5 7 48 3 */
364,	/* OBJ_ad_dvcs                      1 3 6 1 5 5 7 48 4 */
785,	/* OBJ_caRepository                 1 3 6 1 5 5 7 48 5 */
780,	/* OBJ_hmac_md5                     1 3 6 1 5 5 8 1 1 */
781,	/* OBJ_hmac_sha1                    1 3 6 1 5 5 8 1 2 */
58,	/* OBJ_netscape_cert_extension      2 16 840 1 113730 1 */
59,	/* OBJ_netscape_data_type           2 16 840 1 113730 2 */
438,	/* OBJ_pilotAttributeType           0 9 2342 19200300 100 1 */
439,	/* OBJ_pilotAttributeSyntax         0 9 2342 19200300 100 3 */
440,	/* OBJ_pilotObjectClass             0 9 2342 19200300 100 4 */
441,	/* OBJ_pilotGroups                  0 9 2342 19200300 100 10 */
942,	/* OBJ_id_tc26_gost_3410_2012_512_paramSetA 1 2 643 7 1 2 1 2 1 */
943,	/* OBJ_id_tc26_gost_3410_2012_512_paramSetB 1 2 643 7 1 2 1 2 2 */
944,	/* OBJ_id_tc26_gost_28147_param_Z   1 2 643 7 1 2 5 1 1 */
108,	/* OBJ_cast5_cbc                    1 2 840 113533 7 66 10 */
112,	/* OBJ_pbeWithMD5AndCast5_CBC       1 2 840 113533 7 66 12 */
782,	/* OBJ_id_PasswordBasedMAC          1 2 840 113533 7 66 13 */
783,	/* OBJ_id_DHBasedMac                1 2 840 113533 7 66 30 */
 6,	/* OBJ_rsaEncryption                1 2 840 113549 1 1 1 */
 8,	/* OBJ_md5WithRSAEncryption         1 2 840 113549 1 1 4 */
65,	/* OBJ_sha1WithRSAEncryption        1 2 840 113549 1 1 5 */
644,	/* OBJ_rsaOAEPEncryptionSET         1 2 840 113549 1 1 6 */
919,	/* OBJ_rsaesOaep                    1 2 840 113549 1 1 7 */
911,	/* OBJ_mgf1                         1 2 840 113549 1 1 8 */
912,	/* OBJ_rsassaPss                    1 2 840 113549 1 1 10 */
668,	/* OBJ_sha256WithRSAEncryption      1 2 840 113549 1 1 11 */
669,	/* OBJ_sha384WithRSAEncryption      1 2 840 113549 1 1 12 */
670,	/* OBJ_sha512WithRSAEncryption      1 2 840 113549 1 1 13 */
671,	/* OBJ_sha224WithRSAEncryption      1 2 840 113549 1 1 14 */
28,	/* OBJ_dhKeyAgreement               1 2 840 113549 1 3 1 */
10,	/* OBJ_pbeWithMD5AndDES_CBC         1 2 840 113549 1 5 3 */
169,	/* OBJ_pbeWithMD5AndRC2_CBC         1 2 840 113549 1 5 6 */
170,	/* OBJ_pbeWithSHA1AndDES_CBC        1 2 840 113549 1 5 10 */
68,	/* OBJ_pbeWithSHA1AndRC2_CBC        1 2 840 113549 1 5 11 */
69,	/* OBJ_id_pbkdf2                    1 2 840 113549 1 5 12 */
161,	/* OBJ_pbes2                        1 2 840 113549 1 5 13 */
162,	/* OBJ_pbmac1                       1 2 840 113549 1 5 14 */
21,	/* OBJ_pkcs7_data                   1 2 840 113549 1 7 1 */
22,	/* OBJ_pkcs7_signed                 1 2 840 113549 1 7 2 */
23,	/* OBJ_pkcs7_enveloped              1 2 840 113549 1 7 3 */
24,	/* OBJ_pkcs7_signedAndEnveloped     1 2 840 113549 1 7 4 */
25,	/* OBJ_pkcs7_digest                 1 2 840 113549 1 7 5 */
26,	/* OBJ_pkcs7_encrypted              1 2 840 113549 1 7 6 */
48,	/* OBJ_pkcs9_emailAddress           1 2 840 113549 1 9 1 */
49,	/* OBJ_pkcs9_unstructuredName       1 2 840 113549 1 9 2 */
50,	/* OBJ_pkcs9_contentType            1 2 840 113549 1 9 3 */
51,	/* OBJ_pkcs9_messageDigest          1 2 840 113549 1 9 4 */
52,	/* OBJ_pkcs9_signingTime            1 2 840 113549 1 9 5 */
53,	/* OBJ_pkcs9_countersignature       1 2 840 113549 1 9 6 */
54,	/* OBJ_pkcs9_challengePassword      1 2 840 113549 1 9 7 */
55,	/* OBJ_pkcs9_unstructuredAddress    1 2 840 113549 1 9 8 */
56,	/* OBJ_pkcs9_extCertAttributes      1 2 840 113549 1 9 9 */
172,	/* OBJ_ext_req                      1 2 840 113549 1 9 14 */
167,	/* OBJ_SMIMECapabilities            1 2 840 113549 1 9 15 */
188,	/* OBJ_SMIME                        1 2 840 113549 1 9 16 */
156,	/* OBJ_friendlyName                 1 2 840 113549 1 9 20 */
157,	/* OBJ_localKeyID                   1 2 840 113549 1 9 21 */
681,	/* OBJ_X9_62_onBasis                1 2 840 10045 1 2 3 1 */
682,	/* OBJ_X9_62_tpBasis                1 2 840 10045 1 2 3 2 */
683,	/* OBJ_X9_62_ppBasis                1 2 840 10045 1 2 3 3 */
417,	/* OBJ_ms_csp_name                  1 3 6 1 4 1 311 17 1 */
856,	/* OBJ_LocalKeySet                  1 3 6 1 4 1 311 17 2 */
390,	/* OBJ_dcObject                     1 3 6 1 4 1 1466 344 */
91,	/* OBJ_bf_cbc                       1 3 6 1 4 1 3029 1 2 */
315,	/* OBJ_id_regCtrl_regToken          1 3 6 1 5 5 7 5 1 1 */
316,	/* OBJ_id_regCtrl_authenticator     1 3 6 1 5 5 7 5 1 2 */
317,	/* OBJ_id_regCtrl_pkiPublicationInfo 1 3 6 1 5 5 7 5 1 3 */
318,	/* OBJ_id_regCtrl_pkiArchiveOptions 1 3 6 1 5 5 7 5 1 4 */
319,	/* OBJ_id_regCtrl_oldCertID         1 3 6 1 5 5 7 5 1 5 */
320,	/* OBJ_id_regCtrl_protocolEncrKey   1 3 6 1 5 5 7 5 1 6 */
321,	/* OBJ_id_regInfo_utf8Pairs         1 3 6 1 5 5 7 5 2 1 */
322,	/* OBJ_id_regInfo_certReq           1 3 6 1 5 5 7 5 2 2 */
365,	/* OBJ_id_pkix_OCSP_basic           1 3 6 1 5 5 7 48 1 1 */
366,	/* OBJ_id_pkix_OCSP_Nonce           1 3 6 1 5 5 7 48 1 2 */
367,	/* OBJ_id_pkix_OCSP_CrlID           1 3 6 1 5 5 7 48 1 3 */
368,	/* OBJ_id_pkix_OCSP_acceptableResponses 1 3 6 1 5 5 7 48 1 4 */
369,	/* OBJ_id_pkix_OCSP_noCheck         1 3 6 1 5 5 7 48 1 5 */
370,	/* OBJ_id_pkix_OCSP_archiveCutoff   1 3 6 1 5 5 7 48 1 6 */
371,	/* OBJ_id_pkix_OCSP_serviceLocator  1 3 6 1 5 5 7 48 1 7 */
372,	/* OBJ_id_pkix_OCSP_extendedStatus  1 3 6 1 5 5 7 48 1 8 */
373,	/* OBJ_id_pkix_OCSP_valid           1 3 6 1 5 5 7 48 1 9 */
374,	/* OBJ_id_pkix_OCSP_path            1 3 6 1 5 5 7 48 1 10 */
375,	/* OBJ_id_pkix_OCSP_trustRoot       1 3 6 1 5 5 7 48 1 11 */
923,	/* OBJ_brainpoolP160r1              1 3 36 3 3 2 8 1 1 1 */
924,	/* OBJ_brainpoolP160t1              1 3 36 3 3 2 8 1 1 2 */
925,	/* OBJ_brainpoolP192r1              1 3 36 3 3 2 8 1 1 3 */
926,	/* OBJ_brainpoolP192t1              1 3 36 3 3 2 8 1 1 4 */
927,	/* OBJ_brainpoolP224r1              1 3 36 3 3 2 8 1 1 5 */
928,	/* OBJ_brainpoolP224t1              1 3 36 3 3 2 8 1 1 6 */
929,	/* OBJ_brainpoolP256r1              1 3 36 3 3 2 8 1 1 7 */
930,	/* OBJ_brainpoolP256t1              1 3 36 3 3 2 8 1 1 8 */
931,	/* OBJ_brainpoolP320r1              1 3 36 3 3 2 8 1 1 9 */
932,	/* OBJ_brainpoolP320t1              1 3 36 3 3 2 8 1 1 10 */
933,	/* OBJ_brainpoolP384r1              1 3 36 3 3 2 8 1 1 11 */
934,	/* OBJ_brainpoolP384t1              1 3 36 3 3 2 8 1 1 12 */
935,	/* OBJ_brainpoolP512r1              1 3 36 3 3 2 8 1 1 13 */
936,	/* OBJ_brainpoolP512t1              1 3 36 3 3 2 8 1 1 14 */
418,	/* OBJ_aes_128_ecb                  2 16 840 1 101 3 4 1 1 */
419,	/* OBJ_aes_128_cbc                  2 16 840 1 101 3 4 1 2 */
420,	/* OBJ_aes_128_ofb128               2 16 840 1 101 3 4 1 3 */
421,	/* OBJ_aes_128_cfb128               2 16 840 1 101 3 4 1 4 */
788,	/* OBJ_id_aes128_wrap               2 16 840 1 101 3 4 1 5 */
895,	/* OBJ_aes_128_gcm                  2 16 840 1 101 3 4 1 6 */
896,	/* OBJ_aes_128_ccm                  2 16 840 1 101 3 4 1 7 */
897,	/* OBJ_id_aes128_wrap_pad           2 16 840 1 101 3 4 1 8 */
422,	/* OBJ_aes_192_ecb                  2 16 840 1 101 3 4 1 21 */
423,	/* OBJ_aes_192_cbc                  2 16 840 1 101 3 4 1 22 */
424,	/* OBJ_aes_192_ofb128               2 16 840 1 101 3 4 1 23 */
425,	/* OBJ_aes_192_cfb128               2 16 840 1 101 3 4 1 24 */
789,	/* OBJ_id_aes192_wrap               2 16 840 1 101 3 4 1 25 */
898,	/* OBJ_aes_192_gcm                  2 16 840 1 101 3 4 1 26 */
899,	/* OBJ_aes_192_ccm                  2 16 840 1 101 3 4 1 27 */
900,	/* OBJ_id_aes192_wrap_pad           2 16 840 1 101 3 4 1 28 */
426,	/* OBJ_aes_256_ecb                  2 16 840 1 101 3 4 1 41 */
427,	/* OBJ_aes_256_cbc                  2 16 840 1 101 3 4 1 42 */
428,	/* OBJ_aes_256_ofb128               2 16 840 1 101 3 4 1 43 */
429,	/* OBJ_aes_256_cfb128               2 16 840 1 101 3 4 1 44 */
790,	/* OBJ_id_aes256_wrap               2 16 840 1 101 3 4 1 45 */
901,	/* OBJ_aes_256_gcm                  2 16 840 1 101 3 4 1 46 */
902,	/* OBJ_aes_256_ccm                  2 16 840 1 101 3 4 1 47 */
903,	/* OBJ_id_aes256_wrap_pad           2 16 840 1 101 3 4 1 48 */
672,	/* OBJ_sha256                       2 16 840 1 101 3 4 2 1 */
673,	/* OBJ_sha384                       2 16 840 1 101 3 4 2 2 */
674,	/* OBJ_sha512                       2 16 840 1 101 3 4 2 3 */
675,	/* OBJ_sha224                       2 16 840 1 101 3 4 2 4 */
802,	/* OBJ_dsa_with_SHA224              2 16 840 1 101 3 4 3 1 */
803,	/* OBJ_dsa_with_SHA256              2 16 840 1 101 3 4 3 2 */
71,	/* OBJ_netscape_cert_type           2 16 840 1 113730 1 1 */
72,	/* OBJ_netscape_base_url            2 16 840 1 113730 1 2 */
73,	/* OBJ_netscape_revocation_url      2 16 840 1 113730 1 3 */
74,	/* OBJ_netscape_ca_revocation_url   2 16 840 1 113730 1 4 */
75,	/* OBJ_netscape_renewal_url         2 16 840 1 113730 1 7 */
76,	/* OBJ_netscape_ca_policy_url       2 16 840 1 113730 1 8 */
77,	/* OBJ_netscape_ssl_server_name     2 16 840 1 113730 1 12 */
78,	/* OBJ_netscape_comment             2 16 840 1 113730 1 13 */
79,	/* OBJ_netscape_cert_sequence       2 16 840 1 113730 2 5 */
139,	/* OBJ_ns_sgc                       2 16 840 1 113730 4 1 */
458,	/* OBJ_userId                       0 9 2342 19200300 100 1 1 */
459,	/* OBJ_textEncodedORAddress         0 9 2342 19200300 100 1 2 */
460,	/* OBJ_rfc822Mailbox                0 9 2342 19200300 100 1 3 */
461,	/* OBJ_info                         0 9 2342 19200300 100 1 4 */
462,	/* OBJ_favouriteDrink               0 9 2342 19200300 100 1 5 */
463,	/* OBJ_roomNumber                   0 9 2342 19200300 100 1 6 */
464,	/* OBJ_photo                        0 9 2342 19200300 100 1 7 */
465,	/* OBJ_userClass                    0 9 2342 19200300 100 1 8 */
466,	/* OBJ_host                         0 9 2342 19200300 100 1 9 */
467,	/* OBJ_manager                      0 9 2342 19200300 100 1 10 */
468,	/* OBJ_documentIdentifier           0 9 2342 19200300 100 1 11 */
469,	/* OBJ_documentTitle                0 9 2342 19200300 100 1 12 */
470,	/* OBJ_documentVersion              0 9 2342 19200300 100 1 13 */
471,	/* OBJ_documentAuthor               0 9 2342 19200300 100 1 14 */
472,	/* OBJ_documentLocation             0 9 2342 19200300 100 1 15 */
473,	/* OBJ_homeTelephoneNumber          0 9 2342 19200300 100 1 20 */
474,	/* OBJ_secretary                    0 9 2342 19200300 100 1 21 */
475,	/* OBJ_otherMailbox                 0 9 2342 19200300 100 1 22 */
476,	/* OBJ_lastModifiedTime             0 9 2342 19200300 100 1 23 */
477,	/* OBJ_lastModifiedBy               0 9 2342 19200300 100 1 24 */
391,	/* OBJ_domainComponent              0 9 2342 19200300 100 1 25 */
478,	/* OBJ_aRecord                      0 9 2342 19200300 100 1 26 */
479,	/* OBJ_pilotAttributeType27         0 9 2342 19200300 100 1 27 */
480,	/* OBJ_mXRecord                     0 9 2342 19200300 100 1 28 */
481,	/* OBJ_nSRecord                     0 9 2342 19200300 100 1 29 */
482,	/* OBJ_sOARecord                    0 9 2342 19200300 100 1 30 */
483,	/* OBJ_cNAMERecord                  0 9 2342 19200300 100 1 31 */
484,	/* OBJ_associatedDomain             0 9 2342 19200300 100 1 37 */
485,	/* OBJ_associatedName               0 9 2342 19200300 100 1 38 */
486,	/* OBJ_homePostalAddress            0 9 2342 19200300 100 1 39 */
487,	/* OBJ_personalTitle                0 9 2342 19200300 100 1 40 */
488,	/* OBJ_mobileTelephoneNumber        0 9 2342 19200300 100 1 41 */
489,	/* OBJ_pagerTelephoneNumber         0 9 2342 19200300 100 1 42 */
490,	/* OBJ_friendlyCountryName          0 9 2342 19200300 100 1 43 */
491,	/* OBJ_organizationalStatus         0 9 2342 19200300 100 1 45 */
492,	/* OBJ_janetMailbox                 0 9 2342 19200300 100 1 46 */
493,	/* OBJ_mailPreferenceOption         0 9 2342 19200300 100 1 47 */
494,	/* OBJ_buildingName                 0 9 2342 19200300 100 1 48 */
495,	/* OBJ_dSAQuality                   0 9 2342 19200300 100 1 49 */
496,	/* OBJ_singleLevelQuality           0 9 2342 19200300 100 1 50 */
497,	/* OBJ_subtreeMinimumQuality        0 9 2342 19200300 100 1 51 */
498,	/* OBJ_subtreeMaximumQuality        0 9 2342 19200300 100 1 52 */
499,	/* OBJ_personalSignature            0 9 2342 19200300 100 1 53 */
500,	/* OBJ_dITRedirect                  0 9 2342 19200300 100 1 54 */
501,	/* OBJ_audio                        0 9 2342 19200300 100 1 55 */
502,	/* OBJ_documentPublisher            0 9 2342 19200300 100 1 56 */
442,	/* OBJ_iA5StringSyntax              0 9 2342 19200300 100 3 4 */
443,	/* OBJ_caseIgnoreIA5StringSyntax    0 9 2342 19200300 100 3 5 */
444,	/* OBJ_pilotObject                  0 9 2342 19200300 100 4 3 */
445,	/* OBJ_pilotPerson                  0 9 2342 19200300 100 4 4 */
446,	/* OBJ_account                      0 9 2342 19200300 100 4 5 */
447,	/* OBJ_document                     0 9 2342 19200300 100 4 6 */
448,	/* OBJ_room                         0 9 2342 19200300 100 4 7 */
449,	/* OBJ_documentSeries               0 9 2342 19200300 100 4 9 */
392,	/* OBJ_Domain                       0 9 2342 19200300 100 4 13 */
450,	/* OBJ_rFC822localPart              0 9 2342 19200300 100 4 14 */
451,	/* OBJ_dNSDomain                    0 9 2342 19200300 100 4 15 */
452,	/* OBJ_domainRelatedObject          0 9 2342 19200300 100 4 17 */
453,	/* OBJ_friendlyCountry              0 9 2342 19200300 100 4 18 */
454,	/* OBJ_simpleSecurityObject         0 9 2342 19200300 100 4 19 */
455,	/* OBJ_pilotOrganization            0 9 2342 19200300 100 4 20 */
456,	/* OBJ_pilotDSA                     0 9 2342 19200300 100 4 21 */
457,	/* OBJ_qualityLabelledData          0 9 2342 19200300 100 4 22 */
189,	/* OBJ_id_smime_mod                 1 2 840 113549 1 9 16 0 */
190,	/* OBJ_id_smime_ct                  1 2 840 113549 1 9 16 1 */
191,	/* OBJ_id_smime_aa                  1 2 840 113549 1 9 16 2 */
192,	/* OBJ_id_smime_alg                 1 2 840 113549 1 9 16 3 */
193,	/* OBJ_id_smime_cd                  1 2 840 113549 1 9 16 4 */
194,	/* OBJ_id_smime_spq                 1 2 840 113549 1 9 16 5 */
195,	/* OBJ_id_smime_cti                 1 2 840 113549 1 9 16 6 */
158,	/* OBJ_x509Certificate              1 2 840 113549 1 9 22 1 */
159,	/* OBJ_sdsiCertificate              1 2 840 113549 1 9 22 2 */
160,	/* OBJ_x509Crl                      1 2 840 113549 1 9 23 1 */
144,	/* OBJ_pbe_WithSHA1And128BitRC4     1 2 840 113549 1 12 1 1 */
145,	/* OBJ_pbe_WithSHA1And40BitRC4      1 2 840 113549 1 12 1 2 */
146,	/* OBJ_pbe_WithSHA1And3_Key_TripleDES_CBC 1 2 840 113549 1 12 1 3 */
147,	/* OBJ_pbe_WithSHA1And2_Key_TripleDES_CBC 1 2 840 113549 1 12 1 4 */
148,	/* OBJ_pbe_WithSHA1And128BitRC2_CBC 1 2 840 113549 1 12 1 5 */
149,	/* OBJ_pbe_WithSHA1And40BitRC2_CBC  1 2 840 113549 1 12 1 6 */
171,	/* OBJ_ms_ext_req                   1 3 6 1 4 1 311 2 1 14 */
134,	/* OBJ_ms_code_ind                  1 3 6 1 4 1 311 2 1 21 */
135,	/* OBJ_ms_code_com                  1 3 6 1 4 1 311 2 1 22 */
136,	/* OBJ_ms_ctl_sign                  1 3 6 1 4 1 311 10 3 1 */
137,	/* OBJ_ms_sgc                       1 3 6 1 4 1 311 10 3 3 */
138,	/* OBJ_ms_efs                       1 3 6 1 4 1 311 10 3 4 */
648,	/* OBJ_ms_smartcard_login           1 3 6 1 4 1 311 20 2 2 */
649,	/* OBJ_ms_upn                       1 3 6 1 4 1 311 20 2 3 */
751,	/* OBJ_camellia_128_cbc             1 2 392 200011 61 1 1 1 2 */
752,	/* OBJ_camellia_192_cbc             1 2 392 200011 61 1 1 1 3 */
753,	/* OBJ_camellia_256_cbc             1 2 392 200011 61 1 1 1 4 */
907,	/* OBJ_id_camellia128_wrap          1 2 392 200011 61 1 1 3 2 */
908,	/* OBJ_id_camellia192_wrap          1 2 392 200011 61 1 1 3 3 */
909,	/* OBJ_id_camellia256_wrap          1 2 392 200011 61 1 1 3 4 */
196,	/* OBJ_id_smime_mod_cms             1 2 840 113549 1 9 16 0 1 */
197,	/* OBJ_id_smime_mod_ess             1 2 840 113549 1 9 16 0 2 */
198,	/* OBJ_id_smime_mod_oid             1 2 840 113549 1 9 16 0 3 */
199,	/* OBJ_id_smime_mod_msg_v3          1 2 840 113549 1 9 16 0 4 */
200,	/* OBJ_id_smime_mod_ets_eSignature_88 1 2 840 113549 1 9 16 0 5 */
201,	/* OBJ_id_smime_mod_ets_eSignature_97 1 2 840 113549 1 9 16 0 6 */
202,	/* OBJ_id_smime_mod_ets_eSigPolicy_88 1 2 840 113549 1 9 16 0 7 */
203,	/* OBJ_id_smime_mod_ets_eSigPolicy_97 1 2 840 113549 1 9 16 0 8 */
204,	/* OBJ_id_smime_ct_receipt          1 2 840 113549 1 9 16 1 1 */
205,	/* OBJ_id_smime_ct_authData         1 2 840 113549 1 9 16 1 2 */
206,	/* OBJ_id_smime_ct_publishCert      1 2 840 113549 1 9 16 1 3 */
207,	/* OBJ_id_smime_ct_TSTInfo          1 2 840 113549 1 9 16 1 4 */
208,	/* OBJ_id_smime_ct_TDTInfo          1 2 840 113549 1 9 16 1 5 */
209,	/* OBJ_id_smime_ct_contentInfo      1 2 840 113549 1 9 16 1 6 */
210,	/* OBJ_id_smime_ct_DVCSRequestData  1 2 840 113549 1 9 16 1 7 */
211,	/* OBJ_id_smime_ct_DVCSResponseData 1 2 840 113549 1 9 16 1 8 */
786,	/* OBJ_id_smime_ct_compressedData   1 2 840 113549 1 9 16 1 9 */
787,	/* OBJ_id_ct_asciiTextWithCRLF      1 2 840 113549 1 9 16 1 27 */
212,	/* OBJ_id_smime_aa_receiptRequest   1 2 840 113549 1 9 16 2 1 */
213,	/* OBJ_id_smime_aa_securityLabel    1 2 840 113549 1 9 16 2 2 */
214,	/* OBJ_id_smime_aa_mlExpandHistory  1 2 840 113549 1 9 16 2 3 */
215,	/* OBJ_id_smime_aa_contentHint      1 2 840 113549 1 9 16 2 4 */
216,	/* OBJ_id_smime_aa_msgSigDigest     1 2 840 113549 1 9 16 2 5 */
217,	/* OBJ_id_smime_aa_encapContentType 1 2 840 113549 1 9 16 2 6 */
218,	/* OBJ_id_smime_aa_contentIdentifier 1 2 840 113549 1 9 16 2 7 */
219,	/* OBJ_id_smime_aa_macValue         1 2 840 113549 1 9 16 2 8 */
220,	/* OBJ_id_smime_aa_equivalentLabels 1 2 840 113549 1 9 16 2 9 */
221,	/* OBJ_id_smime_aa_contentReference 1 2 840 113549 1 9 16 2 10 */
222,	/* OBJ_id_smime_aa_encrypKeyPref    1 2 840 113549 1 9 16 2 11 */
223,	/* OBJ_id_smime_aa_signingCertificate 1 2 840 113549 1 9 16 2 12 */
224,	/* OBJ_id_smime_aa_smimeEncryptCerts 1 2 840 113549 1 9 16 2 13 */
225,	/* OBJ_id_smime_aa_timeStampToken   1 2 840 113549 1 9 16 2 14 */
226,	/* OBJ_id_smime_aa_ets_sigPolicyId  1 2 840 113549 1 9 16 2 15 */
227,	/* OBJ_id_smime_aa_ets_commitmentType 1 2 840 113549 1 9 16 2 16 */
228,	/* OBJ_id_smime_aa_ets_signerLocation 1 2 840 113549 1 9 16 2 17 */
229,	/* OBJ_id_smime_aa_ets_signerAttr   1 2 840 113549 1 9 16 2 18 */
230,	/* OBJ_id_smime_aa_ets_otherSigCert 1 2 840 113549 1 9 16 2 19 */
231,	/* OBJ_id_smime_aa_ets_contentTimestamp 1 2 840 113549 1 9 16 2 20 */
232,	/* OBJ_id_smime_aa_ets_CertificateRefs 1 2 840 113549 1 9 16 2 21 */
233,	/* OBJ_id_smime_aa_ets_RevocationRefs 1 2 840 113549 1 9 16 2 22 */
234,	/* OBJ_id_smime_aa_ets_certValues   1 2 840 113549 1 9 16 2 23 */
235,	/* OBJ_id_smime_aa_ets_revocationValues 1 2 840 113549 1 9 16 2 24 */
236,	/* OBJ_id_smime_aa_ets_escTimeStamp 1 2 840 113549 1 9 16 2 25 */
237,	/* OBJ_id_smime_aa_ets_certCRLTimestamp 1 2 840 113549 1 9 16 2 26 */
238,	/* OBJ_id_smime_aa_ets_archiveTimeStamp 1 2 840 113549 1 9 16 2 27 */
239,	/* OBJ_id_smime_aa_signatureType    1 2 840 113549 1 9 16 2 28 */
240,	/* OBJ_id_smime_aa_dvcs_dvc         1 2 840 113549 1 9 16 2 29 */
241,	/* OBJ_id_smime_alg_ESDHwith3DES    1 2 840 113549 1 9 16 3 1 */
242,	/* OBJ_id_smime_alg_ESDHwithRC2     1 2 840 113549 1 9 16 3 2 */
243,	/* OBJ_id_smime_alg_3DESwrap        1 2 840 113549 1 9 16 3 3 */
244,	/* OBJ_id_smime_alg_RC2wrap         1 2 840 113549 1 9 16 3 4 */
245,	/* OBJ_id_smime_alg_ESDH            1 2 840 113549 1 9 16 3 5 */
246,	/* OBJ_id_smime_alg_CMS3DESwrap     1 2 840 113549 1 9 16 3 6 */
247,	/* OBJ_id_smime_alg_CMSRC2wrap      1 2 840 113549 1 9 16 3 7 */
125,	/* OBJ_zlib_compression             1 2 840 113549 1 9 16 3 8 */
893,	/* OBJ_id_alg_PWRI_KEK              1 2 840 113549 1 9 16 3 9 */
248,	/* OBJ_id_smime_cd_ldap             1 2 840 113549 1 9 16 4 1 */
249,	/* OBJ_id_smime_spq_ets_sqt_uri     1 2 840 113549 1 9 16 5 1 */
250,	/* OBJ_id_smime_spq_ets_sqt_unotice 1 2 840 113549 1 9 16 5 2 */
251,	/* OBJ_id_smime_cti_ets_proofOfOrigin 1 2 840 113549 1 9 16 6 1 */
252,	/* OBJ_id_smime_cti_ets_proofOfReceipt 1 2 840 113549 1 9 16 6 2 */
253,	/* OBJ_id_smime_cti_ets_proofOfDelivery 1 2 840 113549 1 9 16 6 3 */
254,	/* OBJ_id_smime_cti_ets_proofOfSender 1 2 840 113549 1 9 16 6 4 */
255,	/* OBJ_id_smime_cti_ets_proofOfApproval 1 2 840 113549 1 9 16 6 5 */
256,	/* OBJ_id_smime_cti_ets_proofOfCreation 1 2 840 113549 1 9 16 6 6 */
150,	/* OBJ_keyBag                       1 2 840 113549 1 12 10 1 1 */
151,	/* OBJ_pkcs8ShroudedKeyBag          1 2 840 113549 1 12 10 1 2 */
152,	/* OBJ_certBag                      1 2 840 113549 1 12 10 1 3 */
153,	/* OBJ_crlBag                       1 2 840 113549 1 12 10 1 4 */
154,	/* OBJ_secretBag                    1 2 840 113549 1 12 10 1 5 */
155,	/* OBJ_safeContentsBag              1 2 840 113549 1 12 10 1 6 */
34,	/* OBJ_idea_cbc                     1 3 6 1 4 1 188 7 1 1 2 */
};

