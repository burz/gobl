// goblr_matrix_group.t.cpp

#include <goblr_matrix_group.h>

#include <gtest/gtest.h>

#include <chrono>
#include <fstream>

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

TEST(MatrixGroup, writeReadFromFile)
{
    std::time_t now = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now()
    );
    std::ostringstream sstream;
    sstream << ".goblr.test.temp" << now;
    const std::string tempFileName = sstream.str();

    std::cout << "Using file: " << tempFileName << std::endl;

    {
        MatrixGroup group;
        for(unsigned int c = 0; c < 5; ++c)
        {
            Matrix::Ptr matrix_p(new Matrix());
            for(unsigned int i = 0; i < goblb::Board::SIZE; ++i)
            {
                for(unsigned int j = 0; j < goblb::Board::SIZE; ++j)
                {
                    matrix_p->set(i, j, c + i + j);
                }
            }
            group.push(matrix_p);
        }

        std::ofstream fstream(tempFileName, std::ofstream::binary);
        group.writeToFile(fstream);
    }

    {
        MatrixGroup group;
        std::ifstream fstream(tempFileName, std::ifstream::binary);
        group.readFromFile(fstream);
        for(unsigned int c = 0; c < 5; ++c)
        {
            Matrix::Ptr matrix_p = group.get(c);
            ASSERT_TRUE(static_cast<bool>(matrix_p));
            for(unsigned int i = 0; i < goblb::Board::SIZE; ++i)
            {
                for(unsigned int j = 0; j < goblb::Board::SIZE; ++j)
                {
                    EXPECT_EQ(matrix_p->get(i, j), c + i + j);
                }
            }
        }
    }

    std::remove(tempFileName.c_str());
}

} // Close goblr
