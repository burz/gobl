// goblr_generator.t.cpp

#include <goblr_generator.h>

#include <gtest/gtest.h>

namespace goblr {

namespace {

void expectZeros(const Matrix::Ptr& matrix_p)
{
    for(unsigned int i = 0; i < matrix_p->size(); ++i)
    {
        for(unsigned int j = 0; j < matrix_p->size(); ++j)
        {
            EXPECT_EQ(0.0, matrix_p->get(i, j));
        }
    }
}

} // Close anonymous

TEST(Generator, ko)
{
    goblb::Board board;

    {
        Matrix::Ptr matrix_p = Generator::ko(board);
        ASSERT_TRUE(static_cast<bool>(matrix_p));

        std::cout << *matrix_p << std::endl << std::endl;

        expectZeros(matrix_p);
    }

    board.play(0, 1);
    board.play(0, 2);
    board.play(1, 0);
    board.play(1, 1);

    std::cout << board << std::endl;

    {
        Matrix::Ptr matrix_p = Generator::ko(board);
        ASSERT_TRUE(static_cast<bool>(matrix_p));

        std::cout << *matrix_p << std::endl << std::endl;

        expectZeros(matrix_p);
    }

    board.play(0, 0, goblb::SpaceState::WHITE);

    std::cout << board << std::endl;

    {
        Matrix::Ptr matrix_p = Generator::ko(board);
        ASSERT_TRUE(static_cast<bool>(matrix_p));

        std::cout << *matrix_p << std::endl << std::endl;

        EXPECT_EQ(1.0, matrix_p->get(0, 1));
    }

    board.play(0, 1, goblb::SpaceState::BLACK);

    std::cout << board << std::endl;

    {
        Matrix::Ptr matrix_p = Generator::ko(board);
        ASSERT_TRUE(static_cast<bool>(matrix_p));

        std::cout << *matrix_p << std::endl << std::endl;

        EXPECT_EQ(1.0, matrix_p->get(0, 0));
    }
}

TEST(Generator, liberties)
{
}

TEST(Generator, representation)
{
}

} // Close goblr
