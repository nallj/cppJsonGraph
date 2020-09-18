#ifndef NALLJ_CJG_DESERIALIZER
#define NALLJ_CJG_DESERIALIZER

#include <fstream> // ifstream
#include <iomanip> // setw
#include <iostream> // cout
#include <vector> // vector

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include "schema.hpp"
#include "graph.hpp"

using json = nlohmann::json;
using nlohmann::json_schema::json_validator;

namespace nallj {
  class deserializer {
    json_validator validator;

    // Not needed due to implict cast.
    //graph produceGraph(json jsonGraph);
    //void produceGraphAndInsert(json jsonData, std::vector<graph>& collection);

  public:
    deserializer();

    bool isFileValid(std::ifstream& file);
    graph getGraph(std::ifstream& file);
    std::vector<graph> getGraphs(std::ifstream& file);
  };
}

#endif
