#include <cppJsonGraph/serializer.hpp>

namespace nallj {
  serializer::serializer() {}

  void serializer::saveGraph(std::ofstream& output, graph& graph) const {
    json fileJson = {
      { "graph", graph.toJson() }
    };
    output << std::setw(2) << fileJson << std::endl;
  }

  void serializer::saveGraphs(std::ofstream& output, std::vector<graph>& graphs) const {
    if (!output.is_open()) {
      throw cjgException("Output stream is not open.");
    }
    if (graphs.empty()) {
      throw cjgException("No graphs were provided to the serializer for saving.");
    }

    json jsonGraphs;
    for (const auto& graph : graphs) {
      jsonGraphs.push_back(graph.toJson());
    }

    json fileJson = {
      { "graphs", jsonGraphs }
    };
    output << std::setw(2) << fileJson << std::endl;
  }
}
