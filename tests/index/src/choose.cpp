#include "nmtools/array/index/choose.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/testing/doctest.hpp"

// quick workaround to support std::vector
#include "nmtools/array/impl/stl.hpp"

// TODO: properly create testing data for index::choose

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;

using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(index, choose)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[4]  = {0,1,2,3};
        inline size_t array[7] = {3,1,4,1,5,9,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(array);
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct,2_ct,3_ct};
        inline auto array_ct   = nmtools_tuple{3_ct,1_ct,4_ct,1_ct,5_ct,9_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int expected[4] = {3,1,4,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[4] = {1,0,2,3};
        inline size_t array[7] = {3,1,4,1,5,9,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(array);
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct,2_ct,3_ct};
        inline auto array_ct   = nmtools_tuple{3_ct,1_ct,4_ct,1_ct,5_ct,9_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int expected[4] = {1,3,4,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int indices[1] = {2};
        inline size_t array[7] = {3,1,4,1,5,9,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(array);
        inline auto indices_ct = nmtools_tuple{1_ct};
        inline auto array_ct   = nmtools_tuple{3_ct,1_ct,4_ct,1_ct,5_ct,9_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int expected[1] = {4};
    }
}

#define RUN_choose_impl(...) \
nmtools::index::choose(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nmtools::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs choose fn to callable lambda
#define RUN_choose(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("index::choose-") + #case_name; \
    auto name  = nmtools::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_choose_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_choose(case_name, ...) \
RUN_choose_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CHOOSE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, choose, case_name); \
    using namespace args; \
    auto result = RUN_choose(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

TEST_CASE("choose(case1)" * doctest::test_suite("index::choose"))
{
    CHOOSE_SUBCASE( case1, indices, array );
    CHOOSE_SUBCASE( case1, indices_a, array_a );
    CHOOSE_SUBCASE( case1, indices_f, array_f );
    CHOOSE_SUBCASE( case1, indices_h, array_h );
    CHOOSE_SUBCASE( case1, indices_v, array_v );
}

TEST_CASE("choose(case2)" * doctest::test_suite("index::choose"))
{
    CHOOSE_SUBCASE( case2, indices, array );
    CHOOSE_SUBCASE( case2, indices_a, array_a );
    CHOOSE_SUBCASE( case2, indices_f, array_f );
    CHOOSE_SUBCASE( case2, indices_h, array_h );
    CHOOSE_SUBCASE( case2, indices_v, array_v );
}

TEST_CASE("choose(case3)" * doctest::test_suite("index::choose"))
{
    CHOOSE_SUBCASE( case3, indices, array );
    CHOOSE_SUBCASE( case3, indices_a, array_a );
    CHOOSE_SUBCASE( case3, indices_f, array_f );
    CHOOSE_SUBCASE( case3, indices_h, array_h );
    CHOOSE_SUBCASE( case3, indices_v, array_v );
}

#if 0
TEST_CASE("choose(vector)" * doctest::test_suite("index::choose"))
{
    {
        auto indices = std::vector{0,1,2,3};
        auto array   = std::vector{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::vector{3ul,1ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::vector{1,0,2,3};
        auto array   = std::vector{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::vector{1ul,3ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::vector{2};
        auto array   = std::vector{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::vector{4ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }

    {
        auto indices = std::vector{0,1,2,3};
        auto array   = na::hybrid_ndarray({3ul,1ul,4ul,1ul,5ul,9ul,2ul});
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::vector{3ul,1ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::vector{1,0,2,3};
        auto array   = na::hybrid_ndarray({3ul,1ul,4ul,1ul,5ul,9ul,2ul});
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::vector{1ul,3ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::vector{2};
        auto array   = na::hybrid_ndarray({3ul,1ul,4ul,1ul,5ul,9ul,2ul});
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::vector{4ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
}

TEST_CASE("choose(array)" * doctest::test_suite("index::choose"))
{
    {
        auto indices = std::array{0,1,2,3};
        auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{3ul,1ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::array{1,0,2,3};
        auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{1ul,3ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::array{2};
        auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{4ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }

    {
        auto indices = std::array{0,1,2,3};
        auto array   = na::hybrid_ndarray({3ul,1ul,4ul,1ul,5ul,9ul,2ul});
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{3ul,1ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::array{1,0,2,3};
        auto array   = na::hybrid_ndarray({3ul,1ul,4ul,1ul,5ul,9ul,2ul});
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{1ul,3ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::array{2};
        auto array   = na::hybrid_ndarray({3ul,1ul,4ul,1ul,5ul,9ul,2ul});
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{4ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
}

// TEST_CASE("choose(tuple)" * doctest::test_suite("index::choose"))
// {
//     {
//         auto indices = std::tuple{0,1,2,3};
//         auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{3ul,1ul,4ul,1ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::tuple{1,0,2,3};
//         auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{1ul,3ul,4ul,1ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::tuple{2};
//         auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{4ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::array{0,1,2,3};
//         auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{3ul,1ul,4ul,1ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::array{1,0,2,3};
//         auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{1ul,3ul,4ul,1ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::array{2};
//         auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{4ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::tuple{0,1,2,3};
//         auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{3ul,1ul,4ul,1ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::tuple{1,0,2,3};
//         auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{1ul,3ul,4ul,1ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::tuple{2};
//         auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{4ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
// }

TEST_CASE("choose(hybrid_ndarray)" * doctest::test_suite("index::choose"))
{
    // {
    //     auto indices = na::hybrid_ndarray({0,1,2,3});
    //     auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
    //     auto chosen  = nm::index::choose(indices,array);
    //     auto expected = std::array{3ul,1ul,4ul,1ul};
    //     NMTOOLS_ASSERT_CLOSE( chosen, expected );
    // }
    // {
        // auto indices = na::hybrid_ndarray({1,0,2,3});
        // auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        // auto chosen  = nm::index::choose(indices,array);
        // auto expected = std::array{1ul,3ul,4ul,1ul};
        // NMTOOLS_ASSERT_CLOSE( chosen, expected );
    // }
    // {
    //     auto indices = na::hybrid_ndarray({2});
    //     auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
    //     auto chosen  = nm::index::choose(indices,array);
    //     auto expected = std::array{4ul};
    //     NMTOOLS_ASSERT_CLOSE( chosen, expected );
    // }
    // {
    //     auto indices = na::hybrid_ndarray({0,1,2,3});
    //     auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
    //     auto chosen  = nm::index::choose(indices,array);
    //     auto expected = std::array{3ul,1ul,4ul,1ul};
    //     NMTOOLS_ASSERT_CLOSE( chosen, expected );
    // }
    // {
    //     auto indices = na::hybrid_ndarray({1,0,2,3});
    //     auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
    //     auto chosen  = nm::index::choose(indices,array);
    //     auto expected = std::array{1ul,3ul,4ul,1ul};
    //     NMTOOLS_ASSERT_CLOSE( chosen, expected );
    // }
    // {
    //     auto indices = na::hybrid_ndarray({2});
    //     auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
    //     auto chosen  = nm::index::choose(indices,array);
    //     auto expected = std::array{4ul};
    //     NMTOOLS_ASSERT_CLOSE( chosen, expected );
    // }
    {
        auto indices = na::hybrid_ndarray({0,1,2,3});
        auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{3ul,1ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = na::hybrid_ndarray({1,0,2,3});
        auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{1ul,3ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = na::hybrid_ndarray({2});
        auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{4ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
}
#endif