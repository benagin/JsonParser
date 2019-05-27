#ifndef BSTD_JSON_FILE_UTIL_HPP_
#define BSTD_JSON_FILE_UTIL_HPP_

#include <fstream>
#include <iostream>
#include <string_view>

#include <bstd_error.hpp>

namespace bstd::json::utilities {

/// \brief Open a file with the .json extension.
/// \param _path the file path
/// \param _mode the open flags given to the std::fstream constructor
/// \return a std::fstream object pointing to the JSON file, or an empty fstream
///         object otherwise
std::fstream open_json_file(const std::string& _path,
    std::ios_base::openmode _mode);

/// \brief Check if a file has the .json extension.
/// \param _path the file path
/// \return true if _path has the .json extension, false otherwise
const bool is_json_extension(const std::string_view& _path);

}

#endif
