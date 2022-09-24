#include "nmtools/array/array/take.hpp"
#include "nmtools/testing/data/array/take.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_take_impl(...) \
nm::array::take(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs take fn to callable lambda
#define RUN_take(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("take-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_take_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_take(case_name, ...) \
RUN_take_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define TAKE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, take, case_name); \
    using namespace args; \
    auto result = RUN_take(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("case1" * doctest::test_suite("array::take"))
{
    // TODO: fix runtime: len(indices) != len(strides) in compute_offset
    #ifndef NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case1,   array,   indices, axis );
    TAKE_SUBCASE( case1, array_a, indices_a, axis );
    TAKE_SUBCASE( case1, array_f, indices_f, axis );
    TAKE_SUBCASE( case1, array_d, indices_d, axis );
    TAKE_SUBCASE( case1, array_h, indices_h, axis );
    #endif
}

TEST_CASE("case2" * doctest::test_suite("array::take"))
{
    // TODO: fix runtime: len(indices) != len(strides) in compute_offset
    #ifndef NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case2,   array,   indices, axis );
    TAKE_SUBCASE( case2, array_a, indices_a, axis );
    TAKE_SUBCASE( case2, array_f, indices_f, axis );
    TAKE_SUBCASE( case2, array_d, indices_d, axis );
    TAKE_SUBCASE( case2, array_h, indices_h, axis );
    #endif
}

TEST_CASE("case3" * doctest::test_suite("array::take"))
{
    // TODO: fix runtime: len(indices) != len(strides) in compute_offset
    #ifndef NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case3,   array,   indices, axis );
    TAKE_SUBCASE( case3, array_a, indices_a, axis );
    TAKE_SUBCASE( case3, array_f, indices_f, axis );
    TAKE_SUBCASE( case3, array_d, indices_d, axis );
    TAKE_SUBCASE( case3, array_h, indices_h, axis );
    #endif
}

TEST_CASE("case4" * doctest::test_suite("array::take"))
{
    // TODO: fix runtime: len(indices) != len(strides) in compute_offset
    #ifndef NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case4,   array,   indices, axis );
    TAKE_SUBCASE( case4, array_a, indices_a, axis );
    TAKE_SUBCASE( case4, array_f, indices_f, axis );
    TAKE_SUBCASE( case4, array_d, indices_d, axis );
    TAKE_SUBCASE( case4, array_h, indices_h, axis );
    #endif
}

TEST_CASE("case5" * doctest::test_suite("array::take"))
{
    // TODO: fix runtime: len(indices) != len(strides) in compute_offset
    #ifndef NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case5,   array,   indices, axis );
    TAKE_SUBCASE( case5, array_a, indices_a, axis );
    TAKE_SUBCASE( case5, array_f, indices_f, axis );
    TAKE_SUBCASE( case5, array_d, indices_d, axis );
    TAKE_SUBCASE( case5, array_h, indices_h, axis );
    #endif
}

TEST_CASE("case6" * doctest::test_suite("array::take"))
{
    // TODO: fix runtime: len(indices) != len(strides) in compute_offset
    #ifndef NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case6,   array,   indices, axis );
    TAKE_SUBCASE( case6, array_a, indices_a, axis );
    TAKE_SUBCASE( case6, array_f, indices_f, axis );
    TAKE_SUBCASE( case6, array_d, indices_d, axis );
    TAKE_SUBCASE( case6, array_h, indices_h, axis );
    #endif
}