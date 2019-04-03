#include "json_file_util.hpp"


namespace bstd::json::utilities {


std::fstream
open_json_file(const std::string& _path, std::ios_base::openmode _mode) {
  if(!is_json_extension(_path))
    return std::fstream();

  return std::fstream(_path, _mode);
}

const bool
is_json_extension(const std::string_view& _path) {
  return _path.ends_with(".json");
}


}
