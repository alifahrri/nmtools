#include "nmtools/array/array/slice.hpp"
#include "nmtools/testing/data/array/slice.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_slice_impl(...) \
nm::array::slice(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs slice fn to callable lambda
#define RUN_slice(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("slice-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_slice_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_slice(case_name, ...) \
RUN_slice_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, slice, case_name); \
    using namespace args; \
    auto result = RUN_slice(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("slice(case1)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case1,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_a, slice0, slice1, slice2);
    // TODO: remove nested vector support
    SLICE_SUBCASE(case1, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case2)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case2,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case3)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case3,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case4)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case4,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case5)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case5,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case6)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case6,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case7)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case7,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case8)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case8,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case9)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case9,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case10)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case10,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case11)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case11,   array, slice0, slice1);
    SLICE_SUBCASE(case11, array_a, slice0, slice1);
    SLICE_SUBCASE(case11, array_f, slice0, slice1);
    SLICE_SUBCASE(case11, array_d, slice0, slice1);
    SLICE_SUBCASE(case11, array_h, slice0, slice1);
}

TEST_CASE("slice(case12)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case12,   array, slice0, slice1);
    SLICE_SUBCASE(case12, array_a, slice0, slice1);
    SLICE_SUBCASE(case12, array_f, slice0, slice1);
    SLICE_SUBCASE(case12, array_d, slice0, slice1);
    SLICE_SUBCASE(case12, array_h, slice0, slice1);
}

TEST_CASE("slice(case13)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case13,   array, slice0, slice1);
    SLICE_SUBCASE(case13, array_a, slice0, slice1);
    SLICE_SUBCASE(case13, array_f, slice0, slice1);
    SLICE_SUBCASE(case13, array_d, slice0, slice1);
    SLICE_SUBCASE(case13, array_h, slice0, slice1);
}

TEST_CASE("slice(case14)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case14,   array, slice0, slice1);
    SLICE_SUBCASE(case14, array_a, slice0, slice1);
    SLICE_SUBCASE(case14, array_f, slice0, slice1);
    SLICE_SUBCASE(case14, array_d, slice0, slice1);
    SLICE_SUBCASE(case14, array_h, slice0, slice1);
}

TEST_CASE("slice(case15)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case15,   array, slice0, slice1);
    SLICE_SUBCASE(case15, array_a, slice0, slice1);
    SLICE_SUBCASE(case15, array_f, slice0, slice1);
    SLICE_SUBCASE(case15, array_d, slice0, slice1);
    SLICE_SUBCASE(case15, array_h, slice0, slice1);
}

TEST_CASE("slice(case16)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case16,   array, slice0, slice1);
    SLICE_SUBCASE(case16, array_a, slice0, slice1);
    SLICE_SUBCASE(case16, array_f, slice0, slice1);
    SLICE_SUBCASE(case16, array_d, slice0, slice1);
    SLICE_SUBCASE(case16, array_h, slice0, slice1);
}

TEST_CASE("slice(case17)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case17,   array, slice0, slice1);
    SLICE_SUBCASE(case17, array_a, slice0, slice1);
    SLICE_SUBCASE(case17, array_f, slice0, slice1);
    SLICE_SUBCASE(case17, array_d, slice0, slice1);
    SLICE_SUBCASE(case17, array_h, slice0, slice1);
}

TEST_CASE("slice(case18)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case18,   array, slice0, slice1);
    SLICE_SUBCASE(case18, array_a, slice0, slice1);
    SLICE_SUBCASE(case18, array_f, slice0, slice1);
    SLICE_SUBCASE(case18, array_d, slice0, slice1);
    SLICE_SUBCASE(case18, array_h, slice0, slice1);
}

TEST_CASE("slice(case19)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case19,   array, slice0, slice1);
    SLICE_SUBCASE(case19, array_a, slice0, slice1);
    SLICE_SUBCASE(case19, array_f, slice0, slice1);
    SLICE_SUBCASE(case19, array_d, slice0, slice1);
    SLICE_SUBCASE(case19, array_h, slice0, slice1);
}

TEST_CASE("slice(case20)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case20,   array, slice0, slice1);
    SLICE_SUBCASE(case20, array_a, slice0, slice1);
    SLICE_SUBCASE(case20, array_f, slice0, slice1);
    SLICE_SUBCASE(case20, array_d, slice0, slice1);
    SLICE_SUBCASE(case20, array_h, slice0, slice1);
}

TEST_CASE("slice(case21)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case21,   array, slice0, slice1);
    SLICE_SUBCASE(case21, array_a, slice0, slice1);
    SLICE_SUBCASE(case21, array_f, slice0, slice1);
    SLICE_SUBCASE(case21, array_d, slice0, slice1);
    SLICE_SUBCASE(case21, array_h, slice0, slice1);
}

TEST_CASE("slice(case22)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case22,   array, slice0, slice1);
    SLICE_SUBCASE(case22, array_a, slice0, slice1);
    SLICE_SUBCASE(case22, array_f, slice0, slice1);
    SLICE_SUBCASE(case22, array_d, slice0, slice1);
    SLICE_SUBCASE(case22, array_h, slice0, slice1);
}

TEST_CASE("slice(case23)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case23,   array, slice0, slice1);
    SLICE_SUBCASE(case23, array_a, slice0, slice1);
    SLICE_SUBCASE(case23, array_f, slice0, slice1);
    SLICE_SUBCASE(case23, array_d, slice0, slice1);
    SLICE_SUBCASE(case23, array_h, slice0, slice1);
}

TEST_CASE("slice(case24)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case24,   array, slice0, slice1);
    SLICE_SUBCASE(case24, array_a, slice0, slice1);
    SLICE_SUBCASE(case24, array_f, slice0, slice1);
    SLICE_SUBCASE(case24, array_d, slice0, slice1);
    SLICE_SUBCASE(case24, array_h, slice0, slice1);
}

TEST_CASE("slice(case25)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case25,   array, slice0, slice1);
    SLICE_SUBCASE(case25, array_a, slice0, slice1);
    SLICE_SUBCASE(case25, array_f, slice0, slice1);
    SLICE_SUBCASE(case25, array_d, slice0, slice1);
    SLICE_SUBCASE(case25, array_h, slice0, slice1);
}

TEST_CASE("slice(case26)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case26,   array, slice0, slice1);
    SLICE_SUBCASE(case26, array_a, slice0, slice1);
    SLICE_SUBCASE(case26, array_f, slice0, slice1);
    SLICE_SUBCASE(case26, array_d, slice0, slice1);
    SLICE_SUBCASE(case26, array_h, slice0, slice1);
}

TEST_CASE("slice(case27)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case27,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case28)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case28,   array, slice0, slice1);
    SLICE_SUBCASE(case28, array_a, slice0, slice1);
    SLICE_SUBCASE(case28, array_f, slice0, slice1);
    SLICE_SUBCASE(case28, array_d, slice0, slice1);
    SLICE_SUBCASE(case28, array_h, slice0, slice1);
}

TEST_CASE("slice(case29)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case29,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case30)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case30,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case31)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case31,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case32)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case32,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case33)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case33,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case34)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case34,   array, slice0, slice1);
    SLICE_SUBCASE(case34, array_a, slice0, slice1);
    SLICE_SUBCASE(case34, array_f, slice0, slice1);
    SLICE_SUBCASE(case34, array_d, slice0, slice1);
    SLICE_SUBCASE(case34, array_h, slice0, slice1);
}

TEST_CASE("slice(case35)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case35,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case36)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case36,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_h, slice0, slice1, slice2);
}

TEST_CASE("slice(case37)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case37,   array, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_a, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_f, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_d, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_h, slice0, slice1, slice2, slice3);
}

TEST_CASE("slice(case38)" * doctest::test_suite("array::slice"))
{
    SLICE_SUBCASE(case38,   array, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_a, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_f, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_d, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_h, slice0, slice1, slice2, slice3);
}