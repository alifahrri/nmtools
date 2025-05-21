#include "nmtools/network/digraph.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace network = nm::network;
namespace utils = nm::utils;

using nmtools_array;

enum class OpType : int
{
    INDEXING=0,
    UFUNC=1,
    REDUCE=2,
    UNKNOWN=3,
};

struct attribute
{
    OpType kind;
    float weight;
};

TEST_CASE("digraph(case1a)" * doctest::test_suite("network::digraph"))
{
    auto digraph = network::digraph();

    digraph.add_node(1);
    digraph.add_nodes_from(array{2,3});
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
    // CHECK_MESSAGE( true, utils::to_string(digraph,utils::Graphviz) )
}

TEST_CASE("digraph(case1b)" * doctest::test_suite("network::digraph"))
{
    constexpr auto digraph = [](){
        using adjacency_list_t = nmtools_static_vector<nmtools_static_vector<nm_index_t,4>,4>;
        using node_ids_t = nmtools_static_vector<nm_index_t,4>;
        auto digraph = network::digraph_t<adjacency_list_t,node_ids_t>();

        digraph.add_node(1);
        digraph.add_nodes_from(array{2,3});
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
}

TEST_CASE("digraph(case1c)" * doctest::test_suite("network::digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto node_ids = nmtools_list{1,2,3,4};
    auto digraph  = network::digraph(adj_list,node_ids);

    digraph.add_nodes_from(array{2,3});

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )
}

TEST_CASE("digraph(case1d)" * doctest::test_suite("network::digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto digraph  = network::digraph(adj_list);

    digraph.add_nodes_from(array{1,2});

    auto expected = nmtools_tuple{
        nmtools_array<int,0>{},
        nmtools_array{2},
        nmtools_array<int,0>{},
        nmtools_array<int,0>{},
    };

    NMTOOLS_ASSERT_EQUAL( digraph.order(), 4 );
    NMTOOLS_ASSERT_EQUAL( digraph.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )
}

// TEST_CASE("digraph(case1e)" * doctest::test_suite("network::digraph"))
// {
//     auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
//     auto node_ids = nmtools_list{1,2,3,4};
//     auto attributes = nmtools_list<attribute>(4);
//     auto digraph  = network::digraph(adj_list,node_ids,attributes);

//     digraph.add_edge(2,3);

//     digraph.nodes(0) = attribute{.kind=OpType::REDUCE,.weight=0.5f};

//     auto expected = nmtools_tuple{
//         nmtools_array<int,0>{},
//         nmtools_array{2},
//         nmtools_array<int,0>{},
//         nmtools_array<int,0>{},
//     };

//     NMTOOLS_ASSERT_EQUAL( digraph.adjacency_list, expected )
// }

TEST_CASE("digraph(case1f)" * doctest::test_suite("network::digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto digraph  = network::digraph(adj_list);

    digraph.add_nodes_from(array{1,2});

    auto expected = nmtools_list{
        nmtools_array{1,2}
    };

    NMTOOLS_ASSERT_EQUAL( digraph.out_edges(), expected )
}

TEST_CASE("digraph(case1g)" * doctest::test_suite("network::digraph"))
{
    auto adj_list = nmtools_list<nmtools_list<nm_index_t>>(4);
    auto digraph  = network::digraph(adj_list);

    digraph.add_nodes_from(array{1,2});

    CHECK_MESSAGE( true, utils::to_string(digraph,utils::Graphviz) );
}

TEST_CASE("digraph(case2a)" * doctest::test_suite("network::digraph"))
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
}

TEST_CASE("digraph(case2b)" * doctest::test_suite("network::digraph"))
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
}

TEST_CASE("digraph(case2c)" * doctest::test_suite("network::digraph"))
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
}

TEST_CASE("digraph(case2d)" * doctest::test_suite("network::digraph"))
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
}

TEST_CASE("digraph(case2e)" * doctest::test_suite("network::digraph"))
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
}

TEST_CASE("digraph(case2f)" * doctest::test_suite("network::digraph"))
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
}

using namespace nmtools::literals;

TEST_CASE("digraph(case3a)" * doctest::test_suite("network::digraph"))
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
}

TEST_CASE("digraph(case3b)" * doctest::test_suite("network::digraph"))
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
}

TEST_CASE("digraph(case3c)" * doctest::test_suite("network::digraph"))
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
}

TEST_CASE("digraph(case3d)" * doctest::test_suite("network::digraph"))
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

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("digraph(case4a)" * doctest::test_suite("network::digraph"))
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
}