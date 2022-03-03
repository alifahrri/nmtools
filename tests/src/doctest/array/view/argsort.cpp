#include "nmtools/array/view/argsort.hpp"
#include "nmtools/testing/data/array/argsort.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_argsort_impl(...) \
nm::view::argsort(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs argsort fn to callable lambda
#define RUN_argsort(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("argsort-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_argsort_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_argsort(case_name, ...) \
RUN_argsort_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

// TODO: move to testing utility
#define NMTOOLS_REQUIRE_EQUAL(lhs, rhs) \
{ \
    auto lhs_str = nmtools::utils::to_string(lhs); \
    auto rhs_str = nmtools::utils::to_string(rhs); \
    auto msg_str = nmtools_string("\nActual:\n") + lhs_str + nmtools_string("\nExpected:\n") + rhs_str; \
    REQUIRE_MESSAGE( (nmtools::utils::isequal(lhs, rhs)), msg_str ); \
}

// TODO: properly deduce ndarray type
#define ARGSORT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, argsort, case_name); \
    using namespace args; \
    auto view = RUN_argsort(case_name, __VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(*view), nm::shape(expect::result) ); \
    using ndarray_t = na::dynamic_ndarray<int>; \
    auto result = static_cast<ndarray_t>(*view); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("argsort(case1)" * doctest::test_suite("view::argsort"))
{
    ARGSORT_SUBCASE( case1, array, axis );
    ARGSORT_SUBCASE( case1, array_a, axis );
    ARGSORT_SUBCASE( case1, array_f, axis );
    ARGSORT_SUBCASE( case1, array_h, axis );
    ARGSORT_SUBCASE( case1, array_d, axis );
}

TEST_CASE("argsort(case2)" * doctest::test_suite("view::argsort"))
{
    ARGSORT_SUBCASE( case2, array, axis );
    ARGSORT_SUBCASE( case2, array_a, axis );
    ARGSORT_SUBCASE( case2, array_f, axis );
    ARGSORT_SUBCASE( case2, array_h, axis );
    ARGSORT_SUBCASE( case2, array_d, axis );
}

TEST_CASE("argsort(case3)" * doctest::test_suite("view::argsort"))
{
    ARGSORT_SUBCASE( case3, array, axis );
    ARGSORT_SUBCASE( case3, array_a, axis );
    ARGSORT_SUBCASE( case3, array_f, axis );
    ARGSORT_SUBCASE( case3, array_h, axis );
    ARGSORT_SUBCASE( case3, array_d, axis );
}

TEST_CASE("argsort(case4)" * doctest::test_suite("view::argsort"))
{
    ARGSORT_SUBCASE( case4, array, axis );
    ARGSORT_SUBCASE( case4, array_a, axis );
    ARGSORT_SUBCASE( case4, array_f, axis );
    ARGSORT_SUBCASE( case4, array_h, axis );
    ARGSORT_SUBCASE( case4, array_d, axis );
}

TEST_CASE("argsort(case5)" * doctest::test_suite("view::argsort"))
{
    ARGSORT_SUBCASE( case5, array, axis );
    ARGSORT_SUBCASE( case5, array_a, axis );
    ARGSORT_SUBCASE( case5, array_f, axis );
    ARGSORT_SUBCASE( case5, array_h, axis );
    ARGSORT_SUBCASE( case5, array_d, axis );
}

TEST_CASE("argsort(case6)" * doctest::test_suite("view::argsort"))
{
    ARGSORT_SUBCASE( case6, array, axis );
    ARGSORT_SUBCASE( case6, array_a, axis );
    ARGSORT_SUBCASE( case6, array_f, axis );
    ARGSORT_SUBCASE( case6, array_h, axis );
    ARGSORT_SUBCASE( case6, array_d, axis );
}


TEST_CASE("argsort(case7)" * doctest::test_suite("view::argsort"))
{
    ARGSORT_SUBCASE( case7, array, axis );
    ARGSORT_SUBCASE( case7, array_a, axis );
    ARGSORT_SUBCASE( case7, array_f, axis );
    ARGSORT_SUBCASE( case7, array_h, axis );
    ARGSORT_SUBCASE( case7, array_d, axis );
}

TEST_CASE("argsort(case8)" * doctest::test_suite("view::argsort"))
{
    ARGSORT_SUBCASE( case8, array, axis );
    ARGSORT_SUBCASE( case8, array_a, axis );
    ARGSORT_SUBCASE( case8, array_f, axis );
    ARGSORT_SUBCASE( case8, array_h, axis );
    ARGSORT_SUBCASE( case8, array_d, axis );
}


TEST_CASE("argsort(case9)" * doctest::test_suite("view::argsort"))
{
    ARGSORT_SUBCASE( case9, array, axis );
    ARGSORT_SUBCASE( case9, array_a, axis );
    ARGSORT_SUBCASE( case9, array_f, axis );
    ARGSORT_SUBCASE( case9, array_h, axis );
    ARGSORT_SUBCASE( case9, array_d, axis );
}

TEST_CASE("argsort(case10)" * doctest::test_suite("view::argsort"))
{
    ARGSORT_SUBCASE( case10, array, axis );
    ARGSORT_SUBCASE( case10, array_a, axis );
    ARGSORT_SUBCASE( case10, array_f, axis );
    ARGSORT_SUBCASE( case10, array_h, axis );
    ARGSORT_SUBCASE( case10, array_d, axis );
}