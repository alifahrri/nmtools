#include "nmtools/meta/utl/traits.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("is_fixed_index_array" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<int,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_index_array, arg_t );
    }
    {
        using arg_t = utl::array<double,2>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_index_array, arg_t );
    }
    {
        using arg_t = utl::tuple<int,int>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_index_array, arg_t );
    }
    {
        using arg_t = utl::tuple<meta::ct<1>,meta::ct<2>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_index_array, arg_t );
    }
    {
        using arg_t = utl::tuple<double,int>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_index_array, arg_t );
    }
    {
        using arg_t = utl::maybe<utl::array<int,2>>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_index_array, arg_t );
    }
}