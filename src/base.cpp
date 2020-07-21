#include "base.hpp"

namespace nallj {
  base::base() :
    metadataIsSet_(false) { std::cout << "\n I AM THE REGULAR BASE CTOR! \n"; }

  base::base(const json& jsonObj) {
    std::cout << "\n I AM THE BASE! \n";
    hydrateMetadata(jsonObj);
  }

  // base::base(std::unordered_map<std::string, graphNode>, std::vector<graphEdge>) :
  //   metadataIsSet_(false) { }

  template <typename T>
  bool base::hydrateAndCheckIfSet2(const json& jsonGraph, const char* itemKey, T& variable) {
    if (jsonGraph.count(itemKey) == 1) {
      auto item = jsonGraph[itemKey];
      auto value = item.get<T>();
      variable = value;
      return true;
    }
    return false;
  }

  void base::hydrateMetadata(const json& jsonObj) {
    const auto metadataKey = "metadata";

    // std::cout << "Fn entered " << jsonGraph.count(metadataKey)  << "\n";
    // if (jsonGraph.count(metadataKey) > 0) {
    //   std::cout << "Fn entered " << jsonGraph[metadataKey].is_object()  << "\n";
    // }
    if (jsonObj.count(metadataKey) == 1 && jsonObj[metadataKey].is_object()) {
      // std::cout << "Cond entered\n";
      auto metadata = jsonObj[metadataKey];
      // for (json::iterator it = metadata.begin(); it != metadata.end(); ++it) {
      //   std::cout << "IT: " << it.key() << " : " << it.value() << "\n";
      // }

      // Process JSON nodes.
      for (auto& datum : metadata.items()) {
        // std::cout << "MY JSON DATUM\n" << datum.key() << " :\n";
        // std::cout <<  std::setw(2) << datum.value() << "\n";

        auto datumKey = datum.key();
        auto jsonDatumValue = datum.value();
        // std::cout << "Inserting '" << datumKey << "' with value '" << jsonDatumValue << "'\n";
        metadata_.emplace(datumKey, jsonDatumValue);
      }
      metadataIsSet_ = true;
    }
    metadataIsSet_ = false;
  }

  bool base::getMetadataIsSet() {
    return metadataIsSet_;
  }

  std::unordered_map<std::string, std::string> base::getMetadata() {
    return metadata_;
  }

  void base::setMetadata(std::unordered_map<std::string, std::string> metadata) {
    metadataIsSet_ = true;
    metadata_ = metadata;
  }

}
