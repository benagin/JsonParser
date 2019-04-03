#include "json_base.hpp"


namespace bstd::json {


json_base::
~json_base() {}


std::ostream&
operator<<(std::ostream& _os, const json_base& _json_base) {
  return _os << _json_base.to_string();
}


void
json_base::
write(const std::string _path, const bool _include_ws) const {
  auto ofs =
    utilities::open_json_file(_path, std::fstream::out | std::fstream::trunc);

    ofs << to_string(_include_ws);
}


}
