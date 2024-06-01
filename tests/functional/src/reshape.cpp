#include "nmtools/array/functional/reshape.hpp"
#include "nmtools/testing/data/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#if 1
TEST_CASE("reshape(case1)" * doctest::test_suite("functional::reshape"))
{
    NMTOOLS_TESTING_USE_CASE(reshape,case1);
    using namespace args;

    {
        [[maybe_unused]] auto reshape  = fn::reshape[newshape_a];
        [[maybe_unused]] auto reshaped = reshape(array_a);
        NMTOOLS_ASSERT_EQUAL( reshaped, expect::expected );
    }

    // breaks on gcc:
    // error: initializations for multiple members of 'std::_Optional_payload_base
    // TODO: fix on gcc
    #if defined(__clang__)
    {
        [[maybe_unused]] auto reshape_1 = fn::reshape[newshape_a];
        NMTOOLS_ASSERT_EQUAL( reshape_1.arity, 1 );
        [[maybe_unused]] auto reshape_2 = reshape_1 * fn::reshape[newshape];
        NMTOOLS_ASSERT_EQUAL( reshape_2.arity, 1 );
        [[maybe_unused]] auto reshape_3 = fn::reshape[newshape_v] * reshape_2;
        NMTOOLS_ASSERT_EQUAL( reshape_3.arity, 1 );
        [[maybe_unused]] auto reshape_4 = reshape_3 * reshape_2;
        NMTOOLS_ASSERT_EQUAL( reshape_4.arity, 1 );
        [[maybe_unused]] auto reshape_5 = reshape_4 * fn::reshape[newshape_ct];
        NMTOOLS_ASSERT_EQUAL( reshape_5.arity, 1 );
        // TODO: fix utl tuple
        #ifndef NMTOOLS_DISABLE_STL
        [[maybe_unused]] auto reshape_6 = reshape_5 * reshape_4 * reshape_3;
        [[maybe_unused]] auto reshaped = reshape_4(array_a);
        NMTOOLS_ASSERT_EQUAL( reshaped, expect::expected );
        #endif
    }
    #endif
}
#endif

namespace view = nmtools::view;
using nmtools::unwrap;

TEST_CASE("reshape" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_USE_CASE(reshape,case1);
    using namespace args;

    auto a = view::reshape(array,newshape);

    auto function = fn::get_function_composition(a);
    auto expect = fn::reshape[newshape];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("reshape" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(reshape,case1);
    using namespace args;

    auto a = view::reshape(array,newshape);

    auto function = fn::get_function_composition(a);
    auto expect = fn::indexing[unwrap(a).attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}