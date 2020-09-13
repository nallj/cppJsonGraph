#include <cppJsonGraph/graph.hpp>

namespace nallj {

  graph::graph() :
    directed_(true), idIsSet_(false), labelIsSet_(false), typeIsSet_(false) {

    hydratePointerMaps();
  }

  graph::graph(std::unordered_map<std::string, graphNode> nodes, std::vector<graphEdge> edges) :
    directed_(true), idIsSet_(false), labelIsSet_(false), typeIsSet_(false), nodes_(nodes),
    edges_(edges) {

    hydratePointerMaps();
  }

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

    hydratePointerMaps();
  }

  /* Accessors */

  graphEdge graph::getEdgeAt(unsigned index) const {
    if (getEdgeCount() <= index) {
      throw informedException("Requested edge index is out of range.");
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
      throw new informedException("Can't add node; key already has value.");
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
      throw informedException("Requested edge index is out of range.");
    }
    edges_.erase(getEdgeBeginIt() + index);
  }

  void graph::removeEdgeRange(unsigned start, unsigned end) {
    if (getEdgeCount() <= start) {
      throw informedException("Requested edge start index is out of range.");
    }
    if (getEdgeCount() <= end) {
      throw informedException("Requested edge end index is out of range.");
    }
    auto beginning = getEdgeBeginIt();
    edges_.erase(beginning + start, beginning + end);
  }

  void graph::removeNode(std::string key) {
    auto it = nodes_.find(key);
    if (it == nodes_.end()) {
      throw informedException("Graph does not contain requested key.");
    }
    nodes_.erase(it);
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

  void graph::addScalarToGraphJsonIfSet(json& graphJson, graphParamType paramType) const {
    if (graphParamToIsSetPtrMap.at(paramType)) {
      auto graphParamKey = graphParamToKeyMap.at(paramType);
      graphJson[graphParamKey] = *graphParamToValPtrMap.at(paramType).get();
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

  void graph::hydratePointerMaps() {

    auto idPtr = std::make_shared<std::string>(id_);
    auto labelPtr = std::make_shared<std::string>(label_);
    auto typePtr = std::make_shared<std::string>(type_);

    graphParamToValPtrMap.emplace(graphParamType::ID, idPtr);
    graphParamToValPtrMap.emplace(graphParamType::LABEL, labelPtr);
    graphParamToValPtrMap.emplace(graphParamType::TYPE, typePtr);

    auto idIsSetPtr = std::make_shared<bool>(idIsSet_);
    auto labelIsSetPtr = std::make_shared<bool>(labelIsSet_);
    auto typeIsSetPtr = std::make_shared<bool>(typeIsSet_);

    graphParamToIsSetPtrMap.emplace(graphParamType::ID, idIsSetPtr);
    graphParamToIsSetPtrMap.emplace(graphParamType::LABEL, labelIsSetPtr);
    graphParamToIsSetPtrMap.emplace(graphParamType::TYPE, typeIsSetPtr);

    graphParamToKeyMap = {
      { graphParamType::ID, "id" },
      { graphParamType::LABEL, "label" },
      { graphParamType::TYPE, "type" }
    };
  }

  json graph::toJson() const {
    json graphJson = {
      { "directed", directed_ },
    };

    // Get optional parameters if they've been set.
    addScalarToGraphJsonIfSet(graphJson, graphParamType::ID);
    addScalarToGraphJsonIfSet(graphJson, graphParamType::LABEL);
    addScalarToGraphJsonIfSet(graphJson, graphParamType::TYPE);

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
