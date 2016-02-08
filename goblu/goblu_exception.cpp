// goblu_exception.cpp

#include <goblu_exception.h>

namespace goblu {

Exception::Exception(const std::string& error)
: std::runtime_error(error)
{
}

} // Close goblu
