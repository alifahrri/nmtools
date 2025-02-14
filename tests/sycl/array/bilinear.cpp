#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/array/bilinear.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/core/transform/linearize.hpp"
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
// runtime error
TEST_CASE("bilinear(case1)" * doctest::test_suite("array::bilinear") * doctest::skip())
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto a = na::random(array{3,1,2,3},dtype,gen);
    auto b = na::random(array{3,1,2,4},dtype,gen);
    auto weight = na::random(array{2,3,4},dtype,gen);
    auto bias = na::random(array{2},dtype,gen);

    // SYCL_TEST(bilinear,unwrap(a),unwrap(b),unwrap(weight),unwrap(bias));
    SYCL_TEST(bilinear,a,b,weight,bias);
}
#endif

#if 1
TEST_CASE("bilinear(case1b)" * doctest::test_suite("array::bilinear"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto a = na::random(array{3,1,2,3},dtype,gen);
    auto b = na::random(array{3,1,2,4},dtype,gen);
    auto weight = na::random(array{2,3,4},dtype,gen);
    auto bias = na::random(array{2},dtype,gen);

    SYCL_LINEAR_TEST(bilinear,a,b,weight,bias);
}
#endif