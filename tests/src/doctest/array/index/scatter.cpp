#include "nmtools/array/index/scatter.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/constants.hpp"
#include "testing/doctest.hpp"
#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
using namespace nm::literals;
using nmtools::utils::isequal;
using std::tuple;
using std::vector;
using std::array;

TEST_CASE("scatter" * doctest::test_suite("index"))
{
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{0,1,2};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{1,0,2};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{1,2,0};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{0,1,2};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{1,0,2};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{1,2,0};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{0,1,2};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1,0,2};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1,2,0};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{0,1,2};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{1,0,2};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{1,2,0};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{0,1,2};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{1,0,2};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{1,2,0};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{1,2,0};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = vector{2,0,1};
        auto order    = vector{2,0,1};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{0,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{2,0,1};
        auto scattered = nm::index::scatter(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
}