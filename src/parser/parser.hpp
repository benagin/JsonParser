#ifndef BSTD_JSON_PARSER_HPP_
#define BSTD_JSON_PARSER_HPP_

#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>
#include <sstream>

#include <bstd_error.hpp>

#include "json.hpp"
#include "lexer.hpp"
#include "structures/array.hpp"
#include "structures/object.hpp"
#include "structures/json_string.hpp"
#include "utilities/json_file_util.hpp"

namespace bstd::json::parser {

using structures::array;
using structures::json_string;
using structures::object;

/// \brief Parse JSON according to its grammar (https://www.json.org/).
/// There is no need for a class here as no state is stored.

/// \brief Parse a .json file or a JSON string and return the result as a json
///        element.
/// \param _string the .json file or JSON string
/// \return a shared_ptr to a json object
std::shared_ptr<json> parse(const char* _string);
std::shared_ptr<json> parse(const std::string& _string);

/// \brief Parse a tokenized JSON string.
/// \param _lexer a lexer object which contains a tokenized version of a JSON
///               string
/// \return a shared_ptr to a json object
std::shared_ptr<json> parse(const lexer& _lexer);

/// \brief Remove and return the leading whitespace from _string.
/// Example:
/// Given "\t  \nexample string" as _string, _string will become "example string"
/// and "\t  \n" will be returned.
/// \param _string the string to trim
/// \return the trimmed whitespace if any exists
const std::string trim_leading_ws(std::string& _string);


}

#endif
