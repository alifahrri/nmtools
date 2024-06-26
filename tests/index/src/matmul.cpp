#include "nmtools/array/view/matmul.hpp"
#include "nmtools/testing/data/array/matmul.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#include "nmtools/utils/apply_isequal.hpp"

// split for matmul
NMTOOLS_TESTING_DECLARE_CASE(array, split)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int lhs[1] = {2};
        inline int rhs[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = 2;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int lhs[2] = {2,3};
        inline int rhs[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = -2;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int lhs[1] = {2};
        inline int rhs[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = -1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int lhs[2] = {2,3};
        inline int rhs[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto lhs = nmtools_list<int>{};
        inline int rhs[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int lhs[3] = {2,3,2};
        inline auto rhs = nmtools_list<int>{};
    }
}

using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(array, shape_matmul)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int lshape[2] = {3,4};
        inline int rshape[2] = {4,3};
        inline auto lshape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto lshape_cl = nmtools_tuple{"3:[3]"_ct,"4:[4]"_ct};
        inline auto rshape_ct = nmtools_tuple{4_ct,3_ct};
        inline auto rshape_cl = nmtools_tuple{"4:[4]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {3,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int lshape[2] = {4,3};
        inline int rshape[2] = {3,4};
        inline auto lshape_ct = nmtools_tuple{4_ct,3_ct};
        inline auto rshape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto lshape_cl = nmtools_tuple{"4:[4]"_ct,"3:[3]"_ct};
        inline auto rshape_cl = nmtools_tuple{"3:[3]"_ct,"4:[4]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int lshape[2] = {4,1};
        inline int rshape[2] = {1,4};
        inline auto lshape_ct = nmtools_tuple{4_ct,1_ct};
        inline auto rshape_ct = nmtools_tuple{1_ct,4_ct};
        inline auto lshape_cl = nmtools_tuple{"4:[4]"_ct,"1:[1]"_ct};
        inline auto rshape_cl = nmtools_tuple{"1:[1]"_ct,"4:[4]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2] = {4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int lshape[2] = {1,4};
        inline int rshape[2] = {4,1};
        inline auto lshape_ct = nmtools_tuple{1_ct,4_ct};
        inline auto rshape_ct = nmtools_tuple{4_ct,1_ct};
        inline auto lshape_cl = nmtools_tuple{"1:[1]"_ct,"4:[4]"_ct};
        inline auto rshape_cl = nmtools_tuple{"4:[4]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int lshape[2] =   {4,3};
        inline int rshape[3] = {2,3,2};
        inline auto lshape_ct = nmtools_tuple{4_ct,3_ct};
        inline auto rshape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto lshape_cl = nmtools_tuple{"4:[4]"_ct,"3:[3]"_ct};
        inline auto rshape_cl = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {2,4,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int lshape[3] = {2,3,2};
        inline int rshape[2] =   {2,4};
        inline auto lshape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rshape_ct = nmtools_tuple{2_ct,4_ct};
        inline auto lshape_cl = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        inline auto rshape_cl = nmtools_tuple{"2:[2]"_ct,"4:[4]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3] = {2,3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int lshape[4] = {9,5,7,4};
        inline int rshape[4] = {9,5,4,3};
        inline auto lshape_ct = nmtools_tuple{9_ct,5_ct,7_ct,4_ct};
        inline auto rshape_ct = nmtools_tuple{9_ct,5_ct,4_ct,3_ct};
        inline auto lshape_cl = nmtools_tuple{"9:[9]"_ct,"5:[5]"_ct,"7:[7]"_ct,"4:[4]"_ct};
        inline auto rshape_cl = nmtools_tuple{"9:[9]"_ct,"5:[5]"_ct,"4:[4]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[4] = {9,5,7,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int lshape[4] = {1,5,7,4};
        inline int rshape[4] = {9,1,4,3};
        inline auto lshape_ct = nmtools_tuple{1_ct,5_ct,7_ct,4_ct};
        inline auto rshape_ct = nmtools_tuple{9_ct,1_ct,4_ct,3_ct};
        inline auto lshape_cl = nmtools_tuple{"1:[1]"_ct,"5:[5]"_ct,"7:[7]"_ct,"4:[4]"_ct};
        inline auto rshape_cl = nmtools_tuple{"9:[9]"_ct,"1:[1]"_ct,"4:[4]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[4] = {9,5,7,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int lshape[4] = {9,5,7,4};
        inline int rshape[4] = {5,9,4,3};
        inline auto lshape_ct = nmtools_tuple{9_ct,5_ct,7_ct,4_ct};
        inline auto rshape_ct = nmtools_tuple{5_ct,9_ct,4_ct,3_ct};
        inline auto lshape_cl = nmtools_tuple{"9:[9]"_ct,"5:[5]"_ct,"7:[7]"_ct,"4:[4]"_ct};
        inline auto rshape_cl = nmtools_tuple{"5:[5]"_ct,"9:[9]"_ct,"4:[4]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int lshape[3] = {1,4,3};
        inline int rshape[2] = {3,4};
        inline auto lshape_ct = nmtools_tuple{1_ct,4_ct,3_ct};
        inline auto rshape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto lshape_cl = nmtools_tuple{"1:[1]"_ct,"4:[4]"_ct,"3:[3]"_ct};
        inline auto rshape_cl = nmtools_tuple{"3:[3]"_ct,"4:[4]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[3] = {1,4,4};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, matmul)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[2] = {0,0};
        inline int  lshape[2] = {4,3};
        inline int  rshape[2] = {3,4};
        inline int   shape[2] = {4,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto  left = nmtools_tuple{0,nmtools_tuple{None,None}};
        inline auto right = nmtools_tuple{nmtools_tuple{None,None},0};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{0},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{nmtools_tuple{None,None},size_t{0}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[2] = {3,2};
        inline int  lshape[2] = {4,3};
        inline int  rshape[2] = {3,4};
        inline int   shape[2] = {4,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto  left = nmtools_tuple{3,nmtools_tuple{None,None}};
        inline auto right = nmtools_tuple{nmtools_tuple{None,None},2};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{3},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{nmtools_tuple{None,None},size_t{2}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int indices[3] = {0,0,0};
        inline int  lshape[3] = {1,4,3};
        inline int  rshape[2] =   {3,4};
        inline int   shape[3] = {1,4,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto  left = nmtools_tuple{0,0,nmtools_tuple{None,None}};
        inline auto right = nmtools_tuple{nmtools_tuple{None,None},0};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{0},size_t{0},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{nmtools_tuple{None,None},size_t{0}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int indices[3] = {0,3,2};
        inline int  lshape[3] = {1,4,3};
        inline int  rshape[2] =   {3,4};
        inline int   shape[3] = {1,4,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto  left = nmtools_tuple{0,3,nmtools_tuple{None,None}};
        inline auto right = nmtools_tuple{nmtools_tuple{None,None},2};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{0},size_t{3},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{nmtools_tuple{None,None},size_t{2}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int indices[3] = {1,1,0};
        inline int  lshape[2] =   {2,3};
        inline int  rshape[3] = {2,3,2};
        inline int   shape[3] = {2,2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto  left = nmtools_tuple{1,nmtools_tuple{None,None}};
        inline auto right = nmtools_tuple{1,nmtools_tuple{None,None},0};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{1},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{size_t{1},nmtools_tuple{None,None},size_t{0}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int indices[3] = {0,0,0};
        inline int lshape[3]  = {1,4,3};
        inline int rshape[2]  = {3,4};
        inline int shape[3]   = {1,4,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        using all_t = nmtools_tuple<none_t,none_t>;
        inline auto left  = nmtools_tuple{0,0,all_t{}};
        inline auto right = nmtools_tuple{all_t{},0};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{(slice_t)(size_t)0,(slice_t)(size_t)0,(slice_t)all_t{}};
        inline auto right_v = slices_t{(slice_t)all_t{},(slice_t)(size_t)0};
    }
}

#define RUN_split_impl(...) \
nmtools::index::split(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs split fn to callable lambda
#define RUN_split(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("split-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_split_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_split(case_name, ...) \
RUN_split_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SPLIT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, split, case_name); \
    using namespace args; \
    auto result = RUN_split(case_name, __VA_ARGS__); \
    auto lhs = nmtools::get<0>(result); \
    auto rhs = nmtools::get<1>(result); \
    NMTOOLS_ASSERT_EQUAL( lhs, expect::lhs ); \
    NMTOOLS_ASSERT_EQUAL( rhs, expect::rhs ); \
}

TEST_CASE("split(case1)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case1, shape, N );
    SPLIT_SUBCASE( case1, shape_a, N );
    SPLIT_SUBCASE( case1, shape_v, N );
    SPLIT_SUBCASE( case1, shape_f, N );
    SPLIT_SUBCASE( case1, shape_h, N );
}

TEST_CASE("split(case2)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case2, shape, N );
    SPLIT_SUBCASE( case2, shape_a, N );
    SPLIT_SUBCASE( case2, shape_v, N );
    SPLIT_SUBCASE( case2, shape_f, N );
    SPLIT_SUBCASE( case2, shape_h, N );
}

TEST_CASE("split(case3)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case3, shape, N );
    SPLIT_SUBCASE( case3, shape_a, N );
    SPLIT_SUBCASE( case3, shape_v, N );
    SPLIT_SUBCASE( case3, shape_f, N );
    SPLIT_SUBCASE( case3, shape_h, N );
}

TEST_CASE("split(case4)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case4, shape, N );
    SPLIT_SUBCASE( case4, shape_a, N );
    SPLIT_SUBCASE( case4, shape_v, N );
    SPLIT_SUBCASE( case4, shape_f, N );
    SPLIT_SUBCASE( case4, shape_h, N );
}

TEST_CASE("split(case5)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case5, shape, N );
    SPLIT_SUBCASE( case5, shape_a, N );
    SPLIT_SUBCASE( case5, shape_v, N );
    SPLIT_SUBCASE( case5, shape_f, N );
    SPLIT_SUBCASE( case5, shape_h, N );
}

TEST_CASE("split(case6)" * doctest::test_suite("view::detail::split"))
{
    SPLIT_SUBCASE( case6, shape, N );
    SPLIT_SUBCASE( case6, shape_a, N );
    SPLIT_SUBCASE( case6, shape_v, N );
    SPLIT_SUBCASE( case6, shape_f, N );
    SPLIT_SUBCASE( case6, shape_h, N );
}

#define RUN_shape_matmul_impl(...) \
nmtools::index::shape_matmul(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_matmul fn to callable lambda
#define RUN_shape_matmul(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_matmul-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_matmul_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_matmul(case_name, ...) \
RUN_shape_matmul_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_MATMUL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, shape_matmul, case_name); \
    using namespace args; \
    auto result = RUN_shape_matmul(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_matmul(case1)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case1, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case1, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_cl );

    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_h );;
    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_cl );

    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_h );;
    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_cl );

    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_h );;
    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_cl );

    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_h );;
    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_cl );

    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_h );;
    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_cl );

    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_h );;
    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_cl );
}

TEST_CASE("shape_matmul(case2)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case2, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case2, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case2, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case2, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case2, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case2, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case2, lshape_ct, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case2, lshape_cl, rshape_cl );
}

TEST_CASE("shape_matmul(case3)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case3, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case3, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case3, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case3, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case3, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case3, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case3, lshape_ct, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case3, lshape_cl, rshape_cl );
}

TEST_CASE("shape_matmul(case4)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case4, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case4, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case4, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case4, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case4, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case4, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case4, lshape_ct, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case4, lshape_cl, rshape_cl );
}

TEST_CASE("shape_matmul(case5)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case5, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case5, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case5, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case5, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case5, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case5, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case5, lshape_cl, rshape_cl );
    SHAPE_MATMUL_SUBCASE( case5, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case6)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case6, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case6, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case6, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case6, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case6, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case6, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case6, lshape_cl, rshape_cl );
    SHAPE_MATMUL_SUBCASE( case6, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case7)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case7, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case7, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case7, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case7, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case7, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case7, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case7, lshape_cl, rshape_cl );
    SHAPE_MATMUL_SUBCASE( case7, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case8)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case8, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case8, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case8, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case8, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case8, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case8, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case8, lshape_cl, rshape_cl );
    SHAPE_MATMUL_SUBCASE( case8, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case9)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case9, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case9, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case9, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case9, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case9, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case9, lshape_d, rshape_d );

    // SHAPE_MATMUL_SUBCASE( case9, lshape_cl, rshape_cl );
    // SHAPE_MATMUL_SUBCASE( case9, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case10)" * doctest::test_suite("view::detail::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case10, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case10, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case10, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case10, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case10, lshape_h, rshape_h );

    SHAPE_MATMUL_SUBCASE( case10, lshape_cl, rshape_cl );
    SHAPE_MATMUL_SUBCASE( case10, lshape_ct, rshape_ct );
}

#define RUN_index_matmul_impl(...) \
nmtools::view::detail::matmul(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs matmul fn to callable lambda
#define RUN_index_matmul(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("index-matmul-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_index_matmul_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_index_matmul(case_name, ...) \
RUN_index_matmul_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define INDEX_MATMUL_SUBCASE(case_name, res_left, res_right, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, matmul, case_name); \
    using namespace args; \
    auto result = RUN_index_matmul(case_name, __VA_ARGS__); \
    auto left   = nmtools::get<0>(result); \
    auto right  = nmtools::get<1>(result); \
    NMTOOLS_ASSERT_APPLY_EQUAL( left, expect::res_left ); \
    NMTOOLS_ASSERT_APPLY_EQUAL( right, expect::res_right ); \
}

// TODO: check value
// NOTE: isequal can't handle list with either
#define DYNAMIC_INDEX_MATMUL_SUBCASE(case_name, res_left, res_right, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, matmul, case_name); \
    using namespace args; \
    auto result = RUN_index_matmul(case_name, __VA_ARGS__); \
    auto left   = nmtools::get<0>(result); \
    auto right  = nmtools::get<1>(result); \
    NMTOOLS_ASSERT_EQUAL( nm::dim(left), nm::dim(expect::res_left) ); \
    NMTOOLS_ASSERT_EQUAL( nm::dim(right), nm::dim(expect::res_right) ); \
    NMTOOLS_ASSERT_EQUAL( nm::len(left), nm::len(expect::res_left) ); \
    NMTOOLS_ASSERT_EQUAL( nm::len(right), nm::len(expect::res_right) ); \
    NMTOOLS_ASSERT_APPLY_EQUAL( right, expect::res_right ); \
    NMTOOLS_ASSERT_APPLY_EQUAL( left, expect::res_left ); \
}

TEST_CASE("matmul(case1)" * doctest::test_suite("view::detail::matmul"))
{
    INDEX_MATMUL_SUBCASE(case1, left, right, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case1, left, right, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case1, left, right, indices_f, lshape_f, rshape_f, shape_f);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case1, left_v, right_v, indices_h, lshape_h, rshape_h, shape_h);
    // NOTE: isequal can't handle list with either
    DYNAMIC_INDEX_MATMUL_SUBCASE(case1, left_v, right_v, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case2)" * doctest::test_suite("view::detail::matmul"))
{
    INDEX_MATMUL_SUBCASE(case2, left, right, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case2, left, right, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case2, left, right, indices_f, lshape_f, rshape_f, shape_f);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case2, left_v, right_v, indices_h, lshape_h, rshape_h, shape_h);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case2, left_v, right_v, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case3)" * doctest::test_suite("view::detail::matmul"))
{
    INDEX_MATMUL_SUBCASE(case3, left, right, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case3, left, right, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case3, left, right, indices_f, lshape_f, rshape_f, shape_f);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case3, left_v, right_v, indices_h, lshape_h, rshape_h, shape_h);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case3, left_v, right_v, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case4)" * doctest::test_suite("view::detail::matmul"))
{
    INDEX_MATMUL_SUBCASE(case4, left, right, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case4, left, right, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case4, left, right, indices_f, lshape_f, rshape_f, shape_f);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case4, left_v, right_v, indices_h, lshape_h, rshape_h, shape_h);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case4, left_v, right_v, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case5)" * doctest::test_suite("view::detail::matmul"))
{
    INDEX_MATMUL_SUBCASE(case5, left, right, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case5, left, right, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case5, left, right, indices_f, lshape_f, rshape_f, shape_f);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case5, left_v, right_v, indices_h, lshape_h, rshape_h, shape_h);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case5, left_v, right_v, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case6)" * doctest::test_suite("view::detail::matmul"))
{
    INDEX_MATMUL_SUBCASE(case6, left, right, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case6, left, right, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case6, left, right, indices_f, lshape_f, rshape_f, shape_f);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case6, left_v, right_v, indices_h, lshape_h, rshape_h, shape_h);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case6, left_v, right_v, indices_v, lshape_v, rshape_v, shape_v);
}