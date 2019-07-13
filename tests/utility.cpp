#include <gtest/gtest.h>
#include "utility.hpp"

TEST(utility,constants) {
    namespace detail = numeric::helper::detail;
    constexpr detail::Constants<double,100,50,25,25> constants;
    static_assert(constants.values[0]==0.5);
    static_assert(constants.values[1]==0.25);
    static_assert(constants.values[2]==0.25);
}