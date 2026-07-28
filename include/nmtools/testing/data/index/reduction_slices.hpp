#ifndef NMTOOLS_TESTING_DATA_INDEX_REDUCTION_SLICES_HPP
#define NMTOOLS_TESTING_DATA_INDEX_REDUCTION_SLICES_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, reduction_slices)
{
    using namespace literals;

    // reduce on axis 0, keepdims=false
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[2] = {1, 0};
        inline int shape[3] = {2, 3, 2};
        inline int axis = 0;
        inline auto keepdims = False;

        inline auto indices_ct = nmtools_tuple{1_ct,0_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto axis_ct    = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline nm_size_t result[3][2] = {{0,2},{1,2},{0,1}};
    }

    // reduce on axis 1, keepdims=false
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[2] = {0, 1};
        inline int shape[3] = {2, 3, 2};
        inline int axis = 1;
        inline auto keepdims = False;

        inline auto indices_ct = nmtools_tuple{0_ct,1_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto axis_ct    = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline nm_size_t result[3][2] = {{0,1},{0,3},{1,2}};
    }

    // reduce on axis 2, keepdims=false
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int indices[2] = {0, 1};
        inline int shape[3] = {2, 3, 2};
        inline int axis = 2;
        inline auto keepdims = False;

        inline auto indices_ct = nmtools_tuple{0_ct,1_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto axis_ct    = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline nm_size_t result[3][2] = {{0,1},{1,2},{0,2}};
    }

    // reduce on axis -1, keepdims=false
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int indices[2] = {1, 0};
        inline int shape[3] = {2, 3, 2};
        inline int axis = -1;
        inline auto keepdims = False;

        inline auto indices_ct = nmtools_tuple{1_ct,0_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto axis_ct    = "-1"_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline nm_size_t result[3][2] = {{1,2},{0,1},{0,2}};
    }

    // reduce on axis -2, keepdims=false
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int indices[2] = {0, 1};
        inline int shape[3] = {2, 3, 2};
        inline int axis = -2;
        inline auto keepdims = False;

        inline auto indices_ct = nmtools_tuple{0_ct,1_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto axis_ct    = "-2"_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline nm_size_t result[3][2] = {{0,1},{0,3},{1,2}};
    }

    // reduce on axis 0, keepdims=true
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int indices[3] = {1, 0, 1};
        inline int shape[3] = {2, 3, 2};
        inline int axis = 0;
        inline auto keepdims = True;

        inline auto indices_ct = nmtools_tuple{1_ct,0_ct,1_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto axis_ct    = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline nm_size_t result[3][2] = {{0,2},{0,1},{1,2}};
    }

    // reduce on axis 1, keepdims=true
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int indices[3] = {0, 0, 1};
        inline int shape[3] = {2, 3, 2};
        inline int axis = 1;
        inline auto keepdims = True;

        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,1_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto axis_ct    = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline nm_size_t result[3][2] = {{0,1},{0,3},{1,2}};
    }

    // reduce on axis 2, keepdims=true
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int indices[3] = {1, 0, 0};
        inline int shape[3] = {2, 3, 2};
        inline int axis = 2;
        inline auto keepdims = True;

        inline auto indices_ct = nmtools_tuple{1_ct,0_ct,0_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto axis_ct    = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline nm_size_t result[3][2] = {{1,2},{0,1},{0,2}};
    }

    // reduce all axes (axis=None), keepdims=false
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline auto indices = nmtools_array<int,0>{};
        inline int shape[3] = {2, 3, 2};
        inline auto axis = None;
        inline auto keepdims = False;

        inline auto shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline nm_size_t result[3][2] = {{0,2},{0,3},{0,2}};
    }

    // reduce all axes (axis=None), keepdims=true
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int indices[3] = {0, 0, 0};
        inline int shape[3] = {2, 3, 2};
        inline auto axis = None;
        inline auto keepdims = True;

        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,0_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline nm_size_t result[3][2] = {{0,2},{0,3},{0,2}};
    }

    // reduce on multiple axes {0,2}, keepdims=false
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int indices[1] = {1};
        inline int shape[3] = {2, 3, 2};
        inline int axis[2] = {0, 2};
        inline auto keepdims = False;

        inline auto indices_ct = nmtools_tuple{1_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto axis_ct    = nmtools_tuple{0_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline nm_size_t result[3][2] = {{0,2},{1,2},{0,2}};
    }

    // reduce on multiple axes {0,2}, keepdims=true
    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int indices[3] = {0, 1, 1};
        inline int shape[3] = {2, 3, 2};
        inline int axis[2] = {0, 2};
        inline auto keepdims = True;

        inline auto indices_ct = nmtools_tuple{0_ct,1_ct,1_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto axis_ct    = nmtools_tuple{0_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline nm_size_t result[3][2] = {{0,2},{1,2},{0,2}};
    }

    // reduce on multiple axes {0,1}, keepdims=false
    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int indices[1] = {0};
        inline int shape[3] = {2, 3, 2};
        inline int axis[2] = {0, 1};
        inline auto keepdims = False;

        inline auto indices_ct = nmtools_tuple{0_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto axis_ct    = nmtools_tuple{0_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline nm_size_t result[3][2] = {{0,2},{0,3},{0,1}};
    }

    // reduce on multiple axes {1,2}, keepdims=false
    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int indices[1] = {1};
        inline int shape[3] = {2, 3, 2};
        inline int axis[2] = {1, 2};
        inline auto keepdims = False;

        inline auto indices_ct = nmtools_tuple{1_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto axis_ct    = nmtools_tuple{1_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline nm_size_t result[3][2] = {{1,2},{0,3},{0,2}};
    }

    // 2D shape, reduce on axis 0, keepdims=false
    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int indices[1] = {2};
        inline int shape[2] = {4, 3};
        inline int axis = 0;
        inline auto keepdims = False;

        inline auto indices_ct = nmtools_tuple{2_ct};
        inline auto shape_ct   = nmtools_tuple{4_ct,3_ct};
        inline auto axis_ct    = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline nm_size_t result[2][2] = {{0,4},{2,3}};
    }

    // 2D shape, reduce on axis 1, keepdims=false
    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int indices[1] = {0};
        inline int shape[2] = {4, 3};
        inline int axis = 1;
        inline auto keepdims = False;

        inline auto indices_ct = nmtools_tuple{0_ct};
        inline auto shape_ct   = nmtools_tuple{4_ct,3_ct};
        inline auto axis_ct    = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline nm_size_t result[2][2] = {{0,1},{0,3}};
    }

    // 1D shape, reduce on axis 0, keepdims=false
    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline auto indices = nmtools_array<int,0>{};
        inline int shape[1] = {5};
        inline int axis = 0;
        inline auto keepdims = False;

        inline auto shape_ct = nmtools_tuple{5_ct};
        inline auto axis_ct  = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline nm_size_t result[1][2] = {{0,5}};
    }

    // 1D shape, reduce on axis 0, keepdims=true
    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int indices[1] = {0};
        inline int shape[1] = {5};
        inline int axis = 0;
        inline auto keepdims = True;

        inline auto indices_ct = nmtools_tuple{0_ct};
        inline auto shape_ct   = nmtools_tuple{5_ct};
        inline auto axis_ct    = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline nm_size_t result[1][2] = {{0,5}};
    }

    // 4D shape, reduce on axis 1, keepdims=false
    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline int indices[3] = {0, 2, 1};
        inline int shape[4] = {2, 3, 4, 5};
        inline int axis = 1;
        inline auto keepdims = False;

        inline auto indices_ct = nmtools_tuple{0_ct,2_ct,1_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,4_ct,5_ct};
        inline auto axis_ct    = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline nm_size_t result[4][2] = {{0,1},{0,3},{2,3},{1,2}};
    }

    // 4D shape, reduce on axis 1, keepdims=true
    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        inline int indices[4] = {0, 0, 2, 1};
        inline int shape[4] = {2, 3, 4, 5};
        inline int axis = 1;
        inline auto keepdims = True;

        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,2_ct,1_ct};
        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,4_ct,5_ct};
        inline auto axis_ct    = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline nm_size_t result[4][2] = {{0,1},{0,3},{2,3},{1,2}};
    }

    // reduce on axis 0, larger index values
    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        inline int indices[2] = {3, 1};
        inline int shape[3] = {4, 5, 3};
        inline int axis = 0;
        inline auto keepdims = False;

        inline auto indices_ct = nmtools_tuple{3_ct,1_ct};
        inline auto shape_ct   = nmtools_tuple{4_ct,5_ct,3_ct};
        inline auto axis_ct    = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline nm_size_t result[3][2] = {{0,4},{3,4},{1,2}};
    }

    // reduce on axis 1, keepdims=true with larger indices
    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        inline int indices[3] = {2, 0, 1};
        inline int shape[3] = {4, 5, 3};
        inline int axis = 1;
        inline auto keepdims = True;

        inline auto indices_ct = nmtools_tuple{2_ct,0_ct,1_ct};
        inline auto shape_ct   = nmtools_tuple{4_ct,5_ct,3_ct};
        inline auto axis_ct    = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline nm_size_t result[3][2] = {{2,3},{0,5},{1,2}};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_REDUCTION_SLICES_HPP
