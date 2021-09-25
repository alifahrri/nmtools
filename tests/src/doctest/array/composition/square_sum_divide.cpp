#include "nmtools/array/view/ufuncs/square.hpp"
#include "nmtools/array/view/ufuncs/divide.hpp"
#include "nmtools/array/view/sum.hpp"
#include "nmtools/testing/doctest.hpp"

namespace composition
{
    namespace view = nmtools::view;

    template <typename lhs_t, typename axis_t
        , typename dtype_t=nmtools::none_t, typename keepdims_t=std::false_type>
    constexpr auto square_sum(const lhs_t& lhs, const axis_t& axis
        , const dtype_t dtype=dtype_t{}, const keepdims_t keepdims=keepdims_t{})
    {
        auto a = view::square(lhs);
        auto b = view::sum(a,axis,dtype,/*initial=*/nmtools::None,keepdims);
        return b;
    } // square_sum

    template <typename lhs_t, typename rhs_t, typename axis_t
        , typename dtype_t=nmtools::none_t, typename keepdims_t=std::false_type>
    constexpr auto square_sum_divide(const lhs_t& lhs, const rhs_t& rhs, const axis_t& axis
        , const dtype_t dtype=dtype_t{}, const keepdims_t keepdims=keepdims_t{})
    {
        auto a = view::square(lhs);
        auto b = view::sum(a,axis,dtype,/*initial=*/nmtools::None,keepdims);
        auto c = view::divide(b,rhs);
        return c;
    } // square_sum_divide
} // namespace composition

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(composition, square_sum)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[2][3][2] = {
            {
                {-5.5, -4.5},
                {-3.5, -2.5},
                {-1.5, -0.5},
            },
            {
                {0.5, 1.5},
                {2.5, 3.5},
                {4.5, 5.5},
            }
        };
        inline auto axis = None;
        inline auto dtype = None;
        inline auto keepdims = True;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[1][1][1] = {{{143.0}}};
    }
}

#define RUN_square_sum_impl(...) \
composition::square_sum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs square_sum fn to callable lambda
#define RUN_square_sum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("square_sum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_square_sum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_square_sum(case_name, ...) \
RUN_square_sum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SQUARE_SUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(composition, square_sum, case_name); \
    using namespace args; \
    auto result = RUN_square_sum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("square_sum(case1)" * doctest::test_suite("composition::square_sum"))
{
    SQUARE_SUM_SUBCASE( case1,   a, axis, dtype, keepdims );
    SQUARE_SUM_SUBCASE( case1, a_a, axis, dtype, keepdims );
    SQUARE_SUM_SUBCASE( case1, a_f, axis, dtype, keepdims );
    SQUARE_SUM_SUBCASE( case1, a_h, axis, dtype, keepdims );
    // SQUARE_SUM_SUBCASE( case1, a_d, axis, keepdims );

    {
        NMTOOLS_TESTING_DECLARE_NS(composition, square_sum, case1);
        using namespace args;

        auto view = composition::square_sum(a, axis, dtype, keepdims);
        using view_t = decltype(view);
        static_assert(  nm::meta::is_ndarray_v<view_t> );
        static_assert( !nm::meta::is_num_v<view_t> );
    }
}

NMTOOLS_TESTING_DECLARE_CASE(composition, square_sum_divide)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[2][3][2] = {
            {
                {-5.5, -4.5},
                {-3.5, -2.5},
                {-1.5, -0.5},
            },
            {
                {0.5, 1.5},
                {2.5, 3.5},
                {4.5, 5.5},
            }
        };
        inline int N = 12;
        inline auto axis = None;
        inline auto dtype = None;
        inline auto keepdims = None;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result = 11.916666666666666;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[2][3][2] = {
            {
                {-5.5, -4.5},
                {-3.5, -2.5},
                {-1.5, -0.5},
            },
            {
                {0.5, 1.5},
                {2.5, 3.5},
                {4.5, 5.5},
            }
        };
        inline int N = 12;
        inline auto axis = None;
        inline auto dtype = None;
        inline auto keepdims = True;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[1][1][1] = {
            {{11.916666666666666}}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline float a[2][3][2] = {
            {
                {-5.5, -4.5},
                {-3.5, -2.5},
                {-1.5, -0.5},
            },
            {
                {0.5, 1.5},
                {2.5, 3.5},
                {4.5, 5.5},
            }
        };
        inline int N = 12;
        inline auto axis = None;
        inline auto dtype = None;
        inline auto keepdims = False;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline float result = 11.916666666666666;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline float a[2][3][2] = {
            {
                {-5.5, -4.5},
                {-3.5, -2.5},
                {-1.5, -0.5},
            },
            {
                {0.5, 1.5},
                {2.5, 3.5},
                {4.5, 5.5},
            }
        };
        inline int N = 12;
        inline auto axis = None;
        inline auto dtype = None;
        inline auto keepdims = false;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline float result = 11.916666666666666;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline float a[2][3][2] = {
            {
                {-5.5, -4.5},
                {-3.5, -2.5},
                {-1.5, -0.5},
            },
            {
                {0.5, 1.5},
                {2.5, 3.5},
                {4.5, 5.5},
            }
        };
        inline int N = 12;
        inline auto axis = None;
        inline auto dtype = None;
        inline auto keepdims = true;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline float result[1][1][1] = {
            {{11.916666666666666}}
        };
    }
}

#define RUN_square_sum_divide_impl(...) \
composition::square_sum_divide(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs square_sum_divide fn to callable lambda
#define RUN_square_sum_divide(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("square_sum_divide-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_square_sum_divide_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_square_sum_divide(case_name, ...) \
RUN_square_sum_divide_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SQUARE_SUM_DIVIDE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(composition, square_sum_divide, case_name); \
    using namespace args; \
    auto result = RUN_square_sum_divide(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("square_sum_divide(case1)" * doctest::test_suite("composition::square_sum_divide"))
{
    SQUARE_SUM_DIVIDE_SUBCASE( case1,   a, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case1, a_a, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case1, a_f, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case1, a_h, N, axis, dtype, keepdims );
    // SQUARE_SUM_DIVIDE_SUBCASE( case1, a_d, N, axis, dtype, keepdims );
}

TEST_CASE("square_sum_divide(case2)" * doctest::test_suite("composition::square_sum_divide"))
{
    SQUARE_SUM_DIVIDE_SUBCASE( case2, a, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case2, a_a, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case2, a_f, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case2, a_h, N, axis, dtype, keepdims );
    // SQUARE_SUM_DIVIDE_SUBCASE( case2, a_d, N, axis, dtype, keepdims );

    {
        NMTOOLS_TESTING_DECLARE_NS(composition, square_sum_divide, case2);
        using namespace args;

        auto view = composition::square_sum_divide(a, N, axis, dtype, keepdims);
        using view_t = decltype(view);
        static_assert(  nm::meta::is_ndarray_v<view_t> );
        static_assert( !nm::meta::is_num_v<view_t> );
    }
}

TEST_CASE("square_sum_divide(case3)" * doctest::test_suite("composition::square_sum_divide"))
{
    SQUARE_SUM_DIVIDE_SUBCASE( case3, a, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case3, a_a, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case3, a_f, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case3, a_h, N, axis, dtype, keepdims );
    // SQUARE_SUM_DIVIDE_SUBCASE( case3, a_d, N, axis, dtype, keepdims );
}

TEST_CASE("square_sum_divide(case4)" * doctest::test_suite("composition::square_sum_divide"))
{
    SQUARE_SUM_DIVIDE_SUBCASE( case4, a, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case4, a_a, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case4, a_f, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case4, a_h, N, axis, dtype, keepdims );
    // SQUARE_SUM_DIVIDE_SUBCASE( case4, a_d, N, axis, dtype, keepdims );
}

TEST_CASE("square_sum_divide(case5)" * doctest::test_suite("composition::square_sum_divide"))
{
    SQUARE_SUM_DIVIDE_SUBCASE( case5, a, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case5, a_a, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case5, a_f, N, axis, dtype, keepdims );
    SQUARE_SUM_DIVIDE_SUBCASE( case5, a_h, N, axis, dtype, keepdims );
    // SQUARE_SUM_DIVIDE_SUBCASE( case5, a_d, N, axis, dtype, keepdims );
}