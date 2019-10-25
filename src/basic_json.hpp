#ifndef BSTD_BASIC_JSON_HPP_
#define BSTD_BASIC_JSON_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "utilities/json_file_util.hpp"

namespace bstd::json {

class basic_json;
using json = basic_json;

/// \brief A C++ representation of a JSON object.
/// A JSON object consists of objects, arrays, key, value pairs, and other
/// values. These can be easily stored as C++ structures. This interface allows
/// for accessing and changing the object(s). Changes can then be written back
/// to the JSON file.
/// This class also acts as the highest object in the grammar found here:
/// https://www.json.org/
class basic_json {

  public:

    using ObjectType = std::unordered_map<std::string, basic_json>;
    using ArrayType = std::vector<basic_json>;
    using StringType = std::string;
    using NumberType = int;
    using BoolType = bool;
    using NullType = std::nullptr_t;

    /// \brief Construct an empty basic_json object.
    /// \param _debug debug mode flag
    basic_json(const bool _debug = false) : m_debug(_debug) {}

    // TODO: copy constructor.

    /// \brief Copy assignment operator.
    /// \param _rhs the basic_json object on the right hand side of the operator
    basic_json& operator=(basic_json _rhs);

    ~basic_json() {}

    const std::size_t size() const;

    /// \brief Get the path of the associated JSON file.
    /// \return the path as a string
    const std::string& get_path() const;
    /// \brief Set the path of the associated JSON file.
    /// \param _path the path as a string
    void set_path(const std::string& _path);

    /// \brief Equality operator.
    /// \param _rhs the basic_json object on the right hand side of the operator
    /// \return true if this contains the same values as _rhs
    bool operator==(const basic_json& _rhs) const;

    /// \brief Inequality operator.
    /// \param _rhs the basic_json object on the right hand side of the operator
    /// \return true if this does not contain the same value as _rhs
    bool operator!=(const basic_json& _rhs) const;

    /// \brief Shorthand for concatenating two basic_json objects.
    /// This simply concatenates the values of this object and _rhs'.
    /// \param _rhs the basic_json object on the right hand side of the operator
    /// \return this with the concatenated value from _rhs
    basic_json& operator+=(const basic_json& _rhs);

    /// \brief Concatenate two basic_json objects.
    /// \param _lhs the basic_json object on the left hand side of the operator
    /// \param _rhs the basic_json object on the right hand side of the operator
    /// \return _lhs
    friend basic_json operator+(basic_json _lhs, const basic_json& _rhs);

    const std::string to_string(const bool _include_ws = true) const;

    /// \brief Output operator overload.
    /// This calls to_string() which includes whitespace by default.
    /// If you do not want whitespace use
    /// `std::cout << basic_json.to_string(false);`
    /// \param _os std::ostream
    /// \param _json the calling object
    /// \return std::ostream containing the calling object as a string
    friend std::ostream& operator<<(std::ostream& _os, const basic_json& _json);

    /// \brief Writes the basic_json object to m_path.
    /// Note: this erases the contents of m_path if the file exists.
    /// \param _include_ws if true the original whitespace will be included
    void write(const bool _include_ws = true) const;

    /// \brief Write the structure to a path.
    /// \param _path the path to write to
    /// \param _include_ws if true, the original whitespace will be included
    void write(const std::string _path, const bool _include_ws = true) const;

  protected:

    bool m_debug{false};

  private:

    std::string m_path;

    ArrayType m_array;
    ObjectType m_object;

};


basic_json&
basic_json::
operator=(basic_json _rhs) {
  std::swap(m_path, _rhs.m_path);
  // TDOO: implement.

  return *this;
}


const std::size_t
basic_json::
size() const {
  // TDOO: implement.
  return 0;
}


const std::string&
basic_json::
get_path() const {
  return m_path;
}


void
basic_json::
set_path(const std::string& _path) {
  m_path = _path;
}


const std::string
basic_json::
to_string(const bool _include_ws) const {
  // TDOO: implement.
  return "";
}


bool
basic_json::
operator==(const basic_json& _rhs) const {
  if(size() != _rhs.size())
    return false;

  // TDOO: implement.
  return true;
}


bool
basic_json::
operator!=(const basic_json& _rhs) const {
  return !(*this == _rhs);
}


basic_json&
basic_json::
operator+=(const basic_json& _rhs) {
  // TDOO: implement.
  return *this;
}


basic_json
operator+(basic_json _lhs, const basic_json& _rhs) {
  _lhs += _rhs;
  return _lhs;
}


std::ostream&
operator<<(std::ostream& _os, const basic_json& _json) {
  return _os << _json.to_string();
}


void
basic_json::
write(const bool _include_ws) const {
  write(m_path, _include_ws);
}


void
basic_json::
write(const std::string _path, const bool _include_ws) const {
  auto ofs =
    utilities::open_json_file(_path, std::fstream::out | std::fstream::trunc);

    ofs << to_string(_include_ws);
}


}

#endif
