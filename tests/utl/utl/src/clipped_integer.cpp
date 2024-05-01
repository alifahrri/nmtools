#include "nmtools/meta.hpp"
#include "nmtools/utl.hpp"
#include "nmtools/testing/doctest.hpp"

// assume we also have stl
#include <type_traits>

namespace nm  = nmtools;
namespace utl = nm::utl;

using namespace nm::literals;

TEST_CASE("clipped_integer(case1)" * doctest::test_suite("clipped_integer"))
{
    auto i = "2:[3]"_ct;
    // static_assert( meta::is_trivially_destructible_v<decltype(i)> );
    // static_assert( meta::is_trivially_copyable_v<decltype(i)> );
    static_assert( meta::is_copy_constructible_v<decltype(i)> );
    // static_assert( meta::is_trivially_copy_constructible_v<decltype(i)> );
    // static_assert( std::is_trivially_destructible_v<decltype(i)> );
    // static_assert( std::is_trivially_copyable_v<decltype(i)> );
    static_assert( std::is_copy_constructible_v<decltype(i)> );
    // static_assert( std::is_trivially_copy_constructible_v<decltype(i)> );
}

TEST_CASE("array(case1)" * doctest::test_suite("clipped_integer"))
{
    {
        using value_t = nm::clipped_size_t<3>;
        using array_t = utl::array<value_t,3>;

        auto array = array_t{1,2,3};

        static_assert( meta::is_trivially_destructible_v<decltype(array)> );
        // static_assert( meta::is_trivially_copyable_v<decltype(array)> );
        static_assert( std::is_trivially_destructible_v<decltype(array)> );
        // static_assert( std::is_trivially_copyable_v<decltype(array)> );

        NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
        NMTOOLS_ASSERT_EQUAL( array[0], 1 );
        NMTOOLS_ASSERT_EQUAL( array[1], 2 );
        NMTOOLS_ASSERT_EQUAL( array[2], 3 );
    }
    {
        auto array = utl::array{"0:[3]"_ct,"1:[3]"_ct,"2:[3]"_ct};

        // static_assert( meta::is_trivially_destructible_v<decltype(array)> );
        // static_assert( meta::is_trivially_copyable_v<decltype(array)> );
        // static_assert( std::is_trivially_destructible_v<decltype(array)> );
        // static_assert( std::is_trivially_copyable_v<decltype(array)> );

        NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
        NMTOOLS_ASSERT_EQUAL( array[0], 0 );
        NMTOOLS_ASSERT_EQUAL( array[1], 1 );
        NMTOOLS_ASSERT_EQUAL( array[2], 2 );
    }
    {
        using value_t = nm::clipped_size_t<3>;
        using array_t = utl::array<value_t,3>;

        auto array = array_t{};
        for (size_t i=0; i<array.size(); i++) {
            array[i] = i;
        }

        // static_assert( meta::is_trivially_destructible_v<decltype(array)> );
        // static_assert( meta::is_trivially_copyable_v<decltype(array)> );
        // static_assert( std::is_trivially_destructible_v<decltype(array)> );
        // static_assert( std::is_trivially_copyable_v<decltype(array)> );

        NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
        NMTOOLS_ASSERT_EQUAL( array[0], 0 );
        NMTOOLS_ASSERT_EQUAL( array[1], 1 );
        NMTOOLS_ASSERT_EQUAL( array[2], 2 );
    }
}