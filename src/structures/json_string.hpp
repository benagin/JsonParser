#ifndef BSTD_JSON_STRING_HPP_
#define BSTD_JSON_STRING_HPP_

#include <memory>
#include <string>

#include "value.hpp"

namespace bstd::json {

/// \brief Represents string from the JSON grammar (https://www.json.org/).
class json_string final : public value {

  public:

    /// TODO: inherit documentation?
    json_string(const bool _debug = false) : value(_debug) {}

    ~json_string() {}

    /// \brief The size of this array.
    /// \return the size of the underlying vector of values
    const std::size_t size() const override;

    /// TODO: inherit documentation?
    const std::string to_string(const bool _include_ws = true) const override;

    /// TODO: inherit documentation?
    const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) override;

  private:

    std::string m_value{""};

};

}

#endif

