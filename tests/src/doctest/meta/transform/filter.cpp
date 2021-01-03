#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

#include <tuple>
#include <utility>

namespace meta = nmtools::meta;

template <typename T>
using eq_one = meta::constant_eq<T,1>;

template <typename T>
using gt_one = meta::constant_gt<T,1>;

template <typename T>
using lt_one = meta::constant_lt<T,1>;

TEST_CASE("filter" * doctest::test_suite("meta"))
{
    {
        using arg_t      = std::tuple<int>;
        using expected_t = std::tuple<int>;
        using result_t   = meta::filter_t<std::is_integral,arg_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t      = std::tuple<int>;
        using expected_t = std::tuple<>;
        using result_t   = meta::filter_t<meta::is_integral_constant,arg_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t      = std::tuple<int,double,meta::ct<3>,bool,float>;
        using expected_t = std::tuple<int,bool>;
        using result_t   = meta::filter_t<std::is_integral,arg_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t      = std::tuple<int,double,meta::ct<3>,bool,float>;
        using expected_t = std::tuple<meta::ct<3>>;
        using result_t   = meta::filter_t<meta::is_integral_constant,arg_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t      = std::tuple<int,double,meta::ct<3>,bool,float>;
        using expected_t = std::tuple<double,float>;
        using result_t   = meta::filter_t<std::is_floating_point,arg_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t      = std::tuple<int,double,meta::ct<3>,bool,float>;
        using expected_t = std::tuple<int,double,bool,float>;
        using result_t   = meta::filter_t<std::is_arithmetic,arg_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t      = std::tuple<meta::ct<1>,meta::ct<3>,meta::ct<0>,meta::ct<2>,meta::ct<1>,meta::ct<4>>;
        using expected_t = std::tuple<meta::ct<1>,meta::ct<1>>;
        using result_t   = meta::filter_t<eq_one,arg_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t      = std::tuple<meta::ct<1>,meta::ct<3>,meta::ct<0>,meta::ct<2>,meta::ct<1>,meta::ct<4>>;
        using expected_t = std::tuple<meta::ct<3>,meta::ct<2>,meta::ct<4>>;
        using result_t   = meta::filter_t<gt_one,arg_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t      = std::tuple<meta::ct<1>,meta::ct<3>,meta::ct<0>,meta::ct<2>,meta::ct<1>,meta::ct<4>>;
        using expected_t = std::tuple<meta::ct<0>>;
        using result_t   = meta::filter_t<lt_one,arg_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}