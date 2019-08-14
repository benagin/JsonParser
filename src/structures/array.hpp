#ifndef BSTD_JSON_ARRAY_HPP_
#define BSTD_JSON_ARRAY_HPP_

#include <vector>

#include "value.hpp"

namespace bstd::json::structures {

/// \brief Represents an array from the JSON grammar (https://www.json.org/).
class array final : public value {

  public:

    /// \brief Construct an empty array.
    /// \copydetails value::value(bool)
    array(const bool _debug = false) : value(_debug) {}

    ~array() {}

    const std::size_t size() const override;

    /// TODO: write documentation.
    bool operator==(const array& _rhs) const;

    /// TODO: write documentation.
    bool operator!=(const array& _rhs) const;

    /// TODO: write documentation.
    array& operator+=(const array& _rhs);

    const std::string to_string(const bool _include_ws = true) const override;

    const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) override;

  private:

    std::string m_ws; ///< Objects might have whitepsace between their curly
                      ///< brackets instead of elements. This is 'ws' in the
                      ///< grammar for array:\n
                      ///< array\n
                      ///<  '[' ws ']'\n
                      ///<  '[' elements ']'\n

    std::vector<std::shared_ptr<value>> m_values;

};

}

#endif
