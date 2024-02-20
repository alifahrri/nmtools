#include "nmtools/array/functional/reshape.hpp"
#include "nmtools/testing/data/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

TEST_CASE("reshape(case1)" * doctest::test_suite("functional::reshape"))
{
    NMTOOLS_TESTING_DECLARE_NS(reshape,case1);
    using namespace args;

    {
        [[maybe_unused]] auto reshape  = fn::reshape[newshape_a];
        [[maybe_unused]] auto reshaped = reshape(array_a);
        NMTOOLS_ASSERT_EQUAL( reshaped, expect::expected );
    }

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
}

namespace view = nmtools::view;

TEST_CASE("reshape" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(reshape,case1);
    using namespace args;

    auto a = view::reshape(array,newshape);

    auto function = fn::get_function_composition(a);
    auto expect = fn::reshape[newshape];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}