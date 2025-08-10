#include "nmtools/network/compose.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/network/multi_digraph.hpp"
#include "nmtools/testing/data/network/compose.hpp"
#include "nmtools/testing/doctest.hpp"

#include <fstream>

#define COMPOSE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, compose, case_name ); \
    using namespace args; \
    auto result_pair = nmtools::network::compose( __VA_ARGS__ ); \
    const auto& result_list   = nmtools::get<0>(result_pair); \
    const auto& result_map_id = nmtools::get<1>(result_pair); \
    NMTOOLS_ASSERT_EQUAL( result_list, expect::result_list ); \
    NMTOOLS_ASSERT_EQUAL( result_map_id, expect::result_map_id ); \
}

#define CONSTEXPR_COMPOSE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, compose, case_name ); \
    using namespace args; \
    constexpr auto result_pair = nmtools::network::compose( __VA_ARGS__ ); \
    constexpr const auto result_list   = nmtools::get<0>(result_pair); \
    constexpr const auto result_map_id = nmtools::get<1>(result_pair); \
    NMTOOLS_ASSERT_EQUAL( result_list, expect::result_list ); \
    NMTOOLS_ASSERT_EQUAL( result_map_id, expect::result_map_id ); \
}

#define DIGRAPH_COMPOSE_SUBCASE(case_name, g_list, h_list, g_map_id, h_map_id) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, compose, case_name); \
    using namespace args; \
    auto G = nmtools::network::digraph(g_list,g_map_id); \
    auto H = nmtools::network::digraph(h_list,h_map_id); \
    auto result_digraph = nmtools::network::compose(G,H); \
    const auto& result_list   = result_digraph.adjacency_list; \
    const auto& result_map_id = result_digraph.node_ids; \
    NMTOOLS_ASSERT_EQUAL( result_list, expect::result_list ); \
    NMTOOLS_ASSERT_EQUAL( result_map_id, expect::result_map_id ); \
}

#define MULTI_DIGRAPH_COMPOSE_SUBCASE(case_name, g_list, h_list, g_map_id, h_map_id) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, compose, case_name); \
    using namespace args; \
    auto G = nmtools::network::multi_digraph(g_list,g_map_id); \
    auto H = nmtools::network::multi_digraph(h_list,h_map_id); \
    auto result_digraph = nmtools::network::compose(G,H); \
    const auto& result_list   = result_digraph.adjacency_list; \
    const auto& result_map_id = result_digraph.node_ids; \
    NMTOOLS_ASSERT_EQUAL( result_list, expect::result_list ); \
    NMTOOLS_ASSERT_EQUAL( result_map_id, expect::result_map_id ); \
}

#define DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE(case_name, g_list, h_list, g_map_id, h_map_id, g_attributes, h_attributes) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, compose, case_name); \
    using namespace args; \
    auto G = nmtools::network::digraph(g_list,g_map_id,g_attributes); \
    auto H = nmtools::network::digraph(h_list,h_map_id,h_attributes); \
    auto result_digraph = nmtools::network::compose(G,H); \
    const auto& result_list   = nmtools::unwrap(result_digraph).adjacency_list; \
    const auto& result_map_id = nmtools::unwrap(result_digraph).node_ids; \
    NMTOOLS_ASSERT_EQUAL( result_list, expect::result_list ); \
    NMTOOLS_ASSERT_EQUAL( result_map_id, expect::result_map_id ); \
    auto graphviz = nmtools::utils::to_string(nmtools::unwrap(result_digraph),nmtools::utils::Graphviz); \
    CHECK_MESSAGE( true, graphviz ); \
    std::ofstream outputFile; \
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc); \
    outputFile << graphviz << std::endl; \
}

#define MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE(case_name, g_list, h_list, g_map_id, h_map_id, g_attributes, h_attributes) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, compose, case_name); \
    using namespace args; \
    auto G = nmtools::network::multi_digraph(g_list,g_map_id,g_attributes); \
    auto H = nmtools::network::multi_digraph(h_list,h_map_id,h_attributes); \
    auto result_digraph = nmtools::network::compose(G,H); \
    const auto& result_list   = nmtools::unwrap(result_digraph).adjacency_list; \
    const auto& result_map_id = nmtools::unwrap(result_digraph).node_ids; \
    NMTOOLS_ASSERT_EQUAL( result_list, expect::result_list ); \
    NMTOOLS_ASSERT_EQUAL( result_map_id, expect::result_map_id ); \
    auto graphviz = nmtools::utils::to_string(nmtools::unwrap(result_digraph),nmtools::utils::Graphviz); \
    CHECK_MESSAGE( true, graphviz ); \
    std::ofstream outputFile; \
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc); \
    outputFile << graphviz << std::endl; \
}

TEST_CASE("compose(case1)" * doctest::test_suite("network::compose"))
{
    COMPOSE_SUBCASE( case1, g_list_a_sv, h_list_a_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_a_v, h_list_a_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_sv_sv, h_list_a_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_sv_v, h_list_a_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_v_sv, h_list_a_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_v_v, h_list_a_sv, g_map_id, h_map_id );

    COMPOSE_SUBCASE( case1, g_list_a_sv, h_list_a_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_a_v, h_list_a_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_sv_sv, h_list_a_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_sv_v, h_list_a_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_v_sv, h_list_a_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_v_v, h_list_a_v, g_map_id, h_map_id );

    COMPOSE_SUBCASE( case1, g_list_a_sv, h_list_sv_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_a_v, h_list_sv_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_sv_sv, h_list_sv_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_sv_v, h_list_sv_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_v_sv, h_list_sv_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_v_v, h_list_sv_sv, g_map_id, h_map_id );

    COMPOSE_SUBCASE( case1, g_list_a_sv, h_list_sv_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_a_v, h_list_sv_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_sv_sv, h_list_sv_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_sv_v, h_list_sv_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_v_sv, h_list_sv_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_v_v, h_list_sv_v, g_map_id, h_map_id );

    COMPOSE_SUBCASE( case1, g_list_a_sv, h_list_v_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_a_v, h_list_v_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_sv_sv, h_list_v_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_sv_v, h_list_v_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_v_sv, h_list_v_sv, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_v_v, h_list_v_sv, g_map_id, h_map_id );

    COMPOSE_SUBCASE( case1, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case1, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    COMPOSE_SUBCASE( case1, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("constexpr_compose(case1)" * doctest::test_suite("network::compose"))
{
    CONSTEXPR_COMPOSE_SUBCASE( case1, g_list_a_sv_ct, h_list_a_sv_ct, g_map_id, h_map_id );
    CONSTEXPR_COMPOSE_SUBCASE( case1, g_list_sv_sv_ct, h_list_a_sv_ct, g_map_id, h_map_id );

    CONSTEXPR_COMPOSE_SUBCASE( case1, g_list_a_sv_ct, h_list_sv_sv_ct, g_map_id, h_map_id );
    CONSTEXPR_COMPOSE_SUBCASE( case1, g_list_sv_sv_ct, h_list_sv_sv_ct, g_map_id, h_map_id );
}

TEST_CASE("digraph_compose(case1)" * doctest::test_suite("network::compose"))
{
    DIGRAPH_COMPOSE_SUBCASE( case1, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case1, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case1, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case1, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case1, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case1, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    DIGRAPH_COMPOSE_SUBCASE( case1, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("multi_digraph_compose(case1)" * doctest::test_suite("network::compose"))
{
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case1, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case1, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case1, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case1, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case1, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case1, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    MULTI_DIGRAPH_COMPOSE_SUBCASE( case1, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("digraph_attributes_compose(case1)" * doctest::test_suite("network::compose"))
{
    auto g_attributes = nmtools_array<nmtools_string,2>{"1","2"};
    auto h_attributes = nmtools_array<nmtools_string,2>{"3","4"};

    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case1, g_list_a_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case1, g_list_a_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case1, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case1, g_list_sv_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case1, g_list_v_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case1, g_list_v_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );

    // DIGRAPH_COMPOSE_SUBCASE( case1, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("multi_digraph_attributes_compose(case1)" * doctest::test_suite("network::compose"))
{
    auto g_attributes = nmtools_array<nmtools_string,2>{"1","2"};
    auto h_attributes = nmtools_array<nmtools_string,2>{"3","4"};

    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case1, g_list_a_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case1, g_list_a_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case1, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case1, g_list_sv_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case1, g_list_v_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case1, g_list_v_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );

    // MULTI_DIGRAPH_COMPOSE_SUBCASE( case1, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("compose(case2)" * doctest::test_suite("network::compose"))
{
    COMPOSE_SUBCASE( case2, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case2, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case2, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case2, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case2, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case2, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    COMPOSE_SUBCASE( case2, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("constexpr_compose(case2)" * doctest::test_suite("network::compose"))
{
    CONSTEXPR_COMPOSE_SUBCASE( case2, g_list_a_sv_ct, h_list_a_sv_ct, g_map_id, h_map_id );
    CONSTEXPR_COMPOSE_SUBCASE( case2, g_list_sv_sv_ct, h_list_a_sv_ct, g_map_id, h_map_id );

    CONSTEXPR_COMPOSE_SUBCASE( case2, g_list_a_sv_ct, h_list_sv_sv_ct, g_map_id, h_map_id );
    CONSTEXPR_COMPOSE_SUBCASE( case2, g_list_sv_sv_ct, h_list_sv_sv_ct, g_map_id, h_map_id );
}

TEST_CASE("digraph_compose(case2)" * doctest::test_suite("network::compose"))
{
    DIGRAPH_COMPOSE_SUBCASE( case2, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case2, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case2, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case2, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case2, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case2, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    DIGRAPH_COMPOSE_SUBCASE( case2, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("multi_digraph_compose(case2)" * doctest::test_suite("network::compose"))
{
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case2, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case2, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case2, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case2, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case2, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case2, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    MULTI_DIGRAPH_COMPOSE_SUBCASE( case2, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("digraph_attributes_compose(case2)" * doctest::test_suite("network::compose"))
{
    auto g_attributes = nmtools_array<nmtools_string,2>{"1","2"};
    auto h_attributes = nmtools_array<nmtools_string,2>{"3","4"};

    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case2, g_list_a_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case2, g_list_a_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case2, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case2, g_list_sv_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case2, g_list_v_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case2, g_list_v_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );

    // DIGRAPH_COMPOSE_SUBCASE( case2, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("multi_digraph_attributes_compose(case2)" * doctest::test_suite("network::compose"))
{
    auto g_attributes = nmtools_array<nmtools_string,2>{"1","2"};
    auto h_attributes = nmtools_array<nmtools_string,2>{"3","4"};

    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case2, g_list_a_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case2, g_list_a_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case2, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case2, g_list_sv_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case2, g_list_v_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case2, g_list_v_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );

    // MULTI_DIGRAPH_COMPOSE_SUBCASE( case2, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("compose(case3)" * doctest::test_suite("network::compose"))
{
    COMPOSE_SUBCASE( case3, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case3, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case3, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case3, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case3, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case3, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    COMPOSE_SUBCASE( case3, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("constexpr_compose(case3)" * doctest::test_suite("network::compose"))
{
    CONSTEXPR_COMPOSE_SUBCASE( case3, g_list_a_sv_ct, h_list_a_sv_ct, g_map_id, h_map_id );
    CONSTEXPR_COMPOSE_SUBCASE( case3, g_list_sv_sv_ct, h_list_a_sv_ct, g_map_id, h_map_id );

    CONSTEXPR_COMPOSE_SUBCASE( case3, g_list_a_sv_ct, h_list_sv_sv_ct, g_map_id, h_map_id );
    CONSTEXPR_COMPOSE_SUBCASE( case3, g_list_sv_sv_ct, h_list_sv_sv_ct, g_map_id, h_map_id );
}

TEST_CASE("digraph_compose(case3)" * doctest::test_suite("network::compose"))
{
    DIGRAPH_COMPOSE_SUBCASE( case3, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case3, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case3, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case3, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case3, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case3, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    DIGRAPH_COMPOSE_SUBCASE( case3, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("multi_digraph_compose(case3)" * doctest::test_suite("network::compose"))
{
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case3, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case3, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case3, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case3, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case3, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case3, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    MULTI_DIGRAPH_COMPOSE_SUBCASE( case3, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("digraph_attributes_compose(case3)" * doctest::test_suite("network::compose"))
{
    auto g_attributes = nmtools_array<nmtools_string,2>{"1","2"};
    auto h_attributes = nmtools_array<nmtools_string,3>{"3","4","5"};

    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case3, g_list_a_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case3, g_list_a_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case3, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case3, g_list_sv_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case3, g_list_v_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case3, g_list_v_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );

    // DIGRAPH_COMPOSE_SUBCASE( case4, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("multi_digraph_attributes_compose(case3)" * doctest::test_suite("network::compose"))
{
    auto g_attributes = nmtools_array<nmtools_string,2>{"1","2"};
    auto h_attributes = nmtools_array<nmtools_string,3>{"3","4","5"};

    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case3, g_list_a_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case3, g_list_a_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case3, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case3, g_list_sv_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case3, g_list_v_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case3, g_list_v_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );

    // MULTI_DIGRAPH_COMPOSE_SUBCASE( case4, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("compose(case4)" * doctest::test_suite("network::compose"))
{
    COMPOSE_SUBCASE( case4, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case4, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case4, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case4, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case4, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case4, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    // empty map_ids not supported yet
    // TODO: fix
    // COMPOSE_SUBCASE( case4, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("constexpr_compose(case4)" * doctest::test_suite("network::compose"))
{
    CONSTEXPR_COMPOSE_SUBCASE( case4, g_list_a_sv_ct, h_list_a_sv_ct, g_map_id, h_map_id );
    CONSTEXPR_COMPOSE_SUBCASE( case4, g_list_sv_sv_ct, h_list_a_sv_ct, g_map_id, h_map_id );

    CONSTEXPR_COMPOSE_SUBCASE( case4, g_list_a_sv_ct, h_list_sv_sv_ct, g_map_id, h_map_id );
    CONSTEXPR_COMPOSE_SUBCASE( case4, g_list_sv_sv_ct, h_list_sv_sv_ct, g_map_id, h_map_id );
}

TEST_CASE("digraph_compose(case4)" * doctest::test_suite("network::compose"))
{
    DIGRAPH_COMPOSE_SUBCASE( case4, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case4, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case4, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case4, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case4, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case4, g_list_v_v, h_list_v_v, g_map_id, h_map_id );
}

TEST_CASE("multi_digraph_compose(case4)" * doctest::test_suite("network::compose"))
{
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case4, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case4, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case4, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case4, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case4, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case4, g_list_v_v, h_list_v_v, g_map_id, h_map_id );
}

TEST_CASE("digraph_attributes_compose(case4)" * doctest::test_suite("network::compose"))
{
    auto g_attributes = nmtools_array<nmtools_string,2>{"1","2"};
    auto h_attributes = nmtools_array<nmtools_string,0>{};

    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case4, g_list_a_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case4, g_list_a_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case4, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case4, g_list_sv_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case4, g_list_v_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case4, g_list_v_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );

    // DIGRAPH_COMPOSE_SUBCASE( case4, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("multi_digraph_attributes_compose(case4)" * doctest::test_suite("network::compose"))
{
    auto g_attributes = nmtools_array<nmtools_string,2>{"1","2"};
    auto h_attributes = nmtools_array<nmtools_string,0>{};

    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case4, g_list_a_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case4, g_list_a_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case4, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case4, g_list_sv_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case4, g_list_v_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case4, g_list_v_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );

    // MULTI_DIGRAPH_COMPOSE_SUBCASE( case4, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("compose(case5)" * doctest::test_suite("network::compose"))
{
    COMPOSE_SUBCASE( case5, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case5, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case5, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case5, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case5, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case5, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    COMPOSE_SUBCASE( case5, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("constexpr_compose(case5)" * doctest::test_suite("network::compose"))
{
    CONSTEXPR_COMPOSE_SUBCASE( case5, g_list_a_sv_ct, h_list_a_sv_ct, g_map_id, h_map_id );
    CONSTEXPR_COMPOSE_SUBCASE( case5, g_list_sv_sv_ct, h_list_a_sv_ct, g_map_id, h_map_id );

    CONSTEXPR_COMPOSE_SUBCASE( case5, g_list_a_sv_ct, h_list_sv_sv_ct, g_map_id, h_map_id );
    CONSTEXPR_COMPOSE_SUBCASE( case5, g_list_sv_sv_ct, h_list_sv_sv_ct, g_map_id, h_map_id );
}

TEST_CASE("digraph_compose(case5)" * doctest::test_suite("network::compose"))
{
    DIGRAPH_COMPOSE_SUBCASE( case5, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case5, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case5, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case5, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case5, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    DIGRAPH_COMPOSE_SUBCASE( case5, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    DIGRAPH_COMPOSE_SUBCASE( case5, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("multi_digraph_compose(case5)" * doctest::test_suite("network::compose"))
{
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case5, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case5, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case5, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case5, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case5, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    MULTI_DIGRAPH_COMPOSE_SUBCASE( case5, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    MULTI_DIGRAPH_COMPOSE_SUBCASE( case5, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("digraph_attributes_compose(case5)" * doctest::test_suite("network::compose"))
{
    auto g_attributes = nmtools_array<nmtools_string,3>{"1","2","3"};
    auto h_attributes = nmtools_array<nmtools_string,3>{"4","5","6"};

    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case5, g_list_a_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case5, g_list_a_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case5, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case5, g_list_sv_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case5, g_list_v_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case5, g_list_v_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );

    // DIGRAPH_COMPOSE_SUBCASE( case5, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("multi_digraph_attributes_compose(case5)" * doctest::test_suite("network::compose"))
{
    auto g_attributes = nmtools_array<nmtools_string,3>{"1","2","3"};
    auto h_attributes = nmtools_array<nmtools_string,3>{"4","5","6"};

    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case5, g_list_a_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case5, g_list_a_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case5, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case5, g_list_sv_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case5, g_list_v_sv, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );
    MULTI_DIGRAPH_ATTRIBUTES_COMPOSE_SUBCASE( case5, g_list_v_v, h_list_v_v, g_map_id, h_map_id, g_attributes, h_attributes );

    // MULTI_DIGRAPH_COMPOSE_SUBCASE( case5, g_list, h_list, g_map_id, h_map_id );
}

TEST_CASE("digraph_attributes_compose(case6)" * doctest::test_suite("network::compose"))
{
    NMTOOLS_TESTING_USE_CASE(network, compose, case6);
    using namespace args;

    auto G = nmtools::network::digraph(g_list,g_map_id,g_attributes);
    auto H = nmtools::network::digraph(h_list,h_map_id,h_attributes);
    auto result_digraph = nmtools::network::compose(G,H);

    const auto& result_list   = nmtools::unwrap(result_digraph).adjacency_list;
    const auto& result_map_id = nmtools::unwrap(result_digraph).node_ids;

    NMTOOLS_ASSERT_EQUAL( result_list, expect::result_list );
    NMTOOLS_ASSERT_EQUAL( result_map_id, expect::result_map_id );

    auto graphviz = nmtools::utils::to_string(nmtools::unwrap(result_digraph),nmtools::utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("compose(case7)" * doctest::test_suite("network::compose"))
{
    COMPOSE_SUBCASE( case7, g_list_a_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case7, g_list_a_v, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case7, g_list_sv_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case7, g_list_sv_v, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case7, g_list_v_sv, h_list_v_v, g_map_id, h_map_id );
    COMPOSE_SUBCASE( case7, g_list_v_v, h_list_v_v, g_map_id, h_map_id );

    COMPOSE_SUBCASE( case7, g_list, h_list, g_map_id, h_map_id );
}