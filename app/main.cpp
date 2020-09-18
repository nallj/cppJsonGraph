#include <fstream> // ifstream
#include <iomanip> // setw
#include <iostream> // cout
#include <stdlib.h> // EXIT_SUCCESS
#include <string> // string
#include <vector> // vector

#include <cppJsonGraph/deserializer.hpp>
#include <cppJsonGraph/graph.hpp>
#include <cppJsonGraph/serializer.hpp>

void printGraphInfo(nallj::graph graph) {
  std::cout << "\tNAME (is" << (graph.getLabelIsSet() ? "" : " not") << " set): " << graph.getLabel() << "\n";
  std::cout << "\tID (is" << (graph.getIdIsSet() ? "" : " not") << " set): " << graph.getId() << "\n";
  std::cout << "\tTYPE (is" << (graph.getTypeIsSet() ? "" : " not") << " set): " << graph.getType() << "\n";

  auto metadataIsSet = graph.getMetadataIsSet();
  auto metadata = graph.getMetadata();

  std::cout << "\tIs METADATA set: " << (metadataIsSet ? "Y" : "N") << "\n";
  if (metadataIsSet) {
    std::cout << "\tMETADATA keys:";
    for (const auto& [key, _] : metadata) {
      std::cout << " " << key;
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void printGraphCollectionInfo(std::vector<nallj::graph> collection, std::string title) {
  std::cout << "\n" << title << " has " << collection.size() << " graphs...\n";
  for (const auto& graph : collection) {
    printGraphInfo(graph);
  }
}

int main() {
  auto graphFile = std::ifstream("graph.json");
  auto graphsFile = std::ifstream("graphs.json");

  auto reader = nallj::deserializer();

  if (!reader.isFileValid(graphFile) || !reader.isFileValid(graphsFile)) {
    throw nallj::cjgException("One of the input files violates the JSON Graph Schema v2.");
  }

  // Seek to beginning of the input file streams.
  graphFile.seekg(0, graphFile.beg);
  graphsFile.seekg(0, graphsFile.beg);

  std::cout << "SINGLE GRAPH FILE:\n";
  auto singleGraphCollection = reader.getGraphs(graphFile);

  printGraphCollectionInfo(singleGraphCollection, "singleGraphCollection");

  std::cout << "\nTWO GRAPHS FILE:\n";
  auto twoGraphsCollection = reader.getGraphs(graphsFile);

  printGraphCollectionInfo(twoGraphsCollection, "twoGraphsCollection");

  auto writer = nallj::serializer();

  std::ofstream output;
  output.open("single-graph.json");
  writer.saveGraph(output, singleGraphCollection[0]);
  output.close();

  output.open("two-graphs.json");
  writer.saveGraphs(output, twoGraphsCollection);
  output.close();

  return EXIT_SUCCESS;
}
