#include <bstd_json.hpp>

using namespace bstd::json;

int main() {
  const auto& empty = json();
  std::cout << "Empty: " << std::endl << empty << std::endl;

  const auto& null = json(nullptr);
  std::cout << "Null: " << std::endl << null << std::endl;

  const auto& string_json = json("string");
  std::cout << "String: " << std::endl << string_json << std::endl;

  const auto& number = json(100);
  std::cout << "Number: " << std::endl << number << std::endl;

  const auto& boolean = json(true);
  std::cout << "Boolean: " << std::endl << boolean << std::endl;

  const auto& object = json({{"name1", 100}, {"name2", "string"}});
  std::cout << "Object: " << std::endl << object << std::endl;

  /*
  const auto& array = json({1, "string", true, null});
  std::cout << "Array: " << std::endl << array << std::endl;
  */
}
