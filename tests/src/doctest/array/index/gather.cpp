#include "nmtools/array/index/gather.hpp"
// TODO: remove as_tuple
#include "nmtools/array/index/as_tuple.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/constants.hpp"
#include "testing/doctest.hpp"
#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;
using namespace nm::literals;
using nmtools::utils::isequal;
using std::tuple;
using std::vector;
using std::array;

// TODO: add index vector kind, do not use nested vec
#ifndef PLATFORMIO
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid);
#else
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_h = cast(name, kind::hybrid);
#endif // PLATFORMIO

NMTOOLS_TESTING_DECLARE_CASE(gather)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int vec[3]     = {1,2,3};
        int indices[3] = {0,1,2};
        CAST_ARRAYS(vec);
        CAST_ARRAYS(indices);
        // TODO: drop tuple w/ runtime value
        auto vec_t     = index::as_tuple(vec_a);
        auto indices_t = index::as_tuple(indices_a);
        auto vec_ct     = tuple{1_ct,2_ct,3_ct};
        auto indices_ct = tuple{0_ct,1_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[3] = {1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int vec[3]     = {1,2,3};
        int indices[3] = {1,0,2};
        CAST_ARRAYS(vec);
        CAST_ARRAYS(indices);
        auto vec_t     = index::as_tuple(vec_a);
        auto indices_t = index::as_tuple(indices_a);
        auto vec_ct = tuple{1_ct,2_ct,3_ct};
        auto indices_ct = tuple{1_ct,0_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[3] = {2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int vec[3]     = {1,2,3};
        int indices[3] = {1,2,0};
        CAST_ARRAYS(vec);
        CAST_ARRAYS(indices);
        auto vec_t     = index::as_tuple(vec_a);
        auto indices_t = index::as_tuple(indices_a);
        auto vec_ct = tuple{1_ct,2_ct,3_ct};
        auto indices_ct = tuple{1_ct,2_ct,0_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[3] = {2,3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int vec[3]     = {1,2,3};
        int indices[3] = {2,0,1};
        CAST_ARRAYS(vec);
        CAST_ARRAYS(indices);
        auto vec_t     = index::as_tuple(vec_a);
        auto indices_t = index::as_tuple(indices_a);
        auto vec_ct = tuple{1_ct,2_ct,3_ct};
        auto indices_ct = tuple{2_ct,0_ct,1_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[3] = {3,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int vec[3]     = {1,2,3};
        int indices[3] = {2,1,0};
        CAST_ARRAYS(vec);
        CAST_ARRAYS(indices);
        auto vec_t     = index::as_tuple(vec_a);
        auto indices_t = index::as_tuple(indices_a);
        auto vec_ct = tuple{1_ct,2_ct,3_ct};
        auto indices_ct = tuple{2_ct,1_ct,0_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int result[3] = {3,2,1};
    }
    
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int vec[5]     = {1,2,3,4,5};
        int indices[3] = {2,1,0};
        CAST_ARRAYS(vec);
        CAST_ARRAYS(indices);
        auto vec_t     = index::as_tuple(vec_a);
        auto indices_t = index::as_tuple(indices_a);
        auto vec_ct = tuple{1_ct,2_ct,3_ct,4_ct,5_ct};
        auto indices_ct = tuple{2_ct,1_ct,0_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int result[3] = {3,2,1};
    }
}

#undef CAST_ARRAYS

#define RUN_impl(...) \
nm::index::gather(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs gather fn to callable lambda
#define RUN_gather(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("gather-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_gather(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define GATHER_SUBCASE(case_name, vec, indices) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(gather, case_name); \
    auto result = RUN_gather(case_name, args::vec, args::indices); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
} \

TEST_CASE("gather(case1)" * doctest::test_suite("index::gather"))
{
    GATHER_SUBCASE(case1, vec_a, indices_a);
    // TODO: drop tuple w/ runtime value
    GATHER_SUBCASE(case1, vec_t, indices_t);
    GATHER_SUBCASE(case1, vec_t, indices_ct);
    GATHER_SUBCASE(case1, vec_v, indices_v);
    GATHER_SUBCASE(case1, vec_ct, indices_ct);
}

TEST_CASE("gather(case2)" * doctest::test_suite("index::gather"))
{
    GATHER_SUBCASE(case2, vec_a, indices_a);
    GATHER_SUBCASE(case2, vec_t, indices_t);
    GATHER_SUBCASE(case2, vec_t, indices_ct);
    GATHER_SUBCASE(case2, vec_v, indices_v);
    GATHER_SUBCASE(case2, vec_ct, indices_ct);
}

TEST_CASE("gather(case3)" * doctest::test_suite("index::gather"))
{
    GATHER_SUBCASE(case3, vec_a, indices_a);
    GATHER_SUBCASE(case3, vec_t, indices_t);
    GATHER_SUBCASE(case3, vec_t, indices_ct);
    GATHER_SUBCASE(case3, vec_v, indices_v);
    GATHER_SUBCASE(case3, vec_ct, indices_ct);
}

TEST_CASE("gather(case4)" * doctest::test_suite("index::gather"))
{
    GATHER_SUBCASE(case4, vec_a, indices_a);
    GATHER_SUBCASE(case4, vec_t, indices_t);
    GATHER_SUBCASE(case4, vec_t, indices_ct);
    GATHER_SUBCASE(case4, vec_v, indices_v);
    GATHER_SUBCASE(case4, vec_ct, indices_ct);
}

TEST_CASE("gather(case5)" * doctest::test_suite("index::gather"))
{
    GATHER_SUBCASE(case5, vec_a, indices_a);
    GATHER_SUBCASE(case5, vec_t, indices_t);
    GATHER_SUBCASE(case5, vec_t, indices_ct);
    GATHER_SUBCASE(case5, vec_v, indices_v);
    GATHER_SUBCASE(case5, vec_ct, indices_ct);
}

TEST_CASE("gather(case6)" * doctest::test_suite("index::gather"))
{
    GATHER_SUBCASE(case6, vec_a, indices_a);
    GATHER_SUBCASE(case6, vec_t, indices_t);
    GATHER_SUBCASE(case6, vec_t, indices_ct);
    GATHER_SUBCASE(case6, vec_v, indices_v);
    GATHER_SUBCASE(case6, vec_ct, indices_ct);
}

NMTOOLS_TESTING_DECLARE_CASE(index, gahter_constexpr)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr int vec[3]     = {1,2,3};
        constexpr int indices[3] = {1,2,0};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        [[maybe_unused]] constexpr int result[3] = {2,3,1};
    }
}

TEST_CASE("gather(constexpr)" * doctest::test_suite("index::gather"))
{
    NMTOOLS_TESTING_DECLARE_NS(index, gahter_constexpr, case1);
    [[maybe_unused]] constexpr auto result = nm::index::gather(args::vec,args::indices);
    NMTOOLS_STATIC_ASSERT( (nm::utils::isclose(result,expect::result)) );
}

TEST_CASE("gather" * doctest::test_suite("index"))
{
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{0,1,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{1,0,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{1,2,0};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{0,1,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{1,0,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{1,2,0};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{0,1,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{0_ct,1_ct,2_ct};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1,0,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1_ct,0_ct,2_ct};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1,2,0};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1_ct,2_ct,0_ct};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{0,1,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{1,0,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{1,2,0};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{0,1,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{1,0,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{1,2,0};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{2,1,0};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{3,2,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{2,0,1};
        auto order    = vector{2,0,1};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,0};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{2,0,1};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
}