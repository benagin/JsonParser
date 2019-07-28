#ifndef BSTD_JSON_REGEX_HPP_
#define BSTD_JSON_REGEX_HPP_

#include <regex>

namespace bstd::json::parser {

static const std::regex DOUBLE_QUOTE_REGEX{"[\"]"};
static const std::regex TRUE_LITERAL_REGEX{"true"};
static const std::regex FALSE_LITERAL_REGEX{"false"};
static const std::regex NULL_LITERAL_REGEX{"null"};
static const std::regex BEGIN_NUMBER_REGEX{"[0-9+-.]"};

}

#endif

