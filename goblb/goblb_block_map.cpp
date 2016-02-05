// goblb_block_map.cpp

#include <goblb_block_map.h>
#include <goblb_board.h>

#include <iomanip>
#include <cassert>

namespace goblb {

void BlockMap::resetSpace(const Space::Ptr& space_p)
{
    space_p->setState(SpaceState::EMPTY);

    Map::const_iterator pos =
        d_map.find(Coordinates(space_p->i() + 1, space_p->j()));

    if(d_map.end() != pos)
    {
        pos->second->addLiberty(space_p);
    }

    pos = d_map.find(Coordinates(space_p->i() - 1, space_p->j()));

    if(d_map.end() != pos)
    {
        pos->second->addLiberty(space_p);
    }

    pos = d_map.find(Coordinates(space_p->i(), space_p->j() + 1));

    if(d_map.end() != pos)
    {
        pos->second->addLiberty(space_p);
    }

    pos = d_map.find(Coordinates(space_p->i(), space_p->j() - 1));

    if(d_map.end() != pos)
    {
        pos->second->addLiberty(space_p);
    }
}

void BlockMap::insert(const Block::Ptr& block_p)
{
    for(auto itt = block_p->members().begin()
      ; itt != block_p->members().end()
      ; ++itt)
    {
        const Space::Ptr& space_p = *itt;

        d_map.erase(Coordinates(space_p->i(), space_p->j()));

        d_map.insert(Map::value_type(
              Coordinates(space_p->i(), space_p->j())
            , block_p
        ));
    }
}

void BlockMap::remove(const Block::Ptr& block_p)
{
    for(auto itt = block_p->members().begin()
      ; itt != block_p->members().end()
      ; ++itt)
    {
        const Space::Ptr& space_p = *itt;

        d_map.erase(Coordinates(space_p->i(), space_p->j()));

        resetSpace(space_p);
    }
}

Block::Ptr BlockMap::lookup(unsigned int i, unsigned int j) const
{
    assert(i < Board::SIZE);
    assert(j < Board::SIZE);

    Block::Ptr block_p;

    Map::const_iterator pos = d_map.find(Coordinates(i, j));

    if(d_map.end() != pos)
    {
        block_p = pos->second;
    }

    return block_p;
}

void BlockMap::print(std::ostream& stream) const
{
    if(!d_map.empty())
    {
        unsigned int iMin = static_cast<unsigned int>(-1);
        unsigned int iMax = 0;
        unsigned int jMin = static_cast<unsigned int>(-1);
        unsigned int jMax = 0;

        for(auto itt = d_map.begin(); itt != d_map.end(); ++itt)
        {
            if(iMin > itt->first.first)
            {
                iMin = itt->first.first;
            }
            if(iMax < itt->first.first)
            {
                iMax = itt->first.first;
            }

            if(jMin > itt->first.second)
            {
                jMin = itt->first.second;
            }
            if(jMax < itt->first.second)
            {
                jMax = itt->first.second;
            }
        }

        for(unsigned int i = iMax; i >= iMin; --i)
        {
            stream << std::setw(2) << i << "  [";

            for(unsigned int j = jMin; j <= jMax; ++j)
            {
                Map::const_iterator pos =
                    d_map.find(Coordinates(i, j));

                if(d_map.end() != pos)
                {
                    stream << "  " << std::setw(3)
                           << pos->second->libs()
                           << (SpaceState::WHITE == pos->second->state() ? 'W' : 'B')
                           << ' ';
                }
                else
                {
                    stream << "  EMPTY";
                }
            }

            stream << " ]" << std::endl;

            if(0 == i)
            {
                break;
            }
        }

        stream << "   ";

        for(unsigned int j = jMin; j <= jMax; ++j)
        {
            stream << "     " << std::setw(2) << j;
        }
    }
}

std::ostream& operator<<(std::ostream& stream, const BlockMap& blockMap)
{
    blockMap.print(stream);

    return stream;
}

} // Close goblb
