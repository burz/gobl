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
    unsigned int size() const;
    const Matrix::Ptr& get(unsigned int i) const;

    void print(std::ostream& stream) const;
};

// FREE OPERATORS
std::ostream& operator<<(std::ostream& stream, const MatrixGroup& group);

// INLINES
inline
unsigned int MatrixGroup::size() const
{
    return d_group.size();
}

inline
void MatrixGroup::push(const Matrix::Ptr& matrix)
{
    d_group.push_back(matrix);
}

inline
const Matrix::Ptr& MatrixGroup::get(unsigned int i) const
{
    assert(0 <= i && i < d_group.size());

    return d_group[i];
}

} // Close goblr

#endif
