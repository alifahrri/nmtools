#ifndef NMTOOLS_TESTING_DATA_INDEX_DOT_HPP
#define NMTOOLS_TESTING_DATA_INDEX_DOT_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index,dot_lhs_tile)
{
    using namespace literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int lhs_shape[1] = {6};
        inline int rhs_shape[1] = {6};

        inline auto lhs_shape_ct = nmtools_tuple{6_ct};
        inline auto rhs_shape_ct = nmtools_tuple{6_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[2] = {3,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[1] = {3};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[2] = {3,4};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,4_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[2] = {1,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[3] = {2,3,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[2] = {1,2};
    }
    
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[3] = {3,2,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,2_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {1,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[2] = {2,3};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[3] = {1,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[1] = {2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[3] = {1,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[4] = {2,4,2,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,4_ct,2_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[3] = {1,1,2};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index,dot_lhs_reshape)
{
    using namespace literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int lhs_shape[1] = {6};
        inline int rhs_shape[1] = {6};

        inline auto lhs_shape_ct = nmtools_tuple{6_ct};
        inline auto rhs_shape_ct = nmtools_tuple{6_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1] = {6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[2] = {3,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3] = {2,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[1] = {3};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[2] = {3,4};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,4_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[3] = {2,4,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[3] = {2,3,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[4] = {2,1,2,3};
    }
    
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[3] = {3,2,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,2_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[5] = {2,3,1,2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[2] = {2,3};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[4] = {2,3,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[1] = {2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[4] = {2,4,2,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,4_ct,2_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[6] = {2,3,1,1,2,2};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index,dot_rhs_transpose)
{
    using namespace literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int lhs_shape[1] = {6};
        inline int rhs_shape[1] = {6};

        inline auto lhs_shape_ct = nmtools_tuple{6_ct};
        inline auto rhs_shape_ct = nmtools_tuple{6_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[2] = {3,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[1] = {3};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[2] = {3,4};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,4_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[3] = {2,3,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[3] = {0,2,1};
    }
    
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[3] = {3,2,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,2_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {0,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[2] = {2,3};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[1] = {2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[4] = {2,4,2,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,4_ct,2_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[4] = {0,1,3,2};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_DOT_HPP