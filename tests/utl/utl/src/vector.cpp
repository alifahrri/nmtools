#include "nmtools/utl/vector.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/testing/doctest.hpp"
namespace nm = nmtools;
namespace utl = nm::utl;

TEST_CASE("vector" * doctest::test_suite("utl"))
{
    {
        using array_t = utl::vector<int>;
        static_assert( !meta::is_trivially_constructible_v<array_t> );
        static_assert( !meta::is_trivially_copy_constructible_v<array_t> );
        static_assert( meta::is_default_constructible_v<array_t> );
        static_assert( meta::is_copy_constructible_v<array_t> );
        static_assert( meta::is_copy_assignable_v<array_t> );
        static_assert( meta::is_constructible_v<array_t,int> );
        static_assert( meta::is_constructible_v<array_t,int,int,int> );
    }
}

TEST_CASE("vector" * doctest::test_suite("utl"))
{
    SUBCASE("constructor")
    {
        {
            using array_t = utl::vector<int>;
            auto array = array_t(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
        }
        {
            using array_t = utl::vector<int>;
            auto array = array_t();
            NMTOOLS_ASSERT_EQUAL( array.size(), 0 );
        }
    }

    SUBCASE("resize")
    {
        {
            using array_t = utl::vector<int>;
            auto array = array_t();
            array.resize(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
        }
        {
            using array_t = utl::vector<double>;
            auto array = array_t();
            array.resize(12);
            NMTOOLS_ASSERT_EQUAL( array.size(), 12 );
        }
    }

    SUBCASE("assignment")
    {
        {
            using array_t = utl::vector<int>;
            auto array = array_t(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
            array[0] = 1;
            array[1] = 2;
            array[2] = 3;
            NMTOOLS_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_ASSERT_EQUAL( array[2], 3 );
        }
    }

    SUBCASE("copy")
    {
        {
            using array_t = utl::vector<int>;
            auto array  = array_t(3);
            auto copied = array_t(array);
            NMTOOLS_ASSERT_EQUAL( copied.size(), 3 );
        }
    }

    SUBCASE("copy assignment")
    {
        {
            using array_t = utl::vector<int>;
            auto array  = array_t(3);
            auto copied = array_t();
            copied = array;
            NMTOOLS_ASSERT_EQUAL( copied.size(), 3 );
        }
    }

    SUBCASE("len")
    {
        {
            using array_t = utl::vector<int>;
            auto array  = array_t(3);
            NMTOOLS_ASSERT_EQUAL( nm::len(array), 3 );
        }
    }

    SUBCASE("push_back")
    {
        {
            using array_t = utl::vector<int>;
            auto array = array_t();
            NMTOOLS_ASSERT_EQUAL( array.size(), 0 );
            array.push_back(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 1 );
            NMTOOLS_ASSERT_EQUAL( array[0], 3 );
        }
    }

    SUBCASE("return")
    {
        {
            auto f = [](auto size){
                using array_t = utl::vector<int>;
                auto array = array_t();
                array.resize(size);
                return array;
            };
            auto array = f(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
        }
        {
            auto f = [](auto size){
                using array_t = utl::vector<int>;
                auto array = array_t();
                array.resize(size);
                auto copied = array;
                return copied;
            };
            auto array = f(4);
            NMTOOLS_ASSERT_EQUAL( array.size(), 4 );
        }
        {
            auto f = [](auto size){
                using array_t = utl::vector<int>;
                auto array = array_t();
                array.resize(size);
                auto copied = array_t(3);
                copied = array;
                return copied;
            };
            auto array = f(6);
            NMTOOLS_ASSERT_EQUAL( array.size(), 6 );
        }
        {
            auto f = [](auto value1, auto value2){
                using array_t = utl::vector<int>;
                auto array = array_t();
                array.push_back(value1);
                array.push_back(value2);
                return array;
            };
            auto array = f(4,5);
            NMTOOLS_ASSERT_EQUAL( array.size(), 2 );
            NMTOOLS_ASSERT_EQUAL( array.at(0), 4 );
            NMTOOLS_ASSERT_EQUAL( array.at(1), 5 );
        }
    }
}

// TODO: fix runtime
TEST_CASE("maybe_vector" * doctest::test_suite("utl") * doctest::skip())
{
    SUBCASE("constructor")
    {
        {
            using array_t = nmtools_maybe<utl::vector<int>>;
            auto array = array_t(3);
            NMTOOLS_ASSERT_EQUAL( (*array).size(), 3 );
        }
        {
            using array_t = nmtools_maybe<utl::vector<int>>;
            auto array = array_t();
            NMTOOLS_ASSERT_EQUAL( (*array).size(), 0 );
        }
    }
    SUBCASE("resize")
    {
        {
            using array_t = nmtools_maybe<utl::vector<int>>;
            auto array = array_t();
            (*array).resize(3);
            NMTOOLS_ASSERT_EQUAL( (*array).size(), 3 );
        }
        {
            using array_t = nmtools_maybe<utl::vector<double>>;
            auto array = array_t();
            (*array).resize(12);
            NMTOOLS_ASSERT_EQUAL( (*array).size(), 12 );
        }
    }
    SUBCASE("assignment")
    {
        {
            using array_t = nmtools_maybe<utl::vector<int>>;
            auto array = array_t(3);
            NMTOOLS_ASSERT_EQUAL( (*array).size(), 3 );
            (*array)[0] = 1;
            (*array)[1] = 2;
            (*array)[2] = 3;
            NMTOOLS_ASSERT_EQUAL( (*array)[0], 1 );
            NMTOOLS_ASSERT_EQUAL( (*array)[1], 2 );
            NMTOOLS_ASSERT_EQUAL( (*array)[2], 3 );
        }
    }
    SUBCASE("copy")
    {
        {
            using array_t = nmtools_maybe<utl::vector<int>>;
            auto array  = array_t(3);
            auto copied = array_t(array);
            NMTOOLS_ASSERT_EQUAL( (*copied).size(), 3 );
        }
    }
    SUBCASE("copy assignment")
    {
        {
            using array_t = nmtools_maybe<utl::vector<int>>;
            auto array  = array_t(3);
            auto copied = array_t();
            copied = *array;
            NMTOOLS_ASSERT_EQUAL( (*copied).size(), 3 );
        }
        {
            using array_t = nmtools_maybe<utl::vector<int>>;
            auto array  = array_t(3);
            auto copied = array_t();
            copied = array;
            NMTOOLS_ASSERT_EQUAL( (*copied).size(), 3 );
        }
    }
    SUBCASE("push_back")
    {
        {
            using array_t = nmtools_maybe<utl::vector<int>>;
            auto array = array_t();
            NMTOOLS_ASSERT_EQUAL( (*array).size(), 0 );
            (*array).push_back(3);
            NMTOOLS_ASSERT_EQUAL( (*array).size(), 1 );
            NMTOOLS_ASSERT_EQUAL( (*array)[0], 3 );
        }
    }
    SUBCASE("return")
    {
        {
            auto f = [](auto size){
                using array_t = nmtools_maybe<utl::vector<int>>;
                auto array = array_t();
                (*array).resize(size);
                NMTOOLS_ASSERT_EQUAL( (*array).size(), 3 );
                return array;
            };
            auto array = f(3);
            NMTOOLS_ASSERT_EQUAL( array.has_value(), true );
            NMTOOLS_ASSERT_EQUAL( (*array).size(), 3 );
        }
        {
            auto f = [](auto value1, auto value2){
                using array_t = nmtools_maybe<utl::vector<int>>;
                auto array = array_t();
                (*array).push_back(value1);
                (*array).push_back(value2);
                NMTOOLS_ASSERT_EQUAL( (*array).size(), 2 );
                NMTOOLS_ASSERT_EQUAL( (*array).at(0), 4 );
                NMTOOLS_ASSERT_EQUAL( (*array).at(1), 5 );
                return array;
            };
            auto array = f(4,5);
            NMTOOLS_ASSERT_EQUAL( (*array).size(), 2 );
            NMTOOLS_ASSERT_EQUAL( (*array).at(0), 4 );
            NMTOOLS_ASSERT_EQUAL( (*array).at(1), 5 );
        }
    }
}