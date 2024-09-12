#ifndef NMTOOLS_TESTING_DATA_INDEX_HPP
#define NMTOOLS_TESTING_DATA_INDEX_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index,eye)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case4a)
    {
        // assume indexing is of <zeros(),1>
        inline int indices[2] = {0,0};
        inline int dst_shape[2] = {3,4};
        inline int k = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4a)
    {
        inline int result[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4b)
    {
        inline int indices[2] = {0,1};
        inline int dst_shape[2] = {3,4};
        inline int k = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4b)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4c)
    {
        inline int indices[2] = {0,2};
        inline int dst_shape[2] = {3,4};
        inline int k = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4c)
    {
        inline int result[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4d)
    {
        inline int indices[2] = {0,3};
        inline int dst_shape[2] = {3,4};
        inline int k = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4d)
    {
        inline int result[2] = {0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4e)
    {
        inline int indices[2] = {1,0};
        inline int dst_shape[2] = {3,4};
        inline int k = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4e)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4f)
    {
        inline int indices[2] = {1,1};
        inline int dst_shape[2] = {3,4};
        inline int k = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4f)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4g)
    {
        inline int indices[2] = {1,2};
        inline int dst_shape[2] = {3,4};
        inline int k = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4g)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4h)
    {
        inline int indices[2] = {1,3};
        inline int dst_shape[2] = {3,4};
        inline int k = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4h)
    {
        inline int result[2] = {1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4i)
    {
        inline int indices[2] = {2,0};
        inline int dst_shape[2] = {3,4};
        inline int k = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4i)
    {
        inline int result[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4j)
    {
        inline int indices[2] = {2,1};
        inline int dst_shape[2] = {3,4};
        inline int k = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4j)
    {
        inline int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4k)
    {
        inline int indices[2] = {2,2};
        inline int dst_shape[2] = {3,4};
        inline int k = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4k)
    {
        inline int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4l)
    {
        inline int indices[2] = {2,3};
        inline int dst_shape[2] = {3,4};
        inline int k = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4l)
    {
        inline auto result = meta::Nothing;
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_HPP