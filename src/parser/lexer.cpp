#include "lexer.hpp"


namespace bstd::json::parser {

const std::vector<token>
lexer::
get_tokens() const {
  return m_tokens;
}


const token
lexer::
get_next_token() {
  if(m_index == m_tokens.cend())
    throw std::out_of_range("Attempt to get a token after all have \
        been retrieved.");

  return *m_index++;
}


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

  m_tokens.push_back(token(token::end_json));
  m_index = m_tokens.cbegin();

  if(m_debug) {
    std::cout << *this << std::endl;
  }
}


void
lexer::
reset() {
  m_index = m_tokens.cbegin();
}


const std::string
lexer::
to_string() const {
  std::string result = "[";

  for(int i = 0; i < m_tokens.size(); ++i) {
    result += ' ';
    result += m_tokens.at(i).to_string();

    if(i != m_tokens.size() - 1)
      result += ',';
  }

  return result += " ]";
}


std::ostream&
operator<<(std::ostream& _os, const lexer& _lexer) {
  return _os << _lexer.to_string();
}


}
