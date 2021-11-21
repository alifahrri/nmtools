#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("remove_reference" * doctest::test_suite("meta"))
{
    {
        using arg_t = void;
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = void;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = int;
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = int[3];
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = int[3];
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = int*;
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = int*;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = const int*;
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = const int*;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    {
        using arg_t = int&;
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = const int&;
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = const int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = int(&)[3];
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = int[3];
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = int*&;
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = int*;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = const int*&;
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = const int*;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    {
        using arg_t = int&&;
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = const int&&;
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = const int;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = int(&&)[3];
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = int[3];
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = int*&&;
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = int*;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using arg_t = const int*&&;
        using result_t = meta::remove_reference_t<arg_t>;
        using expect_t = const int*;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}