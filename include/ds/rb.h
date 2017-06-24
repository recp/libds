/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#ifndef redblack_h
#define redblack_h
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "allocator.h"
#include "util.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

struct RBTree;
struct RBNode;

typedef void (*RBNodeFn)(struct RBTree *tree, struct RBNode *node);
typedef void (*RBFoundFn)(struct RBTree *tree, void *key, bool *replace);

typedef struct RBNode {
  void          *key;
  void          *val;
  struct RBNode *chld[2];
  uint8_t        color:1;
} RBNode;

typedef struct RBTree {
  DsAllocator *alc;
  RBNode      *root;
  RBNode      *nullNode;
  DsCmpFn      cmp;
  DsPrintFn    print;
  RBNodeFn     onFreeNode;
  RBFoundFn    onFound; /* fires for duplicates */
  size_t       count;
} RBTree;

RBTree*
rb_newtree(DsAllocator *allocator,
           DsCmpFn      cmp,
           DsPrintFn    print);

RBTree*
rb_newtree_str(void);

RBTree*
rb_newtree_ptr(void);

void
rb_insert(RBTree *tree,
          void *key,
          void *val);

void
rb_remove(RBTree *tree, void *key);

void*
rb_find(RBTree *tree, void *key);

RBNode*
rb_find_node(RBTree *tree, void *key);

int
rb_parent(RBTree *tree,
          void *key,
          RBNode ** dest);

void
rb_print(RBTree *tree);

void
rb_walk(RBTree *tree, RBNodeFn walkFn);

int
rb_assert(RBTree *tree, RBNode *root);

void
rb_empty(RBTree *tree);

bool
rb_isempty(RBTree *tree);

void
rb_destroy(RBTree *tree);

#ifdef __cplusplus
}
#endif
#endif /* redblack_h */
