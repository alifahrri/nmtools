#include "nmtools/array/index/concatenate.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/array/index/as_tuple.hpp"

#include "testing/doctest.hpp"

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
        int ashape[2]  = {2,2};
        int bshape[2]  = {1,2};
        int indices[2] = {0,0};
        int axis = 0;
        auto ashape_a = cast<int>(ashape);
        auto ashape_v = cast(ashape,kind::nested_vec);
        auto ashape_h = cast(ashape,kind::hybrid);
        auto ashape_t = idx::as_tuple(ashape_a);
        auto bshape_a = cast<int>(bshape);
        auto bshape_v = cast(bshape,kind::nested_vec);
        auto bshape_h = cast(bshape,kind::hybrid);
        auto bshape_t = idx::as_tuple(bshape_a);
        auto indices_a = cast<int>(indices);
        auto indices_v = cast(indices,kind::nested_vec);
        auto indices_h = cast(indices,kind::hybrid);
        auto indices_t = idx::as_tuple(indices_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto aflag = true;
        auto bflag = false;
        int a_idx[2] = {0,0};
        int b_idx[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int ashape[2]  = {2,2};
        int bshape[2]  = {1,2};
        int indices[2] = {2,1};
        int axis = 0;
        auto ashape_a = cast<int>(ashape);
        auto ashape_v = cast(ashape,kind::nested_vec);
        auto ashape_h = cast(ashape,kind::hybrid);
        auto ashape_t = idx::as_tuple(ashape_a);
        auto bshape_a = cast<int>(bshape);
        auto bshape_v = cast(bshape,kind::nested_vec);
        auto bshape_h = cast(bshape,kind::hybrid);
        auto bshape_t = idx::as_tuple(bshape_a);
        auto indices_a = cast<int>(indices);
        auto indices_v = cast(indices,kind::nested_vec);
        auto indices_h = cast(indices,kind::hybrid);
        auto indices_t = idx::as_tuple(indices_a);
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
        auto ashape_a = cast<int>(ashape);
        auto ashape_v = cast(ashape,kind::nested_vec);
        auto ashape_h = cast(ashape,kind::hybrid);
        auto ashape_t = idx::as_tuple(ashape_a);
        auto bshape_a = cast<int>(bshape);
        auto bshape_v = cast(bshape,kind::nested_vec);
        auto bshape_h = cast(bshape,kind::hybrid);
        auto bshape_t = idx::as_tuple(bshape_a);
        auto indices_a = cast<int>(indices);
        auto indices_v = cast(indices,kind::nested_vec);
        auto indices_h = cast(indices,kind::hybrid);
        auto indices_t = idx::as_tuple(indices_a);
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
        auto ashape_a = cast<int>(ashape);
        auto ashape_v = cast(ashape,kind::nested_vec);
        auto ashape_h = cast(ashape,kind::hybrid);
        auto ashape_t = idx::as_tuple(ashape_a);
        auto bshape_a = cast<int>(bshape);
        auto bshape_v = cast(bshape,kind::nested_vec);
        auto bshape_h = cast(bshape,kind::hybrid);
        auto bshape_t = idx::as_tuple(bshape_a);
        auto indices_a = cast<int>(indices);
        auto indices_v = cast(indices,kind::nested_vec);
        auto indices_h = cast(indices,kind::hybrid);
        auto indices_t = idx::as_tuple(indices_a);
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
        auto ashape_a = cast<int>(ashape);
        auto ashape_v = cast(ashape,kind::nested_vec);
        auto ashape_h = cast(ashape,kind::hybrid);
        auto ashape_t = idx::as_tuple(ashape_a);
        auto bshape_a = cast<int>(bshape);
        auto bshape_v = cast(bshape,kind::nested_vec);
        auto bshape_h = cast(bshape,kind::hybrid);
        auto bshape_t = idx::as_tuple(bshape_a);
        auto indices_a = cast<int>(indices);
        auto indices_v = cast(indices,kind::nested_vec);
        auto indices_h = cast(indices,kind::hybrid);
        auto indices_t = idx::as_tuple(indices_a);
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
        auto ashape_a = cast<int>(ashape);
        auto ashape_v = cast(ashape,kind::nested_vec);
        auto ashape_h = cast(ashape,kind::hybrid);
        auto ashape_t = idx::as_tuple(ashape_a);
        auto bshape_a = cast<int>(bshape);
        auto bshape_v = cast(bshape,kind::nested_vec);
        auto bshape_h = cast(bshape,kind::hybrid);
        auto bshape_t = idx::as_tuple(bshape_a);
        auto indices_a = cast<int>(indices);
        auto indices_v = cast(indices,kind::nested_vec);
        auto indices_h = cast(indices,kind::hybrid);
        auto indices_t = idx::as_tuple(indices_a);
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
        auto ashape_a = cast<int>(ashape);
        auto ashape_v = cast(ashape,kind::nested_vec);
        auto ashape_h = cast(ashape,kind::hybrid);
        auto ashape_t = idx::as_tuple(ashape_a);
        auto bshape_a = cast<int>(bshape);
        auto bshape_v = cast(bshape,kind::nested_vec);
        auto bshape_h = cast(bshape,kind::hybrid);
        auto bshape_t = idx::as_tuple(bshape_a);
        auto indices_a = cast<int>(indices);
        auto indices_v = cast(indices,kind::nested_vec);
        auto indices_h = cast(indices,kind::hybrid);
        auto indices_t = idx::as_tuple(indices_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto aflag = true;
        auto bflag = false;
        int a_idx[2] = {1,0};
        int b_idx[2] = {0,0};
    }
}

#ifdef __clang__
#define CONCATENATE_SUBCASE(case_name, ashape, bshape, indices, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index,concatenate,case_name); \
    auto result = idx::concatenate(args::ashape,args::bshape,args::indices,args::axis); \
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
    auto [aflag,bflag,a_idx,b_idx] = idx::concatenate(args::ashape,args::bshape,args::indices,args::axis); \
    NMTOOLS_ASSERT_EQUAL( aflag, expect::aflag ); \
    NMTOOLS_ASSERT_EQUAL( bflag, expect::bflag ); \
    if (expect::aflag) \
        NMTOOLS_ASSERT_EQUAL( a_idx, expect::a_idx ); \
    if (expect::bflag) \
        NMTOOLS_ASSERT_EQUAL( b_idx, expect::b_idx ); \
}
#endif // __clang__

TEST_CASE("concatenate(raw)" * doctest::test_suite("index::concatenate"))
{
    CONCATENATE_SUBCASE( case1, ashape, bshape, indices, axis );
    CONCATENATE_SUBCASE( case2, ashape, bshape, indices, axis );
    CONCATENATE_SUBCASE( case3, ashape, bshape, indices, axis );
    CONCATENATE_SUBCASE( case4, ashape, bshape, indices, axis );
}

TEST_CASE("concatenate(array)" * doctest::test_suite("index::concatenate"))
{
    CONCATENATE_SUBCASE( case1, ashape_a, bshape_a, indices_a, axis );
    CONCATENATE_SUBCASE( case2, ashape_a, bshape_a, indices_a, axis );
    CONCATENATE_SUBCASE( case3, ashape_a, bshape_a, indices_a, axis );
    CONCATENATE_SUBCASE( case4, ashape_a, bshape_a, indices_a, axis );
    CONCATENATE_SUBCASE( case5, ashape_a, bshape_a, indices_a, axis );
    CONCATENATE_SUBCASE( case6, ashape_a, bshape_a, indices_a, axis );
    CONCATENATE_SUBCASE( case7, ashape_a, bshape_a, indices_a, axis );
}

TEST_CASE("concatenate(vector)" * doctest::test_suite("index::concatenate"))
{
    CONCATENATE_SUBCASE( case1, ashape_v, bshape_v, indices_v, axis );
    CONCATENATE_SUBCASE( case2, ashape_v, bshape_v, indices_v, axis );
    CONCATENATE_SUBCASE( case3, ashape_v, bshape_v, indices_v, axis );
    CONCATENATE_SUBCASE( case4, ashape_v, bshape_v, indices_v, axis );
    CONCATENATE_SUBCASE( case5, ashape_v, bshape_v, indices_v, axis );
    CONCATENATE_SUBCASE( case6, ashape_v, bshape_v, indices_v, axis );
    CONCATENATE_SUBCASE( case7, ashape_v, bshape_v, indices_v, axis );
}

TEST_CASE("concatenate(tuple)" * doctest::test_suite("index::concatenate"))
{
    CONCATENATE_SUBCASE( case1, ashape_t, bshape_t, indices_t, axis );
    CONCATENATE_SUBCASE( case2, ashape_t, bshape_t, indices_t, axis );
    CONCATENATE_SUBCASE( case3, ashape_t, bshape_t, indices_t, axis );
    CONCATENATE_SUBCASE( case4, ashape_t, bshape_t, indices_t, axis );
    CONCATENATE_SUBCASE( case5, ashape_t, bshape_t, indices_t, axis );
    CONCATENATE_SUBCASE( case6, ashape_t, bshape_t, indices_t, axis );
    CONCATENATE_SUBCASE( case7, ashape_t, bshape_t, indices_t, axis );
}

TEST_CASE("concatenate(hybrid_ndarray)" * doctest::test_suite("index::concatenate"))
{
    CONCATENATE_SUBCASE( case1, ashape_h, bshape_h, indices_h, axis );
    CONCATENATE_SUBCASE( case2, ashape_h, bshape_h, indices_h, axis );
    CONCATENATE_SUBCASE( case3, ashape_h, bshape_h, indices_h, axis );
    CONCATENATE_SUBCASE( case4, ashape_h, bshape_h, indices_h, axis );
    CONCATENATE_SUBCASE( case5, ashape_h, bshape_h, indices_h, axis );
    CONCATENATE_SUBCASE( case6, ashape_h, bshape_h, indices_h, axis );
    CONCATENATE_SUBCASE( case7, ashape_h, bshape_h, indices_h, axis );
}