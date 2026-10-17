#include "nmtools/index/compute_strides.hpp"
#include "nmtools/testing/data/index/is_row_major.hpp"
#include "nmtools/utility/isequal.hpp"
#include "nmtools/testing/doctest.hpp"

using nmtools::utils::isequal;
using namespace nmtools::literals;

#define IS_ROW_MAJOR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(is_row_major, case_name); \
    using namespace args; \
    auto result = nmtools::index::is_row_major(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::result, __VA_ARGS__ ); \
}

#define CONSTEXPR_IS_ROW_MAJOR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(is_row_major, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::index::is_row_major(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::result, __VA_ARGS__ ); \
}

#define IS_COL_MAJOR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(is_col_major, case_name); \
    using namespace args; \
    auto result = nmtools::index::is_col_major(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::result, __VA_ARGS__ ); \
}

TEST_CASE("is_row_major(case1)" * doctest::test_suite("index::is_row_major"))
{
    IS_ROW_MAJOR_SUBCASE(case1, shape, strides);
    IS_ROW_MAJOR_SUBCASE(case1, shape_a, strides_a);
    IS_ROW_MAJOR_SUBCASE(case1, shape_f, strides_f);
    CONSTEXPR_IS_ROW_MAJOR_SUBCASE(case1, shape_ct, strides_ct);
}

TEST_CASE("is_row_major(case2)" * doctest::test_suite("index::is_row_major"))
{
    IS_ROW_MAJOR_SUBCASE(case2, shape, strides);
    IS_ROW_MAJOR_SUBCASE(case2, shape_a, strides_a);
    IS_ROW_MAJOR_SUBCASE(case2, shape_f, strides_f);
    CONSTEXPR_IS_ROW_MAJOR_SUBCASE(case2, shape_ct, strides_ct);
}

TEST_CASE("is_row_major(case3)" * doctest::test_suite("index::is_row_major"))
{
    // degenerate dim has don't care stride
    IS_ROW_MAJOR_SUBCASE(case3, shape, strides);
    IS_ROW_MAJOR_SUBCASE(case3, shape_a, strides_a);
}

TEST_CASE("is_row_major(case4)" * doctest::test_suite("index::is_row_major"))
{
    // broadcast zero-stride on a real dim
    IS_ROW_MAJOR_SUBCASE(case4, shape, strides);
    IS_ROW_MAJOR_SUBCASE(case4, shape_a, strides_a);
}

TEST_CASE("is_row_major(case5)" * doctest::test_suite("index::is_row_major"))
{
    // padded leading dimension
    IS_ROW_MAJOR_SUBCASE(case5, shape, strides);
    IS_ROW_MAJOR_SUBCASE(case5, shape_a, strides_a);
}

TEST_CASE("is_row_major(case6)" * doctest::test_suite("index::is_row_major"))
{
    // unknown stride cannot prove a match
    IS_ROW_MAJOR_SUBCASE(case6, shape, strides);
}

TEST_CASE("is_row_major(case7)" * doctest::test_suite("index::is_row_major"))
{
    // known nullable strides still match
    IS_ROW_MAJOR_SUBCASE(case7, shape, strides);
}

TEST_CASE("is_row_major(case8)" * doctest::test_suite("index::is_row_major"))
{
    // maybe-wrapped strides propagate to a maybe result
    IS_ROW_MAJOR_SUBCASE(case8, shape, m_strides_a);
    IS_ROW_MAJOR_SUBCASE(case8, shape, m_strides_f);
}

TEST_CASE("is_row_major(case9)" * doctest::test_suite("index::is_row_major"))
{
    IS_ROW_MAJOR_SUBCASE(case9, shape, strides);
    IS_ROW_MAJOR_SUBCASE(case9, shape_a, strides_a);
}

TEST_CASE("is_col_major(case1)" * doctest::test_suite("index::is_col_major"))
{
    IS_COL_MAJOR_SUBCASE(case1, shape, strides);
    IS_COL_MAJOR_SUBCASE(case1, shape_a, strides_a);
    IS_COL_MAJOR_SUBCASE(case1, shape_f, strides_f);
}

TEST_CASE("is_col_major(case2)" * doctest::test_suite("index::is_col_major"))
{
    IS_COL_MAJOR_SUBCASE(case2, shape, strides);
    IS_COL_MAJOR_SUBCASE(case2, shape_a, strides_a);
    IS_COL_MAJOR_SUBCASE(case2, shape_f, strides_f);
}

TEST_CASE("is_col_major(case3)" * doctest::test_suite("index::is_col_major"))
{
    // degenerate dim has don't care stride
    IS_COL_MAJOR_SUBCASE(case3, shape, strides);
    IS_COL_MAJOR_SUBCASE(case3, shape_a, strides_a);
}

TEST_CASE("is_col_major(case4)" * doctest::test_suite("index::is_col_major"))
{
    // padded col-major with gaps
    IS_COL_MAJOR_SUBCASE(case4, shape, strides);
    IS_COL_MAJOR_SUBCASE(case4, shape_a, strides_a);
}
