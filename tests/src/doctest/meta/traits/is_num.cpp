#include "nmtools/meta/bits/traits/is_num.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("is_num" * doctest::test_suite("meta"))
{
    {
        using type = int;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, type );
    }
    {
        using type = unsigned int;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, type );
    }
    {
        using type = char;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, type );
    }
    {
        using type = signed char;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, type );
    }
    {
        using type = unsigned char;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, type );
    }

    {
        using type = short int;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, type );
    }
    {
        using type = unsigned short int;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, type );
    }

    {
        using type = long int;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, type );
    }
    {
        using type = unsigned long int;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, type );
    }

    {
        using type = long long int;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, type );
    }
    {
        using type = unsigned long long int;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, type );
    }
}