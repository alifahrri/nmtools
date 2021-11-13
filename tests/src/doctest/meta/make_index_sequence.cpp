#include "nmtools/meta/common.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("make_index_sequence" * doctest::test_suite("meta"))
{
    {
        constexpr auto N = 1;
        using result_t = meta::make_index_sequence<N>;
        using expect_t = meta::index_sequence<0>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        constexpr auto N = 2;
        using result_t = meta::make_index_sequence<N>;
        using expect_t = meta::index_sequence<0,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        constexpr auto N = 3;
        using result_t = meta::make_index_sequence<N>;
        using expect_t = meta::index_sequence<0,1,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        constexpr auto N = 4;
        using result_t = meta::make_index_sequence<N>;
        using expect_t = meta::index_sequence<0,1,2,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}