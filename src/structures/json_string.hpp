#ifndef BSTD_JSON_STRING_HPP_
#define BSTD_JSON_STRING_HPP_

#include <memory>
#include <string>

#include "value.hpp"

namespace bstd::json::structures {

/// \brief Represents string from the JSON grammar (https://www.json.org/).
class json_string final : public value {

  public:

    /// \copydoc value::value(bool)
    json_string(const bool _debug = false) : json_string("", _debug) {}

    /// \brief Construct a json_string with a std::string.
    /// \param _value the std::string value
    /// \copydoc json_string::json_string(bool)
    json_string(const std::string& _value, const bool _debug = false)
        : value(_debug), m_value(_value) {}

    ~json_string() {}

    /// Getters and setters.

    const std::size_t size() const override;

    /// Member functions.

    const std::string to_string(const bool _include_ws = true) const override;

    const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) override;

  private:

    std::string m_value{""};

};

}

#endif

