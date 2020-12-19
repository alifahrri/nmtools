#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>

namespace meta = nmtools::meta;

TEST_CASE("sequence_to_constant" * doctest::test_suite("meta"))
{
    {
        using arg_t      = meta::sequence_t<1,0>;
        using result_t   = meta::sequence_to_constant_t<arg_t>;
        using expected_t = std::tuple<std::integral_constant<int,1>,std::integral_constant<int,0>>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}