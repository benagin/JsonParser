#ifndef BSTD_JSON_LEXER_HPP_
#define BSTD_JSON_LEXER_HPP_

#include <ostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "token.hpp"

namespace bstd::json::parser {

/// \brief Tokenize a JSON string.
class lexer final {

  public:

    typedef std::vector<token>::const_iterator CVIT;

    lexer() {}

    /// \brief Deleted copy constructor.
    lexer(const lexer&) = delete;
    /// \brief Deleted copy assignment.
    lexer& operator=(lexer _rhs) = delete;

    ~lexer() {}

    /// \brief Tokenize a JSON string.
    /// This populates m_tokens with tokens that represent the JSON provided.
    /// \param _json_string a JSON string
    void lex(const std::string& _json_string);

    /// \brief Get the next token from m_tokens.
    /// \return the next token, determined by m_index
    /// \throws std::out_of_range if no more tokens can be retrieved
    const token get_next_token();

    /// \brief Output operator overload.
    /// \param _os std::ostream
    /// \param _lexer the calling lexer
    /// \return std::ostream
    friend std::ostream& operator<<(std::ostream& _os,
        const lexer& _lexer);

  private:

    std::vector<token> m_tokens;

    /// The index of m_tokens used when iterating using get_next_token().
    CVIT m_index{m_tokens.cbegin()};

    /// This map stores the single character token types.
    const std::unordered_map<char, token::type> m_char_value_tokens {
        { '{', token::begin_object },
        { '}', token::end_object },
        { '[', token::begin_array},
        { ']', token::end_array },
        { ',', token::comma },
        { ':', token::colon },
    };

};

}

#endif
