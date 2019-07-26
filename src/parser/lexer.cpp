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
  }

  return *m_index++;
}


auto
lexer::
lex_string(std::string::const_iterator& _csit,
    const std::string& _json_string) const {
  ++_csit;
  const auto begin = _csit;
  while(*_csit != '\"') {
    if(_csit == _json_string.cend())
      report_error(bstd::error::context_error(_json_string, _csit,
          "Expected end of string"));

    ++_csit;
  }

  return token(token::string, std::string(begin, _csit));
}


auto
lexer::
lex_literal(const std::string_view& _literal, const token::type _literal_type,
    std::string::const_iterator& _csit, const std::string& _json_string) const {
  const auto size = _literal.size();

  if(std::string(_csit, _csit + size) != _literal)
    report_error(bstd::error::context_error(_json_string, _csit, _csit + 4,
        "Expected the literal \'" + std::string(_literal) + "\'"));

  advance_iterator(_csit, size - 1, _json_string);
  return token(_literal_type);
}


auto
lexer::
lex_true_literal(std::string::const_iterator& _csit,
    const std::string& _json_string) const {
  return lex_literal("true", token::true_literal, _csit, _json_string);
}


auto
lexer::
lex_false_literal(std::string::const_iterator& _csit,
    const std::string& _json_string) const {
  return lex_literal("false", token::false_literal, _csit, _json_string);
}


auto
lexer::
lex_null_literal(std::string::const_iterator& _csit,
    const std::string& _json_string) const {
  return lex_literal("null", token::null_literal, _csit, _json_string);
}


void
lexer::
lex(const std::string& _json_string) {
  // TODO: support nesting.
  for(auto csit = _json_string.cbegin(); csit != _json_string.cend(); ++csit) {
    token t;

    const auto cmit = m_char_value_tokens.find(*csit);
    if (cmit != m_char_value_tokens.cend()) {
      t = token(cmit->second, cmit->first);
    }
    else if (*csit == '\"') {
      t = lex_string(csit, _json_string);
    } else if (isdigit(*csit) or *csit == '-' or *csit == '.') {
      // TODO: handle numbers.
    } else if (*csit == 't') {
      t = lex_true_literal(csit, _json_string);
    } else if (*csit == 'f') {
      t = lex_false_literal(csit, _json_string);
    } else if (*csit == 'n') {
      t = lex_null_literal(csit, _json_string);
    } else if (isspace(*csit)) {
      // TODO: handle whitespace.
    } else {
      // TODO: handle error.
    }

    m_tokens.push_back(t);

    if(!t.is_valid()) {
      report_error(bstd::error::context_error(_json_string, csit,
          "Character does not match the start of any valid JSON value"));
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
  return _os << _lexer.to_string();
}


void
lexer::
advance_iterator(std::string::const_iterator& _csit,
    const std::size_t _distance, const std::string& _json_string) const {
  if(std::distance(_csit, _json_string.cend()) > _distance)
    std::advance(_csit, _distance);
  else if(std::distance(_csit, _json_string.cend()) == _distance)
    std::advance(_csit, _distance - 1);
  else
    report_error(bstd::error::context_error(_json_string, _csit,
        _json_string.cend(), "Token value doesn't fit in the JSON string."));
}


void
lexer::
report_error(const std::runtime_error _e) const {
  if(m_throw)
    throw _e;
  else
    std::cerr << _e.what() << std::endl;
}


}
