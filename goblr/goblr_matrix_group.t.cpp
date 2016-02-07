// goblr_matrix_group.t.cpp

#include <goblr_matrix_group.h>

#include <gtest/gtest.h>

namespace goblr {

TEST(MatrixGroup, constructor)
{
    MatrixGroup matrixGroup;

    EXPECT_EQ(0u, matrixGroup.size());
}

TEST(MatrixGroup, pushGet)
{
    MatrixGroup group;

    Matrix::Ptr matrix_p(new Matrix());
    matrix_p->set(0, 1, 4.5);

    EXPECT_EQ(0u, group.size());

    group.push(matrix_p);

    EXPECT_EQ(1u, group.size());

    Matrix::Ptr returnedMatrix_p = group.get(0);

    EXPECT_EQ(matrix_p.get(), returnedMatrix_p.get());
}

} // Close goblr
