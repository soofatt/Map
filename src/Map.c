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

/*Function to store an element in the map(Separate chaining method)
 *
 *Input : *map : The map
 *        *element : The element to be stored
 *        (*compare)(void *, void *) : Compare function
 *        (*hash)(void *) : Hash function
 *
 */
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

/*Function to find an element in the map(Separate chaining method)
 *
 *Input : *map : The map
 *        *element : The element to be found
 *        (*compare)(void *, void *) : Compare function
 *        (*hash)(void *) : Hash function
 *
 *Output : returnPerson : The found element
 *
 */              
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

/*Function to remove an element in the map(Separate chaining method)
 *
 *Input : *map : The map
 *        *element : The element to be found
 *        (*compare)(void *, void *) : Compare function
 *        (*hash)(void *) : Hash function
 *
 *Output : removePerson : The removed element
 *
 */
void *mapRemove(Map *map, void *element, int (*compare)(void *, void *), unsigned int (*hash)(void *)){
  Person *removePerson = NULL;
  List *prevList, *currentList;
  int index;
  
  index = hash(element);
  currentList = ((List *)map->bucket[index]);
  
  if(map->bucket[index] != NULL){
    while(currentList != NULL){
      if(compare(currentList->data, element) == 1){
        removePerson = (Person *)(currentList->data);
        if(((List *)map->bucket[index])->next == NULL)
          map->bucket[index] = currentList->next;
        else
          prevList->next = currentList->next;
      }
      prevList = currentList;
      currentList = currentList->next;
    }  
  }
  
	return removePerson;
}

/*Function to store an element in the map(Linear probing method)
 *
 *Input : *map : The map
 *        *element : The element to be stored
 *        (*compare)(void *, void *) : Compare function
 *        (*hash)(void *) : Hash function
 *
 */
void mapLinearStore(Map *map, void *element, int (*compare)(void *, void *), unsigned int (*hash)(void *)){
  int index;
  
  index = hash(element);
  
  if(isBucketEmpty(map->bucket[index])){
    map->bucket[index] = element;
  }
  else{
    while(index < map->length){
      if(map->bucket[index] != NULL){
        if(compare(map->bucket[index], element) == 1)
          Throw(ERR_SAME_ELEMENT);
        else
          index++;
      }
      
      else{
        map->bucket[index] = element;
        return;
      }
    }
  }
  if(index >= map->length)
      Throw(ERR_OUT_OF_BOUNDS);
}

/*Function to find an element in the map(Linear probing method)
 *
 *Input : *map : The map
 *        *element : The element to be found
 *        (*compare)(void *, void *) : Compare function
 *        (*hash)(void *) : Hash function
 *
 *Output : personFound : The found element
 *
 */
void *mapLinearFind(Map *map, void *element, int (*compare)(void *, void *), unsigned int (*hash)(void *)){
  int index;
  Person *personFound = NULL;
  
  index = hash(element);

  while(map->bucket[index] != NULL && index < map->length){
    if(isBucketMarked(map->bucket[index]))
      index++;
    else{
      if(compare(map->bucket[index], element) == 1){
        personFound = (Person *)map->bucket[index];
        break;
      }
      else
        index++;
    }
  }
  
  if(index >= map->length)
      Throw(ERR_OUT_OF_BOUNDS);
  
  return personFound;
}  

/*Function to remove an element in the map(Linear probing method)
 *
 *Input : *map : The map
 *        *element : The element to be removed
 *        (*compare)(void *, void *) : Compare function
 *        (*hash)(void *) : Hash function
 *
 *Output : personReturn : The removed element
 *
 */
void *mapLinearRemove(Map *map, void *element, int (*compare)(void *, void *), unsigned int (*hash)(void *)){
  int index;
  Person *personReturn = NULL;
  
  index = hash(element);
  
  while(map->bucket[index] != NULL && index < map->length){
    if(isBucketMarked(map->bucket[index]))
      index++;
    else{
      if(compare(map->bucket[index], element) == 1){
        personReturn = (Person *)map->bucket[index];
        if(map->bucket[index+1] == NULL){
          map->bucket[index] = NULL;
          while(isBucketMarked(map->bucket[--index])){
            map->bucket[index] = NULL;
          }
        }
        else
          map->bucket[index] = (void *)-1;
        break;
      }
      else
        index++;
    }
  }
  
  if(index >= map->length)
      Throw(ERR_OUT_OF_BOUNDS);
  
  return personReturn;
}  
