//  :copyright: (c) 2017 Alex Huszagh.
//  :license: BSD-like or MIT, see LICENSE.md for more details.

#include <gtest/gtest.h>
#include <wtl/string.hpp>

// DATA
// ----

std::string STR = {0, 84, 104, 105, 115, 32, 105, 115, 32, 100, 97, 116, 97, 10};
std::string NONNULL = {84, 104, 105, 115, 32, 105, 115, 32, 100, 97, 116, 97, 10};

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

    str += 5;
    EXPECT_EQ(str.size(), 9);

    str -= 5;
    EXPECT_EQ(str.size(), 14);

    str += 20;
    EXPECT_EQ(str.size(), 0);
}


TEST(string, operations)
{
    wtl::string str(STR);
    wtl::string null;
    wtl::string non_null(NONNULL);

    // find
    EXPECT_EQ(str.find(wtl::string("is")), 3);
    EXPECT_EQ(str.find("is"), 3);
    EXPECT_EQ(str.find(std::string("is")), 3);
    EXPECT_EQ(str.find("is", 0, 2), 3);
    EXPECT_EQ(str.find('i'), 3);

    // find_first_of
    EXPECT_EQ(str.find_first_of(wtl::string("hsi")), 2);
    EXPECT_EQ(str.find_first_of("hsi"), 2);
    EXPECT_EQ(str.find_first_of(std::string("hsi")), 2);
    EXPECT_EQ(str.find_first_of("hsi", 0, 3), 2);
    EXPECT_EQ(str.find_first_of('h'), 2);

    EXPECT_EQ(str.find_first_of(wtl::string("x")), wtl::string::npos);
    EXPECT_EQ(str.find_first_of("x"), wtl::string::npos);
    EXPECT_EQ(str.find_first_of(std::string("x")), wtl::string::npos);
    EXPECT_EQ(str.find_first_of("x", 0, 1), wtl::string::npos);
    EXPECT_EQ(str.find_first_of('x'), wtl::string::npos);

    // find_first_not_of
    EXPECT_EQ(non_null.find_first_not_of(wtl::string("Tish")), 4);
    EXPECT_EQ(non_null.find_first_not_of("Tish"), 4);
    EXPECT_EQ(non_null.find_first_not_of(std::string("Tish")), 4);
    EXPECT_EQ(non_null.find_first_not_of("Tish", 0, 4), 4);
    EXPECT_EQ(non_null.find_first_not_of('T'), 1);

    EXPECT_EQ(non_null.find_first_not_of(wtl::string("Thisdta \n")), wtl::string::npos);
    EXPECT_EQ(non_null.find_first_not_of("Thisdta \n"), wtl::string::npos);
    EXPECT_EQ(non_null.find_first_not_of(std::string("Thisdta \n")), wtl::string::npos);
    EXPECT_EQ(non_null.find_first_not_of("Thisdta \n", 0, 9), wtl::string::npos);

    // rfind
    EXPECT_EQ(str.rfind(wtl::string("is")), 6);
    EXPECT_EQ(str.rfind("is"), 6);
    EXPECT_EQ(str.rfind(std::string("is")), 6);
    EXPECT_EQ(str.rfind("is", 0, 2), 6);
    EXPECT_EQ(str.rfind('i'), 6);

    EXPECT_EQ(str.rfind(wtl::string("isx")), wtl::string::npos);
    EXPECT_EQ(str.rfind("isx"), wtl::string::npos);
    EXPECT_EQ(str.rfind(std::string("isx")), wtl::string::npos);
    EXPECT_EQ(str.rfind("isx", 0, 3), wtl::string::npos);
    EXPECT_EQ(str.rfind('x'), wtl::string::npos);

    EXPECT_EQ(null.rfind('i'), wtl::string::npos);

    // find_last_of
    EXPECT_EQ(str.find_last_of(wtl::string("hsi")), 7);
    EXPECT_EQ(str.find_last_of("hsi"), 7);
    EXPECT_EQ(str.find_last_of(std::string("hsi")), 7);
    EXPECT_EQ(str.find_last_of("hsi", 0, 3), 7);
    EXPECT_EQ(str.find_last_of('h'), 2);

    EXPECT_EQ(str.find_last_of(wtl::string("x")), wtl::string::npos);
    EXPECT_EQ(str.find_last_of("x"), wtl::string::npos);
    EXPECT_EQ(str.find_last_of(std::string("x")), wtl::string::npos);
    EXPECT_EQ(str.find_last_of("x", 0, 1), wtl::string::npos);
    EXPECT_EQ(str.find_last_of('x'), wtl::string::npos);

    // find_last_not_of
    EXPECT_EQ(non_null.find_last_not_of(wtl::string("dat\n")), 7);
    EXPECT_EQ(non_null.find_last_not_of("dat\n"), 7);
    EXPECT_EQ(non_null.find_last_not_of(std::string("dat\n")), 7);
    EXPECT_EQ(non_null.find_last_not_of("dat\n", 0, 4), 7);
    EXPECT_EQ(non_null.find_last_not_of('\n'), 11);

    EXPECT_EQ(non_null.find_last_not_of(wtl::string("Thisdta \n")), wtl::string::npos);
    EXPECT_EQ(non_null.find_last_not_of("Thisdta \n"), wtl::string::npos);
    EXPECT_EQ(non_null.find_last_not_of(std::string("Thisdta \n")), wtl::string::npos);
    EXPECT_EQ(non_null.find_last_not_of("Thisdta \n", 0, 9), wtl::string::npos);
}


TEST(string, conversions)
{
    wtl::string str(STR);
    wtl::string other;
    EXPECT_TRUE(bool(str));
    EXPECT_FALSE(bool(other));

    EXPECT_EQ(std::string(str), STR);
    EXPECT_EQ(std::string(other), "");
}
