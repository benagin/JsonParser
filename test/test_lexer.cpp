#include "test_lexer.hpp"

BSTD_TEST_MAIN(test_lexer)


test_lexer::
test_lexer() {
  ADD_TEST(test_lexer::lexer_get_next_token);
  ADD_TEST(test_lexer::lexer_lex);
}


void
test_lexer::
lexer_get_next_token() {
  lexer l(true);
  l.lex(m_json_string1);

  const auto& tokens = l.get_tokens();
  VERIFY(l.get_next_token() == *tokens.cbegin(), "lexer::get_next_token first call")
  VERIFY(l.get_next_token() == *(tokens.cbegin() + 1), "lexer::get_next_token first call")
  VERIFY(l.get_next_token() == *(tokens.cbegin() + 2), "lexer::get_next_token first call")
  VERIFY(l.get_next_token() == *(tokens.cbegin() + 3), "lexer::get_next_token first call")
}


void
test_lexer::
lexer_lex() {
  lexer l1(true);
  l1.lex(m_json_string1);
  std::vector<token> l1_expected { token() };

  lexer l2(true);
  l2.lex(m_json_string2);
  std::vector<token> l2_expected { token() };

  VERIFY(l1.get_tokens() == l1_expected,
      "lexer::lex JSON string: " + m_json_string1)
  VERIFY(l2.get_tokens() == l2_expected,
      "lexer::lex JSON string: " + m_json_string2)
}
