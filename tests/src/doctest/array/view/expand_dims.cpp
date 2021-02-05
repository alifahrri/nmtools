#include "nmtools/array/view/expand_dims.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(expand_dims)
{
    // (6) -> (1x6)
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        double array[6] = {1,2,3,4,5,6};
        int axis[1]  = {0};
        auto array_a = cast<double>(array);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
        auto array_v = cast(array,kind::nested_vec);
        auto axis_a  = cast<int>(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {1,6};
        double expected[1][6] = {{1,2,3,4,5,6}};
    }

    // (6) -> (1x6)
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        double array[6] = {1,2,3,4,5,6};
        int axis     = 0;
        auto array_a = cast<double>(array);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
        auto array_v = cast(array,kind::nested_vec);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape[2] = {1,6};
        double expected[1][6] = {{1,2,3,4,5,6}};
    }

    // (6) -> (6x1)
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        double array[6] = {1,2,3,4,5,6};
        int axis     = 1;
        auto array_a = cast<double>(array);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
        auto array_v = cast(array,kind::nested_vec);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape[2] = {6,1};
        double expected[6][1] = {{1},{2},{3},{4},{5},{6}};
    }

    // (6) -> (1x1x6)
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        double array[6] = {1,2,3,4,5,6};
        int axis[2]  = {0,1};
        auto array_a = cast<double>(array);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
        auto array_v = cast(array,kind::nested_vec);
        auto axis_a  = cast<int>(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[3] = {1,1,6};
        double expected[1][1][6] = {
            {
                {1,2,3,4,5,6}
            }
        };
    }

    // (6) -> (1x6x1)
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        double array[6] = {1,2,3,4,5,6};
        int axis[2]  = {0,2};
        auto array_a = cast<double>(array);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
        auto array_v = cast(array,kind::nested_vec);
        auto axis_a  = cast<int>(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int shape[3] = {1,6,1};
        double expected[1][6][1] = {
            {
                {1},{2},{3},{4},{5},{6}
            }
        };
    }

    // (3x2) -> (1x3x2)
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        double array[3][2] = {
            {1,2},
            {3,4},
            {5,6}
        };
        int axis = 0;
        auto array_a = cast<double>(array);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
        auto array_v = cast(array,kind::nested_vec);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int shape[3] = {1,3,2};
        double expected[1][3][2] = {
            {
                {1,2},
                {3,4},
                {5,6}
            }
        };
    }

    // (3x2) -> (3x1x2)
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        double array[3][2] = {
            {1,2},
            {3,4},
            {5,6}
        };
        int axis = 1;
        auto array_a = cast<double>(array);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
        auto array_v = cast(array,kind::nested_vec);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int shape[3] = {3,1,2};
        double expected[3][1][2] = {
            {
                {1,2},
            },
            {
                {3,4},
            },
            {
                {5,6}
            }
        };
    }

    // (3x2) -> (3x2x1)
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        double array[3][2] = {
            {1,2},
            {3,4},
            {5,6}
        };
        int axis = 2;
        auto array_a = cast<double>(array);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
        auto array_v = cast(array,kind::nested_vec);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int shape[3] = {3,2,1};
        double expected[3][2][1] = {
            {
                {1},
                {2}
            },
            {
                {3},
                {4}
            },
            {
                {5},
                {6}
            }
        };
    }

    // (3x1x2) -> (1x3x1x2)
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        double array[3][1][2] = {
            {
                {1,2},
            },
            {
                {3,4},
            },
            {
                {5,6}
            }
        };
        int axis = 0;
        auto array_a = cast<double>(array);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
        auto array_v = cast(array,kind::nested_vec);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int shape[4] = {1,3,1,2};
        double expected[1][3][1][2] = {{
            {
                {1,2},
            },
            {
                {3,4},
            },
            {
                {5,6}
            }
        }};
    }

    // (3x1x1x2) -> (1x3x1x1x2x1)
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        double array[3][1][1][2] = {
            {
                {
                    {1,2},
                }
            },
            {
                {
                    {3,4},
                }
            },
            {
                {
                    {5,6}
                }
            }
        };
        int axis[2] = {0,5};
        auto array_a = cast<double>(array);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
        auto array_v = cast(array,kind::nested_vec);
        auto axis_a  = cast<int>(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        int shape[6] = {1,3,1,1,2,1};
        double expected[1][3][1][1][2][1] = {{
            {
                {
                    {{1},{2}},
                }
            },
            {
                {
                    {{3},{4}},
                }
            },
            {
                {
                    {{5},{6}}
                }
            }
        }};
    }
}

#define EXPAND_DIMS_SUBCASE(case_name, array, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(expand_dims, case_name); \
    auto array_ref = view::expand_dims(args::array, args::axis); \
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("expand_dims(raw)" * doctest::test_suite("view::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case1, array, axis_a );
    EXPAND_DIMS_SUBCASE( case2, array, axis );
    EXPAND_DIMS_SUBCASE( case3, array, axis );
    EXPAND_DIMS_SUBCASE( case4, array, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array, axis_a );
    EXPAND_DIMS_SUBCASE( case6, array, axis );
    EXPAND_DIMS_SUBCASE( case7, array, axis );
    EXPAND_DIMS_SUBCASE( case8, array, axis );
    EXPAND_DIMS_SUBCASE( case9, array, axis );
    EXPAND_DIMS_SUBCASE( case10, array, axis_a );
}

TEST_CASE("expand_dims(array)" * doctest::test_suite("view::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case1, array_a, axis_a );
    EXPAND_DIMS_SUBCASE( case2, array_a, axis );
    EXPAND_DIMS_SUBCASE( case3, array_a, axis );
    EXPAND_DIMS_SUBCASE( case4, array_a, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_a, axis_a );
    EXPAND_DIMS_SUBCASE( case6, array_a, axis );
    EXPAND_DIMS_SUBCASE( case7, array_a, axis );
    EXPAND_DIMS_SUBCASE( case8, array_a, axis );
    EXPAND_DIMS_SUBCASE( case9, array_a, axis );
    EXPAND_DIMS_SUBCASE( case10, array_a, axis_a );
}

TEST_CASE("expand_dims(fixed_ndarray)" * doctest::test_suite("view::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case1, array_f, axis_a );
    EXPAND_DIMS_SUBCASE( case2, array_f, axis );
    EXPAND_DIMS_SUBCASE( case3, array_f, axis );
    EXPAND_DIMS_SUBCASE( case4, array_f, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_f, axis_a );
    EXPAND_DIMS_SUBCASE( case6, array_f, axis );
    EXPAND_DIMS_SUBCASE( case7, array_f, axis );
    EXPAND_DIMS_SUBCASE( case8, array_f, axis );
    EXPAND_DIMS_SUBCASE( case9, array_f, axis );
    EXPAND_DIMS_SUBCASE( case10, array_f, axis_a );
}

TEST_CASE("expand_dims(dynamic_ndarray)" * doctest::test_suite("view::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case1, array_d, axis_a );
    EXPAND_DIMS_SUBCASE( case2, array_d, axis );
    EXPAND_DIMS_SUBCASE( case3, array_d, axis );
    EXPAND_DIMS_SUBCASE( case4, array_d, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_d, axis_a );
    EXPAND_DIMS_SUBCASE( case6, array_d, axis );
    EXPAND_DIMS_SUBCASE( case7, array_d, axis );
    EXPAND_DIMS_SUBCASE( case8, array_d, axis );
    EXPAND_DIMS_SUBCASE( case9, array_d, axis );
    EXPAND_DIMS_SUBCASE( case10, array_d, axis_a );
}

TEST_CASE("expand_dims(hybrid_ndarray)" * doctest::test_suite("view::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case1, array_h, axis_a );
    EXPAND_DIMS_SUBCASE( case2, array_h, axis );
    EXPAND_DIMS_SUBCASE( case3, array_h, axis );
    EXPAND_DIMS_SUBCASE( case4, array_h, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_h, axis_a );
    EXPAND_DIMS_SUBCASE( case6, array_h, axis );
    EXPAND_DIMS_SUBCASE( case7, array_h, axis );
    EXPAND_DIMS_SUBCASE( case8, array_h, axis );
    EXPAND_DIMS_SUBCASE( case9, array_h, axis );
    EXPAND_DIMS_SUBCASE( case10, array_h, axis_a );
}

TEST_CASE("expand_dims(vector)" * doctest::test_suite("view::expand_dims"))
{
    EXPAND_DIMS_SUBCASE( case1, array_v, axis_a );
    EXPAND_DIMS_SUBCASE( case2, array_v, axis );
    EXPAND_DIMS_SUBCASE( case3, array_v, axis );
    EXPAND_DIMS_SUBCASE( case4, array_v, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_v, axis_a );
    EXPAND_DIMS_SUBCASE( case6, array_v, axis );
    EXPAND_DIMS_SUBCASE( case7, array_v, axis );
    EXPAND_DIMS_SUBCASE( case8, array_v, axis );
    EXPAND_DIMS_SUBCASE( case9, array_v, axis );
    EXPAND_DIMS_SUBCASE( case10, array_v, axis_a );
}