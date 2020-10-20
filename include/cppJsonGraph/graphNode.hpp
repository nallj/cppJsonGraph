#ifndef NALLJ_CJG_GRAPH_NODE
#define NALLJ_CJG_GRAPH_NODE

#include <unordered_map>

// Remove later.
#include <iostream>

#include <nlohmann/json.hpp>

#include "base.hpp"
#include "graph.hpp"

using json = nlohmann::json;

namespace nallj {
  // Needed forward declaration.
  class graphNode;

  using nodePtr = std::shared_ptr<graphNode>;
  template<class T>
  using lookupMap = std::unordered_map<std::string, T>;
  using nodeMap = lookupMap<nodePtr>;
  using nodeValList = std::vector<graphNode>;

  class graphNode : public base {
    // Unrequired items
    std::string label_;

    // Internal
    bool labelIsSet_;
    nodeMap traversableNeighbors_; // TODO: Change to a 'destination node key' to edge map.

  public:
    graphNode();
    graphNode(const graphNode& node);
    graphNode(const json& jsonNode);

    // Accessors
    std::string getLabel() const;
    bool getLabelIsSet() const;
    lookupMap<graphNode> getTraversableNeighborMap() const;
    nodeValList getTraversableNeighbors() const;
    bool hasTraversableNeighbor(std::string key) const;
  
    // Mutators
    void addTraversableNeighbor(std::string key, nodePtr node);
    void clearTraversableNeighbors();
    void removeTraversableNeighbor(std::string key);
    void setLabel(std::string label);
    void unsetLabel();

    // Methods
    // TODO: Figure out why utility.hpp doesn't work.
    template <typename T>
    bool hydrateAndCheckIfSet(const json& jsonNode, const char* itemKey, T& variable);
    // TODO: Place in utility.hpp when ready.
    bool hydrateMetadataAndCheckIfSet(const json& jsonNode);
    json toJson() const;
  };
}

#endif
