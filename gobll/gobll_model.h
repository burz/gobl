// gobll_model.h
#ifndef INCLUDED_GOBLL_MODEL
#define INCLUDED_GOBLL_MODEL

#ifndef INCLUDED_GOBLD_GAME_ITERATOR
#include <gobld_game_iterator.h>
#endif

#include <string>
#include <vector>

namespace gobll {

class Model
{
  public:
    // CREATORS
    virtual ~Model();

  public:
    // MANIPULATORS
    virtual void train(gobld::GameIterator& gameIterator) = 0;
    virtual float test(gobld::GameIterator& gameIterator) = 0;

    void train(const std::vector<std::string>& strings, bool files = false);
    float test(const std::vector<std::string>& strings, bool files = false);

    virtual void readFromFile(const std::string& fileName) const = 0;

  public:
    // ACCESSORS
    virtual void writeToFile(const std::string& fileName) const = 0;
};

// INLINES
inline
void Model::train(const std::vector<std::string>& strings, bool files)
{
    gobld::GameIterator itt(strings, files);

    train(itt);
}

inline
float Model::test(const std::vector<std::string>& strings, bool files)
{
    gobld::GameIterator itt(strings, files);

    return test(itt);
}

} // Close gobll

#endif
