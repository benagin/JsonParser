#ifndef TEST_OBJECT_HPP_
#define TEST_OBJECT_HPP_

#include <bstd_json.hpp>
#include <bstd_test.hpp>

class test_object final : public bstd::test::test {

  public:

    test_object();

    const bstd::test::result object_size() const;
    //const bstd::test::result object_assignment_operator() const;
    //const bstd::test::result object_equal_operator() const;
    //const bstd::test::result object_addition_operator() const;
    const bstd::test::result object_to_string() const;
    const bstd::test::result object_add_value() const;

  private:

    std::string m_object_path{"test/json/json_files/object.json"};
    std::string m_object_large_path{"test/json/json_files/object_large.json"};

    std::string m_object_string1{"{ \"name\": \"value\" }"};
    std::string m_object_string2{"{ \"name2\": \"value2\" }"};

};


#endif
