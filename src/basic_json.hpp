#ifndef BSTD_BASIC_JSON_HPP_
#define BSTD_BASIC_JSON_HPP_

#include <exception>
#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace bstd::json {

using namespace std::string_literals;

template<
  template<typename, typename, typename...> class ObjectType = std::map,
  template<typename, typename...> class ArrayType = std::vector,
  class StringType = std::string,
  class NumberType = int,
  class BoolType = bool,
  class NullType = std::nullptr_t>
class basic_json;

using json = basic_json<>;

#define BASIC_JSON_TEMPLATE_DECLARATION                         \
  template<                                                     \
    template<typename, typename, typename...> class ObjectType, \
    template<typename, typename...> class ArrayType,            \
    class StringType,                                           \
    class NumberType,                                           \
    class BoolType,                                             \
    class NullType>                                             \

#define BASIC_JSON_TEMPLATE     \
  basic_json<ObjectType,        \
    ArrayType,                  \
    StringType,                 \
    NumberType,                 \
    BoolType,                   \
    NullType>                   \

/// \brief A C++ representation of a JSON object.
/// A JSON object consists of objects, arrays, and other values. These can be
/// easily stored as C++ structures. This interface allows
/// for accessing and changing the object(s).
/// See https://www.json.org/ for more details on JSON.
BASIC_JSON_TEMPLATE_DECLARATION
class basic_json final {

  public:

    using basic_json_t = BASIC_JSON_TEMPLATE;
    using object_t = ObjectType<const StringType, basic_json>;
    using array_t = ArrayType<basic_json>;
    using string_t = StringType;
    using number_t = NumberType;
    using boolean_t = BoolType;
    using null_t = NullType;
    using object_value_t = std::pair<const string_t, basic_json>;

    enum class value_t {
      object,
      array,
      string,
      number,
      boolean,
      null
    };

    basic_json() = default;
    basic_json(const basic_json&) = default;
    basic_json& operator=(const basic_json&) = default;
    basic_json(basic_json&&) = default;
    basic_json& operator=(basic_json&&) = default;

    /// \brief Construct a JSON with a character array.
    /// This constructor attempts to construct a `string_t` from a character
    /// array. Without this, character arrays would invoke the
    /// `basic_json(const boolean_t)` constructor.
    /// \param _string The string to use.
    basic_json(const char* _string)
      : basic_json(string_t{_string}) {}

    /// \brief Construct a JSON with a string value.
    /// \param _string The string to use.
    basic_json(const string_t& _string)
      : m_type{value_t::string}, m_value{_string} {}

    /// \brief Construct a JSON with a number value.
    /// \param _number The number to use.
    basic_json(const number_t _number)
      : m_type{value_t::number}, m_value{_number} {}

    /// \brief Construct a JSON with a boolean value.
    /// \param _boolean The boolean value to use.
    basic_json(const boolean_t _boolean)
      : m_type{value_t::boolean}, m_value{_boolean} {}

    /// \brief Construct a JSON with a null value.
    /// \param _null The null value to use.
    basic_json(const null_t _null)
      : m_type{value_t::null}, m_value{_null} {}

    /// \brief Construct a JSON object with initializer list.
    /// \param _il An std::intializer_list containing object values.
    basic_json(const std::initializer_list<object_value_t>& _il)
      : m_type{value_t::object}, m_value{object_t{_il}} {}

    /// \brief Check if the JSON object, array or string is empty.
    /// \return `true` if the JSON value is empty; `false` otherwise.
    /// \throws std::domain_error if `m_type` is not one of object, array, or
    ///         string.
    bool empty() const {
      switch (m_type) {
        case value_t::object:
          return std::get<object_t>(m_value).empty();
        case value_t::array:
          return std::get<array_t>(m_value).empty();
        case value_t::string:
          return std::get<string_t>(m_value).empty();
        case value_t::number:
        case value_t::boolean:
        case value_t::null:
        default:
          throw std::domain_error("empty is only defined for objects, arrays, " \
              "and strings.");
      }
    }

    // TODO: support array and string iterator versions of these methods.

    /// \brief Get an iterator to the beginning of the JSON object, array, or
    ///        string.
    /// \returns An iterator to the beginning of the JSON value.
    typename object_t::iterator begin() noexcept;

    /// \brief Get a const iterator to the beginning of the JSON object, array,
    ///        or string.
    /// \returns A const iterator to the beginning of the JSON value.
    typename object_t::const_iterator begin() const noexcept;
    const typename object_t::const_iterator cbegin() const noexcept;

    /// \brief Get an iterator to the end of the JSON object, array, or
    ///        string.
    /// \returns An iterator to the end of the JSON value.
    typename object_t::iterator end() noexcept;

    /// \brief Get a const iterator to the end of the JSON object, array, or
    ///        string.
    /// \returns A const iterator to the end of the JSON value.
    typename object_t::const_iterator end() const noexcept;
    const typename object_t::const_iterator cend() const noexcept;

    /// \brief Convert JSON to string.
    /// \param _include_ws If `true`, the original whitespace will be included.
    std::string to_string(const bool _include_ws = true) const noexcept;

    /// \brief Output operator overload.
    /// This calls to_string() which includes whitespace by default.
    /// If you do not want whitespace use
    /// `std::cout << basic_json.to_string(false);`
    /// \param _os An `std::ostream`.
    /// \param _json The calling object.
    /// \return An `std::ostream` containing the calling object as a string.
    friend std::ostream& operator<<(std::ostream& _os,
        const basic_json& _json) {
      return _os << _json.to_string();
    }

  private:

    friend std::ostream& operator<<(std::ostream& _os, const value_t& _type) {
      switch (_type) {
        case value_t::object:
          _os << "object";
          break;
        case value_t::array:
          _os << "array";
          break;
        case value_t::string:
          _os << "string";
          break;
        case value_t::number:
          _os << "number";
          break;
        case value_t::boolean:
          _os << "boolean";
          break;
        case value_t::null:
          _os << "null";
          break;
      }

      return _os;
    }

    value_t m_type{value_t::null};

    std::variant<object_t, array_t, string_t, number_t, boolean_t, null_t>
      m_value{nullptr};
};


BASIC_JSON_TEMPLATE_DECLARATION
std::string
BASIC_JSON_TEMPLATE::
to_string(const bool _include_ws) const noexcept {
  switch (m_type) {
    case value_t::object:
      return object_to_string(this, _include_ws);
    case value_t::array:
      // TODO: implement.
      return "array";
    case value_t::string:
      return std::get<string_t>(m_value);
    case value_t::number:
      return std::to_string(std::get<number_t>(m_value));
    case value_t::boolean:
      return std::to_string(std::get<boolean_t>(m_value));
    case value_t::null:
      return "null";
  }
}


BASIC_JSON_TEMPLATE_DECLARATION
typename BASIC_JSON_TEMPLATE::object_t::iterator
BASIC_JSON_TEMPLATE::
begin() noexcept {
  return std::get<object_t>(m_value).begin();
}


BASIC_JSON_TEMPLATE_DECLARATION
typename BASIC_JSON_TEMPLATE::object_t::const_iterator
BASIC_JSON_TEMPLATE::
begin() const noexcept {
  return std::get<object_t>(m_value).begin();
}


BASIC_JSON_TEMPLATE_DECLARATION
const typename BASIC_JSON_TEMPLATE::object_t::const_iterator
BASIC_JSON_TEMPLATE::
cbegin() const noexcept {
  return std::get<object_t>(m_value).cbegin();
}


BASIC_JSON_TEMPLATE_DECLARATION
typename BASIC_JSON_TEMPLATE::object_t::iterator
BASIC_JSON_TEMPLATE::
end() noexcept {
  return std::get<object_t>(m_value).end();
}


BASIC_JSON_TEMPLATE_DECLARATION
typename BASIC_JSON_TEMPLATE::object_t::const_iterator
BASIC_JSON_TEMPLATE::
end() const noexcept {
  return std::get<object_t>(m_value).end();
}


BASIC_JSON_TEMPLATE_DECLARATION
const typename BASIC_JSON_TEMPLATE::object_t::const_iterator
BASIC_JSON_TEMPLATE::
cend() const noexcept {
  return std::get<object_t>(m_value).cend();
}


BASIC_JSON_TEMPLATE_DECLARATION
std::string
object_to_string(const BASIC_JSON_TEMPLATE* _json,
    const bool _include_ws = true) {
  auto result = "{"s;

  for (const auto& member : *_json) {
    result += member.first + ":" + member.second.to_string();

    if (member != *std::prev(_json->end())) {
      result += ", ";
    }
  }

  return result += "}";
}


BASIC_JSON_TEMPLATE_DECLARATION
bool operator==(const BASIC_JSON_TEMPLATE& _json1,
    const BASIC_JSON_TEMPLATE& _json2) noexcept {
  // TODO: implement.
  return true;
}


}

#endif
