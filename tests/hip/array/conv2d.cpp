#include "nmtools/evaluator/hip.hpp"
#include "nmtools/array/conv2d.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
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

#if 1
// runtime error
TEST_CASE("conv2d(case1)" * doctest::test_suite("array::conv2d") * doctest::skip())
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto input  = na::random(array{1,1,4,4},dtype,gen);
    auto weight = na::random(array{1,1,3,3},dtype,gen);

    HIP_TEST(conv2d,input,weight,nm::None,nm::None,nm::None,nm::None,meta::ct_v<1>);
}
#endif

TEST_CASE("conv2d(case1b)" * doctest::test_suite("array::conv2d"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto input  = na::random(array{1,1,4,4},dtype,gen);
    auto weight = na::random(array{1,1,3,3},dtype,gen);

    HIP_LINEAR_TEST(conv2d,input,weight,nm::None,nm::None,nm::None,nm::None,meta::ct_v<1>);
}