#include "nmtools/meta.hpp"
#include "nmtools/utility/forward.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

struct A {};

A foo() { return A{}; }
const A const_foo() { return A{}; }

TEST_CASE("forward" * doctest::test_suite("meta"))
{
    auto a = A{};
    const auto ca = A{};

    {
        using result_t = decltype(nm::forward<A&>(a));
        using expect_t = A&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using result_t = decltype(nm::forward<A>(a));
        using expect_t = A&&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using result_t = decltype(nm::forward<A>(foo()));
        using expect_t = A&&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    {
        using result_t = decltype(nm::forward<const A&>(a));
        using expect_t = const A&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using result_t = decltype(nm::forward<const A>(a));
        using expect_t = const A&&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using result_t = decltype(nm::forward<const A>(foo()));
        using expect_t = const A&&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    {
        using result_t = decltype(nm::forward<const A&>(ca));
        using expect_t = const A&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using result_t = decltype(nm::forward<const A>(ca));
        using expect_t = const A&&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using result_t = decltype(nm::forward<const A>(const_foo()));
        using expect_t = const A&&;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}