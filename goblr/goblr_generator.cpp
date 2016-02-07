// goblr_generator.cpp

#include <goblr_generator.h>

namespace goblr {

Matrix::Ptr Generator::ko(const goblb::Board& board)
{
    Matrix::Ptr matrix_p(new Matrix());

    const goblb::Space::Ptr& ko_p = board.ko();

    if(ko_p)
    {
        matrix_p->set(ko_p->i(), ko_p->j(), 1.0);
    }

    return matrix_p;
}

MatrixGroup::Ptr Generator::liberties(const goblb::Board& board)
{
    MatrixGroup::Ptr matrixGroup_p(new MatrixGroup());

    return matrixGroup_p;
}

} // Close goblr
