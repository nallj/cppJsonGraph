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
#include "informedException.hpp"
#include "utility.hpp"

using json = nlohmann::json;

namespace nallj {
  enum graphParamType {
    ID, LABEL, TYPE, DIRECTED
  };

  class graph : public base {
    std::unordered_map<graphParamType, std::shared_ptr<bool>> graphParamToIsSetPtrMap;
    std::unordered_map<graphParamType, std::shared_ptr<std::string>> graphParamToValPtrMap;
    std::unordered_map<graphParamType, std::string> graphParamToKeyMap;

    // Required items.
    std::unordered_map<std::string, graphNode> nodes_;
    std::vector<graphEdge> edges_;

    // Defaulted items.
    bool directed_; // Defaults to true.

    // Unrequired items.
    std::string id_;
    std::string label_;
    std::string type_;
    // std::unordered_map<std::string, std::string> metadata_;

    bool idIsSet_;
    bool labelIsSet_;
    bool typeIsSet_;
    // bool metadataIsSet_;

    void addScalarToGraphJsonIfSet(json& graphJson, graphParamType paramType) const;
    void hydratePointerMaps();
    // TODO: Figure out the undefined reference when using `base`.
    template <typename T>
    bool hydrateAndCheckIfSet(const json& jsonGraph, const char* itemKey, T& variable);
    // TODO: Place in utility.hpp when ready.
    //bool hydrateMetadataAndCheckIfSet(const json& jsonGraph);

  public:
    graph();
    graph(const json& jsonGraph);
    graph(std::unordered_map<std::string, graphNode> nodes_, std::vector<graphEdge> edges_);

    // Accessors
    graphEdge getEdgeAt(unsigned index) const;
    std::vector<graphEdge>::const_iterator getEdgeBeginIt() const;
    unsigned getEdgeCount() const;
    std::vector<graphEdge>::const_iterator getEdgeEndIt() const;
    std::string getId() const;
    bool getIdIsSet() const;
    std::string getLabel() const;
    bool getLabelIsSet() const;
    std::string getType() const;
    bool getTypeIsSet() const;
    bool hasNode(std::string key) const;

    // Mutators
    void addEdge(graphEdge& edge);
    void addNode(std::string key, graphNode& node);
    void clearEdges();
    void clearNodes();
    void removeEdgeAt(unsigned index);
    void removeEdgeRange(unsigned start, unsigned end);
    void removeNode(std::string key);
    void setId(std::string id);
    void setLabel(std::string label);
    void setType(std::string type);
    void unsetId();
    void unsetLabel();
    void unsetType();

    // Methods
    json toJson() const;
  };
}

#endif
