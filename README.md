# C++ JSON Graph

A library that provides graph data structures and methods for serializing and deserializing to/from the [JSON Graph Format](http://jsongraphformat.info/) v2.

## Dependencies
* [JSON for Modern C++](https://github.com/nlohmann/json)
* [JSON schema validator for JSON for Modern C++](https://github.com/pboettch/json-schema-validator)

## Installation
* Clone 'JSON for Modern C++' repository into the `lib` directory.  Do the same for 'JSON schema validator for JSON for Modern C++'.
  * git clone git@github.com:nlohmann/json.git (or git clone git@github.com:ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git)
  * git clone git@github.com:pboettch/json-schema-validator.git
* From the project root directory run `cmake -Dnlohmann_json_DIR=build/lib/json ..` in the `build` directory.
* Run `make`.  Once completed, copy `cpp-graph-json-driver` into the root of the project directory (i.e. `mv cpp-graph-json-driver ../cpp-graph-json-driver`).
* In the project root, run `./cpp-graph-json-driver`.
