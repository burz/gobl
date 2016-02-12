// gobls_sgf_iterator.t.cpp

#include <gobls_sgf_iterator.h>

#include <gtest/gtest.h>

namespace gobls {

TEST(SgfIterator, constructor)
{
    SgfIterator::Strings strings;
    SgfIterator itt(strings);
    EXPECT_EQ(0u, itt.succeeded());
    EXPECT_EQ(0u, itt.failed());

    EXPECT_FALSE(itt.next());
    EXPECT_EQ(0u, itt.succeeded());
    EXPECT_EQ(0u, itt.failed());
}

TEST(SgfIterator, nextValueSuccess)
{
    SgfIterator::Strings strings;
    strings.push_back("(;A[0])");

    SgfIterator itt(strings);
    EXPECT_EQ(0u, itt.succeeded());
    EXPECT_EQ(0u, itt.failed());

    EXPECT_TRUE(itt.next());
    EXPECT_EQ(1u, itt.succeeded());
    EXPECT_EQ(0u, itt.failed());

    Sgf::Ptr sgf_p = itt.value();

    std::cout << *sgf_p << std::endl;

    EXPECT_EQ("0", sgf_p->lookup("A"));

    EXPECT_FALSE(itt.next());
    EXPECT_EQ(1u, itt.succeeded());
    EXPECT_EQ(0u, itt.failed());
}

TEST(SgfIterator, nextValueFailure)
{
    SgfIterator::Strings strings;
    strings.push_back("(;A[0]lololol ololol\n");

    SgfIterator itt(strings);

    EXPECT_EQ(0u, itt.succeeded());
    EXPECT_EQ(0u, itt.failed());

    EXPECT_FALSE(itt.next());
    EXPECT_EQ(0u, itt.succeeded());
    EXPECT_EQ(1u, itt.failed());
}

TEST(SgfIterator, nextValueSuccessFailureSuccess)
{
    SgfIterator::Strings strings;
    strings.push_back("(;A[0])");
    strings.push_back("(;A[1]; lol olol[\\]ol\n");
    strings.push_back("(;A[2])");

    SgfIterator itt(strings);

    EXPECT_EQ(0u, itt.succeeded());
    EXPECT_EQ(0u, itt.failed());

    EXPECT_TRUE(itt.next());
    EXPECT_EQ(1u, itt.succeeded());
    EXPECT_EQ(0u, itt.failed());

    Sgf::Ptr sgf_p = itt.value();
    std::cout << *sgf_p << std::endl;

    EXPECT_EQ("0", sgf_p->lookup("A"));

    EXPECT_TRUE(itt.next());
    EXPECT_EQ(2u, itt.succeeded());
    EXPECT_EQ(1u, itt.failed());

    sgf_p = itt.value();
    std::cout << *sgf_p << std::endl;

    EXPECT_EQ("2", sgf_p->lookup("A"));

    EXPECT_FALSE(itt.next());
    EXPECT_EQ(2u, itt.succeeded());
    EXPECT_EQ(1u, itt.failed());
}

} // Close gobls
