#include <cppJsonGraph/graphEdge.hpp>

namespace nallj {
  graphEdge::graphEdge() :
    directed_(true), idIsSet_(false), labelIsSet_(false), relationIsSet_(false) {}

  graphEdge::graphEdge(const graphEdge& edge) :
    directed_(edge.directed_), id_(edge.id_), idIsSet_(edge.idIsSet_), label_(edge.label_),
    labelIsSet_(edge.labelIsSet_), relation_(edge.relation_), relationIsSet_(edge.relationIsSet_),
    source_(edge.source_), target_(edge.target_) {}

  graphEdge::graphEdge(const json& jsonEdge) :
    base(jsonEdge), directed_(true), idIsSet_(false), labelIsSet_(false), relationIsSet_(false) {

    // Get required paramters.
    hydrateScalar(jsonEdge, "source", source_);
    hydrateScalar(jsonEdge, "target", target_);

    // Get optional parameters.
    idIsSet_ = hydrateAndCheckIfSet(jsonEdge, "id", id_);
    labelIsSet_ = hydrateAndCheckIfSet(jsonEdge, "label", label_);
    relationIsSet_ = hydrateAndCheckIfSet(jsonEdge, "relation", relation_);

    // Get optional parameter with default value.
    hydrateAndCheckIfSet(jsonEdge, "directed", directed_);
  }

  graphEdge::graphEdge(std::string source, std::string target) :
    idIsSet_(false), labelIsSet_(false), relationIsSet_(false), source_(source), target_(target) {}

  /* Accessors */

  bool graphEdge::getDirected() const {
    return directed_;
  }

  std::string graphEdge::getId() const {
    return id_;
  }

  bool graphEdge::getIdIsSet() const {
    return idIsSet_;
  }

  std::string graphEdge::getLabel() const {
    return label_;
  }

  bool graphEdge::getLabelIsSet() const {
    return labelIsSet_;
  }

  std::string graphEdge::getRelation() const {
    return relation_;
  }

  bool graphEdge::getRelationIsSet() const {
    return relationIsSet_;
  }

  std::string graphEdge::getSource() const {
    return source_;
  }

  std::string graphEdge::getTarget() const {
    return target_;
  }

  /* Mutators */

  void graphEdge::setDirected(bool directed) {
    directed_ = directed;
  }

  void graphEdge::setId(std::string id) {
    id_ = id;
    idIsSet_ = true;
  }

  void graphEdge::setLabel(std::string label) {
    label_ = label;
    labelIsSet_ = true;
  }

  void graphEdge::setRelation(std::string relation) {
    relation_ = relation;
    relationIsSet_ = true;
  }

  void graphEdge::setSource(std::string source) {
    source_ = source;
  }

  void graphEdge::setTarget(std::string target) {
    target_ = target;
  }

  void graphEdge::unsetId() {
    id_ = "";
    idIsSet_ = false;
  }

  void graphEdge::unsetLabel() {
    label_ = "";
    labelIsSet_ = false;
  }

  void graphEdge::unsetRelation() {
    relation_ = "";
    relationIsSet_ = false;
  }

  /* Methods */

  void graphEdge::addScalarToGraphJsonIfSet(json& graphJson, paramType paramType) const {
    auto varTuple = getOptParamByType(paramType);
    auto [varIsSet, varJsonKey, varVal] = varTuple;
    if (varIsSet) {
      graphJson[varJsonKey] = varVal;
    }
  }

  std::tuple<bool, std::string, std::string> graphEdge::getOptParamByType(paramType type) const {
    switch (type) {
      case paramType::ID:
        return { idIsSet_, "id", id_ };
      case paramType::LABEL:
        return { labelIsSet_, "label", label_ };
      case paramType::RELATION:
        return { relationIsSet_, "relation", relation_ };
      default:
        throw cjgException("Invalid param type requested.");
    }
  }

  template <typename T>
  bool graphEdge::hydrateAndCheckIfSet(const json& jsonEdge, const char* itemKey, T& variable) {
    if (jsonEdge.count(itemKey) == 1) {
      auto item = jsonEdge[itemKey];
      auto value = item.get<T>();
      variable = value;
      return true;
    }
    return false;
  }

  template <typename T>
  void graphEdge::hydrateScalar(const json& jsonEdge, const char* itemKey, T& variable) {
    if (jsonEdge.count(itemKey) != 1) {
      std::string message =
        std::string("JSON object supplied missing required parameter \"") + itemKey + std::string("\".");
      throw cjgException(message);
    }
    auto item = jsonEdge[itemKey];
    auto value = item.get<T>();
    variable = value;
  }

  json graphEdge::toJson() const {
    // Create edge with all required parameters.
    json edgeJson = {
      { "directed", directed_ },
      { "source", source_ },
      { "target", target_ }
    };

    // Add optional parameters if set.
    addScalarToGraphJsonIfSet(edgeJson, paramType::ID);
    addScalarToGraphJsonIfSet(edgeJson, paramType::LABEL);
    addScalarToGraphJsonIfSet(edgeJson, paramType::RELATION);

    if (getMetadataIsSet()) {
      edgeJson["metadata"] = getMetadataJson();
    }

    return edgeJson;
  }
}
