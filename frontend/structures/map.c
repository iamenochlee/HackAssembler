#include "../include/structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// extern int VERBOSE_MODE;

static void grow_map(Map *map) {

  int oldcapacity = map->capacity;
  map->capacity *= 2; // Double the size (exponential growth)

  map->data = realloc(map->data, sizeof(struct Pair) * map->capacity);
  if (map->data == NULL) {
    fprintf(stderr, "Error: Failed to grow symbol map to capacity %d\n",
            map->capacity);
    exit(EXIT_FAILURE);
  }

  // if (VERBOSE_MODE) {
  //   printf("Grew map data sfrom %d to %d capacity (reallocation occurred)\n",
  //          oldcapacity, map->capacity);
  // }
}

static void Map__init(Map *map, int capacity) {
  map->capacity = capacity;
  map->size = 0;
  map->data = malloc(sizeof(struct Pair) * capacity);
}

int Map__add(Map *map, char *key, int value) {
  if (map->size >= map->capacity) {
    grow_map(map);
  }

  map->data[map->size].key = key;
  map->data[map->size].value = value;
  map->size++;
  return 0;
}
Map *Map__create(int capacity) {

  Map *map = malloc(sizeof(Map));
  Map__init(map, capacity);

  return map;
};

int Map__find(Map *map, const char *key) {
  for (int i = 0; i < map->size; i++) {
    if (strcmp(map->data[i].key, key) == 0) {
      return map->data[i].value;
    }
  }
  return -1;
}

void Map__free(Map *map) {
  if (map->data != NULL) {
    // Free individual map keys
    for (int i = 0; i < map->size; i++) {
      if (map->data[i].key != NULL) {
        free(map->data[i].key);
      }
    }
    free(map->data);
    map->data = NULL;
  }
  map->size = 0;
  map->capacity = 0;

  free(map);
}
