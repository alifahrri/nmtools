#include "nmtools/utl/maybe.hpp"
#include "nmtools/utl/array.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;

template <typename T>
static constexpr auto test(bool valid, const T& t)
{
    using result_t = utl::maybe<T>;
    auto res = result_t{};

    if (valid) {
        // union's active member can't be changed at constexpr :(
        // res = t;
        return result_t{t};
    }

    return res;
}

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

    SUBCASE("constexpr")
    {
        {
            constexpr auto res = test(false,utl::array{0ul,1ul,2ul});
            CHECK( !res );
        }
        {
            constexpr auto res = test(true,utl::array{0ul,1ul,2ul});
            CHECK( res );
        }
    }
}