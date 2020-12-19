#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>

namespace meta = nmtools::meta;

TEST_CASE("sequence" * doctest::test_suite("meta"))
{
    {
        using result_t   = meta::sequence_t<1,0>;
        using expected_t = std::integer_sequence<int,1,0>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}