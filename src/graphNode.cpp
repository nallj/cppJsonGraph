#include <cppJsonGraph/graphNode.hpp>

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
    labelIsSet_(false) { }

  std::string graphNode::getLabel() const {
    return label_;
  }

  bool graphNode::getLabelIsSet() const {
    return labelIsSet_;
  }

  void graphNode::setLabel(std::string label) {
    label_ = label;
    labelIsSet_ = true;
  }

  void graphNode::unsetLabel() {
    label_ = "";
    labelIsSet_ = false;
  }

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

  json graphNode::toJson() const {
    json nodeJson = json::object();
    
    if (labelIsSet_) {
      nodeJson["label"] = label_;
    }

    const auto metadataJson = getMetadataJson();
    if (!metadataJson.is_null()) {
      nodeJson["metadata"] = metadataJson;
    }

    return nodeJson;
  }
}
