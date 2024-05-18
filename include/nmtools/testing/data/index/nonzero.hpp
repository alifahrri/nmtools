#ifndef NMTOOLS_TESTING_DATA_INDEX_NONZERO_HPP
#define NMTOOLS_TESTING_DATA_INDEX_NONZERO_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(nonzero)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int x[6] = {0,1,2,3,4,5};
        NMTOOLS_CAST_INDEX_ARRAYS(x);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(x);
        inline auto x_ct = nmtools_tuple{0_ct,1_ct,2_ct,3_ct,4_ct,5_ct};
        inline auto x_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct,"4:[4]"_ct,"5:[5]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[5] = {1,2,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int x[6] = {1,2,0,3,5,6};
        NMTOOLS_CAST_INDEX_ARRAYS(x);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(x);
        inline auto x_ct = nmtools_tuple{1_ct,2_ct,0_ct,3_ct,5_ct,6_ct};
        inline auto x_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"0:[1]"_ct,"3:[3]"_ct,"5:[5]"_ct,"6:[6]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[5] = {0,1,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline nm_bool_t x[6] = {true,true,false,true,true,true};
        NMTOOLS_CAST_INDEX_ARRAYS(x);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[5] = {0,1,3,4,5};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_NONZERO_HPP