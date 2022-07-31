#include "nmtools/array/index/broadcast_to.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(broadcast_to)
{
    using nmtools_tuple;
    using namespace nmtools::literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int ashape[2] = {3,1};
        int bshape[2] = {3,1};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        auto ashape_ct = tuple{3_ct,1_ct};
        auto bshape_ct = tuple{3_ct,1_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto success = true;
        auto shape   = nmtools_array{3,1};
        auto free    = nmtools_array{false,false};
        auto results = nmtools_tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int ashape[2] = {3,1};
        int bshape[2] = {3,3};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        auto ashape_ct = tuple{3_ct,1_ct};
        auto bshape_ct = tuple{3_ct,3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto success = true;
        auto shape   = nmtools_array{3,3};
        auto free    = nmtools_array{false,true};
        auto results = nmtools_tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int ashape[2] = {3,1};
        int bshape[3] = {3,3,1};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        auto ashape_ct = tuple{3_ct,1_ct};
        auto bshape_ct = tuple{3_ct,3_ct,1_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto success = true;
        auto shape   = nmtools_array{3,3,1};
        auto free    = nmtools_array{true,false,false};
        auto results = nmtools_tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int ashape[2] = {3,1};
        int bshape[3] = {3,3,6};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        auto ashape_ct = tuple{3_ct,1_ct};
        auto bshape_ct = tuple{3_ct,3_ct,6_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto success = true;
        auto shape   = nmtools_array{3,3,6};
        auto free    = nmtools_array{true,false,true};
        auto results = nmtools_tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int ashape[2] = {3,1};
        int bshape[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        auto ashape_ct = tuple{3_ct,1_ct};
        auto bshape_ct = tuple{3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto success = false;
        auto shape   = nmtools_array{0};
        auto free    = nmtools_array{false};
        auto results = nmtools_tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int ashape[2] = {3,1};
        int bshape[3] = {3,6,6};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        auto ashape_ct = tuple{3_ct,1_ct};
        auto bshape_ct = tuple{3_ct,6_ct,6_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto success = false;
        auto shape   = nmtools_array{0,0,6};
        auto free    = nmtools_array{false,false,true};
        auto results = nmtools_tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int ashape[2] = {3,1};
        int bshape[4] = {7,3,3,6};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        auto ashape_ct = tuple{3_ct,1_ct};
        auto bshape_ct = tuple{7_ct,3_ct,3_ct,6_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto success = true;
        auto shape   = nmtools_array{7,3,3,6};
        auto free    = nmtools_array{true,true,false,true};
        auto results = nmtools_tuple{success,shape,free};
    }
}

#define RUN_impl(...) \
nm::index::shape_broadcast_to(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs broadcast_to fn to callable lambda
#define RUN_broadcast_to(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("broadcast_to-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_broadcast_to(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

// @note clang refuses to compile structured binding for this expr
#ifndef __clang__
#define BROADCAST_TO_SUBCASE(case_name, ashape, bshape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_to, case_name); \
    const auto [success, shape, free] = RUN_broadcast_to(case_name, args::ashape, args::bshape); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
    NMTOOLS_ASSERT_EQUAL( free, expect::free ); \
}
#else
#define BROADCAST_TO_SUBCASE(case_name, ashape, bshape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_to, case_name); \
    auto results = RUN_broadcast_to(case_name, args::ashape, args::bshape); \
    auto success = nmtools::get<0>(results); \
    auto shape   = nmtools::get<1>(results); \
    auto free    = nmtools::get<2>(results); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
    NMTOOLS_ASSERT_EQUAL( free, expect::free ); \
}
#endif

TEST_CASE("broadcast_to(case1)" * doctest::test_suite("index::shape_broadcast_to"))
{
    BROADCAST_TO_SUBCASE(case1, ashape, bshape);

    BROADCAST_TO_SUBCASE(case1, ashape_a, bshape_a);
    BROADCAST_TO_SUBCASE(case1, ashape_v, bshape_v);
    BROADCAST_TO_SUBCASE(case1, ashape_h, bshape_h);

    BROADCAST_TO_SUBCASE(case1, ashape_a, bshape_v);
    BROADCAST_TO_SUBCASE(case1, ashape_h, bshape_v);

    BROADCAST_TO_SUBCASE(case1, ashape_v, bshape_a);
    BROADCAST_TO_SUBCASE(case1, ashape_h, bshape_a);
    
    BROADCAST_TO_SUBCASE(case1, ashape_a, bshape_h);
    BROADCAST_TO_SUBCASE(case1, ashape_v, bshape_h);

    BROADCAST_TO_SUBCASE(case1, ashape_ct, bshape_ct);

    BROADCAST_TO_SUBCASE(case1,   ashape, bshape_ct);
    BROADCAST_TO_SUBCASE(case1, ashape_a, bshape_ct);
    BROADCAST_TO_SUBCASE(case1, ashape_v, bshape_ct);
    BROADCAST_TO_SUBCASE(case1, ashape_h, bshape_ct);

    BROADCAST_TO_SUBCASE(case1, ashape_ct,   bshape);
    BROADCAST_TO_SUBCASE(case1, ashape_ct, bshape_a);
    BROADCAST_TO_SUBCASE(case1, ashape_ct, bshape_v);
    BROADCAST_TO_SUBCASE(case1, ashape_ct, bshape_h);
}

TEST_CASE("broadcast_to(case2)" * doctest::test_suite("index::shape_broadcast_to"))
{
    BROADCAST_TO_SUBCASE(case2, ashape, bshape);

    BROADCAST_TO_SUBCASE(case2, ashape_a, bshape_a);
    BROADCAST_TO_SUBCASE(case2, ashape_v, bshape_v);
    BROADCAST_TO_SUBCASE(case2, ashape_h, bshape_h);

    BROADCAST_TO_SUBCASE(case2, ashape_a, bshape_v);
    BROADCAST_TO_SUBCASE(case2, ashape_h, bshape_v);

    BROADCAST_TO_SUBCASE(case2, ashape_v, bshape_a);
    BROADCAST_TO_SUBCASE(case2, ashape_h, bshape_a);
    
    BROADCAST_TO_SUBCASE(case2, ashape_a, bshape_h);
    BROADCAST_TO_SUBCASE(case2, ashape_v, bshape_h);

    BROADCAST_TO_SUBCASE(case2, ashape_ct, bshape_ct);

    BROADCAST_TO_SUBCASE(case2,   ashape, bshape_ct);
    BROADCAST_TO_SUBCASE(case2, ashape_a, bshape_ct);
    BROADCAST_TO_SUBCASE(case2, ashape_v, bshape_ct);
    BROADCAST_TO_SUBCASE(case2, ashape_h, bshape_ct);

    BROADCAST_TO_SUBCASE(case2, ashape_ct,   bshape);
    BROADCAST_TO_SUBCASE(case2, ashape_ct, bshape_a);
    BROADCAST_TO_SUBCASE(case2, ashape_ct, bshape_v);
    BROADCAST_TO_SUBCASE(case2, ashape_ct, bshape_h);
}

TEST_CASE("broadcast_to(case3)" * doctest::test_suite("index::shape_broadcast_to"))
{
    BROADCAST_TO_SUBCASE(case3, ashape_a, bshape_a);
    BROADCAST_TO_SUBCASE(case3, ashape_v, bshape_v);
    BROADCAST_TO_SUBCASE(case3, ashape_h, bshape_h);

    BROADCAST_TO_SUBCASE(case3, ashape_a, bshape_v);
    BROADCAST_TO_SUBCASE(case3, ashape_h, bshape_v);

    BROADCAST_TO_SUBCASE(case3, ashape_v, bshape_a);
    BROADCAST_TO_SUBCASE(case3, ashape_h, bshape_a);
    
    BROADCAST_TO_SUBCASE(case3, ashape_a, bshape_h);
    BROADCAST_TO_SUBCASE(case3, ashape_v, bshape_h);
}

TEST_CASE("broadcast_to(case4)" * doctest::test_suite("index::shape_broadcast_to"))
{
    BROADCAST_TO_SUBCASE(case4, ashape_a, bshape_a);
    BROADCAST_TO_SUBCASE(case4, ashape_v, bshape_v);
    BROADCAST_TO_SUBCASE(case4, ashape_h, bshape_h);

    BROADCAST_TO_SUBCASE(case4, ashape_a, bshape_v);
    BROADCAST_TO_SUBCASE(case4, ashape_h, bshape_v);

    BROADCAST_TO_SUBCASE(case4, ashape_v, bshape_a);
    BROADCAST_TO_SUBCASE(case4, ashape_h, bshape_a);
    
    BROADCAST_TO_SUBCASE(case4, ashape_a, bshape_h);
    BROADCAST_TO_SUBCASE(case4, ashape_v, bshape_h);

    BROADCAST_TO_SUBCASE(case4, ashape_ct, bshape_ct);

    BROADCAST_TO_SUBCASE(case4,   ashape, bshape_ct);
    BROADCAST_TO_SUBCASE(case4, ashape_a, bshape_ct);
    BROADCAST_TO_SUBCASE(case4, ashape_v, bshape_ct);
    BROADCAST_TO_SUBCASE(case4, ashape_h, bshape_ct);

    BROADCAST_TO_SUBCASE(case4, ashape_ct,   bshape);
    BROADCAST_TO_SUBCASE(case4, ashape_ct, bshape_a);
    BROADCAST_TO_SUBCASE(case4, ashape_ct, bshape_v);
    BROADCAST_TO_SUBCASE(case4, ashape_ct, bshape_h);
}

TEST_CASE("broadcast_to(case5)" * doctest::test_suite("index::shape_broadcast_to"))
{
    BROADCAST_TO_SUBCASE(case5, ashape_a, bshape_a);
    // TODO: fix invalid value for utl::vector
    #ifndef NMTOOLS_DISABLE_STL
    BROADCAST_TO_SUBCASE(case5, ashape_v, bshape_v);
    #endif
    BROADCAST_TO_SUBCASE(case5, ashape_h, bshape_h);

    // TODO: fix invalid value for utl::vector
    #ifndef NMTOOLS_DISABLE_STL
    BROADCAST_TO_SUBCASE(case5, ashape_a, bshape_v);
    BROADCAST_TO_SUBCASE(case5, ashape_h, bshape_v);

    BROADCAST_TO_SUBCASE(case5, ashape_v, bshape_a);
    #endif
    BROADCAST_TO_SUBCASE(case5, ashape_h, bshape_a);
    
    BROADCAST_TO_SUBCASE(case5, ashape_a, bshape_h);
    // TODO: fix invalid value for utl::vector
    #ifndef NMTOOLS_DISABLE_STL
    BROADCAST_TO_SUBCASE(case5, ashape_v, bshape_h);
    #endif

    BROADCAST_TO_SUBCASE(case5, ashape_ct, bshape_ct);

    BROADCAST_TO_SUBCASE(case5,   ashape, bshape_ct);
    BROADCAST_TO_SUBCASE(case5, ashape_a, bshape_ct);
    BROADCAST_TO_SUBCASE(case5, ashape_v, bshape_ct);
    BROADCAST_TO_SUBCASE(case5, ashape_h, bshape_ct);

    BROADCAST_TO_SUBCASE(case5, ashape_ct,   bshape);
    BROADCAST_TO_SUBCASE(case5, ashape_ct, bshape_a);
    BROADCAST_TO_SUBCASE(case5, ashape_ct, bshape_v);
    BROADCAST_TO_SUBCASE(case5, ashape_ct, bshape_h);
}

TEST_CASE("broadcast_to(case6)" * doctest::test_suite("index::shape_broadcast_to"))
{
    BROADCAST_TO_SUBCASE(case6, ashape_a, bshape_a);
    // TODO: fix invalid value for utl::vector
    #ifndef NMTOOLS_DISABLE_STL
    BROADCAST_TO_SUBCASE(case6, ashape_v, bshape_v);
    #endif
    BROADCAST_TO_SUBCASE(case6, ashape_h, bshape_h);

    // TODO: fix invalid value for utl::vector
    #ifndef NMTOOLS_DISABLE_STL
    BROADCAST_TO_SUBCASE(case6, ashape_a, bshape_v);
    BROADCAST_TO_SUBCASE(case6, ashape_h, bshape_v);

    BROADCAST_TO_SUBCASE(case6, ashape_v, bshape_a);
    #endif
    BROADCAST_TO_SUBCASE(case6, ashape_h, bshape_a);
    
    BROADCAST_TO_SUBCASE(case6, ashape_a, bshape_h);
    // TODO: fix invalid value for utl::vector
    #ifndef NMTOOLS_DISABLE_STL
    BROADCAST_TO_SUBCASE(case6, ashape_v, bshape_h);
    #endif

    BROADCAST_TO_SUBCASE(case6, ashape_ct, bshape_ct);

    BROADCAST_TO_SUBCASE(case6,   ashape, bshape_ct);
    BROADCAST_TO_SUBCASE(case6, ashape_a, bshape_ct);
    BROADCAST_TO_SUBCASE(case6, ashape_v, bshape_ct);
    BROADCAST_TO_SUBCASE(case6, ashape_h, bshape_ct);

    BROADCAST_TO_SUBCASE(case6, ashape_ct,   bshape);
    BROADCAST_TO_SUBCASE(case6, ashape_ct, bshape_a);
    BROADCAST_TO_SUBCASE(case6, ashape_ct, bshape_v);
    BROADCAST_TO_SUBCASE(case6, ashape_ct, bshape_h);
}

TEST_CASE("broadcast_to(case7)" * doctest::test_suite("index::shape_broadcast_to"))
{
    BROADCAST_TO_SUBCASE(case7, ashape_a, bshape_a);
    BROADCAST_TO_SUBCASE(case7, ashape_v, bshape_v);
    BROADCAST_TO_SUBCASE(case7, ashape_h, bshape_h);

    BROADCAST_TO_SUBCASE(case7, ashape_a, bshape_v);
    BROADCAST_TO_SUBCASE(case7, ashape_h, bshape_v);

    BROADCAST_TO_SUBCASE(case7, ashape_v, bshape_a);
    BROADCAST_TO_SUBCASE(case7, ashape_h, bshape_a);
    
    BROADCAST_TO_SUBCASE(case7, ashape_a, bshape_h);
    BROADCAST_TO_SUBCASE(case7, ashape_v, bshape_h);

    BROADCAST_TO_SUBCASE(case7, ashape_ct, bshape_ct);

    BROADCAST_TO_SUBCASE(case7,   ashape, bshape_ct);
    BROADCAST_TO_SUBCASE(case7, ashape_a, bshape_ct);
    BROADCAST_TO_SUBCASE(case7, ashape_v, bshape_ct);
    BROADCAST_TO_SUBCASE(case7, ashape_h, bshape_ct);

    BROADCAST_TO_SUBCASE(case7, ashape_ct,   bshape);
    BROADCAST_TO_SUBCASE(case7, ashape_ct, bshape_a);
    BROADCAST_TO_SUBCASE(case7, ashape_ct, bshape_v);
    BROADCAST_TO_SUBCASE(case7, ashape_ct, bshape_h);
}

TEST_CASE("broadcast_to(constexpr)" * doctest::test_suite("index::shape_broadcast_to"))
{
    {
        constexpr int ashape[2] = {3,1};
        constexpr int bshape[4] = {7,3,3,6};
        constexpr auto broadcasted = nm::index::shape_broadcast_to(ashape,bshape);
        [[maybe_unused]] constexpr auto success = nmtools::get<0>(broadcasted);
        [[maybe_unused]] constexpr auto shape = nmtools::get<1>(broadcasted);
        [[maybe_unused]] constexpr auto free  = nmtools::get<2>(broadcasted);
        [[maybe_unused]] constexpr auto expected_free = nmtools_array{true,true,false,true};
        NMTOOLS_STATIC_ASSERT( success );
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, bshape );
        NMTOOLS_STATIC_ASSERT_EQUAL( free, expected_free );
    }
}