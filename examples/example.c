#include "tinyvec.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  tinyvec_t vec;
  int status;

  // 1. Initialize: Creating a vector for integers
  printf("Initializing vector...\n");
  status = tinyvec_init(&vec, sizeof(int), 2);
  if (status != TINYVEC_SUCCESS)
    return 1;

  // 2. Reserve: Pre-allocating space to avoid repeated reallocations
  tinyvec_reserve(&vec, 10);

  // 3. Push: Adding elements
  printf("Pushing elements...\n");
  for (int i = 0; i < 5; ++i) {
    int val = i * 10;
    tinyvec_push(&vec, &val);
  }

  // 4. Metadata Inspection: Get length, capacity, and element size
  size_t len, cap, sz;
  tinyvec_len(&vec, &len);
  tinyvec_cap(&vec, &cap);
  tinyvec_elemsz(&vec, &sz);
  printf("Vector Info -> Len: %zu, Cap: %zu, ElemSz: %zu bytes\n", len, cap,
         sz);

  // 5. Set: Modifying an existing element (e.g., setting index 0 to 99)
  int new_val = 99;
  tinyvec_set(&vec, &new_val, 0);

  // 6. Get: Retrieving an element
  int retrieved;
  tinyvec_get(&vec, &retrieved, 0);
  printf("Value at index 0 (after set): %d\n", retrieved);

  // 7. Resize: Shrinking the vector
  printf("Resizing vector to 2 elements...\n");
  tinyvec_resize(&vec, 2);

  // Verify resize
  tinyvec_len(&vec, &len);
  printf("New length: %zu\n", len);

  // 8. Cleanup: Always free memory to prevent leaks
  tinyvec_free(&vec);
  printf("Vector freed successfully.\n");

  return 0;
}