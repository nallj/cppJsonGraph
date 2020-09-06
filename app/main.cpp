#include <fstream> // ifstream
#include <iomanip> // setw
#include <iostream> // cout

//#include <nlohmann/json.hpp>
//#include <nlohmann/json-schema.hpp>

#include <cppJsonGraph/jgWriter.hpp>
#include <cppJsonGraph/jgReader.hpp>

using jgReader = nallj::jgReader;

//using json = nlohmann::json;
//using nlohmann::json_schema::json_validator;

// // The schema is defined based upon a string literal
// static json person_schema = R"(
// {
//     "$schema": "http://json-schema.org/draft-07/schema#",
//     "title": "A person",
//     "properties": {
//         "name": {
//             "description": "Name",
//             "type": "string"
//         },
//         "age": {
//             "description": "Age of the person",
//             "type": "number",
//             "minimum": 2,
//             "maximum": 200
//         }
//     },
//     "required": [
//                  "name",
//                  "age"
//                  ],
//     "type": "object"
// }

// )"_json;

// // JSON Graph Schema v2
// static json json_graph_schema = R"(
// {
//   "$schema": "http://json-schema.org/draft-07/schema#",
//   "$id": "http://jsongraphformat.info/v2.0/json-graph-schema.json",
//   "title": "JSON Graph Schema",
//   "oneOf": [
//     {
//       "type": "object",
//       "properties": {
//         "graph": {
//           "$ref": "#/definitions/graph"
//         }
//       },
//       "additionalProperties": false,
//       "required": [
//         "graph"
//       ]
//     },
//     {
//       "type": "object",
//       "properties": {
//         "graphs": {
//           "type": "array",
//           "items": {
//             "$ref": "#/definitions/graph"
//           }
//         }
//       },
//       "additionalProperties": false
//     }
//   ],
//   "definitions": {
//     "graph": {
//       "type": "object",
//       "additionalProperties": false,
//       "properties": {
//         "id": {
//           "type": "string"
//         },
//         "label": {
//           "type": "string"
//         },
//         "directed": {
//           "type": [
//             "boolean"
//           ],
//           "default": true
//         },
//         "type": {
//           "type": "string"
//         },
//         "metadata": {
//           "type": [
//             "object"
//           ]
//         },
//         "nodes": {
//           "type": "object",
//           "additionalProperties": {
//             "type": "object",
//             "properties": {
//               "label": {
//                 "type": "string"
//               },
//               "metadata": {
//                 "type": "object"
//               }
//             },
//             "additionalProperties": false
//           }
//         },
//         "edges": {
//           "type": [
//             "array"
//           ],
//           "items": {
//             "type": "object",
//             "additionalProperties": false,
//             "properties": {
//               "id": {
//                 "type": "string"
//               },
//               "source": {
//                 "type": "string"
//               },
//               "target": {
//                 "type": "string"
//               },
//               "relation": {
//                 "type": "string"
//               },
//               "directed": {
//                 "type": [
//                   "boolean"
//                 ],
//                 "default": true
//               },
//               "label": {
//                 "type": "string"
//               },
//               "metadata": {
//                 "type": [
//                   "object"
//                 ]
//               }
//             },
//             "required": [
//               "source",
//               "target"
//             ]
//           }
//         }
//       }
//     }
//   }
// }
// )"_json;

// The people are defined with brace initialization
// static json bad_person = {{"age", 42}};
// static json good_person = {{"name", "Albert"}, {"age", 42}};

// class custom_error_handler : public nlohmann::json_schema::basic_error_handler
// {
//   void error(const nlohmann::json_pointer<nlohmann::basic_json<>> &pointer, const json &instance,
//       const std::string &message) override
//   {
//     nlohmann::json_schema::basic_error_handler::error(pointer, instance, message);
//     std::cerr << "ERROR: '" << pointer << "' - '" << instance << "': " << message << "\n";
//   }
// };

int main() {
  std::cout << "OMG LOL 22 \n";

  // // read a JSON file
  // std::ifstream i("test.json");
  // json j;
  // i >> j;

  // // write prettified JSON to another file
  // std::ofstream o("pretty.json");
  // o << std::setw(2) << j << std::endl;

  // std::cout << j;

  auto reader = jgReader();

  
  // auto fakeFile = std::ifstream("fake_file.no");
  // reader.isFileValid(fakeFile);

  // auto nonJsonFile = std::ifstream("CMakeCache.txt");
  // reader.isFileValid(nonJsonFile);

  auto graphFile = std::ifstream("graph.json");
  // reader.isFileValid(graphFile);

  // auto invalidJsonFile = std::ifstream("pretty.json");
  // reader.isFileValid(invalidJsonFile);

  auto graphsFile = std::ifstream("graphs.json");
  // reader.isFileValid(graphsFile);
  


  graphFile.seekg(0, graphFile.beg);
  std::cout << "\n\nSINGLE GRAPH FILE:\n";
  auto singleGraphCollection = reader.getGraphs(graphFile);

  std::cout << "\nsingleGraphCollection has " << singleGraphCollection.size() << " elements\n\n";

  auto one = singleGraphCollection[0];
  std::cout << "NAME: " << one.getLabel() << "\n";
  std::cout << "ID: " << one.getId() << "\n";
  std::cout << "TYPE: " << one.getType() << "\n";
  std::cout << "label i set: " << one.getLabelIsSet() << "\n";
  std::cout << "idis set: " << one.getIdIsSet() << "\n";
  std::cout << "ty[e is set]: " << one.getTypeIsSet() << "\n";

  graphsFile.seekg(0, graphsFile.beg);
  std::cout << "\n\nMULTI GRAPH FILE:\n";
  auto multiGraphCollection = reader.getGraphs(graphsFile);

  std::cout << "multiGraphCollection has " << multiGraphCollection.size() << " elements\n\n";

    auto two = multiGraphCollection[0];
  std::cout << "NAME: " << two.getLabel() << "\n";
  std::cout << "ID: " << two.getId() << "\n";
  std::cout << "TYPE: " << two.getType() << "\n";
  std::cout << "label i set: " << two.getLabelIsSet() << "\n";
  std::cout << "idis set: " << two.getIdIsSet() << "\n";
  std::cout << "ty[e is set]: " << two.getTypeIsSet() << "\n";

      auto two2 = multiGraphCollection[1];
  std::cout << "NAME: " << two2.getLabel() << "\n";
  std::cout << "ID: " << two2.getId() << "\n";
  std::cout << "TYPE: " << two2.getType() << "\n";
  std::cout << "label i set: " << two2.getLabelIsSet() << "\n";
  std::cout << "idis set: " << two2.getIdIsSet() << "\n";
  std::cout << "ty[e is set]: " << two2.getTypeIsSet() << "\n";

  //auto derp = jgWriter();



  /* json-parse the schema */

  // json_validator validator; // create validator

  // // try {
  // //     validator.set_root_schema(person_schema); // insert root-schema
  // // } catch (const std::exception &e) {
  // //     std::cerr << "Validation of schema failed, here is why: " << e.what() << "\n";
  // //     return EXIT_FAILURE;
  // // }

  // std::ifstream i("graph.json");
  // json j;
  // i >> j;

  // std::ifstream i2("graphs.json");
  // json j2;
  // i2 >> j2;

  // try {
  //   validator.set_root_schema(json_graph_schema);
  // } catch (const std::exception &e) {
  //   std::cerr << "Validation of schema failed, here is why: " << e.what() << "\n";
  //   return EXIT_FAILURE;
  // }

  // /* json-parse the people - API of 1.0.0, default throwing error handler */

  // // for (auto &person : {j, j2}) {
  // //   std::cout << "About to validate this graph file:\n"
  // //             << std::setw(2) << person << std::endl;
  // //   try {
  // //       validator.validate(person); // validate the document - uses the default throwing error-handler
  // //       std::cout << "Validation succeeded\n";
  // //   } catch (const std::exception &e) {
  // //       std::cerr << "Validation failed, here is why: " << e.what() << "\n";
  // //   }
  // // }

  // // for (auto &person : {bad_person, good_person}) {
  // //   std::cout << "About to validate this person:\n"
  // //             << std::setw(2) << person << std::endl;

  // //   custom_error_handler err;
  // //   validator.validate(person, err); // validate the document

  // //   if (err)
  // //     std::cerr << "Validation failed\n";
  // //   else
  // //     std::cout << "Validation succeeded\n";
  // // }

  return EXIT_SUCCESS;
}
