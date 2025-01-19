#include "nmtools/index/roll.hpp"
#include "nmtools/testing/data/index/roll.hpp"
#include "nmtools/testing/doctest.hpp"

namespace meta = nmtools::meta;

#define ROLL_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, roll, case_name); \
    using namespace args; \
    auto result = nmtools::index::roll(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::result, __VA_ARGS__ ); \
}

TEST_CASE("roll(case1a1)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1a1, shape, indices, shift );
    ROLL_SUBCASE( case1a1, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1a1, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1a1, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1a1, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1a1, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1a1)" * doctest::test_suite("index::roll"))
{
    {
        using meta::to_value_v;
        NMTOOLS_TESTING_USE_CASE(index,roll,case1a1);
        using namespace args;
        NMTOOLS_ASSERT_EQUAL( to_value_v<decltype(shape_ct)>, shape );
        NMTOOLS_ASSERT_EQUAL( to_value_v<decltype(indices_ct)>, indices );
        NMTOOLS_ASSERT_EQUAL( to_value_v<decltype(shift_ct)>, shift );
        auto result = nmtools::index::roll(
            to_value_v<decltype(shape_ct)>
            , to_value_v<decltype(indices_ct)>
            , to_value_v<decltype(shift_ct)>
        );
        NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::result, to_value_v<decltype(shape_ct)>
            , to_value_v<decltype(indices_ct)>
            , to_value_v<decltype(shift_ct)> );
    }
}

TEST_CASE("roll(case1a2)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1a2, shape, indices, shift );
    ROLL_SUBCASE( case1a2, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1a2, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1a2, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1a2, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1a2, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1a3)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1a3, shape, indices, shift );
    ROLL_SUBCASE( case1a3, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1a3, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1a3, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1a3, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1a3, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1a4)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1a4, shape, indices, shift );
    ROLL_SUBCASE( case1a4, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1a4, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1a4, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1a4, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1a4, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1a5)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1a5, shape, indices, shift );
    ROLL_SUBCASE( case1a5, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1a5, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1a5, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1a5, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1a5, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1a6)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1a6, shape, indices, shift );
    ROLL_SUBCASE( case1a6, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1a6, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1a6, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1a6, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1a6, shape_ct, indices_ct, shift_ct );
}

/*===============================================================*/

TEST_CASE("roll(case1b1)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1b1, shape, indices, shift );
    ROLL_SUBCASE( case1b1, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1b1, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1b1, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1b1, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1b1, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1b2)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1b2, shape, indices, shift );
    ROLL_SUBCASE( case1b2, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1b2, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1b2, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1b2, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1b2, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1b3)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1b3, shape, indices, shift );
    ROLL_SUBCASE( case1b3, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1b3, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1b3, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1b3, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1b3, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1b4)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1b4, shape, indices, shift );
    ROLL_SUBCASE( case1b4, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1b4, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1b4, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1b4, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1b4, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1b5)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1b5, shape, indices, shift );
    ROLL_SUBCASE( case1b5, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1b5, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1b5, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1b5, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1b5, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1b6)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1b6, shape, indices, shift );
    ROLL_SUBCASE( case1b6, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1b6, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1b6, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1b6, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1b6, shape_ct, indices_ct, shift_ct );
}

/*===============================================================*/

TEST_CASE("roll(case1c1)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1c1, shape, indices, shift );
    ROLL_SUBCASE( case1c1, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1c1, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1c1, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1c1, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1c1, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1c2)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1c2, shape, indices, shift );
    ROLL_SUBCASE( case1c2, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1c2, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1c2, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1c2, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1c2, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1c3)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1c3, shape, indices, shift );
    ROLL_SUBCASE( case1c3, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1c3, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1c3, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1c3, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1c3, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1c4)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1c4, shape, indices, shift );
    ROLL_SUBCASE( case1c4, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1c4, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1c4, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1c4, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1c4, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1c5)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1c5, shape, indices, shift );
    ROLL_SUBCASE( case1c5, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1c5, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1c5, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1c5, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1c5, shape_ct, indices_ct, shift_ct );
}

TEST_CASE("roll(case1c6)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case1c6, shape, indices, shift );
    ROLL_SUBCASE( case1c6, shape_a, indices_a, shift );
    ROLL_SUBCASE( case1c6, shape_v, indices_v, shift );
    ROLL_SUBCASE( case1c6, shape_f, indices_f, shift );
    ROLL_SUBCASE( case1c6, shape_h, indices_h, shift );

    ROLL_SUBCASE( case1c6, shape_ct, indices_ct, shift_ct );
}

/*===============================================================*/

TEST_CASE("roll(case2c1)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2c1, shape, indices, shift, axis );
    ROLL_SUBCASE( case2c1, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2c1, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2c1, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2c1, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2c1, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case2c2)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2c2, shape, indices, shift, axis );
    ROLL_SUBCASE( case2c2, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2c2, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2c2, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2c2, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2c2, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case2c3)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2c3, shape, indices, shift, axis );
    ROLL_SUBCASE( case2c3, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2c3, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2c3, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2c3, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2c3, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case2c4)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2c4, shape, indices, shift, axis );
    ROLL_SUBCASE( case2c4, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2c4, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2c4, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2c4, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2c4, shape_ct, indices_ct, shift_ct, axis_ct );
}

/*===============================================================*/

TEST_CASE("roll(case2d1)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2d1, shape, indices, shift, axis );
    ROLL_SUBCASE( case2d1, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2d1, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2d1, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2d1, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2d1, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case2d2)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2d2, shape, indices, shift, axis );
    ROLL_SUBCASE( case2d2, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2d2, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2d2, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2d2, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2d2, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case2d3)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2d3, shape, indices, shift, axis );
    ROLL_SUBCASE( case2d3, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2d3, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2d3, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2d3, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2d3, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case2d4)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2d4, shape, indices, shift, axis );
    ROLL_SUBCASE( case2d4, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2d4, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2d4, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2d4, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2d4, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case2d5)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2d5, shape, indices, shift, axis );
    ROLL_SUBCASE( case2d5, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2d5, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2d5, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2d5, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2d5, shape_ct, indices_ct, shift_ct, axis_ct );
}

/*===============================================================*/

TEST_CASE("roll(case2e1)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2e1, shape, indices, shift, axis );
    ROLL_SUBCASE( case2e1, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2e1, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2e1, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2e1, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2e1, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case2e2)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2e2, shape, indices, shift, axis );
    ROLL_SUBCASE( case2e2, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2e2, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2e2, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2e2, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2e2, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case2e3)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2e3, shape, indices, shift, axis );
    ROLL_SUBCASE( case2e3, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2e3, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2e3, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2e3, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2e3, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case2e4)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2e4, shape, indices, shift, axis );
    ROLL_SUBCASE( case2e4, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2e4, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2e4, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2e4, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2e4, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case2e5)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case2e5, shape, indices, shift, axis );
    ROLL_SUBCASE( case2e5, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case2e5, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case2e5, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case2e5, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case2e5, shape_ct, indices_ct, shift_ct, axis_ct );
}

/*===============================================================*/

TEST_CASE("roll(case3b1)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case3b1, shape, indices, shift, axis );
    ROLL_SUBCASE( case3b1, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case3b1, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case3b1, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case3b1, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case3b1, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case3b2)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case3b2, shape, indices, shift, axis );
    ROLL_SUBCASE( case3b2, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case3b2, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case3b2, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case3b2, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case3b2, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case3b3)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case3b3, shape, indices, shift, axis );
    ROLL_SUBCASE( case3b3, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case3b3, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case3b3, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case3b3, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case3b3, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case3b4)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case3b4, shape, indices, shift, axis );
    ROLL_SUBCASE( case3b4, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case3b4, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case3b4, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case3b4, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case3b4, shape_ct, indices_ct, shift_ct, axis_ct );
}

TEST_CASE("roll(case3b5)" * doctest::test_suite("index::roll"))
{
    ROLL_SUBCASE( case3b5, shape, indices, shift, axis );
    ROLL_SUBCASE( case3b5, shape_a, indices_a, shift, axis );
    ROLL_SUBCASE( case3b5, shape_v, indices_v, shift, axis );
    ROLL_SUBCASE( case3b5, shape_f, indices_f, shift, axis );
    ROLL_SUBCASE( case3b5, shape_h, indices_h, shift, axis );

    ROLL_SUBCASE( case3b5, shape_ct, indices_ct, shift_ct, axis_ct );
}