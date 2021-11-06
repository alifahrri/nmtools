#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

#include <tuple>
#include <utility>

namespace meta = nmtools::meta;

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
}