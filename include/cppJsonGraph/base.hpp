#ifndef NALLJ_CJG_BASE
#define NALLJ_CJG_BASE

// #include <deque>
#include <map> // unordered_map
#include <memory> // shared_ptr
#include <vector> // vector

// Get rid of later.
#include <iostream> // cout
#include <iomanip> // setw

#include <nlohmann/json.hpp>
// #include <nlohmann/json-schema.hpp>

#include "cjgException.hpp"
#include "utility.hpp"

using json = nlohmann::json;
namespace nallj {
  class base {
    // Unrequired items.
    std::unordered_map<std::string, std::string> metadata_;

    bool metadataIsSet_;

    void hydrateMetadata(const json& jsonGraph);

  protected:
    base();
    base(const base& node);
    base(const json&);
    // FIXME: Including graphEdge.hpp causes a circular reference that causes base to not be
    // identified as a class.
    // base(std::unordered_map<std::string, graphNode>, std::vector<graphEdge>);
    // TODO: Figure out the undefined reference.
    // template <typename T>
    // bool hydrateAndCheckIfSet2(const json& jsonGraph, const char* itemKey, T& variable);
    // FIXME: More undefined symbols. :/
    // template <typename T, typename TValue>
    // std::vector<TValue> getPtrMapValues(const std::unordered_map<T, std::shared_ptr<TValue>>& sourceMap) const;

  public:
    // Accessors
    std::unordered_map<std::string, std::string> getMetadata() const;
    bool getMetadataIsSet() const;
    json getMetadataJson() const;
    bool hasMetadata(std::string key) const;

    // Mutators
    void addMetadata(std::string key, std::string value);
    void clearMetadata();
    void setMetadata(std::unordered_map<std::string, std::string> metadata);
    void unsetMetadata();
  };
}

#endif
