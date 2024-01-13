#include "dArray.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void print_array(struct array *self){
  for(size_t i =0; i<self->size; ++i){
    printf("[%d]", self->data[i]);
  }
  printf("\n");
}

void array_create(struct array *self) {
  self-> capacity = 10;
  self-> size = 0;
  self-> data = calloc(self-> capacity, sizeof(int));
}

void array_copy(int *copy, const int *copied, size_t size){
  for(size_t i = 0; i<size; ++i){
    copy[i] = copied[i];
  }
}

void array_create_from(struct array *self, const int *other, size_t size) {
  self-> capacity = size*2;
  self-> size = size;
  self-> data = calloc(self-> capacity, sizeof(int));
  array_copy(self->data, other, size);
}

void array_destroy(struct array *self){
  if(self-> data != NULL)free(self->data);
}

bool array_empty(const struct array *self) {
  if(self-> size > 0){
    return false;
  }
  return true;
}

size_t array_size(const struct array *self) {
  return self-> size;
}

bool array_equals(const struct array *self, const int *content, size_t size) {
  if(self-> size != size){
    return false;
  }
  for(size_t i = 0; i < size; ++i){
    if(self-> data[i] != content[i]){
      return false;
    }
  }
  return true;
}

void array_size_up(struct array *self,int *copied){
  if(self->capacity <= 1) self-> capacity = 10;
  else self-> capacity = self->size*2;
  self->data = calloc(self->capacity,sizeof(int));
  for(size_t i = 0; i<self->size; ++i){
    self->data[i] = copied[i];
  }
}

void array_push_back(struct array *self, int value) {
  if((self-> capacity-self-> size)<2) array_size_up(self, self->data);
  self->data[self->size] = value;
  self->size +=1;
}

void array_pop_back(struct array *self) {
  self-> data[self-> size-1] = 0;
  self-> size = self-> size-1;
}

void array_insert(struct array *self, int value, size_t index) {
  if((self-> capacity-self-> size)<2) array_size_up(self, self->data);
  for(size_t i = self->size; i > index; --i){
    self->data[i] = self-> data[i-1];
  }
  self->size +=1;
  self->data[index] =  value;
}

void array_remove(struct array *self, size_t index) {
  for(size_t i = index; i < self->size ; ++i){
    self->data[i] = self-> data[i+1];
  }
  self->size -=1;
}

int array_get(const struct array *self, size_t index) {
  if(index < self->size) return self-> data[index];
  return 0;
}

void array_set(struct array *self, size_t index, int value) {
  if(self-> size >= index){
    self-> data[index] = value;
  }
}

size_t array_search(const struct array *self, int value) {
  size_t i = 0;
  while (i < self-> size && self-> data[i] != value) {
    i++;
  }
  return i;
}


size_t array_search_sorted(const struct array *self, int value) {
  size_t i = 0;
  while (i < self-> size && self-> data[i] != value) {
    i++;
  }
  return i;
}

bool array_is_sorted(const struct array *self) {
  for(size_t i = 1; i < self->size; ++i){
    if(self->data[i] < self->data[i-1]) return false;
  }
  return true;
}

void array_swap(struct array *self, size_t i, size_t j){
  int stock = self->data[i];
  self->data[i] = self->data[j];
  self->data[j] = stock;
}

ptrdiff_t array_partition(struct array *self, ptrdiff_t i, ptrdiff_t j) {
  ptrdiff_t pivot_index = i;
  const int pivot = self->data[pivot_index];
  array_swap(self, pivot_index, j);
  ptrdiff_t l = i;
  for (ptrdiff_t k = i; k < j; ++k) {
    if (self->data[k] < pivot) {
      array_swap(self, k, l);
      ++l;
    }
  }
  array_swap(self, l, j);
  return l;
}

void array_quick_sort_partial(struct array *self,ptrdiff_t i, ptrdiff_t j) {
  if (i < j) {
    ptrdiff_t p = array_partition(self, i, j);
    array_quick_sort_partial(self, i, p - 1);
    array_quick_sort_partial(self, p + 1, j);
  }
}

void array_quick_sort(struct array *self){
  array_quick_sort_partial(self,0,self->size-1);
}

void heapify(struct array *self, int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && self->data[l] > self->data[largest])largest = l;
    if (r < n && self->data[r] > self->data[largest])largest = r;
    if (largest != i) {
        array_swap(self,i,largest);
         heapify(self, n, largest);
    }
}

void array_heap_sort(struct array *self){
  int n = (int)(self->size);
  for (int i = n / 2 - 1; i >= 0; i--) heapify(self, n, i);
  for (int i = n - 1; i > 0; i--){
      array_swap(self,0,i);
      heapify(self, i, 0);
  }
}

bool array_is_heap(const struct array *self) {
  for(size_t i=0; i<self->size;++i){
    if(2*i+1<self->size){
      if(self->data[i]<self->data[2*i+1])return false;
      if(2*i+2<self->size){
        if(self->data[i]<self->data[2*i+2])return false;
      }
    }
  }
  return true;
}

void array_heap_add(struct array *self, int value) {
  size_t i = self->size;
  array_push_back(self,value);
  while (i > 0) {
    size_t j = (i - 1) / 2;
    if (self->data[i] < self->data[j]) {
      break;
    }
    array_swap(self, i, j);
    i = j;
  }
}

int array_heap_top(const struct array *self) {
  return self->data[0];
}

void array_heap_remove_top(struct array *self) {
  size_t n = (int)(self->size);
  self->data[0] = self->data[n-1];
  size_t i =0;
  while (i < ((n)/2)){
    size_t lt = 2 * i + 1;
    size_t rt = 2 * i + 2;
    if (self->data[i] > self->data[lt] && self->data[i] > self->data[rt]) {
      break;
    }
    size_t j = (self->data[lt] > self->data[rt]) ? lt : rt;
    array_swap(self, i, j);
    i = j;
  }
  array_pop_back(self);
}