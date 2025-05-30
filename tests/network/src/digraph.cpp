#include "nmtools/network/digraph.hpp"
#include "nmtools/testing/doctest.hpp"

#include <fstream>

namespace nm = nmtools;
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

    auto to_string() const noexcept
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

    auto to_string() const noexcept
    {
        auto str = nmtools_string();

        // str += "{";
        str += "weight=";
        str += utils::to_string(weight);
        // str += "}";

        return str;
    }
};

/*==================================================================*/

TEST_CASE("digraph(case1)" * doctest::test_suite("network::digraph"))
{
    auto digraph = network::digraph();

    digraph.add_node(1);
    digraph.add_nodes_from(array{2,3}).add_edge(2,3);
    digraph.add_node(4);

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( digraph.number_of_nodes(), 4 );
    NMTOOLS_ASSERT_EQUAL( digraph.number_of_edges(), 1 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("digraph(case2)" * doctest::test_suite("network::digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto node_ids = nmtools_list{1,2,3,4};
    auto digraph  = network::digraph(adj_list,node_ids);

    digraph.add_nodes_from(array{2,3}).add_edge(2,3);

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("digraph(case3)" * doctest::test_suite("network::digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto digraph  = network::digraph(adj_list);

    digraph.add_nodes_from(array{1,2}).add_edge(1,2);

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("digraph(case4)" * doctest::test_suite("network::digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto digraph  = network::digraph(adj_list);

    digraph.add_nodes_from(array{1,2}).add_edge(1,2);

    auto expected = nmtools_list{
        nmtools_array{1,2}
    };

    NMTOOLS_ASSERT_EQUAL( digraph.out_edges(), expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("digraph(case5)" * doctest::test_suite("network::digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto digraph  = network::digraph(adj_list);

    digraph.add_nodes_from(array{1,2});

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("digraph(case6)" * doctest::test_suite("network::digraph"))
{
    auto digraph = network::digraph();

    digraph.add_node(1);
    digraph.add_nodes_from(array{2,3});
    digraph.add_node(4);

    digraph.add_edge(1,2);
    digraph.add_edge(1,3);
    digraph.add_edge(2,3);
    digraph.add_edge(3,4);
    digraph.add_edge(1,1); // self-loop

    auto expected = nmtools_tuple{
        nmtools_array{1,2,0},
        nmtools_array{2},
        nmtools_array{3},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 5 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("digraph(case7)" * doctest::test_suite("network::digraph"))
{
    constexpr auto digraph = [](){
        constexpr auto max_nodes = meta::ct_v<4>;
        constexpr auto digraph = network::digraph(max_nodes)
            .add_node(1)
            .add_nodes_from(array{2,3})
            .add_node(4)
            .add_edge(1,2)
            .add_edge(1,3)
            .add_edge(2,3)
            .add_edge(3,4)
            .add_edge(1,1); // self-loop

        return digraph;
    }();

    auto expected = nmtools_tuple{
        nmtools_array{1,2,0},
        nmtools_array{2},
        nmtools_array{3},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 5 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

using namespace nmtools::literals;

TEST_CASE("digraph(case8)" * doctest::test_suite("network::digraph"))
{
    auto digraph = network::digraph();
    digraph.add_node(0);
    digraph.add_node(1);
    digraph.add_node(2);
    digraph.add_node(3);
    digraph.add_node(4);
    digraph.add_edge(0,1);
    digraph.add_edge(0,3);
    digraph.add_edge(1,0);
    digraph.add_edge(1,2);
    digraph.add_edge(2,1);
    digraph.add_edge(2,3);
    digraph.add_edge(3,0);
    digraph.add_edge(3,2);

    auto expected = nmtools_tuple{
        nmtools_array{1, 3},
        nmtools_array{0, 2},
        nmtools_array{1, 3},
        nmtools_array{0, 2},
        nmtools_array<int,0>{}
    };

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 5 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 8 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("digraph(case9)" * doctest::test_suite("network::digraph"))
{
    auto digraph = network::digraph();
    digraph.add_node(0);
    digraph.add_node(1);
    digraph.add_node(2);
    digraph.add_node(3);
    digraph.add_node(4);
    digraph.add_node(4);
    digraph.add_edge(0,1);
    digraph.add_edge(0,2);
    digraph.add_edge(1,2);
    digraph.add_edge(2,4);
    digraph.add_edge(2,3);
    digraph.add_edge(4,5);
    digraph.add_edge(3,5);

    auto expected = nmtools_tuple{
        nmtools_array{1, 2},
        nmtools_array{2},
        nmtools_array{4,3},
        nmtools_array{5},
        nmtools_array{5},
        nmtools_array<int,0>{}
    };

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 6 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 7 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("digraph(case10)" * doctest::test_suite("network::digraph"))
{
    auto digraph = network::digraph();
    digraph.add_nodes_from(nmtools_array{0,1,2,3,4,5,6,7,8,9});

    digraph.add_edges_from(nmtools_list{
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

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 10 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 10 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

// trie
TEST_CASE("digraph(case11)" * doctest::test_suite("network::digraph"))
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
    auto digraph = network::digraph(adjacency_list,nm::None,node_attr,edge_attr);

    digraph.edges(0,1)  = "t";
    digraph.edges(0,2)  = "A";
    digraph.edges(0,3)  = "i";
    digraph.edges(1,4)  = "o";
    digraph.edges(1,5)  = "e";
    digraph.edges(3,6)  = "n";
    digraph.edges(5,7)  = "a";
    digraph.edges(5,8)  = "d";
    digraph.edges(5,9)  = "n";
    digraph.edges(6,10) = "n";

    digraph.nodes(1) = "t";
    digraph.nodes(2) = "A";
    digraph.nodes(3) = "i";
    digraph.nodes(4) = "to";
    digraph.nodes(5) = "te";
    digraph.nodes(6) = "in";
    digraph.nodes(7) = "tea";
    digraph.nodes(8) = "ted";
    digraph.nodes(9) = "ten";
    digraph.nodes(10) = "inn";

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 11 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 10 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, adjacency_list )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

/*=================================================================== */

TEST_CASE("constexpr_digraph(case1)" * doctest::test_suite("network::digraph"))
{
    constexpr auto digraph = [](){
        using adjacency_list_t = nmtools_static_vector<nmtools_static_vector<nm_index_t,4>,4>;
        using node_ids_t = nmtools_static_vector<nm_index_t,4>;
        auto digraph = network::digraph_t<adjacency_list_t,node_ids_t>();

        digraph.add_node(1);
        digraph.add_nodes_from(array{2,3}).add_edge(2,3);
        digraph.add_node(4);
        return digraph;
    }();

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("constexpr_digraph(case2)" * doctest::test_suite("network::digraph"))
{
    constexpr auto digraph = [](){
        using adjacency_list_t = nmtools_static_vector<nmtools_static_vector<nm_index_t,4>,4>;
        using node_ids_t = nmtools_static_vector<nm_index_t,4>;
        auto digraph = network::digraph_t<adjacency_list_t,node_ids_t>();

        digraph.add_node(1);
        digraph.add_nodes_from(array{2,3});
        digraph.add_node(4);

        digraph.add_edge(1,2);
        digraph.add_edge(1,3);
        digraph.add_edge(2,3);
        digraph.add_edge(3,4);
        digraph.add_edge(1,1); // self-loop

        return digraph;
    }();

    auto expected = nmtools_tuple{
        nmtools_array{1,2,0},
        nmtools_array{2},
        nmtools_array{3},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 5 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("constexpr_digraph(case3)" * doctest::test_suite("network::digraph"))
{
    constexpr auto digraph = [](){
        constexpr auto max_nodes = meta::ct_v<4>;
        auto digraph = network::digraph(max_nodes)
            .add_node(1)
            .add_nodes_from(array{2,3})
            .add_node(4)
        ;

        digraph.add_edges_from(nmtools_tuple{
            nmtools_array{1,2},
            nmtools_array{1,3},
            nmtools_array{2,3},
            nmtools_array{3,4},
            nmtools_array{1,1},
        });

        return digraph;
    }();

    auto expected = nmtools_tuple{
        nmtools_array{1,2,0},
        nmtools_array{2},
        nmtools_array{3},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 5 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("constexpr_digraph(case4)" * doctest::test_suite("network::digraph"))
{
    constexpr auto digraph = [](){
        constexpr auto max_nodes = meta::ct_v<4>;
        auto digraph = network::digraph(max_nodes)
            .add_node(1)
            .add_nodes_from(array{2,3})
            .add_node(4)
        ;

        digraph.add_edges_from(nmtools_tuple{
            nmtools_array{1,2},
            nmtools_array{1,3},
            nmtools_array{2,3},
            nmtools_array{3,4},
            nmtools_array{1,1},
        });

        return digraph;
    }();

    auto expected = nmtools_list{
        nmtools_array{1,2},
        nmtools_array{1,3},
        nmtools_array{1,1},
        nmtools_array{2,3},
        nmtools_array{3,4},
    };

    NMTOOLS_ASSERT_EQUAL( digraph.out_edges(), expected );

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("constexpr_digraph(case5)" * doctest::test_suite("network::digraph"))
{
    constexpr auto digraph = [](){
        constexpr auto max_nodes = meta::ct_v<4>;
        auto digraph = network::digraph(max_nodes)
            .add_node(1)
            .add_nodes_from(array{2,3})
            .add_node(4)
        ;

        digraph.add_edges_from(nmtools_tuple{
            nmtools_array{1,2},
            nmtools_array{1,3},
            nmtools_array{2,3},
            nmtools_array{3,4},
            nmtools_array{1,1},
        });

        return digraph;
    }();

    CHECK_MESSAGE( true, utils::to_string(digraph,utils::Graphviz) );

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("constexpr_digraph(case6)" * doctest::test_suite("network::digraph"))
{
    constexpr auto list = nmtools_tuple{
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct},
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct}
    };
    auto digraph = network::digraph(list);
    static_assert( meta::is_constant_adjacency_list_v<decltype(digraph.adjacency_list)> );

    auto result = digraph.add_node(meta::ct_v<4>);
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

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("constexpr_digraph(case7)" * doctest::test_suite("network::digraph"))
{
    constexpr auto list = nmtools_tuple{
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct},
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct}
    };
    auto digraph = network::digraph(list);
    static_assert( meta::is_constant_adjacency_list_v<decltype(digraph.adjacency_list)> );

    auto result = digraph.add_node(meta::ct_v<4>);
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

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("constexpr_digraph(case8)" * doctest::test_suite("network::digraph"))
{
    constexpr auto list = nmtools_tuple{
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct},
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct}
    };
    auto digraph = network::digraph(list);
    static_assert( meta::is_constant_adjacency_list_v<decltype(digraph.adjacency_list)> );

    auto result = digraph.add_node(meta::ct_v<4>);
    static_assert( meta::is_constant_adjacency_list_v<decltype(result.adjacency_list)> );

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("constexpr_digraph(case9)" * doctest::test_suite("network::digraph"))
{
    constexpr auto list = nmtools_tuple{
        nmtools_tuple{},
        nmtools_tuple{},
        nmtools_tuple{},
        nmtools_tuple{}
    };
    auto digraph = network::digraph(list)
        .add_edge(0_ct,1_ct)
        .add_edge(0_ct,3_ct)
        .add_edge(1_ct,0_ct)
        .add_edge(1_ct,2_ct)
        .add_edge(2_ct,1_ct)
        .add_edge(2_ct,3_ct)
        .add_edge(3_ct,0_ct)
        .add_edge(3_ct,2_ct)
    ;
    static_assert( meta::is_constant_adjacency_list_v<decltype(digraph.adjacency_list)> );

    auto result = digraph.add_node(meta::ct_v<4>);
    static_assert( meta::is_constant_adjacency_list_v<decltype(result.adjacency_list)> );

    auto expected = nmtools_tuple{
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct},
        nmtools_tuple{1_ct, 3_ct},
        nmtools_tuple{0_ct, 2_ct},
        nmtools_tuple{}
    };
    NMTOOLS_ASSERT_EQUAL( result.adjacency_list, expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

/*=================================================================*/

TEST_CASE("digraph_attribute(case1)" * doctest::test_suite("network::digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto node_ids = nmtools_list{1,2,3,4};
    auto node_attributes = nmtools_list<node_attribute>(4);
    auto digraph  = network::digraph(adj_list,node_ids,node_attributes);

    digraph.add_edge(2,3);

    digraph.nodes(1) = node_attribute{.kind=OpType::REDUCE,.weight=0.5f};

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )
    CHECK( digraph.nodes(1).kind == OpType::REDUCE );
    CHECK( digraph.nodes(2).kind == OpType::UNKNOWN );
    CHECK( digraph.nodes(3).kind == OpType::UNKNOWN );
    CHECK( digraph.nodes(4).kind == OpType::UNKNOWN );

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("digraph_attribute(case2)" * doctest::test_suite("network::digraph"))
{
    auto node_attributes = meta::as_value_v<node_attribute>;
    auto edge_attributes = meta::as_value_v<edge_attribute>;
    auto digraph = network::digraph(nm::None,nm::None,node_attributes,edge_attributes);

    digraph.add_node(0);
    digraph.add_node(1);
    digraph.add_node(2);
    digraph.add_node(3);

    digraph.add_edge(2,3,{.weight=0.75});
    digraph.add_edge(2,0);
    digraph.add_edge(2,1);
    digraph.edges(2,1) = {.weight = 0.5};
    digraph.edges(2,0).weight = 0.25;

    digraph.nodes(1) = node_attribute{.kind=OpType::REDUCE,.weight=0.5f};

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
        nmtools_array{3,0,1},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_CLOSE( digraph.edges(2,0).weight, 0.25 );
    NMTOOLS_ASSERT_CLOSE( digraph.edges(2,1).weight, 0.5 );
    NMTOOLS_ASSERT_CLOSE( digraph.edges(2,3).weight, 0.75 );
    NMTOOLS_ASSERT_EQUAL( digraph.has_edge(2,3), true );
    NMTOOLS_ASSERT_EQUAL( digraph.has_edge(2,1), true );
    NMTOOLS_ASSERT_EQUAL( digraph.has_edge(3,2), false );
    NMTOOLS_ASSERT_EQUAL( digraph.has_edge(1,2), false );
    NMTOOLS_ASSERT_EQUAL( digraph.has_edge(0,1), false );
    NMTOOLS_ASSERT_EQUAL( digraph.has_edge(1,2), false );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )
    CHECK( digraph.nodes(0).kind == OpType::UNKNOWN );
    CHECK( digraph.nodes(1).kind == OpType::REDUCE );
    CHECK( digraph.nodes(2).kind == OpType::UNKNOWN );
    CHECK( digraph.nodes(3).kind == OpType::UNKNOWN );

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("digraph_attribute(case3)" * doctest::test_suite("network::digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto node_ids = nmtools_list{1,2,3,4};
    auto node_attributes = nmtools_list<node_attribute>(4);
    auto edge_attributes = nmtools_list<nmtools_list<edge_attribute>>(4);
    auto digraph  = network::digraph(adj_list,node_ids,node_attributes,edge_attributes);

    digraph.add_node(0);
    digraph.add_node(1);
    digraph.add_node(2);
    digraph.add_node(3);

    digraph.add_edge(2,3,{.weight=0.75});

    digraph.nodes(1) = node_attribute{.kind=OpType::REDUCE,.weight=0.5f};

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )
    CHECK( digraph.nodes(1).kind == OpType::REDUCE );
    CHECK( digraph.nodes(2).kind == OpType::UNKNOWN );
    CHECK( digraph.nodes(3).kind == OpType::UNKNOWN );
    CHECK( digraph.nodes(4).kind == OpType::UNKNOWN );

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}

TEST_CASE("digraph_attribute(case4)" * doctest::test_suite("network::digraph"))
{
    auto node_attributes = meta::as_value_v<node_attribute>;
    auto edge_attributes = meta::as_value_v<edge_attribute>;
    auto digraph = network::digraph(nm::None,nm::None,node_attributes,edge_attributes);
    digraph.add_nodes_from(nmtools_array{0,1,2,3,4,5,6,7,8,9});

    digraph.add_edges_from(nmtools_list{
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

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 10 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 10 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )

    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    // write to file for convinient visualizing
    std::ofstream outputFile;
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc);
    outputFile << graphviz << std::endl;
}