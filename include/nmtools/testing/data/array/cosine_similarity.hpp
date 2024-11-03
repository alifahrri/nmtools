#ifndef NMTOOLS_TESTING_DATA_ARRAY_COSINE_SIMILARITY_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_COSINE_SIMILARITY_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,cosine_similarity)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int a[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int b[3][4] = {
            {12,13,14,15},
            {16,17,18,19},
            {20,21,22,23},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline float result[3] = {0.848372,0.990665,0.997876};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int a[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int b[4] = {12,13,14,15};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline float result[3] = {0.848372,0.993056,0.999404};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int a[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int b[3][4] = {
            {12,13,14,15},
            {16,17,18,19},
            {20,21,22,23},
        };

        inline int axis = 0;
        inline int axis_ct = 0_ct;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline float result[4] = {0.885438,0.925359,0.949553,0.964747};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int b[2][3][2] = {
            {
                {12,13},
                {14,15},
                {16,17},
            },
            {
                {18,19},
                {20,21},
                {22,23},
            },
        };

        inline int axis = 0;
        inline auto axis_ct = 0_ct;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline float result[3][2] = {
            {0.832050,0.896871},
            {0.933857,0.955779},
            {0.969334,0.978056},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int b[3][2] = {
            {12,13},
            {14,15},
            {16,17},
        };

        inline int axis = 0;
        inline auto axis_ct = 0_ct;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline float result[3][2] = {
            {0.707107, 0.800000},
            {0.857493, 0.894427},
            {0.919145, 0.936329},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int b[3][2] = {
            {12,13},
            {14,15},
            {16,17},
        };

        inline int axis = 1;
        inline auto axis_ct = 1_ct;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline float result[2][2] = {
            {0.842655, 0.924893},
            {0.996369, 0.997477},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int b[3][2] = {
            {12,13},
            {14,15},
            {16,17},
        };

        inline int axis = 2;
        inline auto axis_ct = 2_ct;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline float result[2][3] = {
            {0.734803, 0.986757, 0.996773},
            {0.999323, 0.999705, 0.999851},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_COSINE_SIMILARITY_HPP