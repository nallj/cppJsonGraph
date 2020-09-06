file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${cppJsonGraph_SOURCE_DIR}/include/cppJsonGraph/*.hpp")

add_library(cpp_graph_json STATIC
  base.cpp
  graph.cpp
  graphEdge.cpp
  graphNode.cpp
  jgReader.cpp
  jgWriter.cpp
  ${HEADER_LIST} # Why is this necessary?  What good are the headers.
)

# We need this directory, and users of our library will need it too.
target_include_directories(cpp_graph_json PUBLIC ../include)

target_link_libraries(cpp_graph_json
  PRIVATE nlohmann_json::nlohmann_json
  PRIVATE nlohmann_json_schema_validator)

# All users of this library will need at least C++11.
target_compile_features(cpp_graph_json PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place.
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
