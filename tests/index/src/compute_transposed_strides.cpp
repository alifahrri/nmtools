#include "nmtools/index/compute_strides.hpp"
#include "nmtools/testing/data/index/compute_transposed_strides.hpp"
#include "nmtools/utility/isequal.hpp"
#include "nmtools/testing/doctest.hpp"

using nmtools::utils::isequal;
using namespace nmtools::literals;

#define COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(compute_transposed_strides, case_name); \
    using namespace args; \
    auto result = nmtools::index::compute_transposed_strides(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::result, __VA_ARGS__ ); \
}

TEST_CASE("compute_transposed_strides(case1)" * doctest::test_suite("index::compute_transposed_strides"))
{
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case1, shape, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case1, shape_a, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case1, shape_v, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case1, shape_f, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case1, shape_h, axes);

    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case1, m_shape_a, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case1, m_shape_v, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case1, m_shape_f, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case1, m_shape_h, axes);

    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case1, shape_ct, axes_ct);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case1, shape_mx1, axes_ct);
}

TEST_CASE("compute_transposed_strides(case2)" * doctest::test_suite("index::compute_transposed_strides"))
{
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case2, shape, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case2, shape_a, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case2, shape_v, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case2, shape_f, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case2, shape_h, axes);
}

TEST_CASE("compute_transposed_strides(case3)" * doctest::test_suite("index::compute_transposed_strides"))
{
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case3, shape, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case3, shape_a, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case3, shape_v, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case3, shape_f, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case3, shape_h, axes);

    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case3, m_shape_a, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case3, m_shape_v, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case3, m_shape_f, axes);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case3, m_shape_h, axes);

    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case3, shape_ct, axes_ct);
}

TEST_CASE("compute_transposed_strides(case4)" * doctest::test_suite("index::compute_transposed_strides"))
{
    // default axes (None) reverses the strides
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case4, shape);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case4, shape_a);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case4, shape_v);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case4, shape_f);
    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case4, shape_h);

    COMPUTE_TRANSPOSED_STRIDES_SUBCASE(case4, shape_ct);
}
