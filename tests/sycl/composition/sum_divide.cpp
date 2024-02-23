#include "nmtools/array/array/sum.hpp"
#include "nmtools/array/array/ufuncs/divide.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/eval/sycl.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/sum.hpp"

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

TEST_CASE("sum_divide(case1)" * doctest::test_suite("array::sum_divide"))
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
    auto divisor = nmtools_array{lhs_numel};

    auto x = view::sum(lhs,axis,dtype,initial,keepdims);
    auto y = view::divide(x,divisor);

    CUDA_SUBCASE( y );
}