# TinyVec Documentation

> **IMPORTANT NOTE**: Anything that is not documented in this file that was declared/defined in the header is not for public usage. Do not depend on it.

## Macros

### TINYVEC_SUCCESS

The value returned by _all_ **TinyVec** functions on success.

### TINYVEC_EALLOC

The value returned by _all_ **TinyVec** functions on allocation failure.

### TINYVEC_EINVAL

The value returned by _all_ **TinyVec** functions when an invalid parameter is passed.

## Types

### struct tinyvec_s

The vector type for **TinyVec**.

### tinyvec_t

An alias for `struct tinyvec_s`.

## Functions

### tinyvec_init

Initialize a **TinyVec** `struct tinyvec_s` vector.

Signature: `int tinyvec_init(tinyvec_t *vec, size_t elem_sz, size_t initial_cap)`

Parameters:

- `tinyvec_t *vec`: The vector to initialize
- `size_t elem_sz`: The size of each element in the array. Must be greater than 0.
- `size_t initial_cap`: The initial capacity of the array.

Important notes:

- This function overwrites the current contents of the vector `tinyvec_t *vec`. If this previously pointed to a valid vector, it will cause a leak.
- Returns `TINYVEC_SUCCESS` on success, `TINYVEC_EINVAL` if parameters are invalid, or `TINYVEC_EALLOC` if allocation fails.

### tinyvec_free

Free a **TinyVec** `struct tinyvec_s` vector.

Signature: `int tinyvec_free(tinyvec_t *vec)`

Parameters:

- `tinyvec_t *vec`: A pointer to the vector to free.

Important notes:

- This function only frees the internal buffer of the vector where applicable. Do not expect it to free the vector if it was on heap.
- Returns `TINYVEC_SUCCESS` on success, `TINYVEC_EINVAL` if parameters are invalid.

### tinyvec_elemsz

Get the size of each element stored in a **TinyVec** vector.

Signature: `int tinyvec_elemsz(const tinyvec_t *vec, size_t *out)`

Parameters:

- `const tinyvec_t *vec`: The vector to query.
- `size_t *out`: Pointer to a variable where the element size will be stored.

Important notes:

- The element size is the same as what was provided during `tinyvec_init`.
- Returns `TINYVEC_SUCCESS` on success, `TINYVEC_EINVAL` if parameters are invalid.

### tinyvec_set

Set the value of an element in the vector at a given index.

Signature: `int tinyvec_set(tinyvec_t *vec, const void *val, size_t idx)`

Parameters:

- `tinyvec_t *vec`: The vector to modify.
- `const void *val`: Pointer to the value to copy into the vector.
- `size_t idx`: Index of the element to set. Must be less than `tinyvec_len(vec)`.

Important notes:

- Copies `elem_sz` bytes from `val` into the vector at position `idx`.
- Returns `TINYVEC_SUCCESS` on success, `TINYVEC_EINVAL` if parameters are invalid or index is out of bounds.

### tinyvec_get

Retrieve the value of an element in the vector at a given index.

Signature: `int tinyvec_get(const tinyvec_t *vec, void *buf, size_t idx)`

Parameters:

- `const tinyvec_t *vec`: The vector to query.
- `void *buf`: Pointer to memory where the value will be copied.
- `size_t idx`: Index of the element to get. Must be less than `tinyvec_len(vec)`.

Important notes:

- Copies `elem_sz` bytes from the vector into `buf`.
- Returns `TINYVEC_SUCCESS` on success, `TINYVEC_EINVAL` if parameters are invalid or index is out of bounds.

### tinyvec_push

Append a new element to the end of the vector.

Signature: `int tinyvec_push(tinyvec_t *vec, const void *val)`

Parameters:

- `tinyvec_t *vec`: The vector to modify.
- `const void *val`: Pointer to the value to append.

Important notes:

- If the vector’s capacity is full, it will automatically grow using the power-of-2 growth rule (0 -> 1 -> 2 -> 4 -> 8 -> ...).
- Returns `TINYVEC_SUCCESS` on success, `TINYVEC_EINVAL` if parameters are invalid, or `TINYVEC_EALLOC` if memory allocation fails.

### tinyvec_resize

Resize the vector to a new number of elements.

Signature: `int tinyvec_resize(tinyvec_t *vec, size_t new_sz)`

Parameters:

- `tinyvec_t *vec`: The vector to resize.
- `size_t new_sz`: The new size of the vector in elements.

Important notes:

- If `new_sz` is less than the current length, elements beyond `new_sz` are discarded.
- If `new_sz` is greater than the current capacity, memory is reallocated.
- Returns `TINYVEC_SUCCESS` on success, `TINYVEC_EINVAL` if parameters are invalid, or `TINYVEC_EALLOC` if memory allocation fails.

### tinyvec_reserve

Ensure that the vector has at least a minimum capacity.

Signature: `int tinyvec_reserve(tinyvec_t *vec, size_t min_cap)`

Parameters:

- `tinyvec_t *vec`: The vector to modify.
- `size_t min_cap`: The minimum capacity to reserve.

Important notes:

- If the current capacity is already equal to or greater than `min_cap`, this function does nothing.
- Otherwise, the vector is resized to at least `min_cap` elements.
- Returns `TINYVEC_SUCCESS` on success, `TINYVEC_EINVAL` if parameters are invalid, or `TINYVEC_EALLOC` if memory allocation fails.

### tinyvec_len

Get the current number of elements in the vector.

Signature: `int tinyvec_len(const tinyvec_t *vec, size_t *out)`

Parameters:

- `const tinyvec_t *vec`: The vector to query.
- `size_t *out`: Pointer to store the length.

Important notes:

- Returns the number of elements that have been added to the vector (not the capacity).
- Returns `TINYVEC_SUCCESS` on success, `TINYVEC_EINVAL` if parameters are invalid.

### tinyvec_cap

Get the current capacity of the vector.

Signature: `int tinyvec_cap(const tinyvec_t *vec, size_t *out)`

Parameters:

- `const tinyvec_t *vec`: The vector to query.
- `size_t *out`: Pointer to store the capacity.

Important notes:

- Capacity is the maximum number of elements the vector can hold without reallocating.
- Returns `TINYVEC_SUCCESS` on success, `TINYVEC_EINVAL` if parameters are invalid.
