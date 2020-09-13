#include <cppJsonGraph/graphEdge.hpp>

namespace nallj {
  graphEdge::graphEdge() :
    directed_(true), idIsSet_(false), labelIsSet_(false), relationIsSet_(false) {

    hydratePointerMaps();
  }

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

    hydratePointerMaps();
  }

  graphEdge::graphEdge(std::string source, std::string target) :
    source_(source), target_(target), idIsSet_(false), labelIsSet_(false), relationIsSet_(false) {

    hydratePointerMaps();
  }

  /* Accessors */

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
    auto lol = *paramToIsSetPtrMap.at(paramType).get();
    std::cout << "  Checking isSet: " << (lol ? "SET" : "UNSET");
    if (*paramToIsSetPtrMap.at(paramType).get()) {
      auto graphParamKey = paramToKeyMap.at(paramType);
      std::cout << "  Value is\"" << *paramToValPtrMap.at(paramType).get() << "\"";
      graphJson[graphParamKey] = *paramToValPtrMap.at(paramType).get();
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
      throw informedException(message);
    }
    auto item = jsonEdge[itemKey];
    auto value = item.get<T>();
    variable = value;
  }

  void graphEdge::hydratePointerMaps() {
    auto idPtr = std::make_shared<std::string>(id_);
    auto labelPtr = std::make_shared<std::string>(label_);
    auto relationPtr = std::make_shared<std::string>(relation_);

    paramToValPtrMap.emplace(paramType::ID, idPtr);
    paramToValPtrMap.emplace(paramType::LABEL, labelPtr);
    paramToValPtrMap.emplace(paramType::RELATION, relationPtr);

    auto idIsSetPtr = std::make_shared<bool>(idIsSet_);
    auto labelIsSetPtr = std::make_shared<bool>(labelIsSet_);
    auto relationIsSetPtr = std::make_shared<bool>(relationIsSet_);

    paramToIsSetPtrMap.emplace(paramType::ID, idIsSetPtr);
    paramToIsSetPtrMap.emplace(paramType::LABEL, labelIsSetPtr);
    paramToIsSetPtrMap.emplace(paramType::RELATION, relationIsSetPtr);

    paramToKeyMap = {
      { paramType::ID, "id" },
      { paramType::LABEL, "label" },
      { paramType::RELATION, "relation" }
    };
  }

  json graphEdge::toJson() const {
    // Create edge with all required parameters.
    json edgeJson = {
      { "directed", directed_ },
      { "source", source_ },
      { "target", target_ }
    };

    std::cout << "this edge is {" << idIsSet_ << "," << labelIsSet_ << ","
              << relationIsSet_ << "}\n";

    // Add optional parameters if set.
    std::cout << "Adding ID if set:\n";
    addScalarToGraphJsonIfSet(edgeJson, paramType::ID);
    std::cout << "Adding LABEL if set:\n";
    addScalarToGraphJsonIfSet(edgeJson, paramType::LABEL);
    std::cout << "Adding RELATION if set:\n";
    addScalarToGraphJsonIfSet(edgeJson, paramType::RELATION);

    if (getMetadataIsSet()) {
      edgeJson["metadata"] = getMetadataJson();
    }

    std::cout << "Created JSON:\n" << edgeJson;
    return edgeJson;
  }
}
