#include "nmtools/index/slice.hpp"
#include "nmtools/testing/data/index/compute_index.hpp"
#include "nmtools/testing/doctest.hpp"

using namespace nmtools::literals;

#define COMPUTE_INDEX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, compute_index, case_name); \
    using namespace args; \
    auto result = nmtools::index::compute_index(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("compute_index(case1)" * doctest::test_suite("index::compute_index"))
{
    COMPUTE_INDEX_SUBCASE(case1, indices, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case1, indices_a, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case1, indices_v, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case1, indices_f, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case1, indices_h, si, start, stop, step, i_i);
}

TEST_CASE("compute_index(case2)" * doctest::test_suite("index::compute_index"))
{
    COMPUTE_INDEX_SUBCASE(case2, indices, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case2, indices_a, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case2, indices_v, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case2, indices_f, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case2, indices_h, si, start, stop, step, i_i);
}

TEST_CASE("compute_index(case3)" * doctest::test_suite("index::compute_index"))
{
    COMPUTE_INDEX_SUBCASE(case3, indices, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case3, indices_a, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case3, indices_v, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case3, indices_f, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case3, indices_h, si, start, stop, step, i_i);
}

TEST_CASE("compute_index(case4)" * doctest::test_suite("index::compute_index"))
{
    COMPUTE_INDEX_SUBCASE(case4, indices, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case4, indices_a, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case4, indices_v, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case4, indices_f, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case4, indices_h, si, start, stop, step, i_i);
}

TEST_CASE("compute_index(case5)" * doctest::test_suite("index::compute_index"))
{
    COMPUTE_INDEX_SUBCASE(case5, indices, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case5, indices_a, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case5, indices_v, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case5, indices_f, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case5, indices_h, si, start, stop, step, i_i);
}

TEST_CASE("compute_index(case6)" * doctest::test_suite("index::compute_index"))
{
    COMPUTE_INDEX_SUBCASE(case6, indices, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case6, indices_a, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case6, indices_v, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case6, indices_f, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case6, indices_h, si, start, stop, step, i_i);
}

TEST_CASE("compute_index(case7)" * doctest::test_suite("index::compute_index"))
{
    COMPUTE_INDEX_SUBCASE(case7, indices, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case7, indices_a, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case7, indices_v, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case7, indices_f, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case7, indices_h, si, start, stop, step, i_i);
}

TEST_CASE("compute_index(case8)" * doctest::test_suite("index::compute_index"))
{
    COMPUTE_INDEX_SUBCASE(case8, indices, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case8, indices_a, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case8, indices_v, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case8, indices_f, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case8, indices_h, si, start, stop, step, i_i);
}

TEST_CASE("compute_index(case9)" * doctest::test_suite("index::compute_index"))
{
    COMPUTE_INDEX_SUBCASE(case9, indices, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case9, indices_a, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case9, indices_v, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case9, indices_f, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case9, indices_h, si, start, stop, step, i_i);
}

TEST_CASE("compute_index(case10)" * doctest::test_suite("index::compute_index"))
{
    COMPUTE_INDEX_SUBCASE(case10, indices, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case10, indices_a, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case10, indices_v, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case10, indices_f, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case10, indices_h, si, start, stop, step, i_i);
}

TEST_CASE("compute_index(case11)" * doctest::test_suite("index::compute_index"))
{
    COMPUTE_INDEX_SUBCASE(case11, indices, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case11, indices_a, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case11, indices_v, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case11, indices_f, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case11, indices_h, si, start, stop, step, i_i);
}

TEST_CASE("compute_index(case12)" * doctest::test_suite("index::compute_index"))
{
    COMPUTE_INDEX_SUBCASE(case12, indices, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case12, indices_a, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case12, indices_v, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case12, indices_f, si, start, stop, step, i_i);
    COMPUTE_INDEX_SUBCASE(case12, indices_h, si, start, stop, step, i_i);
}
