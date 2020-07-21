#ifndef JG_READER_HPP
#define JG_READER_HPP

#include <fstream> // ifstream
#include <iomanip> // setw
#include <iostream> // cout
#include <vector> // vector

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include "schema.cpp"
#include "graph.hpp"

using json = nlohmann::json;
using nlohmann::json_schema::json_validator;

namespace nallj {
  class jgReader {
    json_validator validator;

    // Not needed due to implict cast.
    //graph produceGraph(json jsonGraph);
    //void produceGraphAndInsert(json jsonData, std::vector<graph>& collection);

  public:
    jgReader();

    bool isFileValid(std::ifstream& file);
    std::vector<graph> getGraphs(std::ifstream& file);
  };
}

#endif
