#include "nmtools/network/remove_edge.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/network/multi_digraph.hpp"
#include "nmtools/testing/data/network/remove_edge.hpp"
#include "nmtools/testing/doctest.hpp"

#define REMOVE_EDGE_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, remove_edge, case_name ); \
    using namespace args; \
    auto result = nmtools::network::remove_edge( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define DIGRAPH_REMOVE_EDGE_SUBCASE(case_name, adj_list, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, remove_edge, case_name ); \
    using namespace args; \
    auto u_id = nmtools::network::map_ids(u,src_node_ids); \
    auto v_id = nmtools::network::map_ids(v,src_node_ids); \
    auto digraph = nmtools::network::digraph(adj_list,src_node_ids,src_node_attributes,src_edge_attributes); \
    { \
        auto graphviz = nmtools::utils::to_string(nmtools::unwrap(digraph),nmtools::utils::Graphviz); \
        CHECK_MESSAGE( true, graphviz ); \
        std::ofstream outputFile; \
        outputFile.open("src.dot", std::ios::out | std::ios::trunc); \
        outputFile << graphviz << std::endl; \
    } \
    auto result  = digraph.remove_edge(u_id,v_id,key); \
    const auto& result_list = nmtools::unwrap(result).adjacency_list; \
    NMTOOLS_ASSERT_EQUAL( result_list, expect::result); \
    { \
        auto graphviz = nmtools::utils::to_string(nmtools::unwrap(result),nmtools::utils::Graphviz); \
        CHECK_MESSAGE( true, graphviz ); \
        std::ofstream outputFile; \
        outputFile.open("res.dot", std::ios::out | std::ios::trunc); \
        outputFile << graphviz << std::endl; \
    } \
}

#define MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE(case_name, adj_list, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, remove_edge, case_name ); \
    using namespace args; \
    auto u_id = nmtools::network::map_ids(u,src_node_ids); \
    auto v_id = nmtools::network::map_ids(v,src_node_ids); \
    auto digraph = nmtools::network::multi_digraph(adj_list,src_node_ids,src_node_attributes,src_edge_attributes); \
    { \
        auto graphviz = nmtools::utils::to_string(nmtools::unwrap(digraph),nmtools::utils::Graphviz); \
        CHECK_MESSAGE( true, graphviz ); \
        std::ofstream outputFile; \
        outputFile.open("src.dot", std::ios::out | std::ios::trunc); \
        outputFile << graphviz << std::endl; \
    } \
    auto result  = digraph.remove_edge(u_id,v_id,key); \
    const auto& result_list = nmtools::unwrap(result).adjacency_list; \
    NMTOOLS_ASSERT_EQUAL( result_list, expect::result); \
    { \
        auto graphviz = nmtools::utils::to_string(nmtools::unwrap(result),nmtools::utils::Graphviz); \
        CHECK_MESSAGE( true, graphviz ); \
        std::ofstream outputFile; \
        outputFile.open("res.dot", std::ios::out | std::ios::trunc); \
        outputFile << graphviz << std::endl; \
    } \
}

using namespace nmtools::literals;

TEST_CASE("remove_edge(case1)" * doctest::test_suite("network::remove_edge"))
{
    REMOVE_EDGE_SUBCASE( case1, list_a_sv, u, v );
    REMOVE_EDGE_SUBCASE( case1, list_a_v, u, v );
    REMOVE_EDGE_SUBCASE( case1, list_sv_sv, u, v );
    REMOVE_EDGE_SUBCASE( case1, list_sv_v, u, v );
    REMOVE_EDGE_SUBCASE( case1, list_v_sv, u, v );
    REMOVE_EDGE_SUBCASE( case1, list_v_v, u, v );

    REMOVE_EDGE_SUBCASE( case1, list, u_ct, v_ct );
}

TEST_CASE("digraph_remove_edge(case1a)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools::None;
    auto src_edge_attributes = nmtools::None;
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("digraph_remove_edge(case1b)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b","c"};
    auto src_edge_attributes = nmtools::None;
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("digraph_remove_edge(case1c)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b","c"};
    auto src_edge_attributes = nmtools_list<nmtools_list<nmtools_string>>{{"x","y"},{"z"},{}};
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("digraph_remove_edge(case1d)" * doctest::test_suite("network::remove_edge"))
{
    auto key = 0;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b","c"};
    auto src_edge_attributes = nmtools_list<nmtools_list<nmtools_string>>{{"x","y"},{"z"},{}};
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}


TEST_CASE("multi_digraph_remove_edge(case1a)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools::None;
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case1b)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b","c"};
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case1c)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b","c"};
    auto src_edge_attributes = nmtools_list<nmtools_list<nmtools_string>>{{"x","y"},{"z"},{}};
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case1d)" * doctest::test_suite("network::remove_edge"))
{
    auto key = 0;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b","c"};
    auto src_edge_attributes = nmtools_list<nmtools_list<nmtools_string>>{{"x","y"},{"z"},{}};
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case1, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("remove_edge(case2)" * doctest::test_suite("network::remove_edge"))
{
    REMOVE_EDGE_SUBCASE( case2, list_a_sv, u, v );
    REMOVE_EDGE_SUBCASE( case2, list_a_v, u, v );
    REMOVE_EDGE_SUBCASE( case2, list_sv_sv, u, v );
    REMOVE_EDGE_SUBCASE( case2, list_sv_v, u, v );
    REMOVE_EDGE_SUBCASE( case2, list_v_sv, u, v );
    REMOVE_EDGE_SUBCASE( case2, list_v_v, u, v );

    REMOVE_EDGE_SUBCASE( case2, list, u_ct, v_ct );
}

TEST_CASE("digraph_remove_edge(case2a)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools::None;
    auto src_edge_attributes = nmtools::None;
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("digraph_remove_edge(case2b)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b"};
    auto src_edge_attributes = nmtools::None;
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("digraph_remove_edge(case2c)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b"};
    auto src_edge_attributes = nmtools_list<nmtools_list<nmtools_string>>{{"x"},{}};
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case2a)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools::None;
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case2b)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b"};
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case2c)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b"};
    auto src_edge_attributes = nmtools_list<nmtools_list<nmtools_string>>{{"x"},{}};
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case2, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("remove_edge(case3)" * doctest::test_suite("network::remove_edge"))
{
    REMOVE_EDGE_SUBCASE( case3, list_a_sv, u, v );
    REMOVE_EDGE_SUBCASE( case3, list_a_v, u, v );
    REMOVE_EDGE_SUBCASE( case3, list_sv_sv, u, v );
    REMOVE_EDGE_SUBCASE( case3, list_sv_v, u, v );
    REMOVE_EDGE_SUBCASE( case3, list_v_sv, u, v );
    REMOVE_EDGE_SUBCASE( case3, list_v_v, u, v );

    REMOVE_EDGE_SUBCASE( case3, list, u_ct, v_ct );
}

TEST_CASE("digraph_remove_edge(case3a)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools::None;
    auto src_edge_attributes = nmtools::None;
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("digraph_remove_edge(case3b)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b"};
    auto src_edge_attributes = nmtools::None;
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("digraph_remove_edge(case3c)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b"};
    auto src_edge_attributes = nmtools_list<nmtools_list<nmtools_string>>{{"x","y"},{}};
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case3a)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools::None;
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case3b)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b"};
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case3c)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools_list<nmtools_string>{"a","b"};
    auto src_edge_attributes = nmtools_list<nmtools_list<nmtools_string>>{{"x","y"},{}};
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case3, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("remove_edge(case4)" * doctest::test_suite("network::remove_edge"))
{
    REMOVE_EDGE_SUBCASE( case4, list_a_sv, u, v, multi );
    REMOVE_EDGE_SUBCASE( case4, list_a_v, u, v, multi );
    REMOVE_EDGE_SUBCASE( case4, list_sv_sv, u, v, multi );
    REMOVE_EDGE_SUBCASE( case4, list_sv_v, u, v, multi );
    REMOVE_EDGE_SUBCASE( case4, list_v_sv, u, v, multi );
    REMOVE_EDGE_SUBCASE( case4, list_v_v, u, v, multi );

    REMOVE_EDGE_SUBCASE( case4, list, u_ct, v_ct, multi_ct );
}

TEST_CASE("multi_digraph_remove_edge(case4a)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools::None;
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case4b)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools_array<nmtools_string,2>{"a","b"};
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case4c)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools_array<nmtools_string,2>{"a","b"};
    auto src_edge_attributes = nmtools_list<nmtools_list<nmtools_string>>{{"x","y"},{}};
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case4d)" * doctest::test_suite("network::remove_edge"))
{
    auto key = 0;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools_array<nmtools_string,2>{"a","b"};
    auto src_edge_attributes = nmtools_list<nmtools_list<nmtools_string>>{{"x","y"},{}};
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case4, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("remove_edge(case5)" * doctest::test_suite("network::remove_edge"))
{
    REMOVE_EDGE_SUBCASE( case5, list_a_sv, u, v, multi );
    REMOVE_EDGE_SUBCASE( case5, list_a_v, u, v, multi );
    REMOVE_EDGE_SUBCASE( case5, list_sv_sv, u, v, multi );
    REMOVE_EDGE_SUBCASE( case5, list_sv_v, u, v, multi );
    REMOVE_EDGE_SUBCASE( case5, list_v_sv, u, v, multi );
    REMOVE_EDGE_SUBCASE( case5, list_v_v, u, v, multi );

    REMOVE_EDGE_SUBCASE( case5, list, u_ct, v_ct, multi_ct );
}

TEST_CASE("multi_digraph_remove_edge(case5a)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools::None;
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case5b)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools_array<nmtools_string,3>{"a","b","c"};
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case5c)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools_array<nmtools_string,3>{"a","b","c"};
    auto src_edge_attributes = nmtools_list<nmtools_list<nmtools_string>>{{"x","y","z"},{},{}};
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case5, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("remove_edge(case6)" * doctest::test_suite("network::remove_edge"))
{
    REMOVE_EDGE_SUBCASE( case6, list_a_sv, u, v, multi );
    REMOVE_EDGE_SUBCASE( case6, list_a_v, u, v, multi );
    REMOVE_EDGE_SUBCASE( case6, list_sv_sv, u, v, multi );
    REMOVE_EDGE_SUBCASE( case6, list_sv_v, u, v, multi );
    REMOVE_EDGE_SUBCASE( case6, list_v_sv, u, v, multi );
    REMOVE_EDGE_SUBCASE( case6, list_v_v, u, v, multi );

    REMOVE_EDGE_SUBCASE( case6, list, u_ct, v_ct, multi_ct );
}

TEST_CASE("multi_digraph_remove_edge(case6a)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools::None;
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case6b)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools_array<nmtools_string,2>{"a","b"};
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case6c)" * doctest::test_suite("network::remove_edge"))
{
    auto key = nmtools::None;
    auto src_node_ids = nmtools_tuple{0_ct,100_ct};
    auto src_node_attributes = nmtools_array<nmtools_string,2>{"a","b"};
    auto src_edge_attributes = nmtools_list<nmtools_list<nmtools_string>>{{"x","y","z"},{}};
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case6, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("remove_edge(case7)" * doctest::test_suite("network::remove_edge"))
{
    REMOVE_EDGE_SUBCASE( case7, list_a_sv, u, v, multi, key );
    REMOVE_EDGE_SUBCASE( case7, list_a_v, u, v, multi, key );
    REMOVE_EDGE_SUBCASE( case7, list_sv_sv, u, v, multi, key );
    REMOVE_EDGE_SUBCASE( case7, list_sv_v, u, v, multi, key );
    REMOVE_EDGE_SUBCASE( case7, list_v_sv, u, v, multi, key );
    REMOVE_EDGE_SUBCASE( case7, list_v_v, u, v, multi, key );

    REMOVE_EDGE_SUBCASE( case7, list, u_ct, v_ct, multi_ct, key_ct );
}

TEST_CASE("multi_digraph_remove_edge(case7a)" * doctest::test_suite("network::remove_edge"))
{
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools::None;
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case7b)" * doctest::test_suite("network::remove_edge"))
{
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools_array<nmtools_string,3>{"a","b","c"};
    auto src_edge_attributes = nmtools::None;
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}

TEST_CASE("multi_digraph_remove_edge(case7c)" * doctest::test_suite("network::remove_edge"))
{
    auto src_node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
    auto src_node_attributes = nmtools_array<nmtools_string,3>{"a","b","c"};
    auto src_edge_attributes = nmtools_list<nmtools_list<nmtools_string>>{{"x","y","z"},{},{}};
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_a_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_a_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_sv_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_sv_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_v_sv, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
    MULTI_DIGRAPH_REMOVE_EDGE_SUBCASE( case7, list_v_v, src_node_ids, src_node_attributes, src_edge_attributes, u, v, key );
}