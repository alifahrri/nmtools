#ifndef NMTOOLS_TESTING_DATA_NETWORK_CONTRACTED_EDGE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_CONTRACTED_EDGE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, contracted_edge)
{
    using nmtools_array;
    using nmtools_tuple;

    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 3_ct},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{1_ct, 3_ct},
            nmtools_tuple{0_ct, 2_ct}
        };
        constexpr inline auto edge_to_contract = array{0, 1};
        constexpr inline bool self_loops_flag = true;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{0_ct,1_ct};
        constexpr inline auto self_loops_flag_ct  = 1_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{10_ct,11_ct,12_ct,13_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,4>{"n10","n11","n12","n13"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto contracted_list = nmtools_tuple{
            array{0, 1, 2},
            array{0, 2},
            array{0, 1}
        };
        constexpr inline auto dst_node_ids = nmtools_tuple{11_ct,12_ct,13_ct};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 3_ct},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{1_ct, 3_ct},
            nmtools_tuple{0_ct, 2_ct}
        };
        constexpr inline auto edge_to_contract = array{0, 1};
        constexpr inline bool self_loops_flag = false;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{0_ct,1_ct};
        constexpr inline auto self_loops_flag_ct  = 0_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{10_ct,11_ct,12_ct,13_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,4>{"n10","n11","n12","n13"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto contracted_list = nmtools_tuple{
            array{1, 2},
            array{0, 2},
            array{0, 1}
        };
        constexpr inline auto dst_node_ids = nmtools_tuple{11_ct,12_ct,13_ct};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto edge_to_contract = array{0, 1};
        constexpr inline bool self_loops_flag = true;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{0_ct,1_ct};
        constexpr inline auto self_loops_flag_ct  = 1_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{11_ct,12_ct,13_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,3>{"n11","n12","n13"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto contracted_list = nmtools_tuple{
            array{1},
            array<int,0>{}
        };
        inline auto dst_node_ids = nmtools_tuple{12_ct,13_ct};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto edge_to_contract = array{1, 0};
        constexpr inline bool self_loops_flag = true;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{1_ct,0_ct};
        constexpr inline auto self_loops_flag_ct  = 1_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{11_ct,12_ct,13_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,3>{"n11","n12","n13"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto contracted_list = nmtools_tuple{
            array{1},
            array<int,0>{}
        };

        inline auto dst_node_ids = nmtools_tuple{11_ct,13_ct};
    }
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto edge_to_contract = array{1, 0};
        constexpr inline bool self_loops_flag = false;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{1_ct,0_ct};
        constexpr inline auto self_loops_flag_ct  = 0_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{11_ct,12_ct,13_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,3>{"n11","n12","n13"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto contracted_list = nmtools_tuple{
            array{1},
            array<int,0>{}
        };

        inline auto dst_node_ids = nmtools_tuple{11_ct,13_ct};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{0_ct}
        };
        constexpr inline auto edge_to_contract = array{0, 1};
        constexpr inline bool self_loops_flag = true;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{0_ct,1_ct};
        constexpr inline auto self_loops_flag_ct = 1_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{100_ct,200_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,3>{"n11","n12"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto contracted_list = nmtools_tuple{
            array{0}
        };

        inline auto dst_node_ids = nmtools_tuple{200_ct};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{0_ct}
        };
        constexpr inline auto edge_to_contract = array{0, 1};
        constexpr inline bool self_loops_flag = false;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{0_ct,1_ct};
        constexpr inline auto self_loops_flag_ct  = 0_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{100_ct,200_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,3>{"n11","n12"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto contracted_list = nmtools_tuple{
            array<int,0>{}
        };

        inline auto dst_node_ids = nmtools_tuple{200_ct};
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_CONTRACTED_EDGE_HPP
