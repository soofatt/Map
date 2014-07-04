#include "Map.h"
#include "Person.h"
#include "List.h"
#include "Hash.h"
#include "ComparePerson.h"
#include "CException.h"
#include <stdio.h>
#include <malloc.h>

Map *mapNew(int length){
  Map *map = malloc(sizeof(Map));
  map->bucket = calloc(sizeof(void *), length);
  map->length = length;
  map->size = 0;
  return map;
}

void mapStore(Map *map, void *element, int (*compare)(void *, void *), unsigned int (*hash)(void *)){
 int index;
 List *list = listNew(element, NULL);
 
 index = hash(element);
 
 map->bucket[index] = list;
}
              
void *mapFind(Map *map,
              void *element, 
              int (*compare)(void *, void *),
              unsigned int (*hash)(void *)){
  return NULL;
}