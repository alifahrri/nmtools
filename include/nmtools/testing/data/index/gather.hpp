#ifndef NMTOOLS_TESTING_DATA_INDEX_GATHER_HPP
#define NMTOOLS_TESTING_DATA_INDEX_GATHER_HPP

#include "nmtools/array/index/gather.hpp"
#include "nmtools/utility/isequal.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;
using namespace nm::literals;
using nmtools::utils::isequal;

NMTOOLS_TESTING_DECLARE_CASE(gather)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int32_t vec[3]     = {1,2,3};
        inline int32_t indices[3] = {0,1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(vec);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        inline auto vec_ct     = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct,2_ct};
        inline auto vec_cl     = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"2:[2]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3] = {1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int vec[3]     = {1,2,3};
        inline int indices[3] = {1,0,2};
        NMTOOLS_CAST_INDEX_ARRAYS(vec);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        inline auto vec_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto vec_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct,2_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"0:[1]"_ct,"2:[2]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3] = {2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int vec[3]     = {1,2,3};
        inline int indices[3] = {1,2,0};
        NMTOOLS_CAST_INDEX_ARRAYS(vec);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        inline auto vec_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto vec_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto indices_ct = nmtools_tuple{1_ct,2_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"0:[1]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {2,3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int vec[3]     = {1,2,3};
        inline int indices[3] = {2,0,1};
        NMTOOLS_CAST_INDEX_ARRAYS(vec);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        inline auto vec_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto vec_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto indices_ct = nmtools_tuple{2_ct,0_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"2:[2]"_ct,"0:[1]"_ct,"1:[1]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[3] = {3,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int vec[3]     = {1,2,3};
        inline int indices[3] = {2,1,0};
        NMTOOLS_CAST_INDEX_ARRAYS(vec);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        inline auto vec_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto vec_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto indices_ct = nmtools_tuple{2_ct,1_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct,"0:[1]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {3,2,1};
    }
    
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int vec[5]     = {1,2,3,4,5};
        inline int indices[3] = {2,1,0};
        NMTOOLS_CAST_INDEX_ARRAYS(vec);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        inline auto vec_ct = nmtools_tuple{1_ct,2_ct,3_ct,4_ct,5_ct};
        inline auto vec_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct,"4:[4]"_ct,"5:[5]"_ct};
        inline auto indices_ct = nmtools_tuple{2_ct,1_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct,"0:[1]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3] = {3,2,1};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_GATHER_HPP