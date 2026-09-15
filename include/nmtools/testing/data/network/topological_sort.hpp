#ifndef NMTOOLS_TESTING_DATA_NETWORK_TOPOLOGICAL_SORT_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_TOPOLOGICAL_SORT_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, topological_sort)
{
    using namespace literals;

    using nmtools_array;
    using nmtools_tuple;
    using nmtools_either; 
    using nmtools_list;   

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},          
            nmtools_tuple{2_ct},          
            nmtools_tuple{},              
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        
        constexpr inline auto sorted_nodes = array{0, 1, 2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct, 3_ct},       
            nmtools_tuple{2_ct, 3_ct},       
            nmtools_tuple{},    
            nmtools_tuple{},    
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        
        constexpr inline auto sorted_nodes = array{0, 1, 2, 3};
        
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},          
            nmtools_tuple{2_ct},          
            nmtools_tuple{0_ct},          
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        
        constexpr inline auto sorted_nodes = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{}; 
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        
        constexpr inline array<int,0> sorted_nodes {};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct}, 
            nmtools_tuple{},     
            nmtools_tuple{3_ct}, 
            nmtools_tuple{},     
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        
        constexpr inline auto sorted_nodes = array{0, 2, 1, 3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<>>{};
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto sorted_nodes = array{0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct}, 
            nmtools_tuple{3_ct},       
            nmtools_tuple{3_ct, 4_ct}, 
            nmtools_tuple{5_ct},       
            nmtools_tuple{5_ct},       
            nmtools_tuple{},           
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        
        constexpr inline auto sorted_nodes = array{0, 1, 2, 3, 4, 5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},          
            nmtools_tuple{1_ct},          
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        
        constexpr inline auto sorted_nodes = meta::Nothing;
    }

} 

#endif 
