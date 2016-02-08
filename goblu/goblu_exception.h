// goblu_exception.h
#ifndef INCLUDED_GOBLU_EXCEPTION
#define INCLUDED_GOBLU_EXCEPTION

#include <stdexcept>
#include <string>
#include <sstream>

namespace goblu {

class Exception : public std::runtime_error
{
  public:
    // CREATORS
    Exception(const std::string& error);
};

#define THROW_GOBL(goblu__error_stream)                 \
    do {                                                \
        std::ostringstream goblu__stream;               \
        goblu__stream << "goblu::Exception thrown at "  \
                      << __FILE__ << ':' << __LINE__    \
                      << " with message '"              \
                      << goblu__error_stream << "'";    \
        std::string goblu__error = goblu__stream.str(); \
        throw goblu::Exception(goblu__error);           \
    } while(0)

} // Close goblu

#endif
