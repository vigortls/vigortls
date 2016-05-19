/*
 * Copyright 1999-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

/*
 * This header only exists to break a circular dependency between pem and err
 * Ben 30 Jan 1999.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HEADER_PEM_H
void ERR_load_PEM_strings(void);
#endif

#ifdef __cplusplus
}
#endif
