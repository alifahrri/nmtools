#include "nmtools/array/functional/combinator.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace cb = nmtools::combinator;
namespace view = nmtools::view;

TEST_CASE("dig1(case1)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};

    auto f = cb::dig1;

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

TEST_CASE("dig1(case2)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};
    int c[3][1][1] = {{{4}},{{5}},{{6}}};

    auto f = cb::dig1;

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

TEST_CASE("dig2(case1)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};
    int c[3][1][1] = {{{4}},{{5}},{{6}}};

    auto f = cb::dig2;

    {
        auto result = f (a) (b) (c);
        auto expect = nm::pack_operands(c,a,b);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a,b,c);
        auto expect = nm::pack_operands(c,a,b);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b) (a) (c);
        auto expect = nm::pack_operands(c,b,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("dig2(case2)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};
    int c[3][1][1] = {{{4}},{{5}},{{6}}};
    int d[4][1][1][1] = {{{{7}}},{{{8}}},{{{9}}},{{{10}}}};

    auto f = cb::dig2;
    static_assert( decltype(f)::arity == 3 );

    {
        auto result = f (a,b,c,d);
        auto expect = nm::pack_operands(c,a,b,d);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d,c,a);
        auto expect = nm::pack_operands(c,b,d,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a) (b) (c,d);
        auto expect = nm::pack_operands(c,a,b,d);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b) (d) (c,a);
        auto expect = nm::pack_operands(c,b,d,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d) (c,a);
        auto expect = nm::pack_operands(c,b,d,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("dig2(case3)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};
    int c[3][1][1] = {{{4}},{{5}},{{6}}};
    int d[4][1][1][1] = {{{{7}}},{{{8}}},{{{9}}},{{{10}}}};
    int e[5][1][1][1][1] = {{{{{11}}}},{{{{12}}}},{{{{13}}}},{{{{14}}}},{{{{15}}}}};

    auto f = cb::dig2;
    static_assert( decltype(f)::arity == 3 );

    {
        auto result = f (a,b,c,d,e);
        auto expect = nm::pack_operands(c,a,b,d,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d,c,a,e);
        auto expect = nm::pack_operands(c,b,d,a,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a) (b) (c,d,e);
        auto expect = nm::pack_operands(c,a,b,d,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b) (d) (c,a,e);
        auto expect = nm::pack_operands(c,b,d,a,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d) (c,a,e);
        auto expect = nm::pack_operands(c,b,d,a,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("dig3(case1)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};
    int c[3][1][1] = {{{4}},{{5}},{{6}}};
    int d[4][1][1][1] = {{{{7}}},{{{8}}},{{{9}}},{{{10}}}};

    auto f = cb::dig_n<3>;
    static_assert( decltype(f)::arity == 4 );

    {
        auto result = f (a)(b)(c)(d);
        auto expect = nm::pack_operands(d,a,b,c);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a,b,c,d);
        auto expect = nm::pack_operands(d,a,b,c);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d,c,a);
        auto expect = nm::pack_operands(a,b,d,c);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a) (b) (c,d);
        auto expect = nm::pack_operands(d,a,b,c);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b) (d) (c,a);
        auto expect = nm::pack_operands(a,b,d,c);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d) (c,a);
        auto expect = nm::pack_operands(a,b,d,c);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("dig3(case2)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};
    int c[3][1][1] = {{{4}},{{5}},{{6}}};
    int d[4][1][1][1] = {{{{7}}},{{{8}}},{{{9}}},{{{10}}}};
    int e[5][1][1][1][1] = {{{{{11}}}},{{{{12}}}},{{{{13}}}},{{{{14}}}},{{{{15}}}}};

    auto f = cb::dig_n<3>;
    static_assert( decltype(f)::arity == 4 );

    {
        auto result = f (a) (b) (c) (d,e);
        auto expect = nm::pack_operands(d,a,b,c,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a,b,c,d,e);
        auto expect = nm::pack_operands(d,a,b,c,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d,c,a,e);
        auto expect = nm::pack_operands(a,b,d,c,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a) (b) (c,d,e);
        auto expect = nm::pack_operands(d,a,b,c,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b) (d) (c,a,e);
        auto expect = nm::pack_operands(a,b,d,c,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d) (c,a,e);
        auto expect = nm::pack_operands(a,b,d,c,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

#if 0
// crashed at runtime for clang,
// compile error for gcc:
// error: initializations for multiple members of 'std::_Optional_payload_base
// TODO: fix
TEST_CASE("dig2" * doctest::test_suite("combinator") * doctest::skip())
{
    auto a_shape = nmtools_array{2,3,2};
    auto a_numel = ix::product(a_shape);
    auto a_start = 0;
    auto a_stop  = a_start + a_numel;
    auto a_flat  = na::arange(a_start,a_stop);
    auto a = na::reshape(a_flat,a_shape);

    auto b_shape = nmtools_array{3,2};
    auto b_numel = ix::product(b_shape);
    auto b_start = -b_numel/2;
    auto b_stop  = b_start + b_numel;
    auto b_flat  = na::arange(b_start,b_stop);
    auto b = na::reshape(b_flat,b_shape);

    auto f = fn::add * cb::swap * fn::multiply * cb::swap * cb::dig2 * cb::dup;
    // (add * swap * multiply * swap * dig2 * dup) (a) (b)
    // (add * swap * multiply * swap * dig2) (a) (a) (b)
    // (add * swap * multiply * swap) (b) (a) (a)
    // (add * swap * multiply) (a) (b) (a)
    // (add * swap) (multiply(a,b)) (a)
    // (add) (a) (multiply(a,b))
    // add(a,multiply(a,b))

    auto result = f (a) (b);

    auto t1 = view::multiply(a,b);
    auto t2 = view::add(a,t1);
    auto expect = t2;

    NMTOOLS_ASSERT_CLOSE( result, expect );
}
#endif