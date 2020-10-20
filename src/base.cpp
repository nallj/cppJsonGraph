#include <cppJsonGraph/base.hpp>
namespace nallj {
  base::base() :
    metadataIsSet_(false) {}

  base::base(const base& entity) :
    metadata_(entity.metadata_), metadataIsSet_(entity.metadataIsSet_) {}

  base::base(const json& jsonObj) {
    hydrateMetadata(jsonObj);
  }

  /* Accessors */

  std::unordered_map<std::string, std::string> base::getMetadata() const {
    return metadata_;
  }

  // template <typename T, typename TValue>
  // std::vector<TValue> base::getPtrMapValues(const std::unordered_map<T, std::shared_ptr<TValue>>& sourceMap) const {
  //   std::vector<TValue> values;
  //   for (const auto& entry : sourceMap) {
  //     const auto ptr = entry.second.get();
  //     values.push_back(*ptr);
  //   }
  //   return values;
  // }

  bool base::getMetadataIsSet() const {
    return metadataIsSet_;
  }
  
  json base::getMetadataJson() const {
    if (!metadataIsSet_) {
      throw new cjgException("Can't get metadata JSON; it's not set.");
    }

    json metadataJson = json::object();
    for (const auto [key, value] : metadata_) {
      metadataJson[key] = value;
    }
    return metadataJson;
  }

  bool base::hasMetadata(std::string key) const {
    auto it = metadata_.find(key);
    return it != metadata_.end();
  }

  /* Mutators */

  void base::addMetadata(std::string key, std::string value) {
    if (hasMetadata(key)) {
      throw new cjgException("Can't add metadata; key already has value.");
    }
    metadata_[key] = value;
    metadataIsSet_ = true;
  }

  void base::clearMetadata() {
    metadata_.clear();
  }

  void base::setMetadata(std::unordered_map<std::string, std::string> metadata) {
    metadata_ = metadata;
    metadataIsSet_ = true;
  }

  void base::unsetMetadata() {
    metadata_.clear();
    metadataIsSet_ = false;
  }

  /* Methods */

  // template <typename T>
  // bool base::hydrateAndCheckIfSet2(const json& jsonGraph, const char* itemKey, T& variable) {
  //   if (jsonGraph.count(itemKey) == 1) {
  //     auto item = jsonGraph[itemKey];
  //     auto value = item.get<T>();
  //     variable = value;
  //     return true;
  //   }
  //   return false;
  // }

  void base::hydrateMetadata(const json& jsonObj) {
    const auto metadataKey = "metadata";

    metadataIsSet_ = false;
    if (jsonObj.count(metadataKey) == 1 && jsonObj[metadataKey].is_object()) {
      auto metadata = jsonObj[metadataKey];

      // Process JSON nodes.
      for (auto& datum : metadata.items()) {

        auto datumKey = datum.key();
        auto jsonDatumValue = datum.value();

        metadata_.emplace(datumKey, jsonDatumValue);
      }
      metadataIsSet_ = true;
    }
  }
}
