#include "test_json.hpp"

BSTD_TEST_MAIN(test_json)


test_json::
test_json() {
  ADD_TEST(test_json::json_size);
  ADD_TEST(test_json::json_assignment_operator);
  ADD_TEST(test_json::json_equal_operator);
  ADD_TEST(test_json::json_addition_operator);
  ADD_TEST(test_json::json_to_string);
}


void
test_json::
json_size() {
  const auto empty_json = bstd::json::parser::parse("");
  const auto one_value = bstd::json::parser::parse(m_json_string1);

  VERIFY(empty_json->size() == 0, "empty basic_json::size")
  VERIFY(one_value->size() == 0, "single valued basic_json::size")
}


void
test_json::
json_assignment_operator() {
  const auto json1 = bstd::json::parser::parse(m_json_string1);
  const auto copy = json1;

  const bool test = json1 == copy;

  VERIFY(test, "basic_json assignment operator");
}


void
test_json::
json_equal_operator() {
  const auto json1 = bstd::json::parser::parse(m_json_string1);
  const auto json1_copy = bstd::json::parser::parse(m_json_string1);
  const auto json2 = bstd::json::parser::parse(m_json_string2);

  const bool test1 = json1 == json1_copy;
  const bool test2 = json1 != json2;

  VERIFY(test1, "basic_json equal comparison operator (==)")
  VERIFY(test2, "basic_json not equal comparison operator (!=)")
}


void
test_json::
json_addition_operator() {
  const auto json1 = bstd::json::parser::parse(m_json_string1);
  const auto json2 = bstd::json::parser::parse(m_json_string2);
  const auto json3 = bstd::json::parser::parse(m_json_string1 + m_json_string2);

  const auto result = *json1 + *json2;

  VERIFY(result.size() == 2, "basic_json addition operator (+)")
}


void
test_json::
json_to_string() {
  const auto json1 = bstd::json::parser::parse(m_json_string1);

  VERIFY(json1->to_string() == m_json_string1, "basic_json::to_string vs. parser output")
}
