#include "nmtools/array/index/slice.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
auto name##_a = cast(name, kind::nested_arr); \
auto name##_v = cast(name, kind::nested_vec); \
auto name##_f = cast(name, kind::fixed); \
auto name##_d = cast(name, kind::dynamic); \
auto name##_h = cast(name, kind::hybrid); \

using std::tuple;

NMTOOLS_TESTING_DECLARE_CASE(view, slice)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[2][1][2] = {
            {{0,1}},

            {{6,7}}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{None,None};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        auto slice0 = tuple{1,2};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[1][1][2] = {{{6,7}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        auto slice0 = tuple{1,3};
        auto slice1 = tuple{0,1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[1][1][2] = {{{6,7}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{0,2};
        auto slice2 = tuple{None,-1};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int result[2][2][1] = {
            {
                {0},
                {2},
            },
            {
                {6},
                {8},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        auto slice0 = tuple{None,None};
        auto slice1 = 0;
        auto slice2 = tuple{None,-1};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int result[2][1] = {
            {0},
            {6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        auto slice0 = 1;
        auto slice1 = tuple{0,2};
        auto slice2 = tuple{None,-1};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int result[2][1] = {
            {6},
            {8},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        auto slice0 = tuple{None,None,-1};
        auto slice1 = tuple{None,None};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{None,None,-1};
        auto slice2 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        auto slice0 = tuple{None,None,-1};
        auto slice1 = tuple{None,None};
        auto slice2 = tuple{None,None,-1};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        auto slice0 = tuple{None,None,2};
        auto slice1 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        int result[2][2] = {
            {0,1},
            {4,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        auto slice0 = tuple{None,None,2};
        auto slice1 = tuple{None,2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        int result[2][2] = {
            {0,1},
            {4,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        auto slice0 = tuple{None,None,2};
        auto slice1 = tuple{1,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        int result[2][1] = {
            {1},
            {5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        auto slice0 = tuple{None,None,2};
        auto slice1 = tuple{1,None,2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        int result[2][2] = {
            {1},
            {5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        auto slice0 = tuple{None,None,-2};
        auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        int result[2][1] = {
            {7},
            {3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        auto slice0 = tuple{3,None,-2};
        auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        int result[2][1] = {
            {7},
            {3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        auto slice0 = tuple{3,None,2};
        auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        int result[1][1] = {{7}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        auto slice0 = tuple{1,None,-2};
        auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        int result[1][1] = {{3}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        auto slice0 = tuple{2,None,-2};
        auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        int result[2][1] = {
            {5},
            {1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        auto slice0 = tuple{None,None};
        auto slice1 = tuple{1,None,4};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        int result[4][1] = {
            {1},
            {3},
            {5},
            {7},
        };
    }
}

#define RUN_slice_impl(...) \
nm::view::slice(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs slice fn to callable lambda
#define RUN_slice(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("slice-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_slice_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_slice(case_name, ...) \
RUN_slice_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, slice, case_name); \
    using namespace args; \
    auto result = RUN_slice(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("slice(case1)" * doctest::test_suite("view::slice"))
{
    SLICE_SUBCASE(case1,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case2)" * doctest::test_suite("view::slice"))
{
    SLICE_SUBCASE(case2,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case3)" * doctest::test_suite("view::slice"))
{
    SLICE_SUBCASE(case3,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case4)" * doctest::test_suite("view::slice"))
{
    SLICE_SUBCASE(case4,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case5)" * doctest::test_suite("view::slice"))
{
    SLICE_SUBCASE(case5,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case6)" * doctest::test_suite("view::slice"))
{
    SLICE_SUBCASE(case6,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case7)" * doctest::test_suite("view::slice"))
{
    SLICE_SUBCASE(case7,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_v, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_h, slice0, slice1, slice2);
}