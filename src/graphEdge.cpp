#include <cppJsonGraph/graphEdge.hpp>

namespace nallj {
  graphEdge::graphEdge(const json& jsonGraphEdge) :
    base(jsonGraphEdge), idIsSet_(false), labelIsSet_(false), relationIsSet_(false) {
    std::cout << "graphEdge(jsonGraphEdge)" << jsonGraphEdge;
  }

  graphEdge::graphEdge(std::string source, std::string target) :
    source_(source), target_(target), idIsSet_(false), labelIsSet_(false), relationIsSet_(false) {
    std::cout << "I am graph edge\n";
  }

  void graphEdge::setId(std::string id) {
    id_ = id;
  }

  void graphEdge::setLabel(std::string label) {
    label_ = label;
  }

  void graphEdge::setRelation(std::string relation) {
    relation_ = relation;
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
}
