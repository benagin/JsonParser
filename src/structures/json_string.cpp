#include "json_string.hpp"

namespace bstd::json {


const std::size_t
json_string::
size() const {
  return m_value.size();
}


const std::string
json_string::
to_string(const bool _include_ws) const {
  return "\"" + m_value + "\"";
}


const std::shared_ptr<value>&
json_string::
add_value(const std::shared_ptr<value>& _value) {
  // TODO: implement.

  return _value;
}

}
