#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/array/pairwise_distance.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nmtools::view;

// TODO: fix to accept maybe type
using nmtools_array, nmtools_tuple, nmtools::unwrap;

#define SYCL_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,na::sycl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define SYCL_LINEAR_TEST(fun,...) \
{ \
    auto ctx = na::sycl::default_context(); \
    auto expect = na::fun(__VA_ARGS__); \
    auto view   = view::fun(__VA_ARGS__); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#if 1
TEST_CASE("pairwise_distance(case1)" * doctest::test_suite("array::pairwise_distance"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto lhs = na::random(array{3,4},dtype,gen);
    auto rhs = na::random(array{2,1,4},dtype,gen);

    SYCL_TEST(pairwise_distance,lhs,rhs,meta::ct_v<2>,1e-6f,nm::False);
}
#endif

#if 1
TEST_CASE("pairwise_distance(case1b)" * doctest::test_suite("array::pairwise_distance"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto lhs = na::random(array{3,4},dtype,gen);
    auto rhs = na::random(array{2,1,4},dtype,gen);

    SYCL_LINEAR_TEST(pairwise_distance,lhs,rhs,meta::ct_v<2>,1e-6f,nm::False);
}
#endif