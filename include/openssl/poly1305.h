/* Copyright (c) 2014, Google Inc.
*
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
* SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
* OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
* CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

#ifndef HEADER_POLY1305_H_
#define HEADER_POLY1305_H_

#include <stdint.h>
#include <openssl/opensslconf.h>

#if defined(OPENSSL_NO_POLY1305)
#error Poly1305 support is disabled.
#endif

typedef unsigned char poly1305_state[512];

/* poly1305_init sets up |state| so that it can be used to calculate an
 * authentication tag with the one-time key |key|. Note that |key| is a
 * one-time key and therefore there is no `reset' method because that would
 * enable several messages to be authenticated with the same key. */
extern void CRYPTO_poly1305_init(poly1305_state *state,
                                 const unsigned char key[32]);

/* poly1305_update processes |in_len| bytes from |in|. It can be called zero or
 * more times after poly1305_init. */
extern void CRYPTO_poly1305_update(poly1305_state *state,
                                   const unsigned char *in,
                                   size_t in_len);

/* poly1305_finish completes the poly1305 calculation and writes a 16 byte
 * authentication tag to |mac|. */
extern void CRYPTO_poly1305_finish(poly1305_state *state,
                                   unsigned char mac[16]);

#endif /* HEADER_POLY1305_H_ */
