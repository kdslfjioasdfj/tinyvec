#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef TINYVEC_TINYVEC_H
#define TINYVEC_TINYVEC_H

#include <stddef.h>

#ifdef _MSC_VER
#define TINYVEC_INTERNAL_RESTRICT __restrict
#elif defined(__cplusplus)
#define TINYVEC_INTERNAL_RESTRICT
#else
#define TINYVEC_INTERNAL_RESTRICT restrict
#endif // _MSC_VER || __cplusplus

#ifdef _WIN32
#ifdef TINYVEC_CONFIG_BUILDING
#define TINYVEC_PUBLIC_API __declspec(dllexport)
#else
#define TINYVEC_PUBLIC_API __declspec(dllimport)
#endif // TINYVEC_CONFIG_BUILDING
#else
#define TINYVEC_PUBLIC_API // Not needed outside of Windows
#endif                     // _WIN32

#define TINYVEC_SUCCESS ((int)0)
#define TINYVEC_EALLOC ((int)1)
#define TINYVEC_EINVAL ((int)2)

typedef struct tinyvec_s {
  void *mem;
  size_t len;
  size_t cap;
  size_t elem_sz;
} tinyvec_t;

TINYVEC_PUBLIC_API int tinyvec_init(tinyvec_t *vec, size_t elem_sz,
                                    size_t initial_cap);

TINYVEC_PUBLIC_API int tinyvec_free(tinyvec_t *vec);

TINYVEC_PUBLIC_API int
tinyvec_elemsz(const tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
               size_t *TINYVEC_INTERNAL_RESTRICT out);

TINYVEC_PUBLIC_API int tinyvec_set(tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
                                   const void *TINYVEC_INTERNAL_RESTRICT val,
                                   size_t idx);

TINYVEC_PUBLIC_API int tinyvec_get(const tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
                                   void *TINYVEC_INTERNAL_RESTRICT buf,
                                   size_t idx);

TINYVEC_PUBLIC_API int tinyvec_push(tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
                                    const void *TINYVEC_INTERNAL_RESTRICT val);

TINYVEC_PUBLIC_API int tinyvec_resize(tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
                                      size_t new_sz);

TINYVEC_PUBLIC_API int tinyvec_reserve(tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
                                       size_t min_cap);

TINYVEC_PUBLIC_API int
tinyvec_len(const tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
            size_t *TINYVEC_INTERNAL_RESTRICT out);

TINYVEC_PUBLIC_API int
tinyvec_cap(const tinyvec_t *TINYVEC_INTERNAL_RESTRICT vec,
            size_t *TINYVEC_INTERNAL_RESTRICT out);

#undef TINYVEC_PUBLIC_API

#endif // TINYVEC_TINYVEC_H

#ifdef __cplusplus
}
#endif // __cplusplus
