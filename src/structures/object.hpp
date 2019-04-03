#ifndef BSTD_JSON_OBJECT_HPP_
#define BSTD_JSON_OBJECT_HPP_

#include <algorithm>
#include <vector>

#include "value.hpp"

namespace bstd::json {

// Represents an object from the JSON grammar (https://www.json.org/).
class object final : public value {

  public:

    object(const bool _debug = false) : value(_debug) {}

    ~object() {}

    // Getters and setters.

    const std::size_t size() const override;

    // Accessors.

    value& operator[](const std::string& _string);
    value& operator[](const std::string&& _string);

    value& at(const std::string& _string);
    const value& at(const std::string& _string) const;

    // Operator overloads.

    bool operator==(const object& _rhs) const;

    bool operator!=(const object& _rhs) const;

    object& operator+=(const object& _rhs);

    // Member functions.

    const std::string to_string(const bool _include_ws = true) const override;

    const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) override;

  private:

    // Objects might have whitepsace between their curly brackets instead of
    // members. This is 'ws' in the grammar for object:
    // object
    //  '{' ws '}'
    //  '{' members '}'
    std::string m_ws{""};

    std::vector<std::shared_ptr<value>> m_values;

};

}

#endif
