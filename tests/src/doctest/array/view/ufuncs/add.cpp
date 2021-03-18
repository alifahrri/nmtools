#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
auto name##_a = cast(name, kind::nested_arr); \
auto name##_v = cast(name, kind::nested_vec); \
auto name##_f = cast(name, kind::fixed); \
auto name##_d = cast(name, kind::dynamic); \
auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(view, add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        int b[3] = {0,1,2};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        int result[3][3] = {
            {0, 2, 4},
            {3, 5, 7},
            {6, 8,10},
        };
    }
}

#define RUN_add_impl(...) \
nm::view::add(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs add fn to callable lambda
#define RUN_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("add-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_add(case_name, ...) \
RUN_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, add, case_name); \
    using namespace args; \
    auto result = RUN_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("add(case1)" * doctest::test_suite("view::add"))
{
    ADD_SUBCASE( case1,   a,   b );
    ADD_SUBCASE( case1, a_a, b_a );
    ADD_SUBCASE( case1, a_v, b_v );
    ADD_SUBCASE( case1, a_f, b_f );
    ADD_SUBCASE( case1, a_d, b_d );
    ADD_SUBCASE( case1, a_h, b_h );
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis = 0;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,2};
        int result[3][2] = {
            { 6, 8},
            {10,12},
            {14,16},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis = 1;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape[2] = {2,2};
        int result[2][2] = {
            { 6, 9},
            {24,27},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis = 2;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape[2] = {2,3};
        int result[2][3] = {
            { 1,  5,  9},
            {13, 17, 21}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis[2] = {0,1};
        CAST_ARRAYS(a)
        CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[1]  = {2};
        int result[2] = {30,36};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis[2] = {0,2};
        CAST_ARRAYS(a)
        CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int shape[1]  = {3};
        int result[3] = {14,22,30};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis[2] = {1,2};
        CAST_ARRAYS(a)
        CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int shape[1]  = {2};
        int result[2] = {15,51};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        uint8_t a[2][3][2] = {
            {
                {255, 1},
                {  2, 3},
                {  4, 5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis = 0;
        // must provide dtype for correct result
        auto dtype = int16;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int shape[2] = {3,2};
        int result[3][2] = {
            {261, 8},
            { 10,12},
            { 14,16},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        uint8_t a[2][3][2] = {
            {
                {  0, 1},
                {  2, 3},
                {  4, 5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis = 2;
        // must provide dtype for correct result
        auto dtype = int16;
        auto initial = 255;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int shape[2] = {2,3};
        int result[2][3] = {
            {256,260,264},
            {268,272,276},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis = 0;
        auto dtype = None;
        auto initial = None;
        auto keepdims = True;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int shape[3] = {1,3,2};
        int result[1][3][2] = {
            {
                { 6, 8},
                {10,12},
                {14,16},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis = 1;
        auto dtype = None;
        auto initial = None;
        auto keepdims = False;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        int shape[2] = {2,2};
        int result[2][2] = {
            { 6, 9},
            {24,27},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        auto dtype = None;
        auto initial = None;
        auto keepdims = true;
        int axis = 2;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        int shape[3] = {2,3,1};
        int result[2][3][1] = {
            {
                {1},
                {5},
                {9}
            },
            {
                {13},
                {17},
                {21}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis[2] = {0,1};
        auto dtype = None;
        auto initial = None;
        auto keepdims = false;
        CAST_ARRAYS(a)
        CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        int shape[1]  = {2};
        int result[2] = {30,36};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis[2] = {0,2};
        auto dtype = None;
        auto initial = None;
        auto keepdims = true;
        CAST_ARRAYS(a)
        CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        int shape[3]  = {1,3,1};
        int result[1][3][1] = {
            {
                {14},
                {22},
                {30},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis[2] = {1,2};
        auto dtype = None;
        auto initial = None;
        auto keepdims = false;
        CAST_ARRAYS(a)
        CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        int shape[1]  = {2};
        int result[2] = {15,51};
    }
}

#define RUN_reduce_add_impl(...) \
nm::view::reduce_add(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_add fn to callable lambda
#define RUN_reduce_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_add-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_add(case_name, ...) \
RUN_reduce_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_add, case_name); \
    using namespace args; \
    auto result = RUN_reduce_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_add(case1)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case1,   a, axis );
    REDUCE_ADD_SUBCASE( case1, a_a, axis );
    REDUCE_ADD_SUBCASE( case1, a_v, axis );
    REDUCE_ADD_SUBCASE( case1, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // REDUCE_ADD_SUBCASE( case1, a_d, axis );
    REDUCE_ADD_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_add(case2)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case2,   a, axis );
    REDUCE_ADD_SUBCASE( case2, a_a, axis );
    REDUCE_ADD_SUBCASE( case2, a_v, axis );
    REDUCE_ADD_SUBCASE( case2, a_f, axis );
    REDUCE_ADD_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_add(case3)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case3,   a, axis );
    REDUCE_ADD_SUBCASE( case3, a_a, axis );
    REDUCE_ADD_SUBCASE( case3, a_v, axis );
    REDUCE_ADD_SUBCASE( case3, a_f, axis );
    REDUCE_ADD_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_add(case4)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case4,   a,   axis );
    REDUCE_ADD_SUBCASE( case4, a_a, axis_a );
    REDUCE_ADD_SUBCASE( case4, a_v, axis_v );
    REDUCE_ADD_SUBCASE( case4, a_f, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_h, axis_h );
}

TEST_CASE("reduce_add(case5)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case5,   a,   axis );
    REDUCE_ADD_SUBCASE( case5, a_a, axis_a );
    REDUCE_ADD_SUBCASE( case5, a_v, axis_v );
    REDUCE_ADD_SUBCASE( case5, a_f, axis_f );
    REDUCE_ADD_SUBCASE( case5, a_h, axis_h );
}

TEST_CASE("reduce_add(case6)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case6,   a,   axis );
    REDUCE_ADD_SUBCASE( case6, a_a, axis_a );
    REDUCE_ADD_SUBCASE( case6, a_v, axis_v );
    REDUCE_ADD_SUBCASE( case6, a_f, axis_f );
    REDUCE_ADD_SUBCASE( case6, a_h, axis_h );
}

TEST_CASE("reduce_add(case7)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case7,   a, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_a, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_v, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_f, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_h, axis, dtype );
}

TEST_CASE("reduce_add(case8)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case8,   a, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_a, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_v, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_f, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_add(case9)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_add(case10)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_add(case11)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_add(case12)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_add(case13)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case13,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_add(case14)" * doctest::test_suite("view::reduce_add"))
{
    REDUCE_ADD_SUBCASE( case14,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_h, axis, dtype, initial, keepdims );
}

NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis = 0;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[3] = {2,3,2};
        int result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  8},
                {10, 12},
                {14, 16},
            } 
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis = 1;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape[3] = {2,3,2};
        int result[2][3][2] = {
            {
                {0,1},
                {2,4},
                {6,9},
            },
            {
                { 6,  7},
                {14, 16},
                {24, 27},
            } 
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        int axis = 2;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape[3] = {2,3,2};
        int result[2][3][2] = {
            {
                {0,1},
                {2,5},
                {4,9},
            },
            {
                { 6, 13},
                { 8, 17},
                {10, 21},
            } 
        };
    }
}

#define RUN_accumulate_add_impl(...) \
nm::view::accumulate_add(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_add fn to callable lambda
#define RUN_accumulate_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_add-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_add(case_name, ...) \
RUN_accumulate_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_add, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_add(case1)" * doctest::test_suite("view::accumulate_add"))
{
    ACCUMULATE_ADD_SUBCASE( case1,   a, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_a, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_v, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // ACCUMULATE_ADD_SUBCASE( case1, a_d, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_h, axis );
}

TEST_CASE("accumulate_add(case2)" * doctest::test_suite("view::accumulate_add"))
{
    ACCUMULATE_ADD_SUBCASE( case2,   a, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_a, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_v, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // ACCUMULATE_ADD_SUBCASE( case2, a_d, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_h, axis );
}

TEST_CASE("accumulate_add(case3)" * doctest::test_suite("view::accumulate_add"))
{
    ACCUMULATE_ADD_SUBCASE( case3,   a, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_a, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_v, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // ACCUMULATE_ADD_SUBCASE( case3, a_d, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_h, axis );
}