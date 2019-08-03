#ifndef BSTD_JSON_REGEX_HPP_
#define BSTD_JSON_REGEX_HPP_

#include <regex>

namespace bstd::json::parser {

  // TODO: string regex
  static const std::regex STRING_REGEX{R"("([^"\r]*)\")"};
  static const std::regex NUMBER_REGEX{R"([+-]?\d{0,10}\.?\d{0,10}(e\d|E\d|e\+\d|e-\d|E\+\d|E-\d)?\d{0,10})"};
  static const std::regex TRUE_LITERAL_REGEX{"true"};
  static const std::regex FALSE_LITERAL_REGEX{"false"};
  static const std::regex NULL_LITERAL_REGEX{"null"};
  static const std::regex WHITESPACE_REGEX{R"([ \n\r\t]+)"};

}

#endif

