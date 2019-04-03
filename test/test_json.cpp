#include "test_json.hpp"

BSTD_TEST_MAIN(test_json)


test_json::
test_json() {
  ADD_TEST(test_json::json_size);
  ADD_TEST(test_json::json_assignment_operator);
  ADD_TEST(test_json::json_equal_operator);
  ADD_TEST(test_json::json_addition_operator);
  ADD_TEST(test_json::json_to_string);
  ADD_TEST(test_json::json_add_value);
}


const bstd::test::result
test_json::
json_size() const {
  const auto empty_json = bstd::json::parse("");
  const auto one_value = bstd::json::parse(m_json_string1);

  const auto zero = empty_json->size();
  const auto one = one_value->size();

  return bstd::test::result(zero == 0 && one == 1, "json size failed");
}


const bstd::test::result
test_json::
json_assignment_operator() const {
  const auto json1 = bstd::json::parse(m_json_string1);
  const auto copy = json1;

  // Check member variables.
  const bool test = copy->get_path() == json1->get_path()
      && copy->get_value() == json1->get_value();

  return bstd::test::result(test, "json assignment failed");
}


const bstd::test::result
test_json::
json_equal_operator() const {
  const auto json1 = bstd::json::parse(m_json_string1);
  const auto json1_copy = bstd::json::parse(m_json_string1);
  const auto json2 = bstd::json::parse(m_json_string2);

  const bool test1 = *json1 == *json1_copy;
  const bool test2 = *json1 != *json2;

  return bstd::test::result(test1 && test2,
      "json equal operator failed");
}


const bstd::test::result
test_json::
json_addition_operator() const {
  const auto json1 = bstd::json::parse(m_json_string1);
  const auto json2 = bstd::json::parse(m_json_string2);
  const auto json3 = bstd::json::parse(m_json_string1 + m_json_string2);

  const auto result = *json1 + *json2;

  return bstd::test::result(result.size() == 2 && result  == *json3,
      "json addition operator failed");
}


const bstd::test::result
test_json::
json_to_string() const {
  const auto json1 = bstd::json::parse(m_json_string1);

  const auto test = json1->to_string() == m_json_string1;

  return bstd::test::result(test, "json to string failed");
}


const bstd::test::result
test_json::
json_add_value() const {
  const auto json1 = bstd::json::parse(m_json_string1);
  const auto json2 = bstd::json::parse(m_json_string2);
  const auto json3 = bstd::json::parse(m_json_string1 + m_json_string2);

  const auto result = json1->add_value(json2->get_value());

  return bstd::test::result(json3->get_value() == result, "json add value failed");
}
