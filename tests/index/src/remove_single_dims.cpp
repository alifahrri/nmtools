#include "nmtools/array/index/remove_single_dims.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define RUN_impl(...) \
::nmtools::index::remove_single_dims(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs remove_single_dims fn to callable lambda
#define RUN_remove_single_dims(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("remove_single_dims-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_remove_single_dims(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REMOVE_SINGLE_DIMS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, remove_single_dims, case_name) \
    using namespace args; \
    auto result = RUN_remove_single_dims(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

NMTOOLS_TESTING_DECLARE_CASE(index, remove_single_dims)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int shape[3] = {1,2,3};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int shape[3] = {1,2,3};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[2] = {2,3};
    }
}

TEST_CASE("remove_single_dims(case1)" * doctest::test_suite("index::remove_single_dims"))
{
    REMOVE_SINGLE_DIMS_SUBCASE( case1, shape );
    REMOVE_SINGLE_DIMS_SUBCASE( case1, shape_a );
    REMOVE_SINGLE_DIMS_SUBCASE( case1, shape_v );
    REMOVE_SINGLE_DIMS_SUBCASE( case1, shape_f );
    // REMOVE_SINGLE_DIMS_SUBCASE( case1, shape_d );
    REMOVE_SINGLE_DIMS_SUBCASE( case1, shape_h );
}

TEST_CASE("remove_single_dims(case2)" * doctest::test_suite("index::remove_single_dims"))
{
    REMOVE_SINGLE_DIMS_SUBCASE( case2, shape );
    REMOVE_SINGLE_DIMS_SUBCASE( case2, shape_a );
    REMOVE_SINGLE_DIMS_SUBCASE( case2, shape_v );
    REMOVE_SINGLE_DIMS_SUBCASE( case2, shape_f );
    // REMOVE_SINGLE_DIMS_SUBCASE( case2, shape_d );
    REMOVE_SINGLE_DIMS_SUBCASE( case2, shape_h );
}

TEST_CASE("remove_single_dims" * doctest::test_suite("index::remove_single_dims"))
{
    {
        auto shape = nmtools_array{1,2,3};
        auto squeezed = nm::index::remove_single_dims(shape);
        auto expected = nmtools_array{2,3};
        NMTOOLS_ASSERT_EQUAL( squeezed, expected );
    }
    // using tuple with runtime value not supported yet
    // {
    //     auto shape = std::tuple{1,2,3};
    //     auto squeezed = nm::index::remove_single_dims(shape);
    //     auto expected = nmtools_array{2,3};
    //     NMTOOLS_ASSERT_EQUAL( squeezed, expected );
    // }
    #ifndef NMTOOLS_DISABLE_STL
    {
        auto shape = std::vector{1,2,3};
        auto squeezed = nm::index::remove_single_dims(shape);
        auto expected = nmtools_array{2,3};
        NMTOOLS_ASSERT_EQUAL( squeezed, expected );
    }
    #endif // NMTOOLS_DISABLE_STL
    {
        auto shape = nm::array::hybrid_ndarray({1,2,3});
        auto squeezed = nm::index::remove_single_dims(shape);
        auto expected = nmtools_array{2,3};
        NMTOOLS_ASSERT_EQUAL( squeezed, expected );
    }
}