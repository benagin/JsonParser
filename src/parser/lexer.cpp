#include "lexer.hpp"


namespace bstd::json::parser {


const std::unordered_map<char, token::type> lexer::m_char_value_tokens = {
  { '{', token::begin_object },
  { '}', token::end_object },
  { '[', token::begin_array},
  { ']', token::end_array },
  { ',', token::comma },
  { ':', token::colon },
};


const std::vector<token>&
lexer::
get_tokens() const noexcept {
  return m_tokens;
}


const lexer::CVIT
lexer::
next_token() {
  if(m_index == m_tokens.cend())
    throw std::runtime_error("Attempt to process a token after all have been \
        retrieved.");

  return m_index++;
}


bool
lexer::
apply_regex_filter(const std::regex& _regex) const {
  std::smatch match;
  return std::regex_search(get_element(), get_container()->cend(), match, _regex)
      ? match.position() == 0 : false;
}


const token
lexer::
lex_string() {
  // TODO: use regex.
  return token(token::invalid);
}


const token
lexer::
lex_number() {
  // TODO: use regex.
  return token(token::invalid);
}


const token
lexer::
lex_literal(const token::type& _type, const std::regex& _regex) {
  std::smatch match;
  if(!std::regex_search(get_element(), get_container()->cend(), match, _regex)
      or match.position() != 0)
    return token(token::invalid);

  advance_index(match.length() - 1);
  return token(_type);
}


void
lexer::
lex() {
  // TODO: support nesting.
  for(;;) {
    token t;

    const auto cmit = m_char_value_tokens.find(*get_element());
    if(cmit != m_char_value_tokens.cend())
      t = token(cmit->second, cmit->first);
    else if(apply_regex_filter(DOUBLE_QUOTE_REGEX))
      t = lex_string();
    else if(apply_regex_filter(BEGIN_NUMBER_REGEX))
      t = lex_number();
    else if(apply_regex_filter(TRUE_LITERAL_REGEX))
      t = lex_literal(token::true_literal, TRUE_LITERAL_REGEX);
    else if(apply_regex_filter(FALSE_LITERAL_REGEX))
      t = lex_literal(token::false_literal, FALSE_LITERAL_REGEX);
    else if(apply_regex_filter(NULL_LITERAL_REGEX))
      t = lex_literal(token::null_literal, NULL_LITERAL_REGEX);
    // TODO: use regex to parse large chunks of whitespace
    else if(isspace(*get_element()))
      t = token(token::whitespace, *get_element());

    m_tokens.push_back(t);

    if(!t.is_valid()) {
      report_error(bstd::error::context_error(*get_container(), get_element(),
          "Character does not match the start of any valid JSON value"));
      break;
    }

    // TODO: figure out a better loop system than this.
    if(peek_next_element() != get_container()->cend()) {
      next_element();
    }
    else
      break;
  }

  m_tokens.push_back(token(token::end_json));
  m_index = m_tokens.cbegin();

  if(m_debug) {
    std::cout << *this << std::endl;
  }
}


void
lexer::
reset() noexcept {
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
  return _os << std::endl << _lexer.to_string();
}


}
