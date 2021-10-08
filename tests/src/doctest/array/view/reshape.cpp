#include "nmtools/array/view/reshape.hpp"
#include "nmtools/testing/data/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

#define RUN_impl(...) \
nm::view::reshape(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reshape fn to callable lambda
#define RUN_reshape(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reshape-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reshape(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define RESHAPE_SUBCASE(case_name, array, newshape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(reshape, case_name) \
    auto array_ref = RUN_reshape(case_name, args::array, args::newshape); \
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("reshape(raw)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE( case1, array, newshape_a );
    RESHAPE_SUBCASE( case1, array, newshape_v );
    RESHAPE_SUBCASE( case1, array, newshape_t );
    RESHAPE_SUBCASE( case1, array, newshape_ct );

    RESHAPE_SUBCASE( case2, array, newshape_a );
    RESHAPE_SUBCASE( case2, array, newshape_v );
    RESHAPE_SUBCASE( case2, array, newshape_t );
    RESHAPE_SUBCASE( case2, array, newshape_ct );

    RESHAPE_SUBCASE( case3, array, newshape_a );
    RESHAPE_SUBCASE( case3, array, newshape_v );
    RESHAPE_SUBCASE( case3, array, newshape_t );
    RESHAPE_SUBCASE( case3, array, newshape_ct );
}

TEST_CASE("reshape(array)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE( case1, array_a, newshape_a );
    RESHAPE_SUBCASE( case1, array_a, newshape_v );
    RESHAPE_SUBCASE( case1, array_a, newshape_t );
    RESHAPE_SUBCASE( case1, array_a, newshape_ct );

    RESHAPE_SUBCASE( case2, array_a, newshape_a );
    RESHAPE_SUBCASE( case2, array_a, newshape_v );
    RESHAPE_SUBCASE( case2, array_a, newshape_t );
    RESHAPE_SUBCASE( case2, array_a, newshape_ct );

    RESHAPE_SUBCASE( case3, array_a, newshape_a );
    RESHAPE_SUBCASE( case3, array_a, newshape_v );
    RESHAPE_SUBCASE( case3, array_a, newshape_t );
    RESHAPE_SUBCASE( case3, array_a, newshape_ct );
}

TEST_CASE("reshape(fixed_ndarray)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE( case1, array_f, newshape_a );
    RESHAPE_SUBCASE( case1, array_f, newshape_v );
    RESHAPE_SUBCASE( case1, array_f, newshape_t );
    RESHAPE_SUBCASE( case1, array_f, newshape_ct );

    RESHAPE_SUBCASE( case2, array_f, newshape_a );
    RESHAPE_SUBCASE( case2, array_f, newshape_v );
    RESHAPE_SUBCASE( case2, array_f, newshape_t );
    RESHAPE_SUBCASE( case2, array_f, newshape_ct );

    RESHAPE_SUBCASE( case3, array_f, newshape_a );
    RESHAPE_SUBCASE( case3, array_f, newshape_v );
    RESHAPE_SUBCASE( case3, array_f, newshape_t );
    RESHAPE_SUBCASE( case3, array_f, newshape_ct );
}

TEST_CASE("reshape(vector)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE( case1, array_v, newshape_a );
    RESHAPE_SUBCASE( case1, array_v, newshape_v );
    RESHAPE_SUBCASE( case1, array_v, newshape_t );
    RESHAPE_SUBCASE( case1, array_v, newshape_ct );

    RESHAPE_SUBCASE( case2, array_v, newshape_a );
    RESHAPE_SUBCASE( case2, array_v, newshape_v );
    RESHAPE_SUBCASE( case2, array_v, newshape_t );
    RESHAPE_SUBCASE( case2, array_v, newshape_ct );

    RESHAPE_SUBCASE( case3, array_v, newshape_a );
    RESHAPE_SUBCASE( case3, array_v, newshape_v );
    RESHAPE_SUBCASE( case3, array_v, newshape_t );
    RESHAPE_SUBCASE( case3, array_v, newshape_ct );
}

TEST_CASE("reshape(dynamic_ndarray)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE( case1, array_d, newshape_a );
    RESHAPE_SUBCASE( case1, array_d, newshape_v );
    RESHAPE_SUBCASE( case1, array_d, newshape_t );
    RESHAPE_SUBCASE( case1, array_d, newshape_ct );

    RESHAPE_SUBCASE( case2, array_d, newshape_a );
    RESHAPE_SUBCASE( case2, array_d, newshape_v );
    RESHAPE_SUBCASE( case2, array_d, newshape_t );
    RESHAPE_SUBCASE( case2, array_d, newshape_ct );

    RESHAPE_SUBCASE( case3, array_d, newshape_a );
    RESHAPE_SUBCASE( case3, array_d, newshape_v );
    RESHAPE_SUBCASE( case3, array_d, newshape_t );
    RESHAPE_SUBCASE( case3, array_d, newshape_ct );
}

TEST_CASE("reshape(hybrid_ndarray)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE( case1, array_h, newshape_a );
    RESHAPE_SUBCASE( case1, array_h, newshape_v );
    RESHAPE_SUBCASE( case1, array_h, newshape_t );
    RESHAPE_SUBCASE( case1, array_h, newshape_ct );

    RESHAPE_SUBCASE( case2, array_h, newshape_a );
    RESHAPE_SUBCASE( case2, array_h, newshape_v );
    RESHAPE_SUBCASE( case2, array_h, newshape_t );
    RESHAPE_SUBCASE( case2, array_h, newshape_ct );

    RESHAPE_SUBCASE( case3, array_h, newshape_a );
    RESHAPE_SUBCASE( case3, array_h, newshape_v );
    RESHAPE_SUBCASE( case3, array_h, newshape_t );
    RESHAPE_SUBCASE( case3, array_h, newshape_ct );
}