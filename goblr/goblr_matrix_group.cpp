// goblr_matrix_group.cpp

#include <goblr_matrix_group.h>

namespace goblr {

void MatrixGroup::print(std::ostream& stream) const
{
    unsigned int count = 0;

    for(auto itt = d_group.begin(); itt != d_group.end(); ++itt)
    {
        stream << "<< MATRIX " << count << **itt << ">>" << std::endl;

        ++count;
    }
}

std::ostream& operator<<(std::ostream& stream, const MatrixGroup& group)
{
    group.print(stream);

    return stream;
}

} // Close goblr
