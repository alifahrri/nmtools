#include "nmtools/array/functional/pooling.hpp"
#include "nmtools/testing/data/array/pooling.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;

#define POOL2D_SUBCASE(subcase_name, function, array) \
SUBCASE(subcase_name) \
{ \
    auto result = function(array); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("avg_pool2d(case1)" * doctest::test_suite("functional::avg_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,avg_pool2d,case1);
    using namespace args;

    POOL2D_SUBCASE( "case1", fn::avg_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case1", fn::avg_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case1", fn::avg_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case1", fn::avg_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case1", fn::avg_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("avg_pool2d(case2)" * doctest::test_suite("functional::avg_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,avg_pool2d,case2);
    using namespace args;

    POOL2D_SUBCASE( "case2", fn::avg_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case2", fn::avg_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case2", fn::avg_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case2", fn::avg_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case2", fn::avg_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("avg_pool2d(case3)" * doctest::test_suite("functional::avg_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,avg_pool2d,case3);
    using namespace args;

    POOL2D_SUBCASE( "case3", fn::avg_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case3", fn::avg_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case3", fn::avg_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case3", fn::avg_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case3", fn::avg_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("avg_pool2d(case4)" * doctest::test_suite("functional::avg_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,avg_pool2d,case4);
    using namespace args;

    POOL2D_SUBCASE( "case4", fn::avg_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case4", fn::avg_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case4", fn::avg_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case4", fn::avg_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case4", fn::avg_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("avg_pool2d(case5)" * doctest::test_suite("functional::avg_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,avg_pool2d,case5);
    using namespace args;

    POOL2D_SUBCASE( "case5", fn::avg_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case5", fn::avg_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case5", fn::avg_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case5", fn::avg_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case5", fn::avg_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("avg_pool2d(case6)" * doctest::test_suite("functional::avg_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,avg_pool2d,case6);
    using namespace args;

    POOL2D_SUBCASE( "case6", fn::avg_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case6", fn::avg_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case6", fn::avg_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case6", fn::avg_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case6", fn::avg_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("avg_pool2d(case7)" * doctest::test_suite("functional::avg_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,avg_pool2d,case7);
    using namespace args;

    POOL2D_SUBCASE( "case7", fn::avg_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case7", fn::avg_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case7", fn::avg_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case7", fn::avg_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case7", fn::avg_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("avg_pool2d(case8)" * doctest::test_suite("functional::avg_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,avg_pool2d,case8);
    using namespace args;

    POOL2D_SUBCASE( "case8", fn::avg_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case8", fn::avg_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case8", fn::avg_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case8", fn::avg_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case8", fn::avg_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("avg_pool2d(case9)" * doctest::test_suite("functional::avg_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,avg_pool2d,case9);
    using namespace args;

    POOL2D_SUBCASE( "case9", fn::avg_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case9", fn::avg_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case9", fn::avg_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case9", fn::avg_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case9", fn::avg_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("avg_pool2d(case10)" * doctest::test_suite("functional::avg_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,avg_pool2d,case10);
    using namespace args;

    POOL2D_SUBCASE( "case10", fn::avg_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case10", fn::avg_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case10", fn::avg_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case10", fn::avg_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case10", fn::avg_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}

TEST_CASE("max_pool2d(case1)" * doctest::test_suite("functional::max_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,max_pool2d,case1);
    using namespace args;

    POOL2D_SUBCASE( "case1", fn::max_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case1", fn::max_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case1", fn::max_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case1", fn::max_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case1", fn::max_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("max_pool2d(case2)" * doctest::test_suite("functional::max_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,max_pool2d,case2);
    using namespace args;

    POOL2D_SUBCASE( "case2", fn::max_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case2", fn::max_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case2", fn::max_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case2", fn::max_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case2", fn::max_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("max_pool2d(case3)" * doctest::test_suite("functional::max_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,max_pool2d,case3);
    using namespace args;

    POOL2D_SUBCASE( "case3", fn::max_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case3", fn::max_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case3", fn::max_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case3", fn::max_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case3", fn::max_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("max_pool2d(case4)" * doctest::test_suite("functional::max_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,max_pool2d,case4);
    using namespace args;

    POOL2D_SUBCASE( "case4", fn::max_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case4", fn::max_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case4", fn::max_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case4", fn::max_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case4", fn::max_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("max_pool2d(case5)" * doctest::test_suite("functional::max_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,max_pool2d,case5);
    using namespace args;

    POOL2D_SUBCASE( "case5", fn::max_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case5", fn::max_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case5", fn::max_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case5", fn::max_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case5", fn::max_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("max_pool2d(case6)" * doctest::test_suite("functional::max_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,max_pool2d,case6);
    using namespace args;

    POOL2D_SUBCASE( "case6", fn::max_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case6", fn::max_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case6", fn::max_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case6", fn::max_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case6", fn::max_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("max_pool2d(case7)" * doctest::test_suite("functional::max_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,max_pool2d,case7);
    using namespace args;

    POOL2D_SUBCASE( "case7", fn::max_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case7", fn::max_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case7", fn::max_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case7", fn::max_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case7", fn::max_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("max_pool2d(case8)" * doctest::test_suite("functional::max_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,max_pool2d,case8);
    using namespace args;

    POOL2D_SUBCASE( "case8", fn::max_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case8", fn::max_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case8", fn::max_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case8", fn::max_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case8", fn::max_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("max_pool2d(case9)" * doctest::test_suite("functional::max_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,max_pool2d,case9);
    using namespace args;

    POOL2D_SUBCASE( "case9", fn::max_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case9", fn::max_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case9", fn::max_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case9", fn::max_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case9", fn::max_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}


TEST_CASE("max_pool2d(case10)" * doctest::test_suite("functional::max_pool2d"))
{
    NMTOOLS_TESTING_USE_CASE(array,max_pool2d,case10);
    using namespace args;

    POOL2D_SUBCASE( "case10", fn::max_pool2d [kernel_size]   [stride]   [ceil_mode], array );
    POOL2D_SUBCASE( "case10", fn::max_pool2d [kernel_size_a] [stride_a] [ceil_mode], array_a );
    POOL2D_SUBCASE( "case10", fn::max_pool2d [kernel_size_f] [stride_f] [ceil_mode], array_f );
    POOL2D_SUBCASE( "case10", fn::max_pool2d [kernel_size_h] [stride_h] [ceil_mode], array_h );
    POOL2D_SUBCASE( "case10", fn::max_pool2d [kernel_size_v] [stride_v] [ceil_mode], array_d );
}

namespace view = nmtools::view;

TEST_CASE("max_pool2d" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(array,max_pool2d,case10);
    using namespace args;

    auto a = view::max_pool2d(array,kernel_size,stride,ceil_mode);

    auto function = fn::get_function_composition(a);
    auto expect = fn::max_pool2d[kernel_size][stride][ceil_mode];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}