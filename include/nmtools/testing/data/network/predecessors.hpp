#ifndef NMTOOLS_TESTING_DATA_NETWORK_PREDECESSORS_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_PREDECESSORS_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, predecessors)
{
    using nmtools_array;
    using nmtools_tuple;
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{},
            nmtools_tuple{2_ct}
        };
        constexpr inline auto node_idx = 2;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400};

        inline auto node_idx_ct = 2_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto preds = nmtools_array{0, 1, 3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 1;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 1_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto preds = nmtools_array{0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline nmtools_array<int,0> preds {};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct, 0_ct},
            nmtools_tuple{0_ct}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto preds = nmtools_array{1, 2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct, 4_ct},
            nmtools_tuple{0_ct, 4_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 4;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400,500};

        inline auto node_idx_ct = 4_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct,500_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto preds = nmtools_array{2, 3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 5;
        constexpr inline auto src_node_ids = nmtools_array{100,200};

        inline auto node_idx_ct = 5_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto preds = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{};
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline nmtools_array<int,0> preds {};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{},
            nmtools_tuple{0_ct, 1_ct}
        };

        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400};
        constexpr inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto preds = nmtools_tuple{
            array{3},
            array{0, 3},
            array{0, 1},
            array<int,0>{}
        };
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_PREDECESSORS_HPP
