#include "nmtools/array/index/broadcast_to.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/broadcast_to.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace kind = na::kind;

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
#define SHAPE_BROADCAST_TO_SUBCASE(case_name, ashape, bshape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, broadcast_to, case_name); \
    const auto [success, shape, free] = RUN_broadcast_to(case_name, args::ashape, args::bshape); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    if ((success == expect::success) && success) { \
        NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
        NMTOOLS_ASSERT_EQUAL( free, expect::free ); \
    } \
}
#else
#define SHAPE_BROADCAST_TO_SUBCASE(case_name, ashape, bshape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, broadcast_to, case_name); \
    auto results = RUN_broadcast_to(case_name, args::ashape, args::bshape); \
    auto success = nmtools::get<0>(results); \
    auto shape   = nmtools::get<1>(results); \
    auto free    = nmtools::get<2>(results); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    if ((success == expect::success) && success) { \
        NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
        NMTOOLS_ASSERT_EQUAL( free, expect::free ); \
    } \
}
#endif

TEST_CASE("broadcast_to(case1)" * doctest::test_suite("index::shape_broadcast_to"))
{
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape, bshape);

    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_a, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_v, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_h, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_sv, bshape_sv);

    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_a, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_h, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_sv, bshape_v);

    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_v, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_h, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_sv, bshape_a);
    
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_a, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_v, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_sv, bshape_h);

    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_a, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_v, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_h, bshape_sv);

    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_ct, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_cl, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case1,   ashape, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_a, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_v, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_h, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_sv, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_cl, bshape_ct);

    SHAPE_BROADCAST_TO_SUBCASE(case1,    ashape, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case1,  ashape_a, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case1,  ashape_v, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case1,  ashape_h, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case1,  ashape_sv, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_ct,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_ct, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_ct, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_ct, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_ct, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_cl,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_cl, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_cl, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_cl, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_cl, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_cl, bshape_ct);
}

TEST_CASE("broadcast_to(case2)" * doctest::test_suite("index::shape_broadcast_to"))
{
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape, bshape);

    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_a, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_v, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_h, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_sv, bshape_sv);

    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_a, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_h, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_sv, bshape_v);

    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_v, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_h, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_sv, bshape_a);
    
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_a, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_v, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_sv, bshape_h);

    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_ct, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_cl, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case2,   ashape, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_a, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_v, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_h, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_sv, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_cl, bshape_ct);

    SHAPE_BROADCAST_TO_SUBCASE(case2,   ashape, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_a, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_v, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_h, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_sv, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_ct,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_ct, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_ct, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_ct, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_ct, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_cl,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_cl, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_cl, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_cl, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_cl, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_cl, bshape_ct);
}

TEST_CASE("broadcast_to(case3)" * doctest::test_suite("index::shape_broadcast_to"))
{
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_a, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_v, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_h, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_sv, bshape_sv);

    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_a, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_h, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_sv, bshape_v);

    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_v, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_h, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_sv, bshape_a);
    
    #if 1
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_a, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_v, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_sv, bshape_h);

    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_ct, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_cl, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case3,   ashape, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_a, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_v, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_h, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_sv, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_cl, bshape_ct);

    SHAPE_BROADCAST_TO_SUBCASE(case3,    ashape, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case3,  ashape_a, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case3,  ashape_v, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case3,  ashape_h, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_sv, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_ct,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_ct, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_ct, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_ct, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_ct, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_cl,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_cl, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_cl, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_cl, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_cl, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case3, ashape_cl, bshape_ct);    
    #endif
}

TEST_CASE("broadcast_to(case4)" * doctest::test_suite("index::shape_broadcast_to"))
{
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_a, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_v, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_h, bshape_h);

    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_a, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_h, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_sv, bshape_v);

    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_v, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_h, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_sv, bshape_a);
    
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_a, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_v, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_sv, bshape_h);

    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_ct, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_cl, bshape_cl);

    {
        constexpr auto i = meta::ct_v<2ul>;
        constexpr size_t LEN_A = 2;
        constexpr auto ai = meta::ct_v<(int)LEN_A-decltype(i)::value-1>;
        static_assert( (int)ai == -1 );
    }

    SHAPE_BROADCAST_TO_SUBCASE(case4,   ashape, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_a, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_v, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_h, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_sv, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_cl, bshape_ct);

    SHAPE_BROADCAST_TO_SUBCASE(case4,   ashape, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_a, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_v, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_h, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_sv, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_ct,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_ct, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_ct, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_ct, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_ct, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_cl,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_cl, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_cl, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_cl, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_cl, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_cl, bshape_cl);
}

TEST_CASE("broadcast_to(case5)" * doctest::test_suite("index::shape_broadcast_to"))
{
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_a, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_v, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_h, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_sv, bshape_h);

    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_a, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_h, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_sv, bshape_v);

    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_v, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_h, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_sv, bshape_a);
    
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_a, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_v, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_sv, bshape_h);

    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_ct, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_cl, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case5,   ashape, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_a, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_v, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_h, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_sv, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_cl, bshape_ct);

    SHAPE_BROADCAST_TO_SUBCASE(case5,   ashape, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_a, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_v, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_h, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_ct,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_ct, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_ct, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_ct, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_ct, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_cl,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_cl, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_cl, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_cl, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_cl, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_cl, bshape_ct);
}

TEST_CASE("broadcast_to(case6)" * doctest::test_suite("index::shape_broadcast_to"))
{
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_a, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_v, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_h, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_sv, bshape_sv);

    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_a, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_h, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_sv, bshape_v);

    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_v, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_h, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_sv, bshape_a);
    
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_a, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_v, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_sv, bshape_h);

    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_ct, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_cl, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case6,   ashape, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_a, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_v, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_h, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_sv, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_cl, bshape_ct);

    SHAPE_BROADCAST_TO_SUBCASE(case6,   ashape, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_a, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_v, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_h, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_sv, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_ct,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_ct, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_ct, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_ct, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_ct, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_cl,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_cl, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_cl, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_cl, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_cl, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_cl, bshape_ct);
}

TEST_CASE("broadcast_to(case7)" * doctest::test_suite("index::shape_broadcast_to"))
{
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_a, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_v, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_h, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_sv, bshape_sv);

    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_a, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_h, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_sv, bshape_v);

    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_v, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_h, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_sv, bshape_a);
    
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_a, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_v, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_sv, bshape_h);

    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_ct, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_cl, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case7,   ashape, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_a, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_v, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_h, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_sv, bshape_ct);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_cl, bshape_ct);

    SHAPE_BROADCAST_TO_SUBCASE(case7,   ashape, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_a, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_v, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_h, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_sv, bshape_cl);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_ct,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_ct, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_ct, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_ct, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_ct, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_ct, bshape_cl);

    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_cl,   bshape);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_cl, bshape_a);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_cl, bshape_v);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_cl, bshape_h);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_cl, bshape_sv);
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_cl, bshape_ct);
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