#include "nmtools/array/mean.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nm::view;

namespace composition
{
    template <typename array_t, typename axis_t, typename dtype_t=nmtools::none_t>
    constexpr auto mean_subtract(const array_t& array, const axis_t& axis, dtype_t dtype=dtype_t{})
    {
        // must keep dimension to properly subtract
        auto a = view::mean(array,axis,dtype,nmtools::True);
        auto b = view::subtract(array,a);
        return b;
    } // mean_subtract
} // composition

namespace na = nm::array;
namespace kind = na::kind;


NMTOOLS_TESTING_DECLARE_CASE(composition, mean_subtract)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[2][3][2] = {
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
        inline int axis[1] = {0};
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[2][3][2] = {
            {
                {-3, -3},
                {-3, -3},
                {-3, -3},
            },
            {
                {3, 3},
                {3, 3},
                {3, 3},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[2][3][2] = {
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
        inline int axis[1] = {1};
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[2][3][2] = {
            {
                {-2., -2.},
                { 0.,  0.},
                { 2.,  2.},
            },
            {
                {-2., -2.},
                { 0.,  0.},
                { 2.,  2.},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[2][3][2] = {
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
        inline int axis[1] = {1};
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline float result[2][3][2] = {
            {
                {-2., -2.},
                { 0.,  0.},
                { 2.,  2.},
            },
            {
                {-2., -2.},
                { 0.,  0.},
                { 2.,  2.},
            }
        };
    }

    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[2][3][2] = {
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
        inline auto axis = 0_ct;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline float result[2][3][2] = {
            {
                {-3, -3},
                {-3, -3},
                {-3, -3},
            },
            {
                {3, 3},
                {3, 3},
                {3, 3},
            }
        };
    }
}

#define RUN_mean_subtract_impl(...) \
composition::mean_subtract(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs mean_subtract fn to callable lambda
#define RUN_mean_subtract(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("mean_subtract-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_mean_subtract_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_mean_subtract(case_name, ...) \
RUN_mean_subtract_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MEAN_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(composition, mean_subtract, case_name); \
    using namespace args; \
    auto result = RUN_mean_subtract(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("mean_subtract(case1)" * doctest::test_suite("composition::mean_subtract"))
{
    {
        NMTOOLS_TESTING_USE_CASE(composition, mean_subtract, case1);
    }

    MEAN_SUBTRACT_SUBCASE( case1, array, axis );
    MEAN_SUBTRACT_SUBCASE( case1, array_a, axis_a );
    MEAN_SUBTRACT_SUBCASE( case1, array_f, axis_f );
    MEAN_SUBTRACT_SUBCASE( case1, array_h, axis_h );
    // dynamic-dim not supported yet
    // TODO: support dynamic dimension
    // MEAN_SUBTRACT_SUBCASE( case1, array_d, axis );
}

TEST_CASE("mean_subtract(case2)" * doctest::test_suite("composition::mean_subtract"))
{
    MEAN_SUBTRACT_SUBCASE( case2, array, axis );
    MEAN_SUBTRACT_SUBCASE( case2, array_a, axis_a );
    MEAN_SUBTRACT_SUBCASE( case2, array_f, axis_f );
    MEAN_SUBTRACT_SUBCASE( case2, array_h, axis_h );
    // dynamic-dim not supported yet
    // TODO: support dynamic dimension
    // MEAN_SUBTRACT_SUBCASE( case2, array_d, axis );
}

TEST_CASE("mean_subtract(case3)" * doctest::test_suite("composition::mean_subtract"))
{
    MEAN_SUBTRACT_SUBCASE( case3, array, axis );
    MEAN_SUBTRACT_SUBCASE( case3, array_a, axis_a );
    MEAN_SUBTRACT_SUBCASE( case3, array_f, axis_f );
    MEAN_SUBTRACT_SUBCASE( case3, array_h, axis_h );
    // dynamic-dim not supported yet
    // TODO: support dynamic dimension
    // MEAN_SUBTRACT_SUBCASE( case3, array_d, axis );
}

namespace meta = nmtools::meta;

TEST_CASE("mean_subtract(case4)" * doctest::test_suite("composition::mean_subtract"))
{
    // TODO: fix compile-time shape inference
    #if 0
    {
        NMTOOLS_TESTING_USE_CASE(composition, mean_subtract, case4);
        using namespace args;

        auto a = composition::mean_subtract( array, axis );
        using a_t = decltype(a);
        static_assert( meta::is_fixed_size_ndarray_v<a_t> );
    }
    #endif
    MEAN_SUBTRACT_SUBCASE( case4, array, axis );
    MEAN_SUBTRACT_SUBCASE( case4, array_a, axis );
    MEAN_SUBTRACT_SUBCASE( case4, array_f, axis );
    MEAN_SUBTRACT_SUBCASE( case4, array_h, axis );
    // dynamic-dim not supported yet
    // TODO: support dynamic dimension
    // MEAN_SUBTRACT_SUBCASE( case4, array_d, axis );
}