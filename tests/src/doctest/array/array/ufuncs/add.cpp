#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

using nm::None;
using nm::False;
using nm::True;

#define RUN_add_impl(...) \
na::add(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs add fn to callable lambda
#define RUN_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("add-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_add(case_name, ...) \
RUN_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, add, case_name); \
    using namespace args; \
    auto result = RUN_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("add(case1)" * doctest::test_suite("array::add"))
{
    auto context = None;

    ADD_SUBCASE( case1,   a,   b, context );
    ADD_SUBCASE( case1, a_a, b_a, context );
    // ADD_SUBCASE( case1, a_v, b_v, context );
    ADD_SUBCASE( case1, a_f, b_f, context );
    ADD_SUBCASE( case1, a_d, b_d, context );
    ADD_SUBCASE( case1, a_h, b_h, context );

    auto output  = meta::as_value<int[3][3]>{};
    ADD_SUBCASE( case1,   a,   b, context, output );
    ADD_SUBCASE( case1, a_a, b_a, context, output );
    // ADD_SUBCASE( case1, a_v, b_v, context, output );
    ADD_SUBCASE( case1, a_f, b_f, context, output );
    ADD_SUBCASE( case1, a_d, b_d, context, output );
    ADD_SUBCASE( case1, a_h, b_h, context, output );
}

TEST_CASE("add(case2)" * doctest::test_suite("array::add"))
{
    auto context = None;

    ADD_SUBCASE( case2,   a, b, context );
    ADD_SUBCASE( case2, a_a, b, context );
    // ADD_SUBCASE( case2, a_v, b, context );
    ADD_SUBCASE( case2, a_f, b, context );
    ADD_SUBCASE( case2, a_d, b, context );
    ADD_SUBCASE( case2, a_h, b, context );

    auto output  = meta::as_value<int[3][3]>{};
    ADD_SUBCASE( case2,   a, b, context, output );
    ADD_SUBCASE( case2, a_a, b, context, output );
    // ADD_SUBCASE( case2, a_v, b, context, output );
    ADD_SUBCASE( case2, a_f, b, context, output );
    ADD_SUBCASE( case2, a_d, b, context, output );
    ADD_SUBCASE( case2, a_h, b, context, output );
}

TEST_CASE("add(case3)" * doctest::test_suite("array::add"))
{
    ADD_SUBCASE(case3, a, b);
}

TEST_CASE("add(case4)" * doctest::test_suite("array::add"))
{
    ADD_SUBCASE(case4, a, b);
    ADD_SUBCASE(case4, a_a, b);
    ADD_SUBCASE(case4, a_f, b);
    ADD_SUBCASE(case4, a_d, b);
    ADD_SUBCASE(case4, a_h, b);
}

// skip constexpr test for emscripten
// NOTE: temporarily disable constexpr test,
// latest changes to support view composition makes it not possible for the current implementaion,
// gcc complains about ref wrapper to broadcast to can't be used in constexpr context
// possible fixes are don't take pointer for evaluation
// TODO: fixe constexpr support
// #if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__) && !defined(__arm__) && !defined(__MINGW32__)
// TEST_CASE("add(constexpr)"  * doctest::test_suite("array::add"))
// {
//     NMTOOLS_TESTING_DECLARE_NS(view, constexpr_add, case1);
//     constexpr auto output = meta::as_value<int[3][3]>{};
//     constexpr auto result = na::add(args::a,args::b,None,output);
//     NMTOOLS_STATIC_ASSERT_CLOSE( result, expect::result ); 
// }
// #endif

#define RUN_reduce_add_impl(...) \
na::fn::add::reduce(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs add.reduce fn to callable lambda
#define RUN_reduce_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("add.reduce-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_add(case_name, ...) \
RUN_reduce_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_add, case_name); \
    using namespace args; \
    auto result = RUN_reduce_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("add.reduce(case1)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case1,   a, axis );
    REDUCE_ADD_SUBCASE( case1, a_a, axis );
    // REDUCE_ADD_SUBCASE( case1, a_v, axis );
    REDUCE_ADD_SUBCASE( case1, a_f, axis );
    REDUCE_ADD_SUBCASE( case1, a_h, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // REDUCE_ADD_SUBCASE( case1, a_d, axis );

    /* array, axis, dtype, initial, keepdims, context, output */
    REDUCE_ADD_SUBCASE( case1,   a, axis, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case1, a_a, axis, None, None, False, context, output );
    // REDUCE_ADD_SUBCASE( case1, a_v, axis, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case1, a_f, axis, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case1, a_h, axis, None, None, False, context, output );
}

TEST_CASE("add.reduce(case2)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case2,   a, axis );
    REDUCE_ADD_SUBCASE( case2, a_a, axis );
    // REDUCE_ADD_SUBCASE( case2, a_v, axis );
    REDUCE_ADD_SUBCASE( case2, a_f, axis );
    REDUCE_ADD_SUBCASE( case2, a_h, axis );

                        /* array, axis, dtype, initial, keepdims, context, output */
    REDUCE_ADD_SUBCASE( case2,   a, axis, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case2, a_a, axis, None, None, False, context, output );
    // REDUCE_ADD_SUBCASE( case2, a_v, axis, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case2, a_f, axis, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case2, a_h, axis, None, None, False, context, output );
}

TEST_CASE("add.reduce(case3)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case3,   a, axis );
    REDUCE_ADD_SUBCASE( case3, a_a, axis );
    // REDUCE_ADD_SUBCASE( case3, a_v, axis );
    REDUCE_ADD_SUBCASE( case3, a_f, axis );
    REDUCE_ADD_SUBCASE( case3, a_h, axis );

    REDUCE_ADD_SUBCASE( case3,   a, axis, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case3, a_a, axis, None, None, False, context, output );
    // REDUCE_ADD_SUBCASE( case3, a_v, axis, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case3, a_f, axis, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case3, a_h, axis, None, None, False, context, output );
}

TEST_CASE("add.reduce(case4)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case4,   a,   axis );
    REDUCE_ADD_SUBCASE( case4, a_a, axis_a );
    // REDUCE_ADD_SUBCASE( case4, a_v, axis_v );
    REDUCE_ADD_SUBCASE( case4, a_f, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_h, axis_h );

    REDUCE_ADD_SUBCASE( case4,   a,   axis, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case4, a_a, axis_a, None, None, False, context, output );
    // REDUCE_ADD_SUBCASE( case4, a_v, axis_v, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case4, a_f, axis_f, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case4, a_h, axis_h, None, None, False, context, output );
}

TEST_CASE("add.reduce(case5)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case5,   a,   axis );
    REDUCE_ADD_SUBCASE( case5, a_a, axis_a );
    // REDUCE_ADD_SUBCASE( case5, a_v, axis_v );
    REDUCE_ADD_SUBCASE( case5, a_f, axis_f );
    REDUCE_ADD_SUBCASE( case5, a_h, axis_h );

    REDUCE_ADD_SUBCASE( case5,   a,   axis, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case5, a_a, axis_a, None, None, False, context, output );
    // REDUCE_ADD_SUBCASE( case5, a_v, axis_v, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case5, a_f, axis_f, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case5, a_h, axis_h, None, None, False, context, output );
}

TEST_CASE("add.reduce(case6)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case6,   a,   axis );
    REDUCE_ADD_SUBCASE( case6, a_a, axis_a );
    // REDUCE_ADD_SUBCASE( case6, a_v, axis_v );
    REDUCE_ADD_SUBCASE( case6, a_f, axis_f );
    REDUCE_ADD_SUBCASE( case6, a_h, axis_h );

    REDUCE_ADD_SUBCASE( case6,   a,   axis, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case6, a_a, axis_a, None, None, False, context, output );
    // REDUCE_ADD_SUBCASE( case6, a_v, axis_v, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case6, a_f, axis_f, None, None, False, context, output );
    REDUCE_ADD_SUBCASE( case6, a_h, axis_h, None, None, False, context, output );
}

TEST_CASE("add.reduce(case7)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case7,   a, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_a, axis, dtype );
    // REDUCE_ADD_SUBCASE( case7, a_v, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_f, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_h, axis, dtype );

    REDUCE_ADD_SUBCASE( case7,   a, axis, dtype, None, False, context, output );
    REDUCE_ADD_SUBCASE( case7, a_a, axis, dtype, None, False, context, output );
    // REDUCE_ADD_SUBCASE( case7, a_v, axis, dtype, None, False, context, output );
    REDUCE_ADD_SUBCASE( case7, a_f, axis, dtype, None, False, context, output );
    REDUCE_ADD_SUBCASE( case7, a_h, axis, dtype, None, False, context, output );
}

TEST_CASE("add.reduce(case8)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case8,   a, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_a, axis, dtype, initial );
    // REDUCE_ADD_SUBCASE( case8, a_v, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_f, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_h, axis, dtype, initial );

    REDUCE_ADD_SUBCASE( case8,   a, axis, dtype, initial, False, context, output );
    REDUCE_ADD_SUBCASE( case8, a_a, axis, dtype, initial, False, context, output );
    // REDUCE_ADD_SUBCASE( case8, a_v, axis, dtype, initial, False, context, output );
    REDUCE_ADD_SUBCASE( case8, a_f, axis, dtype, initial, False, context, output );
    REDUCE_ADD_SUBCASE( case8, a_h, axis, dtype, initial, False, context, output );
}

TEST_CASE("add.reduce(case9)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    // REDUCE_ADD_SUBCASE( case9, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case9,   a, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case9, a_a, axis, dtype, initial, keepdims, context, output );
    // REDUCE_ADD_SUBCASE( case9, a_v, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case9, a_f, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case9, a_h, axis, dtype, initial, keepdims, context, output );
}

TEST_CASE("add.reduce(case10)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    // REDUCE_ADD_SUBCASE( case10, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case10,   a, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case10, a_a, axis, dtype, initial, keepdims, context, output );
    // REDUCE_ADD_SUBCASE( case10, a_v, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case10, a_f, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case10, a_h, axis, dtype, initial, keepdims, context, output );
}

TEST_CASE("add.reduce(case11)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    // REDUCE_ADD_SUBCASE( case11, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case11,   a, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case11, a_a, axis, dtype, initial, keepdims, context, output );
    // REDUCE_ADD_SUBCASE( case11, a_v, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case11, a_f, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case11, a_h, axis, dtype, initial, keepdims, context, output );
}

TEST_CASE("add.reduce(case12)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    // REDUCE_ADD_SUBCASE( case12, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case12,   a, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case12, a_a, axis, dtype, initial, keepdims, context, output );
    // REDUCE_ADD_SUBCASE( case12, a_v, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case12, a_f, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case12, a_h, axis, dtype, initial, keepdims, context, output );
}

TEST_CASE("add.reduce(case13)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case13,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_a, axis, dtype, initial, keepdims );
    // REDUCE_ADD_SUBCASE( case13, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_h, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case13,   a, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case13, a_a, axis, dtype, initial, keepdims, context, output );
    // REDUCE_ADD_SUBCASE( case13, a_v, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case13, a_f, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case13, a_h, axis, dtype, initial, keepdims, context, output );
}

TEST_CASE("add.reduce(case14)" * doctest::test_suite("array::add.reduce"))
{
    auto context = None;
    using output_t = nm::array::dynamic_ndarray<int>;
    auto output  = meta::as_value_v<output_t>;

    REDUCE_ADD_SUBCASE( case14,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_a, axis, dtype, initial, keepdims );
    // REDUCE_ADD_SUBCASE( case14, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_h, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case14,   a, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case14, a_a, axis, dtype, initial, keepdims, context, output );
    // REDUCE_ADD_SUBCASE( case14, a_v, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case14, a_f, axis, dtype, initial, keepdims, context, output );
    REDUCE_ADD_SUBCASE( case14, a_h, axis, dtype, initial, keepdims, context, output );
}

TEST_CASE("add.reduce(case15)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case15,   a, axis );
    REDUCE_ADD_SUBCASE( case15, a_a, axis );
    // REDUCE_ADD_SUBCASE( case15, a_v, axis );
    REDUCE_ADD_SUBCASE( case15, a_f, axis );
    REDUCE_ADD_SUBCASE( case15, a_h, axis );
}

TEST_CASE("add.reduce(case16)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case16,   a, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_a, axis, nmtools::None, initial );
    // REDUCE_ADD_SUBCASE( case16, a_v, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_f, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_h, axis, nmtools::None, initial );
}

TEST_CASE("add.reduce(case17)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case17,   a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case17, a_a, axis, nmtools::None, initial, keepdims );
    // REDUCE_ADD_SUBCASE( case17, a_v, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case17, a_f, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case17, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("add.reduce(case18)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case18,   a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_a, axis, nmtools::None, initial, keepdims );
    // REDUCE_ADD_SUBCASE( case18, a_v, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_f, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("add.reduce(case19)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case19,   a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_a, axis, nmtools::None, initial, keepdims );
    // REDUCE_ADD_SUBCASE( case19, a_v, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_f, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("add.reduce(case20)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case20,   a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_a, axis, nmtools::None, initial, keepdims );
    // REDUCE_ADD_SUBCASE( case20, a_v, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_f, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("add.reduce(case21)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case21,   a, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_a, axis, dtype );
    // TODO: remove support for nested std::vector
    // REDUCE_ADD_SUBCASE( case21, a_v, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_f, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_h, axis, dtype );
}

TEST_CASE("add.reduce(case22)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case22,   a, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_a, axis, dtype );
    // TODO: remove support for nested std::vector
    // REDUCE_ADD_SUBCASE( case22, a_v, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_f, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_h, axis, dtype );
}

TEST_CASE("add.reduce(case23)" * doctest::test_suite("array::reduce_add"))
{
    auto dtype   = nmtools::None;
    auto initial = nmtools::None;
    REDUCE_ADD_SUBCASE( case23,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_a, axis, dtype, initial, keepdims );
    // TODO: remove support for nested std::vector
    // REDUCE_ADD_SUBCASE( case23, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("add.reduce(case24)" * doctest::test_suite("array::reduce_add"))
{
    auto dtype   = nmtools::None;
    auto initial = nmtools::None;
    REDUCE_ADD_SUBCASE( case24,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_a, axis, dtype, initial, keepdims );
    // TODO: remove support for nested std::vector
    // REDUCE_ADD_SUBCASE( case24, a_v, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_h, axis, dtype, initial, keepdims );
}

#define RUN_accumulate_add_impl(...) \
na::add.accumulate(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs add.accumulate fn to callable lambda
#define RUN_accumulate_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("add.accumulate-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_add(case_name, ...) \
RUN_accumulate_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_add, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("add.accumulate(case1)" * doctest::test_suite("array::add.accumulate"))
{
    auto context = None;
    auto output  = meta::as_value<int[2][3][2]>{};

    ACCUMULATE_ADD_SUBCASE( case1,   a, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_a, axis );
    // ACCUMULATE_ADD_SUBCASE( case1, a_v, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_f, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_h, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // ACCUMULATE_ADD_SUBCASE( case1, a_d, axis );

    /* array, axis, dtype, context, output */
    ACCUMULATE_ADD_SUBCASE( case1,   a, axis, None, context, output );
    ACCUMULATE_ADD_SUBCASE( case1, a_a, axis, None, context, output );
    // ACCUMULATE_ADD_SUBCASE( case1, a_v, axis, None, context, output );
    ACCUMULATE_ADD_SUBCASE( case1, a_f, axis, None, context, output );
    ACCUMULATE_ADD_SUBCASE( case1, a_h, axis, None, context, output );
}

TEST_CASE("add.accumulate(case2)" * doctest::test_suite("array::add.accumulate"))
{
    auto context = None;
    auto output  = meta::as_value<int[2][3][2]>{};

    ACCUMULATE_ADD_SUBCASE( case2,   a, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_a, axis );
    // ACCUMULATE_ADD_SUBCASE( case2, a_v, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_f, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_h, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // ACCUMULATE_ADD_SUBCASE( case2, a_d, axis );

    ACCUMULATE_ADD_SUBCASE( case2,   a, axis, None, context, output );
    ACCUMULATE_ADD_SUBCASE( case2, a_a, axis, None, context, output );
    // ACCUMULATE_ADD_SUBCASE( case2, a_v, axis, None, context, output );
    ACCUMULATE_ADD_SUBCASE( case2, a_f, axis, None, context, output );
    ACCUMULATE_ADD_SUBCASE( case2, a_h, axis, None, context, output );
}

TEST_CASE("add.accumulate(case3)" * doctest::test_suite("array::add.accumulate"))
{
    auto context = None;
    auto output  = meta::as_value<int[2][3][2]>{};

    ACCUMULATE_ADD_SUBCASE( case3,   a, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_a, axis );
    // ACCUMULATE_ADD_SUBCASE( case3, a_v, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_f, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_h, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // ACCUMULATE_ADD_SUBCASE( case3, a_d, axis );

    ACCUMULATE_ADD_SUBCASE( case3,   a, axis, None, context, output );
    ACCUMULATE_ADD_SUBCASE( case3, a_a, axis, None, context, output );
    // ACCUMULATE_ADD_SUBCASE( case3, a_v, axis, None, context, output );
    ACCUMULATE_ADD_SUBCASE( case3, a_f, axis, None, context, output );
    ACCUMULATE_ADD_SUBCASE( case3, a_h, axis, None, context, output );
}

#define RUN_outer_add_impl(...) \
na::add.outer(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs add.outer fn to callable lambda
#define RUN_outer_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("add.outer-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_add(case_name, ...) \
RUN_outer_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_add, case_name); \
    using namespace args; \
    auto result = RUN_outer_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("add.outer(case1)" * doctest::test_suite("array::add.outer"))
{
    auto context = None;
    auto output  = meta::as_value<int[2][3][3]>{};

    OUTER_ADD_SUBCASE( case1,   a,   b );
    OUTER_ADD_SUBCASE( case1, a_a, b_a );
    // disable nested array for now
    // OUTER_ADD_SUBCASE( case1, a_v, b_v );
    OUTER_ADD_SUBCASE( case1, a_f, b_f );
    OUTER_ADD_SUBCASE( case1, a_d, b_d );
    OUTER_ADD_SUBCASE( case1, a_h, b_h );

    OUTER_ADD_SUBCASE( case1,   a,   b, None, context, output );
    OUTER_ADD_SUBCASE( case1, a_a, b_a, None, context, output );
    // OUTER_ADD_SUBCASE( case1, a_v, b_v, None, context, output );
    OUTER_ADD_SUBCASE( case1, a_f, b_f, None, context, output );
    OUTER_ADD_SUBCASE( case1, a_d, b_d, None, context, output );
    OUTER_ADD_SUBCASE( case1, a_h, b_h, None, context, output );
}