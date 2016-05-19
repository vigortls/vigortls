/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include "ssl_locl.h"

const char *SSL_state_string_long(const SSL *s)
{
    const char *str;

    switch (s->state) {
        case SSL_ST_BEFORE:
            str = "before SSL initialization";
            break;
        case SSL_ST_ACCEPT:
            str = "before accept initialization";
            break;
        case SSL_ST_CONNECT:
            str = "before connect initialization";
            break;
        case SSL_ST_OK:
            str = "SSL negotiation finished successfully";
            break;
        case SSL_ST_RENEGOTIATE:
            str = "SSL renegotiate ciphers";
            break;
        case SSL_ST_BEFORE | SSL_ST_CONNECT:
            str = "before/connect initialization";
            break;
        case SSL_ST_OK | SSL_ST_CONNECT:
            str = "ok/connect SSL initialization";
            break;
        case SSL_ST_BEFORE | SSL_ST_ACCEPT:
            str = "before/accept initialization";
            break;
        case SSL_ST_OK | SSL_ST_ACCEPT:
            str = "ok/accept SSL initialization";
            break;
        case SSL_ST_ERR:
            str = "error";
            break;

        /* SSLv3 additions */
        case SSL3_ST_CW_CLNT_HELLO_A:
            str = "SSLv3 write client hello A";
            break;
        case SSL3_ST_CW_CLNT_HELLO_B:
            str = "SSLv3 write client hello B";
            break;
        case SSL3_ST_CR_SRVR_HELLO_A:
            str = "SSLv3 read server hello A";
            break;
        case SSL3_ST_CR_SRVR_HELLO_B:
            str = "SSLv3 read server hello B";
            break;
        case SSL3_ST_CR_CERT_A:
            str = "SSLv3 read server certificate A";
            break;
        case SSL3_ST_CR_CERT_B:
            str = "SSLv3 read server certificate B";
            break;
        case SSL3_ST_CR_KEY_EXCH_A:
            str = "SSLv3 read server key exchange A";
            break;
        case SSL3_ST_CR_KEY_EXCH_B:
            str = "SSLv3 read server key exchange B";
            break;
        case SSL3_ST_CR_CERT_REQ_A:
            str = "SSLv3 read server certificate request A";
            break;
        case SSL3_ST_CR_CERT_REQ_B:
            str = "SSLv3 read server certificate request B";
            break;
        case SSL3_ST_CR_SESSION_TICKET_A:
            str = "SSLv3 read server session ticket A";
            break;
        case SSL3_ST_CR_SESSION_TICKET_B:
            str = "SSLv3 read server session ticket B";
            break;
        case SSL3_ST_CR_SRVR_DONE_A:
            str = "SSLv3 read server done A";
            break;
        case SSL3_ST_CR_SRVR_DONE_B:
            str = "SSLv3 read server done B";
            break;
        case SSL3_ST_CW_CERT_A:
            str = "SSLv3 write client certificate A";
            break;
        case SSL3_ST_CW_CERT_B:
            str = "SSLv3 write client certificate B";
            break;
        case SSL3_ST_CW_CERT_C:
            str = "SSLv3 write client certificate C";
            break;
        case SSL3_ST_CW_CERT_D:
            str = "SSLv3 write client certificate D";
            break;
        case SSL3_ST_CW_KEY_EXCH_A:
            str = "SSLv3 write client key exchange A";
            break;
        case SSL3_ST_CW_KEY_EXCH_B:
            str = "SSLv3 write client key exchange B";
            break;
        case SSL3_ST_CW_CERT_VRFY_A:
            str = "SSLv3 write certificate verify A";
            break;
        case SSL3_ST_CW_CERT_VRFY_B:
            str = "SSLv3 write certificate verify B";
            break;

        case SSL3_ST_CW_CHANGE_A:
        case SSL3_ST_SW_CHANGE_A:
            str = "SSLv3 write change cipher spec A";
            break;
        case SSL3_ST_CW_CHANGE_B:
        case SSL3_ST_SW_CHANGE_B:
            str = "SSLv3 write change cipher spec B";
            break;
        case SSL3_ST_CW_FINISHED_A:
        case SSL3_ST_SW_FINISHED_A:
            str = "SSLv3 write finished A";
            break;
        case SSL3_ST_CW_FINISHED_B:
        case SSL3_ST_SW_FINISHED_B:
            str = "SSLv3 write finished B";
            break;
        case SSL3_ST_CR_CHANGE_A:
        case SSL3_ST_SR_CHANGE_A:
            str = "SSLv3 read change cipher spec A";
            break;
        case SSL3_ST_CR_CHANGE_B:
        case SSL3_ST_SR_CHANGE_B:
            str = "SSLv3 read change cipher spec B";
            break;
        case SSL3_ST_CR_FINISHED_A:
        case SSL3_ST_SR_FINISHED_A:
            str = "SSLv3 read finished A";
            break;
        case SSL3_ST_CR_FINISHED_B:
        case SSL3_ST_SR_FINISHED_B:
            str = "SSLv3 read finished B";
            break;

        case SSL3_ST_CW_FLUSH:
        case SSL3_ST_SW_FLUSH:
            str = "SSLv3 flush data";
            break;

        case SSL3_ST_SR_CLNT_HELLO_A:
            str = "SSLv3 read client hello A";
            break;
        case SSL3_ST_SR_CLNT_HELLO_B:
            str = "SSLv3 read client hello B";
            break;
        case SSL3_ST_SR_CLNT_HELLO_C:
            str = "SSLv3 read client hello C";
            break;
        case SSL3_ST_SW_HELLO_REQ_A:
            str = "SSLv3 write hello request A";
            break;
        case SSL3_ST_SW_HELLO_REQ_B:
            str = "SSLv3 write hello request B";
            break;
        case SSL3_ST_SW_HELLO_REQ_C:
            str = "SSLv3 write hello request C";
            break;
        case SSL3_ST_SW_SRVR_HELLO_A:
            str = "SSLv3 write server hello A";
            break;
        case SSL3_ST_SW_SRVR_HELLO_B:
            str = "SSLv3 write server hello B";
            break;
        case SSL3_ST_SW_CERT_A:
            str = "SSLv3 write certificate A";
            break;
        case SSL3_ST_SW_CERT_B:
            str = "SSLv3 write certificate B";
            break;
        case SSL3_ST_SW_KEY_EXCH_A:
            str = "SSLv3 write key exchange A";
            break;
        case SSL3_ST_SW_KEY_EXCH_B:
            str = "SSLv3 write key exchange B";
            break;
        case SSL3_ST_SW_CERT_REQ_A:
            str = "SSLv3 write certificate request A";
            break;
        case SSL3_ST_SW_CERT_REQ_B:
            str = "SSLv3 write certificate request B";
            break;
        case SSL3_ST_SW_SESSION_TICKET_A:
            str = "SSLv3 write session ticket A";
            break;
        case SSL3_ST_SW_SESSION_TICKET_B:
            str = "SSLv3 write session ticket B";
            break;
        case SSL3_ST_SW_SRVR_DONE_A:
            str = "SSLv3 write server done A";
            break;
        case SSL3_ST_SW_SRVR_DONE_B:
            str = "SSLv3 write server done B";
            break;
        case SSL3_ST_SR_CERT_A:
            str = "SSLv3 read client certificate A";
            break;
        case SSL3_ST_SR_CERT_B:
            str = "SSLv3 read client certificate B";
            break;
        case SSL3_ST_SR_KEY_EXCH_A:
            str = "SSLv3 read client key exchange A";
            break;
        case SSL3_ST_SR_KEY_EXCH_B:
            str = "SSLv3 read client key exchange B";
            break;
        case SSL3_ST_SR_CERT_VRFY_A:
            str = "SSLv3 read certificate verify A";
            break;
        case SSL3_ST_SR_CERT_VRFY_B:
            str = "SSLv3 read certificate verify B";
            break;

        /* DTLS */
        case DTLS1_ST_CR_HELLO_VERIFY_REQUEST_A:
            str = "DTLS1 read hello verify request A";
            break;
        case DTLS1_ST_CR_HELLO_VERIFY_REQUEST_B:
            str = "DTLS1 read hello verify request B";
            break;
        case DTLS1_ST_SW_HELLO_VERIFY_REQUEST_A:
            str = "DTLS1 write hello verify request A";
            break;
        case DTLS1_ST_SW_HELLO_VERIFY_REQUEST_B:
            str = "DTLS1 write hello verify request B";
            break;

        default:
            str = "unknown state";
            break;
    }
    return (str);
}

const char *SSL_rstate_string_long(const SSL *s)
{
    const char *str;

    switch (s->rstate) {
        case SSL_ST_READ_HEADER:
            str = "read header";
            break;
        case SSL_ST_READ_BODY:
            str = "read body";
            break;
        case SSL_ST_READ_DONE:
            str = "read done";
            break;
        default:
            str = "unknown";
            break;
    }
    return (str);
}

const char *SSL_state_string(const SSL *s)
{
    const char *str;

    switch (s->state) {
        case SSL_ST_BEFORE:
            str = "PINIT ";
            break;
        case SSL_ST_ACCEPT:
            str = "AINIT ";
            break;
        case SSL_ST_CONNECT:
            str = "CINIT ";
            break;
        case SSL_ST_OK:
            str = "SSLOK ";
            break;
        case SSL_ST_ERR:
            str = "SSLERR";
            break;

        /* SSLv3 additions */
        case SSL3_ST_SW_FLUSH:
        case SSL3_ST_CW_FLUSH:
            str = "3FLUSH";
            break;
        case SSL3_ST_CW_CLNT_HELLO_A:
            str = "3WCH_A";
            break;
        case SSL3_ST_CW_CLNT_HELLO_B:
            str = "3WCH_B";
            break;
        case SSL3_ST_CR_SRVR_HELLO_A:
            str = "3RSH_A";
            break;
        case SSL3_ST_CR_SRVR_HELLO_B:
            str = "3RSH_B";
            break;
        case SSL3_ST_CR_CERT_A:
            str = "3RSC_A";
            break;
        case SSL3_ST_CR_CERT_B:
            str = "3RSC_B";
            break;
        case SSL3_ST_CR_KEY_EXCH_A:
            str = "3RSKEA";
            break;
        case SSL3_ST_CR_KEY_EXCH_B:
            str = "3RSKEB";
            break;
        case SSL3_ST_CR_CERT_REQ_A:
            str = "3RCR_A";
            break;
        case SSL3_ST_CR_CERT_REQ_B:
            str = "3RCR_B";
            break;
        case SSL3_ST_CR_SRVR_DONE_A:
            str = "3RSD_A";
            break;
        case SSL3_ST_CR_SRVR_DONE_B:
            str = "3RSD_B";
            break;
        case SSL3_ST_CW_CERT_A:
            str = "3WCC_A";
            break;
        case SSL3_ST_CW_CERT_B:
            str = "3WCC_B";
            break;
        case SSL3_ST_CW_CERT_C:
            str = "3WCC_C";
            break;
        case SSL3_ST_CW_CERT_D:
            str = "3WCC_D";
            break;
        case SSL3_ST_CW_KEY_EXCH_A:
            str = "3WCKEA";
            break;
        case SSL3_ST_CW_KEY_EXCH_B:
            str = "3WCKEB";
            break;
        case SSL3_ST_CW_CERT_VRFY_A:
            str = "3WCV_A";
            break;
        case SSL3_ST_CW_CERT_VRFY_B:
            str = "3WCV_B";
            break;

        case SSL3_ST_SW_CHANGE_A:
        case SSL3_ST_CW_CHANGE_A:
            str = "3WCCSA";
            break;
        case SSL3_ST_SW_CHANGE_B:
        case SSL3_ST_CW_CHANGE_B:
            str = "3WCCSB";
            break;
        case SSL3_ST_SW_FINISHED_A:
        case SSL3_ST_CW_FINISHED_A:
            str = "3WFINA";
            break;
        case SSL3_ST_SW_FINISHED_B:
        case SSL3_ST_CW_FINISHED_B:
            str = "3WFINB";
            break;
        case SSL3_ST_SR_CHANGE_A:
        case SSL3_ST_CR_CHANGE_A:
            str = "3RCCSA";
            break;
        case SSL3_ST_SR_CHANGE_B:
        case SSL3_ST_CR_CHANGE_B:
            str = "3RCCSB";
            break;
        case SSL3_ST_SR_FINISHED_A:
        case SSL3_ST_CR_FINISHED_A:
            str = "3RFINA";
            break;
        case SSL3_ST_SR_FINISHED_B:
        case SSL3_ST_CR_FINISHED_B:
            str = "3RFINB";
            break;

        case SSL3_ST_SW_HELLO_REQ_A:
            str = "3WHR_A";
            break;
        case SSL3_ST_SW_HELLO_REQ_B:
            str = "3WHR_B";
            break;
        case SSL3_ST_SW_HELLO_REQ_C:
            str = "3WHR_C";
            break;
        case SSL3_ST_SR_CLNT_HELLO_A:
            str = "3RCH_A";
            break;
        case SSL3_ST_SR_CLNT_HELLO_B:
            str = "3RCH_B";
            break;
        case SSL3_ST_SR_CLNT_HELLO_C:
            str = "3RCH_C";
            break;
        case SSL3_ST_SW_SRVR_HELLO_A:
            str = "3WSH_A";
            break;
        case SSL3_ST_SW_SRVR_HELLO_B:
            str = "3WSH_B";
            break;
        case SSL3_ST_SW_CERT_A:
            str = "3WSC_A";
            break;
        case SSL3_ST_SW_CERT_B:
            str = "3WSC_B";
            break;
        case SSL3_ST_SW_KEY_EXCH_A:
            str = "3WSKEA";
            break;
        case SSL3_ST_SW_KEY_EXCH_B:
            str = "3WSKEB";
            break;
        case SSL3_ST_SW_CERT_REQ_A:
            str = "3WCR_A";
            break;
        case SSL3_ST_SW_CERT_REQ_B:
            str = "3WCR_B";
            break;
        case SSL3_ST_SW_SRVR_DONE_A:
            str = "3WSD_A";
            break;
        case SSL3_ST_SW_SRVR_DONE_B:
            str = "3WSD_B";
            break;
        case SSL3_ST_SR_CERT_A:
            str = "3RCC_A";
            break;
        case SSL3_ST_SR_CERT_B:
            str = "3RCC_B";
            break;
        case SSL3_ST_SR_KEY_EXCH_A:
            str = "3RCKEA";
            break;
        case SSL3_ST_SR_KEY_EXCH_B:
            str = "3RCKEB";
            break;
        case SSL3_ST_SR_CERT_VRFY_A:
            str = "3RCV_A";
            break;
        case SSL3_ST_SR_CERT_VRFY_B:
            str = "3RCV_B";
            break;

        /* DTLS */
        case DTLS1_ST_CR_HELLO_VERIFY_REQUEST_A:
            str = "DRCHVA";
            break;
        case DTLS1_ST_CR_HELLO_VERIFY_REQUEST_B:
            str = "DRCHVB";
            break;
        case DTLS1_ST_SW_HELLO_VERIFY_REQUEST_A:
            str = "DWCHVA";
            break;
        case DTLS1_ST_SW_HELLO_VERIFY_REQUEST_B:
            str = "DWCHVB";
            break;

        default:
            str = "UNKWN ";
            break;
    }
    return (str);
}

const char *SSL_alert_type_string_long(int value)
{
    value >>= 8;
    if (value == SSL3_AL_WARNING)
        return ("warning");
    else if (value == SSL3_AL_FATAL)
        return ("fatal");
    else
        return ("unknown");
}

const char *SSL_alert_type_string(int value)
{
    value >>= 8;
    if (value == SSL3_AL_WARNING)
        return ("W");
    else if (value == SSL3_AL_FATAL)
        return ("F");
    else
        return ("U");
}

const char *SSL_alert_desc_string(int value)
{
    const char *str;

    switch (value & 0xff) {
        case SSL3_AD_CLOSE_NOTIFY:
            str = "CN";
            break;
        case SSL3_AD_UNEXPECTED_MESSAGE:
            str = "UM";
            break;
        case SSL3_AD_BAD_RECORD_MAC:
            str = "BM";
            break;
        case SSL3_AD_DECOMPRESSION_FAILURE:
            str = "DF";
            break;
        case SSL3_AD_HANDSHAKE_FAILURE:
            str = "HF";
            break;
        case SSL3_AD_NO_CERTIFICATE:
            str = "NC";
            break;
        case SSL3_AD_BAD_CERTIFICATE:
            str = "BC";
            break;
        case SSL3_AD_UNSUPPORTED_CERTIFICATE:
            str = "UC";
            break;
        case SSL3_AD_CERTIFICATE_REVOKED:
            str = "CR";
            break;
        case SSL3_AD_CERTIFICATE_EXPIRED:
            str = "CE";
            break;
        case SSL3_AD_CERTIFICATE_UNKNOWN:
            str = "CU";
            break;
        case SSL3_AD_ILLEGAL_PARAMETER:
            str = "IP";
            break;
        case TLS1_AD_DECRYPTION_FAILED:
            str = "DC";
            break;
        case TLS1_AD_RECORD_OVERFLOW:
            str = "RO";
            break;
        case TLS1_AD_UNKNOWN_CA:
            str = "CA";
            break;
        case TLS1_AD_ACCESS_DENIED:
            str = "AD";
            break;
        case TLS1_AD_DECODE_ERROR:
            str = "DE";
            break;
        case TLS1_AD_DECRYPT_ERROR:
            str = "CY";
            break;
        case TLS1_AD_EXPORT_RESTRICTION:
            str = "ER";
            break;
        case TLS1_AD_PROTOCOL_VERSION:
            str = "PV";
            break;
        case TLS1_AD_INSUFFICIENT_SECURITY:
            str = "IS";
            break;
        case TLS1_AD_INTERNAL_ERROR:
            str = "IE";
            break;
        case TLS1_AD_USER_CANCELLED:
            str = "US";
            break;
        case TLS1_AD_NO_RENEGOTIATION:
            str = "NR";
            break;
        case TLS1_AD_UNSUPPORTED_EXTENSION:
            str = "UE";
            break;
        case TLS1_AD_CERTIFICATE_UNOBTAINABLE:
            str = "CO";
            break;
        case TLS1_AD_UNRECOGNIZED_NAME:
            str = "UN";
            break;
        case TLS1_AD_BAD_CERTIFICATE_STATUS_RESPONSE:
            str = "BR";
            break;
        case TLS1_AD_BAD_CERTIFICATE_HASH_VALUE:
            str = "BH";
            break;
        case TLS1_AD_UNKNOWN_PSK_IDENTITY:
            str = "UP";
            break;
        default:
            str = "UK";
            break;
    }
    return (str);
}

const char *SSL_alert_desc_string_long(int value)
{
    const char *str;

    switch (value & 0xff) {
        case SSL3_AD_CLOSE_NOTIFY:
            str = "close notify";
            break;
        case SSL3_AD_UNEXPECTED_MESSAGE:
            str = "unexpected_message";
            break;
        case SSL3_AD_BAD_RECORD_MAC:
            str = "bad record mac";
            break;
        case SSL3_AD_DECOMPRESSION_FAILURE:
            str = "decompression failure";
            break;
        case SSL3_AD_HANDSHAKE_FAILURE:
            str = "handshake failure";
            break;
        case SSL3_AD_NO_CERTIFICATE:
            str = "no certificate";
            break;
        case SSL3_AD_BAD_CERTIFICATE:
            str = "bad certificate";
            break;
        case SSL3_AD_UNSUPPORTED_CERTIFICATE:
            str = "unsupported certificate";
            break;
        case SSL3_AD_CERTIFICATE_REVOKED:
            str = "certificate revoked";
            break;
        case SSL3_AD_CERTIFICATE_EXPIRED:
            str = "certificate expired";
            break;
        case SSL3_AD_CERTIFICATE_UNKNOWN:
            str = "certificate unknown";
            break;
        case SSL3_AD_ILLEGAL_PARAMETER:
            str = "illegal parameter";
            break;
        case TLS1_AD_DECRYPTION_FAILED:
            str = "decryption failed";
            break;
        case TLS1_AD_RECORD_OVERFLOW:
            str = "record overflow";
            break;
        case TLS1_AD_UNKNOWN_CA:
            str = "unknown CA";
            break;
        case TLS1_AD_ACCESS_DENIED:
            str = "access denied";
            break;
        case TLS1_AD_DECODE_ERROR:
            str = "decode error";
            break;
        case TLS1_AD_DECRYPT_ERROR:
            str = "decrypt error";
            break;
        case TLS1_AD_EXPORT_RESTRICTION:
            str = "export restriction";
            break;
        case TLS1_AD_PROTOCOL_VERSION:
            str = "protocol version";
            break;
        case TLS1_AD_INSUFFICIENT_SECURITY:
            str = "insufficient security";
            break;
        case TLS1_AD_INTERNAL_ERROR:
            str = "internal error";
            break;
        case TLS1_AD_USER_CANCELLED:
            str = "user canceled";
            break;
        case TLS1_AD_NO_RENEGOTIATION:
            str = "no renegotiation";
            break;
        case TLS1_AD_UNSUPPORTED_EXTENSION:
            str = "unsupported extension";
            break;
        case TLS1_AD_CERTIFICATE_UNOBTAINABLE:
            str = "certificate unobtainable";
            break;
        case TLS1_AD_UNRECOGNIZED_NAME:
            str = "unrecognized name";
            break;
        case TLS1_AD_BAD_CERTIFICATE_STATUS_RESPONSE:
            str = "bad certificate status response";
            break;
        case TLS1_AD_BAD_CERTIFICATE_HASH_VALUE:
            str = "bad certificate hash value";
            break;
        case TLS1_AD_UNKNOWN_PSK_IDENTITY:
            str = "unknown PSK identity";
            break;
        default:
            str = "unknown";
            break;
    }
    return (str);
}

const char *SSL_rstate_string(const SSL *s)
{
    const char *str;

    switch (s->rstate) {
        case SSL_ST_READ_HEADER:
            str = "RH";
            break;
        case SSL_ST_READ_BODY:
            str = "RB";
            break;
        case SSL_ST_READ_DONE:
            str = "RD";
            break;
        default:
            str = "unknown";
            break;
    }
    return (str);
}
