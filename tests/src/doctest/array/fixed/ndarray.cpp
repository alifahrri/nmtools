#include "nmtools/array/fixed.hpp"
#include "testing/doctest.hpp"
#include <array>

using nmtools::utils::isclose;
using nmtools::utils::isequal;
using nmtools::shape;
using nmtools::array::fixed_ndarray;

static_assert( nmtools::meta::is_ndarray_v<fixed_ndarray<double,1>>);
static_assert(!nmtools::meta::is_dynamic_ndarray_v<fixed_ndarray<double,1>>);
static_assert( nmtools::meta::is_fixed_size_ndarray_v<fixed_ndarray<double,1>>);

static_assert( nmtools::meta::is_ndarray_v<fixed_ndarray<double,2,3>>);
static_assert(!nmtools::meta::is_dynamic_ndarray_v<fixed_ndarray<double,2,3>>);
static_assert( nmtools::meta::is_fixed_size_ndarray_v<fixed_ndarray<double,2,3>>);

static_assert( nmtools::meta::is_ndarray_v<fixed_ndarray<double,1,3,2>>);
static_assert(!nmtools::meta::is_dynamic_ndarray_v<fixed_ndarray<double,1,3,2>>);
static_assert( nmtools::meta::is_fixed_size_ndarray_v<fixed_ndarray<double,1,3,2>>);

TEST_CASE("fixed_ndarray[2,3,2]")
{
    // @note that the first angle bracket are for aggregate initialization
    auto ndarray = fixed_ndarray{{
        {
            {0,1},
            {2,3},
            {4,5},
        },
        {
            {6,7},
            {8,9},
            {10,11},
        },
    }};
    CHECK(ndarray.dim()==3);
    NMTOOLS_ASSERT_EQUAL( ndarray.shape(), (std::array{2,3,2}) );
    NMTOOLS_ASSERT_EQUAL( ndarray.strides(), (std::array{6,2,1}) );
    {
        ndarray = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            },
        };
        double expected[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            },
        };
        NMTOOLS_ASSERT_CLOSE( ndarray, expected );
    }
    // @note should fail
    {
        // ndarray = {
        //     {
        //         {{0},{1}},
        //         {{2},{3}},
        //         {{4},{5}},
        //     },
        //     {
        //         {{6},{7}},
        //         {{8},{9}},
        //         {{10},{11}},
        //     },
        // };
        // no matching calls
        // ndarray = 1;
        // static assertion failed: unsupported dim for fixed_ndarray assignment
        // ndarray = std::array{1,2,3,4};
    }
}

TEST_CASE("fixed_ndarray[2,3,1]")
{
    constexpr auto ndarray = fixed_ndarray{
        {
            {{1.},{2.},{3.}},
            {{4.},{5.},{6.}}
        }
    };
    CHECK(ndarray.dim()==3);
    NMTOOLS_ASSERT_EQUAL( ndarray.shape(), (std::array{2,3,1}) );
    NMTOOLS_ASSERT_EQUAL( ndarray.strides(), (std::array{3,1,1}) );
    constexpr auto expected_shape = std::array{2ul,3ul,1ul};
    static_assert(isequal(shape(ndarray),expected_shape));
}

TEST_CASE("fixed_ndarray[2,3]")
{
    auto ndarray = fixed_ndarray{
        {
            {1.,2.,3.},
            {4.,5.,6.}
        }
    };
    CHECK(ndarray.dim()==2);
    NMTOOLS_ASSERT_EQUAL( ndarray.shape(),   (std::array{2,3}) );
    NMTOOLS_ASSERT_EQUAL( ndarray.strides(), (std::array{3,1}) );
    {
        ndarray = {
            {1,2,3},
            {4,5,6},
        };
        double expected[2][3] = {
            {1,2,3},
            {4,5,6},
        };
        NMTOOLS_ASSERT_CLOSE( ndarray, expected );
    }
}

TEST_CASE("fixed_ndarray[3]")
{
    auto ndarray = fixed_ndarray{{1.,2.,3.}};
    CHECK(ndarray.dim()==1);
    NMTOOLS_ASSERT_EQUAL( ndarray.shape(),   std::array{3} );
    NMTOOLS_ASSERT_EQUAL( ndarray.strides(), std::array{1} );
    {
        ndarray = {1,2,3};
        double expected[3] = {1,2,3};
        NMTOOLS_ASSERT_CLOSE( ndarray, expected );
    }
}