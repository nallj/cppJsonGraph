#ifndef NALLJ_CJG_GRAPH_EDGE
#define NALLJ_CJG_GRAPH_EDGE

#include <unordered_map> // unordered_map
#include <string> // string

// Remove later.
#include <iostream> // cout
#include <memory> // make_shared, shared_ptr

#include <nlohmann/json.hpp>

#include "base.hpp"
#include "informedException.hpp"

//class base;

/*
"edges": {
    "type": [
    "array"
    ],
    "items": {
    "type": "object",
    "additionalProperties": false,
    "properties": {
        "id": {
        "type": "string"
        },
        "source": {
        "type": "string"
        },
        "target": {
        "type": "string"
        },
        "relation": {
        "type": "string"
        },
        "directed": {
        "type": [
            "boolean"
        ],
        "default": true
        },
        "label": {
        "type": "string"
        },
        "metadata": {
        "type": [
            "object"
        ]
        }
    },
    "required": [
        "source",
        "target"
    ]
    }
}
*/

using json = nlohmann::json;

namespace nallj {
  // enum graphEdgeParamType {
  //   DIRECTED, ID, LABEL, RELATION, SOURCE, TARGET
  // };

  class graphEdge : public base {
    enum paramType {
      DIRECTED, ID, LABEL, RELATION, SOURCE, TARGET
    };

    std::unordered_map<paramType, std::shared_ptr<bool>> paramToIsSetPtrMap;
    std::unordered_map<paramType, std::shared_ptr<std::string>> paramToValPtrMap;
    std::unordered_map<paramType, std::string> paramToKeyMap;
    
    // std::unordered_map<graphEdgeParamType, std::shared_ptr<bool>> paramToIsSetPtrMap;
    // std::unordered_map<graphEdgeParamType, std::shared_ptr<std::string>> paramToValPtrMap;
    // std::unordered_map<graphEdgeParamType, std::string> paramToKeyMap;

    // Required items.
    std::string source_;
    std::string target_;

    // Defaulted items.
    bool directed_; // Defaults to true.

    // Unrequired items.
    std::string id_;
    std::string label_;
    // std::unordered_map<std::string, std::string> metadata_;
    std::string relation_;

    bool idIsSet_;
    bool labelIsSet_;
    // bool metadataIsSet_;
    bool relationIsSet_;

  public:
    graphEdge();
    graphEdge(const json& jsonEdge);
    graphEdge(std::string source, std::string target);

    // Accessors
    std::string getId() const;
    bool getIdIsSet() const;
    std::string getLabel() const;
    bool getLabelIsSet() const;
    std::string getRelation() const;
    bool getRelationIsSet() const;
    std::string getSource() const;
    std::string getTarget() const;

    // Mutators
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
    void hydratePointerMaps();
    template <typename T>
    void hydrateScalar(const json& jsonEdge, const char* itemKey, T& variable);
    // TODO: Place in utility.hpp when ready.
    // bool hydrateMetadataAndCheckIfSet(const json& jsonEdge);
    json toJson() const;
  };
}

#endif
