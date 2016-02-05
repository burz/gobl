// goblr_generator.cpp

#include <goblr_generator.h>

namespace goblr {

Matrix::Ptr Generator::ko(const goblb::Board& board)
{
    Matrix::Ptr matrix_p(new Matrix());

    return matrix_p;
}

MatrixGroup::Ptr Generator::liberties(const goblb::Board& board)
{
    MatrixGroup::Ptr matrixGroup_p(new MatrixGroup());

    return matrixGroup_p;
}

} // Close goblr
