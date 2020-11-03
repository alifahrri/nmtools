#include <gtest/gtest.h>
#include "nmtools/utility.hpp"

TEST(utility, constants) {
    namespace detail = nmtools::helper::detail;
    constexpr detail::Constants<double,100,50,25,25> constants;
    static_assert(constants.values[0]==0.5);
    static_assert(constants.values[1]==0.25);
    static_assert(constants.values[2]==0.25);
}

TEST(traits, is_callable) {
    namespace nm = nmtools;
    auto f1 = [](double) {};
    auto f2 = [](double,double) {};
    static_assert( nm::meta::is_callable<decltype(f1),double>::value);
    static_assert(!nm::meta::is_callable<decltype(f1),double,double>::value);
    static_assert( nm::meta::is_callable<decltype(f2),double,double>::value);
    static_assert(!nm::meta::is_callable<decltype(f2),double>::value);
}