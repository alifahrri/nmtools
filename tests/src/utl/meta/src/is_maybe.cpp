#include "nmtools/meta/utl/traits.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("is_maybe" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::maybe<int>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_maybe, arg_t );
    }
    {
        using arg_t = utl::maybe<utl::array<double,2>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_maybe, arg_t );
    }
    {
        using arg_t = utl::array<double,2>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_maybe, arg_t );
    }
    {
        using arg_t = utl::tuple<int,int,int>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_maybe, arg_t );
    }
    {
        using arg_t = utl::either<utl::array<double,2>,double>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_maybe, arg_t );
    }
}