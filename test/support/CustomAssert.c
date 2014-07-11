#include "unity.h"
#include "CustomAssert.h"


void assertEqualPerson(char *expectedName, 
                       int expectedAge,
                       float expectedWeight,
                       Person *actual, 
                       int line, char *msg){
  UNITY_TEST_ASSERT_EQUAL_STRING(expectedName, actual->name, line, "Not the same name");
  UNITY_TEST_ASSERT_EQUAL_INT(expectedAge, actual->age, line, "Not the same age");
  UNITY_TEST_ASSERT_FLOAT_WITHIN(0.0001, expectedWeight, actual->weight, line, "Not the same weight");
}