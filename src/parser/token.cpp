#include "token.hpp"


namespace bstd::json::parser {

const
std::unordered_map<token::type, std::string> token::m_type_to_string = {
    { token::invalid, "invalid" },
    { token::begin_object, "begin_object" },
    { token::end_object, "end_object" },
    { token::begin_array, "begin_array" },
    { token::end_array, "end_array" },
    { token::comma, "comma" },
    { token::colon, "colon" },
    { token::whitespace, "whitespace" },
    { token::string, "string" },
    { token::number, "number" },
    { token::true_literal, "true_literal" },
    { token::false_literal, "false_literal" },
    { token::null_literal, "null_literal" },
    { token::end_json, "end_json" }
};

const
std::unordered_map<token::type, std::string> token::m_type_to_default_value = {
    { token::invalid, "invalid" },
    { token::begin_object, "{" },
    { token::end_object, "}" },
    { token::begin_array, "[" },
    { token::end_array, "]" },
    { token::comma, "," },
    { token::colon, ":" },
    { token::whitespace, " " },
    { token::string, "string" },
    { token::number, "1" },
    { token::true_literal, "true" },
    { token::false_literal, "false" },
    { token::null_literal, "null" },
    { token::end_json, "end_json" }
};



const token::type
token::
get_type() const {
  return m_type;
}


const std::string
token::
get_type_as_string() const {
  return m_type_to_string.at(m_type);
}


void
token::
set_type(const type _type) {
  m_type = _type;
}


const std::string
token::
get_value() const {
  return m_value;
}


void
token::
set_value(const char _value) {
  set_value(std::string(1, _value));
}


void
token::
set_value(const std::string& _value) {
  m_value = _value;
}


bool
token::
operator==(const token& _rhs) const {
  return m_type == _rhs.m_type and m_value == _rhs.m_value;
}


bool
token::
operator!=(const token& _rhs) const {
  return !(*this == _rhs);
}


std::ostream&
operator<<(std::ostream& _os, const token& _token) {
  return _os << _token.to_string();
}


bool
token::
is_valid() const {
  return m_type != invalid;
}


const std::string
token::
to_string() const {
  return std::string('(' + get_type_as_string() + ", " + get_value() + ')');
}


}
