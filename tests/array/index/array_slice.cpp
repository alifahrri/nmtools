#include "nmtools/array/index/array_slice.hpp"
#include "nmtools/testing/data/array/array_slice.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_shape_array_slice_impl(...) \
nm::index::shape_array_slice(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_array_slice fn to callable lambda
#define RUN_shape_array_slice(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_array_slice-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_array_slice_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_array_slice(case_name, ...) \
RUN_shape_array_slice_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_ARRAY_SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, shape_array_slice, case_name); \
    using namespace args; \
    auto result = RUN_shape_array_slice(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("shape_array_slice(case1)" * doctest::test_suite("index::shape_array_slice"))
{
    SHAPE_ARRAY_SLICE_SUBCASE( case1, shape, slice0, slice1 );
    SHAPE_ARRAY_SLICE_SUBCASE( case1, shape_a, slice0_a, slice1_a );
    SHAPE_ARRAY_SLICE_SUBCASE( case1, shape_f, slice0_f, slice1_f );
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    SHAPE_ARRAY_SLICE_SUBCASE( case1, shape_v, slice0_v, slice1_v );
    #endif
}

TEST_CASE("shape_array_slice(case2)" * doctest::test_suite("index::shape_array_slice"))
{
    SHAPE_ARRAY_SLICE_SUBCASE( case2, shape, slice0, slice1 );
    SHAPE_ARRAY_SLICE_SUBCASE( case2, shape_a, slice0_a, slice1_a );
    SHAPE_ARRAY_SLICE_SUBCASE( case2, shape_f, slice0_f, slice1_f );
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    SHAPE_ARRAY_SLICE_SUBCASE( case2, shape_v, slice0_v, slice1_v );
    #endif
}

TEST_CASE("shape_array_slice(case3)" * doctest::test_suite("index::shape_array_slice"))
{
    SHAPE_ARRAY_SLICE_SUBCASE( case3, shape, slice0, slice1 );
    SHAPE_ARRAY_SLICE_SUBCASE( case3, shape_a, slice0_a, slice1_a );
    SHAPE_ARRAY_SLICE_SUBCASE( case3, shape_f, slice0_f, slice1_f );
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    SHAPE_ARRAY_SLICE_SUBCASE( case3, shape_v, slice0_v, slice1_v );
    #endif
}

TEST_CASE("shape_array_slice(case4)" * doctest::test_suite("index::shape_array_slice"))
{
    SHAPE_ARRAY_SLICE_SUBCASE( case4, shape, slice0, slice1 );
    SHAPE_ARRAY_SLICE_SUBCASE( case4, shape_a, slice0_a, slice1_a );
    SHAPE_ARRAY_SLICE_SUBCASE( case4, shape_f, slice0_f, slice1_f );
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    SHAPE_ARRAY_SLICE_SUBCASE( case4, shape_v, slice0_v, slice1_v );
    #endif
}

TEST_CASE("shape_array_slice(case5)" * doctest::test_suite("index::shape_array_slice"))
{
    #ifndef NMTOOLS_DISABLE_STL
    // NOTE: the following requires std::vector
    // TODO: implement utl vector
    SHAPE_ARRAY_SLICE_SUBCASE( case5, shape, slice0 );
    SHAPE_ARRAY_SLICE_SUBCASE( case5, shape_a, slice0_a );
    SHAPE_ARRAY_SLICE_SUBCASE( case5, shape_f, slice0_f );
    #endif // NMTOOLS_DISABLE_STL
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    SHAPE_ARRAY_SLICE_SUBCASE( case5, shape_v, slice0_v );
    #endif
}

TEST_CASE("shape_array_slice(case6)" * doctest::test_suite("index::shape_array_slice"))
{
    #ifndef NMTOOLS_DISABLE_STL
    // NOTE: the following requires std::vector
    // TODO: implement utl vector
    SHAPE_ARRAY_SLICE_SUBCASE( case6, shape, slice0 );
    SHAPE_ARRAY_SLICE_SUBCASE( case6, shape_a, slice0_a );
    SHAPE_ARRAY_SLICE_SUBCASE( case6, shape_f, slice0_f );
    #endif
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    SHAPE_ARRAY_SLICE_SUBCASE( case6, shape_v, slice0_v );
    #endif
}

TEST_CASE("shape_array_slice(case7)" * doctest::test_suite("index::shape_array_slice"))
{
    #ifndef NMTOOLS_DISABLE_STL
    // NOTE: the following requires std::vector
    // TODO: implement utl vector
    SHAPE_ARRAY_SLICE_SUBCASE( case7, shape, slice0 );
    SHAPE_ARRAY_SLICE_SUBCASE( case7, shape_a, slice0_a );
    SHAPE_ARRAY_SLICE_SUBCASE( case7, shape_f, slice0_f );
    #endif
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    SHAPE_ARRAY_SLICE_SUBCASE( case7, shape_v, slice0_v );
    #endif
}

TEST_CASE("shape_array_slice(case8)" * doctest::test_suite("index::shape_array_slice"))
{
    #ifndef NMTOOLS_DISABLE_STL
    // NOTE: the following requires std::vector
    // TODO: implement utl vector
    SHAPE_ARRAY_SLICE_SUBCASE( case8, shape, slice0, slice1 );
    SHAPE_ARRAY_SLICE_SUBCASE( case8, shape_a, slice0_a, slice1_a );
    SHAPE_ARRAY_SLICE_SUBCASE( case8, shape_f, slice0_f, slice1_f );
    #endif
    #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
    SHAPE_ARRAY_SLICE_SUBCASE( case8, shape_v, slice0_v, slice1_v );
    #endif
}