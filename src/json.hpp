#ifndef BSTD_JSON_HPP_
#define BSTD_JSON_HPP_

#include "json_base.hpp"
#include "structures/json_string.hpp"

namespace bstd::json {

using structures::json_string;

/// \brief A C++ representation of a JSON object.
/// A JSON object consists of objects, arrays, key, value pairs, and other
/// values. These can be easily stored as C++ structures. This interface allows
/// for accessing and changing the object(s). Changes can then be written back
/// to the JSON file.
/// This class also acts as the highest object in the grammar found here:
/// https://www.json.org/
class json final : public json_base {

  public:

    /// \brief Construct an empty json object.
    /// TODO: inherit documentation?
    /// \param _debug debug mode flag
    json(const bool _debug = false) : json_base(_debug),
        m_value(std::make_shared<json_string>()) {}

    // TODO: copy constructor.

    /// \brief Copy assignment operator.
    /// \param _rhs the json object on the right hand side of the operator
    json& operator=(json _rhs);

    ~json() {}

    /// Getters and setters.

    /// \brief The size of this json object.
    /// \return the size of the root value
    const std::size_t size() const override;

    /// \brief Get the path of the associated JSON file.
    /// \return the path as a string
    const std::string& get_path() const;
    /// \brief Set the path of the associated JSON file.
    /// \param _path the path as a string
    void set_path(const std::string& _path);

    /// \brief Get the root value.
    /// \return a shared_ptr to the root value
    const std::shared_ptr<value>& get_value() const;
    /// \brief Set the root value.
    /// \param _value a shared_ptr to a value
    void set_value(const std::shared_ptr<value>& _value);

    /// Operator overloads.

    /// \brief Equality operator.
    /// \param _rhs the json object on the right hand side of the operator
    /// \return true if this contains the same values as _rhs
    bool operator==(const json& _rhs) const;

    /// \brief Inequality operator.
    /// \param _rhs the json object on the right hand side of the operator
    /// \return true if this does not contain the same value as _rhs
    bool operator!=(const json& _rhs) const;

    /// \brief Shorthand for concatenating two json objects.
    /// This simply concatenates the values of this object and _rhs'.
    /// \param _rhs the json object on the right hand side of the operator
    /// \return this with the concatenated value from _rhs
    json& operator+=(const json& _rhs);

    /// \brief Concatenate two json objects.
    /// \param _lhs the json object on the left hand side of the operator
    /// \param _rhs the json object on the right hand side of the operator
    /// \return _lhs
    friend json operator+(json _lhs, const json& _rhs);

    /// Member functions.

    /// \brief Convert this json object to a string representation.
    /// This will be the same string that was originally parsed.
    /// \param _includ_ws if true, the original whitespace will be included in
    ///                   the string.
    /// \return a string representation of this json object
    const std::string to_string(const bool _include_ws = true) const override;

    /// \brief Concatenate _value to m_value. The behavior depends on the type of
    /// _value.
    /// \param _value the value to be concatenated
    /// \return the new, concatenated value
    const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) override;

    using json_base::write;

    /// \brief Writes the json object to m_path.
    /// Note: this erases the contents of m_path if the file exists.
    /// \param _include_ws if true the original whitespace will be included
    void write(const bool _include_ws = true) const;

  private:

    std::string m_path{""};

    /// The root JSON element.
    std::shared_ptr<value> m_value;

};

}

#endif
