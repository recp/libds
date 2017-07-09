/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "common.h"
#include "../include/ds/forward-list.h"
#include "default/default.h"

#include <assert.h>

static
void
flist_sp_perform_rm(FListItem **first,
                    FListItem  *prev,
                    FListItem  *tofree);

DS_EXPORT
void
flist_sp_insert(FListItem **first,
                void       *value) {
  DsAllocator *alc;
  FListItem   *item;

  alc  = ds_allocator();
  item = alc->calloc(sizeof(*item), 1);

  item->data = value;
  item->next = *first;
  *first     = item;
}

DS_EXPORT
void
flist_sp_append(FListItem **first,
                void       *value) {
  DsAllocator *alc;
  FListItem   *item;
  FListItem   *last;

  alc  = ds_allocator();
  item = alc->calloc(sizeof(*item), 1);

  item->data = value;
  item->next = NULL; /* we are appending it */

  if (!(last = *first)) {
    *first = item;
    return;
  }

  if (last->next) {
    do {
      last = last->next;
    } while (last->next);
  }

  last->next = item;
}

static
void
flist_sp_perform_rm(FListItem **first,
                    FListItem  *prev,
                    FListItem  *tofree) {
  DsAllocator *alc;

  alc = ds_allocator();
  if (*first == tofree && !(*first)->next) {
    *first = NULL;
    alc->free(tofree);
    return;
  }

  if (*first == tofree)
    *first = tofree->next;

  if (prev->next == tofree)
    prev->next = tofree->next;

  alc->free(tofree);
}

DS_EXPORT
void
flist_sp_remove(FListItem **first, FListItem *item) {
  FListItem *prev, *tofree;

  prev = *first;
  if (!prev)
    return;

  if (prev == item) {
    tofree = prev;
    goto freeitm;
  }

  tofree = NULL;
  while (prev->next) {
    if (prev->next == item) {
      tofree = prev->next;
      break;
    }
    prev = prev->next;
  }

  if (!tofree)
    return;

freeitm:
  flist_sp_perform_rm(first, prev, tofree);
}

DS_EXPORT
void
flist_sp_remove_by(FListItem **first, void *value) {
  FListItem *prev, *tofree;

  prev = *first;
  if (!prev)
    return;

  if (prev->data == value) {
    tofree = prev;
    goto freeitm;
  }

  tofree = NULL;
  while (prev->next) {
    if (prev->next->data == value) {
      tofree = prev->next;
      break;
    }
    prev = prev->next;
  }

  if (!tofree)
    return;

freeitm:
  flist_sp_perform_rm(first, prev, tofree);
}

DS_EXPORT
bool
flist_sp_contains(FListItem **first, void *value) {
  FListItem *item;

  item = *first;
  while (item) {
    if (item->data == value)
      return true;
    item = item->next;
  }

  return false;
}

DS_EXPORT
void
flist_sp_destroy(FListItem **first) {
  DsAllocator *alc;
  FListItem   *item, *tofree;

  alc  = ds_allocator();
  item = *first;

  tofree = NULL;
  while (item) {
    tofree = item;
    item   = item->next;

    alc->free(tofree);
  }

  *first = NULL;
}
