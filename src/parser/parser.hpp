#ifndef BSTD_JSON_PARSER_HPP_
#define BSTD_JSON_PARSER_HPP_

#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>
#include <sstream>

#include <bstd_error.hpp>

#include "json.hpp"
#include "token.hpp"
#include "structures/array.hpp"
#include "structures/object.hpp"
#include "structures/json_string.hpp"
#include "utilities/json_file_util.hpp"

namespace bstd::json {

class json;

/// \brief Parse JSON according to its grammar (https://www.json.org/).
/// There is no need for a class here as no state is stored.

/// \brief Parse a .json file or a JSON string and return the result as a json
/// object. The type of object depends on the contents of the file or string.
/// \param _string the .json file or JSON string
/// \return a shared_ptr to a json object
std::shared_ptr<json> parse(const std::string& _string);

/// \brief Scan a JSON string and return a tokenized version.
/// \param _string the .json file or JSON string
/// \return a vector of tokens
std::vector<token> scan(const std::string& _string);

/// \brief Parse a tokenized JSON string.
/// \param _tokens a vector of tokens
/// \return a shared_ptr to a json object
std::shared_ptr<json> parse(const std::vector<token> _tokens);

/// \brief Parse a JSON object.
/// \param _string the JSON object string
/// \return a shared_ptr to an object
std::shared_ptr<object> parse_object(const std::string _string);

/// \brief Parse a JSON array.
/// \param _string the JSON array string
/// \return a shared_ptr to an array
std::shared_ptr<array> parse_array(const std::string _string);

/// \brief Remove and return the leading whitespace from _string.
/// Example:
/// Given "\t  \nexample string" as _string, _string will become "example string"
/// and "\t  \n" will be returned.
/// \param _string the string to trim
/// \return the trimmed whitespace if any exists
const std::string trim_leading_ws(std::string& _string);

}

#endif
