#include "Map.h"
#include "Person.h"
#include "List.h"
#include "Hash.h"
#include "ComparePerson.h"
#include "CException.h"
#include "ErrorCode.h"
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
  
  index = hash(element);
 
  if(map->bucket[index] != NULL){
    if(compare(((List *)map->bucket[index])->data, element) == 1){
      Throw(ERR_SAME_ELEMENT);
    }
		else{
			List *list = listNew(element, (List *)map->bucket[index]);
			map->bucket[index] = list;
		}
  }
	else{
		List *list = listNew(element, NULL);
		map->bucket[index] = list;
	}
}
              
void *mapFind(Map *map, void *element, int (*compare)(void *, void *), unsigned int (*hash)(void *)){
  Person *returnPerson = NULL;
  List *nextList;
  int index;
  
  index = hash(element);
  nextList = ((List *)map->bucket[index]);
  
  if(map->bucket[index] != NULL){
    while(nextList != NULL){
      if(compare(nextList->data, element) == 1){
        returnPerson = (Person *)(nextList->data);
      }
      nextList = nextList->next;
    }  
  }
	return returnPerson;
}