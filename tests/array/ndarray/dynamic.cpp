#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/testing/doctest.hpp"
#include <array>

using nmtools::utils::isclose;
using nmtools::utils::isequal;

using nmtools_list;
using nmtools::shape;
using nmtools::dim;
using nmtools::array::dynamic_ndarray;

static_assert( nmtools::meta::is_ndarray_v<dynamic_ndarray<double>>);
static_assert( nmtools::meta::is_dynamic_ndarray_v<dynamic_ndarray<double>>);
static_assert(!nmtools::meta::is_fixed_size_ndarray_v<dynamic_ndarray<double>>);

TEST_CASE("dynamic_ndarray[2,3,2]")
{
    auto shape_ = vector{2ul,3ul,2ul};
    auto ndarray = dynamic_ndarray<double>();
    ndarray.resize(shape_);
    CHECK(ndarray.dim()==3);
    NMTOOLS_ASSERT_EQUAL( ndarray.shape(),(nmtools_array{2,3,2}) );
    NMTOOLS_ASSERT_EQUAL( ndarray.strides(),(nmtools_array{6,2,1}) );
    CHECK( dim(ndarray)==3 );
    NMTOOLS_ASSERT_EQUAL( shape(ndarray), (vector{2ul,3ul,2ul}) );
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
        CHECK( isclose(ndarray,expected) );
    }
}

TEST_CASE("dynamic_ndarray[2,3,1]")
{
    auto ndarray = dynamic_ndarray<double>();
    ndarray.resize({2ul,3ul,1ul});
    CHECK( ndarray.dim()==3 );
    NMTOOLS_ASSERT_EQUAL( ndarray.shape(),   (vector{2,3,1}) );
    NMTOOLS_ASSERT_EQUAL( ndarray.strides(), (vector{3,1,1}) );
    NMTOOLS_ASSERT_EQUAL( shape(ndarray),    (vector{2ul,3ul,1ul}) );
}

TEST_CASE("dynamic_ndarray[2]")
{
    auto ndarray = dynamic_ndarray<double>();
    ndarray.resize({2ul,3ul});
    CHECK( ndarray.dim()==2 );
    NMTOOLS_ASSERT_EQUAL( ndarray.shape(),   (vector{2,3}) );
    NMTOOLS_ASSERT_EQUAL( ndarray.strides(), (vector{3,1}) );
    NMTOOLS_ASSERT_EQUAL( shape(ndarray),    (vector{2ul,3ul}) );
}

TEST_CASE("dynamic_ndarray[5]")
{
    auto ndarray = dynamic_ndarray({1.,2.,3.,4.,5.});
    CHECK(ndarray.dim()==1);
    NMTOOLS_ASSERT_EQUAL( ndarray.shape(), nmtools_array{5} );
    NMTOOLS_ASSERT_CLOSE( ndarray, (vector{1,2,3,4,5}) );
    // utl vector tripped on this
    // TODO: fix
    #ifndef NMTOOLS_DISABLE_STL
    NMTOOLS_ASSERT_EQUAL( shape(ndarray), vector<size_t>{5ul});
    #else
    {
        auto expect = vector<size_t>(1);
        expect[0] = 5;
        NMTOOLS_ASSERT_EQUAL( shape(ndarray), expect);
    }
    #endif
}

TEST_CASE("dynamic_ndarray[3,3]")
{
    auto ndarray = dynamic_ndarray({{1.,2.,3.},{4.,5.,6.},{7.,8.,9.}});
    CHECK(ndarray.dim()==2);
    NMTOOLS_ASSERT_EQUAL( ndarray.shape(), (vector{3,3}) );
    {
        double expected[3][3] = {{1.,2.,3.},{4.,5.,6.},{7.,8.,9.}};
        NMTOOLS_ASSERT_CLOSE( ndarray, expected );
    }
    NMTOOLS_ASSERT_CLOSE( shape(ndarray), (vector{3ul,3ul}) );
}

TEST_CASE("dynamic_ndarray[1,3,1]")
{
    // error: ambiuous call 
    // candidate: dynamic_ndarray(T (&&a)[Shape1][Shape2][Shape3]) { init(a); }
    // candidate: dynamic_ndarray(T (&&a)[Rows][Cols]) { init(a); }
    // note: adding extra brace make non-ambiguous, but causes gcc error dynamic_ndarray(T (&&a)[Rows][Cols]) { init(a); } while clang only gives warning
    // auto ndarray = dynamic_ndarray<double>({{{1.},{2.},{3.}}});
    double a[1][3][1] = {{{1.},{2.},{3.}}};
    auto ndarray = dynamic_ndarray(std::move(a));
    // auto ndarray = dynamic_ndarray<double>(a);
    CHECK(ndarray.dim()==3);
    NMTOOLS_ASSERT_EQUAL( ndarray.shape(), (vector{1,3,1}) );
    NMTOOLS_ASSERT_EQUAL( shape(ndarray),  (vector{1,3,1}) );
    {
        double expected[1][3][1] = {{{1},{2},{3}}};
        NMTOOLS_ASSERT_CLOSE( ndarray, expected );
    }
}