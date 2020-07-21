#ifndef JG_GRAPH_EDGE_HPP
#define JG_GRAPH_EDGE_HPP

#include <unordered_map> // unordered_map

// Remove later.
#include <iostream> // cout

#include <nlohmann/json.hpp>

#include "base.hpp"

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
  class graphEdge : public base {
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
    graphEdge(const json& jsonGraphEdge);
    graphEdge(std::string source, std::string target);

    // Getters.
    void setId(std::string id);
    void setLabel(std::string label);
    // void setMetadata(std::unordered_map<std::string, std::string> metadata);
    void setRelation(std::string relation);

    // TODO: Figure out why utility.hpp doesn't work.
    template <typename T>
    bool hydrateAndCheckIfSet(const json& jsonEdge, const char* itemKey, T& variable);
    // TODO: Place in utility.hpp when ready.
    // bool hydrateMetadataAndCheckIfSet(const json& jsonEdge);

    // Setters.
    //std::string getId
  };
}

#endif
