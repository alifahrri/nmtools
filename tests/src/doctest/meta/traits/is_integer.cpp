#include "nmtools/meta/bits/traits/is_integer.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("is_integer" * doctest::test_suite("meta"))
{
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_integer, int );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_integer, unsigned int );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_integer, const int );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_integer, long int );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_integer, unsigned long );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_integer, short int );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_integer, const short int );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_integer, char );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_integer, unsigned char );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_integer, signed char );
    }
    {
        // following stl integral constant is not integral type
        using arg_t = meta::integral_constant<unsigned long,1>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_integer, arg_t );
    }
}