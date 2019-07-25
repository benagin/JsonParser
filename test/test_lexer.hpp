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

    const std::string m_symbols{"{}[],:"};
    const std::vector<token> m_lexed_symbols {{
        { token::begin_object },
        { token::end_object },
        { token::begin_array },
        { token::end_array },
        { token::comma },
        { token::colon },
        { token::end_json }
    }};

    const std::string m_simple_objects{"[1,true,\"string\",null,false]"};
    const std::vector<token> m_lexed_simple_objects {{
        { token::begin_array },
        { token::number, "1" },
        { token::comma },
        { token::true_literal },
        { token::comma },
        { token::begin_string },
        { token::string, "string"},
        { token::end_string },
        { token::comma },
        { token::null_literal },
        { token::comma },
        { token::false_literal},
        { token::end_array },
        { token::end_json }
    }};

    const std::string m_numbers{"[1,2.5,0,-0.000,0.5,-5.1,-.5e-10,5.123E5]"};
    const std::vector<token> m_lexed_numbers {{
        { token::begin_array },
        { token::number, "1" },
        { token::comma },
        { token::number, "2.5" },
        { token::comma },
        { token::number, "0" },
        { token::comma },
        { token::number, "-0.000" },
        { token::comma },
        { token::number, "0.5" },
        { token::comma },
        { token::number, "-5.1" },
        { token::comma },
        { token::number, "-.5e-10" },
        { token::comma },
        { token::number, "5.123E5" },
        { token::end_array },
        { token::end_json }
    }};

    const std::string m_whitespace{"  [ 1\v ,\f 3,\rnull   ,\t ]\n"};
    const std::vector<token> m_lexed_whitespace {{
        { token::whitespace },
        { token::whitespace },
        { token::whitespace },
        { token::begin_array },
        { token::whitespace },
        { token::number, "1" },
        { token::whitespace, "\v" },
        { token::whitespace },
        { token::comma },
        { token::whitespace, "\f"},
        { token::whitespace },
        { token::number, "3" },
        { token::whitespace, "\r" },
        { token::null_literal },
        { token::whitespace },
        { token::whitespace },
        { token::whitespace },
        { token::comma },
        { token::whitespace, "\t" },
        { token::whitespace },
        { token::end_array },
        { token::whitespace, "\n" },
        { token::end_json }
    }};

};


#endif
