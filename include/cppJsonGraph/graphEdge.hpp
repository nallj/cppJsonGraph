#ifndef NALLJ_CJG_GRAPH_EDGE
#define NALLJ_CJG_GRAPH_EDGE

#include <unordered_map> // unordered_map
#include <string> // string

// Remove later.
#include <iostream> // cout
#include <tuple>

#include <nlohmann/json.hpp>

#include "base.hpp"
#include "cjgException.hpp"
#include "graph.hpp"

using json = nlohmann::json;

namespace nallj {
  class graphEdge : public base {
    enum paramType {
      DIRECTED, ID, LABEL, RELATION, SOURCE, TARGET
    };

    // Required items
    std::string source_;
    std::string target_;

    // Defaulted items
    bool directed_; // Defaults to true.

    // Unrequired items
    std::string id_;
    std::string label_;
    std::string relation_;

    bool idIsSet_;
    bool labelIsSet_;
    bool relationIsSet_;

    std::tuple<bool, std::string, std::string> getOptParamByType(paramType type) const;

  public:
    graphEdge();
    graphEdge(const graphEdge& edge);
    graphEdge(const json& jsonEdge);
    graphEdge(std::string source, std::string target);

    // Accessors
    bool getDirected() const;
    std::string getId() const;
    bool getIdIsSet() const;
    std::string getLabel() const;
    bool getLabelIsSet() const;
    std::string getRelation() const;
    bool getRelationIsSet() const;
    std::string getSource() const;
    std::string getTarget() const;

    // Mutators
    void setDirected(bool directed);
    void setId(std::string id);
    void setLabel(std::string label);
    void setRelation(std::string relation);
    void setSource(std::string source);
    void setTarget(std::string target);
    void unsetId();
    void unsetLabel();
    void unsetRelation();

    // Methods
    void addScalarToGraphJsonIfSet(json& edgeJson, paramType paramType) const;
    // TODO: Figure out why utility.hpp doesn't work.
    template <typename T>
    bool hydrateAndCheckIfSet(const json& jsonEdge, const char* itemKey, T& variable);
    template <typename T>
    void hydrateScalar(const json& jsonEdge, const char* itemKey, T& variable);
    json toJson() const;
  };
}

#endif
