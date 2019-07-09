#include "lexer.hpp"


namespace bstd::json::parser {


void
lexer::
lex(const std::string& _json_string) {
  // TODO: Figure out what to do with errors.
  // TODO: Create argument for allowing exceptions.

  // The first thing we do here is handle some special cases were we gather more
  // information to construct a more abstract object. These cases include
  // strings, numbers, literals, and whitespace.
  // If none of these conditions apply we simply create a token with the
  // character.
  // TODO: support nesting.
  for(auto csit = _json_string.cbegin(); csit != _json_string.cend();
      ++csit) {
    token t;

    if (*csit == '\"') {
      // TODO: handle strings.
    } else if (isdigit(*csit) or *csit == '-') {
      // TODO: handle numbers.
    } else if (*csit == 't') {
      // TODO: handle the literal true.
    } else if (*csit == 'f') {
      // TODO: handle the literal false.
    } else if (*csit == 'n') {
      // TODO: handle the literal null.
    } else if (isspace(*csit)) {
      // TODO: handle whitespace.
    } else if (m_char_value_tokens.find(*csit) != m_char_value_tokens.cend()) {
      t.set_type(m_char_value_tokens.find(*csit)->second);
      t.set_value(*csit);
    }

    if (!t.is_valid()) {
      // Throw if flag is not set.
    }

    m_tokens.push_back(t);
  }
}


const token
lexer::
get_next_token() {
  if(m_index == m_tokens.cend())
    throw std::out_of_range("Attempt to get a token after all have \
        been retrieved.");

  return *m_index++;
}


std::ostream&
operator<<(std::ostream& _os, const lexer& _lexer) {
  _os << '[';
  for(int i = 0; i < _lexer.m_tokens.size(); ++i) {
    _os << _lexer.m_tokens.at(i) << ' ';

    if(i != _lexer.m_tokens.size() - 1)
      _os << ',';
  }
  _os << ']' << std::endl;

  return _os;
}


}
