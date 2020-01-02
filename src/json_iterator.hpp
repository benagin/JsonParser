#ifndef BSTD_JSON_ITERATOR_HPP_
#define BSTD_JSON_ITERATOR_HPP_

#include <iterator>

namespace bstd::json {

/// \brief An iterator for JSON objects, arrays, and strings.
/// Other JSON values cannot have iterators.
/// \tparam Iter The underlying object, array, or string implementation iterator.
template<class Iter>
class json_iterator {

  public:

    using value_type = typename std::iterator_traits<Iter>::value_type;
    using difference_type = typename std::iterator_traits<Iter>::difference_type;
    using pointer = typename std::iterator_traits<Iter>::pointer;
    using reference = typename std::iterator_traits<Iter>::reference;
    using iterator_category =
      typename std::iterator_traits<Iter>::iterator_category;
    using iterator_type = Iter;

    /// \brief Default constructor.
    constexpr json_iterator() {}

    /// \brief Construct with a different iterator type.
    /// \param _it Another iterator.
    constexpr explicit json_iterator(iterator_type _it) : m_base{_it} {}

    /// \brief Construct with another `json_iterator`.
    /// \param _other Another iterator.
    /// \template An iterator type.
    template<class U>
    constexpr json_iterator(const json_iterator<U>& _other)
        : m_base{_other.base()} {}

    /// \brief Copy assignment constructor.
    /// \param _other Another iterator.
    /// \tparam U Another iterator type.
    template<class U>
    constexpr json_iterator& operator=(const json_iterator<U>& _other) {
      m_base = _other.base();
      return *this;
    }

    /// \brief Get the underlying base iterator.
    /// \return The underlying base iterator.
    constexpr iterator_type base() const {
      return m_base();
    }

    /// \brief Dereference operator.
    /// \return A reference to the element that this iterator points to.
    constexpr reference operator*() const {
      return *base();
    }


    /// \brief Dereference operator.
    /// \return A pointer to the element that this iterator points to.
    constexpr pointer operator->() const {
      return std::addressof(operator*());
    }

    /// \brief Access operator.
    /// \param _n The relative position.
    /// \return A reference to the element at the relative position.
    constexpr value_type& operator[](difference_type _n) const {
      return base()[_n];
    }

    /// \brief Pre-increment operator.
    /// \return This iterator.
    constexpr json_iterator& operator++() {
      ++base();
      return *this;
    }

    /// \brief Pre-decrement operator.
    /// \return This iterator.
    constexpr json_iterator& operator--() {
      --base();
      return *this;
    }

    /// \brief Post-increment operator.
    /// \return A copy of this iterator before the change.
    constexpr json_iterator operator++(int) {
      auto copy = *this;
      base()++;
      return copy;
    }

    /// \brief Post-decrement operator.
    /// \return A copy of this iterator before the change.
    constexpr json_iterator operator--(int) {
      auto copy = *this;
      base()--;
      return copy;
    }

    /// \brief Get an advanced iterator.
    /// \param _n The amount to advance.
    /// \return An iterator advance by _n.
    constexpr json_iterator operator+(difference_type _n) const {
      return json_iterator(base() + _n);
    }

    /// \brief Get an advanced iterator in the negative direction.
    /// \param _n The amount to advance.
    /// \return An iterator advance by _n.
    constexpr json_iterator operator-(difference_type _n) const {
      return json_iterator(base() - _n);
    }

    /// \brief Advance this iterator.
    /// \param _n The amount to advance.
    /// \return This iterator.
    constexpr json_iterator& operator+=(difference_type _n) {
      base() + _n;
      return *this;
    }

    /// \brief Advance this iterator in the negative direction.
    /// \param _n The amount to advance.
    /// \return This iterator.
    constexpr json_iterator& operator-=(difference_type _n) {
      base() - _n;
      return *this;
    }

  private:

    iterator_type m_base{};

};


template<class Iterator1, class Iterator2>
constexpr bool
operator==(const json_iterator<Iterator1>& _lhs,
    const json_iterator<Iterator2>& _rhs) {
  return _lhs.base() == _rhs.base();
}


template<class Iterator1, class Iterator2>
constexpr bool
operator!=(const json_iterator<Iterator1>& _lhs,
    const json_iterator<Iterator2>& _rhs) {
  return _lhs.base() != _rhs.base();
}


template<class Iterator1, class Iterator2>
constexpr bool
operator<(const json_iterator<Iterator1>& _lhs,
    const json_iterator<Iterator2>& _rhs) {
  return _lhs.base() < _rhs.base();
}


template<class Iterator1, class Iterator2>
constexpr bool
operator<=(const json_iterator<Iterator1>& _lhs,
    const json_iterator<Iterator2>& _rhs) {
  return _lhs.base() <= _rhs.base();
}


template<class Iterator1, class Iterator2>
constexpr bool
operator>(const json_iterator<Iterator1>& _lhs,
    const json_iterator<Iterator2>& _rhs) {
  return _lhs.base() > _rhs.base();
}


template<class Iterator1, class Iterator2>
constexpr bool
operator>=(const json_iterator<Iterator1>& _lhs,
    const json_iterator<Iterator2>& _rhs) {
  return _lhs.base() >= _rhs.base();
}


template<class Iter>
constexpr json_iterator<Iter>
operator+(typename json_iterator<Iter>::difference_type _n,
    const json_iterator<Iter>& _it) {
  return json_iterator<Iter>(_it.base() + _n);
}


template<class Iterator1, class Iterator2>
constexpr auto
operator-(const json_iterator<Iterator1>& _lhs,
    const json_iterator<Iterator2>& _rhs) -> decltype(_rhs.base() - _lhs.base()) {
  return _rhs.base() - _lhs.base();
}


}

#endif
