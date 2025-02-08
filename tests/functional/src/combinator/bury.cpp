#include "nmtools/core/combinator.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/utility/apply_isequal.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace cb = nmtools::combinator;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

TEST_CASE("bury1(case1)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};

    auto f = cb::bury1;

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

#if 1
TEST_CASE("bury1(case2)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};
    int c[3][1][1] = {{{4}},{{5}},{{6}}};

    auto f = cb::bury1;

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

TEST_CASE("bury2(case1)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};
    int c[3][1][1] = {{{4}},{{5}},{{6}}};

    auto f = cb::bury2;

    {
        auto result = f (a) (b) (c);
        auto expect = nm::pack_operands(b,c,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a,b,c);
        auto expect = nm::pack_operands(b,c,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b) (a) (c);
        auto expect = nm::pack_operands(a,c,b);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("bury2(case2)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};
    int c[3][1][1] = {{{4}},{{5}},{{6}}};
    int d[4][1][1][1] = {{{{7}}},{{{8}}},{{{9}}},{{{10}}}};

    auto f = cb::bury2;
    static_assert( decltype(f)::arity == 3 );

    {
        auto result = f (a,b,c,d);
        auto expect = nm::pack_operands(b,c,a,d);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d,c,a);
        auto expect = nm::pack_operands(d,c,b,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a) (b) (c,d);
        auto expect = nm::pack_operands(b,c,a,d);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b) (d) (c,a);
        auto expect = nm::pack_operands(d,c,b,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d) (c,a);
        auto expect = nm::pack_operands(d,c,b,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("bury2(case3)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};
    int c[3][1][1] = {{{4}},{{5}},{{6}}};
    int d[4][1][1][1] = {{{{7}}},{{{8}}},{{{9}}},{{{10}}}};
    int e[5][1][1][1][1] = {{{{{11}}}},{{{{12}}}},{{{{13}}}},{{{{14}}}},{{{{15}}}}};

    auto f = cb::bury2;
    static_assert( decltype(f)::arity == 3 );

    {
        auto result = f (a,b,c,d,e);
        auto expect = nm::pack_operands(b,c,a,d,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d,c,a,e);
        auto expect = nm::pack_operands(d,c,b,a,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a) (b) (c,d,e);
        auto expect = nm::pack_operands(b,c,a,d,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b) (d) (c,a,e);
        auto expect = nm::pack_operands(d,c,b,a,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d) (c,a,e);
        auto expect = nm::pack_operands(d,c,b,a,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("bury3(case1)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};
    int c[3][1][1] = {{{4}},{{5}},{{6}}};
    int d[4][1][1][1] = {{{{7}}},{{{8}}},{{{9}}},{{{10}}}};

    auto f = cb::bury_n<3>;
    static_assert( decltype(f)::arity == 4 );

    {
        auto result = f (a)(b)(c)(d);
        auto expect = nm::pack_operands(b,c,d,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a,b,c,d);
        auto expect = nm::pack_operands(b,c,d,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d,c,a);
        auto expect = nm::pack_operands(d,c,a,b);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a) (b) (c,d);
        auto expect = nm::pack_operands(b,c,d,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b) (d) (c,a);
        auto expect = nm::pack_operands(d,c,a,b);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d) (c,a);
        auto expect = nm::pack_operands(d,c,a,b);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("bury3(case2)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};
    int c[3][1][1] = {{{4}},{{5}},{{6}}};
    int d[4][1][1][1] = {{{{7}}},{{{8}}},{{{9}}},{{{10}}}};
    int e[5][1][1][1][1] = {{{{{11}}}},{{{{12}}}},{{{{13}}}},{{{{14}}}},{{{{15}}}}};

    auto f = cb::bury_n<3>;
    static_assert( decltype(f)::arity == 4 );

    {
        auto result = f (a) (b) (c) (d,e);
        auto expect = nm::pack_operands(b,c,d,a,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a,b,c,d,e);
        auto expect = nm::pack_operands(b,c,d,a,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d,c,a,e);
        auto expect = nm::pack_operands(d,c,a,b,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (a) (b) (c,d,e);
        auto expect = nm::pack_operands(b,c,d,a,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b) (d) (c,a,e);
        auto expect = nm::pack_operands(d,c,a,b,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = f (b,d) (c,a,e);
        auto expect = nm::pack_operands(d,c,a,b,e);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("bury1" * doctest::test_suite("combinator"))
{
    auto a = nmtools_array{1,2,3};
    auto b = nmtools_array{1,2,3};

    auto f = fn::square * fn::add * cb::bury1;

    auto result = f (a) (b);

    auto e1 = view::add(b,a);
    auto expect = view::square(e1);

    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("bury2" * doctest::test_suite("combinator"))
{
    auto a = nmtools_array{1,2,3};
    auto b = nmtools_array{1,2,3};
    auto c = nmtools_array{1,2,3};

    auto f = fn::add * fn::square * fn::add * cb::bury2;

    auto result = f (a) (b) (c);

    auto e1 = view::add(b,c);
    auto e2 = view::square(e1);
    auto e3 = view::add(e2,a);
    auto expect = e3;

    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("bury2" * doctest::test_suite("combinator"))
{
    auto a = nmtools_array{1,2,3};
    auto b = nmtools_array{1,2,3};
    auto c = nmtools_array{1,2,3};

    auto axis = 0;

    auto f = fn::sum[axis] * fn::add * fn::square * fn::add * cb::bury2;

    auto result = f (a) (b) (c);

    auto e1 = view::add(b,c);
    auto e2 = view::square(e1);
    auto e3 = view::add(e2,a);
    auto e4 = view::sum(e3,axis);
    auto expect = e4;

    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("bury2" * doctest::test_suite("combinator"))
{
    auto a = nmtools_array{1,2,3};
    auto b = nmtools_array{1,2,3};
    auto c = nmtools_array{1,2,3};

    auto axis = 0;

    auto f = fn::sum[axis] * fn::square * fn::add * fn::add * cb::bury2;

    auto result = f (a) (b) (c);

    auto e1 = view::add(b,c);
    auto e2 = view::add(e1,a);
    auto e3 = view::square(e2);
    auto e4 = view::sum(e3,axis);
    auto expect = e4;

    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("bury2" * doctest::test_suite("combinator"))
{
    auto a = nmtools_array{1,2,3};
    auto b = nmtools_array{1,2,3};
    auto c = nmtools_array{1,2,3};

    auto axis = 0;

    auto f = fn::subtract * fn::divide * fn::sum[axis] * cb::bury2;

    NMTOOLS_ASSERT_EQUAL( decltype(f)::arity, 3 );

    auto result = f (a) (b) (c);

    auto e1 = view::sum(b,axis);
    auto e2 = view::divide(e1,c);
    auto e3 = view::subtract(e2,a);
    auto expect = e3;

    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("bury2" * doctest::test_suite("combinator"))
{
    
}

#if 1
// crashed at runtime for clang,
// compile error for gcc:
// error: initializations for multiple members of 'std::_Optional_payload_base
// TODO: fix
TEST_CASE("bury2" * doctest::test_suite("combinator") * doctest::skip())
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

    auto f = fn::subtract * fn::divide * fn::sum[0] * cb::bury2;

    // NOTE: broken
    // auto result = f (c) (a) (b);
    auto result = f (c,a,b);
    // TODO: support this
    // auto result = f * c * a * b;
    // (fn::subtract * fn::divide * fn::reduce_add * cb::bury2) (c) (a) (b)
    // (fn::subtract * fn::divide * fn::reduce_add) (a) (b) (c)
    // (fn::subtract * fn::divide) (fn::reduce_add(a)) (b) (c)
    // (fn::subtract) (fn::divide(fn::reduce_add(a),b)) (c)
    // fn::subtract(fn::divide(fn::reduce_add(a),b),c)

    auto t1 = view::sum(a,0);
    auto t2 = view::divide(t1,b);
    auto t3 = view::subtract(t2,c);
    auto expect = t3;

    NMTOOLS_ASSERT_CLOSE( result, expect );
}
#endif
#endif