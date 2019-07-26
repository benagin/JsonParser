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
  lexer l(true, false);
  l.lex(m_simple_objects);
  const auto& tokens = l.get_tokens();

  for(int i = 0; i < tokens.size(); ++i) {
    VERIFY(l.get_next_token() == tokens.at(i), "get token " + std::to_string(i))
  }
}


void
test_lexer::
reset() {
  lexer l(true, false);
  l.lex(m_simple_objects);
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
  lexer symbols_lexer(true, false);
  symbols_lexer.lex(m_symbols);

  VERIFY(symbols_lexer.get_tokens() == m_lexed_symbols,
      "lexer::lex JSON symbols")

  lexer simple_objects_lexer(true, false);
  simple_objects_lexer.lex(m_simple_objects);

  VERIFY(simple_objects_lexer.get_tokens() == m_lexed_simple_objects,
      "lexer::lex JSON simple objects")

  lexer numbers_lexer(true, false);
  numbers_lexer.lex(m_numbers);

  VERIFY(numbers_lexer.get_tokens() == m_lexed_numbers,
      "lexer::lex JSON numbers")

  lexer ws_lexer(true, false);
  ws_lexer.lex(m_whitespace);

  VERIFY(ws_lexer.get_tokens() == m_lexed_whitespace,
      "lexer::lex JSON whitespace")

}
