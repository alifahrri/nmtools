#include "nmtools/array/mean.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/evaluator/cuda.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace view = nm::view;

namespace composition
{
    template <typename array_t, typename axis_t, typename dtype_t=nmtools::none_t>
    constexpr auto mean_subtract(const array_t& array, const axis_t& axis, dtype_t dtype=dtype_t{})
    {
        // must keep dimension to properly subtract
        auto a = view::mean(array,axis,dtype,nmtools::True);
        auto b = view::subtract(array,a);
        return b;
    } // mean_subtract
} // composition

TEST_CASE("mean_subtract(case1)" * doctest::test_suite("mean_subtract"))
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start+numel;
    auto step  = 1;
    auto dtype = nm::float32;

    auto input = na::reshape(na::arange(start,stop,step,dtype),shape);
    auto axis  = 0;
    auto array = composition::mean_subtract(input,axis,dtype);
}

TEST_CASE("mean" * doctest::test_suite("get_graph"))
{
    auto nodes = nmtools_tuple{fn::alias,fn::alias,fn::reduce_add,fn::divide};
    /* operand list */
    auto adjacency_list = nmtools_tuple{nm::None,nm::None,nmtools_array{0},nmtools_array{2,1}};
}