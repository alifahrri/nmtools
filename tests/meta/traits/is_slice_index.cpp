#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("is_slice_index" * doctest::test_suite("meta::is_slice_index"))
{
    SUBCASE("case1")
    {
        using T = int;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index, T );
    }
    SUBCASE("case2")
    {
        using T = float;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index, T );
    }
    SUBCASE("case3")
    {
        using T = nm::ellipsis_t;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index, T );
    }
    SUBCASE("case4")
    {
        using T = nm::none_t;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index, T );
    }
    SUBCASE("case5")
    {
        using T = nmtools_either<int,nm::ellipsis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index, T );
    }
}