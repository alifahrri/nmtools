#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("is_constant_index_array" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::tuple<meta::ct<1>,meta::ct<2>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_constant_index_array, arg_t );
    }
    {
        using arg_t = utl::tuple<int,int>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_constant_index_array, arg_t );
    }
    {
        using arg_t = utl::array<int,2>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_constant_index_array, arg_t );
    }
}