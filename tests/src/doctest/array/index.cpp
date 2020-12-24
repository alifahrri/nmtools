/**
 * @file index.cpp
 * @author your name (you@domain.com)
 * @brief test file for indices_pack
 * @version 0.1
 * @date 2020-11-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "nmtools/array/detail.hpp"
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

TEST_CASE("indices_pack({3,2})" * doctest::test_suite("index"))
{
    auto indices = nm::indices_pack(tuple{3,2});
    REQUIRE( indices.size() == 6 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,tuple{0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,tuple{0,1}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,tuple{1,0}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,tuple{1,1}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,tuple{2,0}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,tuple{2,1}) ));
    }
}

TEST_CASE("indices_pack(vector{3,2})" * doctest::test_suite("index"))
{
    auto indices = nm::indices_pack(vector{3,2});
    REQUIRE( indices.size() == 6 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,vector{0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,vector{0,1}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,vector{1,0}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,vector{1,1}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,vector{2,0}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,vector{2,1}) ));
    }
}

TEST_CASE("indices_pack({3,2,3})" * doctest::test_suite("index"))
{
    auto indices = nm::indices_pack(tuple{3,2,3});
    REQUIRE( indices.size() == 18 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,tuple{0,0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,tuple{0,0,1}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,tuple{0,0,2}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,tuple{0,1,0}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,tuple{0,1,1}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,tuple{0,1,2}) ));
    }
    {
        auto i = indices[6];
        CHECK(( isequal(i,tuple{1,0,0}) ));
    }
    {
        auto i = indices[7];
        CHECK(( isequal(i,tuple{1,0,1}) ));
    }
    {
        auto i = indices[8];
        CHECK(( isequal(i,tuple{1,0,2}) ));
    }
    {
        auto i = indices[9];
        CHECK(( isequal(i,tuple{1,1,0}) ));
    }
    {
        auto i = indices[10];
        CHECK(( isequal(i,tuple{1,1,1}) ));
    }
    {
        auto i = indices[11];
        CHECK(( isequal(i,tuple{1,1,2}) ));
    }
    {
        auto i = indices[12];
        CHECK(( isequal(i,tuple{2,0,0}) ));
    }
    {
        auto i = indices[13];
        CHECK(( isequal(i,tuple{2,0,1}) ));
    }
    {
        auto i = indices[14];
        CHECK(( isequal(i,tuple{2,0,2}) ));
    }
    {
        auto i = indices[15];
        CHECK(( isequal(i,tuple{2,1,0}) ));
    }
    {
        auto i = indices[16];
        CHECK(( isequal(i,tuple{2,1,1}) ));
    }
    {
        auto i = indices[17];
        CHECK(( isequal(i,tuple{2,1,2}) ));
    }
}

TEST_CASE("indices_pack({3,2,3})" * doctest::test_suite("index"))
{
    auto indices = nm::indices_pack(vector{3,2,3});
    REQUIRE( indices.size() == 18 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,vector{0,0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,vector{0,0,1}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,vector{0,0,2}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,vector{0,1,0}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,vector{0,1,1}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,vector{0,1,2}) ));
    }
    {
        auto i = indices[6];
        CHECK(( isequal(i,vector{1,0,0}) ));
    }
    {
        auto i = indices[7];
        CHECK(( isequal(i,vector{1,0,1}) ));
    }
    {
        auto i = indices[8];
        CHECK(( isequal(i,vector{1,0,2}) ));
    }
    {
        auto i = indices[9];
        CHECK(( isequal(i,vector{1,1,0}) ));
    }
    {
        auto i = indices[10];
        CHECK(( isequal(i,vector{1,1,1}) ));
    }
    {
        auto i = indices[11];
        CHECK(( isequal(i,vector{1,1,2}) ));
    }
    {
        auto i = indices[12];
        CHECK(( isequal(i,vector{2,0,0}) ));
    }
    {
        auto i = indices[13];
        CHECK(( isequal(i,vector{2,0,1}) ));
    }
    {
        auto i = indices[14];
        CHECK(( isequal(i,vector{2,0,2}) ));
    }
    {
        auto i = indices[15];
        CHECK(( isequal(i,vector{2,1,0}) ));
    }
    {
        auto i = indices[16];
        CHECK(( isequal(i,vector{2,1,1}) ));
    }
    {
        auto i = indices[17];
        CHECK(( isequal(i,vector{2,1,2}) ));
    }
}

TEST_CASE("indices_pack({3,2,3,1})" * doctest::test_suite("index"))
{
    auto indices = nm::indices_pack(tuple{3,2,3,1});
    REQUIRE( indices.size() == 18 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,tuple{0,0,0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,tuple{0,0,1,0}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,tuple{0,0,2,0}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,tuple{0,1,0,0}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,tuple{0,1,1,0}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,tuple{0,1,2,0}) ));
    }
    {
        auto i = indices[6];
        CHECK(( isequal(i,tuple{1,0,0,0}) ));
    }
    {
        auto i = indices[7];
        CHECK(( isequal(i,tuple{1,0,1,0}) ));
    }
    {
        auto i = indices[8];
        CHECK(( isequal(i,tuple{1,0,2,0}) ));
    }
    {
        auto i = indices[9];
        CHECK(( isequal(i,tuple{1,1,0,0}) ));
    }
    {
        auto i = indices[10];
        CHECK(( isequal(i,tuple{1,1,1,0}) ));
    }
    {
        auto i = indices[11];
        CHECK(( isequal(i,tuple{1,1,2,0}) ));
    }
    {
        auto i = indices[12];
        CHECK(( isequal(i,tuple{2,0,0,0}) ));
    }
    {
        auto i = indices[13];
        CHECK(( isequal(i,tuple{2,0,1,0}) ));
    }
    {
        auto i = indices[14];
        CHECK(( isequal(i,tuple{2,0,2,0}) ));
    }
    {
        auto i = indices[15];
        CHECK(( isequal(i,tuple{2,1,0,0}) ));
    }
    {
        auto i = indices[16];
        CHECK(( isequal(i,tuple{2,1,1,0}) ));
    }
    {
        auto i = indices[17];
        CHECK(( isequal(i,tuple{2,1,2,0}) ));
    }
}

TEST_CASE("indices_pack({3,2,3,1})" * doctest::test_suite("index"))
{
    auto indices = nm::indices_pack(tuple{2,3,1,3,1});
    REQUIRE( indices.size() == 18 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,tuple{0,0,0,0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,tuple{0,0,0,1,0}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,tuple{0,0,0,2,0}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,tuple{0,1,0,0,0}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,tuple{0,1,0,1,0}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,tuple{0,1,0,2,0}) ));
    }
    {
        auto i = indices[6];
        CHECK(( isequal(i,tuple{0,2,0,0,0}) ));
    }
    {
        auto i = indices[7];
        CHECK(( isequal(i,tuple{0,2,0,1,0}) ));
    }
    {
        auto i = indices[8];
        CHECK(( isequal(i,tuple{0,2,0,2,0}) ));
    }
    {
        auto i = indices[9];
        CHECK(( isequal(i,tuple{1,0,0,0,0}) ));
    }
    {
        auto i = indices[10];
        CHECK(( isequal(i,tuple{1,0,0,1,0}) ));
    }
    {
        auto i = indices[11];
        CHECK(( isequal(i,tuple{1,0,0,2,0}) ));
    }
    {
        auto i = indices[12];
        CHECK(( isequal(i,tuple{1,1,0,0,0}) ));
    }
    {
        auto i = indices[13];
        CHECK(( isequal(i,tuple{1,1,0,1,0}) ));
    }
    {
        auto i = indices[14];
        CHECK(( isequal(i,tuple{1,1,0,2,0}) ));
    }
    {
        auto i = indices[15];
        CHECK(( isequal(i,tuple{1,2,0,0,0}) ));
    }
    {
        auto i = indices[16];
        CHECK(( isequal(i,tuple{1,2,0,1,0}) ));
    }
    {
        auto i = indices[17];
        CHECK(( isequal(i,tuple{1,2,0,2,0}) ));
    }
}

using std::array;
using std::vector;
using std::tuple;

TEST_CASE("reverse" * doctest::test_suite("index"))
{
    {
        auto indices  = tuple{1};
        auto reversed = nm::detail::reverse(indices);
        CHECK( isequal(reversed,tuple{1}) );
    }
    {
        auto indices  = tuple{0,1};
        auto reversed = nm::detail::reverse(indices);
        CHECK( isequal(reversed,tuple{1,0}) );
    }
    {
        auto indices  = tuple{2,0,1};
        auto reversed = nm::detail::reverse(indices);
        CHECK( isequal(reversed,tuple{1,0,2}) );
    }
    {
        auto indices  = array{1};
        auto reversed = nm::detail::reverse(indices);
        CHECK( isequal(reversed,array{1}) );
    }
    {
        auto indices  = array{0,1};
        auto reversed = nm::detail::reverse(indices);
        CHECK( isequal(reversed,array{1,0}) );
    }
    {
        auto indices  = array{2,0,1};
        auto reversed = nm::detail::reverse(indices);
        CHECK( isequal(reversed,array{1,0,2}) );
    }
    {
        auto indices  = vector{1};
        auto reversed = nm::detail::reverse(indices);
        CHECK( isequal(reversed,array{1}) );
    }
    {
        auto indices  = vector{0,1};
        auto reversed = nm::detail::reverse(indices);
        CHECK( isequal(reversed,array{1,0}) );
    }
    {
        auto indices  = vector{2,0,1};
        auto reversed = nm::detail::reverse(indices);
        CHECK( isequal(reversed,array{1,0,2}) );
    }
}

TEST_CASE("gather" * doctest::test_suite("index"))
{
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{0,1,2};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{1,0,2};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{1,2,0};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{0,1,2};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{1,0,2};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{1,2,0};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{0,1,2};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{0_ct,1_ct,2_ct};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1,0,2};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1_ct,0_ct,2_ct};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1,2,0};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1_ct,2_ct,0_ct};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{0,1,2};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{1,0,2};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{1,2,0};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{0,1,2};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{1,0,2};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{1,2,0};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{2,1,0};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{3,2,1};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{2,0,1};
        auto order    = vector{2,0,1};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{1,2,0};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{2,0,1};
        auto gatherd = nm::detail::gather(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( gatherd, expected );
    }
}

TEST_CASE("scatter" * doctest::test_suite("index"))
{
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{0,1,2};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{1,0,2};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = array{1,2,0};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{0,1,2};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{1,0,2};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = vector{1,2,0};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{0,1,2};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1,0,2};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = tuple{1,2,3};
        auto order    = tuple{1,2,0};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{0,1,2};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{1,0,2};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = array{1,2,3};
        auto order    = array{1,2,0};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{0,1,2};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{1,2,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{1,0,2};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{2,1,3};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{1,2,0};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{1,2,0};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = vector{2,0,1};
        auto order    = vector{2,0,1};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{0,1,2};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
    {
        auto indices  = vector{1,2,3};
        auto order    = vector{2,0,1};
        auto scattered = nm::detail::scatter(indices, order);
        auto expected = array{2,3,1};
        NMTOOLS_ASSERT_EQUAL( scattered, expected );
    }
}