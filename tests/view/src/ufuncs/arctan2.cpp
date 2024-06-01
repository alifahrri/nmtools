#include "nmtools/array/view/ufuncs/arctan2.hpp"
#include "nmtools/testing/data/array/arctan2.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define ARCTAN2_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arctan2, case_name); \
    using namespace args; \
    auto result = view::arctan2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arctan2(case1)" * doctest::test_suite("view::arctan2"))
{
    ARCTAN2_SUBCASE( case1,   a,   b );
    ARCTAN2_SUBCASE( case1, a_a, b_a );
    ARCTAN2_SUBCASE( case1, a_f, b_f );
    ARCTAN2_SUBCASE( case1, a_d, b_d );
    ARCTAN2_SUBCASE( case1, a_h, b_h );
}


#define ARCTAN2_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_arctan2(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

// TODO: fix
#if 0
TEST_CASE("arctan2(fixed_shape)" * doctest::test_suite("view::arctan2"))
{
    namespace meta = nmtools::meta;
    {
        constexpr auto expected_shape = std::array{3};
        int A[3] = {1,2,3};
        int B[3] = {1,2,3};
        ARCTAN2_FIXED_SHAPE_SUBCASE( raw, expected_shape, A, B );
    }
    {
        constexpr auto expected_shape = std::array{3};
        auto A = std::array{1,2,3};
        auto B = std::array{1,2,3};
        ARCTAN2_FIXED_SHAPE_SUBCASE( array, expected_shape, A, B );
    }
    {
        constexpr auto expected_shape = std::array{3};
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{1,2,3}};
        ARCTAN2_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A, B );
    }
}
#endif