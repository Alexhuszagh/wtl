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


TEST(string, swap)
{
    wtl::string str(STR);
    wtl::string other;
    EXPECT_EQ(str.size(), 14);
    EXPECT_EQ(other.size(), 0);

    std::swap(str, other);
    EXPECT_EQ(str.size(), 0);
    EXPECT_EQ(other.size(), 14);

    wtl::swap(str, other);
    EXPECT_EQ(str.size(), 14);
    EXPECT_EQ(other.size(), 0);
}


TEST(string, relational)
{
    wtl::string str(STR);
    wtl::string other;

    // eq
    EXPECT_TRUE(str == str);
    EXPECT_FALSE(str == other);
    EXPECT_TRUE(str == STR);
    EXPECT_FALSE(str == str.data());
    EXPECT_FALSE(str.data() == str);

    // ne
    EXPECT_FALSE(str != str);
    EXPECT_TRUE(str != other);
    EXPECT_FALSE(str != STR);
    EXPECT_TRUE(str != str.data());
    EXPECT_TRUE(str.data() != str);

    // lt
    EXPECT_FALSE(str < str);
    EXPECT_FALSE(str < other);
    EXPECT_FALSE(str < STR);
    EXPECT_FALSE(str < str.data());
    EXPECT_TRUE(str.data() < str);

    // le
    EXPECT_TRUE(str <= str);
    EXPECT_FALSE(str <= other);
    EXPECT_TRUE(str <= STR);
    EXPECT_FALSE(str <= str.data());
    EXPECT_TRUE(str.data() <= str);

    // gt
    EXPECT_FALSE(str > str);
    EXPECT_TRUE(str > other);
    EXPECT_FALSE(str > STR);
    EXPECT_TRUE(str > str.data());
    EXPECT_FALSE(str.data() > str);

    // ge
    EXPECT_TRUE(str >= str);
    EXPECT_TRUE(str >= other);
    EXPECT_TRUE(str >= STR);
    EXPECT_TRUE(str >= str.data());
    EXPECT_FALSE(str.data() >= str);
}


TEST(string, iterator)
{
    wtl::string str(STR);
    std::string reversed(STR.rbegin(), STR.rend());
    EXPECT_EQ(std::string(str.begin(), str.end()), STR);
    EXPECT_EQ(std::string(str.rbegin(), str.rend()), reversed);
}


TEST(string, capacity)
{
    wtl::string str(STR);
    wtl::string other;

    EXPECT_EQ(str.size(), 14);
    EXPECT_EQ(other.size(), 0);

    EXPECT_EQ(str.length(), 14);
    EXPECT_EQ(other.length(), 0);

    EXPECT_FALSE(str.empty());
    EXPECT_TRUE(other.empty());
}


TEST(string, element)
{
    wtl::string str(STR);

    EXPECT_EQ(str[0], '\0');
    EXPECT_EQ(str.at(0), '\0');
    EXPECT_EQ(str[1], 'T');
    EXPECT_EQ(str.at(1), 'T');
    EXPECT_EQ(str.front(), '\0');
    EXPECT_EQ(str.back(), '\n');
}


TEST(string, modifier)
{
    wtl::string str;

    str.assign(STR);
    EXPECT_EQ(str.size(), 14);

    str.assign(STR, 4, 10);
    EXPECT_EQ(str.size(), 10);

    str.assign(STR.data());
    EXPECT_EQ(str.size(), 0);

    str.assign(STR.data());
    EXPECT_EQ(str.size(), 0);

    str.assign(STR.data(), STR.size());
    EXPECT_EQ(str.size(), 14);

    str.assign(nullptr);
    EXPECT_EQ(str.size(), 0);
}


TEST(string, operators)
{
    wtl::string str(STR);
    ++str;
    EXPECT_EQ(str.size(), 13);

    --str;
    EXPECT_EQ(str.size(), 14);
}


TEST(string, operations)
{}


TEST(string, conversions)
{
    wtl::string str(STR);
    wtl::string other;
    EXPECT_TRUE(bool(str));
    EXPECT_FALSE(bool(other));

    EXPECT_EQ(std::string(str), STR);
    EXPECT_EQ(std::string(other), "");
}
