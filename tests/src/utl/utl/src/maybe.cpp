#include "nmtools/utl/maybe.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;

TEST_CASE("maybe" * doctest::test_suite("utl"))
{
    SUBCASE("constructor")
    {
        {
            auto t = int{3};
            auto maybe = utl::maybe(t);
            CHECK( *maybe == 3 );
        }
        {
            using maybe_int_t = utl::maybe<int>;
            auto maybe = maybe_int_t{};
            CHECK( !maybe );
        }
        {
            auto maybe = utl::maybe(3);
            auto other_maybe = maybe;
            CHECK( static_cast<bool>(other_maybe) );
        }
        {
            constexpr auto t = int{3};
            constexpr auto maybe = utl::maybe(t);
            CHECK( *maybe == 3 );
        }
        {
            using maybe_int_t = utl::maybe<int>;
            constexpr auto maybe = maybe_int_t{};
            CHECK( !maybe );
        }
    }

    SUBCASE("assignment")
    {
        {
            auto t = int{3};
            auto maybe = utl::maybe(t);
            CHECK( *maybe == 3 );

            maybe = utl::nothing;
            CHECK( !maybe );
        }
        {
            auto maybe = utl::maybe<int>{};
            CHECK( !maybe );

            maybe = 3;
            CHECK( *maybe == 3 );
        }
    }
}