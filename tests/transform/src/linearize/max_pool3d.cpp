#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/array/pooling.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/random.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace meta = nmtools::meta;
namespace view = nmtools::view;
namespace na = nmtools;
namespace ix = nmtools::index;
namespace utl = nmtools::utl;
namespace utils = nmtools::utils;
namespace utility = nmtools::utility;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

TEST_CASE("transform_unary_fusion(max_pool3d1)" * doctest::test_suite("transfomr"))
{
    auto gen = na::random_engine();

    auto dtype = nm::float32;

    auto input = na::random(array{1,1,4,5,6},dtype,gen);
    auto kernel_size = array{4,2,3};
    auto stride    = 2;
    auto padding   = array{0,1,1};
    auto dilation  = nm::None;
    auto ceil_mode = nm::True;

    auto res = view::max_pool3d(input,kernel_size,stride,padding,dilation,ceil_mode);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::transform_unary_fusion(graph,meta::ct_v<-1>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("linearize(max_pool3d)" * doctest::test_suite("transfomr"))
{
    auto gen = na::random_engine();

    auto dtype = nm::float32;

    auto input = na::random(array{1,1,4,5,6},dtype,gen);
    auto kernel_size = array{4,2,3};
    auto stride    = 2;
    auto padding   = array{0,1,1};
    auto dilation  = nm::None;
    auto ceil_mode = nm::True;

    auto res = view::max_pool3d(input,kernel_size,stride,padding,dilation,ceil_mode);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::linearize(graph);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}