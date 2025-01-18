#include "nmtools/array/group_norm.hpp"
#include "nmtools/testing/data/array/group_norm.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nmtools::view;

#define GROUP_NORM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, group_norm, case_name); \
    using namespace args; \
    auto result = nmtools::view::group_norm(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("group_norm(case1)" * doctest::test_suite("view::group_norm"))
{
    GROUP_NORM_SUBCASE( case1, input,   num_groups, weight,   bias );
    GROUP_NORM_SUBCASE( case1, input_a, num_groups, weight_a, bias_a );
    GROUP_NORM_SUBCASE( case1, input_f, num_groups, weight_f, bias_f );
    GROUP_NORM_SUBCASE( case1, input_h, num_groups, weight_h, bias_h );
    GROUP_NORM_SUBCASE( case1, input_d, num_groups, weight_d, bias_d );
}

TEST_CASE("group_norm(case2)" * doctest::test_suite("view::group_norm"))
{
    GROUP_NORM_SUBCASE( case2, input,   num_groups, weight,   bias );
    GROUP_NORM_SUBCASE( case2, input_a, num_groups, weight_a, bias_a );
    GROUP_NORM_SUBCASE( case2, input_f, num_groups, weight_f, bias_f );
    GROUP_NORM_SUBCASE( case2, input_h, num_groups, weight_h, bias_h );
    GROUP_NORM_SUBCASE( case2, input_d, num_groups, weight_d, bias_d );
}

TEST_CASE("group_norm(case3)" * doctest::test_suite("view::group_norm"))
{
    GROUP_NORM_SUBCASE( case3, input,   num_groups, weight,   bias );
    GROUP_NORM_SUBCASE( case3, input_a, num_groups, weight_a, bias_a );
    GROUP_NORM_SUBCASE( case3, input_f, num_groups, weight_f, bias_f );
    GROUP_NORM_SUBCASE( case3, input_h, num_groups, weight_h, bias_h );
    GROUP_NORM_SUBCASE( case3, input_d, num_groups, weight_d, bias_d );
}

TEST_CASE("group_norm(case4)" * doctest::test_suite("view::group_norm"))
{
    GROUP_NORM_SUBCASE( case4, input,   num_groups, weight,   bias );
    GROUP_NORM_SUBCASE( case4, input_a, num_groups, weight_a, bias_a );
    GROUP_NORM_SUBCASE( case4, input_f, num_groups, weight_f, bias_f );
    GROUP_NORM_SUBCASE( case4, input_h, num_groups, weight_h, bias_h );
    GROUP_NORM_SUBCASE( case4, input_d, num_groups, weight_d, bias_d );
}

TEST_CASE("group_norm(case5)" * doctest::test_suite("view::group_norm"))
{
    GROUP_NORM_SUBCASE( case5, input,   num_groups, weight,   bias );
    GROUP_NORM_SUBCASE( case5, input_a, num_groups, weight_a, bias_a );
    GROUP_NORM_SUBCASE( case5, input_f, num_groups, weight_f, bias_f );
    GROUP_NORM_SUBCASE( case5, input_h, num_groups, weight_h, bias_h );
    GROUP_NORM_SUBCASE( case5, input_d, num_groups, weight_d, bias_d );
}

TEST_CASE("group_norm(case6)" * doctest::test_suite("view::group_norm"))
{
    GROUP_NORM_SUBCASE( case6, input,   num_groups, weight,   bias );
    GROUP_NORM_SUBCASE( case6, input_a, num_groups, weight_a, bias_a );
    GROUP_NORM_SUBCASE( case6, input_f, num_groups, weight_f, bias_f );
    GROUP_NORM_SUBCASE( case6, input_h, num_groups, weight_h, bias_h );
    GROUP_NORM_SUBCASE( case6, input_d, num_groups, weight_d, bias_d );
}