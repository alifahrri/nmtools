#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

#include <tuple>
#include <ratio>
#include <utility>

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("reduce(add)" * doctest::test_suite("meta"))
{
    {
        using arg_t = std::tuple<meta::ct<1>,meta::ct<3>>;
        using result_t = meta::apply_reduce_t<meta::add,arg_t>;
        using expected_t = meta::ct<4>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t = std::tuple<meta::ct<1>,meta::ct<3>,meta::ct<7>>;
        using result_t = meta::apply_reduce_t<meta::add,arg_t>;
        using expected_t = meta::ct<11>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t = std::tuple<meta::ct<1>,std::ratio<1,3>,meta::ct<2>>;
        using result_t = meta::apply_reduce_t<meta::add,arg_t>;
        using expected_t = std::ratio<10,3>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}

TEST_CASE("reduce(mul)" * doctest::test_suite("meta"))
{
    {
        using arg_t = std::tuple<meta::ct<1>,meta::ct<3>>;
        using result_t = meta::apply_reduce_t<meta::mul,arg_t>;
        using expected_t = meta::ct<3>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t = std::tuple<meta::ct<1>,meta::ct<3>,meta::ct<7>>;
        using result_t = meta::apply_reduce_t<meta::mul,arg_t>;
        using expected_t = meta::ct<21>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t = std::tuple<meta::ct<1>,std::ratio<1,3>,meta::ct<2>>;
        using result_t = meta::apply_reduce_t<meta::mul,arg_t>;
        using expected_t = std::ratio<2,3>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}

TEST_CASE("reduce(sub)" * doctest::test_suite("meta"))
{
    {
        using arg_t = std::tuple<meta::ct<1>,meta::ct<3>>;
        using result_t = meta::apply_reduce_t<meta::sub,arg_t>;
        using expected_t = meta::ct<-2>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t = std::tuple<meta::ct<1>,meta::ct<3>,meta::ct<7>>;
        using result_t = meta::apply_reduce_t<meta::sub,arg_t>;
        using expected_t = meta::ct<-9>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t = std::tuple<meta::ct<1>,std::ratio<1,3>,meta::ct<2>>;
        using result_t = meta::apply_reduce_t<meta::sub,arg_t>;
        using expected_t = std::ratio<-4,3>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}

TEST_CASE("reduce(div)" * doctest::test_suite("meta"))
{
    {
        using arg_t = std::tuple<meta::ct<1>,meta::ct<3>>;
        using result_t = meta::apply_reduce_t<meta::div,arg_t>;
        using expected_t = std::ratio<1,3>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t = std::tuple<meta::ct<1>,meta::ct<3>,meta::ct<7>>;
        using result_t = meta::apply_reduce_t<meta::div,arg_t>;
        using expected_t = std::ratio<1,21>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}