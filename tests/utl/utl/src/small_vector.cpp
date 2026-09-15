#include "nmtools/utl/small_vector.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;
namespace meta = nm::meta;

TEST_CASE("small_vector(case1)" * doctest::test_suite("utl"))
{
    using array_t = utl::small_vector<int,4>;

    auto a = array_t{};
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 0 );

    a.push_back(3);
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.at(0), 3 );

    a.push_back(4);
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 2 );
    NMTOOLS_ASSERT_EQUAL( a.at(1), 4 );

    a.push_back(5);
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 3 );
    NMTOOLS_ASSERT_EQUAL( a.at(2), 5 );

    a.push_back(6);
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 4 );
    NMTOOLS_ASSERT_EQUAL( a.at(3), 6 );

    a.push_back(7);
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 0 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 5 );
    NMTOOLS_ASSERT_EQUAL( a.at(4), 7 );

    a.push_back(8);
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 0 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 6 );
    NMTOOLS_ASSERT_EQUAL( a.at(5), 8 );
}

TEST_CASE("small_vector(case2)" * doctest::test_suite("utl"))
{
    SUBCASE("constructor")
    {
        {
            using array_t = utl::small_vector<int,4>;
            auto array = array_t(3);
            NMTOOLS_ASSERT_EQUAL( array.is_static(), 1 );
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
            static_assert( meta::is_ndarray_v<array_t> );
            static_assert( meta::is_list_v<array_t> );
            static_assert( meta::is_copy_constructible_v<array_t> );
        }
        {
            using array_t = utl::small_vector<int,4>;
            auto array = array_t();
            NMTOOLS_ASSERT_EQUAL( array.is_static(), 1 );
            NMTOOLS_ASSERT_EQUAL( array.size(), 0 );
        }
        {
            using array_t = utl::small_vector<int,4>;
            auto array = array_t(4);
            NMTOOLS_ASSERT_EQUAL( array.is_static(), 0 );
            NMTOOLS_ASSERT_EQUAL( array.size(), 4 );
        }
        {
            using array_t = utl::small_vector<int,4>;
            auto array = array_t(8);
            NMTOOLS_ASSERT_EQUAL( array.is_static(), 0 );
            NMTOOLS_ASSERT_EQUAL( array.size(), 8 );
        }
    }

    SUBCASE("variadic constructor")
    {
        {
            auto array = utl::small_vector{3,4,5,6,7};
            NMTOOLS_ASSERT_EQUAL( array.is_static(), 1 );
            NMTOOLS_ASSERT_EQUAL( array.size(), 5 );
            NMTOOLS_ASSERT_EQUAL( utl::size(array), 5 );
            NMTOOLS_ASSERT_EQUAL( nm::len(array), 5 );
            NMTOOLS_ASSERT_EQUAL( array[0], 3 );
            NMTOOLS_ASSERT_EQUAL( array[1], 4 );
            NMTOOLS_ASSERT_EQUAL( array[2], 5 );
            NMTOOLS_ASSERT_EQUAL( array[3], 6 );
            NMTOOLS_ASSERT_EQUAL( array[4], 7 );
        }
    }

    SUBCASE("resize")
    {
        {
            using array_t = utl::small_vector<int,4>;
            auto array = array_t();
            array.resize(3);
            NMTOOLS_ASSERT_EQUAL( array.is_static(), 1 );
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
        }
        {
            using array_t = utl::small_vector<int,4>;
            auto array = array_t();
            array.resize(9);
            NMTOOLS_ASSERT_EQUAL( array.is_static(), 0 );
            NMTOOLS_ASSERT_EQUAL( array.size(), 9 );
            array[0] = 1;
            array[1] = 2;
            NMTOOLS_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_ASSERT_EQUAL( array[1], 2 );
        }
        {
            // growing from static to dynamic preserves values
            using array_t = utl::small_vector<int,4>;
            auto array = array_t(3);
            array[0] = 1;
            array[1] = 2;
            array[2] = 3;
            array.resize(6);
            NMTOOLS_ASSERT_EQUAL( array.is_static(), 0 );
            NMTOOLS_ASSERT_EQUAL( array.size(), 6 );
            NMTOOLS_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_ASSERT_EQUAL( array[2], 3 );
        }
        {
            // shrinking dynamic stays dynamic
            using array_t = utl::small_vector<int,4>;
            auto array = array_t(9);
            array[0] = 1;
            array[1] = 2;
            NMTOOLS_ASSERT_EQUAL( array.is_static(), 0 );
            array.resize(3);
            NMTOOLS_ASSERT_EQUAL( array.is_static(), 0 );
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_ASSERT_EQUAL( array[1], 2 );
        }
    }

    SUBCASE("assignment")
    {
        {
            using array_t = utl::small_vector<int,4>;
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
            using array_t = utl::small_vector<int,4>;
            auto array  = array_t(3);
            array[0] = 1;
            array[1] = 2;
            array[2] = 3;
            auto copied = array_t(array);
            NMTOOLS_ASSERT_EQUAL( copied.is_static(), 1 );
            NMTOOLS_ASSERT_EQUAL( copied.size(), 3 );
            NMTOOLS_ASSERT_EQUAL( copied[0], 1 );
            NMTOOLS_ASSERT_EQUAL( copied[1], 2 );
            NMTOOLS_ASSERT_EQUAL( copied[2], 3 );
        }
        {
            using array_t = utl::small_vector<int,4>;
            auto array  = array_t(8);
            array[0] = 5;
            auto copied = array_t(array);
            NMTOOLS_ASSERT_EQUAL( copied.is_static(), 0 );
            NMTOOLS_ASSERT_EQUAL( copied.size(), 8 );
            NMTOOLS_ASSERT_EQUAL( copied[0], 5 );
        }
    }

    SUBCASE("copy assignment")
    {
        {
            using array_t = utl::small_vector<int,4>;
            auto array  = array_t(3);
            auto copied = array_t();
            copied = array;
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_ASSERT_EQUAL( copied.is_static(), 1 );
            NMTOOLS_ASSERT_EQUAL( copied.size(), 3 );
        }
        {
            using array_t = utl::small_vector<int,4>;
            auto array = array_t(8);
            array[0] = 5;
            auto copied = array_t();
            copied = array;
            NMTOOLS_ASSERT_EQUAL( copied.is_static(), 0 );
            NMTOOLS_ASSERT_EQUAL( copied.size(), 8 );
            NMTOOLS_ASSERT_EQUAL( copied[0], 5 );
        }
    }

    SUBCASE("len")
    {
        {
            using array_t = utl::small_vector<int,4>;
            auto array  = array_t(3);
            NMTOOLS_ASSERT_EQUAL( nm::len(array), 3 );
        }
    }

    SUBCASE("push_back")
    {
        {
            using array_t = utl::small_vector<int,4>;
            auto array = array_t();
            NMTOOLS_ASSERT_EQUAL( array.size(), 0 );
            array.push_back(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 1 );
            NMTOOLS_ASSERT_EQUAL( array[0], 3 );
        }
    }

    SUBCASE("range-for")
    {
        {
            auto array  = utl::small_vector{3,4,5,6,7};
            auto i = 0;
            for (const auto& v : array) {
                NMTOOLS_ASSERT_EQUAL( v, array[i] );
                i = i + 1;
            }
            NMTOOLS_ASSERT_EQUAL( i, 5 );
        }
    }

    SUBCASE("iterators")
    {
        {
            auto array = utl::small_vector{3,4,5};
            auto i = 0;
            for (auto it = array.begin(); it != array.end(); it++) {
                NMTOOLS_ASSERT_EQUAL( *it, array[i] );
                i = i + 1;
            }
            NMTOOLS_ASSERT_EQUAL( i, 3 );
        }
        {
            const auto array = utl::small_vector{3,4,5};
            NMTOOLS_ASSERT_EQUAL( array.data()[1], 4 );
            auto i = 0;
            for (auto it = utl::begin(array); it != utl::end(array); it++) {
                NMTOOLS_ASSERT_EQUAL( *it, array[i] );
                i = i + 1;
            }
            NMTOOLS_ASSERT_EQUAL( i, 3 );
        }
    }

    SUBCASE("return")
    {
        {
            auto f = [](auto size){
                using array_t = utl::small_vector<int,4>;
                auto array = array_t{};
                array.resize(size);
                return array;
            };
            auto array = f(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
        }
        {
            auto f = [](auto size){
                using array_t = utl::small_vector<int,4>;
                auto array = array_t{};
                array.resize(size);
                return array;
            };
            auto array = f(9);
            NMTOOLS_ASSERT_EQUAL( array.size(), 9 );
        }
        {
            auto f = [](auto value1, auto value2){
                using array_t = utl::small_vector<int,4>;
                auto array = array_t{};
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

TEST_CASE("small_vector(case3)" * doctest::test_suite("utl"))
{
    // should use NMTOOLS_SMALL_VECTOR_DEFAULT_DIM
    using array_t = utl::small_vector<int>;

    auto a = array_t{};
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 0 );

    a.push_back(3);
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.at(0), 3 );

    a.push_back(4);
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 2 );
    NMTOOLS_ASSERT_EQUAL( a.at(1), 4 );

    a.push_back(5);
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 3 );
    NMTOOLS_ASSERT_EQUAL( a.at(2), 5 );

    a.push_back(6);
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 4 );
    NMTOOLS_ASSERT_EQUAL( a.at(3), 6 );

    a.push_back(7);
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 5 );
    NMTOOLS_ASSERT_EQUAL( a.at(4), 7 );

    a.push_back(8);
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 6 );
    NMTOOLS_ASSERT_EQUAL( a.at(5), 8 );
}

TEST_CASE("small_vector(case4)" * doctest::test_suite("utl"))
{
    // resize to dynamic, then shrink below DIM,
    // buffer kind is kept as dynamic
    auto f = [](auto size){
        using array_t = utl::small_vector<int,4>;
        auto array = array_t{};
        array.resize(size);
        return array;
    };
    auto array = f(9);
    NMTOOLS_ASSERT_EQUAL( array.is_static(), 0 );
    NMTOOLS_ASSERT_EQUAL( array.size(), 9 );
    array.resize(3);
    NMTOOLS_ASSERT_EQUAL( array.is_static(), 0 );
    NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
}
