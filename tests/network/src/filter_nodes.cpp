#include "nmtools/network/filter_nodes.hpp"
#include "nmtools/testing/data/network/filter_nodes.hpp"
#include "nmtools/testing/doctest.hpp"

namespace meta = nmtools::meta;

#define FILTER_NODES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, filter_nodes, case_name ); \
    using namespace args; \
    auto result = nmtools::network::filter_nodes(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

#define FILTER_NODES_SUBCASE_STRING(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, filter_nodes, case_name ); \
    using namespace args; \
    auto result = nmtools::unwrap(nmtools::network::filter_nodes(__VA_ARGS__)); \
    NMTOOLS_ASSERT_EQUAL( nmtools::len(result), nmtools::len(expect::expected) ); \
    auto n = result.size(); \
    for (nm_size_t i=0; i<(nm_size_t)n; i++) { \
        CHECK( nmtools::at(result,i) == nmtools::at(expect::expected,i) );  \
    } \
}

TEST_CASE("filter_nodes(case1)" * doctest::test_suite("network::filter_nodes"))
{
    FILTER_NODES_SUBCASE( case1, node_attributes, src_node_ids, dst_node_ids );
    FILTER_NODES_SUBCASE( case1, node_attributes_a, src_node_ids_a, dst_node_ids_a );
    FILTER_NODES_SUBCASE( case1, node_attributes_v, src_node_ids_v, dst_node_ids_v );
    FILTER_NODES_SUBCASE( case1, node_attributes_f, src_node_ids_f, dst_node_ids_f );
    FILTER_NODES_SUBCASE( case1, node_attributes_h, src_node_ids_h, dst_node_ids_h );

    FILTER_NODES_SUBCASE( case1, node_attributes_ct, src_node_ids_ct, dst_node_ids_ct );
}

TEST_CASE("filter_nodes(case2)" * doctest::test_suite("network::filter_nodes"))
{
    FILTER_NODES_SUBCASE( case2, node_attributes, src_node_ids, dst_node_ids );
    FILTER_NODES_SUBCASE( case2, node_attributes_a, src_node_ids_a, dst_node_ids_a );
    FILTER_NODES_SUBCASE( case2, node_attributes_v, src_node_ids_v, dst_node_ids_v );
    FILTER_NODES_SUBCASE( case2, node_attributes_f, src_node_ids_f, dst_node_ids_f );
    FILTER_NODES_SUBCASE( case2, node_attributes_h, src_node_ids_h, dst_node_ids_h );

    FILTER_NODES_SUBCASE( case2, node_attributes_ct, src_node_ids_ct, dst_node_ids_ct );
}

TEST_CASE("filter_nodes(case3)" * doctest::test_suite("network::filter_nodes"))
{
    // FILTER_NODES_SUBCASE( case3, node_attributes, src_node_ids, dst_node_ids );
    FILTER_NODES_SUBCASE_STRING( case3, node_attributes_a, src_node_ids_a, dst_node_ids_a );
    FILTER_NODES_SUBCASE_STRING( case3, node_attributes_v, src_node_ids_v, dst_node_ids_v );
    // FILTER_NODES_SUBCASE( case3, node_attributes_f, src_node_ids_f, dst_node_ids_f );
    // FILTER_NODES_SUBCASE( case3, node_attributes_h, src_node_ids_h, dst_node_ids_h );
}

TEST_CASE("filter_nodes(case4)" * doctest::test_suite("network::filter_nodes"))
{
    FILTER_NODES_SUBCASE( case4, node_attributes, src_node_ids, dst_node_ids );
    FILTER_NODES_SUBCASE( case4, node_attributes_a, src_node_ids_a, dst_node_ids_a );
    FILTER_NODES_SUBCASE( case4, node_attributes_v, src_node_ids_v, dst_node_ids_v );
    FILTER_NODES_SUBCASE( case4, node_attributes_f, src_node_ids_f, dst_node_ids_f );
    FILTER_NODES_SUBCASE( case4, node_attributes_h, src_node_ids_h, dst_node_ids_h );
}

TEST_CASE("filter_nodes(case5)" * doctest::test_suite("network::filter_nodes"))
{
    FILTER_NODES_SUBCASE( case5, node_attributes, src_node_ids, dst_node_ids );
    FILTER_NODES_SUBCASE( case5, node_attributes_a, src_node_ids_a, dst_node_ids );
    FILTER_NODES_SUBCASE( case5, node_attributes_v, src_node_ids_v, dst_node_ids );
    FILTER_NODES_SUBCASE( case5, node_attributes_f, src_node_ids_f, dst_node_ids );
    FILTER_NODES_SUBCASE( case5, node_attributes_h, src_node_ids_h, dst_node_ids );
}

TEST_CASE("filter_nodes(case6)" * doctest::test_suite("network::filter_nodes"))
{
    // FILTER_NODES_SUBCASE_STRING( case6, node_attributes, src_node_ids, dst_node_ids );
    FILTER_NODES_SUBCASE_STRING( case6, node_attributes_a, src_node_ids_a, dst_node_ids_a );
    FILTER_NODES_SUBCASE_STRING( case6, node_attributes_v, src_node_ids_v, dst_node_ids_v );
    // FILTER_NODES_SUBCASE_STRING( case6, node_attributes_f, src_node_ids_f, dst_node_ids_f );
    // FILTER_NODES_SUBCASE_STRING( case6, node_attributes_h, src_node_ids_h, dst_node_ids_h );
}

TEST_CASE("filter_nodes(case7)" * doctest::test_suite("network::filter_nodes"))
{
    NMTOOLS_TESTING_USE_CASE( network, filter_nodes, case7 );
    using namespace args;
    auto result = nmtools::unwrap(nmtools::network::filter_nodes(node_attributes,src_node_ids_ct,dst_node_ids_ct));
    NMTOOLS_ASSERT_EQUAL( nmtools::len(result), nmtools::len(expect::expected) );
    CHECK( nmtools::get<0>(result).tag == nmtools::get<0>(expect::expected).tag );
    CHECK( nmtools::get<1>(result).tag == nmtools::get<1>(expect::expected).tag );

    CHECK( nmtools::get<0>(result).value == nmtools::get<0>(expect::expected).value );
    CHECK( nmtools::get<1>(result).value == nmtools::get<1>(expect::expected).value );
}