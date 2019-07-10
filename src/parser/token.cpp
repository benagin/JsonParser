#include "token.hpp"


namespace bstd::json::parser {


token::type
token::
get_type() const {
  return m_type;
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
  return std::string('(' + std::to_string(get_type()) + ", " + get_value() + ')');
}


}
