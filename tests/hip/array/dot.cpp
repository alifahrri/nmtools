#include "nmtools/evaluator/hip.hpp"
#include "nmtools/array/dot.hpp"
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
TEST_CASE("dot(case1)" * doctest::test_suite("array::dot") * doctest::skip())
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto a = na::random(array{2,3,2},dtype,gen);
    auto b = na::random(array{2,4,2,2},dtype,gen);

    HIP_TEST(dot,a,b);
}
#endif

#if 1
TEST_CASE("dot(case1b)" * doctest::test_suite("array::dot"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto a = na::random(array{2,3,2},dtype,gen);
    auto b = na::random(array{2,4,2,2},dtype,gen);

    HIP_LINEAR_TEST(dot,a,b);
}
#endif