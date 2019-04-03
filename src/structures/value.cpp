#include "value.hpp"

namespace bstd::json {


value::
~value() {}


const std::string
value::
get_name() const {
  return m_name;
}


const std::string
value::
to_string(const bool _include_ws) const {
  std::string result = m_name;

  if(_include_ws)
    result = m_name_ws.first + m_name + m_name_ws.second;

  return result.empty() ? result : result + ":";
}


}
