#include "nmtools/utility/small_vector.hpp"
#include "nmtools/testing/doctest.hpp"

TEST_CASE("small_vector(case1)" * doctest::test_suite("utility::small_vector"))
{
    using small_vector = nmtools::small_vector<nm_size_t,4>;

    auto a = small_vector{};
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 0 );

    a.push_back(3);
    NMTOOLS_ASSERT_EQUAL( a.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.at(0), 3 );

    a.push_back(4);
    NMTOOLS_ASSERT_EQUAL( a.size(), 2 );
    NMTOOLS_ASSERT_EQUAL( a.at(1), 4 );

    a.push_back(5);
    NMTOOLS_ASSERT_EQUAL( a.size(), 3 );
    NMTOOLS_ASSERT_EQUAL( a.at(2), 5 );

    a.push_back(6);
    NMTOOLS_ASSERT_EQUAL( a.size(), 4 );
    NMTOOLS_ASSERT_EQUAL( a.at(3), 6 );

    a.push_back(7);
    NMTOOLS_ASSERT_EQUAL( a.size(), 5 );
    NMTOOLS_ASSERT_EQUAL( a.at(4), 7 );

    NMTOOLS_ASSERT_EQUAL( a.is_static(), 0 );

    a.push_back(8);
    NMTOOLS_ASSERT_EQUAL( a.size(), 6 );
    NMTOOLS_ASSERT_EQUAL( a.at(5), 8 );
}

TEST_CASE("small_vector(case2)" * doctest::test_suite("utility::small_vector"))
{
    auto a = nmtools::small_vector{3,4,5,6,7};
    NMTOOLS_ASSERT_EQUAL( a.is_static(), 1 );
    NMTOOLS_ASSERT_EQUAL( a.size(), 5 );
    NMTOOLS_ASSERT_EQUAL( nmtools::size(a), 5 );
    NMTOOLS_ASSERT_EQUAL( nmtools::len(a), 5 );

    auto expect = nmtools_array{3,4,5,6,7};
    NMTOOLS_ASSERT_EQUAL( a, expect );
}

TEST_CASE("small_vector(case3)" * doctest::test_suite("utility::small_vector"))
{
    // should use NMTOOLS_SMALL_VECTOR_DEFAULT_DIM
    using small_vector = nmtools::small_vector<nm_size_t>;

    auto a = small_vector{};
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

TEST_CASE("small_vector(case3)" * doctest::test_suite("utility::small_vector"))
{
    // for-loop
    auto array  = nmtools::small_vector{3,4,5,6,7};
    auto expect = nmtools_array{3,4,5,6,7};

    NMTOOLS_ASSERT_EQUAL( array.size(), expect.size() );
    auto i = 0;
    for (const auto& a : array) {
        NMTOOLS_ASSERT_EQUAL( a, expect.at(i) );
        i = i + 1;
    }
    for (nm_size_t i=0; i<(nm_size_t)nmtools::size(array); i++) {
        NMTOOLS_ASSERT_EQUAL( nmtools::at(array,i), expect.at(i) );
    }
    for (nm_size_t i=0; i<(nm_size_t)nmtools::size(array); i++) {
        NMTOOLS_ASSERT_EQUAL( array[i], expect.at(i) );
    }
}

TEST_CASE("small_vector(case4)" * doctest::test_suite("utility::small_vector"))
{
    auto f = [](auto size){
        using array_t = nmtools::small_vector<nm_size_t>;
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

TEST_CASE("small_vector(case5)" * doctest::test_suite("utility::small_vector"))
{
    using array_t = nmtools_maybe<nmtools::small_vector<nm_size_t>>;
    auto array = array_t(3);
    NMTOOLS_ASSERT_EQUAL( (*array).size(), 3 );
    (*array).resize(12);
    NMTOOLS_ASSERT_EQUAL( (*array).size(), 12 );
    (*array)[0] = 1;
    (*array)[1] = 2;
    (*array)[2] = 3;
    NMTOOLS_ASSERT_EQUAL( (*array)[0], 1 );
    NMTOOLS_ASSERT_EQUAL( (*array)[1], 2 );
    NMTOOLS_ASSERT_EQUAL( (*array)[2], 3 );

    auto new_array = array_t(4);
    new_array = *array;
    NMTOOLS_ASSERT_EQUAL( (*new_array).size(), 12 );
    (*new_array)[0] = 1;
    (*new_array)[1] = 2;
    (*new_array)[2] = 3;
    NMTOOLS_ASSERT_EQUAL( (*new_array)[0], 1 );
    NMTOOLS_ASSERT_EQUAL( (*new_array)[1], 2 );
    NMTOOLS_ASSERT_EQUAL( (*new_array)[2], 3 );

    (*new_array).push_back(99);
    NMTOOLS_ASSERT_EQUAL( (*new_array).size(), 13 );
    NMTOOLS_ASSERT_EQUAL( (*new_array)[12], 99 );
}