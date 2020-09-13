#ifndef NALLJ_CJG_SERIALIZER
#define NALLJ_CJG_SERIALIZER

#include <fstream> // ifstream, ofstream
#include <iomanip> // setw
#include <iostream> // cout

#include <nlohmann/json.hpp>

#include "graph.hpp"
#include "informedException.hpp"

using json = nlohmann::json;

namespace nallj {
  class serializer {
  public:
    serializer();
    void saveGraph(std::ofstream& output, graph& graphs);
    void saveGraphs(std::ofstream& output, std::vector<graph>& graphs);
  };
};

#endif
