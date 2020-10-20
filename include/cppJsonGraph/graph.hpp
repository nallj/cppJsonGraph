#ifndef NALLJ_CJG_GRAPH
#define NALLJ_CJG_GRAPH

#include <memory> // make_shared, shared_ptr
#include <unordered_map> // unordered_map
#include <vector> // vector

// Get rid of later.
#include <iostream> // cout
#include <iomanip> // setw

#include <nlohmann/json.hpp>

#include "base.hpp"
#include "graphEdge.hpp"
#include "graphNode.hpp"
#include "cjgException.hpp"
#include "utility.hpp"

namespace nallj {
  // Needed forward declaration.
  class graphEdge;
  class graphNode;

  using edgePtr = std::shared_ptr<graphEdge>;
  using nodePtr = std::shared_ptr<graphNode>;
  template<class T>
  using lookupMap = std::unordered_map<std::string, T>;

  using edgeList = std::vector<edgePtr>;
  using json = nlohmann::json;
  using keyMap = lookupMap<void*>;
  using nodeList = std::vector<nodePtr>;
  using nodePairList = std::vector<graphNode>;
  using nodeValList = std::vector<graphNode>;
  using nodeKeyMap = lookupMap<keyMap>;
  using nodeMap = lookupMap<nodePtr>;

  class graph : public base {
    enum paramType {
      ID, LABEL, TYPE, DIRECTED
    };

    // Required items
    nodeMap nodes_;
    edgeList edges_;

    // Defaulted items
    bool directed_; // Defaults to true.

    // Unrequired items
    std::string id_;
    std::string label_;
    std::string type_;

    // Internal use
    nodeMap endNodes_;
    // All the nodes coming from node ID, where the first dimension map is keyed with the source
    // node ID and the second dimension map is keyed with the target node ID. Out of strict mode,
    // there may be records for nonexistent nodes.
    nodeKeyMap fromNodesMap_;
    bool idIsSet_;
    bool labelIsSet_;
    nodeMap startNodes_;
    bool strict_; // a.k.a. opinionative mode
    // All nodes going to node ID, where the first dimension map is keyed with the target node ID
    // and the second dimension map is keyed with the source node ID. Out of strict mode, there may
    // be records for nonexistent nodes.
    nodeKeyMap toNodesMap_;
    bool typeIsSet_;

    // Methods
    void addScalarToGraphJsonIfSet(json& graphJson, paramType paramType) const;
    void createNodeLink(std::string sourceKey, nodePtr source, std::string targetKey, nodePtr target);
    // TODO: Upon figuring out what's wrong with base's getPtrMapValues, move this there as well.
    lookupMap<graphNode> getNodeMapValues(const nodeMap& sourceMap) const;
    nodeValList getNodePtrMapValues(const nodeMap& sourceMap) const;
    std::tuple<bool, std::string, std::string> getOptParamByType(paramType type) const;
    // TODO: Figure out the undefined reference when using `base`.
    template <typename T>
    bool hydrateAndCheckIfSet(const json& jsonGraph, const char* itemKey, T& variable);
    void throwStrictModeViolation(const std::string& reason) const;

  public:
    graph();
    graph(const graph& g);
    graph(bool strict);
    graph(const json& jsonGraph);
    graph(nodeMap nodes_, edgeList edges_, bool strict);

    // Accessors
    bool getDirected() const;
    graphEdge getEdgeAt(unsigned index) const;
    edgeList::const_iterator getEdgeBeginIt() const;
    unsigned getEdgeCount() const;
    edgeList::const_iterator getEdgeEndIt() const;
    lookupMap<graphNode> getEndNodeMap() const;
    nodeValList getEndNodes() const;
    std::string getId() const;
    bool getIdIsSet() const;
    std::string getLabel() const;
    bool getLabelIsSet() const;
    graphNode getNodeAt(std::string key) const;
    nodeMap::const_iterator getNodeBeginIt() const;
    nodeMap::const_iterator getNodeEndIt() const;
    lookupMap<graphNode> getStartNodeMap() const;
    nodeValList getStartNodes() const;
    std::string getType() const;
    bool getTypeIsSet() const;
    bool hasNode(std::string key) const;

    // Mutators
    void addEdge(const graphEdge& edge);
    void addNode(const std::string& key, const graphNode& node);
    void clearEdges();
    void clearNodes();
    void removeEdgeAt(unsigned index);
    void removeEdgeRange(unsigned start, unsigned end);
    void removeNode(std::string& key);
    void setDirected(bool directed);
    void setId(std::string& id);
    void setLabel(std::string& label);
    void setType(std::string& type);
    void unsetId();
    void unsetLabel();
    void unsetType();

    // Methods
    json toJson() const;
  };
}

#endif
