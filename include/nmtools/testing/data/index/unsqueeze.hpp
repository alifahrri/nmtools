#ifndef NMTOOLS_TESTING_DATA_INDEX_UNSQUEEZE_HPP
#define NMTOOLS_TESTING_DATA_INDEX_UNSQUEEZE_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(shape_unsqueeze)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[2] = {3,4};
        inline int axis = 0;

        inline auto shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto axis_ct = 0_ct;
        
        inline auto shape_cl = to_clipped(shape_ct);

        inline auto shape_nl1 = to_nullable(shape,0);
        inline auto shape_nl2 = to_nullable(shape,1);

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3] = {1,3,4};
        inline auto result_nl1 = to_nullable(result,1);
        inline auto result_nl2 = to_nullable(result,2);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[2] = {3,4};
        inline int axis = 1;

        inline auto shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto axis_ct = 1_ct;
        
        inline auto shape_cl = to_clipped(shape_ct);

        inline auto shape_nl1 = to_nullable(shape,0);
        inline auto shape_nl2 = to_nullable(shape,1);

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3] = {3,1,4};
        inline auto result_nl1 = to_nullable(result,0);
        inline auto result_nl2 = to_nullable(result,2);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[2] = {3,4};
        inline int axis = 2;

        inline auto shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto axis_ct = 2_ct;
        
        inline auto shape_cl = to_clipped(shape_ct);

        inline auto shape_nl1 = to_nullable(shape,0);
        inline auto shape_nl2 = to_nullable(shape,1);

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {3,4,1};
        inline auto result_nl1 = to_nullable(result,0);
        inline auto result_nl2 = to_nullable(result,1);
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_UNSQUEEZE_HPP