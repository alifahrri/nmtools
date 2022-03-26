#include "nmtools/array/view/ufuncs/subtract.hpp"
#include "nmtools/array/view/ufuncs/fabs.hpp"
#include "nmtools/array/view/ufuncs/square.hpp"
#include "nmtools/testing/doctest.hpp"

namespace composition
{
    namespace view = nmtools::view;

    template <typename lhs_t, typename rhs_t>
    constexpr auto subtract_fabs_square(const lhs_t& lhs, const rhs_t& rhs)
    {
        auto a = view::subtract(lhs, rhs);
        auto b = view::fabs(a);
        auto c = view::square(b);
        return c;
    } // subtract_fabs_square
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

NMTOOLS_TESTING_DECLARE_CASE(composition, subtract_fabs_square)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        inline float b[1][1][1] = {
            {
                {5.5}
            }
        };
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[2][3][2] = {
            {
                {30.25, 20.25},
                {12.25,  6.25},
                { 2.25,  0.25},
            },
            {
                { 0.25,  2.25},
                { 6.25, 12.25},
                {20.25, 30.25},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        inline float b = 5.5;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[2][3][2] = {
            {
                {30.25, 20.25},
                {12.25,  6.25},
                { 2.25,  0.25},
            },
            {
                { 0.25,  2.25},
                { 6.25, 12.25},
                {20.25, 30.25},
            }
        };
    }
}

#define RUN_subtract_fabs_square_impl(...) \
composition::subtract_fabs_square(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs subtract_fabs_square fn to callable lambda
#define RUN_subtract_fabs_square(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("subtract_fabs_square-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_subtract_fabs_square_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_subtract_fabs_square(case_name, ...) \
RUN_subtract_fabs_square_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SUBTRACT_FABS_SQUARE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(composition, subtract_fabs_square, case_name); \
    using namespace args; \
    auto result = RUN_subtract_fabs_square(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("subtract_fabs_square(case1)" * doctest::test_suite("composition::subtract_fabs_square"))
{
    SUBTRACT_FABS_SQUARE_SUBCASE( case1, a, b );
    SUBTRACT_FABS_SQUARE_SUBCASE( case1, a_a, b_a );
    SUBTRACT_FABS_SQUARE_SUBCASE( case1, a_f, b_f );
    SUBTRACT_FABS_SQUARE_SUBCASE( case1, a_h, b_h );
    SUBTRACT_FABS_SQUARE_SUBCASE( case1, a_d, b_d );
}

TEST_CASE("subtract_fabs_square(case2)" * doctest::test_suite("composition::subtract_fabs_square"))
{
    SUBTRACT_FABS_SQUARE_SUBCASE( case2,   a, b );
    SUBTRACT_FABS_SQUARE_SUBCASE( case2, a_a, b );
    SUBTRACT_FABS_SQUARE_SUBCASE( case2, a_f, b );
    SUBTRACT_FABS_SQUARE_SUBCASE( case2, a_h, b );
    SUBTRACT_FABS_SQUARE_SUBCASE( case2, a_d, b );
}