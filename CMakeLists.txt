# Required by json-schema-validator.
cmake_minimum_required(VERSION 3.2)

# Set project identifier.
project(cpp_graph_json)

#[[
  TODO: Use the repositories as external sources.
  https://stackoverflow.com/questions/38006584/how-to-clone-and-integrate-external-from-git-cmake-project-into-local-one

  NOTE: Always run `cmake` in the build directory (a.k.a. uild out-of-source)
  https://stackoverflow.com/questions/9680420/looking-for-a-cmake-clean-command-to-clear-up-cmake-output

  add_library may use “generator expressions” with the syntax $<...>.
  https://cmake.org/cmake/help/v3.2/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)

  NESTED target_link_libraries
  https://stackoverflow.com/questions/57186187/cmake-nested-libraries

  From the website (https://cmake.org/cmake/help/v3.2/manual/cmake-buildsystem.7.html#binary-targets)
    add_library(archive archive.cpp zip.cpp lzma.cpp)
    add_executable(zipapp zipapp.cpp)
    target_link_libraries(zipapp archive)
]]

# We're not interested in extras.
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(BUILD_TESTS OFF CACHE BOOL "Don't build tests for nlohmann_json_schema_validator." FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "Don't build examples for nlohmann_json_schema_validator." FORCE)

# add_subdirectory(nlohmann_json)
add_subdirectory(lib/json)
add_subdirectory(lib/json-schema-validator)

# Library CMakeLists.txt files
#find_package(nlohmann_json 3.2.0 REQUIRED)
#find_package(nlohmann_json_schema_validator REQUIRED)

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
add_executable(cpp-graph-json-driver src/main.cpp) # cpp_graph_json)
#[[
  add_executable(cpp-graph-json-driver
    src/main.cpp
    src/schema.cpp
    src/jgReader.cpp
    src/graph.cpp
    src/utility.cpp)
]]

target_link_libraries(cpp-graph-json-driver
  PRIVATE cpp_graph_json
  PRIVATE nlohmann_json::nlohmann_json
  PRIVATE nlohmann_json_schema_validator)
#[[
  target_link_libraries(cpp-graph-json-driver
    PRIVATE nlohmann_json::nlohmann_json
    PRIVATE nlohmann_json_schema_validator)
]]







# Working - json library with driver
#[[
  set(JSON_BuildTests OFF CACHE INTERNAL "")
  set(BUILD_TESTS OFF CACHE BOOL "Don't build tests for nlohmann_json_schema_validator." FORCE)
  set(BUILD_EXAMPLES OFF CACHE BOOL "Don't build examples for nlohmann_json_schema_validator." FORCE)

  add_subdirectory(lib/json)
  add_subdirectory(lib/json-schema-validator)

  find_package(nlohmann_json 3.2.0 REQUIRED)
  find_package(nlohmann_json_schema_validator REQUIRED)

  add_library(cpp_graph_json STATIC src/jgWriter.cpp src/graph.cpp src/jgReader.cpp)

  target_link_libraries(cpp_graph_json PRIVATE nlohmann_json::nlohmann_json)

  # add the executable
  add_executable(cpp-graph-json-driver src/main.cpp) # cpp_graph_json)

  target_link_libraries(cpp-graph-json-driver
    PRIVATE cpp_graph_json
    PRIVATE nlohmann_json::nlohmann_json
    PRIVATE nlohmann_json_schema_validator)
]]
