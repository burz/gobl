// goblr_matrix.cpp

#include <goblr_matrix.h>

#include <iomanip>
#include <fstream>

namespace goblr {

Matrix::Matrix(unsigned int size)
: d_matrix(size, std::vector<double>(size, 0.0))
{
}

void Matrix::readFromFile(std::ifstream& fstream)
{
    unsigned int size;
    fstream.read(
          reinterpret_cast<char*>(&size)
        , sizeof(unsigned int)
    );

    d_matrix = std::vector<std::vector<double> >(
          size
        , std::vector<double>(size, 0.0)
    );

    for(unsigned int i = 0; i < d_matrix.size(); ++i)
    {
        for(unsigned int j = 0; j < d_matrix.size(); ++j)
        {
            fstream.read(
                  reinterpret_cast<char*>(&d_matrix[i][j])
                , sizeof(double)
            );
        }
    }
}

void Matrix::writeToFile(std::ofstream& fstream) const
{
    const unsigned int size = d_matrix.size();
    fstream.write(
          reinterpret_cast<const char*>(&size)
        , sizeof(unsigned int)
    );

    for(unsigned int i = 0; i < d_matrix.size(); ++i)
    {
        for(unsigned int j = 0; j < d_matrix.size(); ++j)
        {
            fstream.write(
                  reinterpret_cast<const char*>(&d_matrix[i][j])
                , sizeof(double)
            );
        }
    }
}

void Matrix::print(std::ostream& stream) const
{
    stream << std::endl;

    for(unsigned int i = 1; i <= d_matrix.size(); ++i)
    {
        const unsigned int k = d_matrix.size() - i;

        stream << std::setw(2) << k << "  [ "
               << std::fixed << std::setprecision(3)
               << d_matrix[k][0];

        for(unsigned int j = 1; j < d_matrix.size(); ++j)
        {
            stream << ", " << std::fixed << std::setprecision(3)
                   << d_matrix[k][j];
        }

        stream << " ]\n";
    }

    stream << "  ";

    for(unsigned int j = 0; j < d_matrix.size(); ++j)
    {
        stream << "     " << std::setw(2) << j;
    }

    stream << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const Matrix& matrix)
{
    matrix.print(stream);

    return stream;
}

} // Close goblr
