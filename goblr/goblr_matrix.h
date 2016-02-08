// goblr_matrix.h
#ifndef INCLUDED_GOBLR_MATRIX
#define INCLUDED_GOBLR_MATRIX

#ifndef INCLUDED_GOBLB_BOARD
#include <goblb_board.h>
#endif

#include <cassert>
#include <iostream>
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
    // MANIPULATORS
    void set(unsigned int i, unsigned int j, double value);

  public:
    // ACCESSORS
    unsigned int size() const;
    double get(unsigned int i, unsigned int j) const;

    void print(std::ostream& stream) const;

  public:
    // OPERATORS
    bool operator==(const Matrix& matrix) const;
    bool operator!=(const Matrix& matrix) const;
};

// FREE OPERATORS
std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);

// INLINES
inline
unsigned int Matrix::size() const
{
    return d_size;
}

inline
void Matrix::set(unsigned int i, unsigned int j, double value)
{
    assert(i < d_size);
    assert(j < d_size);

    d_matrix[i][j] = value;
}

inline
double Matrix::get(unsigned int i, unsigned int j) const
{
    assert(i < d_size);
    assert(j < d_size);

    return d_matrix[i][j];
}

inline
bool Matrix::operator==(const Matrix& matrix) const
{
    return d_matrix == matrix.d_matrix;
}

inline
bool Matrix::operator!=(const Matrix& matrix) const
{
    return d_matrix != matrix.d_matrix;
}

} // Close goblr

#endif
