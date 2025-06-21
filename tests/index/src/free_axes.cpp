#include "nmtools/index/free_axes.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/index/free_axes.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace meta = nm::meta;
namespace kind = na::kind;

#define FREE_AXES_SUBCASE(case_name, a, b) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(free_axes, case_name); \
    auto result = ::nmtools::index::free_axes(args::a, args::b); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES(result, expect::x, args::a, args::b); \
}

TEST_CASE("free_axes(case1)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case1, a, b);
    FREE_AXES_SUBCASE(case1, a_a, b_a);
    FREE_AXES_SUBCASE(case1, a_v, b_v);
    FREE_AXES_SUBCASE(case1, a_f, b_f);
    FREE_AXES_SUBCASE(case1, a_h, b_h);

    FREE_AXES_SUBCASE(case1, m_a_a, b_a);
    FREE_AXES_SUBCASE(case1, m_a_v, b_v);
    FREE_AXES_SUBCASE(case1, m_a_f, b_f);
    FREE_AXES_SUBCASE(case1, m_a_h, b_h);

    FREE_AXES_SUBCASE(case1, a_a, m_b_a);
    FREE_AXES_SUBCASE(case1, a_v, m_b_v);
    FREE_AXES_SUBCASE(case1, a_f, m_b_f);
    FREE_AXES_SUBCASE(case1, a_h, m_b_h);

    FREE_AXES_SUBCASE(case1, m_a_a, m_b_a);
    FREE_AXES_SUBCASE(case1, m_a_v, m_b_v);
    FREE_AXES_SUBCASE(case1, m_a_f, m_b_f);
    FREE_AXES_SUBCASE(case1, m_a_h, m_b_h);

    FREE_AXES_SUBCASE(case1, a_ct, b_ct);
}

TEST_CASE("free_axes(case2)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case2, a, b);
    FREE_AXES_SUBCASE(case2, a_a, b_a);
    FREE_AXES_SUBCASE(case2, a_v, b_v);
    FREE_AXES_SUBCASE(case2, a_f, b_f);
    FREE_AXES_SUBCASE(case2, a_h, b_h);

    FREE_AXES_SUBCASE(case2, m_a_a, b_a);
    FREE_AXES_SUBCASE(case2, m_a_v, b_v);
    FREE_AXES_SUBCASE(case2, m_a_f, b_f);
    FREE_AXES_SUBCASE(case2, m_a_h, b_h);

    FREE_AXES_SUBCASE(case2, a_a, m_b_a);
    FREE_AXES_SUBCASE(case2, a_v, m_b_v);
    FREE_AXES_SUBCASE(case2, a_f, m_b_f);
    FREE_AXES_SUBCASE(case2, a_h, m_b_h);

    FREE_AXES_SUBCASE(case2, m_a_a, m_b_a);
    FREE_AXES_SUBCASE(case2, m_a_v, m_b_v);
    FREE_AXES_SUBCASE(case2, m_a_f, m_b_f);
    FREE_AXES_SUBCASE(case2, m_a_h, m_b_h);
}

TEST_CASE("free_axes(case3)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case2, a, b);
    FREE_AXES_SUBCASE(case3, a_a, b_a);
    FREE_AXES_SUBCASE(case3, a_v, b_v);
    FREE_AXES_SUBCASE(case3, a_f, b_f);
    FREE_AXES_SUBCASE(case3, a_h, b_h);

    FREE_AXES_SUBCASE(case3, m_a_a, b_a);
    FREE_AXES_SUBCASE(case3, m_a_v, b_v);
    FREE_AXES_SUBCASE(case3, m_a_f, b_f);
    FREE_AXES_SUBCASE(case3, m_a_h, b_h);

    FREE_AXES_SUBCASE(case3, a_a, m_b_a);
    FREE_AXES_SUBCASE(case3, a_v, m_b_v);
    FREE_AXES_SUBCASE(case3, a_f, m_b_f);
    FREE_AXES_SUBCASE(case3, a_h, m_b_h);

    FREE_AXES_SUBCASE(case3, m_a_a, m_b_a);
    FREE_AXES_SUBCASE(case3, m_a_v, m_b_v);
    FREE_AXES_SUBCASE(case3, m_a_f, m_b_f);
    FREE_AXES_SUBCASE(case3, m_a_h, m_b_h);
}

TEST_CASE("free_axes(case4)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case4, a, b);
    FREE_AXES_SUBCASE(case4, a_a, b_a);
    FREE_AXES_SUBCASE(case4, a_v, b_v);
    FREE_AXES_SUBCASE(case4, a_f, b_f);
    FREE_AXES_SUBCASE(case4, a_h, b_h);

    FREE_AXES_SUBCASE(case4, m_a_a, b_a);
    FREE_AXES_SUBCASE(case4, m_a_v, b_v);
    FREE_AXES_SUBCASE(case4, m_a_f, b_f);
    FREE_AXES_SUBCASE(case4, m_a_h, b_h);

    FREE_AXES_SUBCASE(case4, a_a, m_b_a);
    FREE_AXES_SUBCASE(case4, a_v, m_b_v);
    FREE_AXES_SUBCASE(case4, a_f, m_b_f);
    FREE_AXES_SUBCASE(case4, a_h, m_b_h);

    FREE_AXES_SUBCASE(case4, m_a_a, m_b_a);
    FREE_AXES_SUBCASE(case4, m_a_v, m_b_v);
    FREE_AXES_SUBCASE(case4, m_a_f, m_b_f);
    FREE_AXES_SUBCASE(case4, m_a_h, m_b_h);
}

TEST_CASE("free_axes(case5)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case5, a, b);
    FREE_AXES_SUBCASE(case5, a_a, b_a);
    FREE_AXES_SUBCASE(case5, a_v, b_v);
    FREE_AXES_SUBCASE(case5, a_f, b_f);
    FREE_AXES_SUBCASE(case5, a_h, b_h);

    FREE_AXES_SUBCASE(case5, m_a_a, b_a);
    FREE_AXES_SUBCASE(case5, m_a_v, b_v);
    FREE_AXES_SUBCASE(case5, m_a_f, b_f);
    FREE_AXES_SUBCASE(case5, m_a_h, b_h);

    FREE_AXES_SUBCASE(case5, a_a, m_b_a);
    FREE_AXES_SUBCASE(case5, a_v, m_b_v);
    FREE_AXES_SUBCASE(case5, a_f, m_b_f);
    FREE_AXES_SUBCASE(case5, a_h, m_b_h);

    FREE_AXES_SUBCASE(case5, m_a_a, m_b_a);
    FREE_AXES_SUBCASE(case5, m_a_v, m_b_v);
    FREE_AXES_SUBCASE(case5, m_a_f, m_b_f);
    FREE_AXES_SUBCASE(case5, m_a_h, m_b_h);
}