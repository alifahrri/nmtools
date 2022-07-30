#include "nmtools/utl/array.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;

TEST_CASE("array" * doctest::test_suite("utl"))
{
    SUBCASE("constructor")
    {
        {
            using array_t = utl::array<int,3>;
            auto array = array_t{1,2,3};
            NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_ASSERT_EQUAL( array[2], 3 );
        }
        {
            auto array = utl::array{1,2,3};
            NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_ASSERT_EQUAL( array[2], 3 );
        }
        {
            constexpr auto array = utl::array{1,2,3};
            NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_ASSERT_EQUAL( array[2], 3 );
        }
        {
            constexpr auto array = utl::array{1,2,3};

            // #ifdef __clang__
            const auto& a = utl::get<0>(array);
            const auto& b = utl::get<1>(array);
            const auto& c = utl::get<2>(array);
            // #else
            // const auto& [a,b,c] = array;
            // #endif
            NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
            CHECK( a == 1 );
            CHECK( b == 2 );
            CHECK( c == 3 );
        }
        {
            // copy constructor
            auto array = utl::array<int,3>{1,2,3};
            auto new_array = utl::array{array};


            // #ifdef __clang__
            const auto& a = utl::get<0>(new_array);
            const auto& b = utl::get<1>(new_array);
            const auto& c = utl::get<2>(new_array);
            // #else
            // const auto& [a,b,c] = new_array;
            // #endif
            NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
            CHECK( a == 1 );
            CHECK( b == 2 );
            CHECK( c == 3 );
        }
    }

    SUBCASE("get")
    {
        {
            auto array = utl::array{1,2,3};
            auto value = nm::get<0>(array);
            NMTOOLS_ASSERT_EQUAL( value, 1 );
        }
    }

    SUBCASE("len")
    {
        {
            auto array = utl::array{1,2,3};
            NMTOOLS_ASSERT_EQUAL( nm::len(array), 3 );
        }
    }
}