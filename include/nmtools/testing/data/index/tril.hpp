#ifndef NMTOOLS_TESTING_DATA_INDEX_TRIL_HPP
#define NMTOOLS_TESTING_DATA_INDEX_TRIL_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index,shape_tril)
{
    using namespace literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int src_shape[2] = {3,4};
        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int src_shape[3] = {2,3,3};
        inline auto src_shape_ct = nmtools_tuple{2_ct,3_ct,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3] = {2,3,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int src_shape[1] = {6};
        inline auto src_shape_ct = nmtools_tuple{6_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2] = {6,6};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index,tril)
{
    using namespace literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1a1)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {0,0};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a1)
    {
        inline int result[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a2)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {0,1};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a2)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a3)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {0,2};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a3)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a4)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {0,3};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a4)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a5)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {1,0};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a5)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a6)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {1,1};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a6)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a7)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {1,2};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a7)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a8)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {1,3};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a8)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a9)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {2,0};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a9)
    {
        inline int result[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a10)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {2,1};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a10)
    {
        inline int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a11)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {2,2};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a11)
    {
        inline int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a12)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {2,3};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a12)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b1)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {0,0};
        inline int k = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        
        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b1)
    {
        inline int result[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b2)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {0,1};
        inline int k = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b2)
    {
        inline int result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b3)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {0,2};
        inline int k = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b3)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b4)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {0,3};
        inline int k = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b4)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b5)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {1,0};
        inline int k = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b5)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b6)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {1,1};
        inline int k = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b6)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b7)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {1,2};
        inline int k = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b7)
    {
        inline int result[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b8)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {1,3};
        inline int k = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b8)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b9)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {2,0};
        inline int k = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b9)
    {
        inline int result[2] = {2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b10)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {2,1};
        inline int k = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b10)
    {
        inline int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b11)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {2,2};
        inline int k = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b11)
    {
        inline int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b12)
    {
        inline int src_shape[2] = {3,4};
        inline int indices[2] = {2,3};
        inline int k = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto k_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b12)
    {
        inline int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a1)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {0,0};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a1)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a2)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {0,1};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a2)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a3)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {0,2};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a3)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a4)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {1,0};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a4)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a5)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {1,1};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a5)
    {
        inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a6)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {1,2};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a6)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a7)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {2,0};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a7)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a8)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {2,1};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a8)
    {
        inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a9)
    {
        inline int src_shape[1] = {3};
        inline int indices[2] = {2,2};
        inline int k = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)

        inline auto src_shape_ct = nmtools_tuple{3_ct};
        inline auto k_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a9)
    {
        inline int result[1] = {2};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_TRIL_HPP