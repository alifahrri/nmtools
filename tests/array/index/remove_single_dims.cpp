#include "nmtools/array/index/remove_single_dims.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
auto name##_a = cast(name, kind::nested_arr); \
auto name##_v = cast(name, kind::nested_vec); \
auto name##_f = cast(name, kind::fixed); \
auto name##_d = cast(name, kind::dynamic); \
auto name##_h = cast(name, kind::hybrid); \

#define RUN_impl(...) \
::nmtools::index::remove_single_dims(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
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
    NMTOOLS_TESTING_DECLARE_NS(index, remove_single_dims, case_name) \
    using namespace args; \
    auto result = RUN_remove_single_dims(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

NMTOOLS_TESTING_DECLARE_CASE(index, remove_single_dims)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int shape[3] = {1,2,3};
        CAST_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int shape[3] = {1,2,3};
        CAST_ARRAYS(shape)
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
        auto shape = std::array{1,2,3};
        auto squeezed = nm::index::remove_single_dims(shape);
        auto expected = std::array{2,3};
        NMTOOLS_ASSERT_EQUAL( squeezed, expected );
    }
    // using tuple with runtime value not supported yet
    // {
    //     auto shape = std::tuple{1,2,3};
    //     auto squeezed = nm::index::remove_single_dims(shape);
    //     auto expected = std::array{2,3};
    //     NMTOOLS_ASSERT_EQUAL( squeezed, expected );
    // }
    {
        auto shape = std::vector{1,2,3};
        auto squeezed = nm::index::remove_single_dims(shape);
        auto expected = std::array{2,3};
        NMTOOLS_ASSERT_EQUAL( squeezed, expected );
    }
    {
        auto shape = nm::array::hybrid_ndarray({1,2,3});
        auto squeezed = nm::index::remove_single_dims(shape);
        auto expected = std::array{2,3};
        NMTOOLS_ASSERT_EQUAL( squeezed, expected );
    }
}