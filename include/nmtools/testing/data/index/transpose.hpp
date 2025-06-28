#ifndef NMTOOLS_TESTING_DATA_INDEX_TRANSPOSE_HPP
#define NMTOOLS_TESTING_DATA_INDEX_TRANSPOSE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(index, shape_transpose)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        inline auto axes = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[2] = {2,3};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        inline auto axes = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[3] = {2,2,3};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        inline auto axes = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {3,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[4] = {2,2,1,3};
        inline int axes[4] = {1,0,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[4] = {2,2,3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[2] = {2,3};
        inline int axes[2] = {0,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[3] = {2,2,3};
        inline int axes[3] = {2,0,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3] = {3,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[3] = {2,2,3};
        inline int axes[3] = {1,2,0};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int shape[4] = {2,2,1,3};
        inline int axes[4] = {0,1,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[4] = {2,2,3,1};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_TRANSPOSE_HPP