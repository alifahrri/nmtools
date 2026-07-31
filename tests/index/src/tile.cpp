#include "nmtools/array/tile.hpp"
#include "nmtools/testing/data/index/tile.hpp"
#include "nmtools/ndarray.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;

using namespace nmtools::literals;

#define SHAPE_TILE_SUBCASE(case_name,shape,reps) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( shape_tile, case_name ); \
    auto result = nmtools::index::shape_tile( args::shape,args::reps ); \
    NMTOOLS_ASSERT_EQUAL( result, expect:: result ); \
}

#define SHAPE_TILE_EXPECTED_SUBCASE(case_name,expected,shape,reps) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( shape_tile, case_name ); \
    auto result = nmtools::index::shape_tile( args::shape,args::reps ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

#define CONSTEXPR_SHAPE_TILE_SUBCASE(case_name,shape,reps) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( constexpr_shape_tile, case_name ); \
    constexpr auto result = nmtools::index::shape_tile( args::shape,args::reps ); \
    NMTOOLS_ASSERT_EQUAL( result, expect:: result ); \
}

TEST_CASE("shape_tile(case1)" * doctest::test_suite("index::shape_tile"))
{
    SHAPE_TILE_SUBCASE( case1, shape, reps );
    SHAPE_TILE_SUBCASE( case1, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case1, shape_v, reps_v );
    SHAPE_TILE_SUBCASE( case1, shape_f, reps_f );
    SHAPE_TILE_SUBCASE( case1, shape_h, reps_h );

    SHAPE_TILE_SUBCASE( case1, shape_ct, reps_ct );
    SHAPE_TILE_SUBCASE( case1, shape_ct, reps_cl );
    SHAPE_TILE_SUBCASE( case1, shape_ct, reps_a );
    SHAPE_TILE_SUBCASE( case1, shape_ct, reps_v );
    SHAPE_TILE_SUBCASE( case1, shape_ct, reps_f );
    SHAPE_TILE_SUBCASE( case1, shape_ct, reps_h );

    SHAPE_TILE_SUBCASE( case1, shape_cl, reps_cl );
    SHAPE_TILE_SUBCASE( case1, shape_cl, reps_ct );
    SHAPE_TILE_SUBCASE( case1, shape_cl, reps_a );
    SHAPE_TILE_SUBCASE( case1, shape_cl, reps_v );
    SHAPE_TILE_SUBCASE( case1, shape_cl, reps_f );
    SHAPE_TILE_SUBCASE( case1, shape_cl, reps_h );

    SHAPE_TILE_EXPECTED_SUBCASE( case1, result_nl, shape_nl, reps_nl );
}

TEST_CASE("shape_tile(case2)" * doctest::test_suite("index::shape_tile"))
{
    SHAPE_TILE_SUBCASE( case2, shape, reps );
    SHAPE_TILE_SUBCASE( case2, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case2, shape_v, reps_v );
    SHAPE_TILE_SUBCASE( case2, shape_f, reps_f );
    SHAPE_TILE_SUBCASE( case2, shape_h, reps_h );

    SHAPE_TILE_SUBCASE( case2, shape_ct, reps_ct );
    SHAPE_TILE_SUBCASE( case2, shape_ct, reps_cl );
    SHAPE_TILE_SUBCASE( case2, shape_ct, reps_a );
    SHAPE_TILE_SUBCASE( case2, shape_ct, reps_v );
    SHAPE_TILE_SUBCASE( case2, shape_ct, reps_f );
    SHAPE_TILE_SUBCASE( case2, shape_ct, reps_h );

    SHAPE_TILE_SUBCASE( case2, shape_cl, reps_cl );
    SHAPE_TILE_SUBCASE( case2, shape_cl, reps_ct );
    SHAPE_TILE_SUBCASE( case2, shape_cl, reps_a );
    SHAPE_TILE_SUBCASE( case2, shape_cl, reps_v );
    SHAPE_TILE_SUBCASE( case2, shape_cl, reps_f );
    SHAPE_TILE_SUBCASE( case2, shape_cl, reps_h );

    SHAPE_TILE_EXPECTED_SUBCASE( case2, result_nl1, shape_nl1, reps_nl1 );
    SHAPE_TILE_EXPECTED_SUBCASE( case2, result_nl2, shape_nl2, reps_nl2 );

    // static_assert( nm::is_mixed_index_array_v<decltype(nmtools_tuple{3})> );
    
    SHAPE_TILE_SUBCASE( case2, shape_mx2, reps_mx2 );
}

TEST_CASE("shape_tile(case3)" * doctest::test_suite("index::shape_tile"))
{
    SHAPE_TILE_SUBCASE( case3, shape, reps );
    SHAPE_TILE_SUBCASE( case3, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case3, shape_v, reps_v );
    SHAPE_TILE_SUBCASE( case3, shape_f, reps_f );
    SHAPE_TILE_SUBCASE( case3, shape_h, reps_h );

    SHAPE_TILE_SUBCASE( case3, shape_ct, reps_ct );
    SHAPE_TILE_SUBCASE( case3, shape_ct, reps_cl );
    SHAPE_TILE_SUBCASE( case3, shape_ct, reps_a );
    SHAPE_TILE_SUBCASE( case3, shape_ct, reps_v );
    SHAPE_TILE_SUBCASE( case3, shape_ct, reps_f );
    SHAPE_TILE_SUBCASE( case3, shape_ct, reps_h );

    SHAPE_TILE_SUBCASE( case3, shape_cl, reps_cl );
    SHAPE_TILE_SUBCASE( case3, shape_cl, reps_ct );
    SHAPE_TILE_SUBCASE( case3, shape_cl, reps_a );
    SHAPE_TILE_SUBCASE( case3, shape_cl, reps_v );
    SHAPE_TILE_SUBCASE( case3, shape_cl, reps_f );
    SHAPE_TILE_SUBCASE( case3, shape_cl, reps_h );

    SHAPE_TILE_EXPECTED_SUBCASE( case3, result_nl1, shape_nl1, reps_nl1 );
    SHAPE_TILE_EXPECTED_SUBCASE( case3, result_nl2, shape_nl2, reps_nl2 );

    SHAPE_TILE_SUBCASE( case3, shape_mx1, reps_mx1 );
    SHAPE_TILE_SUBCASE( case3, shape_mx2, reps_mx2 );
}

TEST_CASE("shape_tile(case4)" * doctest::test_suite("index::shape_tile"))
{
    SHAPE_TILE_SUBCASE( case4, shape, reps );
    SHAPE_TILE_SUBCASE( case4, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case4, shape_v, reps_v );
    SHAPE_TILE_SUBCASE( case4, shape_f, reps_f );
    SHAPE_TILE_SUBCASE( case4, shape_h, reps_h );

    SHAPE_TILE_SUBCASE( case4, shape_ct, reps_ct );
    SHAPE_TILE_SUBCASE( case4, shape_ct, reps_cl );
    SHAPE_TILE_SUBCASE( case4, shape_ct, reps_a );
    SHAPE_TILE_SUBCASE( case4, shape_ct, reps_v );
    SHAPE_TILE_SUBCASE( case4, shape_ct, reps_f );
    SHAPE_TILE_SUBCASE( case4, shape_ct, reps_h );

    SHAPE_TILE_SUBCASE( case4, shape_cl, reps_cl );
    SHAPE_TILE_SUBCASE( case4, shape_cl, reps_ct );
    SHAPE_TILE_SUBCASE( case4, shape_cl, reps_a );
    SHAPE_TILE_SUBCASE( case4, shape_cl, reps_v );
    SHAPE_TILE_SUBCASE( case4, shape_cl, reps_f );
    SHAPE_TILE_SUBCASE( case4, shape_cl, reps_h );

    SHAPE_TILE_EXPECTED_SUBCASE( case4, result_nl1, shape_nl1, reps_nl1 );
    SHAPE_TILE_EXPECTED_SUBCASE( case4, result_nl2, shape_nl2, reps_nl2 );

    SHAPE_TILE_SUBCASE( case4, shape_mx1, reps_mx1 );
    SHAPE_TILE_SUBCASE( case4, shape_mx2, reps_mx2 );
}

TEST_CASE("shape_tile(case5)" * doctest::test_suite("index::shape_tile"))
{
    SHAPE_TILE_SUBCASE( case5, shape, reps );
    SHAPE_TILE_SUBCASE( case5, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case5, shape_v, reps_v );
    SHAPE_TILE_SUBCASE( case5, shape_f, reps_f );
    SHAPE_TILE_SUBCASE( case5, shape_h, reps_h );

    SHAPE_TILE_SUBCASE( case5, shape_ct, reps_ct );
    SHAPE_TILE_SUBCASE( case5, shape_ct, reps_cl );
    SHAPE_TILE_SUBCASE( case5, shape_ct, reps_a );
    SHAPE_TILE_SUBCASE( case5, shape_ct, reps_v );
    SHAPE_TILE_SUBCASE( case5, shape_ct, reps_f );
    SHAPE_TILE_SUBCASE( case5, shape_ct, reps_h );

    SHAPE_TILE_SUBCASE( case5, shape_cl, reps_cl );
    SHAPE_TILE_SUBCASE( case5, shape_cl, reps_ct );
    SHAPE_TILE_SUBCASE( case5, shape_cl, reps_a );
    SHAPE_TILE_SUBCASE( case5, shape_cl, reps_v );
    SHAPE_TILE_SUBCASE( case5, shape_cl, reps_f );
    SHAPE_TILE_SUBCASE( case5, shape_cl, reps_h );

    SHAPE_TILE_EXPECTED_SUBCASE( case5, result_nl1, shape_nl1, reps_nl1 );
    SHAPE_TILE_EXPECTED_SUBCASE( case5, result_nl2, shape_nl2, reps_nl2 );

    SHAPE_TILE_SUBCASE( case5, shape_mx1, reps_mx1 );
    SHAPE_TILE_SUBCASE( case5, shape_mx2, reps_mx2 );
}

TEST_CASE("shape_tile(case6)" * doctest::test_suite("index::shape_tile"))
{
    SHAPE_TILE_SUBCASE( case6, shape, reps );
    SHAPE_TILE_SUBCASE( case6, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case6, shape_v, reps_v );
    SHAPE_TILE_SUBCASE( case6, shape_f, reps_f );
    SHAPE_TILE_SUBCASE( case6, shape_h, reps_h );

    SHAPE_TILE_SUBCASE( case6, shape_ct, reps_ct );
    SHAPE_TILE_SUBCASE( case6, shape_ct, reps_cl );
    SHAPE_TILE_SUBCASE( case6, shape_ct, reps_a );
    SHAPE_TILE_SUBCASE( case6, shape_ct, reps_v );
    SHAPE_TILE_SUBCASE( case6, shape_ct, reps_f );
    SHAPE_TILE_SUBCASE( case6, shape_ct, reps_h );

    SHAPE_TILE_SUBCASE( case6, shape_cl, reps_cl );
    SHAPE_TILE_SUBCASE( case6, shape_cl, reps_ct );
    SHAPE_TILE_SUBCASE( case6, shape_cl, reps_a );
    SHAPE_TILE_SUBCASE( case6, shape_cl, reps_v );
    SHAPE_TILE_SUBCASE( case6, shape_cl, reps_f );
    SHAPE_TILE_SUBCASE( case6, shape_cl, reps_h );

    SHAPE_TILE_EXPECTED_SUBCASE( case6, result_nl1, shape_nl1, reps_nl1 );
    SHAPE_TILE_EXPECTED_SUBCASE( case6, result_nl2, shape_nl2, reps_nl2 );

    SHAPE_TILE_SUBCASE( case6, shape_mx1, reps_mx1 );
    SHAPE_TILE_SUBCASE( case6, shape_mx2, reps_mx2 );
}


TEST_CASE("shape_tile(case1)" * doctest::test_suite("index::constexpr_shape_tile"))
{
    CONSTEXPR_SHAPE_TILE_SUBCASE( case1, shape, reps );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case1, shape_a, reps_a );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case1, shape_f, reps_f );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case1, shape_h, reps_h );

    CONSTEXPR_SHAPE_TILE_SUBCASE( case1, shape_ct, reps_ct );
}

TEST_CASE("shape_tile(case2)" * doctest::test_suite("index::constexpr_shape_tile"))
{
    CONSTEXPR_SHAPE_TILE_SUBCASE( case2, shape, reps );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case2, shape_a, reps_a );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case2, shape_f, reps_f );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case2, shape_h, reps_h );

    CONSTEXPR_SHAPE_TILE_SUBCASE( case2, shape_ct, reps_ct );
}

TEST_CASE("shape_tile(case3)" * doctest::test_suite("index::constexpr_shape_tile"))
{
    CONSTEXPR_SHAPE_TILE_SUBCASE( case3, shape, reps );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case3, shape_a, reps_a );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case3, shape_f, reps_f );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case3, shape_h, reps_h );

    CONSTEXPR_SHAPE_TILE_SUBCASE( case4, shape_ct, reps_ct );
}

TEST_CASE("shape_tile(case4)" * doctest::test_suite("index::constexpr_shape_tile"))
{
    CONSTEXPR_SHAPE_TILE_SUBCASE( case4, shape, reps );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case4, shape_a, reps_a );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case4, shape_f, reps_f );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case4, shape_h, reps_h );

    CONSTEXPR_SHAPE_TILE_SUBCASE( case4, shape_ct, reps_ct );
}

TEST_CASE("shape_tile(case5)" * doctest::test_suite("index::constexpr_shape_tile"))
{
    CONSTEXPR_SHAPE_TILE_SUBCASE( case5, shape, reps );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case5, shape_a, reps_a );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case5, shape_f, reps_f );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case5, shape_h, reps_h );

    CONSTEXPR_SHAPE_TILE_SUBCASE( case5, shape_ct, reps_ct );
}

#include "nmtools/ndarray.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

#define TILE_SUBCASE(case_name, shape, reps, indices) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(tile, case_name) \
    auto result = nmtools::index::tile( args::shape, args::reps, args::indices); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("tile(case1)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case1, shape, reps, indices );
    TILE_SUBCASE( case1, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case1, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case1, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case1, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case2)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case2, shape, reps, indices );
    TILE_SUBCASE( case2, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case2, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case2, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case2, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case3)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case3, shape, reps, indices );
    TILE_SUBCASE( case3, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case3, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case3, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case3, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case4)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case4, shape, reps, indices );
    TILE_SUBCASE( case4, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case4, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case4, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case4, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case5)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case5, shape, reps, indices );
    TILE_SUBCASE( case5, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case5, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case5, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case5, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case6)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case6, shape, reps, indices );
    TILE_SUBCASE( case6, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case6, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case6, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case6, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case7)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case7, shape, reps, indices );
    TILE_SUBCASE( case7, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case7, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case7, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case7, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case8)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case8, shape, reps, indices );
    TILE_SUBCASE( case8, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case8, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case8, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case8, shape_h, reps_h, indices_h );
}