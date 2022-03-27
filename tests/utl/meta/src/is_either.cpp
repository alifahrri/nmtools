#include "nmtools/meta/utl/traits.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("is_either" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::either<utl::array<double,2>,double>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_either, arg_t );
    }
    {
        using arg_t = utl::maybe<utl::array<double,2>>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_either, arg_t );
    }
    {
        using arg_t = utl::tuple<int,int,int>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_either, arg_t );
    }
    {
        using arg_t = utl::array<int,3>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_either, arg_t );
    }
}