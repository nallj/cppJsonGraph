#ifndef NALLJ_CJG_INFORMED_EXCEPTION
#define NALLJ_CJG_INFORMED_EXCEPTION

#include <exception>
#include <string>

namespace nallj {
  class informedException : public std::exception {
    std::string message_;
  public:
    explicit informedException(const std::string& message);
    virtual const char* what() const throw() {
        return message_.c_str();
    }
  };
};

#endif
