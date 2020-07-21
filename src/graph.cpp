#include "graph.hpp"

namespace nallj {
  // graph::graph() {}

  graph::graph(std::unordered_map<std::string, graphNode> nodes, std::vector<graphEdge> edges) :
    directed_(true), idIsSet_(false), labelIsSet_(false), typeIsSet_(false), nodes_(nodes),
    edges_(edges) {}

  graph::graph(const json& jsonGraph) :
    base(jsonGraph), directed_(true), idIsSet_(false), labelIsSet_(false), typeIsSet_(false) {

    idIsSet_ = hydrateAndCheckIfSet(jsonGraph, "id", id_);
    labelIsSet_ = hydrateAndCheckIfSet(jsonGraph, "label", label_);
    typeIsSet_ = hydrateAndCheckIfSet(jsonGraph, "type", type_);

    
    // hydrateMetadata(jsonGraph); // DRY, leave this to the base
    hydrateAndCheckIfSet(jsonGraph, "directed", directed_);

    // Process JSON nodes.
    for (auto& jsonNode : jsonGraph["nodes"].items()) {
      std::cout << "MY JSON NODE\n" << jsonNode.key() << " :\n";
      std::cout <<  std::setw(2) << jsonNode.value() << "\n";

      auto nodeId = jsonNode.key();
      auto jsonNodeData = jsonNode.value();
      nodes_.emplace(nodeId, jsonNodeData);

      std::cout << "metadata single0n " << nodes_["nodeIdBlarg"].getMetadata()["single0n"] << "\n";
    }
    
    // Process JSON edges.
    for (auto& jsonEdge : jsonGraph["edges"]) {
      std::cout << "MY JSON EDGE\n" << std::setw(2) << jsonEdge << "\n";
      edges_.push_back(jsonEdge);
    }
  }

  template <typename T>
  bool graph::hydrateAndCheckIfSet(const json& jsonGraph, const char* itemKey, T& variable) {
    if (jsonGraph.count(itemKey) == 1) {
      auto item = jsonGraph[itemKey];
      auto value = item.get<T>();
      variable = value;
      return true;
    }
    return false;
  }

}
