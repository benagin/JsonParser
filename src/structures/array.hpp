#ifndef BSTD_JSON_ARRAY_HPP_
#define BSTD_JSON_ARRAY_HPP_

#include <vector>

#include "value.hpp"

namespace bstd::json {

// Represents an array from the JSON grammar (https://www.json.org/).
class array final : public value {

  public:

    array(const bool _debug = false) : value(_debug) {}

    ~array() {}

    // Getters and setters.

    const std::size_t size() const override;

    // Accessors.

    // Operator overloads.

    bool operator==(const array& _rhs) const;

    bool operator!=(const array& _rhs) const;

    array& operator+=(const array& _rhs);

    // Member functions.

    const std::string to_string(const bool _include_ws = true) const override;

    // Add _value to m_values.
    const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) override;

  private:

    // Objects might have whitepsace between their curly brackets instead of
    // elements. This is 'ws' in the grammar for array:
    // array
    //  '[' ws ']'
    //  '[' elements ']'
    std::string m_ws{""};

    std::vector<std::shared_ptr<value>> m_values;

};

}

#endif
