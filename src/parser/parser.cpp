#include "parser.hpp"

namespace bstd::json::parser {


std::shared_ptr<json>
parse(const char* _string) {
  return parse(std::string(_string));
}

std::shared_ptr<json>
parse(const std::string& _string) {
  // Could be a .json file path or a JSON string.
  auto json_as_string = _string;

  // Try to open string as a path.
  auto ifs = utilities::open_json_file(_string, std::fstream::in);

  if(ifs.is_open()) {
    json_as_string = std::string((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());
  }

  // Now we are certain we have a JSON string.

  // TODO: setup debug flag for output like this.
  std::cout << json_as_string << std::endl;

  // TODO: change this to store the lexer in the parser once parser is a class.
  lexer l(json_as_string);
  l.lex();
  return parse(l);
}

std::shared_ptr<json>
parse(const lexer& _lexer) {
  // TODO: implement.
  return std::make_shared<json>();
}

// TODO: Figure out what to do with this. It's dead code right now.
const std::string
trim_leading_ws(std::string& _string) {
  // Whitespace characters supported by JSON.
  // See grammar (www.json.org) for ws.
  constexpr std::string_view ws = " \t\n\r";

  const auto index = _string.find_first_not_of(ws);

  // Case where there is no whitespace.
  if(index == 0) {
    return "";
  }

  // Case where the whole string is whitespace.
  if(index == _string.npos) {
    _string = "";
    return _string;
  }

  return _string.substr(0, index);
}


}
