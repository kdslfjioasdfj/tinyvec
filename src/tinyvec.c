#include "tinyvec.h"
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define GROWTH_FACTOR ((size_t)2)
_Static_assert(GROWTH_FACTOR > 0, "GROWTH_FACTOR MUST BE GREATER THAN 0");

int tinyvec_init(tinyvec_t *vec, size_t elem_sz, size_t initial_cap) {
  if (!vec || !elem_sz)
    return TINYVEC_EINVAL;

  if (elem_sz > SIZE_MAX / initial_cap)
    return TINYVEC_EALLOC;

  if (initial_cap == 0) {
    vec->mem = NULL;
    vec->cap = 0;
    vec->len = 0;
    vec->elem_sz = elem_sz;
    return TINYVEC_SUCCESS;
  }

  vec->mem = malloc(elem_sz * initial_cap);
  if (!vec->mem)
    return TINYVEC_EALLOC;

  vec->cap = initial_cap;
  vec->len = 0;
  vec->elem_sz = elem_sz;

  return TINYVEC_SUCCESS;
}

int tinyvec_free(tinyvec_t *vec) {
  if (!vec)
    return TINYVEC_EINVAL;

  if (vec->mem)
    free(vec->mem);

  return TINYVEC_SUCCESS;
}

int tinyvec_elemsz(const tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
                   size_t *TINYVEC_INTERNAL_RESTRICT out) {
  if (!vec || !out)
    return TINYVEC_EINVAL;

  *out = vec->elem_sz;

  return TINYVEC_SUCCESS;
}

int tinyvec_set(tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
                const void *TINYVEC_INTERNAL_RESTRICT val, size_t idx) {
  if (!vec || !val || idx >= vec->len)
    return TINYVEC_EINVAL;

  memcpy(((uint8_t *)(vec->mem)) + (vec->elem_sz * idx), val, vec->elem_sz);

  return TINYVEC_SUCCESS;
}

int tinyvec_get(const tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
                void *TINYVEC_INTERNAL_RESTRICT buf, size_t idx) {
  if (!vec || !buf || idx >= vec->len)
    return TINYVEC_EINVAL;

  memcpy(buf, ((uint8_t *)(vec->mem)) + (vec->elem_sz * idx), vec->elem_sz);

  return TINYVEC_SUCCESS;
}

int tinyvec_push(tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
                 const void *TINYVEC_INTERNAL_RESTRICT val) {
  if (!vec || !val)
    return TINYVEC_EINVAL;

  if (vec->cap > SIZE_MAX / vec->elem_sz / GROWTH_FACTOR)
    return TINYVEC_EALLOC;

  if (vec->cap == vec->len) {
    void *tmp = realloc(vec->mem, (vec->cap > 0 ? vec->cap : 1) * vec->elem_sz *
                                      GROWTH_FACTOR);
    if (!tmp)
      return TINYVEC_EALLOC;
    vec->mem = tmp;
    vec->cap = (vec->cap > 0 ? vec->cap : 1) * GROWTH_FACTOR;
  }

  memcpy(((uint8_t *)(vec->mem)) + (vec->len * vec->elem_sz), val,
         vec->elem_sz);
  vec->len++;

  return TINYVEC_SUCCESS;
}

int tinyvec_resize(tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec, size_t new_sz) {
  if (!vec)
    return TINYVEC_EINVAL;

  if (new_sz == 0) {
    free(vec->mem);
    vec->mem = NULL;
    vec->cap = 0;
    vec->len = 0;
    return TINYVEC_SUCCESS;
  }

  if (new_sz > SIZE_MAX / vec->elem_sz)
    return TINYVEC_EALLOC;

  void *tmp = realloc(vec->mem, new_sz * vec->elem_sz);
  if (!tmp)
    return TINYVEC_EALLOC;
  vec->mem = tmp;
  vec->cap = new_sz;
  vec->len = (vec->len > new_sz) ? new_sz : vec->len;

  return TINYVEC_SUCCESS;
}

int tinyvec_reserve(tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec, size_t min_cap) {
  if (!vec)
    return TINYVEC_EINVAL;

  if (min_cap > SIZE_MAX / vec->elem_sz)
    return TINYVEC_EALLOC;

  if (vec->cap >= min_cap)
    return TINYVEC_SUCCESS;
  else
    return tinyvec_resize(vec, min_cap);
}

int tinyvec_len(const tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
                size_t *TINYVEC_INTERNAL_RESTRICT out) {
  if (!vec || !out)
    return TINYVEC_EINVAL;

  *out = vec->len;

  return TINYVEC_SUCCESS;
}

int tinyvec_cap(const tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
                size_t *TINYVEC_INTERNAL_RESTRICT out) {
  if (!vec || !out)
    return TINYVEC_EINVAL;

  *out = vec->cap;

  return TINYVEC_SUCCESS;
}
