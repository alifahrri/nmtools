#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/array/tensordot.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
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

TEST_CASE("tensordot(case1)" * doctest::test_suite("array::tensordot") * doctest::skip())
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto lhs = na::random(array{2,3,4,5},dtype,gen);
    auto rhs = na::random(array{3,5,4,2},dtype,gen);
    auto axes = nmtools_tuple{
        nmtools_array{2,3},
        nmtools_array{-2,-3},
    };

    SYCL_TEST(tensordot,lhs,rhs,axes);
}

TEST_CASE("tensordot(case1)" * doctest::test_suite("array::tensordot"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto lhs = na::random(array{2,3,4,5},dtype,gen);
    auto rhs = na::random(array{3,5,4,2},dtype,gen);
    auto axes = nmtools_tuple{
        nmtools_array{2,3},
        nmtools_array{-2,-3},
    };

    SYCL_LINEAR_TEST(tensordot,lhs,rhs,axes);
}