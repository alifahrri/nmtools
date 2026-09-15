#ifndef NMTOOLS_TESTING_DATA_NETWORK_HAS_PATH_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_HAS_PATH_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, has_path)
{
    using nmtools_array;
    using nmtools_tuple;
    using nmtools_static_vector;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            array{1},
            array{2},
            array<int,0>(),
        };

        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 2;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline bool exists = true;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            array{1},
            array<int,0>(),
            array{3},
            array<int,0>(),
        };
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 3;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline bool exists = false;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            array{1},
            array<int,0>(),
        };
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 0;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline bool exists = true;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            array{1},
            array<int,0>(),
            array<int,0>(),
        };
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 2;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline bool exists = false;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            array{1,2},
            array{3},
            array{4},
            array<int,0>(),
            array{0},
        };
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 3;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline bool exists = true;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            array{1},
            array{0},
            array{3},
            array{2},
        };
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 2;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline bool exists = false;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            array{1},
            array<int,0>(),
        };
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 5;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline bool exists = false;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{};
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 0;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline bool exists = false;
    }


}

#endif // NMTOOLS_TESTING_DATA_NETWORK_HAS_PATH_HPP
