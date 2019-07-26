#ifndef BSTD_JSON_LEXER_HPP_
#define BSTD_JSON_LEXER_HPP_

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include <bstd_error.hpp>

#include "token.hpp"

namespace bstd::json::parser {

/// \brief Tokenize a JSON string.
class lexer final {

  public:

    typedef std::vector<token>::const_iterator CVIT;

    lexer(const bool _debug = false) : m_debug(_debug) {}

    /// \brief Deleted copy constructor.
    lexer(const lexer&) = delete;
    /// \brief Deleted copy assignment.
    lexer& operator=(lexer _rhs) = delete;

    ~lexer() {}

    /// Getters and setters.

    /// \brief Get tokens.
    /// \return m_tokens
    const std::vector<token> get_tokens() const;

    /// \brief Get the next token from m_tokens.
    /// \return the next token, determined by m_index
    /// \throws std::out_of_range if no more tokens can be retrieved
    const token get_next_token();

    /// Member functions.

    /// \brief Tokenize a JSON string.
    /// This populates m_tokens with tokens that represent the JSON provided.
    /// \param _json_string a JSON string
    void lex(const std::string& _json_string);

    /// \brief Reset the token iterator.
    void reset();

    /// \brief Convert tokens to a string.
    /// \return tokens as a string
    const std::string to_string() const;

    /// Operator overloads.

    /// \brief Output operator overload.
    /// \param _os std::ostream
    /// \param _lexer the calling lexer
    /// \return std::ostream
    friend std::ostream& operator<<(std::ostream& _os,
        const lexer& _lexer);

  private:

    /// \brief Lex strings. This consumes the starting and ending quotes.
    /// This function advances _csit to the end of the string.
    /// \param _csit iterator to the first element in the string
    /// \param _json_string the source JSON string
    auto lex_string(std::string::const_iterator& _csit,
        const std::string& _json_string) const;

    /// \brief Lex a literal.
    /// This function advances _csit to the end of the literal.
    /// \param _literal the literal to lex
    /// \param _csit iterator to the first character in the literal
    /// \param _json_string the source JSON string
    auto lex_literal(const std::string_view& _literal,
        const token::type _literal_type, std::string::const_iterator& _csit,
        const std::string& _json_string) const;

    /// \brief Lex the literal 'true'.
    /// \param _csit iterator to the 't' in 'true'
    /// \param _json_string the source JSON string
    auto lex_true_literal(std::string::const_iterator& _csit,
        const std::string& _json_string) const;

    /// \brief Lex the literal 'false'.
    /// \param _csit iterator to the 'f' in 'false'
    /// \param _json_string the source JSON string
    auto lex_false_literal(std::string::const_iterator& _csit,
        const std::string& _json_string) const;

    /// \brief Lex the literal 'null'.
    /// \param _csit iterator to the 'n' in 'null'
    /// \param _json_string the source JSON string
    auto lex_null_literal(std::string::const_iterator& _csit,
        const std::string& _json_string) const;

    /// \brief Safely advances _csit as far as possible up to _distance.
    /// This modifies _csit.
    /// \param _csit iterator to advance
    /// \param _distance largest distance to advance _csit
    void advance_iterator(std::string::const_iterator& _csit,
        const std::size_t _distance, const std::string& _json_string) const;

    bool m_debug{false};

    std::vector<token> m_tokens;

    /// The index of m_tokens used when iterating using get_next_token().
    CVIT m_index;

    /// This map stores the single character token types.
    static const std::unordered_map<char, token::type> m_char_value_tokens;

};

}

#endif
