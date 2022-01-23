#ifndef NMTOOLS_TESTING_DATA_ARRAY_MATMUL_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_MATMUL_HPP

#include "nmtools/testing/array_cast.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

// split for matmul
NMTOOLS_TESTING_DECLARE_CASE(array, split)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = 1;
        NMTOOLS_CAST_ARRAYS(shape);
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
        NMTOOLS_CAST_ARRAYS(shape);
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
        NMTOOLS_CAST_ARRAYS(shape);
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
        NMTOOLS_CAST_ARRAYS(shape);
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
        NMTOOLS_CAST_ARRAYS(shape);
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
        NMTOOLS_CAST_ARRAYS(shape);
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
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {3,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int lshape[2] = {4,3};
        inline int rshape[2] = {3,4};
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int lshape[2] = {4,1};
        inline int rshape[2] = {1,4};
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2] = {4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int lshape[2] = {1,4};
        inline int rshape[2] = {4,1};
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int lshape[2] =   {4,3};
        inline int rshape[3] = {2,3,2};
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {2,4,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int lshape[3] = {2,3,2};
        inline int rshape[2] =   {2,4};
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3] = {2,3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int lshape[4] = {9,5,7,4};
        inline int rshape[4] = {9,5,4,3};
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[4] = {9,5,7,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int lshape[4] = {1,5,7,4};
        inline int rshape[4] = {9,1,4,3};
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[4] = {9,5,7,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int lshape[4] = {9,5,7,4};
        inline int rshape[4] = {5,9,4,3};
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto result = meta::nothing;
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, broadcast_matmul_indices)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[1] = {0};
        inline int   shape[3] = {1,4,3};
        inline int  bshape[1] = {1};
        NMTOOLS_CAST_ARRAYS(indices);
        NMTOOLS_CAST_ARRAYS(shape);
        NMTOOLS_CAST_ARRAYS(bshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1] = {0};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, concat_indices)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[1] = {0};
        inline auto tuple = nmtools_tuple{2,nmtools_tuple{None,None}};
        NMTOOLS_CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        using value_type = nmtools_either<int,nmtools_tuple<none_t,none_t>>;
        using result_t   = nmtools_list<value_type>;
        inline auto result = nmtools_tuple{0,2,nmtools_tuple{None,None}};
        inline auto result_list = result_t{0,2,nmtools_tuple{None,None}};
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
        NMTOOLS_CAST_ARRAYS(indices);
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
        NMTOOLS_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto  left = std::tuple{0,std::tuple{None,None}};
        inline auto right = std::tuple{std::tuple{None,None},0};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{0},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{nmtools_tuple{None,None},size_t{0}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[2] = {3,2};
        inline int  lshape[2] = {4,3};
        inline int  rshape[2] = {3,4};
        inline int   shape[2] = {4,4};
        NMTOOLS_CAST_ARRAYS(indices);
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
        NMTOOLS_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto  left = std::tuple{3,std::tuple{None,None}};
        inline auto right = std::tuple{std::tuple{None,None},2};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{3},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{nmtools_tuple{None,None},size_t{2}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int indices[3] = {0,0,0};
        inline int  lshape[3] = {1,4,3};
        inline int  rshape[2] =   {3,4};
        inline int   shape[3] = {1,4,4};
        NMTOOLS_CAST_ARRAYS(indices);
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
        NMTOOLS_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto  left = std::tuple{0,0,std::tuple{None,None}};
        inline auto right = std::tuple{std::tuple{None,None},0};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{0},size_t{0},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{nmtools_tuple{None,None},size_t{0}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int indices[3] = {0,3,2};
        inline int  lshape[3] = {1,4,3};
        inline int  rshape[2] =   {3,4};
        inline int   shape[3] = {1,4,4};
        NMTOOLS_CAST_ARRAYS(indices);
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
        NMTOOLS_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto  left = std::tuple{0,3,std::tuple{None,None}};
        inline auto right = std::tuple{std::tuple{None,None},2};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{0},size_t{3},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{nmtools_tuple{None,None},size_t{2}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int indices[3] = {1,1,0};
        inline int  lshape[2] =   {2,3};
        inline int  rshape[3] = {2,3,2};
        inline int   shape[3] = {2,2,2};
        NMTOOLS_CAST_ARRAYS(indices);
        NMTOOLS_CAST_ARRAYS(lshape);
        NMTOOLS_CAST_ARRAYS(rshape);
        NMTOOLS_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto  left = std::tuple{1,std::tuple{None,None}};
        inline auto right = std::tuple{1,std::tuple{None,None},0};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{1},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{size_t{1},nmtools_tuple{None,None},size_t{0}};
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
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
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
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
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
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
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
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
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
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
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
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
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

#endif // NMTOOLS_TESTING_DATA_ARRAY_MATMUL_HPP