#ifndef BSTD_JSON_TOKEN_HPP_
#define BSTD_JSON_TOKEN_HPP_

#include <ostream>
#include <string>

namespace bstd::json::parser {

/// \brief Token object used by the parser.
class token final {

  public:

    /// \brief Enum representation of the literal value represented by this
    ///        token.
    enum type {
      invalid = 0,   // Does not match any of the below.
      begin_object,  // {
      end_object,    // }
      begin_array,   // [
      end_array,     // ]
      comma,         // ,
      colon,         // :
      begin_string,  // "
      end_string,    // "
      whitespace,    // ' '\t\n\v\f\r

      string,        // some_name (contents of the string, not including
                     // quotes)
      number,        // 1, -1, 2.5, 1e-10, etc.
      true_literal,  // true
      false_literal, // false
      null_literal,  // null
      end_json       // Special token type signifying the end of a JSON element.
                     // This type has no value.
    };

    /// \brief Default constructor.
    token() {}

    /// \brief Construct a token from a character value.
    /// \param _type type
    /// \param _value the character from the JSON string that this token
    ///               represents
    token(const type _type, const char _value = '\0')
        : token(_type, std::string(1, _value)) {}

    /// \brief Construct a token from a string value.
    /// \param _type type
    /// \param _value the sub string from the JSON string that this token
    ///               represents
    token(const type _type, const std::string& _value = "")
        : m_type(_type), m_value(_value) {}

    ~token() {}

    /// Getters and setters.

    /// \brief Get this token's type.
    /// \return the type of this token
    type get_type() const;
    /// \brief Set this token's type.
    /// \param _type the type to set
    void set_type(const type _type);

    /// \brief Get this token's value.
    /// \return the value of this token
    const std::string get_value() const;
    /// \brief Set this token's value.
    /// \param _value a character to set as the value
    void set_value(const char _value);
    /// \brief Set this token's value.
    /// \param _value a string to set as the value
    void set_value(const std::string& _value);

    /// Operator overloads.

    /// \brief Equality operator.
    /// \param _rhs the json object on the right hand side of the operator
    /// \return true if this contains the same values as _rhs
    bool operator==(const token& _rhs) const;

    /// \brief Output operator overload.
    /// \param _os std::ostream
    /// \param _token the calling token
    /// \return std::ostream
    friend std::ostream& operator<<(std::ostream& _os,
        const token& _token);

    /// Member functions.

    /// \brief Check if this token is invalid.
    /// \returns true if the type is not type::invalid, false otherwise
    bool is_valid() const;

    /// \brief Convert this token to a string.
    /// \return this token as a string
    const std::string to_string() const;

  private:

    type m_type{invalid};

    std::string m_value{"no-value"};

};

}

#endif

