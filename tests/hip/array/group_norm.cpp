#include "nmtools/evaluator/hip.hpp"
#include "nmtools/array/group_norm.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/data/array/group_norm.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nmtools::view;

// TODO: fix to accept maybe type
using nmtools_array, nmtools_tuple, nmtools::unwrap;

#define HIP_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,na::hip::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define HIP_LINEAR_TEST(fun,...) \
{ \
    auto ctx = na::hip::default_context(); \
    auto expect = na::fun(__VA_ARGS__); \
    auto view   = view::fun(__VA_ARGS__); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define GROUP_NORM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, group_norm, case_name); \
    using namespace args; \
    auto ctx = na::hip::default_context(); \
    auto view = nmtools::view::group_norm(__VA_ARGS__); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

// infinite loop?
#if 1
TEST_CASE("group_norm(case1)" * doctest::test_suite("array::group_norm") * doctest::skip())
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto input = na::random(array{1,5,2,2},dtype,gen);
    auto num_groups = 5;
    auto weight = na::random(array{5},dtype,gen);
    auto bias = na::random(array{5},dtype,gen);

    HIP_LINEAR_TEST(group_norm,input,num_groups,weight,bias);
}
#endif

#if 0
TEST_CASE("group_norm(case1)" * doctest::test_suite("array::group_norm"))
{
    GROUP_NORM_SUBCASE( case1, input,   num_groups, weight,   bias );
    GROUP_NORM_SUBCASE( case1, input_a, num_groups, weight_a, bias_a );
    GROUP_NORM_SUBCASE( case1, input_f, num_groups, weight_f, bias_f );
    GROUP_NORM_SUBCASE( case1, input_h, num_groups, weight_h, bias_h );
    GROUP_NORM_SUBCASE( case1, input_d, num_groups, weight_d, bias_d );
}

TEST_CASE("group_norm(case2)" * doctest::test_suite("array::group_norm"))
{
    GROUP_NORM_SUBCASE( case2, input,   num_groups, weight,   bias );
    GROUP_NORM_SUBCASE( case2, input_a, num_groups, weight_a, bias_a );
    GROUP_NORM_SUBCASE( case2, input_f, num_groups, weight_f, bias_f );
    GROUP_NORM_SUBCASE( case2, input_h, num_groups, weight_h, bias_h );
    GROUP_NORM_SUBCASE( case2, input_d, num_groups, weight_d, bias_d );
}

TEST_CASE("group_norm(case3)" * doctest::test_suite("array::group_norm"))
{
    GROUP_NORM_SUBCASE( case3, input,   num_groups, weight,   bias );
    GROUP_NORM_SUBCASE( case3, input_a, num_groups, weight_a, bias_a );
    GROUP_NORM_SUBCASE( case3, input_f, num_groups, weight_f, bias_f );
    GROUP_NORM_SUBCASE( case3, input_h, num_groups, weight_h, bias_h );
    GROUP_NORM_SUBCASE( case3, input_d, num_groups, weight_d, bias_d );
}

TEST_CASE("group_norm(case4)" * doctest::test_suite("array::group_norm"))
{
    GROUP_NORM_SUBCASE( case4, input,   num_groups, weight,   bias );
    GROUP_NORM_SUBCASE( case4, input_a, num_groups, weight_a, bias_a );
    GROUP_NORM_SUBCASE( case4, input_f, num_groups, weight_f, bias_f );
    GROUP_NORM_SUBCASE( case4, input_h, num_groups, weight_h, bias_h );
    GROUP_NORM_SUBCASE( case4, input_d, num_groups, weight_d, bias_d );
}

TEST_CASE("group_norm(case5)" * doctest::test_suite("array::group_norm"))
{
    GROUP_NORM_SUBCASE( case5, input,   num_groups, weight,   bias );
    GROUP_NORM_SUBCASE( case5, input_a, num_groups, weight_a, bias_a );
    GROUP_NORM_SUBCASE( case5, input_f, num_groups, weight_f, bias_f );
    GROUP_NORM_SUBCASE( case5, input_h, num_groups, weight_h, bias_h );
    GROUP_NORM_SUBCASE( case5, input_d, num_groups, weight_d, bias_d );
}

TEST_CASE("group_norm(case6)" * doctest::test_suite("array::group_norm"))
{
    GROUP_NORM_SUBCASE( case6, input,   num_groups, weight,   bias );
    GROUP_NORM_SUBCASE( case6, input_a, num_groups, weight_a, bias_a );
    GROUP_NORM_SUBCASE( case6, input_f, num_groups, weight_f, bias_f );
    GROUP_NORM_SUBCASE( case6, input_h, num_groups, weight_h, bias_h );
    GROUP_NORM_SUBCASE( case6, input_d, num_groups, weight_d, bias_d );
}
#endif