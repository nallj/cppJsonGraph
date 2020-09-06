add_executable(cpp-graph-json-driver main.cpp)
target_compile_features(cpp-graph-json-driver PRIVATE cxx_std_11)

target_link_libraries(cpp-graph-json-driver
  PRIVATE cpp_graph_json
  PRIVATE nlohmann_json::nlohmann_json
  PRIVATE nlohmann_json_schema_validator)
