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


const auto
lexer::
apply_regex_filter(const token::type& _type, const std::regex& _regex) {
  std::smatch results;
  if(!std::regex_search(get_element(), get_container()->cend(), results, _regex))
    return token(token::invalid);

  if(results.empty())
    return token(token::invalid);

  if(results.position() != 0)
    return token(token::invalid);

  const auto& match = results.cbegin();

  advance_index(match->length());

  if(token::is_value_required(_type)) {
    std::string value = *match;
    // Consume quotes.
    if(_type == token::string)
      value = value.substr(1, match->length() - 2);

    return token(_type, value);
  }

  return token(_type);
}


void
lexer::
lex() {
  std::string s;
  while(get_element() != get_container()->cend()) {
    token t;

    const auto cmit = m_char_value_tokens.find(*get_element());
    if(cmit != m_char_value_tokens.cend()) {
      t = token(cmit->second);
      next_element();
    }
    else if(*get_element() == '\"')
      t = apply_regex_filter(token::string, STRING_REGEX);
    else if(std::isdigit(*get_element()) or *get_element()== '+'
        or *get_element() == '-')
      t = apply_regex_filter(token::number, NUMBER_REGEX);
    else if(*get_element() == 't')
      t = apply_regex_filter(token::true_literal, TRUE_LITERAL_REGEX);
    else if(*get_element() == 'f')
      t = apply_regex_filter(token::false_literal, FALSE_LITERAL_REGEX);
    else if(*get_element() == 'n')
      t = apply_regex_filter(token::null_literal, NULL_LITERAL_REGEX);
    else if(isspace(*get_element()))
      t = apply_regex_filter(token::whitespace, WHITESPACE_REGEX);

    m_tokens.push_back(t);

    if(!t.is_valid()) {
      report_error(bstd::error::context_error(*get_container(), get_element(),
            "Character does not match the start of any valid JSON value"));
      break;
    }
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
