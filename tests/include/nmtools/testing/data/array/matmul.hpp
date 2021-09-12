#ifndef NMTOOLS_TESTING_DATA_ARRAY_MATMUL_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_MATMUL_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid);

NMTOOLS_TESTING_DECLARE_CASE(array, split)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = 1;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int lhs[1] = {2};
        inline int rhs[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = 2;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int lhs[2] = {2,3};
        inline int rhs[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = -2;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int lhs[1] = {2};
        inline int rhs[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = -1;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int lhs[2] = {2,3};
        inline int rhs[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = 0;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto lhs = std::vector<int>{};
        inline int rhs[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = 3;
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int lhs[3] = {2,3,2};
        inline auto rhs = std::vector<int>{};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(array, shape_matmul)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int lshape[2] = {3,4};
        inline int rshape[2] = {4,3};
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {3,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int lshape[2] = {4,3};
        inline int rshape[2] = {3,4};
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int lshape[2] = {4,1};
        inline int rshape[2] = {1,4};
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2] = {4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int lshape[2] = {1,4};
        inline int rshape[2] = {4,1};
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int lshape[2] =   {4,3};
        inline int rshape[3] = {2,3,2};
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {2,4,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int lshape[3] = {2,3,2};
        inline int rshape[2] =   {2,4};
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3] = {2,3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int lshape[4] = {9,5,7,4};
        inline int rshape[4] = {9,5,4,3};
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[4] = {9,5,7,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int lshape[4] = {1,5,7,4};
        inline int rshape[4] = {9,1,4,3};
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[4] = {9,5,7,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int lshape[4] = {9,5,7,4};
        inline int rshape[4] = {5,9,4,3};
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto result = meta::nothing;
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, matmul)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[2] = {0,0};
        inline int  lshape[2] = {4,3};
        inline int  rshape[2] = {3,4};
        inline int   shape[2] = {4,4};
        CAST_ARRAYS(indices);
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto  left = std::tuple{0,std::tuple{None,None}};
        inline auto right = std::tuple{std::tuple{None,None},0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[2] = {3,2};
        inline int  lshape[2] = {4,3};
        inline int  rshape[2] = {3,4};
        inline int   shape[2] = {4,4};
        CAST_ARRAYS(indices);
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto  left = std::tuple{3,std::tuple{None,None}};
        inline auto right = std::tuple{std::tuple{None,None},2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int indices[3] = {0,0,0};
        inline int  lshape[3] = {1,4,3};
        inline int  rshape[2] =   {3,4};
        inline int   shape[3] = {1,4,4};
        CAST_ARRAYS(indices);
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto  left = std::tuple{0,0,std::tuple{None,None}};
        inline auto right = std::tuple{std::tuple{None,None},0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int indices[3] = {0,3,2};
        inline int  lshape[3] = {1,4,3};
        inline int  rshape[2] =   {3,4};
        inline int   shape[3] = {1,4,4};
        CAST_ARRAYS(indices);
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto  left = std::tuple{0,3,std::tuple{None,None}};
        inline auto right = std::tuple{std::tuple{None,None},2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int indices[3] = {1,1,0};
        inline int  lshape[2] =   {2,3};
        inline int  rshape[3] = {2,3,2};
        inline int   shape[3] = {2,2,2};
        CAST_ARRAYS(indices);
        CAST_ARRAYS(lshape);
        CAST_ARRAYS(rshape);
        CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto  left = std::tuple{1,std::tuple{None,None}};
        inline auto right = std::tuple{1,std::tuple{None,None},0};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(array, matmul)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int lhs[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int rhs[3][4] = {
            {0, 1, 2, 3},
            {4, 5, 6, 7},
            {8, 9,10,11},
        };
        CAST_ARRAYS(lhs);
        CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[4][4] = {
            { 20,  23,  26,  29},
            { 56,  68,  80,  92},
            { 92, 113, 134, 155},
            {128, 158, 188, 218},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int lhs[3][4] = {
            {0, 1,  2,  3},
            {4, 5,  6,  7},
            {8, 9, 10, 11},
        };
        inline int rhs[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        CAST_ARRAYS(lhs);
        CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3][3] = {
            { 42,  48,  54},
            {114, 136, 158},
            {186, 224, 262},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int lhs[1][4][3] = {
            {
                {0, 1, 2},
                {3, 4, 5},
                {6, 7, 8},
                {9,10,11},
            }
        };
        inline int rhs[3][4] = {
            {0, 1, 2, 3},
            {4, 5, 6, 7},
            {8, 9,10,11},
        };
        CAST_ARRAYS(lhs);
        CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[1][4][4] = {
            {
                { 20,  23,  26,  29},
                { 56,  68,  80,  92},
                { 92, 113, 134, 155},
                {128, 158, 188, 218},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int lhs[1][3][4] = {
            {
                {0, 1,  2,  3},
                {4, 5,  6,  7},
                {8, 9, 10, 11},
            }
        };
        inline int rhs[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        CAST_ARRAYS(lhs);
        CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[1][3][3] = {
            {
                { 42,  48,  54},
                {114, 136, 158},
                {186, 224, 262},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int lhs[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        inline int rhs[1][1][2][3] = {
            {
                {
                    {0,1,2},
                    {3,4,5},
                }
            }
        };
        CAST_ARRAYS(lhs);
        CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[1][2][3][3] = {
            {
                {
                    { 3, 4, 5},
                    { 9,14,19},
                    {15,24,33},
                },
                {
                    {21,34,47},
                    {27,44,61},
                    {33,54,75},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int lhs[3][2][1][2] = {
            {
                {{0,1}},
                {{2,3}},
            },
            {
                {{4,5}},
                {{6,7}},
            },
            {
                {{ 8, 9}},
                {{10,11}},
            },
        };
        inline int rhs[3][2][2][1] = {
            {
                {
                    {0},
                    {1},
                },
                {
                    {2},
                    {3},
                },
            },
            {
                {
                    {4},
                    {5},
                },
                {
                    {6},
                    {7},
                },
            },
            {
                {
                    {8},
                    {9},
                },
                {
                    {10},
                    {11},
                },
            },
        };
        CAST_ARRAYS(lhs);
        CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3][2][1][1] = {
            {
                {{1}},
                {{13}},
            },
            {
                {{41}},
                {{85}},
            },
            {
                {{145}},
                {{221}},
            }
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_MATMUL_HPP