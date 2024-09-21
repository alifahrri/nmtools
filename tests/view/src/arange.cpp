#include "nmtools/array/view/arange.hpp"
#include "nmtools/testing/data/array/arange.hpp"
#include "nmtools/testing/doctest.hpp"

#define ARANGE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, arange, case_name); \
    using namespace args; \
    auto result = nmtools::view::arange(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arange(case1)" * doctest::test_suite("view::arange"))
{
    ARANGE_SUBCASE(case1, stop, dtype );
}

TEST_CASE("arange(case2)" * doctest::test_suite("view::arange"))
{
    ARANGE_SUBCASE(case2, start, stop, dtype );
}

TEST_CASE("arange(case3)" * doctest::test_suite("view::arange"))
{
    ARANGE_SUBCASE(case3, start, stop, step, dtype );
}

TEST_CASE("arange(case4)" * doctest::test_suite("view::arange"))
{
    ARANGE_SUBCASE(case4, start, stop, step, dtype );
}

TEST_CASE("arange(case5)" * doctest::test_suite("view::arange"))
{
    ARANGE_SUBCASE(case5, stop );
}

TEST_CASE("arange(case6)" * doctest::test_suite("view::arange"))
{
    ARANGE_SUBCASE(case6, start, stop );
}

TEST_CASE("arange(case7)" * doctest::test_suite("view::arange"))
{
    ARANGE_SUBCASE(case7, start, stop, step );
}

TEST_CASE("arange(case8)" * doctest::test_suite("view::arange"))
{
    ARANGE_SUBCASE(case8, start, stop, step );
}

TEST_CASE("arange(case9)" * doctest::test_suite("view::arange"))
{
    ARANGE_SUBCASE(case9, start, stop, step );
}

TEST_CASE("arange_traits(case1)" * doctest::test_suite("view::arange_traits"))
{
    {
        auto array = nm::view::arange(0,5,1,nm::float32);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_size_ndarray_v<array_t>;
        static_assert( !is_fixed_shape );
    }
    {
        using namespace nm::literals;
        auto array = nm::view::arange(0_ct,5_ct,1_ct,nm::float32);
        using array_t = decltype(array);
        constexpr auto is_fixed_shape = nm::meta::is_fixed_shape_v<array_t>;
        static_assert( is_fixed_shape );
    }
}