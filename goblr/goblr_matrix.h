// goblr_matrix.h
#ifndef INCLUDED_GOBLR_MATRIX
#define INCLUDED_GOBLR_MATRIX

#ifndef INCLUDED_GOBLB_BOARD
#include <goblb_board.h>
#endif

#include <cassert>
#include <memory>

namespace goblr {

class Matrix
{
  public:
    // TYPES
    typedef std::shared_ptr<Matrix> Ptr;

  private:
    // DATA
    const unsigned int d_size;

    std::vector<std::vector<double> > d_matrix;

  public:
    // CREATORS
    Matrix(unsigned int size = goblb::Board::SIZE);

  public:
    // ACCESSORS
    double value(unsigned int i, unsigned int j) const;
};

// INLINES
inline
double Matrix::value(unsigned int i, unsigned int j) const
{
    assert(i < d_size);
    assert(j < d_size);

    return d_matrix[i][j];
}

} // Close goblr

#endif
