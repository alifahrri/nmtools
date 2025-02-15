#include "nmtools/evaluator/hip.hpp"
#include "nmtools/array/softmax.hpp"
#include "nmtools/array/random.hpp"
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

#if 1
TEST_CASE("softmax(case1)" * doctest::test_suite("array::softmax") * doctest::skip())
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto input = na::random(array{3,4},dtype,gen);
    auto axis  = -1;

    HIP_TEST(softmax,input,axis);
}
#endif

#if 1
TEST_CASE("softmax(case1b)" * doctest::test_suite("array::softmax"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto input = na::random(array{3,4},dtype,gen);
    auto axis  = -1;

    HIP_LINEAR_TEST(softmax,input,axis);
}
#endif