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


auto
lexer::
report_error(const std::runtime_error _e) {
  std::cout << m_error_reported << std::endl;
  if(m_error_reported)
    return token(token::invalid);

  if(m_throw)
    throw _e;
  else
    std::cerr << _e.what() << std::endl;

  m_error_reported = true;
  return token(token::invalid);
}


const std::vector<token>
lexer::
get_tokens() const {
  return m_tokens;
}


const token
lexer::
get_next_token() {
  if(m_index == m_tokens.cend()) {
    return report_error(std::runtime_error("Attempt to get a token after all have \
        been retrieved."));
  }

  return *m_index++;
}


auto
lexer::
lex_string(std::string::const_iterator& _csit, const std::string& _json_string) {
  // Consume quote.
  advance_iterator(_csit, 1, _json_string);

  const auto begin = _csit;
  while(_csit != _json_string.cend()) {
    if(*_csit == '\"')
      return token(token::string, std::string(begin, _csit));

    advance_iterator(_csit, 1, _json_string);
  }

  return report_error(bstd::error::context_error(_json_string, begin,
      "String never closed"));
}


auto
lexer::
lex_number(std::string::const_iterator& _csit, const std::string& _json_string) {
  // What type of number are we handling.
  enum { unknown, integer, floating, exponent, signed_exponent};

  const auto begin = _csit;
  if(*begin == '-' or *begin == '+')
    advance_iterator(_csit, 1, _json_string);

  auto type = unknown;
  if(std::isdigit(*_csit)) {
    type = integer;
    std::cout << *_csit << std::endl;
    advance_iterator(_csit, 1, _json_string);
  }
  else if(*_csit == '.') {
    type = floating;
    advance_iterator(_csit, 1, _json_string);
  }

  // TODO: fix this spaghetti.
  while(_csit != _json_string.cend()) {
    std::cout << "dec: " << *_csit << std::endl;
    if(*_csit == '.') {
      if(type == floating or type == exponent)
        return report_error(bstd::error::context_error(_json_string, _csit,
            "Unexpected decimal"));

      type = floating;
    }
    else if(*_csit == 'e' or *_csit == 'E') {
      if(type == exponent)
        return report_error(bstd::error::context_error(_json_string, _csit,
            "Unexpected exponent"));

      type = exponent;
    }
    else if(*_csit == '-' or *_csit == '+') {
      if(type == integer or type == exponent)
        type = signed_exponent;
      else
        return report_error(bstd::error::context_error(_json_string, _csit,
            "Unexpected sign"));
    }
    else if(std::isdigit(*_csit)) {
      if(type == unknown)
        type = integer;
    }
    else {
      if(begin + 1 < _csit)
        advance_iterator(_csit, -1, _json_string);
      return token(token::number, std::string(begin, _csit));
    }

    advance_iterator(_csit, 1, _json_string);
  }

  return report_error(bstd::error::context_error(_json_string, _csit,
      "Unexpectedly reached end of JSON string"));
}


auto
lexer::
lex_literal(const std::string_view& _literal, const token::type _literal_type,
    std::string::const_iterator& _csit, const std::string& _json_string) {
  const auto size = _literal.size();

  if(std::string(_csit, _csit + size) != _literal)
    return report_error(bstd::error::context_error(_json_string, _csit,
        _csit + 4, "Expected the literal \'" + std::string(_literal) + "\'"));

  advance_iterator(_csit, size - 1, _json_string);
  return token(_literal_type);
}


auto
lexer::
lex_true_literal(std::string::const_iterator& _csit,
    const std::string& _json_string) {
  return lex_literal("true", token::true_literal, _csit, _json_string);
}


auto
lexer::
lex_false_literal(std::string::const_iterator& _csit,
    const std::string& _json_string) {
  return lex_literal("false", token::false_literal, _csit, _json_string);
}


auto
lexer::
lex_null_literal(std::string::const_iterator& _csit,
    const std::string& _json_string) {
  return lex_literal("null", token::null_literal, _csit, _json_string);
}


void
lexer::
lex(const std::string& _json_string) {
  // TODO: support nesting.
  // TODO: maybe rework this simple loop system. See advance_iterator spaghetti.
  for(auto csit = _json_string.cbegin(); csit != _json_string.cend(); ++csit) {
    token t;

    const auto cmit = m_char_value_tokens.find(*csit);
    if(cmit != m_char_value_tokens.cend())
      t = token(cmit->second, cmit->first);
    else if(*csit == '\"')
      t = lex_string(csit, _json_string);
    else if(std::isdigit(*csit) or *csit == '-' or *csit == '+' or *csit == '.')
      t = lex_number(csit, _json_string);
    else if(*csit == 't')
      t = lex_true_literal(csit, _json_string);
    else if(*csit == 'f')
      t = lex_false_literal(csit, _json_string);
    else if(*csit == 'n')
      t = lex_null_literal(csit, _json_string);
    else if(isspace(*csit))
      t = token(token::whitespace, *csit);


    m_tokens.push_back(t);

    if(!t.is_valid()) {
      report_error(bstd::error::context_error(_json_string, csit,
          "Character does not match the start of any valid JSON value"));
      return;
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
  return _os << std::endl << _lexer.to_string();
}


void
lexer::
advance_iterator(std::string::const_iterator& _csit,
    const int _distance, const std::string& _json_string) {
  auto& begin = _csit,
        end   = _json_string.cend();

  auto adjustment = -1;
  if(_distance < 0) {
    end = _json_string.cbegin();
    adjustment = 1;
  }

  if(std::abs(std::distance(begin, end)) > std::abs(_distance))
    std::advance(_csit, _distance);
  else if(std::distance(begin, end) == _distance)
    std::advance(_csit, _distance + adjustment);
  else {
    std::cout << _distance << std::endl;
    report_error(bstd::error::context_error(_json_string, _csit,
        "attempting to advance the lexing iterator beyond its bounds"));
  }
}


}
