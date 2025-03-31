#include "nmtools/index/pooling.hpp"
#include "nmtools/array/pooling.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/utility/apply_isequal.hpp"
#include "nmtools/utility/apply_to_string.hpp"

#include "nmtools/testing/data/array/pooling.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define SHAPE_POOL2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, shape_pool2d, case_name); \
    using namespace args; \
    auto result = nmtools::index::shape_pool2d(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define CONSTEXPR_SHAPE_POOL2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, constexpr_shape_pool2d, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::index::shape_pool2d(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define POOL_PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, pool_pad, case_name); \
    using namespace args; \
    auto result = nmtools::index::pool_pad(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

TEST_CASE("pool_pad(case1)" * doctest::test_suite("index::pool_pad"))
{
    POOL_PAD_SUBCASE( case1, src_shape, kernel_size, stride );
    POOL_PAD_SUBCASE( case1, src_shape_a, kernel_size_a, stride_a );
    POOL_PAD_SUBCASE( case1, src_shape_f, kernel_size_f, stride_f );
    POOL_PAD_SUBCASE( case1, src_shape_h, kernel_size_h, stride_h );
    POOL_PAD_SUBCASE( case1, src_shape_v, kernel_size_v, stride_v );
}

TEST_CASE("pool_pad(case1b)" * doctest::test_suite("index::pool_pad"))
{
    POOL_PAD_SUBCASE( case1b, src_shape, kernel_size, stride );
    POOL_PAD_SUBCASE( case1b, src_shape_a, kernel_size_a, stride_a );
    POOL_PAD_SUBCASE( case1b, src_shape_f, kernel_size_f, stride_f );
    POOL_PAD_SUBCASE( case1b, src_shape_h, kernel_size_h, stride_h );
    POOL_PAD_SUBCASE( case1b, src_shape_v, kernel_size_v, stride_v );
}

TEST_CASE("pool_pad(case1c)" * doctest::test_suite("index::pool_pad"))
{
    POOL_PAD_SUBCASE( case1c, src_shape, kernel_size, stride );
    POOL_PAD_SUBCASE( case1c, src_shape_a, kernel_size_a, stride_a );
    POOL_PAD_SUBCASE( case1c, src_shape_f, kernel_size_f, stride_f );
    POOL_PAD_SUBCASE( case1c, src_shape_h, kernel_size_h, stride_h );
    POOL_PAD_SUBCASE( case1c, src_shape_v, kernel_size_v, stride_v );
}

TEST_CASE("pool_pad(case2)" * doctest::test_suite("index::pool_pad"))
{
    POOL_PAD_SUBCASE( case2, src_shape, kernel_size, stride );
    POOL_PAD_SUBCASE( case2, src_shape_a, kernel_size_a, stride_a );
    POOL_PAD_SUBCASE( case2, src_shape_f, kernel_size_f, stride_f );
    POOL_PAD_SUBCASE( case2, src_shape_h, kernel_size_h, stride_h );
    POOL_PAD_SUBCASE( case2, src_shape_v, kernel_size_v, stride_v );
}

TEST_CASE("pool_pad(case3)" * doctest::test_suite("index::pool_pad"))
{
    POOL_PAD_SUBCASE( case3, src_shape, kernel_size, stride );
    POOL_PAD_SUBCASE( case3, src_shape_a, kernel_size_a, stride_a );
    POOL_PAD_SUBCASE( case3, src_shape_f, kernel_size_f, stride_f );
    POOL_PAD_SUBCASE( case3, src_shape_h, kernel_size_h, stride_h );
    POOL_PAD_SUBCASE( case3, src_shape_v, kernel_size_v, stride_v );
}

TEST_CASE("pool_pad(case4)" * doctest::test_suite("index::pool_pad"))
{
    POOL_PAD_SUBCASE( case4, src_shape, kernel_size, stride );
    POOL_PAD_SUBCASE( case4, src_shape_a, kernel_size_a, stride_a );
    POOL_PAD_SUBCASE( case4, src_shape_f, kernel_size_f, stride_f );
    POOL_PAD_SUBCASE( case4, src_shape_h, kernel_size_h, stride_h );
    POOL_PAD_SUBCASE( case4, src_shape_v, kernel_size_v, stride_v );
}

TEST_CASE("pool_pad(case10)" * doctest::test_suite("index::pool_pad"))
{
    POOL_PAD_SUBCASE( case10, src_shape, kernel_size, stride );
    POOL_PAD_SUBCASE( case10, src_shape_a, kernel_size_a, stride_a );
    POOL_PAD_SUBCASE( case10, src_shape_f, kernel_size_f, stride_f );
    POOL_PAD_SUBCASE( case10, src_shape_h, kernel_size_h, stride_h );
    POOL_PAD_SUBCASE( case10, src_shape_v, kernel_size_v, stride_v );
}

TEST_CASE("pool_pad(case10b)" * doctest::test_suite("index::pool_pad"))
{
    POOL_PAD_SUBCASE( case10b, src_shape, kernel_size, stride );
    POOL_PAD_SUBCASE( case10b, src_shape_a, kernel_size_a, stride_a );
    POOL_PAD_SUBCASE( case10b, src_shape_f, kernel_size_f, stride_f );
    POOL_PAD_SUBCASE( case10b, src_shape_h, kernel_size_h, stride_h );
    POOL_PAD_SUBCASE( case10b, src_shape_v, kernel_size_v, stride_v );
}

TEST_CASE("pool_pad(case10c)" * doctest::test_suite("index::pool_pad"))
{
    POOL_PAD_SUBCASE( case10c, src_shape, kernel_size, stride );
    POOL_PAD_SUBCASE( case10c, src_shape_a, kernel_size_a, stride_a );
    POOL_PAD_SUBCASE( case10c, src_shape_f, kernel_size_f, stride_f );
    POOL_PAD_SUBCASE( case10c, src_shape_h, kernel_size_h, stride_h );
    POOL_PAD_SUBCASE( case10c, src_shape_v, kernel_size_v, stride_v );
}

TEST_CASE("pool_pad(case11)" * doctest::test_suite("index::pool_pad"))
{
    POOL_PAD_SUBCASE( case11, src_shape, kernel_size, stride );
    POOL_PAD_SUBCASE( case11, src_shape_a, kernel_size_a, stride_a );
    POOL_PAD_SUBCASE( case11, src_shape_f, kernel_size_f, stride_f );
    POOL_PAD_SUBCASE( case11, src_shape_h, kernel_size_h, stride_h );
    POOL_PAD_SUBCASE( case11, src_shape_v, kernel_size_v, stride_v );
}

TEST_CASE("pool_pad(case12)" * doctest::test_suite("index::pool_pad"))
{
    POOL_PAD_SUBCASE( case12, src_shape, kernel_size, stride );
    POOL_PAD_SUBCASE( case12, src_shape_a, kernel_size_a, stride_a );
    POOL_PAD_SUBCASE( case12, src_shape_f, kernel_size_f, stride_f );
    POOL_PAD_SUBCASE( case12, src_shape_h, kernel_size_h, stride_h );
    POOL_PAD_SUBCASE( case12, src_shape_v, kernel_size_v, stride_v );
}

TEST_CASE("shape_pool2d(case1)" * doctest::test_suite("index"))
{
    SHAPE_POOL2D_SUBCASE( case1, shape, kernel_size, stride, ceil_mode );
    SHAPE_POOL2D_SUBCASE( case1, shape_a, kernel_size_a, stride_a, ceil_mode );
    SHAPE_POOL2D_SUBCASE( case1, shape_v, kernel_size_v, stride_v, ceil_mode );
    SHAPE_POOL2D_SUBCASE( case1, shape_f, kernel_size_f, stride_f, ceil_mode );
    SHAPE_POOL2D_SUBCASE( case1, shape_h, kernel_size_h, stride_h, ceil_mode );

    static_assert( nm::meta::is_constant_index_v<decltype(nm::True)> );
    static_assert( nm::meta::to_value_v<decltype(nm::True)> );
    SHAPE_POOL2D_SUBCASE( case1, shape_ct, kernel_size_ct, stride_ct, ceil_mode_ct );
}

TEST_CASE("shape_pool2d(case2)" * doctest::test_suite("index"))
{
    SHAPE_POOL2D_SUBCASE( case2, shape, kernel_size, stride, ceil_mode );
    SHAPE_POOL2D_SUBCASE( case2, shape_a, kernel_size_a, stride_a, ceil_mode );
    SHAPE_POOL2D_SUBCASE( case2, shape_v, kernel_size_v, stride_v, ceil_mode );
    SHAPE_POOL2D_SUBCASE( case2, shape_f, kernel_size_f, stride_f, ceil_mode );
    SHAPE_POOL2D_SUBCASE( case2, shape_h, kernel_size_h, stride_h, ceil_mode );

    SHAPE_POOL2D_SUBCASE( case2, shape_ct, kernel_size_ct, stride_ct, ceil_mode_ct );
}

TEST_CASE("shape_pool2d(case3)" * doctest::test_suite("index"))
{
    SHAPE_POOL2D_SUBCASE( case3, shape, kernel_size, stride );
    SHAPE_POOL2D_SUBCASE( case3, shape_a, kernel_size_a, stride_a );
    SHAPE_POOL2D_SUBCASE( case3, shape_v, kernel_size_v, stride_v );
    SHAPE_POOL2D_SUBCASE( case3, shape_f, kernel_size_f, stride_f );
    SHAPE_POOL2D_SUBCASE( case3, shape_h, kernel_size_h, stride_h );
}

TEST_CASE("shape_pool2d(case4)" * doctest::test_suite("index"))
{
    SHAPE_POOL2D_SUBCASE( case4, shape, kernel_size, stride );
    SHAPE_POOL2D_SUBCASE( case4, shape_a, kernel_size_a, stride_a );
    SHAPE_POOL2D_SUBCASE( case4, shape_v, kernel_size_v, stride_v );
    SHAPE_POOL2D_SUBCASE( case4, shape_f, kernel_size_f, stride_f );
    SHAPE_POOL2D_SUBCASE( case4, shape_h, kernel_size_h, stride_h );
}

TEST_CASE("shape_pool2d(case5)" * doctest::test_suite("index"))
{
    SHAPE_POOL2D_SUBCASE( case5, shape, kernel_size, stride );
    SHAPE_POOL2D_SUBCASE( case5, shape_a, kernel_size_a, stride_a );
    SHAPE_POOL2D_SUBCASE( case5, shape_v, kernel_size_v, stride_v );
    SHAPE_POOL2D_SUBCASE( case5, shape_f, kernel_size_f, stride_f );
    SHAPE_POOL2D_SUBCASE( case5, shape_h, kernel_size_h, stride_h );
}

TEST_CASE("shape_pool2d(case6)" * doctest::test_suite("index"))
{
    SHAPE_POOL2D_SUBCASE( case6, shape, kernel_size, stride );
    SHAPE_POOL2D_SUBCASE( case6, shape_a, kernel_size_a, stride_a );
    SHAPE_POOL2D_SUBCASE( case6, shape_v, kernel_size_v, stride_v );
    SHAPE_POOL2D_SUBCASE( case6, shape_f, kernel_size_f, stride_f );
    SHAPE_POOL2D_SUBCASE( case6, shape_h, kernel_size_h, stride_h );
}

TEST_CASE("shape_pool2d(case1)" * doctest::test_suite("index::constexpr_shape_pool2d"))
{
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case1, shape, kernel_size, stride, ceil_mode );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case1, shape_a, kernel_size_a, stride_a, ceil_mode );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case1, shape_f, kernel_size_f, stride_f, ceil_mode );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case1, shape_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("shape_pool2d(case2)" * doctest::test_suite("index::constexpr_shape_pool2d"))
{
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case2, shape, kernel_size, stride, ceil_mode );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case2, shape_a, kernel_size_a, stride_a, ceil_mode );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case2, shape_f, kernel_size_f, stride_f, ceil_mode );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case2, shape_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("shape_pool2d(case3)" * doctest::test_suite("index::constexpr_shape_pool2d"))
{
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case3, shape, kernel_size, stride );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case3, shape_a, kernel_size_a, stride_a );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case3, shape_f, kernel_size_f, stride_f );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case3, shape_h, kernel_size_h, stride_h );
}

TEST_CASE("shape_pool2d(case4)" * doctest::test_suite("index::constexpr_shape_pool2d"))
{
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case4, shape, kernel_size, stride );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case4, shape_a, kernel_size_a, stride_a );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case4, shape_f, kernel_size_f, stride_f );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case4, shape_h, kernel_size_h, stride_h );
}

TEST_CASE("shape_pool2d(case5)" * doctest::test_suite("index::constexpr_shape_pool2d"))
{
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case5, shape, kernel_size, stride );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case5, shape_a, kernel_size_a, stride_a );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case5, shape_f, kernel_size_f, stride_f );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case5, shape_h, kernel_size_h, stride_h );
}

TEST_CASE("shape_pool2d(case6)" * doctest::test_suite("index::constexpr_shape_pool2d"))
{
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case6, shape, kernel_size, stride );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case6, shape_a, kernel_size_a, stride_a );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case6, shape_f, kernel_size_f, stride_f );
    CONSTEXPR_SHAPE_POOL2D_SUBCASE( case6, shape_h, kernel_size_h, stride_h );
}

#define RUN_slice_pool2d_impl(...) \
nm::index::slice_pool2d(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs slice_pool2d fn to callable lambda
#define RUN_slice_pool2d(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("slice_pool2d-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_slice_pool2d_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_slice_pool2d(case_name, ...) \
RUN_slice_pool2d_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define APPLY_STRINGIFY(array) \
nmtools::utils::apply_to_string(array)

#define SLICE_POOL2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, slice_pool2d, case_name); \
    using namespace args; \
    auto result = RUN_slice_pool2d(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_APPLY_EQUAL( result, expect::result ); \
}

TEST_CASE("slice_pool2d(case1)" * doctest::test_suite("index::slice_pool2d"))
{
    SLICE_POOL2D_SUBCASE( case1, indices, shape, kernel_size, stride, ceil_mode );
    SLICE_POOL2D_SUBCASE( case1, indices, shape_a, kernel_size_a, stride_a, ceil_mode );
    SLICE_POOL2D_SUBCASE( case1, indices, shape_v, kernel_size_v, stride_v, ceil_mode );
    SLICE_POOL2D_SUBCASE( case1, indices, shape_f, kernel_size_f, stride_f, ceil_mode );
    SLICE_POOL2D_SUBCASE( case1, indices, shape_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("slice_pool2d(case2)" * doctest::test_suite("index::slice_pool2d"))
{
    SLICE_POOL2D_SUBCASE( case2, indices, shape, kernel_size, stride, ceil_mode );
    SLICE_POOL2D_SUBCASE( case2, indices, shape_a, kernel_size_a, stride_a, ceil_mode );
    SLICE_POOL2D_SUBCASE( case2, indices, shape_v, kernel_size_v, stride_v, ceil_mode );
    SLICE_POOL2D_SUBCASE( case2, indices, shape_f, kernel_size_f, stride_f, ceil_mode );
    SLICE_POOL2D_SUBCASE( case2, indices, shape_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("slice_pool2d(case3)" * doctest::test_suite("index::slice_pool2d"))
{
    SLICE_POOL2D_SUBCASE( case3, indices, shape, kernel_size, stride, ceil_mode );
    SLICE_POOL2D_SUBCASE( case3, indices, shape_a, kernel_size_a, stride_a, ceil_mode );
    SLICE_POOL2D_SUBCASE( case3, indices, shape_v, kernel_size_v, stride_v, ceil_mode );
    SLICE_POOL2D_SUBCASE( case3, indices, shape_f, kernel_size_f, stride_f, ceil_mode );
    SLICE_POOL2D_SUBCASE( case3, indices, shape_h, kernel_size_h, stride_h, ceil_mode );
}

TEST_CASE("slice_pool2d(case4)" * doctest::test_suite("index::slice_pool2d"))
{
    SLICE_POOL2D_SUBCASE( case4, indices, shape, kernel_size, stride, ceil_mode );
    SLICE_POOL2D_SUBCASE( case4, indices, shape_a, kernel_size_a, stride_a, ceil_mode );
    SLICE_POOL2D_SUBCASE( case4, indices, shape_v, kernel_size_v, stride_v, ceil_mode );
    SLICE_POOL2D_SUBCASE( case4, indices, shape_f, kernel_size_f, stride_f, ceil_mode );
    SLICE_POOL2D_SUBCASE( case4, indices, shape_h, kernel_size_h, stride_h, ceil_mode );
}