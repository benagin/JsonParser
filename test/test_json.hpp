#ifndef TEST_JSON_HPP_
#define TEST_JSON_HPP_

#include <bstd_json.hpp>
#include <bstd_test.hpp>

class test_json final : public bstd::test::test {

  public:

    test_json();

    const bstd::test::result json_size() const;
    const bstd::test::result json_assignment_operator() const;
    const bstd::test::result json_equal_operator() const;
    const bstd::test::result json_addition_operator() const;
    const bstd::test::result json_to_string() const;
    const bstd::test::result json_add_value() const;

  private:

    std::string m_json_string1{"{ \"name1\": \"value1\" }"};
    std::string m_json_string2{"{ \"name2\": \"value2\" }"};

};


#endif
