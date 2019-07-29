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
    lexer(const bool _debug = false, const bool _throw = true)
        : parser_base(_debug, _throw) {}

    /// \brief Deleted copy constructor.
    lexer(const lexer&) = delete;
    /// \brief Deleted copy assignment.
    lexer& operator=(const lexer&) = delete;

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


    /// \brief Apply regex to a character.
    /// \param _target the character to match
    /// \param _regex the regex to apply
    /// \return true if a match was found
    auto apply_regex_filter(const std::string::const_iterator& _target,
        const std::regex& _regex) const;

    /// \brief Apply regex to a range.
    /// \param _first the first element in the range
    /// \param _last the last element in the range (one past the end)
    /// \return true if a match was found at the beginning of the range
    auto apply_regex_filter(const std::string::const_iterator& _first,
        const std::string::const_iterator& _last, const std::regex& _regex)
        const;


    /// \brief Lex strings. This consumes the starting and ending quotes.
    /// This function advances _csit to the end of the string.
    /// \param _csit iterator to the first element in the string
    /// \param _json_string the source JSON string
    /// \return the lexed token
    auto lex_string(std::string::const_iterator& _csit,
        const std::string& _json_string);

    /// \brief Lex numbers.
    /// This function advances _csit to the end of the number.
    /// \param _csit iterator to the first value in the number
    /// \param _json_string the source JSON string
    /// \return the lexed token
    auto lex_number(std::string::const_iterator& _csit,
        const std::string& _json_string);

    /// \brief Lex a literal.
    /// This function advances _csit to the end of the literal.
    /// \param _literal the literal to lex
    /// \param _regex a regex pattern to match
    /// \param _csit iterator to the first character in the literal
    /// \param _json_string the source JSON string
    /// \return the lexed token
    auto lex_literal(const token::type& _literal_type, const std::regex& _regex,
        std::string::const_iterator& _csit, const std::string& _json_string);

    /// \brief Safely advances _csit as far as possible up to _distance.
    /// This modifies _csit.
    /// \param _csit iterator to advance
    /// \param _distance largest distance to advance _csit
    void advance_iterator(std::string::const_iterator& _csit,
        const int _distance, const std::string& _json_string);

    std::vector<token> m_tokens;

    /// The index of m_tokens used when iterating using get_next_token().
    CVIT m_index;

    /// This map stores the single character token types.
    static const std::unordered_map<char, token::type> m_char_value_tokens;

};

}

#endif
