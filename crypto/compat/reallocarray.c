/*
 * Copyright (c) 2014 - 2015, Kurt Cancemi (kurt@x64architecture.com)
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef __has_builtin
  #define __has_builtin(x) 0
#endif

#if __has_builtin(__builtin_umull_overflow) || (defined(__GNUC__) && __GNUC__ >= 5)

void *reallocarray(void *ptr, size_t newmem, size_t size)
{
    size_t prod;
    if (__builtin_umull_overflow(size, newmem, &prod)) {
        errno = ENOMEM;
        return NULL;
    }

    return realloc(ptr, prod);
}

#else

#define SQRT_SIZE_MAX ((size_t)1 << (sizeof(size_t) * 4))

void *reallocarray(void *ptr, size_t newmem, size_t size)
{
    if ((size | newmem) > SQRT_SIZE_MAX /* fast test */
        && size && newmem > SIZE_MAX / size) {
        errno = ENOMEM;
        return NULL;
    }

    return realloc(ptr, size * newmem);
}

#endif
