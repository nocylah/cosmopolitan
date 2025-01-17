/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/calls/internal.h"
#include "libc/macros.internal.h"
#include "libc/nt/files.h"
#include "libc/nt/memory.h"
#include "libc/runtime/memtrack.internal.h"

noasan textwindows int sys_msync_nt(void *addr, size_t size, int flags) {
  int x, y, l, r, i;
  x = ROUNDDOWN((intptr_t)addr, FRAMESIZE) >> 16;
  y = ROUNDDOWN((intptr_t)addr + size - 1, FRAMESIZE) >> 16;
  for (i = FindMemoryInterval(&_mmi, x); i < _mmi.i; ++i) {
    if ((x >= _mmi.p[i].x && x <= _mmi.p[i].y) ||
        (y >= _mmi.p[i].x && y <= _mmi.p[i].y)) {
      FlushFileBuffers(_mmi.p[i].h);
    } else {
      break;
    }
  }
  return 0;
}
