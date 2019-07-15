#ifndef BSTD_JSON_PARSE_ERROR_HPP_
#define BSTD_JSON_PARSE_ERROR_HPP_

#include "token.hpp"

namespace bstd::json::parser {

/// \brief
/// TODO: implement this.
class parse_error {

  public:

    parse_error() {}

    ~parse_error() {}

  private:

    token m_token;

};

}

#endif
