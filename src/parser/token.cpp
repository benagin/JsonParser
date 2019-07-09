#include "token.hpp"


namespace bstd::json::parser {


bool
token::
is_valid() const {
  return m_type != invalid;
}


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


std::ostream&
operator<<(std::ostream& _os, const token& _token) {
  return _os << '(' << _token.get_type() << ", " << _token.get_value()
      << ')';
}


}
