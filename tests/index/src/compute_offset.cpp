#include "nmtools/index/compute_offset.hpp"
#include "nmtools/testing/data/index/compute_offset.hpp"
#include "nmtools/testing/doctest.hpp"

#define COMPUTE_OFFSET_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, compute_offset, case_name); \
    using namespace args; \
    auto offset = nmtools::index::compute_offset(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( offset, expect::result, __VA_ARGS__ ); \
}

#define COMPUTE_OFFSET_RESULT_SUBCASE(case_name, result, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, compute_offset, case_name); \
    using namespace args; \
    auto offset = nmtools::index::compute_offset(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( offset, expect::result, __VA_ARGS__ ); \
}

TEST_CASE("compute_offset(case1a)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case1a, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case1a, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1a, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1a, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1a, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1a, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_ct, strides_cl);

    COMPUTE_OFFSET_SUBCASE(case1a, m_indices_a, m_strides_a);
    COMPUTE_OFFSET_SUBCASE(case1a, m_indices_f, m_strides_f);
    COMPUTE_OFFSET_SUBCASE(case1a, m_indices_h, m_strides_h);
    COMPUTE_OFFSET_SUBCASE(case1a, m_indices_v, m_strides_v);

    COMPUTE_OFFSET_SUBCASE(case1a, m_indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1a, m_indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1a, m_indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1a, m_indices_v, strides_v);

    COMPUTE_OFFSET_SUBCASE(case1a, indices_a, m_strides_a);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_f, m_strides_f);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_h, m_strides_h);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_v, m_strides_v);

    COMPUTE_OFFSET_RESULT_SUBCASE(case1a, result_nl1, indices_nl1, strides_nl1);
    
    COMPUTE_OFFSET_SUBCASE(case1a, indices_mx1, strides_mx1);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case1a, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_ct, shape_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_mx1, shape_mx1, strides_mx1);
    COMPUTE_OFFSET_SUBCASE(case1a, indices_mx2, shape_mx2, strides_mx2);

    COMPUTE_OFFSET_RESULT_SUBCASE(case1a, result_nl1, indices_nl1, shape_nl1, strides_nl1);
    COMPUTE_OFFSET_RESULT_SUBCASE(case1a, result_nl2, indices_nl2, shape_nl2, strides_nl2);
}

TEST_CASE("compute_offset(case1b)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case1b, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case1b, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1b, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1b, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1b, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1b, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1b, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_ct, strides_cl);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case1b, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case1b, indices_ct, shape_ct, strides_ct);
}

TEST_CASE("compute_offset(case1c)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case1c, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case1c, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1c, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1c, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1c, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1c, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1c, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_ct, strides_cl);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case1c, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case1c, indices_ct, shape_ct, strides_ct);
}

TEST_CASE("compute_offset(case1d)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case1d, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case1d, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1d, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1d, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1d, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1d, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1d, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_ct, strides_cl);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case1d, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case1d, indices_ct, shape_ct, strides_ct);
}

TEST_CASE("compute_offset(case1e)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case1e, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case1e, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1e, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1e, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1e, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1e, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1e, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_ct, strides_cl);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case1e, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case1e, indices_ct, shape_ct, strides_ct);
}

TEST_CASE("compute_offset(case1f)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case1f, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case1f, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case1f, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case1f, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case1f, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case1f, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case1f, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_ct, strides_cl);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case1f, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case1f, indices_ct, shape_ct, strides_ct);
}

TEST_CASE("compute_offset(case2a)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case2a, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case2a, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2a, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2a, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2a, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2a, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_ct, strides_cl);

    COMPUTE_OFFSET_SUBCASE(case2a, m_indices_a, m_strides_a);
    COMPUTE_OFFSET_SUBCASE(case2a, m_indices_f, m_strides_f);
    COMPUTE_OFFSET_SUBCASE(case2a, m_indices_h, m_strides_h);
    COMPUTE_OFFSET_SUBCASE(case2a, m_indices_v, m_strides_v);

    COMPUTE_OFFSET_SUBCASE(case2a, m_indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2a, m_indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2a, m_indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2a, m_indices_v, strides_v);

    COMPUTE_OFFSET_SUBCASE(case2a, indices_a, m_strides_a);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_f, m_strides_f);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_h, m_strides_h);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_v, m_strides_v);

    COMPUTE_OFFSET_RESULT_SUBCASE(case2a, result_nl1, indices_nl1, strides_nl1);

    COMPUTE_OFFSET_SUBCASE(case2a, indices_mx1, strides_mx1);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case2a, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_ct, shape_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2a, indices_mx1, shape_mx1, strides_mx1);

    COMPUTE_OFFSET_RESULT_SUBCASE(case2a, result_nl1, indices_nl1, shape_nl1, strides_nl1);
}

TEST_CASE("compute_offset(case2b)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case2b, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case2b, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2b, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2b, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2b, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2b, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2b, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_ct, strides_cl);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case2b, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case2b, indices_ct, shape_ct, strides_ct);
}

TEST_CASE("compute_offset(case2c)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case2c, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case2c, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2c, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2c, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2c, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2c, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2c, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_ct, strides_cl);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case2c, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case2c, indices_ct, shape_ct, strides_ct);
}

TEST_CASE("compute_offset(case2d)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case2d, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case2d, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2d, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2d, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2d, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2d, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2d, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_ct, strides_cl);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case2d, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case2d, indices_ct, shape_ct, strides_ct);
}

TEST_CASE("compute_offset(case2e)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case2e, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case2e, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2e, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2e, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2e, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2e, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2e, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_ct, strides_cl);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case2e, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case2e, indices_ct, shape_ct, strides_ct);
}

TEST_CASE("compute_offset(case2f)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case2f, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case2f, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2f, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2f, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2f, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2f, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2f, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_ct, strides_cl);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case2f, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case2f, indices_ct, shape_ct, strides_ct);
}

TEST_CASE("compute_offset(case2g)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case2g, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case2g, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2g, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2g, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2g, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2g, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2g, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_ct, strides_cl);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case2g, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case2g, indices_ct, shape_ct, strides_ct);
}

TEST_CASE("compute_offset(case2h)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case2h, indices, strides);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_a, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_f, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_h, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_v, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_ct, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_cl, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_a, strides);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_f, strides);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_h, strides);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_v, strides);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_ct, strides);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_cl, strides);
    COMPUTE_OFFSET_SUBCASE(case2h, indices, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_f, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_h, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_v, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_ct, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_cl, strides_a);
    COMPUTE_OFFSET_SUBCASE(case2h, indices, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_a, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_h, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_v, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_ct, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_cl, strides_f);
    COMPUTE_OFFSET_SUBCASE(case2h, indices, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_f, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_a, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_v, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_ct, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_cl, strides_h);
    COMPUTE_OFFSET_SUBCASE(case2h, indices, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_a, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_f, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_h, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_ct, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_cl, strides_v);
    COMPUTE_OFFSET_SUBCASE(case2h, indices, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_a, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_f, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_h, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_v, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_cl, strides_ct);
    COMPUTE_OFFSET_SUBCASE(case2h, indices, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_a, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_f, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_h, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_v, strides_cl);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_ct, strides_cl);

    // overloaded version that can handle nested shape/stride/indices
    COMPUTE_OFFSET_SUBCASE(case2h, indices, shape, strides);
    COMPUTE_OFFSET_SUBCASE(case2h, indices_ct, shape_ct, strides_ct);
}

TEST_CASE("compute_offset(case3a)" * doctest::test_suite("index::compute_offset"))
{
    // trait tests
    {
        NMTOOLS_TESTING_USE_CASE(index, compute_offset, case3a);
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_nested_index_array, decltype(nested_shape_a) );
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_nested_index_array, decltype(nested_strides_a) );
        {
            [[maybe_unused]]
            const auto i = nmtools::ct_v<0>;
            const auto shape_i   = nmtools::at(nested_shape_a,i);
            const auto indices_i = nmtools::at(indices,i);
            const auto strides_i = nmtools::at(nested_strides_a,i);

            using shape_i_t   = decltype(shape_i);
            using strides_i_t = decltype(strides_i);
            using indices_i_t [[maybe_unused]] = decltype(indices_i);
            NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_index, shape_i_t );
            NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_index, strides_i_t );
        }
        {
            [[maybe_unused]]
            const auto i = nmtools::ct_v<1>;
            const auto shape_i   = nmtools::at(nested_shape_a,i);
            const auto indices_i = nmtools::at(indices,i);
            const auto strides_i = nmtools::at(nested_strides_a,i);

            using shape_i_t   = decltype(shape_i);
            using strides_i_t = decltype(strides_i);
            using indices_i_t [[maybe_unused]] = decltype(indices_i);
            NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_index_array, shape_i_t );
            NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_index_array, strides_i_t );
        }
    }
}

TEST_CASE("compute_offset(case3a)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3a, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3a, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3a, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3a, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3a, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3b)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3b, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3b, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3b, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3b, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3b, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3c)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3c, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3c, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3c, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3c, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3c, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3d)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3d, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3d, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3d, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3d, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3d, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3e)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3e, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3e, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3e, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3e, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3e, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3f)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3f, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3f, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3f, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3f, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3f, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3g)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3g, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3g, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3g, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3g, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3g, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3h)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3h, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3h, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3h, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3h, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3h, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3i)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3i, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3i, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3i, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3i, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3i, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3j)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3j, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3j, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3j, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3j, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3j, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3k)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3k, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3k, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3k, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3k, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3k, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3l)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3l, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3l, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3l, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3l, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3l, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3m)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3m, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3m, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3m, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3m, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3m, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3n)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3n, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3n, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3n, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3n, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3n, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3o)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3o, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3o, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3o, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3o, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3o, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case3p)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case3p, indices_a, nested_shape_a, nested_strides_a);
    COMPUTE_OFFSET_SUBCASE(case3p, indices_h, nested_shape_h, nested_strides_h);
    COMPUTE_OFFSET_SUBCASE(case3p, indices_v, nested_shape_v, nested_strides_v);
    COMPUTE_OFFSET_SUBCASE(case3p, indices_f, nested_shape_f, nested_strides_f);

    COMPUTE_OFFSET_SUBCASE(case3p, indices_ct, nested_shape_ct, nested_strides_ct);
}

TEST_CASE("compute_offset(case4a)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case4a, indices, shape, striding);
    COMPUTE_OFFSET_SUBCASE(case4a, indices_a, shape_a, striding_a);
    COMPUTE_OFFSET_SUBCASE(case4a, indices_h, shape_h, striding_h);
    COMPUTE_OFFSET_SUBCASE(case4a, indices_v, shape_v, striding_v);
    COMPUTE_OFFSET_SUBCASE(case4a, indices_f, shape_f, striding_f);
    COMPUTE_OFFSET_SUBCASE(case4a, indices_ct, shape_ct, striding_ct);
}

TEST_CASE("compute_offset(case4b)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case4b, indices, shape, striding);
    COMPUTE_OFFSET_SUBCASE(case4b, indices_a, shape_a, striding_a);
    COMPUTE_OFFSET_SUBCASE(case4b, indices_h, shape_h, striding_h);
    COMPUTE_OFFSET_SUBCASE(case4b, indices_v, shape_v, striding_v);
    COMPUTE_OFFSET_SUBCASE(case4b, indices_f, shape_f, striding_f);
    COMPUTE_OFFSET_SUBCASE(case4b, indices_ct, shape_ct, striding_ct);
}

TEST_CASE("compute_offset(case4c)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case4c, indices, shape, striding);
    COMPUTE_OFFSET_SUBCASE(case4c, indices_a, shape_a, striding_a);
    COMPUTE_OFFSET_SUBCASE(case4c, indices_h, shape_h, striding_h);
    COMPUTE_OFFSET_SUBCASE(case4c, indices_v, shape_v, striding_v);
    COMPUTE_OFFSET_SUBCASE(case4c, indices_f, shape_f, striding_f);
    COMPUTE_OFFSET_SUBCASE(case4c, indices_ct, shape_ct, striding_ct);
}

TEST_CASE("compute_offset(case4d)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case4d, indices, shape, striding);
    COMPUTE_OFFSET_SUBCASE(case4d, indices_a, shape_a, striding_a);
    COMPUTE_OFFSET_SUBCASE(case4d, indices_h, shape_h, striding_h);
    COMPUTE_OFFSET_SUBCASE(case4d, indices_v, shape_v, striding_v);
    COMPUTE_OFFSET_SUBCASE(case4d, indices_f, shape_f, striding_f);
    COMPUTE_OFFSET_SUBCASE(case4d, indices_ct, shape_ct, striding_ct);
}

TEST_CASE("compute_offset(case4e)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case4e, indices, shape, striding);
    COMPUTE_OFFSET_SUBCASE(case4e, indices_a, shape_a, striding_a);
    COMPUTE_OFFSET_SUBCASE(case4e, indices_h, shape_h, striding_h);
    COMPUTE_OFFSET_SUBCASE(case4e, indices_v, shape_v, striding_v);
    COMPUTE_OFFSET_SUBCASE(case4e, indices_f, shape_f, striding_f);
    COMPUTE_OFFSET_SUBCASE(case4e, indices_ct, shape_ct, striding_ct);
}

TEST_CASE("compute_offset(case4f)" * doctest::test_suite("index::compute_offset"))
{
    COMPUTE_OFFSET_SUBCASE(case4f, indices, shape, striding);
    COMPUTE_OFFSET_SUBCASE(case4f, indices_a, shape_a, striding_a);
    COMPUTE_OFFSET_SUBCASE(case4f, indices_h, shape_h, striding_h);
    COMPUTE_OFFSET_SUBCASE(case4f, indices_v, shape_v, striding_v);
    COMPUTE_OFFSET_SUBCASE(case4f, indices_f, shape_f, striding_f);
    COMPUTE_OFFSET_SUBCASE(case4f, indices_ct, shape_ct, striding_ct);
}