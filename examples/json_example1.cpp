#include <bstd_json.hpp>

int main() {
  const auto empty = bstd::json::parse("");
  std::cout << "Empty: " << std::endl << *empty << std::endl;

  const auto ws = bstd::json::parse(" ");
  std::cout << "Whitespace: " << std::endl << *ws << std::endl;

  const auto json_object = bstd::json::parse("   { \"test\": \"test\" }");
  std::cout << "Json object: " << std::endl << *json_object << std::endl;

  const auto json_array = bstd::json::parse("   [ 1, 2, 3 ]");
  std::cout << "Json array: " << std::endl << *json_array << std::endl;
}
