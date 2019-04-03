#ifndef BSTD_JSON_HPP_
#define BSTD_JSON_HPP_

#include "json_base.hpp"
#include "parser/parser.hpp"
#include "structures/object.hpp"

namespace bstd::json {

// A C++ representation of a JSON object. A JSON object consists of objects,
// arrays, key, value pairs, and other values. These can be easily stored as
// C++ structures. This interface allows for accessing and changing the
// object(s). Changes can then be written back to the JSON file.
// This also acts as the highest object in the grammar found here:
// https://www.json.org/
class json final : public json_base {

  public:

    // Empty json object.
    json(const bool _debug = false) : json_base(_debug),
        m_value(std::make_shared<object>()) {}

    json& operator=(json _rhs);

    ~json() {}

    // Getters and setters.

    // Returns m_value.size().
    const std::size_t size() const override;

    const std::string& get_path() const;
    void set_path(const std::string& _path);

    const std::shared_ptr<value>& get_value() const;
    void set_value(const std::shared_ptr<value>& _value);

    // Operator overloads.

    // True if this contains exactly the same values as _rhs.
    bool operator==(const json& _rhs) const;

    bool operator!=(const json& _rhs) const;

    json& operator+=(const json& _rhs);

    friend json operator+(json _lhs, const json& _rhs);

    // Member functions.

    const std::string to_string(const bool _include_ws = true) const override;

    // Adds _value to m_value. The behavior depends on the type of _value.
    const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) override;

    using json_base::write;

    // Writes the json object to m_path.
    // Note: this erases the contents of m_path if the file exists.
    void write(const bool _include_ws = true) const;

  private:

    std::string m_path{""};

    // The json element at the highest level.
    std::shared_ptr<value> m_value;

};

}

#endif
