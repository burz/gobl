// goblb_space.t.cpp

#include <goblb_space.h>

#include <gtest/gtest.h>

namespace goblb {

TEST(Space, constructor)
{
    {
        Space space;
        EXPECT_EQ(SpaceState::EMPTY, space.state());
    }
    {
        Space space(SpaceState::EMPTY);
        EXPECT_EQ(SpaceState::EMPTY, space.state());
    }
    {
        Space space(SpaceState::BLACK);
        EXPECT_EQ(SpaceState::BLACK, space.state());
    }
    {
        Space space(SpaceState::WHITE);
        EXPECT_EQ(SpaceState::WHITE, space.state());
    }
}

} // Close goblb
