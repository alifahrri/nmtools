#include <gtest/gtest.h>
#include "ode.hpp"

namespace ode = numeric::ode;

TEST(rk_helper,constants) {
    namespace detail = numeric::helper::detail;

    constexpr detail::Constants<double,100,50,25,25> constants;
    ASSERT_EQ(constants.values[0],0.5);
    ASSERT_EQ(constants.values[1],0.25);
    ASSERT_EQ(constants.values[2],0.25);
}