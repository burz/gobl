// goblb_space_state.t.cpp

#include <goblb_space_state.h>

#include <gtest/gtest.h>

namespace goblb {

TEST(SpaceState, toString)
{
    EXPECT_STREQ("EMPTY", SpaceState::toString(SpaceState::EMPTY));
    EXPECT_STREQ("BLACK", SpaceState::toString(SpaceState::BLACK));
    EXPECT_STREQ("WHITE", SpaceState::toString(SpaceState::WHITE));
}

} // Close goblb
