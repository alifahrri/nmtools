#ifndef NMTOOLS_TESTING_DATA_NETWORK_TOPOLOGICAL_GENERATIONS_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_TOPOLOGICAL_GENERATIONS_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, topological_generations)
{
    
    using nmtools_array;
    using nmtools_tuple;
    using namespace nmtools::literals; 

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{};
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto generations = nmtools_tuple{};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<>>{};
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto generations = nmtools_tuple<nmtools_tuple<meta::ct<0>>>{};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{2_ct}, nmtools_tuple{3_ct}, nmtools_tuple{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto generations = nmtools_tuple{
            nmtools_tuple{0_ct}, nmtools_tuple{1_ct}, nmtools_tuple{2_ct}, nmtools_tuple{3_ct}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct}, nmtools_tuple{2_ct}, nmtools_tuple{3_ct}, nmtools_tuple{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto generations = nmtools_tuple{
            nmtools_tuple{0_ct, 1_ct}, nmtools_tuple{2_ct}, nmtools_tuple{3_ct}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct}, nmtools_tuple{}, nmtools_tuple{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto generations = nmtools_tuple{
            nmtools_tuple{0_ct}, nmtools_tuple{1_ct, 2_ct}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct}, nmtools_tuple{3_ct}, nmtools_tuple{3_ct}, nmtools_tuple{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto generations = nmtools_tuple{
            nmtools_tuple{0_ct}, nmtools_tuple{1_ct, 2_ct}, nmtools_tuple{3_ct}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{}, nmtools_tuple{3_ct}, nmtools_tuple{}, nmtools_tuple{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto generations = nmtools_tuple{
            nmtools_tuple{0_ct, 2_ct, 4_ct}, nmtools_tuple{1_ct, 3_ct}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct, 3_ct},    
            nmtools_tuple{3_ct, 4_ct},    
            nmtools_tuple{5_ct},          
            nmtools_tuple{5_ct, 6_ct},    
            nmtools_tuple{6_ct, 7_ct},    
            nmtools_tuple{8_ct},          
            nmtools_tuple{8_ct, 9_ct},    
            nmtools_tuple{9_ct},          
            nmtools_tuple{},           
            nmtools_tuple{}            
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto generations = nmtools_tuple{
            nmtools_tuple{0_ct, 1_ct}, nmtools_tuple{2_ct, 3_ct, 4_ct}, nmtools_tuple{5_ct, 6_ct, 7_ct}, nmtools_tuple{8_ct, 9_ct}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{2_ct}, nmtools_tuple{0_ct}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        
        constexpr inline auto generations = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<meta::ct<0>>>{};
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        
        constexpr inline auto generations = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{2_ct}, nmtools_tuple{1_ct, 3_ct}, nmtools_tuple{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        
        constexpr inline auto generations = meta::Nothing;
    }

} 

#endif 
