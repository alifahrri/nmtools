#ifndef NMTOOLS_TESTING_DATA_INDEX_KRON_HPP
#define NMTOOLS_TESTING_DATA_INDEX_KRON_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index,kron_dst_transpose)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int lhs_shape[1] = {6};
        inline int rhs_shape[1] = {3};

        inline auto lhs_shape_ct = nmtools_tuple{6_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 1;
        inline int rhs_dim = 1;

        inline auto lhs_dim_ct = 1_ct;
        inline auto rhs_dim_ct = 1_ct;

        inline auto lhs_dim_cl = "1:[1]"_ct;
        inline auto rhs_dim_cl = "1:[1]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int lhs_shape[1] = {6};
        inline int rhs_shape[2] = {3,4};

        inline auto lhs_shape_ct = nmtools_tuple{6_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,4_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 1;
        inline int rhs_dim = 2;

        inline auto lhs_dim_ct = 1_ct;
        inline auto rhs_dim_ct = 2_ct;

        inline auto lhs_dim_cl = "1:[1]"_ct;
        inline auto rhs_dim_cl = "2:[2]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result[3] = {1,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int lhs_shape[1] = {6};
        inline int rhs_shape[3] = {2,3,2};

        inline auto lhs_shape_ct = nmtools_tuple{6_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 1;
        inline int rhs_dim = 3;

        inline auto lhs_dim_ct = 1_ct;
        inline auto rhs_dim_ct = 3_ct;

        inline auto lhs_dim_cl = "1:[1]"_ct;
        inline auto rhs_dim_cl = "3:[3]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result[4] = {1,2,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1d)
    {
        inline int lhs_shape[1] = {6};
        inline int rhs_shape[4] = {2,1,3,2};

        inline auto lhs_shape_ct = nmtools_tuple{6_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 1;
        inline int rhs_dim = 4;

        inline auto lhs_dim_ct = 1_ct;
        inline auto rhs_dim_ct = 4_ct;

        inline auto lhs_dim_cl = "1:[1]"_ct;
        inline auto rhs_dim_cl = "4:[4]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1d)
    {
        inline int result[5] = {1,2,3,0,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1e)
    {
        inline int lhs_shape[1] = {6};
        inline int rhs_shape[5] = {2,1,3,1,2};

        inline auto lhs_shape_ct = nmtools_tuple{6_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct,1_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 1;
        inline int rhs_dim = 5;

        inline auto lhs_dim_ct = 1_ct;
        inline auto rhs_dim_ct = 5_ct;

        inline auto lhs_dim_cl = "1:[1]"_ct;
        inline auto rhs_dim_cl = "5:[5]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1e)
    {
        inline int result[6] = {1,2,3,4,0,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[2] = {3,4};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,4_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 2;
        inline int rhs_dim = 2;

        inline auto lhs_dim_ct = 2_ct;
        inline auto rhs_dim_ct = 2_ct;

        inline auto lhs_dim_cl = "2:[2]"_ct;
        inline auto rhs_dim_cl = "2:[2]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result[4] = {0,2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int lhs_shape[2] = {3,2};
        inline int rhs_shape[2] = {2,3};

        inline auto lhs_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 2;
        inline int rhs_dim = 2;

        inline auto lhs_dim_ct = 2_ct;
        inline auto rhs_dim_ct = 2_ct;

        inline auto lhs_dim_cl = "2:[2]"_ct;
        inline auto rhs_dim_cl = "2:[2]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[4] = {0,2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int lhs_shape[2] = {3,2};
        inline int rhs_shape[1] = {6};

        inline auto lhs_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{6_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 2;
        inline int rhs_dim = 1;

        inline auto lhs_dim_ct = 2_ct;
        inline auto rhs_dim_ct = 1_ct;

        inline auto lhs_dim_cl = "2:[2]"_ct;
        inline auto rhs_dim_cl = "1:[1]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[3] = {0,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int lhs_shape[2] = {3,4};
        inline int rhs_shape[3] = {2,3,2};

        inline auto lhs_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 2;
        inline int rhs_dim = 3;

        inline auto lhs_dim_ct = 2_ct;
        inline auto rhs_dim_ct = 3_ct;

        inline auto lhs_dim_cl = "2:[2]"_ct;
        inline auto rhs_dim_cl = "3:[3]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[5] = {2,0,3,1,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int lhs_shape[2] = {3,4};
        inline int rhs_shape[4] = {2,1,3,2};

        inline auto lhs_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 2;
        inline int rhs_dim = 4;

        inline auto lhs_dim_ct = 2_ct;
        inline auto rhs_dim_ct = 4_ct;

        inline auto lhs_dim_cl = "2:[2]"_ct;
        inline auto rhs_dim_cl = "4:[4]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int result[6] = {2,3,0,4,1,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2f)
    {
        inline int lhs_shape[2] = {3,4};
        inline int rhs_shape[5] = {2,1,3,1,2};

        inline auto lhs_shape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct,1_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 2;
        inline int rhs_dim = 5;

        inline auto lhs_dim_ct = 2_ct;
        inline auto rhs_dim_ct = 5_ct;

        inline auto lhs_dim_cl = "2:[2]"_ct;
        inline auto rhs_dim_cl = "5:[5]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2f)
    {
        inline int result[7] = {2,3,4,0,5,1,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[3] = {2,3,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 3;
        inline int rhs_dim = 3;

        inline auto lhs_dim_ct = 3_ct;
        inline auto rhs_dim_ct = 3_ct;

        inline auto lhs_dim_cl = "3:[3]"_ct;
        inline auto rhs_dim_cl = "3:[3]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[6] = {0,3,1,4,2,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[3] = {2,1,3};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 3;
        inline int rhs_dim = 3;

        inline auto lhs_dim_ct = 3_ct;
        inline auto rhs_dim_ct = 3_ct;

        inline auto lhs_dim_cl = "3:[3]"_ct;
        inline auto rhs_dim_cl = "3:[3]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[6] = {0,3,1,4,2,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[2] = {3,4};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,4_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 3;
        inline int rhs_dim = 2;

        inline auto lhs_dim_ct = 3_ct;
        inline auto rhs_dim_ct = 2_ct;

        inline auto lhs_dim_cl = "3:[3]"_ct;
        inline auto rhs_dim_cl = "2:[2]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[5] = {0,1,3,2,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[1] = {6};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{6_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 3;
        inline int rhs_dim = 1;

        inline auto lhs_dim_ct = 3_ct;
        inline auto rhs_dim_ct = 1_ct;

        inline auto lhs_dim_cl = "3:[3]"_ct;
        inline auto rhs_dim_cl = "1:[1]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[4] = {0,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3e)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[4] = {2,1,3,1};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 3;
        inline int rhs_dim = 4;

        inline auto lhs_dim_ct = 3_ct;
        inline auto rhs_dim_ct = 4_ct;

        inline auto lhs_dim_cl = "3:[3]"_ct;
        inline auto rhs_dim_cl = "4:[4]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3e)
    {
        inline int result[7] = {3,0,4,1,5,2,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3f)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[5] = {2,1,2,3,1};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,1_ct,2_ct,3_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 3;
        inline int rhs_dim = 5;

        inline auto lhs_dim_ct = 3_ct;
        inline auto rhs_dim_ct = 5_ct;

        inline auto lhs_dim_cl = "3:[3]"_ct;
        inline auto rhs_dim_cl = "5:[5]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3f)
    {
        inline int result[8] = {3,4,0,5,1,6,2,7};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4a)
    {
        inline int lhs_shape[4] = {2,1,3,2};
        inline int rhs_shape[4] = {2,2,3,1};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,2_ct,3_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 4;
        inline int rhs_dim = 4;

        inline auto lhs_dim_ct = 4_ct;
        inline auto rhs_dim_ct = 4_ct;

        inline auto lhs_dim_cl = "4:[4]"_ct;
        inline auto rhs_dim_cl = "4:[4]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4a)
    {
        inline int result[8] = {0,4,1,5,2,6,3,7};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4b)
    {
        inline int lhs_shape[4] = {2,1,3,2};
        inline int rhs_shape[3] = {2,3,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 4;
        inline int rhs_dim = 3;

        inline auto lhs_dim_ct = 4_ct;
        inline auto rhs_dim_ct = 3_ct;

        inline auto lhs_dim_cl = "4:[4]"_ct;
        inline auto rhs_dim_cl = "3:[3]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4b)
    {
        inline int result[7] = {0,1,4,2,5,3,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4c)
    {
        inline int lhs_shape[4] = {2,1,3,2};
        inline int rhs_shape[2] = {3,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 4;
        inline int rhs_dim = 2;

        inline auto lhs_dim_ct = 4_ct;
        inline auto rhs_dim_ct = 2_ct;

        inline auto lhs_dim_cl = "4:[4]"_ct;
        inline auto rhs_dim_cl = "2:[2]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4c)
    {
        inline int result[6] = {0,1,2,4,3,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4d)
    {
        inline int lhs_shape[4] = {2,1,3,2};
        inline int rhs_shape[1] = {6};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{6_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 4;
        inline int rhs_dim = 1;

        inline auto lhs_dim_ct = 4_ct;
        inline auto rhs_dim_ct = 1_ct;

        inline auto lhs_dim_cl = "4:[4]"_ct;
        inline auto rhs_dim_cl = "1:[1]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4d)
    {
        inline int result[5] = {0,1,2,3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5a)
    {
        inline int lhs_shape[5] = {2,1,3,1,2};
        inline int rhs_shape[5] = {2,2,1,3,1};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct,1_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,2_ct,1_ct,3_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 5;
        inline int rhs_dim = 5;

        inline auto lhs_dim_ct = 5_ct;
        inline auto rhs_dim_ct = 5_ct;

        inline auto lhs_dim_cl = "5:[5]"_ct;
        inline auto rhs_dim_cl = "5:[5]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5a)
    {
        inline int result[10] = {0,5,1,6,2,7,3,8,4,9};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6a)
    {
        inline int lhs_shape[6] = {2,1,3,1,2,1};
        inline int rhs_shape[6] = {1,3,1,2,1,2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,1_ct,3_ct,1_ct,2_ct,1_ct};
        inline auto rhs_shape_ct = nmtools_tuple{1_ct,3_ct,1_ct,2_ct,1_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)

        inline int lhs_dim = 6;
        inline int rhs_dim = 6;

        inline auto lhs_dim_ct = 6_ct;
        inline auto rhs_dim_ct = 6_ct;

        inline auto lhs_dim_cl = "6:[6]"_ct;
        inline auto rhs_dim_cl = "6:[6]"_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6a)
    {
        inline int result[12] = {0,6,1,7,2,8,3,9,4,10,5,11};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_KRON_HPP