#include "nmtools/index/array.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace ix = nmtools::index;
using namespace nmtools::literals;

TEST_CASE("array(case1)" * doctest::test_suite("index"))
{
    {
        auto buffer = nmtools_array{2,3,2};
        auto a = ix::array(buffer);
        NMTOOLS_ASSERT_EQUAL(a,buffer);
    }
    {
        auto buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto a = ix::array(buffer);
        NMTOOLS_ASSERT_EQUAL(a,buffer);
    }
}

TEST_CASE("array.add(case1)" * doctest::test_suite("index"))
{
    {
        auto a_buffer = nmtools_array{2,3,2};
        auto a = ix::array(a_buffer);
        int b[3] = {2,3,2};
        auto c = a + b;
        auto expected = nmtools_array{4,6,4};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
    {
        auto a_buffer = nmtools_array{2,3,2};
        auto a = ix::array(a_buffer);
        auto b_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto b = ix::array(b_buffer);
        auto c = a + b;
        auto expected = nmtools_array{4,6,4};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
    {
        auto a_buffer = nmtools_list<int>{2,3,2};
        auto a = ix::array(a_buffer);
        auto b_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto b = ix::array(b_buffer);
        auto c = a + b;
        auto expected = nmtools_array{4,6,4};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
    {
        auto a_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto a = ix::array(a_buffer);
        auto b_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto b = ix::array(b_buffer);
        auto c = a + b;
        auto expected = nmtools_array{4,6,4};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
}

TEST_CASE("array.multiply(case1)" * doctest::test_suite("index"))
{
    {
        auto a_buffer = nmtools_array{2,3,2};
        auto a = ix::array(a_buffer);
        int b[3] = {2,3,2};
        auto c = a * b;
        auto expected = nmtools_array{4,9,4};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
    {
        auto a_buffer = nmtools_array{2,3,2};
        auto a = ix::array(a_buffer);
        auto b_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto b = ix::array(b_buffer);
        auto c = a * b;
        auto expected = nmtools_array{4,9,4};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
    {
        auto a_buffer = nmtools_list<int>{2,3,2};
        auto a = ix::array(a_buffer);
        auto b_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto b = ix::array(b_buffer);
        auto c = a * b;
        auto expected = nmtools_array{4,9,4};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
    {
        auto a_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto a = ix::array(a_buffer);
        auto b_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto b = ix::array(b_buffer);
        auto c = a * b;
        auto expected = nmtools_array{4,9,4};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
}

TEST_CASE("array.subtract(case1)" * doctest::test_suite("index"))
{
    {
        auto a_buffer = nmtools_array{2,3,2};
        auto a = ix::array(a_buffer);
        int b[3] = {2,3,2};
        auto c = a - b;
        auto expected = nmtools_array{0,0,0};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
    {
        auto a_buffer = nmtools_array{2,3,2};
        auto a = ix::array(a_buffer);
        auto b_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto b = ix::array(b_buffer);
        auto c = a - b;
        auto expected = nmtools_array{0,0,0};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
    {
        auto a_buffer = nmtools_list<int>{2,3,2};
        auto a = ix::array(a_buffer);
        auto b_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto b = ix::array(b_buffer);
        auto c = a - b;
        auto expected = nmtools_array{0,0,0};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
    {
        auto a_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto a = ix::array(a_buffer);
        auto b_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto b = ix::array(b_buffer);
        auto c = a - b;
        auto expected = nmtools_array{0,0,0};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
}

TEST_CASE("array.divide(case1)" * doctest::test_suite("index"))
{
    {
        auto a_buffer = nmtools_array{2,3,2};
        auto a = ix::array(a_buffer);
        int b[3] = {2,3,2};
        auto c = a / b;
        auto expected = nmtools_array{1,1,1};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
    {
        auto a_buffer = nmtools_array{2,3,2};
        auto a = ix::array(a_buffer);
        auto b_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto b = ix::array(b_buffer);
        auto c = a / b;
        auto expected = nmtools_array{1,1,1};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
    {
        auto a_buffer = nmtools_list<int>{2,3,2};
        auto a = ix::array(a_buffer);
        auto b_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto b = ix::array(b_buffer);
        auto c = a / b;
        auto expected = nmtools_array{1,1,1};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
    {
        auto a_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto a = ix::array(a_buffer);
        auto b_buffer = nmtools_tuple{2_ct,3_ct,2_ct};
        auto b = ix::array(b_buffer);
        auto c = a / b;
        auto expected = nmtools_array{1,1,1};
        NMTOOLS_ASSERT_EQUAL(c,expected);
    }
}

TEST_CASE("array.zeros(case1)" * doctest::test_suite("index"))
{
    {
        auto a = ix::zeros(3_ct);
        auto expected = nmtools_array{0,0,0};
        NMTOOLS_ASSERT_EQUAL( a, expected );
    }
    {
        auto a = ix::zeros(3);
        auto expected = nmtools_array{0,0,0};
        NMTOOLS_ASSERT_EQUAL( a, expected );
    }
    {
        auto a = ix::zeros(4_ct);
        auto expected = nmtools_array{0,0,0,0};
        NMTOOLS_ASSERT_EQUAL( a, expected );
    }
    {
        auto a = ix::zeros(4);
        auto expected = nmtools_array{0,0,0,0};
        NMTOOLS_ASSERT_EQUAL( a, expected );
    }
}

TEST_CASE("array.ones(case1)" * doctest::test_suite("index"))
{
    {
        auto a = ix::ones(3_ct);
        auto expected = nmtools_array{1,1,1};
        NMTOOLS_ASSERT_EQUAL( a, expected );
    }
    {
        auto a = ix::ones(3);
        auto expected = nmtools_array{1,1,1};
        NMTOOLS_ASSERT_EQUAL( a, expected );
    }
    {
        auto a = ix::ones(4_ct);
        auto expected = nmtools_array{1,1,1,1};
        NMTOOLS_ASSERT_EQUAL( a, expected );
    }
    {
        auto a = ix::ones(4);
        auto expected = nmtools_array{1,1,1,1};
        NMTOOLS_ASSERT_EQUAL( a, expected );
    }
}

TEST_CASE("array.full(case1)" * doctest::test_suite("index"))
{
    {
        auto a = ix::full(3_ct,4);
        auto expected = nmtools_array{4,4,4};
        NMTOOLS_ASSERT_EQUAL( a, expected );
    }
    {
        auto a = ix::full(3,4);
        auto expected = nmtools_array{4,4,4};
        NMTOOLS_ASSERT_EQUAL( a, expected );
    }
    {
        auto a = ix::full(4_ct,3_ct);
        auto expected = nmtools_array{3,3,3,3};
        NMTOOLS_ASSERT_EQUAL( a, expected );
    }
    {
        auto a = ix::full(4,3);
        auto expected = nmtools_array{3,3,3,3};
        NMTOOLS_ASSERT_EQUAL( a, expected );
    }
}

TEST_CASE("array.append(case1)" * doctest::test_suite("index"))
{
    {
        auto a = ix::ones(2_ct);
        auto result = a.append(2_ct);
        auto expected = nmtools_array{1,1,2};
        NMTOOLS_ASSERT_EQUAL( result, expected );
    }
}