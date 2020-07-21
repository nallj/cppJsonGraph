#include "utility.hpp"

namespace nallj {
  template <typename T>
  bool jgUtility::hydrateAndCheckIfSet(const json& jsonGraph, const char* itemKey, T& variable) {
    if (jsonGraph.count(itemKey) == 1) {
      auto item = jsonGraph[itemKey];
      auto value = item.get<T>();
      variable = value;
      return true;
    }
    return false;
  }
}
