#include "nmtools/core/combinator.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/sum.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace cb = nmtools::combinator;

TEST_CASE("dup(case1)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};

    auto f = cb::dup;

    {
        auto result = f (a);
        auto expect = nm::pack_operands(a,a);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("dup(case1)" * doctest::test_suite("combinator"))
{
    int a[1] = {1};
    int b[1][2] = {{2,3}};

    auto f = cb::dup;

    {
        auto result = f (a,b);
        auto expect = nm::pack_operands(a,a,b);
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

#if 0
// crashed at runtime for clang,
// compile error for gcc:
// error: initializations for multiple members of 'std::_Optional_payload_base
// TODO: fix
TEST_CASE("dup" * doctest::test_suite("combinator") * doctest::skip())
{
    auto a_shape = nmtools_array{2,3,2};
    auto a_numel = ix::product(a_shape);
    auto a_start = 0;
    auto a_stop  = a_start + a_numel;
    auto a_flat  = na::arange(a_start,a_stop);
    auto a = na::reshape(a_flat,a_shape);

    auto f = fn::add * cb::dup;
    
    [[maybe_unused]]
    auto result = f (a);
    // (fn::add * cb::dup) (a)
    // (fn::add) (a) (a)

    auto expect = fn::add (a) (a);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}
#endif