#include "nmtools/index/broadcast_to.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/broadcast_to.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace kind = na::kind;

#define SHAPE_BROADCAST_TO_SUBCASE(case_name, ashape, bshape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, broadcast_to, case_name); \
    auto m_result = nmtools::index::shape_broadcast_to(args::ashape, args::bshape); \
    auto success  = static_cast<bool>(m_result); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    if ((success == expect::success) && success) { \
        const auto shape = nmtools::get<0>(nmtools::unwrap(m_result)); \
        const auto free  = nmtools::get<1>(nmtools::unwrap(m_result)); \
        NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
        NMTOOLS_ASSERT_EQUAL( free, expect::free ); \
    } \
}

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
        [[maybe_unused]] constexpr auto success = static_cast<bool>(broadcasted);
        [[maybe_unused]] constexpr auto shape = nmtools::get<0>(nmtools::unwrap(broadcasted));
        [[maybe_unused]] constexpr auto free  = nmtools::get<1>(nmtools::unwrap(broadcasted));
        [[maybe_unused]] constexpr auto expected_free = nmtools_array{true,true,false,true};
        NMTOOLS_STATIC_ASSERT( success );
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, bshape );
        NMTOOLS_STATIC_ASSERT_EQUAL( free, expected_free );
    }
}