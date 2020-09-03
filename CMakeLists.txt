# Required by json-schema-validator.
cmake_minimum_required(VERSION 3.2)

# Set project identifier.
project(cpp_graph_json)

# We're not interested in extras.
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(BUILD_TESTS OFF CACHE BOOL "Don't build tests for nlohmann_json_schema_validator." FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "Don't build examples for nlohmann_json_schema_validator." FORCE)

include(FetchContent)

# When all this works, use `ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git` instead.
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


FetchContent_Declare(nlohmann_json_schema_validator
  GIT_REPOSITORY https://github.com/pboettch/json-schema-validator.git
  GIT_TAG 2.1.0)
FetchContent_MakeAvailable(nlohmann_json_schema_validator)


# TODO: Do all these files need to explicitly listed here?
###### add_library(cpp_graph_json STATIC nlohmann_json)
add_library(cpp_graph_json STATIC
  src/base.cpp
  src/graph.cpp
  src/graphEdge.cpp
  src/graphNode.cpp
  src/jgReader.cpp
  src/jgWriter.cpp
  # src/utility.cpp
)

target_link_libraries(cpp_graph_json
  PRIVATE nlohmann_json::nlohmann_json
  PRIVATE nlohmann_json_schema_validator)

# add the executable
add_executable(cpp-graph-json-driver src/main.cpp)

target_link_libraries(cpp-graph-json-driver
  PRIVATE cpp_graph_json
  PRIVATE nlohmann_json::nlohmann_json
  PRIVATE nlohmann_json_schema_validator)
