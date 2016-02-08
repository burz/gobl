// goblr_matrix.cpp

#include <goblr_matrix.h>

#include <iomanip>

namespace goblr {

Matrix::Matrix(unsigned int size)
: d_size(size)
, d_matrix(d_size, std::vector<double>(d_size, 0.0))
{
}

void Matrix::print(std::ostream& stream) const
{
    stream << std::endl;

    for(unsigned int i = 1; i <= d_size; i++)
    {
        const unsigned int k = d_size - i;

        stream << std::setw(2) << k << "  [ "
               << std::fixed << std::setprecision(3)
               << d_matrix[k][0];

        for(unsigned int j = 1; j < d_size; ++j)
        {
            stream << ", " << std::fixed << std::setprecision(3)
                   << d_matrix[k][j];
        }

        stream << " ]\n";
    }

    stream << "  ";

    for(unsigned int j = 0; j < d_size; ++j)
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
