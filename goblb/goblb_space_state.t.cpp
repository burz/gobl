// goblb_space_state.t.cpp

#include <goblb_space_state.h>

#include <gtest/gtest.h>

namespace goblb {

TEST(SpaceState, toString)
{
    EXPECT_STREQ("EMPTY", SpaceState::toString(SpaceState::EMPTY).c_str());
    EXPECT_STREQ("BLACK", SpaceState::toString(SpaceState::BLACK).c_str());
    EXPECT_STREQ("WHITE", SpaceState::toString(SpaceState::WHITE).c_str());
}

} // Close goblb
