#include "graphNode.hpp"

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
  graphNode::graphNode(const json& jsonNode) : 
    base(jsonNode), labelIsSet_(false) {
    
    labelIsSet_ = hydrateAndCheckIfSet(jsonNode, "label", label_);
  }

  graphNode::graphNode() : 
    labelIsSet_(false) {
    std::cout << "\nI am graph node\n";
  }

  void graphNode::setLabel(std::string label) {
    label_ = label;
  }

  // void graphNode::setMetadata(std::unordered_map<std::string, std::string> metadata) {
  //   metadata_ = metadata;
  // }

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
}
