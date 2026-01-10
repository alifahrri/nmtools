#include "nmtools/core/computational_graph.hpp"
#include "nmtools/array/ufuncs/cos.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace nk = nmtools::network;
namespace fn = nmtools::functional;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

TEST_CASE("get_computational_graph(cos)" * doctest::test_suite("transform"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = array{3,4};

    auto a = nm::random(a_shape,dtype,gen);

    auto res = view::cos(a);

    auto graph = fn::get_computational_graph(res);

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );
    NMTOOLS_ASSERT_EQUAL( nm::meta::is_constant_adjacency_list_v<decltype(unwrap(graph).adjacency_list)>, true );

    constexpr auto graph_v = nm::meta::to_value_v<decltype(unwrap(graph))>;
    auto graphviz_v = utils::to_string(unwrap(graph_v),utils::Graphviz);

    auto keys = graph_v.nodes();
    [[maybe_unused]]
    auto cos  = graph_v.nodes(nm::at(keys,0_ct));
    CHECK_MESSAGE( true, cos.to_string().at(0) );
    CHECK_MESSAGE( true, cos.to_string().at(1) );
    CHECK( cos.is_compute() );
    CHECK( cos.kind() == fn::Kind::UNARY_UFUNC );
    CHECK( cos.attributes_.count("op") );

    CHECK_MESSAGE( true, graphviz_v );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph_v), true );
}