#ifndef Map_H
#define Map_H

#include <stdio.h>

#define isBucketEmpty(x) ((x) == NULL || (x) == (void *)-1)
#define isBucketMarked(x) (x) == (void *)-1


typedef struct Map Map;

struct Map{
  void **bucket;
  int length;       //Total number buckets
  int size;         //Number of buckets used
};

Map *mapNew(int length);

//Implementing Seperate chaining method
void mapStore(Map *map,
              void *element, 
              int (*compare)(void *, void *),
              unsigned int (*hash)(void *));

//Implementing Linear probing method              
void mapLinearStore(Map *map,
              void *element, 
              int (*compare)(void *, void *),
              unsigned int (*hash)(void *));

//Implementing Seperate chaining method              
void *mapFind(Map *map,
              void *element, 
              int (*compare)(void *, void *),
              unsigned int (*hash)(void *));

//Implementing Linear probing method          
void *mapLinearFind(Map *map,
              void *element, 
              int (*compare)(void *, void *),
              unsigned int (*hash)(void *));              

//Implementing Seperate chaining method              
void *mapRemove(Map *map,
              void *element, 
              int (*compare)(void *, void *),
              unsigned int (*hash)(void *));

//Implementing Linear probing method              
void *mapLinearRemove(Map *map,
              void *element, 
              int (*compare)(void *, void *),
              unsigned int (*hash)(void *));

#endif // Map_H
