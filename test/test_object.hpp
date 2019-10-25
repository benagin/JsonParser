#ifndef TEST_OBJECT_HPP_
#define TEST_OBJECT_HPP_

#include <bstd_json.hpp>
#include <bstd_test.hpp>

class test_object final : public bstd::test::unit_tester {

  public:

    test_object();

    void object_size();
    //void object_assignment_operator();
    //void object_equal_operator();
    //void object_addition_operator();
    void object_to_string();

  private:

    std::string m_object_path{"test/json/json_files/object.json"};
    std::string m_object_large_path{"test/json/json_files/object_large.json"};

    std::string m_object_string1{"{ \"name\": \"value\" }"};
    std::string m_object_string2{"{ \"name2\": \"value2\" }"};

};


#endif
