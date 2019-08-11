#include "test_lexer.hpp"

BSTD_TEST_MAIN(test_lexer)

test_lexer::
test_lexer() {
  ADD_TEST(test_lexer::next_token);
  ADD_TEST(test_lexer::reset);
  ADD_TEST(test_lexer::lex);
  ADD_TEST(test_lexer::lex_bad_input);
}


void
test_lexer::
next_token() {
  lexer l(m_simple_objects, true, false);
  l.lex();
  const auto& tokens = l.get_tokens();

  for(int i = 0; i < tokens.size(); ++i)
    VERIFY(*l.next_token() == tokens.at(i), "next token " + std::to_string(i))
}


void
test_lexer::
reset() {
  lexer l(m_simple_objects, true, false);
  l.lex();
  const auto& tokens = l.get_tokens();

  VERIFY(*l.next_token() == *tokens.cbegin(),
      "lexer::next_token first call")
  VERIFY(*l.next_token() != *tokens.cbegin(),
      "lexer::next_token second call")

  l.reset();

  VERIFY(*l.next_token() == *tokens.cbegin(),
      "lexer::next_token after reset")
}


void
test_lexer::
lex() {
  lexer symbols_lexer(m_symbols, true, false);
  symbols_lexer.lex();

  VERIFY(symbols_lexer.get_tokens() == m_lexed_symbols,
      "lexer::lex JSON symbols")

  lexer simple_objects_lexer(m_simple_objects, true, false);
  simple_objects_lexer.lex();

  VERIFY(simple_objects_lexer.get_tokens() == m_lexed_simple_objects,
      "lexer::lex JSON simple objects")

  lexer numbers_lexer(m_numbers, true, false);
  numbers_lexer.lex();

  VERIFY(numbers_lexer.get_tokens() == m_lexed_numbers,
      "lexer::lex JSON numbers")

  lexer ws_lexer(m_whitespace, true, false);
  ws_lexer.lex();

  VERIFY(ws_lexer.get_tokens() == m_lexed_whitespace,
      "lexer::lex JSON whitespace")
}


void
test_lexer::
lex_bad_input() {
  lexer bad_input_lexer1(m_bad_input1, true, false);
  bad_input_lexer1.lex();

  VERIFY(bad_input_lexer1.get_tokens() == m_lexed_bad_input1,
      "lexer::lex_bad_input bad_input1")

  lexer bad_input_lexer2(m_bad_input2, true, false);
  bad_input_lexer2.lex();

  VERIFY(bad_input_lexer2.get_tokens() == m_lexed_bad_input2,
      "lexer::lex_bad_input bad_input2")

}
