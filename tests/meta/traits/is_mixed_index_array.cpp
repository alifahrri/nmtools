#include "nmtools/meta/bits/traits/is_mixed_index_array.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nmtools::meta;

TEST_CASE("is_mixed_index_array" * doctest::test_suite("meta::traits"))
{
    {
        using T = nmtools_tuple<int,int>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_mixed_index_array, T );
    }
    {
        using T = nmtools_tuple<int,meta::ct<2>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_mixed_index_array, T );
    }
    {
        using T = nmtools_tuple<meta::ct<1>,meta::ct<2>>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_mixed_index_array, T );
    }
    {
        using T = nmtools_array<int,4>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_mixed_index_array, T );
    }
}