#include <cppJsonGraph/graphNode.hpp>

namespace nallj {
  graphNode::graphNode() :
    labelIsSet_(false) {}

  graphNode::graphNode(const graphNode& node) :
    base(node), label_(node.label_), labelIsSet_(node.labelIsSet_) {}

  graphNode::graphNode(const json& jsonNode) : 
    base(jsonNode), labelIsSet_(false) {

    labelIsSet_ = hydrateAndCheckIfSet(jsonNode, "label", label_);
  }

  void graphNode::addTraversableNeighbor(std::string key, nodePtr node) {
    if (hasTraversableNeighbor(key)) {
      throw cjgException("Can't add traversable neighbor. This node is already registered as a neighbor.");
    }
    traversableNeighbors_.emplace(key, node);
  }

  void graphNode::clearTraversableNeighbors() {
    traversableNeighbors_.clear();
  }

  /**
   * @returns all the traversable neighbors as a node map.
   */
  lookupMap<graphNode> graphNode::getTraversableNeighborMap() const {
    lookupMap<graphNode> desiredMap;
    for (const auto& entry : traversableNeighbors_) {
      const auto node = entry.second;
      desiredMap[entry.first] = *node.get();
    }
    return desiredMap;
  }

  /**
   * @returns all the traversable neighbors of this node.
   */
  nodeValList graphNode::getTraversableNeighbors() const {
    // TODO: Figure out what's wrong with base's getPtrMapValues.
    // return getPtrMapValues(traversableNeighbors_);

    nodeValList desiredNodes;
    for (const auto& nodeEntry : traversableNeighbors_) {
      const auto nodePtr = nodeEntry.second.get();
      desiredNodes.push_back(*nodePtr);
    }
    return desiredNodes;
  }

  bool graphNode::hasTraversableNeighbor(std::string key) const {
    return traversableNeighbors_.find(key) != traversableNeighbors_.end();
  }

  template <typename T>
  bool graphNode::hydrateAndCheckIfSet(const json& jsonNode, const char* itemKey, T& variable) {
    if (jsonNode.count(itemKey) == 1) {
      auto item = jsonNode[itemKey];
      auto value = item.get<T>();
      variable = value;
      return true;
    }
    return false;
  }

  std::string graphNode::getLabel() const {
    return label_;
  }

  bool graphNode::getLabelIsSet() const {
    return labelIsSet_;
  }

  void graphNode::removeTraversableNeighbor(std::string key) {
    if (!hasTraversableNeighbor(key)) {
      throw cjgException("Can't remove nonexistent traversable neighbor.");
    }
    traversableNeighbors_.erase(key);
  }

  void graphNode::setLabel(std::string label) {
    label_ = label;
    labelIsSet_ = true;
  }

  json graphNode::toJson() const {
    json nodeJson = json::object();
    
    if (labelIsSet_) {
      nodeJson["label"] = label_;
    }

    const auto metadataJson = getMetadataJson();
    if (!metadataJson.is_null()) {
      nodeJson["metadata"] = metadataJson;
    }

    return nodeJson;
  }

  void graphNode::unsetLabel() {
    label_ = "";
    labelIsSet_ = false;
  }
}
