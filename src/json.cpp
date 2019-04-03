#include "json.hpp"

namespace bstd::json {


json&
json::
operator=(json _rhs) {
  std::swap(m_path, _rhs.m_path);
  std::swap(m_value, _rhs.m_value);

  return *this;
}


const std::size_t
json::
size() const {
  return m_value ? m_value->size() : 0;
}


const std::string&
json::
get_path() const {
  return m_path;
}


void
json::
set_path(const std::string& _path) {
  m_path = _path;
}


const std::shared_ptr<value>&
json::
get_value() const {
  return m_value;
}


void
json::
set_value(const std::shared_ptr<value>& _value) {
  m_value = _value;
}


const std::string
json::
to_string(const bool _include_ws) const {
  return m_value ? m_value->to_string(_include_ws) : "";
}


bool
json::
operator==(const json& _rhs) const {
  if(size() != _rhs.size())
    return false;

  return m_value == _rhs.m_value;
}


bool
json::
operator!=(const json& _rhs) const {
  return !(*this == _rhs);
}


json&
json::
operator+=(const json& _rhs) {
  add_value(_rhs.m_value);
  return *this;
}


json
operator+(json _lhs, const json& _rhs) {
  _lhs += _rhs;
  return _lhs;
}


const std::shared_ptr<value>&
json::
add_value(const std::shared_ptr<value>& _value) {
  return m_value ? m_value->add_value(_value) : m_value = _value;
}


void
json::
write(const bool _include_ws) const {
    json_base::write(m_path, _include_ws);
}


}
