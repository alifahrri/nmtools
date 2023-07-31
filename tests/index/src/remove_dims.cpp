#include "nmtools/array/index/remove_dims.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(index, remove_dims)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int shape[3] = {1,2,3};
        int axis = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[2] = {1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int shape[3] = {1,2,3};
        int axis = 1;
        auto keepdims = True;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[3] = {1,1,3};
    }
}

#define RUN_impl(...) \
::nmtools::index::remove_dims(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs remove_dims fn to callable lambda
#define RUN_remove_dims(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("remove_dims-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_remove_dims(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REMOVE_DIMS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, remove_dims, case_name) \
    using namespace args; \
    auto result = RUN_remove_dims(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("remove_dims(case1)" * doctest::test_suite("index::remove_dims"))
{
    REMOVE_DIMS_SUBCASE( case1, shape, axis );
    REMOVE_DIMS_SUBCASE( case1, shape_a, axis );
    REMOVE_DIMS_SUBCASE( case1, shape_v, axis );
    REMOVE_DIMS_SUBCASE( case1, shape_f, axis );
    // REMOVE_DIMS_SUBCASE( case1, shape_d, axis );
    REMOVE_DIMS_SUBCASE( case1, shape_h, axis );
}

TEST_CASE("remove_dims(case2)" * doctest::test_suite("index::remove_dims"))
{
    REMOVE_DIMS_SUBCASE( case2, shape, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case2, shape_a, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case2, shape_v, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case2, shape_f, axis, keepdims );
    // REMOVE_DIMS_SUBCASE( case2, shape_d, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case2, shape_h, axis, keepdims );
}