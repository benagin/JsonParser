#ifndef TEST_LEXER_HPP_
#define TEST_LEXER_HPP_

#include <bstd_json.hpp>
#include <bstd_test.hpp>

using namespace bstd::json::parser;

class test_lexer final : public bstd::test::unit_tester {

  public:

    test_lexer();

    const bstd::test::result lexer_get_next_token() const;
    const bstd::test::result lexer_lex() const;

  private:

    std::string m_json_string1{"{ \"name1\": \"value1\" }"};
    std::string m_json_string2{"[ 1, true,  \"string\", null] "};

};


#endif
