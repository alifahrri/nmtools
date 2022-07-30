#include "nmtools/array/index/expand_dims.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/testing/doctest.hpp"

// to allow nmtools_array, vector, tuple identified as array/index
#include "nmtools/meta/stl.hpp"
#include "nmtools/array/impl/stl.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;

TEST_CASE("expand_dims(vector)" * doctest::test_suite("index::expand_dims"))
{
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_array{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_array{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_array{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_array{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_list{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_list{0,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_list{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        // on numpy 1.18
        // >>> np.expand_dims(np.random.rand(1,2,3),(1,2)).shape
        // (1, 1, 1, 2, 3)
        auto expected = nmtools_list{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_list{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_list{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }

    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_array{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_array{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_array{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_array{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_array{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_array{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_array{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = nmtools_array{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }

    #if 0
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = std::tuple{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = std::tuple{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = std::tuple{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = std::tuple{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = std::tuple{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = std::tuple{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = std::tuple{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = std::tuple{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    #endif

    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = na::hybrid_ndarray({0});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = na::hybrid_ndarray({1});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = na::hybrid_ndarray({2});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = na::hybrid_ndarray({3});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = na::hybrid_ndarray({0,1});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = na::hybrid_ndarray({1,2});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = na::hybrid_ndarray({2,3});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_list{1,2,3};
        auto axes  = na::hybrid_ndarray({2,3,0});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_list{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
}

TEST_CASE("expand_dims(array)" * doctest::test_suite("index::expand_dims"))
{
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_array{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_array{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_array{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_array{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_array{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_array{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_array{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_array{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }

    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_array{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_array{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_array{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_array{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_list{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_list{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_list{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = nmtools_list{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }

    #if 0
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = std::tuple{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = std::tuple{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = std::tuple{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = std::tuple{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = std::tuple{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = std::tuple{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = std::tuple{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = std::tuple{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    #endif

    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = na::hybrid_ndarray({0});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = na::hybrid_ndarray({1});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = na::hybrid_ndarray({2});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = na::hybrid_ndarray({3});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = na::hybrid_ndarray({0,1});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = na::hybrid_ndarray({1,2});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = na::hybrid_ndarray({2,3});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = nmtools_array{1,2,3};
        auto axes  = na::hybrid_ndarray({2,3,0});
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
}

#if 0
TEST_CASE("expand_dims(tuple)" * doctest::test_suite("index::expand_dims"))
{
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = nmtools_array{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = nmtools_array{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = nmtools_array{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = nmtools_array{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,3,1};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = nmtools_array{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{0,1};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = nmtools_array{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{1,2};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = nmtools_array{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{2,3};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,2,1,1,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = nmtools_array{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
    {
        auto shape = std::tuple{1,2,3};
        auto axes  = std::tuple{2,3,0};
        auto newshape = nm::index::expand_dims(shape,axes);
        auto expected = nmtools_array{1,1,1,1,2,3};
        NMTOOLS_ASSERT_EQUAL( newshape, expected );
    }
}
#endif