#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/utility/clone.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nmtools::array;

TEST_CASE("clone(double[])" * doctest::test_suite("clone"))
{
    double a[5] = {1,2,3,4,5};
    using res_t = std::array<double,5>;
    auto res = nm::clone(a);
    STATIC_CHECK_IS_SAME( decltype(res), res_t );
    NMTOOLS_ASSERT_CLOSE( res, a );
}

TEST_CASE("clone(array)" * doctest::test_suite("clone"))
{
    auto a = std::array{1.,2.,3.,4.,5.};
    using res_t = std::array<double,5>;
    auto res = nm::clone(a);
    STATIC_CHECK_IS_SAME( decltype(res), res_t );
    NMTOOLS_ASSERT_CLOSE( res, a );
}

TEST_CASE("clone(vector)" * doctest::test_suite("clone"))
{
    auto a = std::vector{1.,2.,3.,4.,5.};
    using res_t = std::vector<double>;
    auto res = nm::clone(a);
    STATIC_CHECK_IS_SAME( decltype(res), res_t );
    NMTOOLS_ASSERT_CLOSE( res, a );
}

TEST_CASE("clone(fixed_vector)" * doctest::test_suite("clone"))
{
    auto a = na::fixed_vector({1.,2.,3.,4.,5.});
    using res_t = na::fixed_vector<double,5>;
    auto res = nm::clone(a);
    STATIC_CHECK_IS_SAME( decltype(res), res_t );
    NMTOOLS_ASSERT_CLOSE( res, a );
}

TEST_CASE("clone(dynamic_vector)" * doctest::test_suite("clone"))
{
    auto a = na::dynamic_vector({1.,2.,3.,4.,5.});
    using res_t = na::dynamic_vector<double>;
    auto res = nm::clone(a);
    STATIC_CHECK_IS_SAME( decltype(res), res_t );
    NMTOOLS_ASSERT_CLOSE( res, a );
}

TEST_CASE("clone(fixed_ndarray)" * doctest::test_suite("clone"))
{
    auto a = na::fixed_ndarray({1.,2.,3.,4.,5.});
    using res_t = na::fixed_ndarray<double,5>;
    auto res = nm::clone(a);
    STATIC_CHECK_IS_SAME( decltype(res), res_t );
    NMTOOLS_ASSERT_CLOSE( res, a );
}

TEST_CASE("clone(dynamic_ndarray)" * doctest::test_suite("clone"))
{
    auto a = na::dynamic_ndarray({1.,2.,3.,4.,5.});
    using res_t = na::dynamic_ndarray<double>;
    auto res = nm::clone(a);
    STATIC_CHECK_IS_SAME( decltype(res), res_t );
    NMTOOLS_ASSERT_CLOSE( res, a );
}