#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/sum.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace view = nm::view;

#define CUDA_SUBCASE(...) \
{ \
    auto result = na::eval(__VA_ARGS__, na::sycl::default_context()); \
    auto expect = na::eval(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

// TODO: fix sycl kernel jit compile error:
// Cannot find symbol free in kernel library
// Cannot find symbol malloc in kernel library
TEST_CASE("fabs_square_sum(case1)" * doctest::test_suite("array::fabs_square_sum") * doctest::skip())
{
    auto a_shape = nmtools_array{128};
    auto a_numel = ix::product(a_shape);
    auto a_start = 0;
    auto a_stop  = a_start + a_numel;
    auto a_step  = 1;
    auto a_flat  = na::arange(a_start,a_stop,a_step);

    auto a = na::reshape(a_flat,a_shape);

    auto axis     = 0;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    auto keepdims = nm::True;

    auto x = view::fabs(a);
    auto y = view::square(x);
    auto z = view::sum(y,axis,dtype,initial,keepdims);

    CUDA_SUBCASE( z );
}