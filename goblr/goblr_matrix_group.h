// goblr_matrix_group.h
#ifndef INCLUDED_GOBLR_MATRIX_GROUP
#define INCLUDED_GOBLR_MATRIX_GROUP

#ifndef INCLUDED_GOBLR_MATRIX
#include <goblr_matrix.h>
#endif

#include <cassert>
#include <vector>

namespace goblr {

class MatrixGroup
{
  public:
    // TYPES
    typedef std::shared_ptr<MatrixGroup> Ptr;

  private:
    // DATA
    std::vector<Matrix::Ptr> d_group;

  public:
    // MANIPULATORS
    void push(const Matrix::Ptr& matrix);

  public:
    // ACCESSORS
    const Matrix::Ptr& matrix(unsigned int i) const;
};

inline
void MatrixGroup::push(const Matrix::Ptr& matrix)
{
    d_group.push_back(matrix);
}

inline
const Matrix::Ptr& MatrixGroup::matrix(unsigned int i) const
{
    assert(0 <= i && i < d_group.size());

    return d_group[i];
}

} // Close goblr

#endif
