#include <gtest/gtest.h>
#include "utility.hpp"

TEST(utility, constants) {
    namespace detail = numeric::helper::detail;
    constexpr detail::Constants<double,100,50,25,25> constants;
    static_assert(constants.values[0]==0.5);
    static_assert(constants.values[1]==0.25);
    static_assert(constants.values[2]==0.25);
}

TEST(utility, append_array) {
    namespace hp = numeric::helper;
    std::array<double,4> a{ 1., 2., 3., 4. };
    auto b = hp::append(a, 5.);
    static_assert( std::is_same_v<std::array<double,5>,decltype(b)> );
    EXPECT_EQ(b[4],5.);
}

TEST(utility, append_vector) {
    namespace hp = numeric::helper;
    std::vector<double> a{ 1., 2., 3., 4. };
    auto b = hp::append(a, 5.);
    static_assert( std::is_same_v<std::vector<double>,decltype(b)> );
    EXPECT_EQ(b.size(),5);
    EXPECT_EQ(b[4],5.);
}