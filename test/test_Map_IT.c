#include "unity.h"
#include "Map.h"
#include "Person.h"
#include "List.h"
#include "CustomAssert.h"
#include "mock_Hash.h"
#include "ComparePerson.h"
#include "CException.h"
#include "ErrorCode.h"

#define getPersonFromBucket(x) ((Person *)((List *)(x))->data)

void setUp(void){}
void tearDown(void){}

void test_mapNew_given_length_of_10_should_create_a_new_map(){
	Map *map = mapNew(10);
  
  TEST_ASSERT_NOT_NULL(map);
  TEST_ASSERT_NOT_NULL(map->bucket);
  TEST_ASSERT_EQUAL(10, map->length);
  TEST_ASSERT_EQUAL(0, map->size);
}

void test_mapStore_given_Ali_should_add_it_to_map(){
  Person *person = personNew("Ali", 25, 70.3);
  Map *map = mapNew(5);
  
  hash_ExpectAndReturn(person, 3);
  
  mapStore(map, person, comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, getPersonFromBucket(map->bucket[3]));
}

void test_mapStore_given_Ali_but_Ali_is_in_the_Map_should_throw_ERR_SAME_ELEMENT_exception(){
  CEXCEPTION_T e;
  Person *person = personNew("Ali", 25, 70.3);
  Map *map = mapNew(5);
  List *list = listNew(person, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(person, 3);
  
  Try{
    mapStore(map, person, comparePerson, hash);
    TEST_FAIL_MESSAGE("Expect ERR_SAME_ELEMENT exception to be thrown");
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_SAME_ELEMENT, e);
    TEST_ASSERT_NOT_NULL(map->bucket[3]);
    TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, getPersonFromBucket(map->bucket[3]));
  }
}

void test_mapStore_given_Ali_Zorro_both_has_same_hash_value(){
  CEXCEPTION_T e;
  Person *personAli = personNew("Ali", 25, 70.3);
  Person *personZorro = personNew("Zorro", 35, 65.5);
  Map *map = mapNew(5);
  List *list = listNew(personAli, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(personZorro, 3);
  
  mapStore(map, personZorro, comparePerson, hash);

	TEST_ASSERT_NOT_NULL(map->bucket[3]);
	TEST_ASSERT_EQUAL_Person("Zorro", 35, 65.5, getPersonFromBucket(map->bucket[3]));
	TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, getPersonFromBucket(((List *)map->bucket[3])->next));

}

void test_mapStore_given_Ali_Dave_should_add_it_to_map(){
  Person *person = personNew("Ali", 25, 70.3);
  Person *person2 = personNew("Dave", 33, 62.2);
  Map *map = mapNew(5);
  
  hash_ExpectAndReturn(person, 3);
  hash_ExpectAndReturn(person2, 4);
  
  mapStore(map, person, comparePerson, hash);
  mapStore(map, person2, comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  TEST_ASSERT_NOT_NULL(map->bucket[4]);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, getPersonFromBucket(map->bucket[3]));
  TEST_ASSERT_EQUAL_Person("Dave", 33, 62.2, getPersonFromBucket(map->bucket[4]));
}

void test_mapFind_given_Ali_and_Ali_is_in_the_map(){
	Person *personAli = personNew("Ali", 25, 70.3);
	Person *personToFind = personNew("Ali", 0, 0);
  Person *result;
	Map *map = mapNew(5);
  List *list = listNew(personAli, NULL);
	map->bucket[3] = list;
	
	hash_ExpectAndReturn(personToFind, 3);
  
  result = mapFind(map, personToFind, comparePerson, hash);
  
  TEST_ASSERT_EQUAL_PTR(personAli, result);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, result);
}

void test_mapFind_given_Ali_but_Ali_is_not_in_map_should_return_NULL(){
	Person *personToFind = personNew("Ali", 0, 0);
  Person *result;
	Map *map = mapNew(5);
	map->bucket[3] = NULL;
	
	hash_ExpectAndReturn(personToFind, 3);
  
  result = mapFind(map, personToFind, comparePerson, hash);
  
  TEST_ASSERT_EQUAL_PTR(NULL, result);
}

void test_mapFind_given_Ali_and_Ali_is_in_the_linked_list(){
	Person *personAli = personNew("Ali", 25, 70.3);
	Person *personJames = personNew("James", 22, 75.1);
	Person *personZorro = personNew("Zorro", 35, 65.5);
	Person *personToFind = personNew("Ali", 0, 0);
  Person *result;
	Map *map = mapNew(5);
  List *list = listNew(personAli, NULL);
  list = listNew(personJames, list);
  list = listNew(personZorro, list);
	map->bucket[3] = list;
	
	hash_ExpectAndReturn(personToFind, 3);
  
  result = mapFind(map, personToFind, comparePerson, hash);
  
  TEST_ASSERT_EQUAL_PTR(personAli, result);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, result);
}

void test_mapFind_given_Ali_and_Ali_is_NOT_in_the_linked_list_given_James_Zorro(){
	Person *personJames = personNew("James", 22, 75.1);
	Person *personZorro = personNew("Zorro", 35, 65.5);
	Person *personToFind = personNew("Ali", 0, 0);
  Person *result;
	Map *map = mapNew(5);
  List *list = listNew(personZorro, NULL);
  list = listNew(personJames, list);
	map->bucket[3] = list;
	
	hash_ExpectAndReturn(personToFind, 3);
  
  result = mapFind(map, personToFind, comparePerson, hash);
  
  TEST_ASSERT_EQUAL_PTR(NULL, result);
}

void test_mapRemove_given_Ali_and_Ali_is_in_the_map(){
	Person *personAli = personNew("Ali", 25, 70.3);
	Person *personToRemove = personNew("Ali", 0, 0);
  Person *result;
	Map *map = mapNew(5);
  List *list = listNew(personAli, NULL);
	map->bucket[3] = list;
	
	hash_ExpectAndReturn(personToRemove, 3);
  
  result = mapRemove(map, personToRemove, comparePerson, hash);
  
  TEST_ASSERT_EQUAL_PTR(personAli, result);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, result);
  TEST_ASSERT_NULL(map->bucket[3]);
}

void test_mapRemove_given_Ali_but_Ali_is_not_in_map_should_return_NULL(){
	Person *personToRemove = personNew("Ali", 0, 0);
  Person *result;
	Map *map = mapNew(5);
	map->bucket[3] = NULL;
	
	hash_ExpectAndReturn(personToRemove, 3);
  
  result = mapRemove(map, personToRemove, comparePerson, hash);
  
  TEST_ASSERT_EQUAL_PTR(NULL, result);
}

void test_mapRemove_given_Ali_and_Ali_is_in_the_linked_list(){
	Person *personAli = personNew("Ali", 25, 70.3);
  Person *personJames = personNew("James", 22, 75.1);
	Person *personZorro = personNew("Zorro", 35, 65.5);
	Person *personToFind = personNew("Ali", 0, 0);
  Person *result;
	Map *map = mapNew(5);
  List *list = listNew(personAli, NULL);
  list = listNew(personJames, list);
  list = listNew(personZorro, list);
	map->bucket[3] = list;
	
	hash_ExpectAndReturn(personToFind, 3);
  // listDump(list, personDump);
  result = mapRemove(map, personToFind, comparePerson, hash);
  
  TEST_ASSERT_EQUAL_PTR(personAli, result);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, result);
  TEST_ASSERT_NULL((list->next)->next);
  
  // listDump(list, personDump);
}

void test_mapRemove_given_Ali_and_Ali_is_NOT_in_the_linked_list_given_James_Zorro(){
	Person *personJames = personNew("James", 22, 75.1);
	Person *personZorro = personNew("Zorro", 35, 65.5);
	Person *personToRemove = personNew("Ali", 0, 0);
  Person *result;
	Map *map = mapNew(5);
  List *list = listNew(personZorro, NULL);
  list = listNew(personJames, list);
	map->bucket[3] = list;
	
	hash_ExpectAndReturn(personToRemove, 3);
  
  result = mapRemove(map, personToRemove, comparePerson, hash);
  
  TEST_ASSERT_EQUAL_PTR(NULL, result);
}

void test_mapRemove_given_Ali_and_Ali_is_the_middle_of_the_linked_list(){
	Person *personAli = personNew("Ali", 25, 70.3);
  Person *personJames = personNew("James", 22, 75.1);
	Person *personZorro = personNew("Zorro", 35, 65.5);
	Person *personToFind = personNew("Ali", 0, 0);
  Person *result;
	Map *map = mapNew(5);
  List *list = listNew(personJames, NULL);
  list = listNew(personAli, list);
  list = listNew(personZorro, list);
	map->bucket[3] = list;
	
	hash_ExpectAndReturn(personToFind, 3);
  // listDump(list, personDump);
  result = mapRemove(map, personToFind, comparePerson, hash);
  
  TEST_ASSERT_EQUAL_PTR(personAli, result);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, result);
  TEST_ASSERT_EQUAL_Person("Zorro", 35, 65.5, getPersonFromBucket(map->bucket[3]));
	TEST_ASSERT_EQUAL_Person("James", 22, 75.1, getPersonFromBucket(((List *)map->bucket[3])->next));
  
  // listDump(list, personDump);
}