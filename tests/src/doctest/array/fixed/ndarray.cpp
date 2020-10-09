#include "doctest/doctest.h"
#include "nmtools/array/fixed.hpp"
#include "nmtools/utility/helper.hpp"
#include <array>

using nmtools::helper::isclose;
using nmtools::array_shape;
using nmtools::array::fixed_ndarray;

static_assert( nmtools::traits::is_ndarray_v<fixed_ndarray<double,1>>);
static_assert(!nmtools::traits::is_dynamic_ndarray_v<fixed_ndarray<double,1>>);
static_assert( nmtools::traits::is_fixed_ndarray_v<fixed_ndarray<double,1>>);

static_assert( nmtools::traits::is_ndarray_v<fixed_ndarray<double,2,3>>);
static_assert(!nmtools::traits::is_dynamic_ndarray_v<fixed_ndarray<double,2,3>>);
static_assert( nmtools::traits::is_fixed_ndarray_v<fixed_ndarray<double,2,3>>);

static_assert( nmtools::traits::is_ndarray_v<fixed_ndarray<double,1,3,2>>);
static_assert(!nmtools::traits::is_dynamic_ndarray_v<fixed_ndarray<double,1,3,2>>);
static_assert( nmtools::traits::is_fixed_ndarray_v<fixed_ndarray<double,1,3,2>>);

TEST_CASE("fixed_ndarray[2,3,2]")
{
    auto ndarray = fixed_ndarray<double,2,3,2>{};
    CHECK(ndarray.dim()==3);
    CHECK(ndarray.shape()[0]==2);
    CHECK(ndarray.shape()[1]==3);
    CHECK(ndarray.shape()[2]==2);
    ndarray(0,1,1) = 1;
    CHECK(ndarray(0,1,1)==1);
    CHECK(ndarray.strides()[0]==6);
    CHECK(ndarray.strides()[1]==2);
    CHECK(ndarray.strides()[2]==1);
    CHECK(array_shape(ndarray)==std::array{2ul,3ul,2ul});
}

TEST_CASE("fixed_ndarray[2,3,1]")
{
    constexpr auto ndarray = fixed_ndarray<double,2,3,1>{};
    CHECK(ndarray.dim()==3);
    CHECK(ndarray.shape()[0]==2);
    CHECK(ndarray.shape()[1]==3);
    CHECK(ndarray.shape()[2]==1);
    CHECK(ndarray.strides()[0]==3);
    CHECK(ndarray.strides()[1]==1);
    constexpr auto expected_shape = std::array{2ul,3ul,1ul};
    static_assert(isclose(array_shape(ndarray),expected_shape));
}

TEST_CASE("fixed_ndarray[2,3]")
{
    auto ndarray = fixed_ndarray<double,2,3>{};
    CHECK(ndarray.dim()==2);
    CHECK(ndarray.shape()[0]==2);
    CHECK(ndarray.shape()[1]==3);
    ndarray(0,1) = 1;
    CHECK(ndarray(0,1)==1);
    CHECK(ndarray.strides()[0]==3);
    CHECK(ndarray.strides()[1]==1);
    CHECK(array_shape(ndarray)==std::array{2ul,3ul});
}

TEST_CASE("fixed_ndarray[3]")
{
    constexpr auto ndarray = fixed_ndarray<double,3>{};
    CHECK(ndarray.dim()==1);
    CHECK(ndarray.shape()[0]==3);
    CHECK(ndarray.strides()[0]==1);
    static_assert(isclose(array_shape(ndarray),std::array{3ul}));
}