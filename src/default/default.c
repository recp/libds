/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "default.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc/malloc.h>

DsAllocator ds__alc = {
  .malloc   = malloc,
  .calloc   = calloc,
  .realloc  = realloc,
  .free     = free,
#ifndef _WIN32
  .memalign = posix_memalign,
#endif
  .strdup   = strdup
};

DS_HIDE
DsAllocator*
ds_def_alc() {
  return &ds__alc;
}
