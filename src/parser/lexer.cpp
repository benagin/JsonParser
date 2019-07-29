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


const std::vector<token>
lexer::
get_tokens() const {
  return m_tokens;
}


const token
lexer::
get_next_token() {
  if(m_index == m_tokens.cend()) {
    report_error(std::runtime_error("Attempt to get a token after all have \
        been retrieved."));
    return token(token::invalid);
  }

  return *m_index++;
}


auto
lexer::
apply_regex_filter(const std::string::const_iterator& _target,
    const std::regex& _regex) const {
  return std::regex_match(std::string(_target, _target + 1), DOUBLE_QUOTE_REGEX);
}


auto
lexer::
apply_regex_filter(const std::string::const_iterator& _first,
    const std::string::const_iterator& _last, const std::regex& _regex) const {
  std::smatch match;
  return std::regex_search(_first, _last, match, _regex)
      ? match.position() == 0 : false;
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

  report_error(bstd::error::context_error(_json_string, begin,
      "String never closed"));
  return token(token::invalid);
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
    advance_iterator(_csit, 1, _json_string);
  }
  else if(*_csit == '.') {
    type = floating;
    advance_iterator(_csit, 1, _json_string);
  }

  // TODO: fix this spaghetti.
  // TODO: fix this eating commas after integers.
  while(_csit != _json_string.cend()) {
    if(*_csit == '.') {
      if(type == floating or type == exponent) {
        report_error(bstd::error::context_error(_json_string, _csit,
            "Unexpected decimal"));
        return token(token::invalid);
      }

      type = floating;
    }
    else if(*_csit == 'e' or *_csit == 'E') {
      if(type == exponent) {
        report_error(bstd::error::context_error(_json_string, _csit,
            "Unexpected exponent"));
        return token(token::invalid);
      }

      type = exponent;
    }
    else if(*_csit == '-' or *_csit == '+') {
      if(type == integer or type == exponent)
        type = signed_exponent;
      else {
        report_error(bstd::error::context_error(_json_string, _csit,
            "Unexpected sign"));
        return token(token::invalid);
      }
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

  report_error(bstd::error::context_error(_json_string, _csit,
      "Unexpectedly reached end of JSON string"));
  return token(token::invalid);
}


auto
lexer::
lex_literal(const token::type& _type, const std::regex& _regex,
    std::string::const_iterator& _csit, const std::string& _json_string) {
  std::smatch match;
  if(!std::regex_search(_csit, _json_string.cend(), match, _regex)
      or match.position() != 0)
    return token(token::invalid);


  advance_iterator(_csit, match.length() - 1, _json_string);
  return token(_type);
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
    else if(apply_regex_filter(csit, DOUBLE_QUOTE_REGEX))
      t = lex_string(csit, _json_string);
    else if(apply_regex_filter(csit, _json_string.cend(), BEGIN_NUMBER_REGEX))
      t = lex_number(csit, _json_string);
    else if(apply_regex_filter(csit, _json_string.cend(), TRUE_LITERAL_REGEX))
      t = lex_literal(token::true_literal, TRUE_LITERAL_REGEX, csit, _json_string);
    else if(apply_regex_filter(csit, _json_string.cend(), FALSE_LITERAL_REGEX))
      t = lex_literal(token::false_literal, FALSE_LITERAL_REGEX, csit, _json_string);
    else if(apply_regex_filter(csit, _json_string.cend(), NULL_LITERAL_REGEX))
      t = lex_literal(token::null_literal, NULL_LITERAL_REGEX, csit, _json_string);
    // TODO: use regex to parse large chunks of whitespace
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
  else
    report_error(bstd::error::context_error(_json_string, _csit,
        "attempting to advance the lexing iterator beyond its bounds"));
}


}
