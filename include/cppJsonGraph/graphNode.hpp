#ifndef NALLJ_CJG_GRAPH_NODE
#define NALLJ_CJG_GRAPH_NODE

#include <unordered_map>

// Remove later.
#include <iostream>

#include <nlohmann/json.hpp>

#include "base.hpp"

using json = nlohmann::json;

/*
"nodes": {
  "type": "object",
  "additionalProperties": {
    "type": "object",
    "properties": {
      "label": {
        "type": "string"
      },
      "metadata": {
        "type": "object"
      }
    },
    "additionalProperties": false
  }
},
*/

namespace nallj {
  class graphNode : public base {
    // Unrequired items.
    std::string label_;

    bool labelIsSet_;

  public:
    graphNode(const json& jsonNode);
    graphNode();
    // graphNode(std::string node_id, unsigned task_type_id);

    // Accessors
    std::string getLabel() const;
    bool getLabelIsSet() const;
  
    // Mutators
    void setLabel(std::string label);
    void unsetLabel();

    // TODO: Figure out why utility.hpp doesn't work.
    template <typename T>
    bool hydrateAndCheckIfSet(const json& jsonNode, const char* itemKey, T& variable);
    // TODO: Place in utility.hpp when ready.
    bool hydrateMetadataAndCheckIfSet(const json& jsonNode);
    json toJson() const;
  };
}

#endif
