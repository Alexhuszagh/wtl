/*
 *  :author: The Regents of the University of California.
 *  :license: Public Domain
 *
 *  This file has been placed in the public domain.
 *  There are no restrictions on its use.
 */

#include <gtest/gtest.h>
#include <wtl/string.hpp>

// DATA
// ----

std::string STR = {0, 84, 104, 105, 115, 32, 105, 115, 32, 100, 97, 116, 97, 10};


// TESTS
// -----


TEST(string, constructors)
{
    wtl::string str(STR);
    wtl::string other;
    EXPECT_EQ(str.size(), 14);

    str = wtl::string(STR.data());
    EXPECT_EQ(str.size(), 0);

    str = wtl::string(STR.data(), STR.size());
    EXPECT_EQ(str.size(), 14);

    str = std::move(other);
    EXPECT_EQ(str.size(), 0);
    EXPECT_EQ(other.size(), 14);

    str = other;
    EXPECT_EQ(str.size(), 14);
    EXPECT_EQ(other.size(), 14);
}
