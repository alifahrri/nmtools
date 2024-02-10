#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/ufuncs/divide.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nm::view;
namespace utils = nm::utils;

using namespace nmtools::literals;

TEST_CASE("reduce_add_divide" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto divisor = 3;

    auto axis = 0;
    auto a = view::reduce_add(lhs_array,axis);
    auto b = view::divide(a,divisor);

    auto graph = fn::get_compute_graph(b);

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,fn::node_t{fn::reduce_add[a.axis][nm::None][a.initial][a.keepdims],nmtools_tuple{0_ct}})
        .add_node(2_ct,divisor)
        .add_node(3_ct,fn::node_t{fn::divide,nmtools_tuple{1_ct,2_ct}})
        .add_edge(0_ct,1_ct)
        .add_edge(1_ct,3_ct)
        .add_edge(2_ct,2_ct)
    ;

    // CHECK_MESSAGE( true, utils::to_string(graph, utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}