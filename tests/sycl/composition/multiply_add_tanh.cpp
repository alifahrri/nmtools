#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"

namespace nm = nmtools;
namespace na = nmtools;
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

TEST_CASE("multiply_add_tanh(case1)" * doctest::test_suite("array::multiply_add_tanh"))
{
    auto a_shape = nmtools_array{128};
    auto a_numel = ix::product(a_shape);
    auto a_start = 0;
    auto a_stop  = a_start + a_numel;
    auto a_step  = 1;
    auto a_flat  = na::arange(a_start,a_stop,a_step);

    auto b_shape = nmtools_array{128};
    auto b_numel = ix::product(b_shape);
    auto b_start = -b_numel/2;
    auto b_stop  = b_start + b_numel;
    auto b_step  = 1;
    auto b_flat  = na::arange(b_start,b_stop,b_step);

    auto c_shape = nmtools_array{128};
    auto c_numel = ix::product(c_shape);
    auto c_start = -c_numel;
    auto c_stop  = c_numel;
    auto c_step  = 2;
    auto c_flat  = na::arange(c_start,c_stop,c_step);

    auto a = na::reshape(a_flat,a_shape);
    auto b = na::reshape(b_flat,b_shape);
    auto c = na::reshape(c_flat,c_shape);

    auto x = view::multiply(a,b);
    auto y = view::add(x,c);
    auto z = view::tanh(y);

    CUDA_SUBCASE( z );
}