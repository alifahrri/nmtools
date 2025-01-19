/**
 * @file ref.cpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief test file for ref view
 * @date 2020-10-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

// @note need to includ array impl first to make sure overaload/specialization is visible
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/array/view.hpp"
#include "nmtools/utility/isclose.hpp"
#include "nmtools/utility/isequal.hpp"
#include "nmtools/testing/testing.hpp"

#if __has_include("doctest/doctest.h")
    #include "doctest/doctest.h"
#else
   #include "doctest.h"
#endif

#include <array>
#include <vector>

namespace view = nmtools::view;
using nmtools::utils::isclose;
using nmtools::utils::isequal;
using nmtools::array::fixed_ndarray;
using nmtools::array::dynamic_ndarray;

/**
 * @test test case for const ref view to 1D nmtools_array
 * 
 */
TEST_CASE("ref(nmtools_array)" * doctest::test_suite("view::ref")) // ref with 1D nmtools_array
{
    auto array = nmtools_array{1.,2.,3.};
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==1 );
    CHECK( isequal(array_ref.shape(),nmtools_array{3}) );

    {
        auto expected = nmtools_array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3; 

    {
        nmtools::at(array,0) = 3;
        auto expected = nmtools_array{3.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    {
        // view should have meta::fixed_ndarray_shape if its underlying array have too
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( nmtools::get<0>(shape)==3 ));
    }
}

#ifndef NMTOOLS_DISABLE_STL
/**
 * @test test case for const ref view to 2D nmtools_array
 * 
 */
TEST_CASE("ref(nmtools_array<nmtools_array>)" * doctest::test_suite("view::ref")) // ref with 2D nmtools_array
{
    auto array = nmtools_array{
        nmtools_array{1.,2.,3.},
        nmtools_array{3.,4.,5.},
    };
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==2 );
    CHECK( isequal(array_ref.shape(),nmtools_array{2,3}) );

    {
        auto expected = nmtools_array{
            nmtools_array{1.,2.,3.},
            nmtools_array{3.,4.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = nmtools_array{
            nmtools_array{1.,6.,3.},
            nmtools_array{7.,4.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }

    {
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}
#endif // NMTOOLS_DISABLE_STL

/**
 * @test case for const ref view to 1D nmtools_list
 * 
 */
TEST_CASE("ref(nmtools_list)" * doctest::test_suite("view::ref")) // ref with 1D nmtools_list
{
    auto array = nmtools_list{1.,2.,3.};
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==1 );
    CHECK( isequal(array_ref.shape(),nmtools_array{3}) );
    {
        auto expected = nmtools_array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3; 

    {
        nmtools::at(array,0) = 3;
        auto expected = nmtools_array{3.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    {
        STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const ref view to 1D fixed_ndarray 
 * 
 */
TEST_CASE("ref(fixed_ndarray[1])" * doctest::test_suite("view::ref")) // ref with 1D fixed_ndarray
{
    auto array = fixed_ndarray({1.,2.,3.});
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==1 );
    CHECK( isequal(array_ref.shape(),nmtools_array{3}) );

    array = nmtools_array{1.,2.,3.};

    {
        STATIC_CHECK(( nmtools::meta::is_ndarray_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const ref view to 2D fixed_ndarray
 * 
 */
TEST_CASE("ref(fixed_ndarray[2])" * doctest::test_suite("view::ref")) // ref with 2D fixed_ndarray
{
    auto array = fixed_ndarray{{
        {1.,2.},
        {3.,4.},
        {4.,5.},
    }};
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==2 );
    CHECK( isequal(array_ref.shape(),nmtools_array{3,2}) );

    CHECK( array_ref(0,1)==2 );
    CHECK( array_ref(1,0)==3 );

    nmtools::at(array,0,1) = 6;
    nmtools::at(array,1,0) = 7;
    
    CHECK( array_ref(0,1)==6 );
    CHECK( array_ref(1,0)==7 );

    {
        STATIC_CHECK(( nmtools::meta::is_ndarray_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const ref view to 3D fixed_ndarray 
 * 
 */
TEST_CASE("ref(fixed_ndarray[3])" * doctest::test_suite("view::ref")) // ref with 3D fixed_ndarray
{
    auto array = fixed_ndarray{{
        {
            {1.,2.,3.,4.},
            {5.,6.,7.,8.}
        },
        {
            {9., 10.,11.,12.},
            {13.,14.,15.,16.}
        },
        {
            {17.,18.,19.,20.},
            {21.,22.,23.,24.},
        }
    }};
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==3 );
    CHECK( isequal(array_ref.shape(),nmtools_array{3,2,4}) );

    // @todo provide constructor/assignment op from 3D array

    nmtools::at(array,0,1,0) = 6;
    CHECK( array_ref(0,1,0)==6 );

    {
        STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const ref view to 4D fixed_ndarray
 * 
 */
TEST_CASE("ref(fixed_ndarray[4])" * doctest::test_suite("view::ref")) // // ref with 4D fixed_ndarray
{
    auto array = fixed_ndarray<double,3,2,4,1>{};
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==4 );
    CHECK( isequal(array_ref.shape(),nmtools_array{3,2,4,1}) );

    // @todo provide constructor/assignment op from 4D array

    nmtools::at(array,0,1,3,0) = 6;
    CHECK( array_ref(0,1,3,0)==6 );
}

/**
 * @test test case for const ref view to 1D dynamic_ndarray
 * 
 */
TEST_CASE("ref(dynamic_ndarray[1])" * doctest::test_suite("view::ref")) // ref with 1D dynamic_ndarray
{
    auto array = dynamic_ndarray({1.,2.,3.});
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==1 );
    CHECK( isequal(array_ref.shape(),nmtools_array{3}) );
}

/**
 * @test test case for const ref view to 2D dynamic_ndarray
 * 
 */
TEST_CASE("ref(dynamic_ndarray[2])" * doctest::test_suite("view::ref")) // ref with 1D dynamic_ndarray
{
    auto array = dynamic_ndarray({
        {1.,2.,3.},
        {3.,4.,5.}
    });
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==2 );
    CHECK( isequal(array_ref.shape(),nmtools_array{2,3}) );
}

/**
 * @test test case for const ref view to 3D dynamic_ndarray
 * 
 */
TEST_CASE("ref(dynamic_ndarray[3])" * doctest::test_suite("view::ref")) // ref with 3D dynamic_ndarray
{
    // @note initialize 3D ndarray from flat storage with specified shape
    // auto array = dynamic_ndarray({1.,2.,3.},{1,3,1});
    auto array = dynamic_ndarray<double>();
    double a[1][3][1] = {{{1.},{2.},{1.}}};
    array.resize({1,3,1});
    array = std::move(a);
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==3 );
    CHECK( isequal(array_ref.shape(),nmtools_array{1,3,1}) );

    // @todo provide constructor/assignment op from 3D array
}

/**
 * @test test case for const ref view to 4D dynamic_ndarray
 * 
 */
TEST_CASE("ref(dynamic_ndarray[4])" * doctest::test_suite("view::ref")) // ref with 4D dynamic_ndarray
{
    // @note initialize 3D ndarray from flat storage with specified shape
    auto array = dynamic_ndarray<double>();
    double a[1][2][2][1] = {
        {
            {
                {1.},
                {2.}
            },
            {
                {3.},
                {4.}
            }
        }
    };
    array.resize({1,2,2,1});
    array = std::move(a);
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==4 );
    CHECK( isequal(array_ref.shape(),nmtools_array{1,2,2,1}) );

    // @todo provide constructor/assignment op from 3D array

    CHECK( array_ref(0,1,1,0)==4 );
    nmtools::at(array,0,1,1,0) = 6;
    CHECK( array_ref(0,1,1,0)==6 );
}