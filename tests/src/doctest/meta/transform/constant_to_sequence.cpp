#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>

namespace meta = nmtools::meta;

TEST_CASE("constant_to_sequence" * doctest::test_suite("meta"))
{
    {
        using arg_t      = meta::constant_t<1,0>;
        using result_t   = meta::constant_to_sequence_t<arg_t>;
        using expected_t = std::integer_sequence<int,1,0>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}