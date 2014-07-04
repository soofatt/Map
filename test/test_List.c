#include "unity.h"
#include "List.h"

void setUp(void){}
void tearDown(void){}

void test_List_given_integer_5_should_create_list(void){
	List *list;
  int int5 = 5;
  
  list = listNew(&int5, NULL);
  
  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_EQUAL(5, *(int *)list->data);
}
