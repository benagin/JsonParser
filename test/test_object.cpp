#include "test_object.hpp"

BSTD_TEST_MAIN(test_object)


test_object::
test_object() {
  ADD_TEST(test_object::object_size);
  //ADD_TEST(test_object::object_assignment_operator);
  //ADD_TEST(test_object::object_equal_operator);
  //ADD_TEST(test_object::object_addition_operator);
  ADD_TEST(test_object::object_to_string);
}


void
test_object::
object_size() {
  const auto empty_object = bstd::json::parser::parse("");
  const auto one_object = bstd::json::parser::parse(m_object_path);
  const auto three_object= bstd::json::parser::parse(m_object_large_path);

  VERIFY(empty_object->size() == 0, "empty object size")
  VERIFY(one_object->size() == 1, "single valued object size")
  VERIFY(three_object->size() == 0, "object size with 3 values")
}


/*
void
test_object::
object_assignment_operator() {
  const auto object1 = bstd::json::parser::parse(m_object_path);
  const auto copy = object1;

  // Check member variables.
  const bool test = <insert-test>;
}


void
test_object::
object_equal_operator() {
  const auto object1 = bstd::json::parser::parse(m_object_string1);
  const auto object1_copy = bstd::json::parser::parse(m_object_string1);
  const auto object2 = bstd::json::parser::parse(m_object_string2);

  const bool test1 = *object1 == *object1_copy;
  const bool test2 = *object1 != *object2;

  VERIFY(test1, "object equal comparison operator (==)")
  VERIFY(test1, "object not equal comparison operator (!=)")
}


void
test_object::
object_addition_operator() {
  const auto object1 = bstd::json::parser::parse(m_object_string1);
  const auto object2 = bstd::json::parser::parse(m_object_string2);
  const auto object3 = bstd::json::parser::parse(m_object_string1 + m_object_string2);

  const auto result = *object1 + *object2;

  VERIFY(result.size() == 2, "object addition operator (+) size")
  VERIFY(result == *object3,"object addition operator (+) contents")
}
*/


void
test_object::
object_to_string() {
  const auto object1 = bstd::json::parser::parse(m_object_string1);

  VERIFY(object1->to_string(true) == m_object_string1,
      "object to_string vs. parser output")
}
