// goblr_matrix.cpp

#include <goblr_matrix.h>

namespace goblr {

Matrix::Matrix(unsigned int size)
: d_size(size)
, d_matrix(d_size, std::vector<double>(d_size, 0.0))
{
}

} // Close goblr
