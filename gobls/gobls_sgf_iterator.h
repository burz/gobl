// gobls_sgf_iterator.h
#ifndef INCLUDED_GOBLS_SGF_ITERATOR
#define INCLUDED_GOBLS_SGF_ITERATOR

#ifndef INCLUDED_GOBLS_SGF
#include <gobls_sgf.h>
#endif

#include <string>
#include <vector>

namespace gobls {

class SgfIterator
{
  public:
    // TYPES
    typedef std::vector<std::string> Strings;

  private:
    // DATA
    bool d_files;

    Strings::const_iterator       d_iterator;
    const Strings::const_iterator d_end;
    Sgf::Ptr                      d_next;
    unsigned int                  d_succeeded;
    unsigned int                  d_failed;

  public:
    // CREATORS
    SgfIterator(const Strings& strings, bool files = false);

  public:
    // MANIPULATORS
    bool next();

  public:
    // ACCESSORS
    Sgf::Ptr value() const;
    unsigned int succeeded() const;
    unsigned int failed() const;
};

// INLINES
inline
Sgf::Ptr SgfIterator::value() const
{
    return d_next;
}

inline
unsigned int SgfIterator::succeeded() const
{
    return d_succeeded;
}

inline
unsigned int SgfIterator::failed() const
{
    return d_failed;
}

} // Close gobls

#endif
