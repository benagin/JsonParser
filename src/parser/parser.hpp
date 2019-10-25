#ifndef BSTD_JSON_PARSER_HPP_
#define BSTD_JSON_PARSER_HPP_

#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>
#include <sstream>

#include <bstd_error.hpp>

#include "basic_json.hpp"
#include "lexer.hpp"
#include "utilities/json_file_util.hpp"

namespace bstd::json::parser {

/// \brief Parse a .json file or a JSON string and return the result as a json
///        element.
/// This acts as the API for the parser. Calling this will create the necessary
/// objects to parse the JSON.
/// \param _string the .json file or JSON string
/// \copydetails parser_base::parser_base()
/// \return a shared_ptr to a json object
std::shared_ptr<json> parse(const char* _string,
    const bool _debug = false, const bool _throw = true);
/// \copydoc parse()
std::shared_ptr<json> parse(const std::string& _string,
    const bool _debug = false, const bool _throw = true);

/// \brief Parse JSON according to its grammar (https://www.json.org/).
class parser final : public parser_base<std::vector<token>> {

  public:

    /// \brief Construct a parser object.
    /// \param _tokens tokenized JSON
    /// \param _debug debug flag
    /// \param _throw if true, this class will throw errors when applicable
    parser(const std::vector<token>& _tokens, const bool _debug = false,
        const bool _throw = true) : parser_base(_tokens, _debug, _throw),
        m_json(std::make_shared<json>()) {}

    /// \brief Get the parsed json object.
    /// \return the parsed json object
    std::shared_ptr<json> get_json() const noexcept;

    const std::string to_string() const noexcept override;

  private:

    std::shared_ptr<json> m_json;

};

}

#endif
