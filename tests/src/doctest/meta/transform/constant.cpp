#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>

namespace meta = nmtools::meta;

TEST_CASE("constant" * doctest::test_suite("meta"))
{
    {
        using result_t   = meta::constant_t<1,0>;
        using expected_t = std::tuple<std::integral_constant<int,1>,std::integral_constant<int,0>>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}