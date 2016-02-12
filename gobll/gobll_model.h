// gobll_model.h
#ifndef INCLUDED_GOBLL_MODEL
#define INCLUDED_GOBLL_MODEL

#ifndef INCLUDED_GOBLD_GAME_ITERATOR
#include <gobld_game_iterator.h>
#endif

#include <string>

namespace gobll {

class Model
{
  public:
    // CREATORS
    virtual ~Model();

  public:
    // MANIPULATORS
    virtual void train(gobld::GameIterator& gameIterator) = 0;
    virtual void test(gobld::GameIterator& gameIterator) = 0;

    virtual void readFromFile(const std::string& fileName) const = 0;

  public:
    // ACCESSORS
    virtual void writeToFile(const std::string& fileName) const = 0;
};

} // Close gobll

#endif
