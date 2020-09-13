#ifndef NALLJ_CJG_GRAPH_NODE
#define NALLJ_CJG_GRAPH_NODE

// #include <deque>
#include <memory> // unique_ptr
#include <unordered_map>
//#include <vector>

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
    //std::unordered_map<std::string, std::string> metadata_;

    bool labelIsSet_;
    //bool metadataIsSet_;

  public:
    graphNode(const json& jsonNode);
    graphNode();
    // graphNode(std::string node_id, unsigned task_type_id);

    std::string getLabel() const;
    bool getLabelIsSet() const;
  
    void setLabel(std::string label);
    // void setMetadata(std::unordered_map<std::string, std::string> metadata);

    // TODO: Figure out why utility.hpp doesn't work.
    template <typename T>
    bool hydrateAndCheckIfSet(const json& jsonNode, const char* itemKey, T& variable);
    // TODO: Place in utility.hpp when ready.
    bool hydrateMetadataAndCheckIfSet(const json& jsonNode);
    json toJson() const;
  };
}

#endif
