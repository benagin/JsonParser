#ifndef TEST_JSON_HPP_
#define TEST_JSON_HPP_

#include <bstd_json.hpp>
#include <bstd_test.hpp>

class test_json final : public bstd::test::unit_tester {

  public:

    test_json();

    void json_size();
    void json_assignment_operator() ;
    void json_equal_operator();
    void json_addition_operator();
    void json_to_string();

  private:

    std::string m_json_short_string{"{ }"};
    std::string m_json_string1{"{ \"name1\": \"value1\" }"};
    std::string m_json_string2{"{ \"name2\": \"value2\" }"};

};


#endif
