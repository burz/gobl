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

TEST(Space, setState)
{
    Space space;
    space.setState(SpaceState::BLACK);
    EXPECT_EQ(SpaceState::BLACK, space.state());
    space.setState(SpaceState::WHITE);
    EXPECT_EQ(SpaceState::WHITE, space.state());
    space.setState(SpaceState::EMPTY);
    EXPECT_EQ(SpaceState::EMPTY, space.state());
}

TEST(Space, equals)
{
    Space space1;

    EXPECT_TRUE(space1 == space1);

    Space space2;

    EXPECT_TRUE(space1 == space2);
    EXPECT_FALSE(space1 != space2);
    space2.setState(SpaceState::BLACK);
    EXPECT_FALSE(space1 == space2);
    EXPECT_TRUE(space1 != space2);
    space2.setState(SpaceState::WHITE);
    EXPECT_FALSE(space1 == space2);
    EXPECT_TRUE(space1 != space2);
    space1.setState(SpaceState::BLACK);
    EXPECT_FALSE(space1 == space2);
    EXPECT_TRUE(space1 != space2);
    space1.setState(SpaceState::WHITE);
    EXPECT_TRUE(space1 == space2);
    EXPECT_FALSE(space1 != space2);
    space1.setState(SpaceState::BLACK);
    space2.setState(SpaceState::BLACK);
    EXPECT_TRUE(space1 == space2);
    EXPECT_FALSE(space1 != space2);
}

} // Close goblb
