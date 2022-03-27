#include "nmtools/array/view/take_along_axis.hpp"
#include "nmtools/testing/data/array/take_along_axis.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_take_along_axis_impl(...) \
nm::view::take_along_axis(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs take_along_axis fn to callable lambda
#define RUN_take_along_axis(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("take_along_axis-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_take_along_axis_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_take_along_axis(case_name, ...) \
RUN_take_along_axis_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

// TODO: properly deduce ndarray type
#define TAKE_ALONG_AXIS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, take_along_axis, case_name); \
    using namespace args; \
    auto view = RUN_take_along_axis(case_name, __VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(*view), nm::shape(expect::result) ); \
    using element_t = nm::meta::get_element_type_t<nm::meta::remove_cvref_t<decltype(*view)>>; \
    using ndarray_t = na::dynamic_ndarray<element_t>; \
    auto result = static_cast<ndarray_t>(*view); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define TAKE_ALONG_AXIS_META_SUBCASE(case_name, ...) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, take_along_axis, case_name); \
    using namespace args; \
    auto view = RUN_take_along_axis(case_name, __VA_ARGS__); \
    using element_t = nm::meta::get_element_type_t<nm::meta::remove_cvref_t<decltype(*view)>>; \
    using expect_t  = nm::meta::get_element_type_t<decltype(expect::result)>; \
    NMTOOLS_STATIC_CHECK_IS_SAME(element_t, expect_t); \
}

TEST_CASE("take_along_axis(case1)" * doctest::test_suite("view::take_along_axis"))
{
    TAKE_ALONG_AXIS_SUBCASE( case1, array, indices, axis );
    TAKE_ALONG_AXIS_SUBCASE( case1, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case1, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case1, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case1, array_h, indices_h, axis );

    TAKE_ALONG_AXIS_META_SUBCASE( case1, array, indices, axis );
    TAKE_ALONG_AXIS_META_SUBCASE( case1, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_META_SUBCASE( case1, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_META_SUBCASE( case1, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_META_SUBCASE( case1, array_h, indices_h, axis );
}

TEST_CASE("take_along_axis(case2)" * doctest::test_suite("view::take_along_axis"))
{
    TAKE_ALONG_AXIS_SUBCASE( case2, array, indices, axis );
    TAKE_ALONG_AXIS_SUBCASE( case2, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case2, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case2, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case2, array_h, indices_h, axis );
}

TEST_CASE("take_along_axis(case3)" * doctest::test_suite("view::take_along_axis"))
{
    TAKE_ALONG_AXIS_SUBCASE( case3, array, indices, axis );
    TAKE_ALONG_AXIS_SUBCASE( case3, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case3, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case3, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case3, array_h, indices_h, axis );
}

TEST_CASE("take_along_axis(case4)" * doctest::test_suite("view::take_along_axis"))
{
    TAKE_ALONG_AXIS_SUBCASE( case4, array, indices, axis );
    TAKE_ALONG_AXIS_SUBCASE( case4, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case4, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case4, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case4, array_h, indices_h, axis );
}

TEST_CASE("take_along_axis(case5)" * doctest::test_suite("view::take_along_axis"))
{
    TAKE_ALONG_AXIS_SUBCASE( case5, array, indices, axis );
    TAKE_ALONG_AXIS_SUBCASE( case5, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case5, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case5, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case5, array_h, indices_h, axis );
}

TEST_CASE("take_along_axis(case6)" * doctest::test_suite("view::take_along_axis"))
{
    TAKE_ALONG_AXIS_SUBCASE( case6, array, indices, axis );
    TAKE_ALONG_AXIS_SUBCASE( case6, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case6, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case6, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case6, array_h, indices_h, axis );
}

TEST_CASE("take_along_axis(case7)" * doctest::test_suite("view::take_along_axis"))
{
    TAKE_ALONG_AXIS_SUBCASE( case7, array, indices, axis );
    TAKE_ALONG_AXIS_SUBCASE( case7, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case7, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case7, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case7, array_h, indices_h, axis );
    // NOTE: fail at runtime
    // TODO: fix type combination
#if 0
    TAKE_ALONG_AXIS_SUBCASE( case7, array, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case7, array, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case7, array, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case7, array, indices_h, axis );
#endif
}

TEST_CASE("take_along_axis(case8)" * doctest::test_suite("view::take_along_axis"))
{
    TAKE_ALONG_AXIS_SUBCASE( case8, array, indices, axis );
    TAKE_ALONG_AXIS_SUBCASE( case8, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case8, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case8, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case8, array_h, indices_h, axis );

    // NOTE: fail at runtime
    // TODO: fix type combination
#if 0
    TAKE_ALONG_AXIS_SUBCASE( case8, array, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case8, array, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case8, array, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case8, array, indices_h, axis );
#endif
}

TEST_CASE("take_along_axis(case9)" * doctest::test_suite("view::take_along_axis"))
{
    TAKE_ALONG_AXIS_SUBCASE( case9, array, indices, axis );
    TAKE_ALONG_AXIS_SUBCASE( case9, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case9, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case9, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case9, array_h, indices_h, axis );
}

TEST_CASE("take_along_axis(case10)" * doctest::test_suite("view::take_along_axis"))
{
    TAKE_ALONG_AXIS_SUBCASE( case10, array, indices, axis );
    TAKE_ALONG_AXIS_SUBCASE( case10, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case10, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case10, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case10, array_h, indices_h, axis );
}

TEST_CASE("take_along_axis(case11)" * doctest::test_suite("view::take_along_axis"))
{
    TAKE_ALONG_AXIS_SUBCASE( case11, array, indices, axis );
    TAKE_ALONG_AXIS_SUBCASE( case11, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case11, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case11, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case11, array_h, indices_h, axis );
}

TEST_CASE("take_along_axis(case12)" * doctest::test_suite("view::take_along_axis"))
{
    TAKE_ALONG_AXIS_SUBCASE( case12, array, indices, axis );
    TAKE_ALONG_AXIS_SUBCASE( case12, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case12, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case12, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case12, array_h, indices_h, axis );
}

TEST_CASE("take_along_axis(case13)" * doctest::test_suite("view::take_along_axis"))
{
    TAKE_ALONG_AXIS_SUBCASE( case13, array, indices, axis );
    TAKE_ALONG_AXIS_SUBCASE( case13, array_a, indices_a, axis );
    TAKE_ALONG_AXIS_SUBCASE( case13, array_f, indices_f, axis );
    TAKE_ALONG_AXIS_SUBCASE( case13, array_d, indices_d, axis );
    TAKE_ALONG_AXIS_SUBCASE( case13, array_h, indices_h, axis );
}