#ifndef BSTD_JSON_PARSER_BASE_HPP_
#define BSTD_JSON_PARSER_BASE_HPP_

#include <iostream>
#include <string>

#include <bstd_error.hpp>

namespace bstd::json::parser {

/// \brief Parser base class to manage some of the common functionality between
/// parser-like classes.
/// \template Container stores the objects we are parsing
template<class Container>
class parser_base {

  protected:

    typedef typename Container::const_iterator CCIT;

    /// \brief Default constructor.
    /// \param _debug debug mode flag
    parser_base(const bool _debug = false, const bool _throw = true)
        : m_debug(_debug), m_throw(_throw) {}

    parser_base(const Container& _container, const bool _debug = false,
        const bool _throw = true)
        : m_container(std::make_unique<Container>(_container)),
          parser_base(m_debug, _throw) {}

    /// \brief Deleted copy constructor.
    parser_base(const parser_base&) = delete;
    /// \brief Deleted copy assignment.
    parser_base& operator=(const parser_base&) = delete;

    virtual ~parser_base() = 0;

    /// \brief Throw an error or write it to standard error.
    /// \param _e an exception to throw or report
    virtual void report_error(const std::runtime_error _e) final;

    /// \biref Output operator overload.
    /// \param _os std::ostream
    /// \param _parser_base the calling object
    /// \return std::ostream
    friend std::ostream& operator<<(std::ostream& _os,
        const parser_base& _parser_base);

    /// \brief Abstract method signature for converting to a string.
    /// \return the object as a string
    virtual const std::string to_string() const = 0;

    bool m_debug{false};

    bool m_throw{true};

  private:

    /// This prevents the parser from reporting unecessary errors after a
    /// problem is detected.
    bool m_error_reported{false};

    std::unique_ptr<Container> m_container;

    /// This allows the parser to keep track of its place as it analyzes the
    /// elements in m_container.
    CCIT m_parse_index;

};


template<class Container>
parser_base<Container>::
~parser_base() {}


template<class Container>
void
parser_base<Container>::
report_error(const std::runtime_error _e) {
  if(m_error_reported)
    return;

  if(m_throw)
    throw _e;
  else
    std::cerr << _e.what() << std::endl;

  m_error_reported = true;
}


template<class Container>
std::ostream&
operator<<(std::ostream& _os, const parser_base<Container>& _parser_base) {
  return _os << _parser_base.to_string();
}


}

#endif
