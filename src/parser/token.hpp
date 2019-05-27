#ifndef BSTD_JSON_TOKEN_HPP_
#define BSTD_JSON_TOKEN_HPP_

#include <ostream>
#include <string>

namespace bstd::json {

/// \brief Token object used by the parser.
class token final {

  public:

    /// \brief Enum representation of the literal value represented by this
    /// token.
    enum type {
      no_type = 0,
      open_curly_bracket,
      closed_curly_bracket,
      open_square_bracket,
      closed_square_bracket,
      comma,
      colon,
      double_quote,
      whitespace,
      number,
      true_literal,
      false_literal,
      null_literal
    };

    /// \brief Construct a token from a character value.
    /// \param _type type
    /// \param _value the character from the JSON string that this token
    ///               represents
    token(const type _type = no_type, const char _value = '\0')
        : token(_type, std::string(1, _value)) {}

    /// \brief Construct a token from a string value.
    /// \param _type type
    /// \param _value the sub string from the JSON string that this token
    ///               represents
    token(const type _type = no_type, const std::string& _value = "")
        : m_type(_type), m_value(_value) {}

    ~token() {}

    /// \brief Get this token's type.
    /// \return the type of this token
    type get_type() const;

    /// \brief Get this token's value.
    /// \return the value of this token
    const std::string get_value() const;

    /// \brief Output operator overload.
    /// \param _os std::ostream
    /// \param _token the calling token
    /// \return std::ostream
    friend std::ostream& operator<<(std::ostream& _os,
        const token& _token);

  private:

    type m_type{no_type};

    std::string m_value{""};
};

}

#endif

