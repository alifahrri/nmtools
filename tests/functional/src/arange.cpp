#include "nmtools/array/arange.hpp"
#include "nmtools/array/functional/arange.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nm::view;

using namespace nmtools::literals;

namespace utils = nmtools::utils;

TEST_CASE("arange" * doctest::test_suite("functional::get_function_composition"))
{
    {
        auto a = view::arange(10);
        auto function = fn::get_function_composition(a);

        NMTOOLS_ASSERT_EQUAL( function, fn::arange[0][10][1][nm::float32] );
    }
    {
        auto dtype = nm::float64;
        auto a = view::arange(10,dtype);
        auto function = fn::get_function_composition(a);

        NMTOOLS_ASSERT_EQUAL( function, fn::arange[0][10][1][dtype] );
    }
}

TEST_CASE("arange" * doctest::test_suite("functional::get_function_composition"))
{
    {
        auto dtype = nm::int64;
        auto a = view::arange(10,dtype);
        auto function = fn::get_function_composition(a);

        NMTOOLS_ASSERT_EQUAL( function, fn::arange[0][10][1][dtype] );
    }
    {
        auto dtype = nm::uint64;
        auto a = view::arange(10,dtype);
        auto function = fn::get_function_composition(a);

        NMTOOLS_ASSERT_EQUAL( function, fn::arange[0][10][1][dtype] );
    }

    {
        auto dtype = nm::int32;
        auto a = view::arange(10,dtype);
        auto function = fn::get_function_composition(a);

        NMTOOLS_ASSERT_EQUAL( function, fn::arange[0][10][1][dtype] );
    }
    {
        auto dtype = nm::uint32;
        auto a = view::arange(10,dtype);
        auto function = fn::get_function_composition(a);

        NMTOOLS_ASSERT_EQUAL( function, fn::arange[0][10][1][dtype] );
    }
    
    {
        auto dtype = nm::int16;
        auto a = view::arange(10,dtype);
        auto function = fn::get_function_composition(a);

        NMTOOLS_ASSERT_EQUAL( function, fn::arange[0][10][1][dtype] );
    }
    {
        auto dtype = nm::uint16;
        auto a = view::arange(10,dtype);
        auto function = fn::get_function_composition(a);

        NMTOOLS_ASSERT_EQUAL( function, fn::arange[0][10][1][dtype] );
    }

    {
        auto dtype = nm::int8;
        auto a = view::arange(10,dtype);
        auto function = fn::get_function_composition(a);

        NMTOOLS_ASSERT_EQUAL( function, fn::arange[0][10][1][dtype] );
    }
    {
        auto dtype = nm::uint8;
        auto a = view::arange(10,dtype);
        auto function = fn::get_function_composition(a);

        NMTOOLS_ASSERT_EQUAL( function, fn::arange[0][10][1][dtype] );
    }
}