// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "testing/testing.hpp"
#include "testing/data/blas.hpp"
#include "testing/data/utility.hpp"

#include "doctest/doctest.h"

#include <array>
#include <vector>

/**
 * @brief define testing using doctest
 * 
 */
#define NMTOOLS_ASSERT_CLOSE NMTOOLS_ASSERT_CLOSE_DOCTEST

/**
 * @brief check if we should disable benchmark
 * 
 */
#ifdef NMTOOLS_TESTING_DOCTEST_DISABLE_BENCH
namespace nmt = nmtools;
#define NMTOOLS_TEST_SUBCASE NMTOOLS_TESTING_DOCTEST_SUBCASE
#else
// TODO: rename to nmtools/bench/common.hpp or something
#include "common.hpp"
// TODO: rename to nmtools/bench/utility.hpp or something
#include "utility.hpp"
namespace nmt = nmtools::bench::nanobench;
#define NMTOOLS_TEST_SUBCASE NMTOOLS_BENCH_DOCTEST_SUBCASE
#endif


TEST_CASE("utility")
{
    using namespace nmtools::testing::data;
    {
        using namespace common_matrix::magic;
        auto row_expect = std::array<double,5>{ 4, 6, 13, 20, 22};
        auto col_expect = std::array<double,5>{ 1, 7, 13, 19, 25};
        NMTOOLS_TEST_SUBCASE( nmt::at, 13, mad5x5, 2, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::at, 13, mvd5x5, 2, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::at, 13, mfd5x5, 2, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::at, 13, maf5x5, 2, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::at, 13, mvf5x5, 2, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::at, 13, mff5x5, 2, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::row, row_expect, mad5x5, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::row, row_expect, mvd5x5, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::row, row_expect, mfd5x5, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::row, row_expect, maf5x5, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::row, row_expect, mvf5x5, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::row, row_expect, mff5x5, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::column, col_expect, mad5x5, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::column, col_expect, mfd5x5, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::column, col_expect, mvd5x5, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::column, col_expect, maf5x5, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::column, col_expect, mff5x5, 2 );
        NMTOOLS_TEST_SUBCASE( nmt::column, col_expect, mvf5x5, 2 );
    }
    {
        using namespace slice::case1;
        using args::start;
        using args::end;
        NMTOOLS_TEST_SUBCASE( (nmt::slice<start,end>), expect::x, args::xad );
        NMTOOLS_TEST_SUBCASE( (nmt::slice<start,end>), expect::x, args::xvd );
        NMTOOLS_TEST_SUBCASE( (nmt::slice<start,end>), expect::x, args::xfd );
        NMTOOLS_TEST_SUBCASE( (nmt::slice<start,end>), expect::x, args::xaf );
        NMTOOLS_TEST_SUBCASE( (nmt::slice<start,end>), expect::x, args::xvf );
        NMTOOLS_TEST_SUBCASE( (nmt::slice<start,end>), expect::x, args::xff );
    }
    {
        using namespace slice::case2;
        using args::start;
        using args::end;
        NMTOOLS_TEST_SUBCASE( (nmt::slice<start,end>), expect::x, args::xad );
        NMTOOLS_TEST_SUBCASE( (nmt::slice<start,end>), expect::x, args::xvd );
        NMTOOLS_TEST_SUBCASE( (nmt::slice<start,end>), expect::x, args::xfd );
        NMTOOLS_TEST_SUBCASE( (nmt::slice<start,end>), expect::x, args::xaf );
        NMTOOLS_TEST_SUBCASE( (nmt::slice<start,end>), expect::x, args::xvf );
        NMTOOLS_TEST_SUBCASE( (nmt::slice<start,end>), expect::x, args::xff );
    }
}