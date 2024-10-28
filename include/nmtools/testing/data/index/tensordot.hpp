#ifndef NMTOOLS_TESTING_DATA_INDEX_TENSORDOT_HPP
#define NMTOOLS_TESTING_DATA_INDEX_TENSORDOT_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index,tensordot_lhs_transpose)
{
    using namespace literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int dim  = 1;
        inline int axes = 1;

        inline auto dim_ct  = 1_ct;
        inline auto axes_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int dim  = 2;
        inline int axes = 2;

        inline auto dim_ct  = 2_ct;
        inline auto axes_ct = 2_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int dim = 2;
        inline int axes = 2;

        inline auto dim_ct = 2_ct;
        inline auto axes_ct = 2_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int dim = 2;
        inline int axes[2] = {0,1};

        inline auto dim_ct = 2_ct;
        inline auto axes_ct = nmtools_tuple{0_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2h)
    {
        inline int dim = 2;
        inline int axes[2] = {1,0};

        inline auto dim_ct = 2_ct;
        inline auto axes_ct = nmtools_tuple{1_ct,0_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2h)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int dim = 3;
        inline int axes = 2;

        inline auto dim_ct = 3_ct;
        inline auto axes_ct = 2_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[3] = {0,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int dim = 3;
        inline int axes[2] = {0,1};

        inline auto dim_ct = 3_ct;
        inline auto axes_ct = nmtools_tuple{0_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[3] = {2,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int dim = 3;
        inline int axes[1] = {0};

        inline auto dim_ct = 3_ct;
        inline auto axes_ct = nmtools_tuple{0_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[3] = {1,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3e)
    {
        inline int dim = 3;
        inline int axes = 3;

        inline auto dim_ct = 3_ct;
        inline auto axes_ct = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3e)
    {
        inline int result[3] = {0,1,2};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index,tensordot_rhs_transpose)
{
    using namespace literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int dim = 1;
        inline int axes[1] = {0};

        inline auto dim_ct = 1_ct;
        inline auto axes_ct = nmtools_tuple{0_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int dim = 2;
        inline int axes[2] = {0,1};

        inline auto dim_ct = 2_ct;
        inline auto axes_ct = nmtools_tuple{0_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int dim = 3;
        inline int axes[2] = {0,1};

        inline auto dim_ct = 3_ct;
        inline auto axes_ct = nmtools_tuple{0_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[3] = {2,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int dim = 4;
        inline int axes[2] = {0,1};

        inline auto dim_ct = 4_ct;
        inline auto axes_ct = nmtools_tuple{0_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[4] = {2,3,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int dim = 3;
        inline int axes[2] = {1,2};

        inline auto dim_ct = 3_ct;
        inline auto axes_ct = nmtools_tuple{1_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int result[3] = {0,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2g)
    {
        inline int dim = 3;
        inline int axes[2] = {1,0};
        
        inline auto dim_ct = 3_ct;
        inline auto axes_ct = nmtools_tuple{1_ct,0_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2g)
    {
        inline int result[3] = {2,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2i)
    {
        inline int dim = 3;
        inline int axes[2] = {2,1};

        inline auto dim_ct = 3_ct;
        inline auto axes_ct = nmtools_tuple{2_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2i)
    {
        inline int result[3] = {0,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2j)
    {
        inline int dim = 2;
        inline int axes[1] = {1};

        inline auto dim_ct = 2_ct;
        inline auto axes_ct = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2j)
    {
        inline int result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int dim = 2;
        inline int axes[2] = {0,1};

        inline auto dim_ct = 2_ct;
        inline auto axes_ct = nmtools_tuple{0_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int dim = 3;
        inline int axes[2] = {2,1};

        inline auto dim_ct  = 3_ct;
        inline auto axes_ct = nmtools_tuple{2_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[3] = {0,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int dim = 3;
        inline int axes[1] = {2};

        inline auto dim_ct = 3_ct;
        inline auto axes_ct = nmtools_tuple{2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[3] = {0,1,2};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index,tensordot_lhs_reshape)
{
    using namespace literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int lhs_shape[1] = {6};
        inline int rhs_shape[1] = {6};
        inline int lhs_axes[1]  = {-1};

        inline auto lhs_shape_ct = nmtools_tuple{6_ct};
        inline auto rhs_shape_ct = nmtools_tuple{6_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result[1] = {6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int lhs_shape[2] = {3,2};
        inline int rhs_shape[2] = {3,2};
        inline int lhs_axes[2]  = {-1,-2};

        inline auto lhs_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct,"-2"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int lhs_shape[2] = {3,2};
        inline int rhs_shape[3] = {3,2,1};
        inline int lhs_axes[2]  = {-1,-2};

        inline auto lhs_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,2_ct,1_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct,"-2"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[3] = {1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int lhs_shape[2] = {3,2};
        inline int rhs_shape[3] = {3,2,2};
        inline int lhs_axes[2]  = {-1,-2};

        inline auto lhs_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,2_ct,2_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct,"-2"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[3] = {1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int lhs_shape[2] = {3,2};
        inline int rhs_shape[4] = {3,2,1,2};
        inline int lhs_axes[2]  = {-1,-2};

        inline auto lhs_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,2_ct,1_ct,2_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct,"-2"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[4] = {1,1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int lhs_shape[2] = {3,2};
        inline int rhs_shape[3] = {1,3,2};
        inline int lhs_axes[2]  = {-1,-2};

        inline auto lhs_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{1_ct,3_ct,2_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct,"-2"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int result[3] = {1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2f)
    {
        inline int lhs_shape[2] = {3,2};
        inline int rhs_shape[3] = {2,3,2};
        inline int lhs_axes[2]  = {-1,-2};

        inline auto lhs_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct,"-2"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2f)
    {
        inline int result[3] = {1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2h)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[3] = {2,3,2};
        inline int lhs_axes[2]  = {-1,-2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct,"-2"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2h)
    {
        inline int result[3] = {1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2j)
    {
        inline int lhs_shape[2] = {2,3};
        inline int rhs_shape[2] = {2,3};
        inline int lhs_axes[1]  = {-1};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2j)
    {
        inline int result[3] = {2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int lhs_shape[3] = {2,3,2};
        inline int rhs_shape[2] = {3,2};
        inline int lhs_axes[2]  = {-1,-2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct,"-2"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int lhs_shape[3] = {2,2,3};
        inline int rhs_shape[2] = {2,3};
        inline int lhs_axes[2]  = {-1,-2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct,"-2"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[3] = {2,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int lhs_shape[3] = {2,2,3};
        inline int rhs_shape[3] = {1,3,2};
        inline int lhs_axes[2]  = {-1,-2};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,2_ct,3_ct};
        inline auto rhs_shape_ct = nmtools_tuple{1_ct,3_ct,2_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct,"-2"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[4] = {2,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int lhs_shape[3] = {3,2,2};
        inline int rhs_shape[3] = {1,3,2};
        inline int lhs_axes[1]  = {-1};

        inline auto lhs_shape_ct = nmtools_tuple{3_ct,2_ct,2_ct};
        inline auto rhs_shape_ct = nmtools_tuple{1_ct,3_ct,2_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[5] = {3,2,1,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3e)
    {
        inline int lhs_shape[3] = {2,3,1};
        inline int rhs_shape[3] = {2,3,1};
        inline int lhs_axes[3]  = {-1,-2,-3};

        inline auto lhs_shape_ct = nmtools_tuple{2_ct,3_ct,1_ct};
        inline auto rhs_shape_ct = nmtools_tuple{2_ct,3_ct,1_ct};
        inline auto lhs_axes_ct  = nmtools_tuple{"-1"_ct,"-2"_ct,"-3"_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3e)
    {
        inline int result[3] = {2,3,1};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_TENSORDOT_HPP