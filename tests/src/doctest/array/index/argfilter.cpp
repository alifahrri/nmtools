#include "nmtools/array/index/argfilter.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;

TEST_CASE("argfilter(vector)" * doctest::test_suite("index::argfilter"))
{
    {
        auto array = std::vector{1,2,1,3,4};
        auto f = [](auto a){
            return a == 1;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::vector{0,2};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = std::vector{1,2,1,3,4};
        auto f = [](auto a){
            return a > 1;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::vector{1,3,4};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = std::vector{1,2,1,3,4};
        auto f = [](auto a){
            return a == 3;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::vector{3};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = std::vector{1,2,1,3,4};
        auto f = [](auto a){
            return a >= 1;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::vector{0,1,2,3,4};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = std::vector{1,2,1,3,4};
        auto f = [](auto a){
            return a == 0;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::vector<size_t>{};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
}

TEST_CASE("argfilter(array)" * doctest::test_suite("index::argfilter"))
{
    {
        auto array = std::array{1,2,1,3,4};
        auto f = [](auto a){
            return a == 1;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::array{0,2};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = std::array{1,2,1,3,4};
        auto f = [](auto a){
            return a > 1;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::array{1,3,4};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = std::array{1,2,1,3,4};
        auto f = [](auto a){
            return a == 3;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::array{3};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = std::array{1,2,1,3,4};
        auto f = [](auto a){
            return a >= 1;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::array{0,1,2,3,4};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = std::array{1,2,1,3,4};
        auto f = [](auto a){
            return a == 0;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::vector<size_t>{};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
}

TEST_CASE("argfilter(tuple)" * doctest::test_suite("index::argfilter"))
{
    {
        auto array = std::tuple{1,2,1,3,4};
        auto f = [](auto a){
            return a == 1;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::array{0,2};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = std::tuple{1,2,1,3,4};
        auto f = [](auto a){
            return a > 1;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::array{1,3,4};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = std::tuple{1,2,1,3,4};
        auto f = [](auto a){
            return a == 3;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::array{3};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = std::tuple{1,2,1,3,4};
        auto f = [](auto a){
            return a >= 1;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::array{0,1,2,3,4};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = std::tuple{1,2,1,3,4};
        auto f = [](auto a){
            return a == 0;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::vector<size_t>{};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
}

TEST_CASE("argfilter(hybrid_ndarray)" * doctest::test_suite("index::argfilter"))
{
    {
        auto array = na::hybrid_ndarray({1,2,1,3,4});
        auto f = [](auto a){
            return a == 1;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::array{0,2};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = na::hybrid_ndarray({1,2,1,3,4});
        auto f = [](auto a){
            return a > 1;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::array{1,3,4};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = na::hybrid_ndarray({1,2,1,3,4});
        auto f = [](auto a){
            return a == 3;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::array{3};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = na::hybrid_ndarray({1,2,1,3,4});
        auto f = [](auto a){
            return a >= 1;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::array{0,1,2,3,4};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
    {
        auto array = na::hybrid_ndarray({1,2,1,3,4});
        auto f = [](auto a){
            return a == 0;
        };
        auto arg = nm::index::argfilter(f,array);
        auto expected = std::vector<size_t>{};
        NMTOOLS_ASSERT_EQUAL( arg, expected );
    }
}