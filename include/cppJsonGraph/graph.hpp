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

using json = nlohmann::json;

namespace nallj {
  class graph : public base {
    enum paramType {
      ID, LABEL, TYPE, DIRECTED
    };

    // Required items.
    std::unordered_map<std::string, graphNode> nodes_;
    std::vector<graphEdge> edges_;

    // Defaulted items.
    bool directed_; // Defaults to true.

    // Unrequired items.
    std::string id_;
    std::string label_;
    std::string type_;

    bool idIsSet_;
    bool labelIsSet_;
    bool typeIsSet_;

    void addScalarToGraphJsonIfSet(json& graphJson, paramType paramType) const;
    std::tuple<bool, std::string, std::string> getOptParamByType(paramType type) const;
    // TODO: Figure out the undefined reference when using `base`.
    template <typename T>
    bool hydrateAndCheckIfSet(const json& jsonGraph, const char* itemKey, T& variable);

  public:
    graph();
    graph(const json& jsonGraph);
    graph(std::unordered_map<std::string, graphNode> nodes_, std::vector<graphEdge> edges_);

    // Accessors
    bool getDirected() const;
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
    void setDirected(bool directed);
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
