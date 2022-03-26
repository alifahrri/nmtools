#include "nmtools/meta/bits/transform/add_reference.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

struct Foo {};

TEST_CASE("add_rvalue_reference" * doctest::test_suite("meta"))
{
    {
        using type = void;
        using result_t = meta::add_rvalue_reference_t<type>;
        using expect_t = void;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = int;
        using result_t = meta::add_rvalue_reference_t<type>;
        using expect_t = int&&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = int[3];
        using result_t = meta::add_rvalue_reference_t<type>;
        using expect_t = int(&&)[3];
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = int&;
        using result_t = meta::add_rvalue_reference_t<type>;
        using expect_t = int&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = const int&;
        using result_t = meta::add_rvalue_reference_t<type>;
        using expect_t = const int&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = int*;
        using result_t = meta::add_rvalue_reference_t<type>;
        using expect_t = int*&&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = const int*;
        using result_t = meta::add_rvalue_reference_t<type>;
        using expect_t = const int*&&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = Foo;
        using result_t = meta::add_rvalue_reference_t<type>;
        using expect_t = Foo&&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}

TEST_CASE("add_lvalue_reference" * doctest::test_suite("meta"))
{
    {
        using type = void;
        using result_t = meta::add_lvalue_reference_t<type>;
        using expect_t = void;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = int;
        using result_t = meta::add_lvalue_reference_t<type>;
        using expect_t = int&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = int[3];
        using result_t = meta::add_lvalue_reference_t<type>;
        using expect_t = int(&)[3];
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = int&;
        using result_t = meta::add_lvalue_reference_t<type>;
        using expect_t = int&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = const int&;
        using result_t = meta::add_lvalue_reference_t<type>;
        using expect_t = const int&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = int*;
        using result_t = meta::add_lvalue_reference_t<type>;
        using expect_t = int*&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = const int*;
        using result_t = meta::add_lvalue_reference_t<type>;
        using expect_t = const int*&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using type     = Foo;
        using result_t = meta::add_lvalue_reference_t<type>;
        using expect_t = Foo&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}