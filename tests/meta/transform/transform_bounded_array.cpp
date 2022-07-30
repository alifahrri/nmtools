#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("transform_bounded_array" * doctest::test_suite("transform_bounded_array"))
{
    {
        using array_t = int[3];
        using tf_t = meta::transform_bounded_array_t<array_t>;
        using expected_t = nmtools_array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( tf_t, expected_t );
    }
}