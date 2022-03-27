#include "nmtools/array/array/compress.hpp"
#include "nmtools/testing/data/array/compress.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_compress_impl(...) \
nm::array::compress(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs compress fn to callable lambda
#define RUN_compress(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("compress-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_compress_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_compress(case_name, ...) \
RUN_compress_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define COMPRESS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, compress, case_name); \
    using namespace args; \
    auto result = RUN_compress(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("compress(case1)" * doctest::test_suite("array::compress"))
{
    COMPRESS_SUBCASE( case1,   condition,   array, axis );
    COMPRESS_SUBCASE( case1, condition_a, array_a, axis );
    COMPRESS_SUBCASE( case1, condition_v, array_v, axis );
    COMPRESS_SUBCASE( case1, condition_f, array_f, axis );
    COMPRESS_SUBCASE( case1, condition_d, array_d, axis );
    COMPRESS_SUBCASE( case1, condition_h, array_h, axis );
}

TEST_CASE("compress(case2)" * doctest::test_suite("array::compress"))
{
    COMPRESS_SUBCASE( case2,   condition,   array, axis );
    COMPRESS_SUBCASE( case2, condition_a, array_a, axis );
    COMPRESS_SUBCASE( case2, condition_v, array_v, axis );
    COMPRESS_SUBCASE( case2, condition_f, array_f, axis );
    COMPRESS_SUBCASE( case2, condition_d, array_d, axis );
    COMPRESS_SUBCASE( case2, condition_h, array_h, axis );
}

TEST_CASE("compress(case3)" * doctest::test_suite("array::compress"))
{
    COMPRESS_SUBCASE( case3,   condition,   array, axis );
    COMPRESS_SUBCASE( case3, condition_a, array_a, axis );
    COMPRESS_SUBCASE( case3, condition_v, array_v, axis );
    COMPRESS_SUBCASE( case3, condition_f, array_f, axis );
    COMPRESS_SUBCASE( case3, condition_d, array_d, axis );
    COMPRESS_SUBCASE( case3, condition_h, array_h, axis );
}

TEST_CASE("compress(case4)" * doctest::test_suite("array::compress"))
{
    COMPRESS_SUBCASE( case4,   condition,   array, axis );
    COMPRESS_SUBCASE( case4, condition_a, array_a, axis );
    COMPRESS_SUBCASE( case4, condition_v, array_v, axis );
    COMPRESS_SUBCASE( case4, condition_f, array_f, axis );
    COMPRESS_SUBCASE( case4, condition_d, array_d, axis );
    COMPRESS_SUBCASE( case4, condition_h, array_h, axis );
}

TEST_CASE("compress(case5)" * doctest::test_suite("array::compress"))
{
    COMPRESS_SUBCASE( case5, condition,   array, axis );
    COMPRESS_SUBCASE( case5, condition, array_a, axis );
    COMPRESS_SUBCASE( case5, condition, array_v, axis );
    COMPRESS_SUBCASE( case5, condition, array_f, axis );
    COMPRESS_SUBCASE( case5, condition, array_d, axis );
    COMPRESS_SUBCASE( case5, condition, array_h, axis );
}