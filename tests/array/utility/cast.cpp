#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/utility/cast.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nmtools::array;

TEST_CASE("cast<array>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = nmtools_array<double,5>; 
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<float>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = float;
    using expected_t = nmtools_array<dst_t,5>;
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<bool>(bool[])" * doctest::test_suite("cast"))
{
    using dst_t = bool;
    using expected_t = nmtools_array<dst_t,5>;
    bool src[5] = {true,false,true,false,true};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<bool>(bool[])" * doctest::test_suite("cast"))
{
    using dst_t = bool;
    using expected_t = nmtools_array<dst_t,5>;
    bool src[5] = {true,false,true,false,true};
    auto res = nm::cast<expected_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<vector>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = nmtools_list<double>;
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<float>(vector)" * doctest::test_suite("cast"))
{
    using src_t = nmtools_list<double>;
    using dst_t = float;
    using expected_t = nmtools_list<dst_t>;
    auto src = src_t{1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<vector>(bool[])" * doctest::test_suite("cast"))
{
    using dst_t = nmtools_list<bool>;
    bool src[5] = {true,false,true,false,true};
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

TEST_CASE("cast<float>(fixed_ndarray)" * doctest::test_suite("cast"))
{
    using src_t = na::fixed_ndarray<double,5>;
    using dst_t = float;
    using expected_t = na::fixed_ndarray<dst_t,5>;
    auto src = src_t{{1,2,3,4,5}};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
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

TEST_CASE("cast<float>(dynamic_ndarray)" * doctest::test_suite("cast"))
{
    using src_t = na::dynamic_ndarray<double>;
    using dst_t = float;
    using expected_t = na::dynamic_ndarray<dst_t>;
    auto src = src_t({1.,2.,3.,4.,5.});
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<array[2]>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = nmtools_array<nmtools_array<double,3>,2>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<float>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = float;
    using expected_t = nmtools_array<nmtools_array<dst_t,3>,2>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

#if 0
TEST_CASE("cast<array[2]>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = nmtools_list<nmtools_list<double>>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<float>(vector[2])" * doctest::test_suite("cast"))
{
    using src_t = nmtools_list<nmtools_list<double>>;
    using dst_t = float;
    using expected_t = nmtools_list<nmtools_list<dst_t>>;
    auto src = src_t{
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}
#endif

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

TEST_CASE("cast<float>(fixed_ndarray[2])" * doctest::test_suite("cast"))
{
    using src_t = na::fixed_ndarray<double,2,3>;
    using dst_t = float;
    using expected_t = na::fixed_ndarray<dst_t,2,3>;
    auto src = src_t{{
        {1,2,3},
        {4,5,6},
    }};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
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

TEST_CASE("cast<float>(dynamic_ndarray[2])" * doctest::test_suite("cast"))
{
    using src_t = na::dynamic_ndarray<double>;
    using dst_t = float;
    using expected_t = na::dynamic_ndarray<dst_t>;
    auto src = src_t({
        {1.,2.,3.},
        {4.,5.,6.},
    });
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<array[3]>(double[3])" * doctest::test_suite("cast"))
{
    using dst_t = nmtools_array<nmtools_array<nmtools_array<double,3>,1>,2>;
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

TEST_CASE("cast<float>(double[3])" * doctest::test_suite("cast"))
{
    using dst_t = float;
    using expected_t = nmtools_array<nmtools_array<nmtools_array<dst_t,3>,1>,2>;
    double src[2][1][3] = {
        {
            {1,2,3}
        },
        {
            {4,5,6}
        },
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

#if 0
TEST_CASE("cast<vector[3]>(double[3])" * doctest::test_suite("cast"))
{
    using dst_t = nmtools_list<nmtools_list<nmtools_list<double>>>;
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

TEST_CASE("cast<float>(vector[3])" * doctest::test_suite("cast"))
{
    using src_t = nmtools_list<nmtools_list<nmtools_list<double>>>;
    using dst_t = float;
    using expected_t = nmtools_list<nmtools_list<nmtools_list<dst_t>>>;
    auto src = src_t{
        {
            {1,2,3}
        },
        {
            {4,5,6}
        },
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}
#endif

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

TEST_CASE("cast<float>(fixed_ndarray[3])" * doctest::test_suite("cast"))
{
    using src_t = na::fixed_ndarray<double,2,1,3>;
    using dst_t = float;
    using expected_t = na::fixed_ndarray<dst_t,2,1,3>;
    auto src = src_t{{
        {
            {1,2,3}
        },
        {
            {4,5,6}
        },
    }};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
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

TEST_CASE("cast<float>(dynamic_ndarray[3])" * doctest::test_suite("cast"))
{
    using src_t = na::dynamic_ndarray<double>;
    using dst_t = float;
    using expected_t = na::dynamic_ndarray<dst_t>;
    auto src = src_t({
        {
            {1.,2.,3.}
        },
        {
            {4.,5.,6.}
        },
    });
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), expected_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<array>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = nmtools_array<float,5>; 
    double src[5] = {1,2,3,4,5};
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

TEST_CASE("cast<vector>(double[])" * doctest::test_suite("cast"))
{
    using dst_t = nmtools_list<float>;
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
    using dst_t = nmtools_array<nmtools_array<float,3>,2>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}

// TODO: disable nested vector support
#if 0
TEST_CASE("cast<array[2]>(double[2])" * doctest::test_suite("cast"))
{
    using dst_t = nmtools_list<nmtools_list<float>>;
    double src[2][3] = {
        {1,2,3},
        {4,5,6},
    };
    auto res = nm::cast<dst_t>(src);
    STATIC_CHECK_IS_SAME( decltype(res), dst_t );
    NMTOOLS_ASSERT_CLOSE( res, src );
}
#endif

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
    using dst_t = nmtools_array<nmtools_array<nmtools_array<float,3>,1>,2>;
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

#if 0
TEST_CASE("cast<vector[3]>(double[3])" * doctest::test_suite("cast"))
{
    using dst_t = nmtools_list<nmtools_list<nmtools_list<float>>>;
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
#endif

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