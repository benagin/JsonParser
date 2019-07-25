#ifndef TEST_LEXER_HPP_
#define TEST_LEXER_HPP_

#include <bstd_json.hpp>
#include <bstd_test.hpp>

using namespace bstd::json::parser;

class test_lexer final : public bstd::test::unit_tester {

  public:

    test_lexer();

    void get_next_token();
    void reset();
    void lex();

  private:

    std::string m_symbols{"{}[],:"};
    std::vector<token> m_lexed_symbols {{
        { token::begin_object },
        { token::end_object },
        { token::begin_array },
        { token::end_array },
        { token::comma },
        { token::colon },
        { token::end_json }
    }};

    std::string m_simple_objects{"[ 1, true,  \"string\", null, false] "};
    std::vector<token> m_lexed_simple_objects {{

    }};

};


#endif
