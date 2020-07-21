#ifndef JG_WRITER_HPP
#define JG_WRITER_HPP

#include <fstream> // ifstream
#include <iomanip> // setw
#include <iostream> // cout

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class jgWriter {
  public:
    jgWriter();
};

#endif
