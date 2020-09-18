#include <cppJsonGraph/deserializer.hpp>

namespace nallj {
  deserializer::deserializer() {
    try {
      validator.set_root_schema(schema);
    } catch (const std::exception &e) {
      std::cerr << "Validation of schema failed. Error: " << e.what() << "\n";
      //return EXIT_FAILURE;
      throw e;
    }
  }

  bool deserializer::isFileValid(std::ifstream& file) {
    json jsonData;

    try {
      file >> jsonData;
      validator.validate(jsonData);
      std::cout << "File LOOKS GOOD!\n";

    } catch (const std::exception &e) {
      std::cerr << "File is not valid: " << e.what() << "\n";
      return false;
    }
    return true;
  }

  graph deserializer::getGraph(std::ifstream& file) {
    auto graphs = getGraphs(file);
    return graphs[0];
  }

  std::vector<graph> deserializer::getGraphs(std::ifstream& file) {
    json jsonData;
    file >> jsonData;

    std::vector<graph> result;

    // This is a singular graph file.
    if (jsonData.count("graph") == 1) {
      result.push_back(jsonData["graph"]);

    // This file contains multiple graphs.
    } else {
      for (auto& jsonGraph : jsonData["graphs"]) {
        result.push_back(jsonGraph);
      }
    }
    return result;
  }
}
