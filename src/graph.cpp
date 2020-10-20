#include <cppJsonGraph/graph.hpp>

namespace nallj {

  graph::graph() :
    directed_(true), idIsSet_(false), labelIsSet_(false), strict_(true), typeIsSet_(false) {}

  graph::graph(const graph& g) :
    directed_(g.directed_), edges_(g.edges_), endNodes_(g.endNodes_), id_(g.id_),
    idIsSet_(g.idIsSet_), label_(g.label_), labelIsSet_(g.labelIsSet_), nodes_(g.nodes_),
    startNodes_(g.startNodes_), strict_(g.strict_), toNodesMap_(g.toNodesMap_), type_(g.type_),
    typeIsSet_(g.typeIsSet_) {}

  /**
   * @param strict - Strict mode ensures all graph edges are valid (both nodes exist in the graph)
   * and that edge node's directed_ value matches the graph's directed_ value.
   */
  graph::graph(bool strict) :
    directed_(true), idIsSet_(false), labelIsSet_(false), strict_(strict), typeIsSet_(false) {}

  graph::graph(nodeMap nodes, edgeList edges, bool strict) :
    directed_(true), edges_(edges), idIsSet_(false), labelIsSet_(false), nodes_(nodes),
    strict_(strict), typeIsSet_(false) {}

  graph::graph(const json& jsonGraph) :
    base(jsonGraph), directed_(true), idIsSet_(false), labelIsSet_(false), strict_(false),
    typeIsSet_(false) {

    idIsSet_ = hydrateAndCheckIfSet(jsonGraph, "id", id_);
    labelIsSet_ = hydrateAndCheckIfSet(jsonGraph, "label", label_);
    typeIsSet_ = hydrateAndCheckIfSet(jsonGraph, "type", type_);

    hydrateAndCheckIfSet(jsonGraph, "directed", directed_);

    // Process JSON nodes.
    for (auto& jsonNode : jsonGraph["nodes"].items()) {
      const auto nodeKey = jsonNode.key();
      const auto jsonNodeData = jsonNode.value();

      addNode(nodeKey, jsonNodeData);
    }

    // Process JSON edges.
    for (const auto& jsonEdge : jsonGraph["edges"]) {
      addEdge(jsonEdge);
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
    return *edges_.at(index).get();
  }

  edgeList::const_iterator graph::getEdgeBeginIt() const {
    return edges_.begin();
  }

  unsigned graph::getEdgeCount() const {
    return edges_.size();
  }

  edgeList::const_iterator graph::getEdgeEndIt() const {
    return edges_.end();
  }

  lookupMap<graphNode> graph::getEndNodeMap() const {
    return getNodeMapValues(startNodes_);
  }

  /**
   * For a directed graph, get all the nodes that have no edges leading out of them.
   *
   * @throws an exception if this is an undirected graph.
   * @returns a list of the end nodes.
   */
  nodeValList graph::getEndNodes() const {
    if (!directed_) {
      throw new cjgException("Undirected graphs have no notion of end nodes.");
    }
    return getNodePtrMapValues(endNodes_);
  }

  std::string graph::getId() const {
    return id_;
  }

  std::string graph::getLabel() const {
    return label_;
  }

  lookupMap<graphNode> graph::getStartNodeMap() const {
    return getNodeMapValues(startNodes_);
  }

  /**
   * For a directed graph, get all the nodes that have no edges leading into them.
   *
   * @throws an exception if this is an undirected graph.
   * @returns a list of the start nodes.
   */
  nodeValList graph::getStartNodes() const {
    if (!directed_) {
      throw new cjgException("Undirected graphs have no notion of start nodes.");
    }
    return getNodePtrMapValues(startNodes_);
  }

  std::string graph::getType() const {
    return type_;
  }

  /**
   * Transform a map that uses pointers as its values into a map that uses the dereferenced values instead
   *
   * @param sourceMap - A string key to node smart pointer map.
   * @returns a map with dereferenced values.
   */
  lookupMap<graphNode> graph::getNodeMapValues(const nodeMap& sourceMap) const {
    lookupMap<graphNode> desiredMap;
    for (const auto& entry : sourceMap) {
      const auto node = entry.second;
      desiredMap[entry.first] = *node.get();
    }
    return desiredMap;
  }

  /**
   * Return all the values (by value) from a node pointer map.
   *
   * @param sourceMap - A string key to node smart pointer map.
   * @returns a list of the map's values.
   */
  nodeValList graph::getNodePtrMapValues(const nodeMap& sourceMap) const {
    // TODO: Figure out what's wrong with base's getPtrMapValues.
    // return getPtrMapValues(sourceMap);

    nodeValList desiredNodes;
    for (const auto& nodeEntry : sourceMap) {
      const auto nodePtr = nodeEntry.second.get();
      desiredNodes.push_back(*nodePtr);
    }
    return desiredNodes;
  }

  bool graph::getIdIsSet() const {
    return idIsSet_;
  }

  bool graph::getLabelIsSet() const {
    return labelIsSet_;
  }

  /**
   * Retrieve a copy of the graph node by its associated key.
   * @param key
   */
  graphNode graph::getNodeAt(std::string key) const {
    if (hasNode(key)) {
      throw cjgException("Requested key does not match any node.");
    }
    return *nodes_.at(key).get();
  }

  nodeMap::const_iterator graph::getNodeBeginIt() const {
    return nodes_.begin();
  }

  nodeMap::const_iterator graph::getNodeEndIt() const {
    return nodes_.end();
  }

  bool graph::getTypeIsSet() const {
    return typeIsSet_;
  }

  bool graph::hasNode(std::string key) const {
    auto it = nodes_.find(key);
    return it != nodes_.end();
  }

  /* Mutators */

  void graph::addEdge(const graphEdge& edge) {
    const auto sourceKey = edge.getSource();
    const auto targetKey = edge.getTarget();

    const auto sourceNodeEntry = nodes_.find(sourceKey);
    const auto targetNodeEntry = nodes_.find(targetKey);

    const auto sourceExists = sourceNodeEntry != nodes_.end();
    const auto targetExists = targetNodeEntry != nodes_.end();
    const auto isEdgeDirected = edge.getDirected();

    // Enforce strict mode.
    if (strict_) {
      if (!sourceExists || !targetExists) {
        throwStrictModeViolation("Can't insert edge without nodes being present in graph.");
      }
      if (directed_ && !isEdgeDirected) {
        throwStrictModeViolation("Can't have undirected edge in directed graph.");
      }
      if (!directed_ && isEdgeDirected) {
        throwStrictModeViolation("Can't have directed edge in undirected graph.");
      }
    }

    // Add the edge to the graph.
    const auto edgePtr = std::make_shared<graphEdge>(edge);
    edges_.push_back(edgePtr);

    // Now some bookkeeping.
    // In strict mode, we assume that the nodes specified by the edge are already in the graph. Out
    // of strict mode, you can introduce an 'undisciplined' edge with one or more elements that
    // don't exist. However, you need both nodes to link them.
    if (strict_ || (sourceExists && targetExists)) {
      const auto& targetNodePtr = targetNodeEntry->second;
      const auto& sourceNodePtr = sourceNodeEntry->second;

      createNodeLink(sourceKey, sourceNodePtr, targetKey, targetNodePtr);

      // Undirected is synonymous with bi-directional in terms of traversability.
      if (!isEdgeDirected) {
        createNodeLink(targetKey, targetNodePtr, sourceKey, sourceNodePtr);
      }
    }
  }

  void graph::addNode(const std::string& key, const graphNode& node) {
    if (hasNode(key)) {
      throw new cjgException("Can't add node; key already has value.");
    }
    const auto nodePtr = std::make_shared<graphNode>(node);
    nodes_[key] = nodePtr;

    if (strict_) {
      // In strict mode new nodes aren't involved in any edges yet. They are both start and end nodes.
      startNodes_[key] = nodePtr;
      endNodes_[key] = nodePtr;

      // In strict mode there are only to/from records when a node has been added.
      fromNodesMap_.emplace(key, keyMap());
      toNodesMap_.emplace(key, keyMap());
    } else {
      // Without strict mode, the current edges need to be examined to determine if node is
      // start/end node.
      const auto fromNodeEntries = fromNodesMap_.find(key);
      const auto toNodeEntries = toNodesMap_.find(key);

      auto addToEndNodes = true;
      auto addToStartNodes = true;

      if (fromNodeEntries == fromNodesMap_.end()) {
        fromNodesMap_.emplace(key, keyMap());

      } else if (fromNodeEntries->second.size() > 0) {
        for (const auto& destNodeEntry : fromNodeEntries->second) {
          const auto& destNodeKey = destNodeEntry.first;

          // Link the destination node if it exists.
          const auto destNodeIt = nodes_.find(destNodeKey);
          if (destNodeIt != nodes_.end()) {
            nodePtr->addTraversableNeighbor(destNodeKey, destNodeIt->second);

            // If a destination node is found for this node, then it can't be an end node.
            addToEndNodes = false;
          }
        }
      }

      // There's no 'to node' entry in the map. Create it and make this node a start node.
      if (toNodeEntries == toNodesMap_.end()) {
        toNodesMap_.emplace(key, keyMap());

      } else if (toNodeEntries->second.size() > 0) {
        for (const auto& srcNodeEntry : toNodeEntries->second) {
          const auto& srcNodeKey = srcNodeEntry.first;

          // Link the source node if it exists.
          const auto srcNodeIt = nodes_.find(srcNodeKey);
          if (srcNodeIt != nodes_.end()) {
            srcNodeIt->second->addTraversableNeighbor(srcNodeKey, nodePtr);

            // If a source node is found for this node, then it can't be an start node.
            addToStartNodes = false;
          }
        }
      }

      // Add this new node to start/end nodes if it is applicable.
      if (addToEndNodes) {
        endNodes_.emplace(key, nodePtr);
      }
      if (addToStartNodes) {
        startNodes_.emplace(key, nodePtr);
      }
    }
  }

  void graph::clearEdges() {
    edges_.clear();
    fromNodesMap_.clear();
    toNodesMap_.clear();

    // Clear travel links for all nodes.
    for (const auto& entry : nodes_) {
      const auto node = entry.second.get();
      node->clearTraversableNeighbors();
    }
  }

  void graph::clearNodes() {
    // Strict mode requires that both source/target nodes exist for all edges.
    if (strict_ && edges_.size() > 0) {
      throwStrictModeViolation("Can't clear all nodes when edges exist.");
    }
    nodes_.clear();
  }

  void graph::createNodeLink(std::string sourceKey, nodePtr source, std::string targetKey, nodePtr target) {
    // Link the two nodes together for ease of travel.
    source->addTraversableNeighbor(targetKey, target);

    const auto toNodeEntryIt = toNodesMap_.find(targetKey);
    const auto fromNodeEntryIt = fromNodesMap_.find(sourceKey);

    // Assert that records for the to/from node maps already exist as container.
    if (toNodeEntryIt == toNodesMap_.end()) {
      const auto reason = "Entry for node '" + targetKey + "' not present in the toNodesMap_.";
      throw cjgException(reason);
    }
    if (fromNodeEntryIt == fromNodesMap_.end()) {
      const auto reason = "Entry for node '" + sourceKey + "' not present in the fromNodesMap_.";
      throw cjgException(reason);
    }

    const auto fromNodeEntries = fromNodeEntryIt->second;
    const auto toNodeEntries = toNodeEntryIt->second;

    // Add entries to the to/from node maps if one doesn't exist already.
    if (fromNodeEntries.find(targetKey) == fromNodeEntries.end()) {
      fromNodesMap_.at(sourceKey).emplace(targetKey, nullptr);
    }
    if (toNodeEntries.find(sourceKey) == toNodeEntries.end()) {
      fromNodesMap_.at(targetKey).emplace(sourceKey, nullptr);
    }

    // Remove the target node from the list of start nodes if present.
    if (startNodes_.find(targetKey) != startNodes_.end()) {
      startNodes_.erase(targetKey);
    }

    // Remove the source node from the list of end nodes if present.
    if (endNodes_.find(sourceKey) != endNodes_.end()) {
      endNodes_.erase(sourceKey);
    }
  }

  void graph::removeEdgeAt(unsigned index) {
    if (getEdgeCount() <= index) {
      throw cjgException("Requested edge index is out of range.");
    }
    const auto edge = edges_[index];
    const auto sourceKey = edge->getSource();
    const auto targetKey = edge->getTarget();

    if (strict_) {
      nodes_[sourceKey]->removeTraversableNeighbor(targetKey);
    } else {
      const auto sourceNodeEntry = nodes_.find(sourceKey);
      const auto targetNodeEntry = nodes_.find(targetKey);

      // If both nodes are present in the graph, break the links between them.
      if (sourceNodeEntry != nodes_.end() && targetNodeEntry != nodes_.end()) {
        targetNodeEntry->second->removeTraversableNeighbor(sourceKey);
        sourceNodeEntry->second->removeTraversableNeighbor(targetKey);
      }
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
    for (auto i = start; i < end; i++) {
      removeEdgeAt(i);
    }
  }

  void graph::removeNode(std::string& key) {
    auto it = nodes_.find(key);
    if (it == nodes_.end()) {
      throw cjgException("Graph does not contain requested key.");
    }

    // Corresponding to/from map records.
    const auto& fromEntry = fromNodesMap_.find(key);
    const auto& toEntry = toNodesMap_.find(key);
    const auto& fromList = fromEntry->second;
    const auto& toList = toEntry->second;

    // Nodes involved in edges can't be deleted in strict mode.
    if (strict_ && (fromList.size() > 0 || toList.size() > 0)) {
      throwStrictModeViolation("Can't delete a node that is sourced/targeted by an edge.");
    }

    // Remove all traversable links to this node.
    for (auto fromNodeEntry : toList) {
      const auto& fromKey = fromNodeEntry.first;
      const auto fromNode = nodes_[key];
      fromNode->removeTraversableNeighbor(key);
    }

    // Remove the node and corresponding records in the to/from maps.
    nodes_.erase(it);
    fromNodesMap_.erase(fromEntry);
    toNodesMap_.erase(toEntry);
  }

  void graph::setDirected(bool directed) {
    directed_ = directed;
  }

  void graph::setId(std::string& id) {
    id_ = id;
    idIsSet_ = true;
  }

  void graph::setLabel(std::string& label) {
    label_ = label;
    labelIsSet_ = true;
  }

  void graph::setType(std::string& type) {
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

  /**
   * Throw an expection labeled as a violation of strict mode.
   * @param reason - Why is this a violation of strict mode.
   */
  void graph::throwStrictModeViolation(const std::string& reason) const {
    if (!strict_) {
      throw cjgException("Can't throw a strict mode violation when not in strict mode.");
    }
    const auto msg = "Strict mode violation: " + reason;
    throw cjgException(msg);
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
    for (const auto& [key, nodePtr] : nodes_) {
      const auto node = *nodePtr.get();
      nodesJson[key] = node.toJson();
    }
    graphJson["nodes"] = nodesJson;

    // Get the JSON objects for the edges.
    auto edgesJson = json::array();
    for (const auto& edgePtr : edges_) {
      const auto edge = *edgePtr.get();
      edgesJson.push_back(edge.toJson());
    }
    graphJson["edges"] = edgesJson;

    return graphJson;
  }
}
