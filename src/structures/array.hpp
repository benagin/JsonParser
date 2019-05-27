#ifndef BSTD_JSON_ARRAY_HPP_
#define BSTD_JSON_ARRAY_HPP_

#include <vector>

#include "value.hpp"

namespace bstd::json {

/// \brief Represents an array from the JSON grammar (https://www.json.org/).
class array final : public value {

  public:

    /// \brief Construct an empty array.
    /// TODO: inherit documentation?
    array(const bool _debug = false) : value(_debug) {}

    ~array() {}

    /// Getters and setters.

    /// \brief The size of this array.
    /// \return the size of the underlying vector of values
    const std::size_t size() const override;

    /// Accessors.

    /// Operator overloads.

    /// TODO: inherit documentation?
    bool operator==(const array& _rhs) const;

    /// TODO: inherit documentation?
    bool operator!=(const array& _rhs) const;

    /// TODO: inherit documentation?
    array& operator+=(const array& _rhs);

    /// Member functions.

    /// TODO: inherit documentation?
    const std::string to_string(const bool _include_ws = true) const override;

    /// TODO: inherit documentation?
    const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) override;

  private:

    std::string m_ws{""}; ///< Objects might have whitepsace between their curly
                          ///< brackets instead of elements. This is 'ws' in the
                          ///< grammar for array:
                          ///< array
                          ///<  '[' ws ']'
                          ///<  '[' elements ']'

    std::vector<std::shared_ptr<value>> m_values;

};

}

#endif
