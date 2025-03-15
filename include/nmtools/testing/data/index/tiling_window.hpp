#ifndef NMTOOLS_TESTING_DATA_INDEX_TILING_WINDOW_HPP
#define NMTOOLS_TESTING_DATA_INDEX_TILING_WINDOW_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index,shape_tiling_window)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int src_shape[1] = {6};
        inline int tile_shape = 3;
        
        inline auto src_shape_ct = nmtools_tuple{6_ct};
        inline auto tile_shape_ct = 3_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int dst_shape[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int dst_shape[4] = {3,2,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape[2] = {2,2};

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{2_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int dst_shape[4] = {2,2,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape = 3;
        inline int axis = 0;

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = 3_ct;
        inline auto axis_ct = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int dst_shape[3] = {1,4,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape = 2;
        inline int axis = 1;

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;
        inline auto axis_ct = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int dst_shape[3] = {3,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int dst_shape[4] = {2,2,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int src_shape[3] = {2,4,3};
        inline int tile_shape[3] = {2,2,3};

        inline auto src_shape_ct = nmtools_tuple{2_ct,4_ct,3_ct};
        inline auto tile_shape_ct = nmtools_tuple{2_ct,2_ct,3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int dst_shape[6] = {1,2,1,2,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int src_shape[3] = {2,6,4};
        inline int tile_shape[2] = {3,2};
        inline int axis[2] = {1,2};

        inline auto src_shape_ct  = nmtools_tuple{2_ct,6_ct,3_ct};
        inline auto tile_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto axis_ct = nmtools_tuple{1_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int dst_shape[5] = {2,2,2,3,2};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index,tiling_window)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1_0_0)
    {
        inline int src_shape[1] = {6};
        inline int tile_shape = 3;
        
        inline auto src_shape_ct = nmtools_tuple{6_ct};
        inline auto tile_shape_ct = 3_ct;

        inline int dst_shape[2] = {2,3};
        inline int dst_indices[2] = {0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1_0_0)
    {
        inline int src_indices[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1_0_1)
    {
        inline int src_shape[1] = {6};
        inline int tile_shape = 3;
        
        inline auto src_shape_ct = nmtools_tuple{6_ct};
        inline auto tile_shape_ct = 3_ct;

        inline int dst_shape[2] = {2,3};
        inline int dst_indices[2] = {0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1_0_1)
    {
        inline int src_indices[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1_0_2)
    {
        inline int src_shape[1] = {6};
        inline int tile_shape = 3;
        
        inline auto src_shape_ct = nmtools_tuple{6_ct};
        inline auto tile_shape_ct = 3_ct;

        inline int dst_shape[2] = {2,3};
        inline int dst_indices[2] = {0,2};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1_0_2)
    {
        inline int src_indices[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1_1_0)
    {
        inline int src_shape[1] = {6};
        inline int tile_shape = 3;
        
        inline auto src_shape_ct = nmtools_tuple{6_ct};
        inline auto tile_shape_ct = 3_ct;

        inline int dst_shape[2] = {2,3};
        inline int dst_indices[2] = {1,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1_1_0)
    {
        inline int src_indices[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1_1_1)
    {
        inline int src_shape[1] = {6};
        inline int tile_shape = 3;
        
        inline auto src_shape_ct = nmtools_tuple{6_ct};
        inline auto tile_shape_ct = 3_ct;

        inline int dst_shape[2] = {2,3};
        inline int dst_indices[2] = {1,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1_1_1)
    {
        inline int src_indices[1] = {4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1_1_2)
    {
        inline int src_shape[1] = {6};
        inline int tile_shape = 3;
        
        inline auto src_shape_ct = nmtools_tuple{6_ct};
        inline auto tile_shape_ct = 3_ct;

        inline int dst_shape[2] = {2,3};
        inline int dst_indices[2] = {1,2};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1_1_2)
    {
        inline int src_indices[1] = {5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_0_0_0_0)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[4] = {3,2,1,2};
        inline int dst_indices[4] = {0,0,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_0_0_0_0)
    {
        inline int src_indices[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_0_0_0_1)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[4] = {3,2,1,2};
        inline int dst_indices[4] = {0,0,0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_0_0_0_1)
    {
        inline int src_indices[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_0_1_0_0)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[4] = {3,2,1,2};
        inline int dst_indices[4] = {0,1,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_0_1_0_0)
    {
        inline int src_indices[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_0_1_0_1)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[4] = {3,2,1,2};
        inline int dst_indices[4] = {0,1,0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_0_1_0_1)
    {
        inline int src_indices[2] = {0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_1_0_0_0)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[4] = {3,2,1,2};
        inline int dst_indices[4] = {1,0,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_1_0_0_0)
    {
        inline int src_indices[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_1_0_0_1)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[4] = {3,2,1,2};
        inline int dst_indices[4] = {1,0,0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_1_0_0_1)
    {
        inline int src_indices[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_1_1_0_0)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[4] = {3,2,1,2};
        inline int dst_indices[4] = {1,1,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_1_1_0_0)
    {
        inline int src_indices[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_1_1_0_1)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[4] = {3,2,1,2};
        inline int dst_indices[4] = {1,1,0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_1_1_0_1)
    {
        inline int src_indices[2] = {1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_2_0_0_0)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[4] = {3,2,1,2};
        inline int dst_indices[4] = {2,0,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_2_0_0_0)
    {
        inline int src_indices[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_2_0_0_1)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[4] = {3,2,1,2};
        inline int dst_indices[4] = {2,0,0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_2_0_0_1)
    {
        inline int src_indices[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_2_1_0_0)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[4] = {3,2,1,2};
        inline int dst_indices[4] = {2,1,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_2_1_0_0)
    {
        inline int src_indices[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_2_1_0_1)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[4] = {3,2,1,2};
        inline int dst_indices[4] = {2,1,0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_2_1_0_1)
    {
        inline int src_indices[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c_0_0_0)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape = 3;
        inline int axis = 0;

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = 3_ct;
        inline auto axis_ct = 0_ct;

        inline int dst_shape[3] = {1,4,3};
        inline int dst_indices[3] = {0,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c_0_0_0)
    {
        inline int src_indices[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c_0_0_1)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape = 3;
        inline int axis = 0;

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = 3_ct;
        inline auto axis_ct = 0_ct;

        inline int dst_shape[3] = {1,4,3};
        inline int dst_indices[3] = {0,0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c_0_0_1)
    {
        inline int src_indices[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c_0_0_2)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape = 3;
        inline int axis = 0;

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = 3_ct;
        inline auto axis_ct = 0_ct;

        inline int dst_shape[3] = {1,4,3};
        inline int dst_indices[3] = {0,0,2};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c_0_0_2)
    {
        inline int src_indices[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c_0_1_0)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape = 3;
        inline int axis = 0;

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = 3_ct;
        inline auto axis_ct = 0_ct;

        inline int dst_shape[3] = {1,4,3};
        inline int dst_indices[3] = {0,1,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c_0_1_0)
    {
        inline int src_indices[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c_0_1_1)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape = 3;
        inline int axis = 0;

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = 3_ct;
        inline auto axis_ct = 0_ct;

        inline int dst_shape[3] = {1,4,3};
        inline int dst_indices[3] = {0,1,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c_0_1_1)
    {
        inline int src_indices[2] = {1,1};
    }
    
    NMTOOLS_TESTING_DECLARE_ARGS(case2c_0_1_2)
    {
        inline int src_shape[2] = {3,4};
        inline int tile_shape = 3;
        inline int axis = 0;

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto tile_shape_ct = 3_ct;
        inline auto axis_ct = 0_ct;

        inline int dst_shape[3] = {1,4,3};
        inline int dst_indices[3] = {0,1,2};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c_0_1_2)
    {
        inline int src_indices[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_0_0_0_0)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {0,0,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_0_0_0_0)
    {
        inline int src_indices[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_0_0_0_1)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {0,0,0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_0_0_0_1)
    {
        inline int src_indices[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_0_0_1_0)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {0,0,1,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_0_0_1_0)
    {
        inline int src_indices[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_0_0_1_1)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {0,0,1,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_0_0_1_1)
    {
        inline int src_indices[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_0_1_0_0)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {0,1,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_0_1_0_0)
    {
        inline int src_indices[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_0_1_0_1)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {0,1,0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_0_1_0_1)
    {
        inline int src_indices[2] = {0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_0_1_1_0)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {0,1,1,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_0_1_1_0)
    {
        inline int src_indices[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_0_1_1_1)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {0,1,1,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_0_1_1_1)
    {
        inline int src_indices[2] = {1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_1_0_0_0)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {1,0,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_1_0_0_0)
    {
        inline int src_indices[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_1_0_0_1)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {1,0,0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_1_0_0_1)
    {
        inline int src_indices[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_1_0_1_0)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {1,0,1,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_1_0_1_0)
    {
        inline int src_indices[2] = {3,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_1_0_1_1)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {1,0,1,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_1_0_1_1)
    {
        inline int src_indices[2] = {3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_1_1_0_0)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {1,1,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_1_1_0_0)
    {
        inline int src_indices[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_1_1_0_1)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {1,1,0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_1_1_0_1)
    {
        inline int src_indices[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_1_1_1_0)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {1,1,1,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_1_1_1_0)
    {
        inline int src_indices[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e_1_1_1_1)
    {
        inline int src_shape[2] = {4,4};
        inline int tile_shape = 2;

        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto tile_shape_ct = 2_ct;

        inline int dst_shape[4] = {2,2,2,2};
        inline int dst_indices[4] = {1,1,1,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e_1_1_1_1)
    {
        inline int src_indices[2] = {3,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d_0_0_0_0_0)
    {
        inline int src_shape[3] = {2,6,4};
        inline int tile_shape[2] = {3,2};
        inline int axis[2] = {1,2};

        inline auto src_shape_ct  = nmtools_tuple{2_ct,6_ct,3_ct};
        inline auto tile_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto axis_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[5] = {2,2,2,3,2};
        inline int dst_indices[5] = {0,0,0,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d_0_0_0_0_0)
    {
        inline int src_indices[3] = {0,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d_0_0_0_0_1)
    {
        inline int src_shape[3] = {2,6,4};
        inline int tile_shape[2] = {3,2};
        inline int axis[2] = {1,2};

        inline auto src_shape_ct  = nmtools_tuple{2_ct,6_ct,3_ct};
        inline auto tile_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto axis_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[5] = {2,2,2,3,2};
        inline int dst_indices[5] = {0,0,0,0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d_0_0_0_0_1)
    {
        inline int src_indices[3] = {0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d_0_0_0_1_0)
    {
        inline int src_shape[3] = {2,6,4};
        inline int tile_shape[2] = {3,2};
        inline int axis[2] = {1,2};

        inline auto src_shape_ct  = nmtools_tuple{2_ct,6_ct,3_ct};
        inline auto tile_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto axis_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[5] = {2,2,2,3,2};
        inline int dst_indices[5] = {0,0,0,1,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d_0_0_0_1_0)
    {
        inline int src_indices[3] = {0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d_0_0_0_1_1)
    {
        inline int src_shape[3] = {2,6,4};
        inline int tile_shape[2] = {3,2};
        inline int axis[2] = {1,2};

        inline auto src_shape_ct  = nmtools_tuple{2_ct,6_ct,3_ct};
        inline auto tile_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto axis_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[5] = {2,2,2,3,2};
        inline int dst_indices[5] = {0,0,0,1,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d_0_0_0_1_1)
    {
        inline int src_indices[3] = {0,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d_0_0_1_0_0)
    {
        inline int src_shape[3] = {2,6,4};
        inline int tile_shape[2] = {3,2};
        inline int axis[2] = {1,2};

        inline auto src_shape_ct  = nmtools_tuple{2_ct,6_ct,3_ct};
        inline auto tile_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto axis_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[5] = {2,2,2,3,2};
        inline int dst_indices[5] = {0,0,1,0,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d_0_0_1_0_0)
    {
        inline int src_indices[3] = {0,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d_0_0_1_0_1)
    {
        inline int src_shape[3] = {2,6,4};
        inline int tile_shape[2] = {3,2};
        inline int axis[2] = {1,2};

        inline auto src_shape_ct  = nmtools_tuple{2_ct,6_ct,3_ct};
        inline auto tile_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto axis_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[5] = {2,2,2,3,2};
        inline int dst_indices[5] = {0,0,1,0,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d_0_0_1_0_1)
    {
        inline int src_indices[3] = {0,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d_0_0_1_1_0)
    {
        inline int src_shape[3] = {2,6,4};
        inline int tile_shape[2] = {3,2};
        inline int axis[2] = {1,2};

        inline auto src_shape_ct  = nmtools_tuple{2_ct,6_ct,3_ct};
        inline auto tile_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto axis_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[5] = {2,2,2,3,2};
        inline int dst_indices[5] = {0,0,1,1,0};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d_0_0_1_1_0)
    {
        inline int src_indices[3] = {0,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d_0_0_1_1_1)
    {
        inline int src_shape[3] = {2,6,4};
        inline int tile_shape[2] = {3,2};
        inline int axis[2] = {1,2};

        inline auto src_shape_ct  = nmtools_tuple{2_ct,6_ct,3_ct};
        inline auto tile_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto axis_ct = nmtools_tuple{1_ct,2_ct};

        inline int dst_shape[5] = {2,2,2,3,2};
        inline int dst_indices[5] = {0,0,1,1,1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d_0_0_1_1_1)
    {
        inline int src_indices[3] = {0,1,3};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_TILING_WINDOW_HPP