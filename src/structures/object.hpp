#ifndef BSTD_JSON_OBJECT_HPP_
#define BSTD_JSON_OBJECT_HPP_

#include <algorithm>
#include <vector>

#include "value.hpp"

namespace bstd::json {

/// \brief Represents an object from the JSON grammar (https://www.json.org/).
class object final : public value {

  public:

    /// \brief Construct an empty object.
    /// TODO: inherit documentation?
    object(const bool _debug = false) : value(_debug) {}

    ~object() {}

    /// Getters and setters.

    /// \brief The size of this object.
    /// \return the size of the underlying vector of values
    const std::size_t size() const override;

    /// Accessors.

    /// TODO: write documentation.
    value& operator[](const std::string& _string);
    value& operator[](const std::string&& _string);

    /// TODO: write documentation.
    value& at(const std::string& _string);
    const value& at(const std::string& _string) const;

    /// Operator overloads.

    /// TODO: write documentation.
    bool operator==(const object& _rhs) const;

    /// TODO: write documentation.
    bool operator!=(const object& _rhs) const;

    /// TODO: write documentation.
    object& operator+=(const object& _rhs);

    /// Member functions.

    /// TODO: inherit documentation?
    const std::string to_string(const bool _include_ws = true) const override;

    /// TODO: inherit documentation?
    const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) override;

  private:

    std::string m_ws{""}; ///< Objects might have whitepsace between their curly
                          ///< brackets instead of members. This is 'ws' in the
                          ///< grammar for object:
                          ///< object
                          ///<  '{' ws '}'
                          ///<  '{' members '}'

    std::vector<std::shared_ptr<value>> m_values;

};

}

#endif
