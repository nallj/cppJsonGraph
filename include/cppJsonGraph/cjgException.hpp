#ifndef NALLJ_CJG_CJG_EXCEPTION
#define NALLJ_CJG_CJG_EXCEPTION

#include <exception>
#include <string>

namespace nallj {
  class cjgException : public std::exception {
    std::string message_;
  public:
    explicit cjgException(const std::string& message);
    virtual const char* what() const throw() {
        return message_.c_str();
    }
  };
};

#endif
