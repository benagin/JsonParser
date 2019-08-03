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
    /// \param _debug debug flag
    /// \param _throw if true, this class will throw errors when applicable
    lexer(const std::string& _json_string, const bool _debug = false,
        const bool _throw = true) : parser_base(_json_string, _debug, _throw) {}

    /// \brief Deleted copy constructor.
    lexer(const lexer&) = delete;
    /// \brief Deleted copy assignment.
    lexer& operator=(const lexer&) = delete;

    ~lexer() {}

    /// \brief Get tokens.
    /// \return m_tokens
    const std::vector<token>& get_tokens() const noexcept;

    /// \brief Process the next token from m_tokens.
    /// \return the next token to be processed, determined by m_index
    /// \throws std::runtime_error if m_throw is true and no more
    ///         tokens can be retrieved
    const CVIT next_token();

    /// \brief Tokenize a JSON string.
    /// This populates m_tokens with tokens that represent the JSON provided.
    /// \throws bstd::error::context_error if m_throw is true and errors in the
    ///         JSON string are found
    void lex();

    /// \brief Reset the token iterator.
    void reset() noexcept;

    /// \brief Convert tokens to a string.
    /// \return tokens as a string
    const std::string to_string() const;

    /// \brief Output operator overload.
    /// \param _os std::ostream
    /// \param _lexer the calling object
    /// \return std::ostream
    friend std::ostream& operator<<(std::ostream& _os,
        const lexer& _lexer);

  private:

    /// \brief Apply regex to a character.
    /// \param _regex the regex to apply
    /// \return true if a match was found starting at the current element
    const auto apply_regex_filter(const token::type& _type,
        const std::regex& _regex);

    /// The index of m_tokens used when iterating using get_next_token().
    CVIT m_index;

    std::vector<token> m_tokens;

    /// This map stores the single character token types.
    static const std::unordered_map<char, token::type> m_char_value_tokens;

};

}

#endif
