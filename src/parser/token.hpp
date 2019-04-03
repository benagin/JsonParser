#ifndef BSTD_JSON_TOKEN_HPP_
#define BSTD_JSON_TOKEN_HPP_

#include <ostream>
#include <string>

namespace bstd::json {

// Token object used by the JSON parser.
class token final {

  public:

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

    token(const type _type = no_type, const char _value = '\0')
        : token(_type, std::string(1, _value)) {}

    token(const type _type = no_type, const std::string& _value = "")
        : m_type(_type), m_value(_value) {}

    ~token() {}

    type get_type() const;

    const std::string get_value() const;

    friend std::ostream& operator<<(std::ostream& _os,
        const token& _token);

  private:

    type m_type{no_type};

    std::string m_value{""};
};

}

#endif

