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
FetchContent_Declare(nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.7.3
  GIT_PROGRESS TRUE
)

FetchContent_Declare(nlohmann_json_schema_validator
  GIT_REPOSITORY https://github.com/pboettch/json-schema-validator.git
  GIT_TAG 2.1.0
  GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(nlohmann_json nlohmann_json_schema_validator) # CMake 3.14+

add_subdirectory(src)

# Only build the driver app if this project is the head.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  add_subdirectory(app)
endif()
