#include "array.hpp"

namespace bstd::json {


const std::size_t
array::
size() const {
  return m_values.size();
}


bool
array::
operator==(const array& _rhs) const {
  // TODO: implement.
  return true;
}


bool
array::
operator!=(const array& _rhs) const {
  return !(*this == _rhs);
}


array&
array::
operator+=(const array& _rhs) {
  // TODO: implement.
  return *this;
}


const std::string
array::
to_string(const bool _include_ws) const {
  std::string result = value::to_string(_include_ws);

  if(_include_ws)
    result += m_value_ws.first;

  result += "[";

  // The array is either empty and might have whitepsace or it contains one or
  // more members.
  if(m_values.empty() and _include_ws)
    result += m_ws;
  else if(m_values.size() == 1)
    result += m_values.front()->to_string(_include_ws);
  else
    for(int i = 0; i < m_values.size(); ++i) {
      result += m_values.at(i)->to_string(_include_ws);

      if(i != m_values.size() - 1)
        result += ',';
    }

  result += "]";

  if(_include_ws)
    result += m_value_ws.first;

  return result;
}


const std::shared_ptr<value>&
array::
add_value(const std::shared_ptr<value>& _value) {
  m_values.push_back(_value);
  return _value;
}


}
