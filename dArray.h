#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct array {
  int *data;
  size_t capacity;
  size_t size;
};

/*
 * Create an empty array
 */
void array_create(struct array *self);

/*
 * Create an array with initial content
 */
void array_create_from(struct array *self, const int *other, size_t size);

/*
 * Destroy an array
 */
void array_destroy(struct array *self);

/*
 * Tell if the array is empty
 */
bool array_empty(const struct array *self);

/*
 * Get the size of the array
 */
size_t array_size(const struct array *self);

/*
 * Compare the array to another array (content and size)
 */
bool array_equals(const struct array *self, const int *content, size_t size);

/*
 * Add an element at the end of the array
 */
void array_push_back(struct array *self, int value);

/*
 * Remove the element at the end of the array
 */
void array_pop_back(struct array *self);

/*
 * Insert an element in the array (preserving the order)
 */
void array_insert(struct array *self, int value, size_t index);

/*
 * Remove an element in the array (preserving the order)
 */
void array_remove(struct array *self, size_t index);

/*
 * Get an element at the specified index in the array, or 0 if the index is not valid
 */
int array_get(const struct array *self, size_t index);

/*
 * Set an element at the specified index in the array to a new value, or do nothing if the index is not valid
 */
void array_set(struct array *self, size_t index, int value);

/*
 * Search for an element in the array.
 */
size_t array_search(const struct array *self, int value);

/*
 * Search for an element in the sorted array.
 */
size_t array_search_sorted(const struct array *self, int value);

/*
 * Tell if the array is sorted
 */
bool array_is_sorted(const struct array *self);

/*
 * Make a partition of the array between i and j (inclusive) and returns the index of the pivot
 */
ptrdiff_t array_partition(struct array *self, ptrdiff_t i, ptrdiff_t j);

/*
 * Sort the array with quick sort
 */
void array_quick_sort(struct array *self);

/*
 * Sort the array with heap sort
 */
void array_heap_sort(struct array *self);

/*
 * Tell if the array is a heap
 */
bool array_is_heap(const struct array *self);

/*
 * Add a value into the array considered as a heap
 */
void array_heap_add(struct array *self, int value);

/*
 * Get the value at the top of the heap
 */
int array_heap_top(const struct array *self);

/*
 * Remove the top value in the array considered as a heap
 */
void array_heap_remove_top(struct array *self);


/*
* Make copy of array in another array_get
*/
void array_copy(int *copy, const int *copied, size_t size);

/*
* Resize capacity of array if it necessary
*/
void array_size_up(struct array *self,int *copied);

/*
* Sawp 2 elements of array
*/
void array_swap(struct array *self, size_t i, size_t j);

/*
* 
*/
void array_quick_sort_partial(struct array *self,ptrdiff_t i, ptrdiff_t j);
