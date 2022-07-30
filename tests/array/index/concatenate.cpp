#include "nmtools/array/index/concatenate.hpp"
#include "nmtools/array/ndarray.hpp"

#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;
namespace idx  = nm::index;
using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(shape_concatenate)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int axis = 0;
        inline int ashape[2] = {2,2};
        inline int bshape[2] = {1,2};
        inline auto axis_ct = 0_ct;
        inline auto ashape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto bshape_ct = nmtools_tuple{1_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape);
        NMTOOLS_CAST_INDEX_ARRAYS(bshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline bool success = true;
        inline int shape[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int axis = 1;
        inline int ashape[2] = {2,2};
        inline int bshape[2] = {1,2};
        inline auto axis_ct = 1_ct;
        inline auto ashape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto bshape_ct = nmtools_tuple{1_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape);
        NMTOOLS_CAST_INDEX_ARRAYS(bshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline bool success = false;
        inline int shape[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int axis = 1;
        inline int ashape[2] = {2,2};
        inline int bshape[2] = {2,1};
        inline auto axis_ct = 1_ct;
        inline auto ashape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto bshape_ct = nmtools_tuple{2_ct,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape);
        NMTOOLS_CAST_INDEX_ARRAYS(bshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline bool success = true;
        inline int shape[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline auto axis = None;
        inline int ashape[2] = {2,2};
        inline int bshape[2] = {2,1};
        inline auto ashape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto bshape_ct = nmtools_tuple{2_ct,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape);
        NMTOOLS_CAST_INDEX_ARRAYS(bshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        bool success = true;
        int shape[1] = {6};
    }
}

#define RUN_shape_concatenate_impl(...) \
nm::index::shape_concatenate(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_concatenate fn to callable lambda
#define RUN_shape_concatenate(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_concatenate-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_concatenate_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_concatenate(case_name, ...) \
RUN_shape_concatenate_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#ifdef __clang__
#define SHAPE_CONCATENATE_SUBCASE(case_name, ashape, bshape, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(shape_concatenate, case_name) \
    auto result = RUN_shape_concatenate(case_name, args::ashape, args::bshape, args::axis); \
    auto success = std::get<0>(result); \
    auto shape = std::get<1>(result); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    if (expect::success) \
        NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
}
#else
#define SHAPE_CONCATENATE_SUBCASE(case_name, ashape, bshape, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(shape_concatenate, case_name) \
    const auto [success, shape] = RUN_shape_concatenate(case_name, args::ashape, args::bshape, args::axis); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    if (expect::success) \
        NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
}
#endif // __clang__

TEST_CASE("shape_concatenate(case1)" * doctest::test_suite("index::shape_concatenate"))
{
    SHAPE_CONCATENATE_SUBCASE( case1, ashape_a, bshape_a, axis );
    SHAPE_CONCATENATE_SUBCASE( case1, ashape_v, bshape_v, axis );
    SHAPE_CONCATENATE_SUBCASE( case1, ashape_h, bshape_h, axis );

    SHAPE_CONCATENATE_SUBCASE( case1, ashape_ct, bshape_ct, axis );
}

TEST_CASE("shape_concatenate(case2)" * doctest::test_suite("index::shape_concatenate"))
{
    SHAPE_CONCATENATE_SUBCASE( case2, ashape_a, bshape_a, axis );
    SHAPE_CONCATENATE_SUBCASE( case2, ashape_v, bshape_v, axis );
    SHAPE_CONCATENATE_SUBCASE( case2, ashape_h, bshape_h, axis );
}

TEST_CASE("shape_concatenate(case3)" * doctest::test_suite("index::shape_concatenate"))
{
    SHAPE_CONCATENATE_SUBCASE( case3, ashape_a, bshape_a, axis );
    SHAPE_CONCATENATE_SUBCASE( case3, ashape_v, bshape_v, axis );
    SHAPE_CONCATENATE_SUBCASE( case3, ashape_h, bshape_h, axis );
}

TEST_CASE("shape_concatenate(case4)" * doctest::test_suite("index::shape_concatenate"))
{
    SHAPE_CONCATENATE_SUBCASE( case4, ashape_a, bshape_a, axis );
    SHAPE_CONCATENATE_SUBCASE( case4, ashape_v, bshape_v, axis );
    SHAPE_CONCATENATE_SUBCASE( case4, ashape_h, bshape_h, axis );
}

#include "nmtools/array/index/concatenate.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"

#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;
namespace idx = nm::index;
using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(index, concatenate)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int ashape[2]  = {2,2};
        inline int bshape[2]  = {1,2};
        inline int indices[2] = {0,0};
        inline int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(ashape);
        NMTOOLS_CAST_INDEX_ARRAYS(bshape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto aflag = true;
        inline auto bflag = false;
        inline int a_idx[2] = {0,0};
        inline int b_idx[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int ashape[2]  = {2,2};
        int bshape[2]  = {1,2};
        int indices[2] = {2,1};
        int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(ashape);
        NMTOOLS_CAST_INDEX_ARRAYS(bshape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto aflag = false;
        auto bflag = true;
        int a_idx[2] = {0,0};
        int b_idx[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int ashape[2]  = {2,2};
        int bshape[2]  = {1,2};
        int indices[2] = {1,1};
        int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(ashape);
        NMTOOLS_CAST_INDEX_ARRAYS(bshape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto aflag = true;
        auto bflag = false;
        int a_idx[2] = {1,1};
        int b_idx[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int ashape[2]  = {2,2};
        int bshape[2]  = {1,2};
        int indices[2] = {2,0};
        int axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(ashape);
        NMTOOLS_CAST_INDEX_ARRAYS(bshape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto aflag = false;
        auto bflag = true;
        int a_idx[2] = {0,0};
        int b_idx[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int ashape[2]  = {2,2};
        int bshape[2]  = {1,2};
        int indices[1] = {4};
        auto axis = None;
        NMTOOLS_CAST_INDEX_ARRAYS(ashape);
        NMTOOLS_CAST_INDEX_ARRAYS(bshape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto aflag = false;
        auto bflag = true;
        int a_idx[2] = {0,0};
        int b_idx[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int ashape[2]  = {2,2};
        int bshape[2]  = {1,2};
        int indices[1] = {5};
        auto axis = None;
        NMTOOLS_CAST_INDEX_ARRAYS(ashape);
        NMTOOLS_CAST_INDEX_ARRAYS(bshape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto aflag = false;
        auto bflag = true;
        int a_idx[2] = {0,0};
        int b_idx[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int ashape[2]  = {2,2};
        int bshape[2]  = {1,2};
        int indices[1] = {2};
        auto axis = None;
        NMTOOLS_CAST_INDEX_ARRAYS(ashape);
        NMTOOLS_CAST_INDEX_ARRAYS(bshape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto aflag = true;
        auto bflag = false;
        int a_idx[2] = {1,0};
        int b_idx[2] = {0,0};
    }
}

#define RUN_impl(...) \
nm::index::concatenate(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs concatenate fn to callable lambda
#define RUN_concatenate(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("concatenate-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_concatenate(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#ifdef __clang__
#define CONCATENATE_SUBCASE(case_name, ashape, bshape, indices, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index,concatenate,case_name); \
    auto result = RUN_concatenate(case_name,args::ashape,args::bshape,args::indices,args::axis); \
    auto aflag = std::get<0>(result) ; \
    auto bflag = std::get<1>(result) ; \
    auto a_idx = std::get<2>(result) ; \
    auto b_idx = std::get<3>(result) ; \
    NMTOOLS_ASSERT_EQUAL( aflag, expect::aflag ); \
    NMTOOLS_ASSERT_EQUAL( bflag, expect::bflag ); \
    if (expect::aflag) \
        NMTOOLS_ASSERT_EQUAL( a_idx, expect::a_idx ); \
    if (expect::bflag) \
        NMTOOLS_ASSERT_EQUAL( b_idx, expect::b_idx ); \
}
#else
#define CONCATENATE_SUBCASE(case_name, ashape, bshape, indices, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index,concatenate,case_name); \
    const auto [aflag,bflag,a_idx,b_idx] = RUN_concatenate(case_name, args::ashape,args::bshape,args::indices,args::axis); \
    NMTOOLS_ASSERT_EQUAL( aflag, expect::aflag ); \
    NMTOOLS_ASSERT_EQUAL( bflag, expect::bflag ); \
    if (expect::aflag) \
        NMTOOLS_ASSERT_EQUAL( a_idx, expect::a_idx ); \
    if (expect::bflag) \
        NMTOOLS_ASSERT_EQUAL( b_idx, expect::b_idx ); \
}
#endif // __clang__

TEST_CASE("concatenate(case1)" * doctest::test_suite("index::concatenate"))
{
    CONCATENATE_SUBCASE( case1, ashape,   bshape,   indices,   axis );
    CONCATENATE_SUBCASE( case1, ashape_a, bshape_a, indices_a, axis );
    CONCATENATE_SUBCASE( case1, ashape_v, bshape_v, indices_v, axis );
    CONCATENATE_SUBCASE( case1, ashape_h, bshape_h, indices_h, axis );
}

TEST_CASE("concatenate(case2)" * doctest::test_suite("index::concatenate"))
{
    CONCATENATE_SUBCASE( case2, ashape,   bshape,   indices,   axis );
    CONCATENATE_SUBCASE( case2, ashape_a, bshape_a, indices_a, axis );
    CONCATENATE_SUBCASE( case2, ashape_v, bshape_v, indices_v, axis );
    CONCATENATE_SUBCASE( case2, ashape_h, bshape_h, indices_h, axis );
}

TEST_CASE("concatenate(case3)" * doctest::test_suite("index::concatenate"))
{
    CONCATENATE_SUBCASE( case3, ashape,   bshape,   indices,   axis );
    CONCATENATE_SUBCASE( case3, ashape_a, bshape_a, indices_a, axis );
    CONCATENATE_SUBCASE( case3, ashape_v, bshape_v, indices_v, axis );
    CONCATENATE_SUBCASE( case3, ashape_h, bshape_h, indices_h, axis );
}

TEST_CASE("concatenate(case4)" * doctest::test_suite("index::concatenate"))
{
    CONCATENATE_SUBCASE( case4, ashape,   bshape,   indices,   axis );
    CONCATENATE_SUBCASE( case4, ashape_a, bshape_a, indices_a, axis );
    CONCATENATE_SUBCASE( case4, ashape_v, bshape_v, indices_v, axis );
    CONCATENATE_SUBCASE( case4, ashape_h, bshape_h, indices_h, axis );
}

TEST_CASE("concatenate(case5)" * doctest::test_suite("index::concatenate"))
{
    CONCATENATE_SUBCASE( case5, ashape,   bshape,   indices,   axis );
    CONCATENATE_SUBCASE( case5, ashape_a, bshape_a, indices_a, axis );
    CONCATENATE_SUBCASE( case5, ashape_v, bshape_v, indices_v, axis );
    CONCATENATE_SUBCASE( case5, ashape_h, bshape_h, indices_h, axis );
}

TEST_CASE("concatenate(case6)" * doctest::test_suite("index::concatenate"))
{
    CONCATENATE_SUBCASE( case6, ashape,   bshape,   indices,   axis );
    CONCATENATE_SUBCASE( case6, ashape_a, bshape_a, indices_a, axis );
    CONCATENATE_SUBCASE( case6, ashape_v, bshape_v, indices_v, axis );
    CONCATENATE_SUBCASE( case6, ashape_h, bshape_h, indices_h, axis );
}

TEST_CASE("concatenate(case7)" * doctest::test_suite("index::concatenate"))
{
    CONCATENATE_SUBCASE( case7, ashape,   bshape,   indices,   axis );
    CONCATENATE_SUBCASE( case7, ashape_a, bshape_a, indices_a, axis );
    CONCATENATE_SUBCASE( case7, ashape_v, bshape_v, indices_v, axis );
    CONCATENATE_SUBCASE( case7, ashape_h, bshape_h, indices_h, axis );
}