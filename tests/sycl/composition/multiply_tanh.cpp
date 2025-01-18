#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/ufuncs/tanh.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/evaluator/sycl.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/tanh.hpp"

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

TEST_CASE("multiply_tanh(case1)" * doctest::test_suite("array::multiply_tanh"))
{
    auto a_shape = nmtools_array{128};
    auto a_numel = ix::product(a_shape);
    auto a_start = 0;
    auto a_stop  = a_start + a_numel;
    auto a_step  = 1;
    auto a_flat  = na::arange(a_start,a_stop,a_step);

    auto a = na::reshape(a_flat,a_shape);

    auto x = view::multiply(a,0.5f);
    auto y = view::tanh(x);

    CUDA_SUBCASE( y );
}