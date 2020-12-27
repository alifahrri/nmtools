#include "nmtools/array/view/reshape.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;
using namespace nm::literals;

TEST_CASE("reshape: array(12)->(12x1)" * doctest::test_suite("view::reshape"))
{
    auto array = std::array{1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.};
    double expected[12][1] = {
        {1.}, {2.}, {3.}, {4.}, {5.}, {6.}, {7.}, {8.}, {9.}, {10.}, {11.}, {12.}
    };
    {
        // should crash
        // auto array_ref = view::reshape(array,std::array{3,2});
    }
    {
        auto newshape  = std::array{12,1};
        auto array_ref = view::reshape(array,newshape);
        using view_t = decltype(array_ref);

        STATIC_CHECK( !meta::is_fixed_size_ndarray_v<view_t> );
        STATIC_CHECK( !meta::is_array1d_v<view_t> );
        STATIC_CHECK(  meta::is_array2d_v<view_t> );
        STATIC_CHECK(  meta::is_ndarray_v<view_t> );

        auto shape = nm::shape(array_ref);
        auto dim   = nm::dim(array_ref);
        NMTOOLS_ASSERT_EQUAL( dim, newshape.size() );
        NMTOOLS_ASSERT_EQUAL( shape, (newshape) );
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), newshape.size() );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), (newshape) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto newshape  = std::vector{12,1};
        auto array_ref = view::reshape(array,newshape);
        using view_t = decltype(array_ref);

        STATIC_CHECK( !meta::is_fixed_size_ndarray_v<view_t> );
        STATIC_CHECK( !meta::is_array1d_v<view_t> );
        STATIC_CHECK( !meta::is_array2d_v<view_t> );
        STATIC_CHECK(  meta::is_ndarray_v<view_t> );

        auto shape = nm::shape(array_ref);
        auto dim   = nm::dim(array_ref);
        NMTOOLS_ASSERT_EQUAL( dim, newshape.size() );
        NMTOOLS_ASSERT_EQUAL( shape, newshape );
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), newshape.size() );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), newshape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto newshape  = std::tuple{12,1};
        auto array_ref = view::reshape(array,newshape);
        using view_t = decltype(array_ref);

        STATIC_CHECK( !meta::is_fixed_size_ndarray_v<view_t> );
        STATIC_CHECK( !meta::is_array1d_v<view_t> );
        STATIC_CHECK(  meta::is_array2d_v<view_t> );
        STATIC_CHECK(  meta::is_ndarray_v<view_t> );

        auto shape = nm::shape(array_ref);
        auto dim   = nm::dim(array_ref);
        NMTOOLS_ASSERT_EQUAL( dim, 2 );
        NMTOOLS_ASSERT_EQUAL( shape, newshape );
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), newshape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto newshape  = std::tuple{12_ct,1_ct};
        auto array_ref = view::reshape(array,newshape);
        using view_t = decltype(array_ref);

        STATIC_CHECK(  meta::is_fixed_size_ndarray_v<view_t> );
        STATIC_CHECK( !meta::is_array1d_v<view_t> );
        STATIC_CHECK(  meta::is_array2d_v<view_t> );
        STATIC_CHECK(  meta::is_ndarray_v<view_t> );

        auto shape = nm::shape(array_ref);
        auto dim   = nm::dim(array_ref);
        NMTOOLS_ASSERT_EQUAL( dim, 2 );
        NMTOOLS_ASSERT_EQUAL( shape, newshape );
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), newshape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("reshape: array(12)->(3x4)" * doctest::test_suite("view::reshape"))
{
    auto array = std::array{1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.};
    double expected[3][4] = {
        {1.,  2.,  3.,  4.},
        {5.,  6.,  7.,  8.},
        {9., 10., 11., 12.}
    };
    {
        auto newshape  = std::array{3,4};
        auto array_ref = view::reshape(array,newshape);
        using view_t = decltype(array_ref);

        STATIC_CHECK( !meta::is_fixed_size_ndarray_v<view_t> );
        STATIC_CHECK( !meta::is_array1d_v<view_t> );
        STATIC_CHECK(  meta::is_array2d_v<view_t> );
        STATIC_CHECK(  meta::is_ndarray_v<view_t> );

        auto shape = nm::shape(array_ref);
        auto dim   = nm::dim(array_ref);
        NMTOOLS_ASSERT_EQUAL( dim, newshape.size() );
        NMTOOLS_ASSERT_EQUAL( shape, (newshape) );
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), newshape.size() );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), (newshape) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto newshape  = std::vector{3,4};
        auto array_ref = view::reshape(array,newshape);
        using view_t = decltype(array_ref);

        STATIC_CHECK( !meta::is_fixed_size_ndarray_v<view_t> );
        STATIC_CHECK( !meta::is_array1d_v<view_t> );
        STATIC_CHECK( !meta::is_array2d_v<view_t> );
        STATIC_CHECK(  meta::is_ndarray_v<view_t> );

        auto shape = nm::shape(array_ref);
        auto dim   = nm::dim(array_ref);
        NMTOOLS_ASSERT_EQUAL( dim, newshape.size() );
        NMTOOLS_ASSERT_EQUAL( shape, newshape );
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), newshape.size() );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), newshape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto newshape  = std::tuple{3,4};
        auto array_ref = view::reshape(array,newshape);
        using view_t = decltype(array_ref);

        STATIC_CHECK( !meta::is_fixed_size_ndarray_v<view_t> );
        STATIC_CHECK( !meta::is_array1d_v<view_t> );
        STATIC_CHECK(  meta::is_array2d_v<view_t> );
        STATIC_CHECK(  meta::is_ndarray_v<view_t> );

        auto shape = nm::shape(array_ref);
        auto dim   = nm::dim(array_ref);
        NMTOOLS_ASSERT_EQUAL( dim, 2 );
        NMTOOLS_ASSERT_EQUAL( shape, newshape );
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), newshape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto newshape  = std::tuple{3_ct,4_ct};
        auto array_ref = view::reshape(array,newshape);
        using view_t = decltype(array_ref);

        STATIC_CHECK(  meta::is_fixed_size_ndarray_v<view_t> );
        STATIC_CHECK( !meta::is_array1d_v<view_t> );
        STATIC_CHECK(  meta::is_array2d_v<view_t> );
        STATIC_CHECK(  meta::is_ndarray_v<view_t> );

        auto shape = nm::shape(array_ref);
        auto dim   = nm::dim(array_ref);
        NMTOOLS_ASSERT_EQUAL( dim, 2 );
        NMTOOLS_ASSERT_EQUAL( shape, newshape );
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), newshape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("reshape: double(12)->(12x1)" * doctest::test_suite("view::reshape"))
{
    double array[12] = {1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.};
    double expected[12][1] = {
        {1.}, {2.}, {3.}, {4.}, {5.}, {6.}, {7.}, {8.}, {9.}, {10.}, {11.}, {12.}
    };
    auto newshape = std::array{12,1};
    auto array_ref = view::reshape(array,newshape);
    using view_t = decltype(array_ref);

    STATIC_CHECK( !meta::is_fixed_size_ndarray_v<view_t> );
    STATIC_CHECK( !meta::is_array1d_v<view_t> );
    STATIC_CHECK(  meta::is_array2d_v<view_t> );
    STATIC_CHECK(  meta::is_ndarray_v<view_t> );

    auto shape = nm::shape(array_ref);
    auto dim   = nm::dim(array_ref);
    NMTOOLS_ASSERT_EQUAL( dim, newshape.size() );
    NMTOOLS_ASSERT_EQUAL( shape, (newshape) );
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), newshape.size() );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), (newshape) );

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("reshape: double(12)->(3x4)" * doctest::test_suite("view::reshape"))
{
    double array[12] = {1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.};
    double expected[3][4] = {
        {1.,  2.,  3.,  4.},
        {5.,  6.,  7.,  8.},
        {9., 10., 11., 12.}
    };
    auto newshape = std::array{3,4};
    auto array_ref = view::reshape(array,newshape);
    using view_t = decltype(array_ref);

    STATIC_CHECK( !meta::is_fixed_size_ndarray_v<view_t> );
    STATIC_CHECK( !meta::is_array1d_v<view_t> );
    STATIC_CHECK(  meta::is_array2d_v<view_t> );
    STATIC_CHECK(  meta::is_ndarray_v<view_t> );

    auto shape = nm::shape(array_ref);
    auto dim   = nm::dim(array_ref);
    NMTOOLS_ASSERT_EQUAL( dim, newshape.size() );
    NMTOOLS_ASSERT_EQUAL( shape, (newshape) );
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), newshape.size() );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), (newshape) );

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("reshape: double(12)->(1x2x3x2)" * doctest::test_suite("view::reshape"))
{
    double array[12] = {1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.};
    double expected[1][2][3][2] = {
        {
            {
                {1., 2.},
                {3., 4.},
                {5., 6.}
            },
            {
                {7.,  8.},
                {9., 10.},
                {11.,12.}
            }
        }
    };
    auto newshape = std::array{1,2,3,2};
    auto array_ref = view::reshape(array,newshape);
    using view_t = decltype(array_ref);

    STATIC_CHECK( !meta::is_fixed_size_ndarray_v<view_t> );
    STATIC_CHECK( !meta::is_array1d_v<view_t> );
    STATIC_CHECK( !meta::is_array2d_v<view_t> );
    STATIC_CHECK(  meta::is_ndarray_v<view_t> );

    auto shape = nm::shape(array_ref);
    auto dim   = nm::dim(array_ref);
    NMTOOLS_ASSERT_EQUAL( dim, newshape.size() );
    NMTOOLS_ASSERT_EQUAL( shape, (newshape) );
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), newshape.size() );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), (newshape) );

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("reshape: vector(12)->(12x1)" * doctest::test_suite("view::reshape"))
{
    auto array = std::vector{1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.};
    double expected[12][1] = {
        {1.}, {2.}, {3.}, {4.}, {5.}, {6.}, {7.}, {8.}, {9.}, {10.}, {11.}, {12.}
    };
    auto newshape = std::array{12,1};
    auto array_ref = view::reshape(array,newshape);
    using view_t = decltype(array_ref);

    STATIC_CHECK( !meta::is_fixed_size_ndarray_v<view_t> );
    STATIC_CHECK( !meta::is_array1d_v<view_t> );
    STATIC_CHECK(  meta::is_array2d_v<view_t> );
    STATIC_CHECK(  meta::is_ndarray_v<view_t> );

    auto shape = nm::shape(array_ref);
    auto dim   = nm::dim(array_ref);
    NMTOOLS_ASSERT_EQUAL( dim, newshape.size() );
    NMTOOLS_ASSERT_EQUAL( shape, (newshape) );
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), newshape.size() );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), (newshape) );

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("reshape: vector(12)->(3x4)" * doctest::test_suite("view::reshape"))
{
    auto array = std::vector{1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.};
    double expected[3][4] = {
        {1.,  2.,  3.,  4.},
        {5.,  6.,  7.,  8.},
        {9., 10., 11., 12.}
    };
    auto newshape = std::array{3,4};
    auto array_ref = view::reshape(array,newshape);
    using view_t = decltype(array_ref);

    STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    STATIC_CHECK_TRAIT_FALSE( meta::is_array1d, view_t );
    STATIC_CHECK_TRAIT_TRUE(  meta::is_array2d, view_t );
    STATIC_CHECK_TRAIT_TRUE(  meta::is_ndarray, view_t );

    auto shape = nm::shape(array_ref);
    auto dim   = nm::dim(array_ref);
    NMTOOLS_ASSERT_EQUAL( dim, newshape.size() );
    NMTOOLS_ASSERT_EQUAL( shape, (newshape) );
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), newshape.size() );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), (newshape) );

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("reshape: fixed_ndarray(12)->(3x4)" * doctest::test_suite("view::reshape"))
{
    auto array = na::fixed_ndarray{{1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.}};
    double expected[3][4] = {
        {1.,  2.,  3.,  4.},
        {5.,  6.,  7.,  8.},
        {9., 10., 11., 12.}
    };
    auto newshape = std::array{3,4};
    auto array_ref = view::reshape(array,newshape);
    using view_t = decltype(array_ref);

    STATIC_CHECK( !meta::is_fixed_size_ndarray_v<view_t> );
    STATIC_CHECK( !meta::is_array1d_v<view_t> );
    STATIC_CHECK(  meta::is_array2d_v<view_t> );
    STATIC_CHECK(  meta::is_ndarray_v<view_t> );

    auto shape = nm::shape(array_ref);
    auto dim   = nm::dim(array_ref);
    NMTOOLS_ASSERT_EQUAL( dim, newshape.size() );
    NMTOOLS_ASSERT_EQUAL( shape, (newshape) );
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), newshape.size() );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), (newshape) );

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("reshape: dynamic_ndarray(12)->(3x4)" * doctest::test_suite("view::reshape"))
{
    auto array = na::dynamic_ndarray({1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.});
    double expected[3][4] = {
        {1.,  2.,  3.,  4.},
        {5.,  6.,  7.,  8.},
        {9., 10., 11., 12.}
    };
    auto newshape = std::array{3,4};
    auto array_ref = view::reshape(array,newshape);
    using view_t = decltype(array_ref);

    STATIC_CHECK( !meta::is_fixed_size_ndarray_v<view_t> );
    STATIC_CHECK( !meta::is_array1d_v<view_t> );
    STATIC_CHECK(  meta::is_array2d_v<view_t> );
    STATIC_CHECK(  meta::is_ndarray_v<view_t> );

    auto shape = nm::shape(array_ref);
    auto dim   = nm::dim(array_ref);
    NMTOOLS_ASSERT_EQUAL( dim, newshape.size() );
    NMTOOLS_ASSERT_EQUAL( shape, (newshape) );
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), newshape.size() );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), (newshape) );

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}