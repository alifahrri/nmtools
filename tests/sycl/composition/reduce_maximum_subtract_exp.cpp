#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/exp.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/exp.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace view = nm::view;

#define SYCL_SUBCASE(...) \
{ \
    auto result = na::eval(__VA_ARGS__, na::sycl::default_context()); \
    auto expect = na::eval(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

// TODO: fix sycl kernel jit compile error:
// Cannot find symbol free in kernel library
// Cannot find symbol malloc in kernel library
TEST_CASE("reduce_maximum_subtract_exp(case1)" * doctest::test_suite("array::reduce_maximum_subtract_exp") * doctest::skip())
{
    auto lhs_shape = nmtools_array{128};
    auto lhs_numel = ix::product(lhs_shape);
    auto lhs_start = 0;
    auto lhs_stop  = lhs_start + lhs_numel;
    auto lhs_step  = 1;
    auto lhs_flat  = na::arange(lhs_start,lhs_stop,lhs_step);

    auto axis     = -1;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    auto keepdims = nm::True;

    auto lhs = na::reshape(lhs_flat,lhs_shape);

    auto x = view::reduce_maximum(lhs,axis,dtype,initial,keepdims);
    auto y = view::subtract(x,lhs);
    auto z = view::exp(y);

    SYCL_SUBCASE( z );
}