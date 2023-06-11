#ifndef NMTOOLS_TESTING_DATA_INDEX_COMPUTE_INDICES_HPP
#define NMTOOLS_TESTING_DATA_INDEX_COMPUTE_INDICES_HPP

#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_ls_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_fb); \

#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/as_tuple.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
using nmtools::utils::isequal;
using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(compute_indices)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1_2d)
    {
        inline int32_t shape[2] = {3,2};
        inline int32_t offset   = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1_2d)
    {
        inline auto indices = nmtools_array{0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_2d)
    {
        inline int32_t shape[2] = {3,2};
        inline int32_t offset   = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_2d)
    {
        inline auto indices = nmtools_array{0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3_2d)
    {
        inline int32_t shape[2] = {3,2};
        inline int32_t offset   = 2;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3_2d)
    {
        inline auto indices = nmtools_array{1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4_2d)
    {
        inline int32_t shape[2] = {3,2};
        inline int32_t offset   = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4_2d)
    {
        inline auto indices = nmtools_array{1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5_2d)
    {
        inline int32_t shape[2] = {3,2};
        inline int32_t offset   = 4;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5_2d)
    {
        inline auto indices = nmtools_array{2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6_2d)
    {
        inline int32_t shape[2] = {3,2};
        inline int32_t offset   = 5;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6_2d)
    {
        inline auto indices = nmtools_array{2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1_3d)
    {
        inline auto indices = nmtools_array{0,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2_3d)
    {
        inline auto indices = nmtools_array{0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 2;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3_3d)
    {
        inline auto indices = nmtools_array{0,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4_3d)
    {
        inline auto indices = nmtools_array{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 4;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5_3d)
    {
        inline auto indices = nmtools_array{0,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 5;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6_3d)
    {
        inline auto indices = nmtools_array{0,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 6;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7_3d)
    {
        inline auto indices = nmtools_array{1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 7;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8_3d)
    {
        inline auto indices = nmtools_array{1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 8;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9_3d)
    {
        inline auto indices = nmtools_array{1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 9;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10_3d)
    {
        inline auto indices = nmtools_array{1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 10;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11_3d)
    {
        inline auto indices = nmtools_array{1,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 11;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12_3d)
    {
        inline auto indices = nmtools_array{1,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 12;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13_3d)
    {
        inline auto indices = nmtools_array{2,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 13;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14_3d)
    {
        inline auto indices = nmtools_array{2,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 14;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15_3d)
    {
        inline auto indices = nmtools_array{2,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 15;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16_3d)
    {
        inline auto indices = nmtools_array{2,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 16;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17_3d)
    {
        inline auto indices = nmtools_array{2,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18_3d)
    {
        inline int32_t shape[3] = {3,2,3};
        inline int32_t offset   = 17;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18_3d)
    {
        inline auto indices = nmtools_array{2,1,2};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_COMPUTE_INDICES_HPP