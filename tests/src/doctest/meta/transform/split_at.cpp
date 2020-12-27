#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <utility>

namespace meta = nmtools::meta;

TEST_CASE("split_at" * doctest::test_suite("meta"))
{
    {
        using arg_t      = std::tuple<int,double>;
        using result     = meta::split_at<arg_t,0>;
        using result_t   = meta::type_t<result>;
        using first_t    = meta::first_t<result>;
        using second_t   = meta::second_t<result>;
        using expected_t = arg_t;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
        STATIC_CHECK_IS_SAME( first_t,  void );
        STATIC_CHECK_IS_SAME( second_t, void );
    }
    {
        using arg_t      = std::tuple<int,double,size_t>;
        using result_t   = meta::split_at_t<arg_t,0>;
        using expected_t = arg_t;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t      = std::tuple<int,double,size_t>;
        using result_t   = meta::split_at_t<arg_t,1>;
        using expected_t = std::pair<std::tuple<int>,std::tuple<double,size_t>>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t      = std::tuple<int,double,size_t>;
        using result_t   = meta::split_at_t<arg_t,2>;
        using expected_t = std::pair<std::tuple<int,double>,std::tuple<size_t>>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t      = std::tuple<int,double,size_t,int,size_t,double>;
        using result_t   = meta::split_at_t<arg_t,3>;
        using expected_t = std::pair<std::tuple<int,double,size_t>,std::tuple<int,size_t,double>>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t = std::tuple<meta::ct<1>,meta::ct<3>,meta::ct<7>>;
        using split_type = meta::split_at<arg_t,2>;
        using fst = meta::first_t<split_type>;
        using snd = meta::second_t<split_type>;
        using result_t   = meta::type_t<split_type>;
        using first_t    = std::tuple<meta::ct<1>,meta::ct<3>>;
        using second_t   = std::tuple<meta::ct<7>>;
        using expected_t = std::pair<first_t,second_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
        STATIC_CHECK_IS_SAME( fst, first_t );
        STATIC_CHECK_IS_SAME( snd, second_t );
    }
}