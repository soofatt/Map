#include "ComparePerson.h"
#include "Person.h"
#include <String.h>

int comparePerson(void *person1, void *person2){
  Person *personOne = (Person *)person1;
  Person *personTwo = (Person *)person2;
  
  if(strcmp(personOne->name, personTwo->name) == 0)
    return 1;
  else
    return 0;
}