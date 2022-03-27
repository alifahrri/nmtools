#include "nmtools/meta/utl/traits.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

TEST_CASE("has_size" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<int,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::has_size, arg_t );
    }
    {
        using arg_t = utl::tuple<int,double>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::has_size, arg_t );
    }
    {
        using arg_t = utl::maybe<utl::array<int,2>>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::has_size, arg_t );
    }
    {
        using arg_t = utl::either<int,double>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::has_size, arg_t );
    }
}

TEST_CASE("has_size_type" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<int,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::has_size_type, arg_t );
    }
    {
        using arg_t = utl::tuple<int,double>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::has_size_type, arg_t );
    }
    {
        using arg_t = utl::either<int,double>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::has_size_type, arg_t );
    }
    {
        using arg_t = utl::maybe<int>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::has_size_type, arg_t );
    }
}