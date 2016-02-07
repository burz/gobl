// goblr_generator.h
#ifndef INCLUDED_GOBLR_GENERATOR
#define INCLUDED_GOBLR_GENERATOR

#ifndef INCLUDED_GOBLB_BOARD
#include <goblb_board.h>
#endif

#ifndef INCLUDED_GOBLR_MATRIX
#include <goblr_matrix.h>
#endif

#ifndef INCLUDED_GOBLR_MATRIX_GROUP
#include <goblr_matrix_group.h>
#endif

namespace goblr {

class Generator
{
  public:
    // CLASS METHODS
    static Matrix::Ptr ko(const goblb::Board& board);

    static MatrixGroup::Ptr liberties(
          const goblb::Board& board
        , goblb::SpaceState::Value perspective
        , unsigned int levels
    );

    static MatrixGroup::Ptr representation(
          const goblb::Board& board
        , goblb::SpaceState::Value perspective
        , unsigned int levels
    );

  private:
    // NOT IMPLEMENTED
    Generator();
};

// INLINES
inline
MatrixGroup::Ptr Generator::representation(
      const goblb::Board& board
    , goblb::SpaceState::Value perspective
    , unsigned int levels
)
{
    MatrixGroup::Ptr matrixGroup_p = liberties(board, perspective, levels);

    matrixGroup_p->push(ko(board));

    return matrixGroup_p;
}

} // Close goblr

#endif
