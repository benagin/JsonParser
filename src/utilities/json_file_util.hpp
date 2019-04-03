#ifndef BSTD_JSON_FILE_UTIL_HPP_
#define BSTD_JSON_FILE_UTIL_HPP_

#include <fstream>
#include <iostream>
#include <string_view>

#include <bstd_error.hpp>

namespace bstd::json::utilities {

std::fstream open_json_file(const std::string& _path,
    std::ios_base::openmode _mode);

const bool is_json_extension(const std::string_view& _path);

}

#endif
