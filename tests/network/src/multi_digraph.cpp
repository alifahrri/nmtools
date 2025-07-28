#include "nmtools/network/multi_digraph.hpp"
#include "nmtools/testing/doctest.hpp"

#include "nmtools/array/flatten.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/core/node.hpp"

#include <fstream>

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace network = nm::network;
namespace utils = nm::utils;

using nmtools_array;

enum class OpType : int
{
    UNKNOWN=0,
    INDEXING=1,
    UFUNC=2,
    REDUCE=3,
    BUFFERED=4,
};

struct node_attribute
{
    OpType kind;
    float weight;

    inline auto to_string() const noexcept
    {
        auto str = nmtools_string();

        // str += "{";
        str += "kind=";
        switch (kind) {
            case OpType::UNKNOWN:
                str += "UNKNOWN";
                break;
            case OpType::INDEXING:
                str += "INDEXING";
                break;
            case OpType::UFUNC:
                str += "UFUNC";
                break;
            case OpType::REDUCE:
                str += "REDUCE";
                break;
            case OpType::BUFFERED:
                str+= "BUFFERED";
                break;
            default:
                break;
        };
        str += "| weight=";
        str += utils::to_string(weight);
        // str += "}";

        return str;
    }
};

struct edge_attribute
{
    float weight;

    inline auto to_string() const noexcept
    {
        auto str = nmtools_string();

        // str += "{";
        str += "weight=";
        str += utils::to_string(weight);
        // str += "}";

        return str;
    }
};

// TODO: how to stringify filename
#define WRITE_GRAPHVIZ( multi_digraph ) \
{ \
    auto graphviz = utils::to_string(multi_digraph,utils::Graphviz); \
    CHECK_MESSAGE( true, graphviz ); \
    std::ofstream outputFile; \
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc); \
    outputFile << graphviz << std::endl; \
}

/*==================================================================*/

TEST_CASE("multi_digraph(case1)" * doctest::test_suite("network::multi_digraph"))
{
    auto multi_digraph = network::multi_digraph();

    multi_digraph.add_node(1);
    multi_digraph.add_nodes_from(array{2,3}).add_edge(2,3);
    multi_digraph.add_node(4);

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.number_of_nodes(), 4 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.number_of_edges(), 1 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("multi_digraph(case2)" * doctest::test_suite("network::multi_digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto node_ids = nmtools_list{1,2,3,4};
    auto multi_digraph  = network::multi_digraph(adj_list,node_ids);

    multi_digraph.add_nodes_from(array{2,3}).add_edge(2,3);

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("multi_digraph(case3)" * doctest::test_suite("network::multi_digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto multi_digraph  = network::multi_digraph(adj_list);

    multi_digraph.add_nodes_from(array{1,2}).add_edge(1,2);

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("multi_digraph(case4)" * doctest::test_suite("network::multi_digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto multi_digraph  = network::multi_digraph(adj_list);

    multi_digraph.add_nodes_from(array{1,2}).add_edge(1,2);

    auto expected = nmtools_list{
        nmtools_array{1,2}
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.out_edges(), expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("multi_digraph(case5)" * doctest::test_suite("network::multi_digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto multi_digraph  = network::multi_digraph(adj_list);

    multi_digraph.add_nodes_from(array{1,2});

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("multi_digraph(case6)" * doctest::test_suite("network::multi_digraph"))
{
    auto multi_digraph = network::multi_digraph();

    multi_digraph.add_node(1);
    multi_digraph.add_nodes_from(array{2,3});
    multi_digraph.add_node(4);

    multi_digraph.add_edge(1,2);
    multi_digraph.add_edge(1,3);
    multi_digraph.add_edge(2,3);
    multi_digraph.add_edge(3,4);
    multi_digraph.add_edge(1,1); // self-loop

    auto expected = nmtools_tuple{
        nmtools_array{1,2,0},
        nmtools_array{2},
        nmtools_array{3},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.size(), 5 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("multi_digraph(case7)" * doctest::test_suite("network::multi_digraph"))
{
    constexpr auto multi_digraph = [](){
        constexpr auto max_nodes = meta::ct_v<4>;
        constexpr auto multi_digraph = network::multi_digraph(max_nodes)
            .add_node(1)
            .add_nodes_from(array{2,3})
            .add_node(4)
            .add_edge(1,2)
            .add_edge(1,3)
            .add_edge(2,3)
            .add_edge(3,4)
            .add_edge(1,1); // self-loop

        return multi_digraph;
    }();

    auto expected = nmtools_tuple{
        nmtools_array{1,2,0},
        nmtools_array{2},
        nmtools_array{3},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.size(), 5 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

using namespace nmtools::literals;

TEST_CASE("multi_digraph(case8)" * doctest::test_suite("network::multi_digraph"))
{
    auto multi_digraph = network::multi_digraph();
    multi_digraph.add_node(0);
    multi_digraph.add_node(1);
    multi_digraph.add_node(2);
    multi_digraph.add_node(3);
    multi_digraph.add_node(4);
    multi_digraph.add_edge(0,1);
    multi_digraph.add_edge(0,3);
    multi_digraph.add_edge(1,0);
    multi_digraph.add_edge(1,2);
    multi_digraph.add_edge(2,1);
    multi_digraph.add_edge(2,3);
    multi_digraph.add_edge(3,0);
    multi_digraph.add_edge(3,2);

    auto expected = nmtools_tuple{
        nmtools_array{1, 3},
        nmtools_array{0, 2},
        nmtools_array{1, 3},
        nmtools_array{0, 2},
        nmtools_array<int,0>{}
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 5 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.size(), 8 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("multi_digraph(case9)" * doctest::test_suite("network::multi_digraph"))
{
    auto multi_digraph = network::multi_digraph();
    multi_digraph.add_node(0);
    multi_digraph.add_node(1);
    multi_digraph.add_node(2);
    multi_digraph.add_node(3);
    multi_digraph.add_node(4);
    multi_digraph.add_node(4);
    multi_digraph.add_edge(0,1);
    multi_digraph.add_edge(0,2);
    multi_digraph.add_edge(1,2);
    multi_digraph.add_edge(2,4);
    multi_digraph.add_edge(2,3);
    multi_digraph.add_edge(4,5);
    multi_digraph.add_edge(3,5);

    auto expected = nmtools_tuple{
        nmtools_array{1, 2},
        nmtools_array{2},
        nmtools_array{4,3},
        nmtools_array{5},
        nmtools_array{5},
        nmtools_array<int,0>{}
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 6 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.size(), 7 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("multi_digraph(case10)" * doctest::test_suite("network::multi_digraph"))
{
    auto multi_digraph = network::multi_digraph();
    multi_digraph.add_nodes_from(nmtools_array{0,1,2,3,4,5,6,7,8,9});

    multi_digraph.add_edges_from(nmtools_list{
        nmtools_array{0,2},
        nmtools_array{0,4},
        nmtools_array{1,3},
        nmtools_array{2,3},
        nmtools_array{3,4},
        nmtools_array{4,5},
        nmtools_array{5,6},
        nmtools_array{6,7},
        nmtools_array{7,9},
        nmtools_array{8,9}
    });

    auto expected = nmtools_tuple{
        nmtools_array{2, 4},
        nmtools_array{3},
        nmtools_array{3},
        nmtools_array{4},
        nmtools_array{5},
        nmtools_array{6},
        nmtools_array{7},
        nmtools_array{9},
        nmtools_array{9},
        nmtools_array<int,0>{}
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 10 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.size(), 10 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

// trie
TEST_CASE("multi_digraph(case11)" * doctest::test_suite("network::multi_digraph"))
{
    // not supported
    // TODO: fix or reject
    // auto adjacency_list = nmtools_tuple{
    //     nmtools_array{1,2,3},
    //     nmtools_array{4,5},
    //     nmtools_array<int,0>{},
    //     nmtools_array{6},
    //     nmtools_array<int,0>{},
    //     nmtools_array{7,8,9},
    //     nmtools_array{10},
    //     nmtools_array<int,0>{},
    //     nmtools_array<int,0>{},
    //     nmtools_array<int,0>{},
    //     nmtools_array<int,0>{},
    // };
    auto adjacency_list = nmtools_list{
        nmtools_list{1,2,3},
        nmtools_list{4,5},
        nmtools_list<int>{},
        nmtools_list{6},
        nmtools_list<int>{},
        nmtools_list{7,8,9},
        nmtools_list{10},
        nmtools_list<int>{},
        nmtools_list<int>{},
        nmtools_list<int>{},
        nmtools_list<int>{},
    };
    auto node_attr = meta::as_value_v<nmtools_string>;
    auto edge_attr = meta::as_value_v<nmtools_string>;
    auto multi_digraph = network::multi_digraph(adjacency_list,nm::None,node_attr,edge_attr);

    multi_digraph.edges(0,1)  = "t";
    multi_digraph.edges(0,2)  = "A";
    multi_digraph.edges(0,3)  = "i";
    multi_digraph.edges(1,4)  = "o";
    multi_digraph.edges(1,5)  = "e";
    multi_digraph.edges(3,6)  = "n";
    multi_digraph.edges(5,7)  = "a";
    multi_digraph.edges(5,8)  = "d";
    multi_digraph.edges(5,9)  = "n";
    multi_digraph.edges(6,10) = "n";

    multi_digraph.nodes(1) = "t";
    multi_digraph.nodes(2) = "A";
    multi_digraph.nodes(3) = "i";
    multi_digraph.nodes(4) = "to";
    multi_digraph.nodes(5) = "te";
    multi_digraph.nodes(6) = "in";
    multi_digraph.nodes(7) = "tea";
    multi_digraph.nodes(8) = "ted";
    multi_digraph.nodes(9) = "ten";
    multi_digraph.nodes(10) = "inn";

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 11 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.size(), 10 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, adjacency_list )

    WRITE_GRAPHVIZ( multi_digraph );
}

/*=================================================================== */

TEST_CASE("constexpr_digraph(case1)" * doctest::test_suite("network::multi_digraph"))
{
    constexpr auto multi_digraph = [](){
        using adjacency_list_t = nmtools_static_vector<nmtools_static_vector<nm_index_t,4>,4>;
        using node_ids_t = nmtools_static_vector<nm_index_t,4>;
        auto multi_digraph = network::multi_digraph_t<adjacency_list_t,node_ids_t>();

        multi_digraph.add_node(1);
        multi_digraph.add_nodes_from(array{2,3}).add_edge(2,3);
        multi_digraph.add_node(4);
        return multi_digraph;
    }();

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("constexpr_digraph(case2)" * doctest::test_suite("network::multi_digraph"))
{
    constexpr auto multi_digraph = [](){
        using adjacency_list_t = nmtools_static_vector<nmtools_static_vector<nm_index_t,4>,4>;
        using node_ids_t = nmtools_static_vector<nm_index_t,4>;
        auto multi_digraph = network::multi_digraph_t<adjacency_list_t,node_ids_t>();

        multi_digraph.add_node(1);
        multi_digraph.add_nodes_from(array{2,3});
        multi_digraph.add_node(4);

        multi_digraph.add_edge(1,2);
        multi_digraph.add_edge(1,3);
        multi_digraph.add_edge(2,3);
        multi_digraph.add_edge(3,4);
        multi_digraph.add_edge(1,1); // self-loop

        return multi_digraph;
    }();

    auto expected = nmtools_tuple{
        nmtools_array{1,2,0},
        nmtools_array{2},
        nmtools_array{3},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.size(), 5 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("constexpr_digraph(case3)" * doctest::test_suite("network::multi_digraph"))
{
    constexpr auto multi_digraph = [](){
        constexpr auto max_nodes = meta::ct_v<4>;
        auto multi_digraph = network::multi_digraph(max_nodes)
            .add_node(1)
            .add_nodes_from(array{2,3})
            .add_node(4)
        ;

        multi_digraph.add_edges_from(nmtools_tuple{
            nmtools_array{1,2},
            nmtools_array{1,3},
            nmtools_array{2,3},
            nmtools_array{3,4},
            nmtools_array{1,1},
        });

        return multi_digraph;
    }();

    auto expected = nmtools_tuple{
        nmtools_array{1,2,0},
        nmtools_array{2},
        nmtools_array{3},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.size(), 5 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("constexpr_digraph(case4)" * doctest::test_suite("network::multi_digraph"))
{
    constexpr auto multi_digraph = [](){
        constexpr auto max_nodes = meta::ct_v<4>;
        auto multi_digraph = network::multi_digraph(max_nodes)
            .add_node(1)
            .add_nodes_from(array{2,3})
            .add_node(4)
        ;

        multi_digraph.add_edges_from(nmtools_tuple{
            nmtools_array{1,2},
            nmtools_array{1,3},
            nmtools_array{2,3},
            nmtools_array{3,4},
            nmtools_array{1,1},
        });

        return multi_digraph;
    }();

    auto expected = nmtools_list{
        nmtools_array{1,2},
        nmtools_array{1,3},
        nmtools_array{1,1},
        nmtools_array{2,3},
        nmtools_array{3,4},
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.out_edges(), expected );

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("constexpr_digraph(case5)" * doctest::test_suite("network::multi_digraph"))
{
    constexpr auto multi_digraph = [](){
        constexpr auto max_nodes = meta::ct_v<4>;
        auto multi_digraph = network::multi_digraph(max_nodes)
            .add_node(1)
            .add_nodes_from(array{2,3})
            .add_node(4)
        ;

        multi_digraph.add_edges_from(nmtools_tuple{
            nmtools_array{1,2},
            nmtools_array{1,3},
            nmtools_array{2,3},
            nmtools_array{3,4},
            nmtools_array{1,1},
        });

        return multi_digraph;
    }();

    CHECK_MESSAGE( true, utils::to_string(multi_digraph,utils::Graphviz) );

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("constexpr_digraph(case6)" * doctest::test_suite("network::multi_digraph"))
{
    constexpr auto list = nmtools_tuple{
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct},
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct}
    };
    auto multi_digraph = network::multi_digraph(list);
    static_assert( meta::is_constant_adjacency_list_v<decltype(multi_digraph.adjacency_list)> );

    auto result = multi_digraph.add_node(meta::ct_v<4>);
    static_assert( meta::is_constant_adjacency_list_v<decltype(result.adjacency_list)> );

    auto expected = nmtools_tuple{
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct},
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct},
        nmtools_tuple{}
    };
    
    NMTOOLS_ASSERT_EQUAL( result.order(), 5 );
    NMTOOLS_ASSERT_EQUAL( result.size(), 8 );
    NMTOOLS_ASSERT_EQUAL( nm::len(result.adjacency_list), 5 )
    NMTOOLS_ASSERT_EQUAL( result.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("constexpr_digraph(case7)" * doctest::test_suite("network::multi_digraph"))
{
    constexpr auto list = nmtools_tuple{
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct},
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct}
    };
    auto multi_digraph = network::multi_digraph(list);
    static_assert( meta::is_constant_adjacency_list_v<decltype(multi_digraph.adjacency_list)> );

    auto result = multi_digraph.add_node(meta::ct_v<4>);
    static_assert( meta::is_constant_adjacency_list_v<decltype(result.adjacency_list)> );

    auto expected = nmtools_list{
        nmtools_array{0,1},
        nmtools_array{0,3},
        nmtools_array{1,0},
        nmtools_array{1,2},
        nmtools_array{2,1},
        nmtools_array{2,3},
        nmtools_array{3,0},
        nmtools_array{3,2},
    };

    NMTOOLS_ASSERT_EQUAL( result.out_edges(), expected );

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("constexpr_digraph(case8)" * doctest::test_suite("network::multi_digraph"))
{
    constexpr auto list = nmtools_tuple{
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct},
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct}
    };
    auto multi_digraph = network::multi_digraph(list);
    static_assert( meta::is_constant_adjacency_list_v<decltype(multi_digraph.adjacency_list)> );

    auto result = multi_digraph.add_node(meta::ct_v<4>);
    static_assert( meta::is_constant_adjacency_list_v<decltype(result.adjacency_list)> );

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("constexpr_digraph(case9)" * doctest::test_suite("network::multi_digraph"))
{
    constexpr auto list = nmtools_tuple{
        nmtools_tuple{},
        nmtools_tuple{},
        nmtools_tuple{},
        nmtools_tuple{}
    };
    auto src_digraph = network::multi_digraph(list);
    auto idx0 = src_digraph.get_index(0_ct);
    static_assert( meta::is_same_v<decltype(idx0),meta::ct<0ul>> );
    auto multi_digraph = src_digraph
        .add_edge(0_ct,1_ct)
        .add_edge(0_ct,3_ct)
        .add_edge(1_ct,0_ct)
        .add_edge(1_ct,2_ct)
        .add_edge(2_ct,1_ct)
        .add_edge(2_ct,3_ct)
        .add_edge(3_ct,0_ct)
        .add_edge(3_ct,2_ct)
    ;
    static_assert( meta::is_constant_adjacency_list_v<decltype(multi_digraph.adjacency_list)> );

    auto result = multi_digraph.add_node(meta::ct_v<4>);
    static_assert( meta::is_constant_adjacency_list_v<decltype(result.adjacency_list)> );

    auto expected = nmtools_tuple{
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct},
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct},
        nmtools_tuple{}
    };
    NMTOOLS_ASSERT_EQUAL( result.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

/*=================================================================*/

TEST_CASE("digraph_attribute(case1)" * doctest::test_suite("network::multi_digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto node_ids = nmtools_list{1,2,3,4};
    auto node_attributes = nmtools_list<node_attribute>(4);
    auto multi_digraph  = network::multi_digraph(adj_list,node_ids,node_attributes);

    multi_digraph.add_edge(2,3);

    multi_digraph.nodes(1) = node_attribute{.kind=OpType::REDUCE,.weight=0.5f};

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )
    CHECK( multi_digraph.nodes(1).kind == OpType::REDUCE );
    CHECK( multi_digraph.nodes(2).kind == OpType::UNKNOWN );
    CHECK( multi_digraph.nodes(3).kind == OpType::UNKNOWN );
    CHECK( multi_digraph.nodes(4).kind == OpType::UNKNOWN );

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("digraph_attribute(case2)" * doctest::test_suite("network::multi_digraph"))
{
    auto node_attributes = meta::as_value_v<node_attribute>;
    auto edge_attributes = meta::as_value_v<edge_attribute>;
    auto multi_digraph = network::multi_digraph(nm::None,nm::None,node_attributes,edge_attributes);

    multi_digraph.add_node(0);
    multi_digraph.add_node(1);
    multi_digraph.add_node(2);
    multi_digraph.add_node(3);

    multi_digraph.add_edge(2,3,{.weight=0.75});
    multi_digraph.add_edge(2,0);
    multi_digraph.add_edge(2,1);
    multi_digraph.edges(2,1) = {.weight = 0.5};
    multi_digraph.edges(2,0).weight = 0.25;

    multi_digraph.nodes(1) = node_attribute{.kind=OpType::REDUCE,.weight=0.5f};

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
        nmtools_array{3,0,1},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_CLOSE( multi_digraph.edges(2,0).weight, 0.25 );
    NMTOOLS_ASSERT_CLOSE( multi_digraph.edges(2,1).weight, 0.5 );
    NMTOOLS_ASSERT_CLOSE( multi_digraph.edges(2,3).weight, 0.75 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.has_edge(2,3), true );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.has_edge(2,1), true );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.has_edge(3,2), false );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.has_edge(1,2), false );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.has_edge(0,1), false );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.has_edge(1,2), false );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )
    CHECK( multi_digraph.nodes(0).kind == OpType::UNKNOWN );
    CHECK( multi_digraph.nodes(1).kind == OpType::REDUCE );
    CHECK( multi_digraph.nodes(2).kind == OpType::UNKNOWN );
    CHECK( multi_digraph.nodes(3).kind == OpType::UNKNOWN );

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("digraph_attribute(case3)" * doctest::test_suite("network::multi_digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto node_ids = nmtools_list{1,2,3,4};
    auto node_attributes = nmtools_list<node_attribute>(4);
    auto edge_attributes = nmtools_list<nmtools_list<edge_attribute>>(4);
    auto multi_digraph  = network::multi_digraph(adj_list,node_ids,node_attributes,edge_attributes);

    multi_digraph.add_node(0);
    multi_digraph.add_node(1);
    multi_digraph.add_node(2);
    multi_digraph.add_node(3);

    multi_digraph.add_edge(2,3,{.weight=0.75});

    multi_digraph.nodes(1) = node_attribute{.kind=OpType::REDUCE,.weight=0.5f};

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )
    CHECK( multi_digraph.nodes(1).kind == OpType::REDUCE );
    CHECK( multi_digraph.nodes(2).kind == OpType::UNKNOWN );
    CHECK( multi_digraph.nodes(3).kind == OpType::UNKNOWN );
    CHECK( multi_digraph.nodes(4).kind == OpType::UNKNOWN );

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("digraph_attribute(case4)" * doctest::test_suite("network::multi_digraph"))
{
    auto node_attributes = meta::as_value_v<node_attribute>;
    auto edge_attributes = meta::as_value_v<edge_attribute>;
    auto multi_digraph = network::multi_digraph(nm::None,nm::None,node_attributes,edge_attributes);
    multi_digraph.add_nodes_from(nmtools_array{0,1,2,3,4,5,6,7,8,9});

    multi_digraph.add_edges_from(nmtools_list{
        nmtools_array{0,2},
        nmtools_array{0,4},
        nmtools_array{1,3},
        nmtools_array{2,3},
        nmtools_array{3,4},
        nmtools_array{4,5},
        nmtools_array{5,6},
        nmtools_array{6,7},
        nmtools_array{7,9},
        nmtools_array{8,9}
    });

    auto expected = nmtools_tuple{
        nmtools_array{2, 4},
        nmtools_array{3},
        nmtools_array{3},
        nmtools_array{4},
        nmtools_array{5},
        nmtools_array{6},
        nmtools_array{7},
        nmtools_array{9},
        nmtools_array{9},
        nmtools_array<int,0>{}
    };

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 10 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.size(), 10 );
    NMTOOLS_ASSERT_EQUAL( multi_digraph.adjacency_list, expected )

    WRITE_GRAPHVIZ( multi_digraph );
}

TEST_CASE("digraph_attribute(case5)" * doctest::test_suite("network::multi_digraph"))
{
    auto functors = fn::reshape[array{3,4}] * fn::flatten;
    auto adjacency_list = nmtools_tuple<nmtools_tuple<>>{};
    auto multi_digraph = network::multi_digraph(adjacency_list,nm::None,nmtools_tuple{fn::compute_node_t{functors,nm::None,nm::None,nm::None}});

    NMTOOLS_ASSERT_EQUAL( multi_digraph.order(), 1 );

    WRITE_GRAPHVIZ( multi_digraph );
}