#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/network/cast.hpp"

namespace meta = nmtools::meta;
namespace tag  = nmtools::tag;
namespace network = nmtools::network;
using meta::ct;

TEST_CASE("case1a" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_list<int>>;
    using element_t [[maybe_unused]] = meta::get_value_type_t<type>;
    NMTOOLS_STATIC_CHECK_IS_SAME( element_t, nmtools_list<int> );
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, type );
}

TEST_CASE("case1b" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_array<int,3>>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, type );
}

TEST_CASE("case1c" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_static_vector<int,3>>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, type );
}

TEST_CASE("case1d" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_static_vector<float,3>>;
    NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_adjacency_list, type );
}

TEST_CASE("case2a" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_list<int>,3>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, type );
}

TEST_CASE("case2b" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_static_vector<int,2>,3>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, type );
}

TEST_CASE("case2c" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_array<int,2>,3>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, type );
}

TEST_CASE("case2d" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_array<float,2>,3>;
    NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_adjacency_list, type );
}

TEST_CASE("case2e" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_array<nmtools_array<int,2>,2>,3>;
    NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_adjacency_list, type );
}

TEST_CASE("case3a" * doctest::test_suite("meta"))
{
    using type = nmtools_static_vector<nmtools_list<int>,3>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, type );
}

TEST_CASE("case3b" * doctest::test_suite("meta"))
{
    using type = nmtools_static_vector<nmtools_array<int,2>,3>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, type );
}

TEST_CASE("case3c" * doctest::test_suite("meta"))
{
    using type = nmtools_static_vector<nmtools_static_vector<int,2>,3>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, type );
}

TEST_CASE("case4a" * doctest::test_suite("meta"))
{
    using type = nmtools_tuple<nmtools_array<int,3>,nmtools_list<int>>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, type );
}

TEST_CASE("case4b" * doctest::test_suite("meta"))
{
    using type = nmtools_tuple<nmtools_array<int,1>,nmtools_list<int>,nmtools_static_vector<int,3>>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, type );
}

TEST_CASE("case4c" * doctest::test_suite("meta"))
{
    using type = nmtools_tuple<nmtools_array<int,1>,nmtools_list<int>,nmtools_static_vector<int,3>,float>;
    NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_adjacency_list, type );
}

TEST_CASE("case5a" * doctest::test_suite("meta"))
{
    using type = nmtools_tuple<
        nmtools_tuple<ct<1>>,
        nmtools_tuple<ct<0>,ct<2>>,
        nmtools_tuple<>
    >;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, type );
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_constant_adjacency_list, type );
}

TEST_CASE("fixed_num_nodes(case1a)" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_list<int>>;
    constexpr auto num_nodes = meta::fixed_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(num_nodes) );
}

TEST_CASE("bounded_num_nodes(case1a)" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_list<int>>;
    constexpr auto b_num_nodes = meta::bounded_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(b_num_nodes) );
}

TEST_CASE("fixed_num_edges(case1a)" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_list<int>>;
    constexpr auto num_edges = meta::fixed_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(num_edges) );
}

TEST_CASE("bounded_num_edges(case1a)" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_list<int>>;
    constexpr auto b_num_edges = meta::bounded_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(b_num_edges) );
}

TEST_CASE("fixed_num_nodes(case1b)" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_array<int,3>>;
    constexpr auto num_nodes = meta::fixed_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(num_nodes) );
}

TEST_CASE("bounded_num_nodes(case1b)" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_array<int,3>>;
    constexpr auto b_num_nodes = meta::bounded_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(b_num_nodes) );
}

TEST_CASE("fixed_num_edges(case1b)" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_array<int,3>>;
    constexpr auto num_edges = meta::fixed_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(num_edges) );
}

TEST_CASE("bounded_num_edges(case1b)" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_array<int,3>>;
    constexpr auto b_num_edges = meta::bounded_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(b_num_edges) );
}

TEST_CASE("fixed_num_nodes(case1c)" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_static_vector<int,3>>;
    constexpr auto num_nodes = meta::fixed_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(num_nodes) );
}

TEST_CASE("bounded_num_nodes(case1c)" * doctest::test_suite("meta"))
{
    using type = nmtools_list<nmtools_static_vector<int,3>>;
    constexpr auto b_num_nodes = meta::bounded_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(b_num_nodes) );
}

TEST_CASE("fixed_num_nodes(case2a)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_list<int>,3>;
    constexpr auto num_nodes = meta::fixed_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(num_nodes) );
    NMTOOLS_STATIC_ASSERT_EQUAL( num_nodes, 3 );
}

TEST_CASE("bounded_num_nodes(case2a)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_list<int>,3>;
    constexpr auto b_num_nodes = meta::bounded_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(b_num_nodes) );
    NMTOOLS_STATIC_ASSERT_EQUAL( b_num_nodes, 3 );
}

TEST_CASE("fixed_num_edges(case2a)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_list<int>,3>;
    constexpr auto num_edges = meta::fixed_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, decltype(num_edges) );
    // can't know the fixed number of edge but should know the worst case number of edges
    // NMTOOLS_STATIC_ASSERT_EQUAL( num_nodes, 3 );
}

TEST_CASE("bounded_num_edges(case2a)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_list<int>,3>;
    constexpr auto b_num_edges = meta::bounded_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(b_num_edges) );
    // can't know the fixed number of edge but should know the worst case number of edges
    // worst case is num_nodes * num_nodes
    NMTOOLS_STATIC_ASSERT_EQUAL( b_num_edges, 9 );
}

TEST_CASE("fixed_num_nodes(case2b)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_static_vector<int,2>,3>;
    constexpr auto num_nodes = meta::fixed_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(num_nodes) );
    NMTOOLS_STATIC_ASSERT_EQUAL( num_nodes, 3 );
}

TEST_CASE("bounded_num_nodes(case2b)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_static_vector<int,2>,3>;
    constexpr auto b_num_nodes = meta::bounded_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(b_num_nodes) );
    NMTOOLS_STATIC_ASSERT_EQUAL( b_num_nodes, 3 );
}

TEST_CASE("fixed_num_edges(case2b)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_static_vector<int,2>,3>;
    constexpr auto num_edges = meta::fixed_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(num_edges) );
}

TEST_CASE("bounded_num_edges(case2b)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_static_vector<int,2>,3>;
    constexpr auto b_num_edges = meta::bounded_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(b_num_edges) );
    NMTOOLS_STATIC_ASSERT_EQUAL( b_num_edges, 6 );
}

TEST_CASE("fixed_num_nodes(case2c)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_array<int,2>,3>;
    constexpr auto num_nodes = meta::fixed_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(num_nodes) );
    NMTOOLS_STATIC_ASSERT_EQUAL( num_nodes, 3 );
}

TEST_CASE("bounded_num_nodes(case2c)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_array<int,2>,3>;
    constexpr auto b_num_nodes = meta::bounded_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(b_num_nodes) );
    NMTOOLS_STATIC_ASSERT_EQUAL( b_num_nodes, 3 );
}

TEST_CASE("fixed_num_edges(case2c)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_array<int,2>,3>;
    constexpr auto num_edges = meta::fixed_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(num_edges) );
    NMTOOLS_STATIC_ASSERT_EQUAL( num_edges, 6 );
}

TEST_CASE("bounded_num_edges(case2c)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_array<int,2>,3>;
    constexpr auto b_num_edges = meta::bounded_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(b_num_edges) );
    NMTOOLS_STATIC_ASSERT_EQUAL( b_num_edges, 6 );
}

TEST_CASE("fixed_num_nodes(case2d)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_array<float,2>,3>;
    constexpr auto num_nodes = meta::fixed_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(num_nodes) );
}

TEST_CASE("bounded_num_nodes(case2d)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_array<float,2>,3>;
    constexpr auto b_num_nodes = meta::bounded_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(b_num_nodes) );
}

TEST_CASE("fixed_num_nodes(case2e)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_array<nmtools_array<int,2>,2>,3>;
    constexpr auto num_nodes = meta::fixed_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(num_nodes) );
}

TEST_CASE("bounded_num_nodes(case2e)" * doctest::test_suite("meta"))
{
    using type = nmtools_array<nmtools_array<nmtools_array<int,2>,2>,3>;
    constexpr auto b_num_nodes = meta::bounded_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(b_num_nodes) );
}

TEST_CASE("fixed_num_nodes(case3a)" * doctest::test_suite("meta"))
{
    using type = nmtools_static_vector<nmtools_list<int>,3>;
    constexpr auto num_nodes = meta::fixed_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(num_nodes) );
}

TEST_CASE("bounded_num_nodes(case3a)" * doctest::test_suite("meta"))
{
    using type = nmtools_static_vector<nmtools_list<int>,3>;
    constexpr auto b_num_nodes = meta::bounded_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(b_num_nodes) );
    NMTOOLS_STATIC_ASSERT_EQUAL( b_num_nodes, 3 );
}

TEST_CASE("fixed_num_edges(case3a)" * doctest::test_suite("meta"))
{
    using type = nmtools_static_vector<nmtools_list<int>,3>;
    constexpr auto num_edges = meta::fixed_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(num_edges) );
}

TEST_CASE("bounded_num_edges(case3a)" * doctest::test_suite("meta"))
{
    using type = nmtools_static_vector<nmtools_list<int>,3>;
    constexpr auto b_num_edges = meta::bounded_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(b_num_edges) );
    NMTOOLS_STATIC_ASSERT_EQUAL( b_num_edges, 9 );
}

TEST_CASE("fixed_num_nodes(case3b)" * doctest::test_suite("meta"))
{
    using type = nmtools_static_vector<nmtools_array<int,2>,3>;
    constexpr auto num_nodes = meta::fixed_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(num_nodes) );
}

TEST_CASE("bounded_num_nodes(case3b)" * doctest::test_suite("meta"))
{
    using type = nmtools_static_vector<nmtools_array<int,2>,3>;
    constexpr auto b_num_nodes = meta::bounded_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(b_num_nodes) );
    NMTOOLS_STATIC_ASSERT_EQUAL( b_num_nodes, 3 );
}

TEST_CASE("fixed_num_edges(case3b)" * doctest::test_suite("meta"))
{
    using type = nmtools_static_vector<nmtools_array<int,2>,3>;
    constexpr auto num_edges = meta::fixed_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(num_edges) );
}

TEST_CASE("bounded_num_edges(case3b)" * doctest::test_suite("meta"))
{
    using type = nmtools_static_vector<nmtools_array<int,2>,3>;
    constexpr auto b_num_edges = meta::bounded_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, decltype(b_num_edges) );
    NMTOOLS_STATIC_ASSERT_EQUAL( b_num_edges, 6 );
}

TEST_CASE("fixed_num_nodes(case5)" * doctest::test_suite("meta"))
{
    using type = nmtools_tuple<
        nmtools_tuple<ct<1>>,
        nmtools_tuple<ct<0>,ct<2>>,
        nmtools_tuple<>
    >;
    constexpr auto num_nodes = meta::fixed_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fail, decltype(num_nodes) );
    NMTOOLS_STATIC_ASSERT_EQUAL( num_nodes, 3 );
}

TEST_CASE("bounded_num_nodes(case5)" * doctest::test_suite("meta"))
{
    using type = nmtools_tuple<
        nmtools_tuple<ct<1>>,
        nmtools_tuple<ct<0>,ct<2>>,
        nmtools_tuple<>
    >;
    constexpr auto b_num_nodes = meta::bounded_num_nodes_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fail, decltype(b_num_nodes) );
    NMTOOLS_STATIC_ASSERT_EQUAL( b_num_nodes, 3 );
}

TEST_CASE("fixed_num_edges(case5)" * doctest::test_suite("meta"))
{
    using type = nmtools_tuple<
        nmtools_tuple<ct<1>>,
        nmtools_tuple<ct<0>,ct<2>>,
        nmtools_tuple<>
    >;
    constexpr auto num_edges = meta::fixed_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fail, decltype(num_edges) );
    NMTOOLS_STATIC_ASSERT_EQUAL( num_edges, 3 );
}

TEST_CASE("bounded_num_edges(case5)" * doctest::test_suite("meta"))
{
    using type = nmtools_tuple<
        nmtools_tuple<ct<1>>,
        nmtools_tuple<ct<0>,ct<2>>,
        nmtools_tuple<>
    >;
    constexpr auto b_num_edges = meta::bounded_num_edges_v<type>;
    NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fail, decltype(b_num_edges) );
    NMTOOLS_STATIC_ASSERT_EQUAL( b_num_edges, 3 );
}

TEST_CASE("cast(case1)" * doctest::test_suite("meta"))
{
    using type = nmtools_tuple<
        nmtools_tuple<ct<1>>,
        nmtools_tuple<ct<0>,ct<2>>,
        nmtools_tuple<>
    >;
    using result_t = meta::resolve_optype_t<tag::network_cast_t,type,network::kind::array_t,network::kind::array_t>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, result_t );
}

TEST_CASE("cast(case2)" * doctest::test_suite("meta"))
{
    using type = nmtools_tuple<
        nmtools_tuple<ct<1>>,
        nmtools_tuple<ct<2>>,
        nmtools_tuple<>
    >;
    using result_t = meta::resolve_optype_t<tag::network_cast_t,type,network::kind::array_t,network::kind::array_t>;
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_adjacency_list, result_t );
}

TEST_CASE("cast(case3)" * doctest::test_suite("meta"))
{
    using type = nmtools_tuple<
        nmtools_tuple<ct<1>>,
        nmtools_tuple<ct<2>>,
        nmtools_tuple<>
    >;
    constexpr auto adjacency_list = meta::to_value_v<type>;
    constexpr auto expected = nmtools_tuple{
        nmtools_array{1},
        nmtools_array{2},
        nmtools_array<int,0>(),
    };
    NMTOOLS_ASSERT_EQUAL( adjacency_list, expected )
}