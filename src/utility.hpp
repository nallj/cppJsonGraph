#ifndef JG_UTILITY_HPP
#define JG_UTILITY_HPP

#include <iostream> // cout

#include <nlohmann/json.hpp>

using json = nlohmann::json;

// FIXME: Linker fails with 'undefined reference to bool nallj::jgUtility::hydrateAndCheckIfSet.'
namespace nallj {
  struct jgUtility {
    template <typename T>
    static bool hydrateAndCheckIfSet(const json& jsonGraph, const char* itemKey, T& variable);
  };
}

#endif
