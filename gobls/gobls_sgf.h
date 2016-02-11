// gobls_sgf.h
#ifndef INCLUDED_GOBLS_SGF
#define INCLUDED_GOBLS_SGF

#ifndef INCLUDED_GOBLB_BOARD
#include <goblb_board.h>
#endif

#include <map>
#include <memory>
#include <vector>

namespace gobls {

class Sgf
{
  public:
    // TYPES
    typedef std::shared_ptr<Sgf>                  Ptr;
    typedef std::map<std::string, std::string>    Metadata;
    typedef std::pair<unsigned int, unsigned int> Move;
    typedef std::vector<Move>::const_iterator     Iterator;

  public:
    // CLASS METHODS
    static bool isPass(const Move& move);
    static Move makePass();

  private:
    // DATA
    Metadata          d_metadata;
    std::vector<Move> d_moves;

  public:
    // MANIPULATORS
    void add(const std::string& attribute, const std::string& value);
    void add(unsigned int i, unsigned int j);

  public:
    // ACCESSORS
    const std::string& lookup(const std::string& attribute) const;

    Iterator begin() const;
    Iterator end() const;
};

// INLINES
inline
bool Sgf::isPass(const Move& move)
{
    return (goblb::Board::SIZE == move.first)
        && (goblb::Board::SIZE == move.second);
}

inline
void Sgf::add(const std::string& attribute, const std::string& value)
{
    d_metadata.insert(Metadata::value_type(attribute, value));
}

inline
void Sgf::add(unsigned int i, unsigned int j)
{
    d_moves.push_back(Move(i, j));
}

inline
Sgf::Iterator Sgf::begin() const
{
    return d_moves.begin();
}

inline
Sgf::Iterator Sgf::end() const
{
    return d_moves.end();
}

} // Close gobls

#endif
