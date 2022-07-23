#include "nmtools/array/index/expand_dims.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;

TEST_CASE("expand_dims(vector)" * doctest::test_suite("index::expand_dims"))
{
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::vector{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::vector{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::vector{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::vector{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::vector{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::vector{0,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::vector{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        // on numpy 1.18
        // >>> np.expand_dims(np.random.rand(1,2,3),(1,2)).shape
        // (1, 1, 1, 2, 3)
        auto expected = std::vector{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::vector{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::vector{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }

    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::array{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::array{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::array{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::array{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::array{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::array{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::array{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::array{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }

    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::tuple{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::tuple{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::tuple{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::tuple{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::tuple{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::tuple{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::tuple{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = std::tuple{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }

    {
        auto shape = std::vector{1,2,3};
        auto axes  = na::hybrid_ndarray({0});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = na::hybrid_ndarray({1});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = na::hybrid_ndarray({2});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = na::hybrid_ndarray({3});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = na::hybrid_ndarray({0,1});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = na::hybrid_ndarray({1,2});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = na::hybrid_ndarray({2,3});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::vector{1,2,3};
        auto axes  = na::hybrid_ndarray({2,3,0});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::vector{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
}

TEST_CASE("expand_dims(array)" * doctest::test_suite("index::expand_dims"))
{
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::array{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::array{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::array{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::array{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::array{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::array{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::array{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::array{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }

    {
        auto shape = std::array{1,2,3};
        auto axes  = std::vector{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::vector{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::vector{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::vector{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::vector{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::vector{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::vector{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::vector{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }

    {
        auto shape = std::array{1,2,3};
        auto axes  = std::tuple{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::tuple{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::tuple{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::tuple{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::tuple{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::tuple{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::tuple{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = std::tuple{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }

    {
        auto shape = std::array{1,2,3};
        auto axes  = na::hybrid_ndarray({0});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = na::hybrid_ndarray({1});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = na::hybrid_ndarray({2});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = na::hybrid_ndarray({3});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = na::hybrid_ndarray({0,1});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = na::hybrid_ndarray({1,2});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = na::hybrid_ndarray({2,3});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::array{1,2,3};
        auto axes  = na::hybrid_ndarray({2,3,0});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
}

TEST_CASE("expand_dims(tuple)" * doctest::test_suite("index::expand_dims"))
{
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::array{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::array{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::array{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::array{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::array{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::array{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::array{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::array{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = std::array{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
}