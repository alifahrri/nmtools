#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/ufuncs/divide.hpp"
#include "nmtools/array/array/ufuncs/subtract.hpp"
#include "nmtools/array/array/ufuncs/fabs.hpp"
#include "nmtools/array/array/ufuncs/square.hpp"
#include "nmtools/array/array/ufuncs/sqrt.hpp"
#include "nmtools/array/array/sum.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufuncs/fabs.hpp"
#include "nmtools/array/functional/ufuncs/square.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufuncs/sqrt.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/array/view/stddev.hpp"
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
using nmtools::unwrap;

TEST_CASE("stddev" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;

    // TODO: support maybe type for stddev
    auto var = view::stddev(unwrap(lhs_array),axis);
    auto graph = fn::get_compute_graph(unwrap(var));
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}