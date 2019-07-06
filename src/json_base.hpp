#ifndef BSTD_JSON_BASE_HPP_
#define BSTD_JSON_BASE_HPP_

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include <bstd_error.hpp>

#include "utilities/json_file_util.hpp"

namespace bstd::json {

namespace structures {

class value;

}

using structures::value;

/// \brief Abstract class used as base for each json related structure.
class json_base {

  public:

    /// \brief Default constructor.
    /// \param _debug debug mode flag
    json_base(const bool _debug) : m_debug(_debug) {}

    virtual ~json_base() = 0;

    /// \brief Abstract method signature for getting the size of the structure.
    /// \return the size of the structure
    virtual const std::size_t size() const = 0;

    /// \biref Output operator overload.
    /// This calls to_string() which includes whitespace by default.
    /// If you do not want whitespace use
    /// `std::cout << derived.to_string(false);`
    /// \param _os std::ostream
    /// \param _json_base the calling object
    /// \return std::ostream
    friend std::ostream& operator<<(std::ostream& _os,
        const json_base& _json_base);

    /// \brief Abstract method signature for converting to a string.
    /// \param _include_ws if true, the original whitespace will be included
    /// \return string representation of the structure
    virtual const std::string to_string(const bool _include_ws = true) const = 0;

    /// \brief Abstract method signature for concatenating a value to the
    ///        structure.
    /// \param _value the value to be concatenated
    /// \return the new, concatenated value
    virtual const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) = 0;

    /// \brief Write the structure to a path.
    /// \param _path the path to write to
    /// \param _include_ws if true, the original whitespace will be included
    virtual void write(const std::string _path, const bool _include_ws = true)
        const final;

  protected:

    bool m_debug{false};

};

}

#endif
