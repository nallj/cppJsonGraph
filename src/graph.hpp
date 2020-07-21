#ifndef JG_GRAPH_HPP
#define JG_GRAPH_HPP

// #include <deque>
#include <map> // unordered_map
#include <memory> // unique_ptr
// #include <vector> // vector

// Get rid of later.
#include <iostream> // cout
#include <iomanip> // setw

#include <nlohmann/json.hpp>
// #include <nlohmann/json-schema.hpp>

#include "base.hpp"
#include "graphEdge.hpp"
#include "graphNode.hpp"

#include "utility.hpp"

using json = nlohmann::json;

// class graph;
// using graphs_t = std::vector<std::shared_ptr<graph>>;

/*
  "id": {
    "type": "string"
  },
  "label": {
    "type": "string"
  },
  "directed": {
    "type": [
      "boolean"
    ],
    "default": true
  },
  "type": {
    "type": "string"
  },
  "metadata": {
    "type": [
      "object"
    ]
  },
*/

namespace nallj {
  class graph : private base {
    // Required items.
    std::unordered_map<std::string, graphNode> nodes_;
    std::vector<graphEdge> edges_;

    // Defaulted items.
    bool directed_; // Defaults to true.

    // Unrequired items.
    std::string id_;
    std::string label_;
    std::string type_;
    // std::unordered_map<std::string, std::string> metadata_;

    bool idIsSet_;
    bool labelIsSet_;
    bool typeIsSet_;
    // bool metadataIsSet_;

    // TODO: Figure out the undefined reference when using `base`.
    template <typename T>
    bool hydrateAndCheckIfSet(const json& jsonGraph, const char* itemKey, T& variable);
    // TODO: Place in utility.hpp when ready.
    //bool hydrateMetadataAndCheckIfSet(const json& jsonGraph);

  public:
    // graph(); // needed in lepton's successor (see graphHandler line 27)
    graph(const json& jsonGraph);
    graph(std::unordered_map<std::string, graphNode> nodes_, std::vector<graphEdge> edges_);

    std::string getId() {
      return id_;
    }

    std::string getLabel() {
      return label_;
    }

    std::string getType() {
      return type_;
    }

    bool getIdIsSet() {
      return idIsSet_;
    }

    bool getLabelIsSet() {
      return labelIsSet_;
    }

    bool getTypeIsSet() {
      return typeIsSet_;
    }
  };
}

#endif
