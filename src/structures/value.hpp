#ifndef BSTD_JSON_VALUE_HPP_
#define BSTD_JSON_VALUE_HPP_

#include <utility>

#include "json_base.hpp"

namespace bstd::json::structures {

/// \brief This class represents a value from the grammar (https://www.json.org/).
/// Different from the grammar, this class also acts as a member and an element.
/// It acts as a member by storing the associated string (name) to the value. An
/// element is simply a value surrounded by optional whitespace. This class keeps
/// track of that whitespace acting as an element as well.
class value : public json_base {

  public:

    /// \brief Construct an empty value.
    /// \copydoc json_base::json_base(bool)
    value(const bool _debug) : json_base(_debug) {}

    virtual ~value() = 0;

    /// Getters.

    /// \brief Get this value's name.
    /// \return this value's name if it represents a JSON member or an empty
    ///         string if this value represents a JSON element
    virtual const std::string get_name() const final;

    virtual const std::size_t size() const override = 0;

    /// Member functions.

    virtual const std::string to_string(const bool _include_ws = true) const
        override = 0;

    virtual const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) override = 0;

  protected:

    std::pair<std::string, std::string> m_value_ws; ///< The whitespace that
                                                    ///< surrounds the value.

  private:

    std::string m_name{""}; ///< The string associated with this value. From the
                            ///< grammar this is the
                            ///< string in:
                            ///< member
                            ///<  ws string ws ':' value

    std::pair<std::string, std::string> m_name_ws; ///< The whitespace that
                                                   ///< surrounds the name of
                                                   ///< this value.
                                                   ///< This can be seen in the
                                                   ///< grammar above for m_name.

};


}

#endif
