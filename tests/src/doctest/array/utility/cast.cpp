#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/utility/cast.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nmtools::array;

TEST_CASE("cast<array>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = std::array<double,5>; 
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<vector>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = std::vector<double>;
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<fixed_vector>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = na::fixed_vector<double,5>;
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<dynamic_vector>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = na::dynamic_vector<double>;
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<fixed_ndarray>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = na::fixed_ndarray<double,5>;
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<dynamic_ndarray>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = na::dynamic_ndarray<double>;
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<array[2]>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = std::array<std::array<double,3>,2>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<array[2]>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = std::vector<std::vector<double>>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<fixed_matrix>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = na::fixed_matrix<double,2,3>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<dynamic_matrix>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = na::dynamic_matrix<double>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<fixed_ndarray>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = na::fixed_ndarray<double,2,3>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<dynamic_ndarray>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = na::dynamic_ndarray<double>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<array[3]>(double[3])" * doctest::test_suite("cast"))
{
    using dst_t = std::array<std::array<std::array<double,3>,1>,2>;
    double src[2][1][3] = {
        {
            {1,2,3}
        },
        {
            {4,5,6}
        },
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<vector[3]>(double[3])" * doctest::test_suite("cast"))
{
    using dst_t = std::vector<std::vector<std::vector<double>>>;
    double src[2][1][3] = {
        {
            {1,2,3}
        },
        {
            {4,5,6}
        },
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<fixed_ndarray>(double[3])" * doctest::test_suite("cast"))
{
    using dst_t = na::fixed_ndarray<double,2,1,3>;
    double src[2][1][3] = {
        {
            {1,2,3}
        },
        {
            {4,5,6}
        },
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<dynamic_ndarray>(double[3])" * doctest::test_suite("cast"))
{
    using dst_t = na::dynamic_ndarray<double>;
    double src[2][1][3] = {
        {
            {1,2,3}
        },
        {
            {4,5,6}
        },
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<array>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = std::array<float,5>; 
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<vector>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = std::vector<float>;
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<fixed_vector>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = na::fixed_vector<float,5>;
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<dynamic_vector>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = na::dynamic_vector<float>;
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<fixed_ndarray>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = na::fixed_ndarray<float,5>;
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<dynamic_ndarray>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = na::dynamic_ndarray<float>;
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<array[2]>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = std::array<std::array<float,3>,2>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<array[2]>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = std::vector<std::vector<float>>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<fixed_matrix>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = na::fixed_matrix<float,2,3>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<dynamic_matrix>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = na::dynamic_matrix<float>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<fixed_ndarray>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = na::fixed_ndarray<float,2,3>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<dynamic_ndarray>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = na::dynamic_ndarray<float>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<array[3]>(double[3])" * doctest::test_suite("cast"))
{
    using dst_t = std::array<std::array<std::array<float,3>,1>,2>;
    double src[2][1][3] = {
        {
            {1,2,3}
        },
        {
            {4,5,6}
        },
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<vector[3]>(double[3])" * doctest::test_suite("cast"))
{
    using dst_t = std::vector<std::vector<std::vector<float>>>;
    double src[2][1][3] = {
        {
            {1,2,3}
        },
        {
            {4,5,6}
        },
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<fixed_ndarray>(double[3])" * doctest::test_suite("cast"))
{
    using dst_t = na::fixed_ndarray<float,2,1,3>;
    double src[2][1][3] = {
        {
            {1,2,3}
        },
        {
            {4,5,6}
        },
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<dynamic_ndarray>(double[3])" * doctest::test_suite("cast"))
{
    using dst_t = na::dynamic_ndarray<float>;
    double src[2][1][3] = {
        {
            {1,2,3}
        },
        {
            {4,5,6}
        },
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}