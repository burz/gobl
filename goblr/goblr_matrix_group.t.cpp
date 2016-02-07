// goblr_matrix_group.t.cpp

#include <goblr_matrix_group.h>

#include <gtest/gtest.h>

namespace goblr {

TEST(MatrixGroup, constructor)
{
    MatrixGroup matrixGroup;
}

TEST(MatrixGroup, pushGet)
{
    MatrixGroup group;

    Matrix::Ptr matrix_p(new Matrix());
    matrix_p->set(0, 1, 4.5);

    group.push(matrix_p);

    Matrix::Ptr returnedMatrix_p = group.get(0);

    EXPECT_EQ(matrix_p.get(), returnedMatrix_p.get());
}

} // Close goblr
