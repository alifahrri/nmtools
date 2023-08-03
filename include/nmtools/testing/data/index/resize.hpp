#ifndef NMTOOLS_TESTING_DATA_INDEX_RESIZE_HPP
#define NMTOOLS_TESTING_DATA_INDEX_RESIZE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index,shape_resize)
{
    using namespace literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto dst_shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto dst_shape_cl = to_clipped(dst_shape_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline uint32_t expected[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {2,3};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto dst_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto dst_shape_cl = to_clipped(dst_shape_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline uint32_t expected[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto dst_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto dst_shape_cl = to_clipped(dst_shape_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline uint32_t expected[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {3,3};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto dst_shape_ct = nmtools_tuple{3_ct,3_ct};
        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto dst_shape_cl = to_clipped(dst_shape_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline uint32_t expected[2] = {3,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {4,2};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto dst_shape_ct = nmtools_tuple{4_ct,2_ct};
        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto dst_shape_cl = to_clipped(dst_shape_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline uint32_t expected[2] = {4,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {8,4};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        inline auto src_shape_ct = nmtools_tuple{4_ct,4_ct};
        inline auto dst_shape_ct = nmtools_tuple{8_ct,4_ct};
        inline auto src_shape_cl = to_clipped(src_shape_ct);
        inline auto dst_shape_cl = to_clipped(dst_shape_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline uint32_t expected[2] = {8,4};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index,resize)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {2,2};
        inline uint32_t indices[2]   = {0,0};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline uint32_t expected[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {2,2};
        inline uint32_t indices[2]   = {0,1};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline uint32_t expected[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {2,2};
        inline uint32_t indices[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline uint32_t expected[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {2,3};
        inline uint32_t indices[2]   = {0,1};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline uint32_t expected[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {2,3};
        inline uint32_t indices[2]   = {0,2};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline uint32_t expected[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {2,3};
        inline uint32_t indices[2]   = {1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline uint32_t expected[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {3,2};
        inline uint32_t indices[2]   = {0,1};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline uint32_t expected[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {3,2};
        inline uint32_t indices[2]   = {1,0};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline uint32_t expected[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {3,2};
        inline uint32_t indices[2]   = {2,0};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline uint32_t expected[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {3,3};
        inline uint32_t indices[2]   = {1,0};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline uint32_t expected[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {3,3};
        inline uint32_t indices[2]   = {1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline uint32_t expected[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {3,2};
        inline uint32_t indices[2]   = {2,1};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline uint32_t expected[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {4,2};
        inline uint32_t indices[2]   = {2,0};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline uint32_t expected[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {4,2};
        inline uint32_t indices[2]   = {3,1};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline uint32_t expected[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {4,2};
        inline uint32_t indices[2]   = {2,1};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline uint32_t expected[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {8,4};
        inline uint32_t indices[2]   = {0,1};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline uint32_t expected[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {8,4};
        inline uint32_t indices[2]   = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline uint32_t expected[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline uint32_t src_shape[2] = {4,4};
        inline uint32_t dst_shape[2] = {8,4};
        inline uint32_t indices[2]   = {7,3};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline uint32_t expected[2] = {3,3};
    }
}

#endif //NMTOOLS_TESTING_DATA_INDEX_RESIZE_HPP