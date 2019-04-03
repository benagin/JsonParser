#include "token.hpp"


namespace bstd::json {


token::type
token::
get_type() const {
  return m_type;
}


const std::string
token::
get_value() const {
  return m_value;
}


std::ostream&
operator<<(std::ostream& _os, const token& _token) {
  return _os << '(' << _token.get_type() << ", " << _token.get_value()
      << ')';
}


}
