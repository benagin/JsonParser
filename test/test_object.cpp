#include "test_object.hpp"

BSTD_TEST_MAIN(test_object)


test_object::
test_object() {
  ADD_TEST(test_object::object_size);
  //ADD_TEST(test_object::object_assignment_operator);
  //ADD_TEST(test_object::object_equal_operator);
  //ADD_TEST(test_object::object_addition_operator);
  ADD_TEST(test_object::object_to_string);
  ADD_TEST(test_object::object_add_value);
}


const bstd::test::result
test_object::
object_size() const {
  const auto empty_object = bstd::json::parse("")->get_value();
  const auto one_object = bstd::json::parse(m_object_path)->get_value();
  const auto three_object= bstd::json::parse(m_object_large_path)->get_value();

  const auto zero = empty_object->size();
  const auto one = one_object->size();
  const auto three = three_object->size();

  return bstd::test::result(zero == 0 && one == 1 && three == 3,
      "object size failed");
}


/*
const bstd::test::result
test_object::
object_assignment_operator() const {
  const auto object1 = bstd::json::parse(m_object_path)->get_value();
  const auto copy = object1;

  // Check member variables.
  const bool test = <insert-test>;

  return bstd::test::result(test, "object assignment failed");
}


const bstd::test::result
test_object::
object_equal_operator() const {
  const auto object1 = bstd::json::parse(m_object_string1);
  const auto object1_copy = bstd::json::parse(m_object_string1);
  const auto object2 = bstd::json::parse(m_object_string2);

  const bool test1 = *object1 == *object1_copy;
  const bool test2 = *object1 != *object2;

  return bstd::test::result(test1 && test2,
      "object equal operator failed");
}


const bstd::test::result
test_object::
object_addition_operator() const {
  const auto object1 = bstd::json::parse(m_object_string1);
  const auto object2 = bstd::json::parse(m_object_string2);
  const auto object3 = bstd::json::parse(m_object_string1 + m_object_string2);

  const auto result = *object1 + *object2;

  return bstd::test::result(result.size() == 2 && result  == *object3,
      "object addition operator failed");
}
*/


const bstd::test::result
test_object::
object_to_string() const {
  const auto object1 = bstd::json::parse(m_object_string1);

  const auto test = object1->to_string(true) == m_object_string1;
  std::cout << "to_string: " << object1->to_string(true) << std::endl;
  std::cout << "string: " << m_object_string1  << std::endl;

  return bstd::test::result(test, "object to string failed");
}


const bstd::test::result
test_object::
object_add_value() const {
  const auto object1 = bstd::json::parse(m_object_string1);
  const auto object2 = bstd::json::parse(m_object_string2);
  const auto object3 = bstd::json::parse(m_object_string1 + m_object_string2);

  const auto result = object1->add_value(object2->get_value());

  return bstd::test::result(object3->get_value() == result,
      "object add value failed");
}
