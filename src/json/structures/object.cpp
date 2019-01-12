#include "object.hpp"

namespace bstd::json {


const std::size_t
object::
size() const {
  return m_values.size();
}


value&
object::
operator[](const std::string& _string) {
  // TODO: implement.
  return *this;
}


value&
object::
operator[](const std::string&& _string) {
  // TODO: implement.
  return *this;
}


value&
object::
at(const std::string& _string) {
  // TODO: implement.
  return *this;
}


const value&
object::
at(const std::string& _string) const {
  // TODO: implement.
  return *this;
}


bool
object::
operator==(const object& _rhs) const {
  // TODO: implement.
  return true;
}


bool
object::
operator!=(const object& _rhs) const {
  return !(*this == _rhs);
}


object&
object::
operator+=(const object& _rhs) {
  // TODO: implement.
  return *this;
}


const std::string
object::
to_string(const bool _include_ws) const {
  std::string result = value::to_string(_include_ws);

  if(_include_ws)
    result += m_value_ws.first;

  result += "{";

  // The object is either empty and might have whitepsace or it contains some
  // members.
  if(m_values.empty() and _include_ws)
    result += m_ws;
  else
    for(const auto& value : m_values)
      result += value->to_string(_include_ws);

  result += "}";

  if(_include_ws)
    result += m_value_ws.first;

  return result;
}


const std::shared_ptr<value>&
object::
add_value(const std::shared_ptr<value>& _value) {
  m_values.push_back(_value);
  return _value;
}


}
