// goblr_generator.cpp

#include <goblr_generator.h>

#include <set>

namespace goblr {

Matrix::Ptr Generator::ko(const goblb::Board& board)
{
    Matrix::Ptr matrix_p(new Matrix());

    const goblb::Space::Ptr& ko_p = board.ko();

    if(ko_p)
    {
        matrix_p->set(ko_p->i(), ko_p->j(), 1.0);
    }

    return matrix_p;
}

MatrixGroup::Ptr Generator::liberties(
      const goblb::Board& board
    , goblb::SpaceState::Value perspective
    , unsigned int levels
)
{
    MatrixGroup::Ptr matrixGroup_p(new MatrixGroup());

    for(unsigned int i = 0; i < levels * 2; ++i)
    {
        matrixGroup_p->push(Matrix::Ptr(new Matrix(board.size())));
    }

    std::set<goblb::Block::Ptr> visitedBlocks;

    for(unsigned int i = 0; i < board.size(); ++i)
    {
        for(unsigned int j = 0; j < board.size(); ++j)
        {
            goblb::Block::Ptr block_p = board.block(i, j);

            if(!block_p || visitedBlocks.end() != visitedBlocks.find(block_p))
            {
                continue;
            }

            unsigned int pos;

            if(perspective == block_p->state())
            {
                pos = 0;
            }
            else
            {
                pos = levels;
            }

            if(block_p->libs() > levels)
            {
                pos += levels - 1;
            }
            else
            {
                pos += block_p->libs() - 1;
            }

            for(auto itt = block_p->members().begin()
              ; itt != block_p->members().end()
              ; ++itt)
            {
                matrixGroup_p->get(pos)->set((*itt)->i(), (*itt)->j(), 1.0);
            }

            visitedBlocks.insert(block_p);
        }
    }

    return matrixGroup_p;
}

} // Close goblr
