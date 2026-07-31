#ifndef NMTOOLS_TESTING_DATA_INDEX_TILE_HPP
#define NMTOOLS_TESTING_DATA_INDEX_TILE_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(shape_tile)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[1] = {3};
        inline int reps[1] = {2};
        inline auto shape_ct = nmtools_tuple{3_ct};
        inline auto reps_ct  = nmtools_tuple{2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)

        inline auto shape_nl = nmtools_array{null_int()};
        inline auto reps_nl = nmtools_array{null_int(2)};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1] = {6};
        inline auto result_nl = nmtools_array{null_int()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[1]  = {3};
        inline int reps[2]   = {2,2};
        inline auto shape_ct = nmtools_tuple{3_ct};
        inline auto reps_ct  = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)

        inline auto shape_nl1 = nmtools_array{null_int()};
        inline auto reps_nl1  = nmtools_array{null_int(),null_int(2)};

        inline auto shape_nl2 = nmtools_array{null_int(3)};
        inline auto reps_nl2  = nmtools_array{null_int(2),null_int()};

        inline auto shape_mx1 = nmtools_tuple{3};
        inline auto reps_mx1  = nmtools_tuple{2,2_ct};

        inline auto shape_mx2 = nmtools_tuple{3_ct};
        inline auto reps_mx2  = nmtools_tuple{2_ct,2};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {2,6};
        inline auto result_nl1 = nmtools_array{null_int(),null_int()};
        inline auto result_nl2 = nmtools_array{null_int(2),null_int()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int shape[1] = {3};
        int reps[3]  = {2,1,2};
        inline auto shape_ct = nmtools_tuple{3_ct};
        inline auto reps_ct  = nmtools_tuple{2_ct,1_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)

        inline auto shape_nl1 = nmtools_array{null_int()};
        inline auto reps_nl1  = nmtools_array{null_int(),null_int(1),null_int(2)};

        inline auto shape_nl2 = nmtools_array{null_int(3)};
        inline auto reps_nl2  = nmtools_array{null_int(2),null_int(1),null_int()};

        inline auto shape_mx1 = nmtools_tuple{3};
        inline auto reps_mx1  = nmtools_tuple{2,1_ct,2_ct};

        inline auto shape_mx2 = nmtools_tuple{3_ct};
        inline auto reps_mx2  = nmtools_tuple{2_ct,1_ct,2};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {2,1,6};
        inline auto result_nl1 = nmtools_array{null_int(),null_int(1),null_int()};
        inline auto result_nl2 = nmtools_array{null_int(2),null_int(1),null_int()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int shape[1] = {3};
        int reps[2]  = {2,1};
        inline auto shape_ct = nmtools_tuple{3_ct};
        inline auto reps_ct  = nmtools_tuple{2_ct,1_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)

        inline auto shape_nl1 = nmtools_array{null_int()};
        inline auto reps_nl1  = nmtools_array{null_int(),null_int(1)};

        inline auto shape_nl2 = nmtools_array{null_int(3)};
        inline auto reps_nl2  = nmtools_array{null_int(2),null_int(1)};

        inline auto shape_mx1 = nmtools_tuple{3};
        inline auto reps_mx1  = nmtools_tuple{2,1_ct};

        inline auto shape_mx2 = nmtools_tuple{3_ct};
        inline auto reps_mx2  = nmtools_tuple{2_ct,1};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2] = {2,3};
        inline auto result_nl1 = nmtools_array{null_int(),null_int()};
        inline auto result_nl2 = nmtools_array{null_int(2),null_int(3)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int shape[3] = {2,1,4};
        int reps[2]  = {2,2};
        inline auto shape_ct = nmtools_tuple{2_ct,1_ct,4_ct};
        inline auto reps_ct  = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)

        inline auto shape_nl1 = nmtools_array{null_int(),null_int(),null_int()};
        inline auto reps_nl1  = nmtools_array{null_int(),null_int(2),null_int(2)};

        inline auto shape_nl2 = nmtools_array{null_int(2),null_int(1),null_int(4)};
        inline auto reps_nl2  = nmtools_array{null_int(2),null_int(2),null_int()};

        inline auto shape_mx1 = nmtools_tuple{2,1,4_ct};
        inline auto reps_mx1  = nmtools_tuple{2,2_ct};

        inline auto shape_mx2 = nmtools_tuple{2_ct,1_ct,4_ct};
        inline auto reps_mx2  = nmtools_tuple{2_ct,2};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {2,2,8};
        inline auto result_nl1 = nmtools_array{null_int(),null_int(),null_int()};
        inline auto result_nl2 = nmtools_array{null_int(4),null_int(2),null_int()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int8_t shape[3] = {2,1,4};
        int8_t reps[2]  = {2,2};
        inline auto shape_ct = nmtools_tuple{2_ct,1_ct,4_ct};
        inline auto reps_ct  = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)

        inline auto shape_nl1 = nmtools_array{null_int(),null_int(),null_int()};
        inline auto reps_nl1  = nmtools_array{null_int(),null_int(2),null_int(2)};

        inline auto shape_nl2 = nmtools_array{null_int(2),null_int(1),null_int(4)};
        inline auto reps_nl2  = nmtools_array{null_int(2),null_int(2),null_int()};

        inline auto shape_mx1 = nmtools_tuple{2,1,4_ct};
        inline auto reps_mx1  = nmtools_tuple{2,2_ct};

        inline auto shape_mx2 = nmtools_tuple{2_ct,1_ct,4_ct};
        inline auto reps_mx2  = nmtools_tuple{2_ct,2};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3] = {2,2,8};
        inline auto result_nl1 = nmtools_array{null_int(),null_int(),null_int()};
        inline auto result_nl2 = nmtools_array{null_int(4),null_int(2),null_int()};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(constexpr_shape_tile)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int shape[1] = {3};
        constexpr inline int reps[1] = {2};
        constexpr inline auto shape_ct = nmtools_tuple{3_ct};
        constexpr inline auto reps_ct  = nmtools_tuple{2_ct};
        constexpr inline auto shape_cl = to_clipped(shape_ct);
        constexpr inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline constexpr int result[1] = {6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int shape[1]  = {3};
        constexpr inline int reps[2]   = {2,2};
        constexpr inline auto shape_ct = nmtools_tuple{3_ct};
        constexpr inline auto reps_ct  = nmtools_tuple{2_ct,2_ct};
        constexpr inline auto shape_cl = to_clipped(shape_ct);
        constexpr inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline constexpr int result[2] = {2,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int shape[1]  = {3};
        constexpr inline int reps[3]   = {2,1,2};
        constexpr inline auto shape_ct = nmtools_tuple{3_ct};
        constexpr inline auto reps_ct  = nmtools_tuple{2_ct,1_ct,2_ct};
        constexpr inline auto shape_cl = to_clipped(shape_ct);
        constexpr inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline constexpr int result[3] = {2,1,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int shape[1] = {3};
        constexpr inline int reps[2]  = {2,1};
        constexpr inline auto shape_ct = nmtools_tuple{3_ct};
        constexpr inline auto reps_ct  = nmtools_tuple{2_ct,1_ct};
        constexpr inline auto shape_cl = to_clipped(shape_ct);
        constexpr inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline constexpr int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int shape[3]  = {2,1,4};
        constexpr inline int reps[2]   = {2,2};
        constexpr inline auto shape_ct = nmtools_tuple{2_ct,1_ct,4_ct};
        constexpr inline auto reps_ct  = nmtools_tuple{2_ct,2_ct};
        constexpr inline auto shape_cl = to_clipped(shape_ct);
        constexpr inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline constexpr int result[3] = {2,2,8};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(tile)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int shape[1] = {3};
        int reps[2]  = {2,2};
        int indices[2] = {1,5};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int shape[1] = {3};
        int reps[2]  = {2,2};
        int indices[2] = {0,4};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int shape[1] = {3};
        int reps[2]  = {2,2};
        int indices[2] = {1,3};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int shape[1] = {3};
        int reps[2]  = {2,2};
        int indices[2] = {0,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int shape[1] = {3};
        int reps[2]  = {2,2};
        int indices[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int shape[3] = {2,1,4};
        int reps[2]  = {2,2};
        int indices[3] = {0,1,7};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3] = {0,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int shape[3] = {2,1,4};
        int reps[2]  = {2,2};
        int indices[3] = {1,0,4};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        int shape[3] = {2,1,4};
        int reps[2]  = {2,2};
        int indices[3] = {0,1,3};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[3] = {0,0,3};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_TILE_HPP