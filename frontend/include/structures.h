#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Pair {
  char *key;
  int value;
};

typedef struct {
  int size;
  int capacity;
  struct Pair *data;
} Map;

int Map__find(Map *map, const char *key);
int Map__add(Map *map, const char *key, int value);
void Map__free(Map *map);
Map *Map__create(int capacity);

typedef void (*FreeFn)(void *element);

typedef struct {
  void **items;
  int count;
  int capacity;
  FreeFn free_fn;
} Vector;

Vector *Vector__create(FreeFn free_fn, int capacity);

void Vector__add(Vector *v, const void *element);
void Vector__free(Vector *v);

#endif