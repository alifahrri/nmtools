#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/testing/data/index/compute_strides.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/testing/doctest.hpp"

using nmtools::utils::isequal;
using namespace nmtools::literals;

#define COMPUTE_STRIDES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(compute_strides, case_name); \
    using namespace args; \
    auto result = nmtools::index::compute_strides(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::result, __VA_ARGS__ ); \
}

TEST_CASE("compute_strides(case1)" * doctest::test_suite("index::compute_strides"))
{
    COMPUTE_STRIDES_SUBCASE(case1, shape);
    COMPUTE_STRIDES_SUBCASE(case1, shape_a);
    COMPUTE_STRIDES_SUBCASE(case1, shape_v);
    COMPUTE_STRIDES_SUBCASE(case1, shape_f);
    COMPUTE_STRIDES_SUBCASE(case1, shape_h);

    COMPUTE_STRIDES_SUBCASE(case1, m_shape_a);
    COMPUTE_STRIDES_SUBCASE(case1, m_shape_v);
    COMPUTE_STRIDES_SUBCASE(case1, m_shape_f);
    COMPUTE_STRIDES_SUBCASE(case1, m_shape_h);

    COMPUTE_STRIDES_SUBCASE(case1, shape_ct);
}

TEST_CASE("compute_strides(case2)" * doctest::test_suite("index::compute_strides"))
{
    COMPUTE_STRIDES_SUBCASE(case2, shape);
    COMPUTE_STRIDES_SUBCASE(case2, shape_a);
    COMPUTE_STRIDES_SUBCASE(case2, shape_v);
    COMPUTE_STRIDES_SUBCASE(case2, shape_f);
    COMPUTE_STRIDES_SUBCASE(case2, shape_h);

    COMPUTE_STRIDES_SUBCASE(case2, m_shape_a);
    COMPUTE_STRIDES_SUBCASE(case2, m_shape_v);
    COMPUTE_STRIDES_SUBCASE(case2, m_shape_f);
    COMPUTE_STRIDES_SUBCASE(case2, m_shape_h);

    COMPUTE_STRIDES_SUBCASE(case2, shape_ct);
}

TEST_CASE("compute_strides(case3)" * doctest::test_suite("index::compute_strides"))
{
    COMPUTE_STRIDES_SUBCASE(case3, shape);
    COMPUTE_STRIDES_SUBCASE(case3, shape_a);
    COMPUTE_STRIDES_SUBCASE(case3, shape_v);
    COMPUTE_STRIDES_SUBCASE(case3, shape_f);
    COMPUTE_STRIDES_SUBCASE(case3, shape_h);

    COMPUTE_STRIDES_SUBCASE(case3, m_shape_a);
    COMPUTE_STRIDES_SUBCASE(case3, m_shape_v);
    COMPUTE_STRIDES_SUBCASE(case3, m_shape_f);
    COMPUTE_STRIDES_SUBCASE(case3, m_shape_h);

    COMPUTE_STRIDES_SUBCASE(case3, shape_ct);
}

TEST_CASE("compute_strides(case4)" * doctest::test_suite("index::compute_strides"))
{
    COMPUTE_STRIDES_SUBCASE(case4, shape);
    COMPUTE_STRIDES_SUBCASE(case4, shape_a);
    COMPUTE_STRIDES_SUBCASE(case4, shape_v);
    COMPUTE_STRIDES_SUBCASE(case4, shape_f);
    COMPUTE_STRIDES_SUBCASE(case4, shape_h);

    COMPUTE_STRIDES_SUBCASE(case4, m_shape_a);
    COMPUTE_STRIDES_SUBCASE(case4, m_shape_v);
    COMPUTE_STRIDES_SUBCASE(case4, m_shape_f);
    COMPUTE_STRIDES_SUBCASE(case4, m_shape_h);

    COMPUTE_STRIDES_SUBCASE(case4, shape_ct);
}