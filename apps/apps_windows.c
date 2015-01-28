/*
 * Copyright (c) 2015, Kurt Cancemi (kurt@x64architecture.com)
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
/*
 * Based off of previous work by:
 * Dongsheng Song <dongsheng.song@gmail.com> and Brent Cook <bcook@openbsd.org>
 */

#ifdef _WIN32

#include <windows.h>

#include "apps.h"

double app_tminterval(int stop, int usertime)
{
    static unsigned __int64 tmstart;
    union {
        unsigned __int64 u64;
        FILETIME ft;
    } ct, et, kt, ut;

    GetProcessTimes(GetCurrentProcess(), &ct.ft, &et.ft, &kt.ft, &ut.ft);

    if (stop == TM_START) {
        tmstart = ut.u64 + kt.u64;
    } else {
        return (ut.u64 + kt.u64 - tmstart) / (double)10000000;
    }
    return 0;
}

#endif