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

    /// \brief Construct with a container to parse.
    /// \param _container the collection of elements to parse
    /// \param _debug debug mode flag
    /// \param _debug if true errors will be thrown, otherwise they will be
    ///               written to standard error
    parser_base(const Container& _container, const bool _debug = false,
        const bool _throw = true)
        : m_debug(_debug), m_throw(_throw),
          m_container(std::make_shared<Container>(_container)),
          m_index(m_container->cbegin()) {}

    /// \brief Deleted copy constructor.
    parser_base(const parser_base&) = delete;
    /// \brief Deleted copy assignment.
    parser_base& operator=(const parser_base&) = delete;

    virtual ~parser_base() = 0;

    /// \brief Get the container.
    /// \returns m_container
    const auto& get_container() const noexcept;

    /// \brief Set the container.
    /// \param _container the container to set
    void set_container(const Container& _container) const noexcept;

    // TODO: think about changing the name from element since these functions
    // return iterators.
    /// \brief Get the current index
    /// \return an iterator to the current element
    const auto& get_element() const noexcept;

    /// \brief Process the next element in m_container.
    /// \return an iterator to the next element in m_container
    /// \throws std::runtime_error if m_throw is true and the next element is
    ///         past-the-end
    const auto next_element();

    /// \brief Check the next element without moving the index.
    /// \return an iterator to the next element in m_container or
    ///         m_container.cend() if the next element is past-the-end
    const auto peek_next_element() noexcept;

    /// \brief Advance the index by _n (_n can be negative).
    /// \throws std::runtime_error if m_throw is true and the advance would move
    ///         the index past-the-end.
    void advance_index(const int _n);

    /// \brief Reset the index.
    void reset() noexcept;

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

    std::shared_ptr<Container> m_container;

    /// This allows the parser to keep track of its place as it analyzes the
    /// elements in m_container.
    CCIT m_index;

};


template<class Container>
parser_base<Container>::
~parser_base() {}


template<class Container>
const auto&
parser_base<Container>::
get_container() const noexcept {
  return m_container;
}


template<class Container>
void
parser_base<Container>::
set_container(const Container& _container) const noexcept {
  m_container = std::make_unique<>(_container);
}


template<class Container>
const auto&
parser_base<Container>::
get_element() const noexcept {
  return m_index;
}


template<class Container>
const auto
parser_base<Container>::
next_element() {
  if(m_index == m_container->cend())
    throw std::runtime_error("Attempt to process an element after all have been \
        retrieved.");

  return m_index++;
}


template<class Container>
const auto
parser_base<Container>::
peek_next_element() noexcept {
  if(m_index == m_container->cend())
    return m_container->cend();

  return std::next(m_index);
}


template<class Container>
void
parser_base<Container>::
advance_index(const int _n) {
  std::advance(m_index, _n);
}


template<class Container>
void
parser_base<Container>::
reset() noexcept {
  m_index = m_container->cbegin();
  m_error_reported = false;
}


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
