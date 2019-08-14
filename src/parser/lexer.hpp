#ifndef BSTD_JSON_LEXER_HPP_
#define BSTD_JSON_LEXER_HPP_

#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <vector>

#include <bstd_error.hpp>

#include "parser_base.hpp"
#include "regex.hpp"
#include "token.hpp"

namespace bstd::json::parser {

/// \brief Tokenize a JSON string.
class lexer final : public parser_base<std::string> {

  public:

    typedef std::vector<token>::const_iterator CVIT;

    /// \brief Construct a lexer object.
    /// \param _json_string a JSON string
    /// \param _debug debug flag
    /// \param _throw if true, this class will throw exceptions when applicable
    lexer(const std::string& _json_string, const bool _debug = false,
        const bool _throw = true) : parser_base(_json_string, _debug, _throw) {}

    ~lexer() {}

    /// \brief Get tokens.
    /// \return m_tokens
    const std::vector<token>& get_tokens() const noexcept;

    /// \brief Process the next token from m_tokens.
    /// \return the next token to be processed, determined by m_index
    const CVIT next_token();

    /// \brief Tokenize a JSON string.
    /// This populates m_tokens with tokens that represent the JSON provided.
    /// \throws bstd::error::context_error if m_throw is true and errors in the
    ///         JSON string are found
    void lex();

    /// \brief Reset the token iterator.
    void reset() noexcept;

    const std::string to_string() const noexcept override;

  private:

    /// \brief Apply regex to a character.
    /// \param _type the token type to filter
    /// \param _regex the regex to apply
    /// \return true if a match was found starting at the current element
    const auto apply_regex_filter(const token::type& _type,
        const std::regex& _regex);

    CVIT m_index; ///< The index of m_tokens used when iterating using get_next_token().

    std::vector<token> m_tokens;

    static const std::unordered_map<char, token::type> m_char_value_tokens; ///< This map stores the single character token types.

};

}

#endif
