#include "parser.hpp"

namespace bstd::json {


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

  // Now we have a JSON string for sure.

  std::cout << json_as_string << std::endl;

  auto tokens = scan(json_as_string);

  std::cout << '[';
  for(int i = 0; i < tokens.size(); ++i) {
    std::cout << tokens.at(i) << ' ';

    if(i != tokens.size() - 1)
      std::cout << ',';
  }
  std::cout << ']';

  return parse(tokens);
}

std::shared_ptr<json>
parse(const std::vector<token> _tokens) {
  // TODO: implement.
  return std::make_shared<json>();
}


std::vector<token>
scan(const std::string& _json_as_string) {
  std::vector<token> tokens;

  for(auto& c : _json_as_string)
    tokens.push_back(token(token::no_type, c));
  // TODO: implement.

  return tokens;
}



std::shared_ptr<object>
parse_object(const std::string _string) {
  // TODO: implement.
  return std::make_shared<object>();
}


std::shared_ptr<array>
parse_array(const std::string _string) {
  // TODO: implement.
  return std::make_shared<array>();
}


std::shared_ptr<json_string>
parse_json_string(const std::string _string) {
  return std::make_shared<json_string>();
}


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

  //_string.remove_prefix(index);

  return _string.substr(0, index);
}


}
