#include "../include/structures.h"
#include <stdlib.h>

Vector *Vector__create(FreeFn free_fn, int capacity) {
  Vector *v = malloc(sizeof(Vector));
  v->count = 0;
  v->capacity = capacity;
  v->items = malloc(sizeof(void *) * v->capacity);
  v->free_fn = free_fn;
  return v;
}

static void vector_grow(Vector *v) {
  v->capacity *= 2;
  v->items = realloc(v->items, sizeof(void *) * v->capacity);
}

void Vector__add(Vector *v, const void *element) {
  if (v->count == v->capacity)
    vector_grow(v);

  v->items[v->count++] = (void *)element;
}

void Vector__free(Vector *v) {
  if (v->free_fn) {
    for (int i = 0; i < v->count; i++)
      v->free_fn(v->items[i]);
  }
  free(v->items);
  free(v);
}