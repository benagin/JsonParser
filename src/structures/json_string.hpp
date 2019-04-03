#ifndef BSTD_JSON_STRING_HPP_
#define BSTD_JSON_STRING_HPP_

#include <memory>
#include <string>

#include "value.hpp"

namespace bstd::json {

class json_string final : public value {

  public:

    json_string(const bool _debug = false) : value(_debug) {}

    ~json_string() {}

    const std::size_t size() const override;

    const std::string to_string(const bool _include_ws = true) const override;

    const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) override;

  private:

    std::string m_value{""};

};

}

#endif

