#include "doctest/doctest.h"
#include "nmtools/array/dynamic.hpp"

using std::vector;
using nmtools::shape;
using nmtools::dim;
using nmtools::array::dynamic_ndarray;

static_assert( nmtools::meta::is_ndarray_v<dynamic_ndarray<double>>);
static_assert( nmtools::meta::is_dynamic_ndarray_v<dynamic_ndarray<double>>);
static_assert(!nmtools::meta::is_fixed_size_ndarray_v<dynamic_ndarray<double>>);

TEST_CASE("dynamic_ndarray[2,3,2]")
{
    auto ndarray = dynamic_ndarray<double>(vector({2ul,3ul,2ul}));
    CHECK(ndarray.dim()==3);
    CHECK(ndarray.shape()[0]==2);
    CHECK(ndarray.shape()[1]==3);
    CHECK(ndarray.shape()[2]==2);
    CHECK(ndarray.strides()[0]==6);
    CHECK(ndarray.strides()[1]==2);
    CHECK(ndarray.strides()[2]==1);
    CHECK(dim(ndarray)==3);
    CHECK(shape(ndarray)==vector({2ul,3ul,2ul}));
}

TEST_CASE("dynamic_ndarray[2,3,1]")
{
    auto ndarray = dynamic_ndarray<double>(vector({2ul,3ul,1ul}));
    CHECK(ndarray.dim()==3);
    CHECK(ndarray.shape()[0]==2);
    CHECK(ndarray.shape()[1]==3);
    CHECK(ndarray.shape()[2]==1);
    CHECK(ndarray.strides()[0]==3);
    CHECK(ndarray.strides()[1]==1);
    CHECK(ndarray.strides()[2]==1);
    CHECK(shape(ndarray)==vector({2ul,3ul,1ul}));
}

TEST_CASE("dynamic_ndarray[2]")
{
    auto ndarray = dynamic_ndarray<double>(vector({2ul,3ul}));
    CHECK(ndarray.dim()==2);
    CHECK(ndarray.shape()[0]==2);
    CHECK(ndarray.shape()[1]==3);
    CHECK(ndarray.strides()[0]==3);
    CHECK(ndarray.strides()[1]==1);
    CHECK(shape(ndarray)==vector({2ul,3ul}));
}

TEST_CASE("dynamic_ndarray[5]")
{
    auto ndarray = dynamic_ndarray({1.,2.,3.,4.,5.});
    CHECK(ndarray.dim()==1);
    CHECK(ndarray.shape()[0]==5);
    CHECK(ndarray.strides()[0]==1);
    CHECK(ndarray(0)==1);
    CHECK(ndarray(1)==2);
    CHECK(ndarray(2)==3);
    CHECK(ndarray(3)==4);
    CHECK(ndarray(4)==5);
    CHECK(shape(ndarray)==vector({5ul}));
}

TEST_CASE("dynamic_ndarray[3,3]")
{
    auto ndarray = dynamic_ndarray({{1.,2.,3.},{4.,5.,6.},{7.,8.,9.}});
    CHECK(ndarray.dim()==2);
    CHECK(ndarray.shape()[0]==3);
    CHECK(ndarray.shape()[1]==3);
    CHECK(ndarray(0,0)==1);
    CHECK(ndarray(0,1)==2);
    CHECK(ndarray(0,2)==3);
    CHECK(ndarray(1,0)==4);
    CHECK(ndarray(1,1)==5);
    CHECK(ndarray(1,2)==6);
    CHECK(ndarray(2,0)==7);
    CHECK(ndarray(2,1)==8);
    CHECK(ndarray(2,2)==9);
    CHECK(shape(ndarray)==vector({3ul,3ul}));
}

TEST_CASE("dynamic_ndarray[1,3,1]")
{
    auto ndarray = dynamic_ndarray({1.,2.,3.},{1,3,1});
    CHECK(ndarray.dim()==3);
    CHECK(ndarray.shape()[0]==1);
    CHECK(ndarray.shape()[1]==3);
    CHECK(ndarray.shape()[2]==1);
    CHECK(ndarray(0,0,0)==1);
    CHECK(ndarray(0,1,0)==2);
    CHECK(ndarray(0,2,0)==3);
    CHECK(shape(ndarray)==vector({1ul,3ul,1ul}));
}