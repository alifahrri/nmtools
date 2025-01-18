#include "nmtools/array/ufuncs/greater_equal.hpp"
#include "nmtools/testing/data/array/greater_equal.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define GREATER_EQUAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, greater_equal, case_name); \
    using namespace args; \
    auto result = view::greater_equal(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("greater_equal(case1)" * doctest::test_suite("view::greater_equal"))
{
    GREATER_EQUAL_SUBCASE( case1,   a,   b );
    GREATER_EQUAL_SUBCASE( case1, a_a, b_a );
    GREATER_EQUAL_SUBCASE( case1, a_f, b_f );
    GREATER_EQUAL_SUBCASE( case1, a_d, b_d );
    GREATER_EQUAL_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("greater_equal(case2)" * doctest::test_suite("view::greater_equal"))
{
    GREATER_EQUAL_SUBCASE( case2,   a, b );
    GREATER_EQUAL_SUBCASE( case2, a_a, b );
    GREATER_EQUAL_SUBCASE( case2, a_f, b );
    GREATER_EQUAL_SUBCASE( case2, a_d, b );
    GREATER_EQUAL_SUBCASE( case2, a_h, b );
}

#define GREATER_EQUAL_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_greater_equal(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

// TODO: fix
#if 0
TEST_CASE("greater_equal(fixed_shape)" * doctest::test_suite("view::greater_equal"))
{
    namespace meta = nmtools::meta;
    {
        int A[1][3] = {{1,2,3}};
        int B[3][1] = {{4},{5},{6}};
        constexpr auto expected_shape = std::array{3,3};
        GREATER_EQUAL_FIXED_SHAPE_SUBCASE( raw, expected_shape, A, B );
    }
    {
        auto A = std::array{1,2,3};
        auto B = std::array{std::array{4,5,6}};
        constexpr auto expected_shape = std::array{3};
        GREATER_EQUAL_FIXED_SHAPE_SUBCASE( array, expected_shape, A, B );
    }
    {
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{{1,2,3},{4,5,6}}};
        constexpr auto expected_shape = std::array{2,3};
        GREATER_EQUAL_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A, B );
    }
}
#endif