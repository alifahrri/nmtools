#include "nmtools/core/combinator.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace cb = nmtools::combinator;
namespace view = nmtools::view;
namespace meta = nmtools::meta;

TEST_CASE("swap(case1)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};

    auto f = cb::swap;

    {
        auto result = f (a) (b);
        auto expect = nm::pack_operands(b,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a,b);
        auto expect = nm::pack_operands(b,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b) (a);
        auto expect = nm::pack_operands(a,b);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("swap(case2)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};
    int c[3][1][1] = {{{4}},{{5}},{{6}}};

    auto f = cb::swap;

    {
        auto result = f (a,b,c);
        auto expect = nm::pack_operands(b,a,c);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,c,a);
        auto expect = nm::pack_operands(c,b,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (c,a,b);
        auto expect = nm::pack_operands(a,c,b);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

#if 0
// crashed at runtime for clang,
// compile error for gcc:
// error: initializations for multiple members of 'std::_Optional_payload_base
// TODO: fix
TEST_CASE("swap" * doctest::test_suite("combinator") * doctest::skip())
{
    auto a_shape = nmtools_array{2,3,2};
    auto a_numel = ix::product(a_shape);
    auto a_start = 0;
    auto a_stop  = a_start + a_numel;
    auto a_flat  = na::arange(a_start,a_stop);
    auto a = na::reshape(a_flat,a_shape);

    auto c_shape = nmtools_array{3,2};
    auto c_numel = ix::product(c_shape);
    auto c_start = -c_numel/2;
    auto c_stop  = c_start + c_numel;
    auto c_flat  = na::arange(c_start,c_stop);
    auto c = na::reshape(c_flat,c_shape);

    auto b = a_numel;

    auto f = fn::subtract * cb::swap * fn::divide;
    auto result = f (a) (b) (c);
    // auto result = f (a,b,c);
    // (fn::subtract * cb::swap) (fn::divide(a,b)) (c)
    // (fn::subtract) (c) (fn::divide(a,b))
    // fn::subtract(c,fn::divide(a,b))

    auto t1 = view::divide(a,b);
    auto t2 = view::subtract(c,t1);
    auto expect = t2;

    NMTOOLS_ASSERT_CLOSE( result, expect );
}
#endif