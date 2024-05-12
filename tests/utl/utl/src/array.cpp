#include "nmtools/utl/array.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/testing/doctest.hpp"

// assume we also have stl
#include <type_traits>

namespace nm = nmtools;
namespace utl = nm::utl;

TEST_CASE("array" * doctest::test_suite("utl"))
{
    {
        using array_t = utl::array<int,3>;
        static_assert( meta::is_trivially_constructible_v<array_t> );
        static_assert( meta::is_trivially_copy_constructible_v<array_t> );
        static_assert( meta::is_default_constructible_v<array_t> );
        static_assert( meta::is_copy_constructible_v<array_t> );
        static_assert( meta::is_trivially_destructible_v<array_t> );
        static_assert( meta::is_copy_assignable_v<array_t> );
        static_assert( sizeof(array_t) == sizeof(int)*3 );
        // static_assert( meta::is_constructible_v<array_t,int,int,int> );
        // static_assert( std::is_constructible_v<array_t,int,int,int> );
    }
}

TEST_CASE("array" * doctest::test_suite("utl"))
{
    SUBCASE("constructor")
    {
        {
            using array_t = utl::array<int,3>;
            auto array = array_t{1,2,3};
            static_assert( meta::is_trivially_destructible_v<decltype(array)> );
            static_assert( meta::is_trivially_copyable_v<decltype(array)> );
            static_assert( std::is_trivially_destructible_v<decltype(array)> );
            static_assert( std::is_trivially_copyable_v<decltype(array)> );
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_ASSERT_EQUAL( array[2], 3 );
        }
        {
            auto array = utl::array{1,2,3};
            static_assert( meta::is_trivially_destructible_v<decltype(array)> );
            static_assert( meta::is_trivially_copyable_v<decltype(array)> );
            static_assert( std::is_trivially_destructible_v<decltype(array)> );
            static_assert( std::is_trivially_copyable_v<decltype(array)> );
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
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

    SUBCASE("copy")
    {
        {
            using array_t = utl::array<int,3>;
            auto array = array_t{1,2,3};
            auto copied = array;
            NMTOOLS_ASSERT_EQUAL( copied.size(), 3 );
            NMTOOLS_ASSERT_EQUAL( copied[0], 1 );
            NMTOOLS_ASSERT_EQUAL( copied[1], 2 );
            NMTOOLS_ASSERT_EQUAL( copied[2], 3 );
        }
    }

    SUBCASE("copy assignment")
    {
        {
            using array_t = utl::array<int,3>;
            auto array = array_t{3,4,5};
            auto copied = array_t();
            copied = array;
            NMTOOLS_ASSERT_EQUAL( copied.size(), 3 );
            NMTOOLS_ASSERT_EQUAL( copied[0], 3 );
            NMTOOLS_ASSERT_EQUAL( copied[1], 4 );
            NMTOOLS_ASSERT_EQUAL( copied[2], 5 );
        }
    }

    SUBCASE("return")
    {
        {
            auto f = [](){
                using array_t = utl::array<int,3>;
                auto array = array_t();
                array[0] = 1;
                array[1] = 2;
                array[2] = 3;
                return array;
            };
            auto array = f();
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_ASSERT_EQUAL( array[2], 3 );
        }
        {
            auto f = [](){
                using array_t = utl::array<int,3>;
                auto array = array_t();
                array[0] = 1;
                array[1] = 2;
                array[2] = 3;
                auto copied = array;
                return copied;
            };
            auto array = f();
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_ASSERT_EQUAL( array[2], 3 );
        }
        {
            auto f = [](){
                using array_t = utl::array<int,3>;
                auto array = array_t();
                array[0] = 1;
                array[1] = 2;
                array[2] = 3;
                auto copied = array_t();
                copied = array;
                return copied;
            };
            auto array = f();
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_ASSERT_EQUAL( array[2], 3 );
        }
    }
}

TEST_CASE("constexpr_array" * doctest::test_suite("utl"))
{
    SUBCASE("constructor")
    {
        {
            using array_t = utl::array<int,3>;
            constexpr auto array = array_t{1,2,3};
            NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[2], 3 );
        }
        {
            constexpr auto array = utl::array{3,4,5};
            NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[0], 3 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[1], 4 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[2], 5 );
        }
    }

    SUBCASE("copy")
    {
        {
            using array_t = utl::array<int,3>;
            constexpr auto array = array_t{1,2,3};
            constexpr auto copied = array;
            NMTOOLS_STATIC_ASSERT_EQUAL( copied.size(), 3 );
            NMTOOLS_STATIC_ASSERT_EQUAL( copied[0], 1 );
            NMTOOLS_STATIC_ASSERT_EQUAL( copied[1], 2 );
            NMTOOLS_STATIC_ASSERT_EQUAL( copied[2], 3 );
        }
    }

    SUBCASE("return")
    {
        {
            constexpr auto f = [](){
                using array_t = utl::array<int,3>;
                auto array = array_t();
                array[0] = 1;
                array[1] = 2;
                array[2] = 3;
                return array;
            };
            constexpr auto array = f();
            NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[2], 3 );
        }
        {
            constexpr auto f = [](){
                using array_t = utl::array<int,3>;
                auto array = array_t();
                array[0] = 1;
                array[1] = 2;
                array[2] = 3;
                auto copied = array;
                return copied;
            };
            constexpr auto array = f();
            NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[2], 3 );
        }
        {
            constexpr auto f = [](){
                using array_t = utl::array<int,3>;
                auto array = array_t();
                array[0] = 1;
                array[1] = 2;
                array[2] = 3;
                auto copied = array_t();
                copied = array;
                return copied;
            };
            constexpr auto array = f();
            NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_STATIC_ASSERT_EQUAL( array[2], 3 );
        }
    }
}

TEST_CASE("maybe_array" * doctest::test_suite("utl"))
{
    SUBCASE("constructor")
    {
        {
            using array_t = nmtools_maybe<utl::array<int,3>>;
            auto array = array_t{{1,2,3}};
            NMTOOLS_ASSERT_EQUAL( (*array).size(), 3 );
            NMTOOLS_ASSERT_EQUAL( (*array)[0], 1 );
            NMTOOLS_ASSERT_EQUAL( (*array)[1], 2 );
            NMTOOLS_ASSERT_EQUAL( (*array)[2], 3 );
        }
    }

    SUBCASE("copy")
    {
        {
            using array_t = nmtools_maybe<utl::array<int,3>>;
            auto array = array_t{{1,2,3}};
            auto copied = array;
            NMTOOLS_ASSERT_EQUAL( (*copied).size(), 3 );
            NMTOOLS_ASSERT_EQUAL( (*copied)[0], 1 );
            NMTOOLS_ASSERT_EQUAL( (*copied)[1], 2 );
            NMTOOLS_ASSERT_EQUAL( (*copied)[2], 3 );
        }
    }

    SUBCASE("copy assignment")
    {
        {
            using array_t = nmtools_maybe<utl::array<int,3>>;
            auto array = array_t{{3,4,5}};
            auto copied = array_t(meta::Nothing);
            copied = array;
            NMTOOLS_ASSERT_EQUAL( (*copied).size(), 3 );
            NMTOOLS_ASSERT_EQUAL( (*copied)[0], 3 );
            NMTOOLS_ASSERT_EQUAL( (*copied)[1], 4 );
            NMTOOLS_ASSERT_EQUAL( (*copied)[2], 5 );
        }
    }

    SUBCASE("return")
    {
        {
            auto f = [](){
                using array_t = nmtools_maybe<utl::array<int,3>>;
                auto array = array_t({1,2,3});
                return array;
            };
            auto array = f();
            NMTOOLS_ASSERT_EQUAL( (*array).size(), 3 );
            NMTOOLS_ASSERT_EQUAL( (*array)[0], 1 );
            NMTOOLS_ASSERT_EQUAL( (*array)[1], 2 );
            NMTOOLS_ASSERT_EQUAL( (*array)[2], 3 );
        }
        {
            auto f = [](){
                using array_t = nmtools_maybe<utl::array<int,3>>;
                auto array = array_t({1,2,3});
                auto copied = array;
                return copied;
            };
            auto array = f();
            NMTOOLS_ASSERT_EQUAL( (*array).size(), 3 );
            NMTOOLS_ASSERT_EQUAL( (*array)[0], 1 );
            NMTOOLS_ASSERT_EQUAL( (*array)[1], 2 );
            NMTOOLS_ASSERT_EQUAL( (*array)[2], 3 );
        }
        {
            auto f = [](){
                using array_t = nmtools_maybe<utl::array<int,3>>;
                auto array = array_t({1,2,3});
                auto copied = array_t();
                copied = array;
                return copied;
            };
            auto array = f();
            NMTOOLS_ASSERT_EQUAL( (*array).size(), 3 );
            NMTOOLS_ASSERT_EQUAL( (*array)[0], 1 );
            NMTOOLS_ASSERT_EQUAL( (*array)[1], 2 );
            NMTOOLS_ASSERT_EQUAL( (*array)[2], 3 );
        }
    }
}

TEST_CASE("constexpr_maybe_array" * doctest::test_suite("utl"))
{
    SUBCASE("constructor")
    {
        {
            using array_t = nmtools_maybe<utl::array<int,3>>;
            constexpr auto array = array_t{{1,2,3}};
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array).size(), 3 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array)[0], 1 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array)[1], 2 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array)[2], 3 );
        }
    }

    SUBCASE("copy")
    {
        {
            using array_t = nmtools_maybe<utl::array<int,3>>;
            constexpr auto array = array_t{{1,2,3}};
            constexpr auto copied = array;
            NMTOOLS_STATIC_ASSERT_EQUAL( (*copied).size(), 3 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*copied)[0], 1 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*copied)[1], 2 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*copied)[2], 3 );
        }
    }

    SUBCASE("return")
    {
        {
            constexpr auto f = [](){
                using array_t = nmtools_maybe<utl::array<int,3>>;
                auto array = array_t({1,2,3});
                return array;
            };
            constexpr auto array = f();
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array).size(), 3 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array)[0], 1 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array)[1], 2 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array)[2], 3 );
        }
        {
            constexpr auto f = [](){
                using array_t = nmtools_maybe<utl::array<int,3>>;
                auto array = array_t({1,2,3});
                auto copied = array;
                return copied;
            };
            constexpr auto array = f();
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array).size(), 3 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array)[0], 1 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array)[1], 2 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array)[2], 3 );
        }
        // error: constexpr variable 'array' must be initialized by a constant expression
        // note: non-constexpr function 'operator=' cannot be used in a constant expression
        #if 0
        {
            constexpr auto f = [](){
                using array_t = nmtools_maybe<utl::array<int,3>>;
                auto array = array_t({1,2,3});
                auto copied = array_t();
                copied = array;
                return copied;
            };
            constexpr auto array = f();
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array).size(), 3 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array)[0], 1 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array)[1], 2 );
            NMTOOLS_STATIC_ASSERT_EQUAL( (*array)[2], 3 );
        }
        #endif
    }
}