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

NMTOOLS_TESTING_DECLARE_CASE(gather)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int vec[3] = {1,2,3};
        int indices[3]   = {0,1,2};
        auto vec_v = cast<vector<int>>(vec);
        auto indices_v   = cast<vector<int>>(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[3] = {1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int vec[3] = {1,2,3};
        int indices[3]   = {1,0,2};
        auto vec_v = cast<vector<int>>(vec);
        auto indices_v   = cast<vector<int>>(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[3] = {2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int vec[3] = {1,2,3};
        int indices[3]   = {1,2,0};
        auto vec_v = cast<vector<int>>(vec);
        auto indices_v   = cast<vector<int>>(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[3] = {2,3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int vec[3] = {1,2,3};
        int indices[3]   = {2,0,1};
        auto vec_v = cast<vector<int>>(vec);
        auto indices_v   = cast<vector<int>>(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[3] = {3,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int vec[3] = {1,2,3};
        int indices[3]   = {2,1,0};
        auto vec_v = cast<vector<int>>(vec);
        auto indices_v   = cast<vector<int>>(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int result[3] = {3,2,1};
    }
    
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int vec[5] = {1,2,3,4,5};
        int indices[3]   = {2,1,0};
        auto vec_v = cast<vector<int>>(vec);
        auto indices_v   = cast<vector<int>>(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int result[3] = {3,2,1};
    }
}

#define GATHER_SUBCASE(case_name, vec, indices) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(gather, case_name); \
    auto result = nm::index::gather(args::vec, args::indices); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
} \

TEST_CASE("gather(vector)" * doctest::test_suite("index::gather"))
{
    GATHER_SUBCASE(case1, vec_v, indices_v);
    GATHER_SUBCASE(case2, vec_v, indices_v);
    GATHER_SUBCASE(case3, vec_v, indices_v);
    GATHER_SUBCASE(case4, vec_v, indices_v);
    GATHER_SUBCASE(case5, vec_v, indices_v);
    GATHER_SUBCASE(case6, vec_v, indices_v);
}

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