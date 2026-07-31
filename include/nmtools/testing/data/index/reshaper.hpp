#ifndef NMTOOLS_TESTING_DATA_INDEX_RESHAPER_HPP
#define NMTOOLS_TESTING_DATA_INDEX_RESHAPER_HPP

#include "nmtools/testing/testing.hpp"

namespace nm = nmtools;
using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(reshaper)
{
    // case1: reshape (2,3) -> (3,2), numel=6
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int src_shape[2] = {2,3};
        inline int dst_shape[2] = {3,2};
        inline int src_size     = 6;
        inline auto src_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto dst_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto src_size_ct  = 6_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)

        inline int idx00[2] = {0,0};
        inline int idx01[2] = {0,1};
        inline int idx10[2] = {1,0};
        inline int idx11[2] = {1,1};
        inline int idx20[2] = {2,0};
        inline int idx21[2] = {2,1};

        inline auto idx00_ct = nmtools_tuple{0_ct,0_ct};
        inline auto idx01_ct = nmtools_tuple{0_ct,1_ct};
        inline auto idx10_ct = nmtools_tuple{1_ct,0_ct};
        inline auto idx11_ct = nmtools_tuple{1_ct,1_ct};
        inline auto idx20_ct = nmtools_tuple{2_ct,0_ct};
        inline auto idx21_ct = nmtools_tuple{2_ct,1_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int res00[2] = {0,0};
        inline int res01[2] = {0,1};
        inline int res10[2] = {0,2};
        inline int res11[2] = {1,0};
        inline int res20[2] = {1,1};
        inline int res21[2] = {1,2};
    }

    // case2: reshape (6,) -> (2,3), numel=6
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int src_shape[1] = {6};
        inline int dst_shape[2] = {2,3};
        inline int src_size     = 6;
        inline auto src_shape_ct = nmtools_tuple{6_ct};
        inline auto dst_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto src_size_ct  = 6_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)

        inline int idx00[2] = {0,0};
        inline int idx01[2] = {0,1};
        inline int idx02[2] = {0,2};
        inline int idx10[2] = {1,0};
        inline int idx11[2] = {1,1};
        inline int idx12[2] = {1,2};

        inline auto idx00_ct = nmtools_tuple{0_ct,0_ct};
        inline auto idx01_ct = nmtools_tuple{0_ct,1_ct};
        inline auto idx02_ct = nmtools_tuple{0_ct,2_ct};
        inline auto idx10_ct = nmtools_tuple{1_ct,0_ct};
        inline auto idx11_ct = nmtools_tuple{1_ct,1_ct};
        inline auto idx12_ct = nmtools_tuple{1_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int res00[1] = {0};
        inline int res01[1] = {1};
        inline int res02[1] = {2};
        inline int res10[1] = {3};
        inline int res11[1] = {4};
        inline int res12[1] = {5};
    }

    // case3: reshape (2,3,4) -> (4,6), numel=24
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int src_shape[3] = {2,3,4};
        inline int dst_shape[2] = {4,6};
        inline int src_size     = 24;
        inline auto src_shape_ct = nmtools_tuple{2_ct,3_ct,4_ct};
        inline auto dst_shape_ct = nmtools_tuple{4_ct,6_ct};
        inline auto src_size_ct  = 24_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)

        inline int idx00[2] = {0,0};
        inline int idx01[2] = {0,1};
        inline int idx05[2] = {0,5};
        inline int idx10[2] = {1,0};
        inline int idx15[2] = {1,5};
        inline int idx35[2] = {3,5};

        inline auto idx00_ct = nmtools_tuple{0_ct,0_ct};
        inline auto idx01_ct = nmtools_tuple{0_ct,1_ct};
        inline auto idx05_ct = nmtools_tuple{0_ct,5_ct};
        inline auto idx10_ct = nmtools_tuple{1_ct,0_ct};
        inline auto idx15_ct = nmtools_tuple{1_ct,5_ct};
        inline auto idx35_ct = nmtools_tuple{3_ct,5_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int res00[3] = {0,0,0};
        inline int res01[3] = {0,0,1};
        inline int res05[3] = {0,1,1};
        inline int res10[3] = {0,1,2};
        inline int res15[3] = {0,2,3};
        inline int res35[3] = {1,2,3};
    }

    // case4: reshape (2,3) -> (6,), numel=6
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int src_shape[2] = {2,3};
        inline int dst_shape[1] = {6};
        inline int src_size     = 6;
        inline auto src_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto dst_shape_ct = nmtools_tuple{6_ct};
        inline auto src_size_ct  = 6_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)

        inline int idx0[1] = {0};
        inline int idx1[1] = {1};
        inline int idx2[1] = {2};
        inline int idx3[1] = {3};
        inline int idx4[1] = {4};
        inline int idx5[1] = {5};

        inline auto idx0_ct = nmtools_tuple{0_ct};
        inline auto idx1_ct = nmtools_tuple{1_ct};
        inline auto idx2_ct = nmtools_tuple{2_ct};
        inline auto idx3_ct = nmtools_tuple{3_ct};
        inline auto idx4_ct = nmtools_tuple{4_ct};
        inline auto idx5_ct = nmtools_tuple{5_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int res0[2] = {0,0};
        inline int res1[2] = {0,1};
        inline int res2[2] = {0,2};
        inline int res3[2] = {1,0};
        inline int res4[2] = {1,1};
        inline int res5[2] = {1,2};
    }

    // case5: reshape (4,3) -> (3,4), numel=12
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int src_shape[2] = {4,3};
        inline int dst_shape[2] = {3,4};
        inline int src_size     = 12;
        inline auto src_shape_ct = nmtools_tuple{4_ct,3_ct};
        inline auto dst_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto src_size_ct  = 12_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)

        inline int idx00[2] = {0,0};
        inline int idx01[2] = {0,1};
        inline int idx03[2] = {0,3};
        inline int idx10[2] = {1,0};
        inline int idx20[2] = {2,0};
        inline int idx23[2] = {2,3};

        inline auto idx00_ct = nmtools_tuple{0_ct,0_ct};
        inline auto idx01_ct = nmtools_tuple{0_ct,1_ct};
        inline auto idx03_ct = nmtools_tuple{0_ct,3_ct};
        inline auto idx10_ct = nmtools_tuple{1_ct,0_ct};
        inline auto idx20_ct = nmtools_tuple{2_ct,0_ct};
        inline auto idx23_ct = nmtools_tuple{2_ct,3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int res00[2] = {0,0};
        inline int res01[2] = {0,1};
        inline int res03[2] = {1,0};
        inline int res10[2] = {1,1};
        inline int res20[2] = {2,2};
        inline int res23[2] = {3,2};
    }

    // case6: reshape (1,6) -> (6,), numel=6
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int src_shape[2] = {1,6};
        inline int dst_shape[1] = {6};
        inline int src_size     = 6;
        inline auto src_shape_ct = nmtools_tuple{1_ct,6_ct};
        inline auto dst_shape_ct = nmtools_tuple{6_ct};
        inline auto src_size_ct  = 6_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)

        inline int idx0[1] = {0};
        inline int idx1[1] = {1};
        inline int idx2[1] = {2};
        inline int idx3[1] = {3};
        inline int idx4[1] = {4};
        inline int idx5[1] = {5};

        inline auto idx0_ct = nmtools_tuple{0_ct};
        inline auto idx1_ct = nmtools_tuple{1_ct};
        inline auto idx2_ct = nmtools_tuple{2_ct};
        inline auto idx3_ct = nmtools_tuple{3_ct};
        inline auto idx4_ct = nmtools_tuple{4_ct};
        inline auto idx5_ct = nmtools_tuple{5_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int res0[2] = {0,0};
        inline int res1[2] = {0,1};
        inline int res2[2] = {0,2};
        inline int res3[2] = {0,3};
        inline int res4[2] = {0,4};
        inline int res5[2] = {0,5};
    }

    // case7: reshape (2,6) -> (2,2,3), numel=12
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int src_shape[2] = {2,6};
        inline int dst_shape[3] = {2,2,3};
        inline int src_size     = 12;
        inline auto src_shape_ct = nmtools_tuple{2_ct,6_ct};
        inline auto dst_shape_ct = nmtools_tuple{2_ct,2_ct,3_ct};
        inline auto src_size_ct  = 12_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)

        inline int idx000[3] = {0,0,0};
        inline int idx001[3] = {0,0,1};
        inline int idx012[3] = {0,1,2};
        inline int idx100[3] = {1,0,0};
        inline int idx110[3] = {1,1,0};
        inline int idx112[3] = {1,1,2};

        inline auto idx000_ct = nmtools_tuple{0_ct,0_ct,0_ct};
        inline auto idx001_ct = nmtools_tuple{0_ct,0_ct,1_ct};
        inline auto idx012_ct = nmtools_tuple{0_ct,1_ct,2_ct};
        inline auto idx100_ct = nmtools_tuple{1_ct,0_ct,0_ct};
        inline auto idx110_ct = nmtools_tuple{1_ct,1_ct,0_ct};
        inline auto idx112_ct = nmtools_tuple{1_ct,1_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int res000[2] = {0,0};
        inline int res001[2] = {0,1};
        inline int res012[2] = {0,5};
        inline int res100[2] = {1,0};
        inline int res110[2] = {1,3};
        inline int res112[2] = {1,5};
    }

    // case8: reshape (3,4) -> (2,6), numel=12
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int src_shape[2] = {3,4};
        inline int dst_shape[2] = {2,6};
        inline int src_size     = 12;
        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto dst_shape_ct = nmtools_tuple{2_ct,6_ct};
        inline auto src_size_ct  = 12_ct;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape)

        inline int idx00[2] = {0,0};
        inline int idx03[2] = {0,3};
        inline int idx05[2] = {0,5};
        inline int idx10[2] = {1,0};
        inline int idx13[2] = {1,3};
        inline int idx15[2] = {1,5};

        inline auto idx00_ct = nmtools_tuple{0_ct,0_ct};
        inline auto idx03_ct = nmtools_tuple{0_ct,3_ct};
        inline auto idx05_ct = nmtools_tuple{0_ct,5_ct};
        inline auto idx10_ct = nmtools_tuple{1_ct,0_ct};
        inline auto idx13_ct = nmtools_tuple{1_ct,3_ct};
        inline auto idx15_ct = nmtools_tuple{1_ct,5_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int res00[2] = {0,0};
        inline int res03[2] = {0,3};
        inline int res05[2] = {1,1};
        inline int res10[2] = {1,2};
        inline int res13[2] = {2,1};
        inline int res15[2] = {2,3};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_RESHAPER_HPP
