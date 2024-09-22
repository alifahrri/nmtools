#ifndef NMTOOLS_TESTING_DATA_INDEX_SWAPAXES_HPP
#define NMTOOLS_TESTING_DATA_INDEX_SWAPAXES_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index,swapaxes_to_transpose)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int src_dim = 2;
        inline int axis1   = 0;
        inline int axis2   = 1;

        inline auto src_dim_ct = 2_ct;
        inline auto axis1_ct   = 0_ct;
        inline auto axis2_ct   = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int src_dim = 3;
        inline int axis1   = 0;
        inline int axis2   = 1;

        inline auto src_dim_ct = 3_ct;
        inline auto axis1_ct   = 0_ct;
        inline auto axis2_ct   = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int src_dim = 3;
        inline int axis1   = 2;
        inline int axis2   = 1;

        inline auto src_dim_ct = 3_ct;
        inline auto axis1_ct   = 2_ct;
        inline auto axis2_ct   = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {0,2,1};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_SWAPAXES_HPP