// goblr_matrix.t.cpp

#include <goblr_matrix.h>

#include <gtest/gtest.h>

namespace goblr {

TEST(Matrix, constructor)
{
    {
        Matrix matrix;

        for(unsigned int i = 0; i < goblb::Board::SIZE; ++i)
        {
            for(unsigned int j = 0; j < goblb::Board::SIZE; ++j)
            {
                EXPECT_EQ(0.0, matrix.value(i, j));
            }
        }
    }
    {
        const unsigned int size = 31;

        Matrix matrix(size);

        for(unsigned int i = 0; i < size; ++i)
        {
            for(unsigned int j = 0; j < size; ++j)
            {
                EXPECT_EQ(0.0, matrix.value(i, j));
            }
        }
    }
}

} // Close goblr
