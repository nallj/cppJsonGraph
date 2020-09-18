#include <cppJsonGraph/graph.hpp>

namespace nallj {

  graph::graph() :
    directed_(true), idIsSet_(false), labelIsSet_(false), typeIsSet_(false) {}

  graph::graph(std::unordered_map<std::string, graphNode> nodes, std::vector<graphEdge> edges) :
    directed_(true), idIsSet_(false), labelIsSet_(false), typeIsSet_(false), nodes_(nodes),
    edges_(edges) {}

  graph::graph(const json& jsonGraph) :
    base(jsonGraph), directed_(true), idIsSet_(false), labelIsSet_(false), typeIsSet_(false) {

    idIsSet_ = hydrateAndCheckIfSet(jsonGraph, "id", id_);
    labelIsSet_ = hydrateAndCheckIfSet(jsonGraph, "label", label_);
    typeIsSet_ = hydrateAndCheckIfSet(jsonGraph, "type", type_);

    hydrateAndCheckIfSet(jsonGraph, "directed", directed_);

    // Process JSON nodes.
    for (auto& jsonNode : jsonGraph["nodes"].items()) {
      auto nodeId = jsonNode.key();
      auto jsonNodeData = jsonNode.value();

      nodes_.emplace(nodeId, jsonNodeData);
    }

    // Process JSON edges.
    for (auto& jsonEdge : jsonGraph["edges"]) {
      edges_.push_back(jsonEdge);
    }
  }

  /* Accessors */

  bool graph::getDirected() const {
    return directed_;
  }

  graphEdge graph::getEdgeAt(unsigned index) const {
    if (getEdgeCount() <= index) {
      throw cjgException("Requested edge index is out of range.");
    }
    return edges_.at(index);
  }

  std::vector<graphEdge>::const_iterator graph::getEdgeBeginIt() const {
    return edges_.begin();
  }

  unsigned graph::getEdgeCount() const {
    return edges_.size();
  }

  std::vector<graphEdge>::const_iterator graph::getEdgeEndIt() const {
    return edges_.end();
  }

  std::string graph::getId() const {
    return id_;
  }

  std::string graph::getLabel() const {
    return label_;
  }

  std::string graph::getType() const {
    return type_;
  }

  bool graph::getIdIsSet() const {
    return idIsSet_;
  }

  bool graph::getLabelIsSet() const {
    return labelIsSet_;
  }

  bool graph::getTypeIsSet() const {
    return typeIsSet_;
  }

  bool graph::hasNode(std::string key) const {
    auto it = nodes_.find(key);
    return it != nodes_.end();
  }

  /* Mutators */

  void graph::addEdge(graphEdge& edge) {
    edges_.push_back(edge);
  }

  void graph::addNode(std::string key, graphNode& node) {
    if (hasNode(key)) {
      throw new cjgException("Can't add node; key already has value.");
    }
    nodes_[key] = node;
  }

  void graph::clearEdges() {
    edges_.clear();
  }

  void graph::clearNodes() {
    nodes_.clear();
  }

  void graph::removeEdgeAt(unsigned index) {
    if (getEdgeCount() <= index) {
      throw cjgException("Requested edge index is out of range.");
    }
    edges_.erase(getEdgeBeginIt() + index);
  }

  void graph::removeEdgeRange(unsigned start, unsigned end) {
    if (getEdgeCount() <= start) {
      throw cjgException("Requested edge start index is out of range.");
    }
    if (getEdgeCount() <= end) {
      throw cjgException("Requested edge end index is out of range.");
    }
    auto beginning = getEdgeBeginIt();
    edges_.erase(beginning + start, beginning + end);
  }

  void graph::removeNode(std::string key) {
    auto it = nodes_.find(key);
    if (it == nodes_.end()) {
      throw cjgException("Graph does not contain requested key.");
    }
    nodes_.erase(it);
  }

  void graph::setDirected(bool directed) {
    directed_ = directed;
  }

  void graph::setId(std::string id) {
    id_ = id;
    idIsSet_ = true;
  }

  void graph::setLabel(std::string label) {
    label_ = label;
    labelIsSet_ = true;
  }

  void graph::setType(std::string type) {
    type_ = type;
    typeIsSet_ = true;
  }
  
  void graph::unsetId() {
    id_ = "";
    idIsSet_ = false;
  }

  void graph::unsetLabel() {
    label_ = "";
    labelIsSet_ = false;
  }

  void graph::unsetType() {
    type_ = "";
    typeIsSet_ = false;
  }

  /* Methods */

  void graph::addScalarToGraphJsonIfSet(json& graphJson, paramType paramType) const {
    auto varTuple = getOptParamByType(paramType);
    auto [varIsSet, varJsonKey, varVal] = varTuple;
    if (varIsSet) {
      graphJson[varJsonKey] = varVal;
    }
  }

  std::tuple<bool, std::string, std::string> graph::getOptParamByType(paramType type) const {
    switch (type) {
      case paramType::ID:
        return { idIsSet_, "id", id_ };
      case paramType::LABEL:
        return { labelIsSet_, "label", label_ };
      case paramType::TYPE:
        return { typeIsSet_, "type", type_ };
      default:
        throw cjgException("Invalid param type requested.");
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

  json graph::toJson() const {
    json graphJson = {
      { "directed", directed_ },
    };

    // Get optional parameters if they've been set.
    addScalarToGraphJsonIfSet(graphJson, paramType::ID);
    addScalarToGraphJsonIfSet(graphJson, paramType::LABEL);
    addScalarToGraphJsonIfSet(graphJson, paramType::TYPE);

    if (getMetadataIsSet()) {
      graphJson["metadata"] = getMetadataJson();
    }

    // Get the JSON objects for the nodes.
    auto nodesJson = json::object();
    for (const auto& [key, node] : nodes_) {
      nodesJson[key] = node.toJson();
    }
    graphJson["nodes"] = nodesJson;

    // Get the JSON objects for the edges.
    auto edgesJson = json::array();
    for (const auto& edge : edges_) {
      edgesJson.push_back(edge.toJson());
    }
    graphJson["edges"] = edgesJson;

    return graphJson;
  }
}
