#include "jgWriter.hpp"

jgWriter::jgWriter() {
  std::cout << "I am the gjWriter!\n";

  // read a JSON file
  std::ifstream i("test.json");
  json j;
  i >> j;

  // write prettified JSON to another file
  std::ofstream o("pretty.json");
  o << std::setw(2) << j << std::endl;

  std::cout << j;
}
