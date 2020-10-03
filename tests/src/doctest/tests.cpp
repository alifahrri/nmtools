#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "nmtools/utility/helper.hpp"
#include "testing/testing.hpp"
#include <array>
#include <vector>

namespace testing = nmtools::testing;

/**
 * @test test case for isclose
 * 
 */
TEST_CASE("nmtools::helper::isclose")
{
    auto a = std::array<double,3>{1,2,3};
    auto v = std::vector<double>{1,2,3};
    double r[3] = {1,2,3};
    auto A = std::array<std::array<double,3>,3>{{
        {1,2,3},
        {1,2,3},
        {1,2,3},
    }};
    auto V = std::vector<std::vector<double>>{{
        {1,2,3},
        {1,2,3},
        {1,2,3},
    }};
    auto t = std::make_tuple(a,v);
    auto u = std::make_tuple(v,v);
    auto T = std::make_tuple(A,V);
    auto U = std::make_tuple(V,V);

    using nmtools::helper::isclose;

    SUBCASE(testing::make_func_args("isclose",a,v).c_str())
    {
        CHECK(nmtools::helper::isclose(a,v));
    }
    SUBCASE(testing::make_func_args("isclose",t,u).c_str())
    {
        CHECK(nmtools::helper::isclose(t,u));
    }
    SUBCASE(testing::make_func_args("isclose",A,V).c_str())
    {
        CHECK(nmtools::helper::isclose(A,V));
    }
    SUBCASE(testing::make_func_args("isclose",T,U).c_str())
    {
        CHECK(nmtools::helper::isclose(T,U));
    }
}