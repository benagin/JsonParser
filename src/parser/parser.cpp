#include "parser.hpp"

namespace bstd::json::parser {


std::shared_ptr<json>
parse(const char* _string, const bool _debug, const bool _throw) {
  return parse(std::string(_string), _debug, _throw);
}


std::shared_ptr<json>
parse(const std::string& _string, const bool _debug, const bool _throw) {
  // Could be a .json file path or a JSON string.
  auto json_as_string = _string;

  // Try to open string as a path.
  auto ifs = utilities::open_json_file(_string, std::fstream::in);

  if(ifs.is_open()) {
    json_as_string = std::string((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());
  }

  // Now we are certain we have a JSON string.

  if(_debug)
    std::cout << json_as_string << std::endl;

  lexer l(json_as_string, _debug, _throw);
  l.lex();

  parser p(l.get_tokens(), _debug, _throw);

  return p.get_json();
}


std::shared_ptr<json>
parser::
get_json() const noexcept {
  return m_json;
}


const std::string
parser::
to_string() const noexcept {
  return m_json->to_string();
}


}
