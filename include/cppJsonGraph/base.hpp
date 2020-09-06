#ifndef JG_BASE_HPP
#define JG_BASE_HPP

// #include <deque>
#include <map> // unordered_map
#include <memory> // unique_ptr
// #include <vector> // vector

// Get rid of later.
#include <iostream> // cout
#include <iomanip> // setw

#include <nlohmann/json.hpp>
// #include <nlohmann/json-schema.hpp>

// #include "graphEdge.hpp"
// #include "graphNode.hpp"

#include "utility.hpp"

using json = nlohmann::json;

// class graph;
// using graphs_t = std::vector<std::shared_ptr<graph>>;

namespace nallj {
  class base {
    // Unrequired items.
    std::unordered_map<std::string, std::string> metadata_;

    bool metadataIsSet_;

    void hydrateMetadata(const json& jsonGraph);

  protected:
    base();
    base(const json&);
    // FIXME: Including graphEdge.hpp causes a circular reference that causes base to not be
    // identified as a class.
    // base(std::unordered_map<std::string, graphNode>, std::vector<graphEdge>);
    // TODO: Figure out the undefined reference.
    template <typename T>
    bool hydrateAndCheckIfSet2(const json& jsonGraph, const char* itemKey, T& variable);

  public:
    bool getMetadataIsSet();
    
    std::unordered_map<std::string, std::string> getMetadata();
    void setMetadata(std::unordered_map<std::string, std::string> metadata);
  };
}

#endif
