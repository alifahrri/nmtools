#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/ufuncs/sqrt.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/sqrt.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"
#include "nmtools/array/stddev.hpp"
#include "nmtools/array/reshape.hpp"
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

// TODO: fix compile on gcc
#ifdef __clang__
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
#endif // __clang__