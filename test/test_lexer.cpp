#include "test_lexer.hpp"

BSTD_TEST_MAIN(test_lexer)


test_lexer::
test_lexer() {
  ADD_TEST(test_lexer::get_next_token);
  ADD_TEST(test_lexer::reset);
  ADD_TEST(test_lexer::lex);
}


void
test_lexer::
get_next_token() {
  lexer l(true);
  l.lex(m_json_string1);
  const auto& tokens = l.get_tokens();

  for(int i = 0; i < tokens.size(); ++i) {
    VERIFY(l.get_next_token() == tokens.at(i), "get token " + std::to_string(i))
  }
}


void
test_lexer::
reset() {
  lexer l(true);
  l.lex(m_json_string1);
  const auto& tokens = l.get_tokens();

  VERIFY(l.get_next_token() == *tokens.cbegin(),
      "lexer::get_next_token first call")
  VERIFY(l.get_next_token() != *tokens.cbegin(),
      "lexer::get_next_token second call")

  l.reset();

  VERIFY(l.get_next_token() == *tokens.cbegin(),
      "lexer::get_next_token after reset")
}


void
test_lexer::
lex() {
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
