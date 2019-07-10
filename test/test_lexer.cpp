#include "test_lexer.hpp"

BSTD_TEST_MAIN(test_lexer)


test_lexer::
test_lexer() {
  ADD_TEST(test_lexer::lexer_get_next_token);
}


const bstd::test::result
test_lexer::
lexer_get_next_token() const {
  lexer l1;
  l1.lex(m_json_string1);
  std::vector<token> l1_expected { token() };

  lexer l2;
  l2.lex(m_json_string2);
  std::vector<token> l2_expected { token() };

  const bool test1 = l1.get_tokens() == l1_expected;
  const bool test2 = l2.get_tokens() == l2_expected;

  return bstd::test::result(test1 && test2, "lex failed");
}
