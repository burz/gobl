// goblr_matrix_group.cpp

#include <goblr_matrix_group.h>

#include <fstream>

namespace goblr {

void MatrixGroup::readFromFile(std::ifstream& fstream)
{
    unsigned int size;
    fstream.read(
          reinterpret_cast<char*>(&size)
        , sizeof(unsigned int)
    );
    d_group.reserve(size);

    for(unsigned int i = 0; i < size; ++i)
    {
        d_group.emplace_back(new Matrix());

        d_group.back()->readFromFile(fstream);
    }
}

void MatrixGroup::writeToFile(std::ofstream& fstream) const
{
    const unsigned int size = d_group.size();
    fstream.write(
          reinterpret_cast<const char*>(&size)
        , sizeof(unsigned int)
    );

    for(unsigned int i = 0; i < size; ++i)
    {
        d_group[i]->writeToFile(fstream);
    }
}

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
