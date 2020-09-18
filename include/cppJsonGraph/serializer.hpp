#ifndef NALLJ_CJG_SERIALIZER
#define NALLJ_CJG_SERIALIZER

#include <fstream> // ifstream, ofstream
#include <iomanip> // setw
#include <iostream> // cout

#include <nlohmann/json.hpp>

#include "graph.hpp"
#include "cjgException.hpp"

using json = nlohmann::json;

namespace nallj {
  class serializer {
  public:
    serializer();
    void saveGraph(std::ofstream& output, graph& graphs) const;
    void saveGraphs(std::ofstream& output, std::vector<graph>& graphs) const;
  };
};

#endif
