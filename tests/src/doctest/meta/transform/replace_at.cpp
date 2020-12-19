#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <utility>

namespace meta = nmtools::meta;

TEST_CASE("replace_at" * doctest::test_suite("meta"))
{
    {
        using arg_t         = std::tuple<int,double>;
        using replacement_t = size_t;
        using result_t      = meta::replace_at_t<arg_t,replacement_t,0>;
        using expected_t    = std::tuple<replacement_t,double>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t         = std::tuple<int,double,size_t>;
        using replacement_t = size_t;
        using result_t      = meta::replace_at_t<arg_t,replacement_t,0>;
        using expected_t    = std::tuple<replacement_t,double,size_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t         = std::tuple<int,double,size_t>;
        using replacement_t = size_t;
        using result_t      = meta::replace_at_t<arg_t,replacement_t,1>;
        using expected_t    = std::tuple<int,replacement_t,size_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t         = std::tuple<int,double,size_t>;
        using replacement_t = size_t;
        using result_t      = meta::replace_at_t<arg_t,replacement_t,2>;
        using expected_t    = std::tuple<int,double,replacement_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}