#ifndef NMTOOLS_TESTING_DATA_INDEX_DIAGONAL_HPP
#define NMTOOLS_TESTING_DATA_INDEX_DIAGONAL_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index,shape_diagonal)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int src_shape[2] = {2,2};
        inline int offset = 0;
        inline int axis1 = 0;
        inline int axis2 = 1;
        
        inline auto src_shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto offset_ct = 0_ct;
        inline auto axis1_ct = 0_ct;
        inline auto axis2_ct = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int src_shape[2] = {2,3};
        inline int offset = 0;
        inline int axis1 = 0;
        inline int axis2 = 1;

        inline auto src_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto offset_ct = 0_ct;
        inline auto axis1_ct = 0_ct;
        inline auto axis2_ct = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int src_shape[2] = {2,2};
        inline int offset = 0;
        inline int axis1 = 0;
        inline int axis2 = 1;

        inline auto src_shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto offset_ct = 0_ct;
        inline auto axis1_ct = 0_ct;
        inline auto axis2_ct = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1d)
    {
        inline int src_shape[2] = {2,2};
        inline int offset = 1;
        inline int axis1  = 0;
        inline int axis2  = 1;

        inline auto src_shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto offset_ct = 1_ct;
        inline auto axis1_ct  = 0_ct;
        inline auto axis2_ct  = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1d)
    {
        inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int src_shape[3] = {2,3,2};
        inline int offset = 0;
        inline int axis1 = 0;
        inline int axis2 = 1;

        inline auto src_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto offset_ct = 0_ct;
        inline auto axis1_ct = 0_ct;
        inline auto axis2_ct = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int src_shape[3] = {2,3,2};
        inline int offset = 0;
        inline int axis1 = 1;
        inline int axis2 = 2;

        inline auto src_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto offset_ct = 0_ct;
        inline auto axis1_ct = 1_ct;
        inline auto axis2_ct = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int src_shape[3] = {2,3,2};
        inline int offset = 0;
        inline int axis1 = 2;
        inline int axis2 = 0;

        inline auto src_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto offset_ct = 0_ct;
        inline auto axis1_ct = 2_ct;
        inline auto axis2_ct = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int src_shape[3] = {2,3,2};
        inline int offset = 0;
        inline int axis1 = -1;
        inline int axis2 = -3;

        inline auto src_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto offset_ct = 0_ct;
        inline auto axis1_ct = "-1"_ct;
        inline auto axis2_ct = "-3"_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int src_shape[3] = {2,3,4};
        inline int offset = 0;
        inline int axis1 = 0;
        inline int axis2 = 1;

        inline auto src_shape_ct = nmtools_tuple{2_ct,3_ct,4_ct};
        inline auto offset_ct = 0_ct;
        inline auto axis1_ct = 0_ct;
        inline auto axis2_ct = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int result[2] = {4,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2f)
    {
        inline int src_shape[3] = {2,3,4};
        inline int offset = 0;
        inline int axis1 = 0;
        inline int axis2 = 2;

        inline auto src_shape_ct = nmtools_tuple{2_ct,3_ct,4_ct};
        inline auto offset_ct = 0_ct;
        inline auto axis1_ct = 0_ct;
        inline auto axis2_ct = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2f)
    {
        inline int result[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int src_shape[4] = {2,1,3,5};
        inline int offset = 0;
        inline int axis1 = 0;
        inline int axis2 = 3;

        inline auto src_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct,5_ct};
        inline auto offset_ct = 0_ct;
        inline auto axis1_ct = 0_ct;
        inline auto axis2_ct = 3_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[3] = {1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int src_shape[4] = {2,1,3,5};
        inline int offset = 0;
        inline int axis1 = 1;
        inline int axis2 = 2;

        inline auto src_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct,5_ct};
        inline auto offset_ct = 0_ct;
        inline auto axis1_ct = 1_ct;
        inline auto axis2_ct = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[3] = {2,5,1};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index,diagonal)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int src_shape[2] = {2,2};
        inline int indices[1] = {0};
        inline int offset = 0;
        inline int axis1  = 0;
        inline int axis2  = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int src_shape[2] = {2,2};
        inline int indices[1] = {1};
        inline int offset = 0;
        inline int axis1  = 0;
        inline int axis2  = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int src_shape[2] = {2,2};
        inline int indices[1] = {0};
        inline int offset = 1;
        inline int axis1  = 0;
        inline int axis2  = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {0,0};
        inline int offset = 0;
        inline int axis1 = 0;
        inline int axis2 = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[3] = {0,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {0,1};
        inline int offset = 0;
        inline int axis1 = 0;
        inline int axis2 = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[3] = {1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {1,0};
        inline int offset = 0;
        inline int axis1 = 0;
        inline int axis2 = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[3] = {0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {1,1};
        inline int offset = 0;
        inline int axis1 = 0;
        inline int axis2 = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[3] = {1,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4a)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {0,0};
        inline int offset = 0;
        inline int axsi1 = 1;
        inline int axis2 = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4a)
    {
        inline int result[3] = {0,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4b)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {0,1};
        inline int offset = 0;
        inline int axis1 = 1;
        inline int axis2 = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4b)
    {
        inline int result[3] = {0,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4c)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {1,0};
        inline int offset = 0;
        inline int axis1 = 1;
        inline int axis2 = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4c)
    {
        inline int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4d)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {1,1};
        inline int offset = 0;
        inline int axis1  = 1;
        inline int axis2  = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4d)
    {
        inline int result[3] = {1,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5a)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {0,0};
        inline int offset = 0;
        inline int axis1  = 2;
        inline int axis2  = 0;
    }
    NMTOOLS_TESITNG_DECLARE_EXPECT(case5a)
    {
        inline int result[3] = {0,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5b)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {0,1};
        inline int offset = 0;
        inline int axis1  = 2;
        inline int axis2  = 0;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5b)
    {
        inline int result[3] = {1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5c)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {1,0};
        inline int offset = 0;
        inline int axis1  = 2;
        inline int axis2  = 0;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5c)
    {
        inline int result[3] = {0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5d)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {1,1};
        inline int offset = 0;
        inline int axis1 = 2;
        inline int axis2 = 0;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5d)
    {
        inline int result[3] = {1,1,1};
    }
    
    NMTOOLS_TESTING_DECLARE_ARGS(case5e)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {2,0};
        inline int offset = 0;
        inline int axis1 = 2;
        inline int axis2 = 0;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5e)
    {
        inline int result[3] = {0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5f)
    {
        inline int src_shape[3] = {2,3,2};
        inline int indices[2] = {2,1};
        inline int offset = 0;
        inline int axis1 = 2;
        inline int axis2 = 0;
    }
    NMTOOLS_TESITNG_DECLARE_EXPECT(case5f)
    {
        inline int result[3] = {1,2,1};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_DIAGONAL_HPP