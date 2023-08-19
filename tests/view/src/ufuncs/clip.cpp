#include "nmtools/array/view/ufuncs/clip.hpp"
#include "nmtools/testing/data/array/clip.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_clip_impl(...) \
nm::view::clip(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs clip fn to callable lambda
#define RUN_clip(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("clip-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_clip_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_clip(case_name, ...) \
RUN_clip_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CLIP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, clip, case_name); \
    using namespace args; \
    auto result = RUN_clip(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("clip(case1)" * doctest::test_suite("view::clip"))
{
    CLIP_SUBCASE( case1,   a,   amin,   amax);
    CLIP_SUBCASE( case1, a_a, amin_a, amax_a);
    CLIP_SUBCASE( case1, a_f, amin_f, amax_f);
    CLIP_SUBCASE( case1, a_d, amin_d, amax_d);
    CLIP_SUBCASE( case1, a_h, amin_h, amax_h);
}

TEST_CASE("clip(case2)" * doctest::test_suite("view::clip"))
{
    CLIP_SUBCASE( case2,   a,   amin,   amax);
    CLIP_SUBCASE( case2, a_a, amin_a, amax_a);
    CLIP_SUBCASE( case2, a_f, amin_f, amax_f);
    CLIP_SUBCASE( case2, a_d, amin_d, amax_d);
    CLIP_SUBCASE( case2, a_h, amin_h, amax_h);
}

TEST_CASE("clip(case3)" * doctest::test_suite("view::clip"))
{
    CLIP_SUBCASE( case3,   a,   amin, amax);
    CLIP_SUBCASE( case3, a_a, amin_a, amax);
    CLIP_SUBCASE( case3, a_f, amin_f, amax);
    CLIP_SUBCASE( case3, a_d, amin_d, amax);
    CLIP_SUBCASE( case3, a_h, amin_h, amax);
}

namespace meta = nmtools::meta;

TEST_CASE("clip(traits)" * doctest::test_suite("view::clip"))
{
    SUBCASE("is_ndarray")
    {
        auto array = nmtools_list{1,2,3};
        auto amin  = nmtools_list{0,0,0};
        auto amax  = nmtools_list{3,3,3};
        auto view  = nm::view::clip(array,amin,amax);
        using view_t = decltype(view);
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
    }
    SUBCASE("is_hybrid_ndarray")
    {
        {
            auto array = na::hybrid_ndarray({1,2,3});
            auto amin  = na::hybrid_ndarray({0,0,0});
            auto amax  = na::hybrid_ndarray({3,3,3});
            auto view  = nm::view::clip(array,amin,amax);
            using view_t = decltype(view);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
    }
}

#define CLIP_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_clip(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

// TODO: fix
#if 0
TEST_CASE("clip(fixed_shape)" * doctest::test_suite("view::clip"))
{
    {
        int A[1][3] = {{1,2,3}};
        int B[3][1] = {{4},{5},{6}};
        int C[3][1][3] = {{{1,2,3}},{{4,5,6}},{{7,8,9}}};
        constexpr auto expected_shape = nmtools_array{3,3,3};
        CLIP_FIXED_SHAPE_SUBCASE( raw, expected_shape, A, B, C );
    }
    {
        auto A = nmtools_array{1,2,3};
        auto B = nmtools_array{nmtools_array{4,5,6},nmtools_array{1,2,3}};
        auto C = nmtools_array<nmtools_array<int,1>,2>{{{7},{8}}};
        constexpr auto expected_shape = nmtools_array{2,3};
        CLIP_FIXED_SHAPE_SUBCASE( array, expected_shape, A, B, C );
    }
    {
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{{1,2,3},{4,5,6}}};
        auto C = na::fixed_ndarray{{{{1,2,3}},{{4,5,6}},{{7,8,9}}}};
        constexpr auto expected_shape = nmtools_array{3,2,3};
        CLIP_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A, B, C );
    }
}
#endif