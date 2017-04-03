//  :copyright: (c) 2017 Alex Huszagh.
//  :license: BSD-like or MIT, see LICENSE.md for more details.

#include <gtest/gtest.h>
#include <wtl/vector.hpp>

// DATA
// ----

std::vector<int> VEC = {0, 1, 2, 3, 4, 5};
std::vector<int> EMPTY;

// TESTS
// -----


TEST(vector, constructors)
{
    wtl::vector<int> vector(VEC);
    wtl::vector<int> other;
    EXPECT_EQ(vector.size(), 6);

    vector = wtl::vector<int>(VEC);
    EXPECT_EQ(vector.size(), 6);

    vector = wtl::vector<int>(VEC.data(), VEC.size());
    EXPECT_EQ(vector.size(), 6);

    vector = std::move(other);
    EXPECT_EQ(vector.size(), 0);
    EXPECT_EQ(other.size(), 6);

    vector = other;
    EXPECT_EQ(vector.size(), 6);
    EXPECT_EQ(other.size(), 6);
}


TEST(vector, swap)
{
    wtl::vector<int> vector(VEC);
    wtl::vector<int> other;

    EXPECT_EQ(vector.size(), 6);
    EXPECT_EQ(other.size(), 0);

    std::swap(vector, other);
    EXPECT_EQ(vector.size(), 0);
    EXPECT_EQ(other.size(), 6);

    wtl::swap(vector, other);
    EXPECT_EQ(vector.size(), 6);
    EXPECT_EQ(other.size(), 0);
}


TEST(vector, relational)
{
    wtl::vector<int> vector(VEC);
    wtl::vector<int> other;

    // eq
    EXPECT_TRUE(vector == vector);
    EXPECT_FALSE(vector == other);

    // ne
    EXPECT_FALSE(vector != vector);
    EXPECT_TRUE(vector != other);

    // lt
    EXPECT_FALSE(vector < vector);
    EXPECT_FALSE(vector < other);

    // le
    EXPECT_TRUE(vector <= vector);
    EXPECT_FALSE(vector <= other);

    // gt
    EXPECT_FALSE(vector > vector);
    EXPECT_TRUE(vector > other);

    // ge
    EXPECT_TRUE(vector >= vector);
    EXPECT_TRUE(vector >= other);
}


TEST(vector, iterator)
{
    wtl::vector<int> vector(VEC);
    std::vector<int> reversed(VEC.rbegin(), VEC.rend());
    EXPECT_EQ(std::vector<int>(vector.begin(), vector.end()), VEC);
    EXPECT_EQ(std::vector<int>(vector.rbegin(), vector.rend()), reversed);
}


TEST(vector, capacity)
{
    wtl::vector<int> vector(VEC);
    wtl::vector<int> other;

    EXPECT_EQ(vector.size(), 6);
    EXPECT_EQ(other.size(), 0);

    EXPECT_FALSE(vector.empty());
    EXPECT_TRUE(other.empty());
}


TEST(vector, element)
{
    wtl::vector<int> vector(VEC);

    EXPECT_EQ(vector[0], 0);
    EXPECT_EQ(vector.at(0), 0);
    EXPECT_EQ(vector[1], 1);
    EXPECT_EQ(vector.at(1), 1);
    EXPECT_EQ(vector.front(), 0);
    EXPECT_EQ(vector.back(), 5);
}


TEST(vector, modifier)
{
    wtl::vector<int> vector(VEC);
    wtl::vector<int> other;

    EXPECT_EQ(vector.size(), 6);
    EXPECT_EQ(other.size(), 0);

    vector.swap(other);
    EXPECT_EQ(vector.size(), 0);
    EXPECT_EQ(other.size(), 6);
}


TEST(vector, conversions)
{
    wtl::vector<int> vector(VEC);
    wtl::vector<int> other;

    EXPECT_TRUE(bool(vector));
    EXPECT_FALSE(bool(other));

    EXPECT_EQ(std::vector<int>(vector), VEC);
    EXPECT_EQ(std::vector<int>(other), EMPTY);
}
