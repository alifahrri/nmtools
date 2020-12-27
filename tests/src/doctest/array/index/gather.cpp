#include "nmtools/array/index.hpp"
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

TEST_CASE("gather" * doctest::test_suite("index"))
{
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{0,1,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{1,0,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{1,2,0};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{0,1,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{1,0,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{1,2,0};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{0,1,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{0_ct,1_ct,2_ct};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1,0,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1_ct,0_ct,2_ct};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1,2,0};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1_ct,2_ct,0_ct};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{0,1,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{1,0,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{1,2,0};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{0,1,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{1,0,2};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{1,2,0};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{2,1,0};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{3,2,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{2,0,1};
        auto order    = vector{2,0,1};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{1,2,0};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{2,0,1};
        auto gatherd = nm::index::gather(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
}