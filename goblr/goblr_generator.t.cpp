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
    {
        goblb::Board board(9);

        MatrixGroup::Ptr group_p
        = Generator::liberties(
              board
            , goblb::SpaceState::BLACK
            , 2
        );
        ASSERT_TRUE(static_cast<bool>(group_p));
        ASSERT_EQ(4u, group_p->size());

        std::cout << *group_p << std::endl;

        MatrixGroup::Ptr group2_p
        = Generator::liberties(
              board
            , goblb::SpaceState::WHITE
            , 2
        );
        ASSERT_TRUE(static_cast<bool>(group2_p));

        ASSERT_EQ(group_p->size(), group2_p->size());

        for(unsigned int i = 0; i < group_p->size(); ++i)
        {
            expectZeros(group_p->get(i));
            expectZeros(group2_p->get(i));
        }
    }
    {
        goblb::Board board(4);

        board.play(0, 0);
        board.play(0, 1);
        board.play(2, 2);

        std::cout << board << std::endl;

        MatrixGroup::Ptr group_p
        = Generator::liberties(
              board
            , goblb::SpaceState::BLACK
            , 3
        );

        ASSERT_TRUE(static_cast<bool>(group_p));
        ASSERT_EQ(6u, group_p->size());

        std::cout << *group_p << std::endl;

        expectZeros(group_p->get(1));
        expectZeros(group_p->get(3));
        expectZeros(group_p->get(5));

        {
            Matrix matrix(4);
            matrix.set(0, 0, 1.0);

            EXPECT_EQ(matrix, *group_p->get(0));
        }
        {
            Matrix matrix(4);
            matrix.set(2, 2, 1.0);

            EXPECT_EQ(matrix, *group_p->get(2));
        }
        {
            Matrix matrix(4);
            matrix.set(0, 1, 1.0);

            EXPECT_EQ(matrix, *group_p->get(4));
        }
    }
}

TEST(Generator, representation)
{
}

} // Close goblr
