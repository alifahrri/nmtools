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
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/view.hpp"
#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/isequal.hpp"
#include "testing/testing.hpp"

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
using nmtools::array::fixed_vector;
using nmtools::array::fixed_matrix;
using nmtools::array::fixed_ndarray;
using nmtools::array::dynamic_vector;
using nmtools::array::dynamic_matrix;
using nmtools::array::dynamic_ndarray;

/**
 * @test test case for const ref view to 1D std::array
 * 
 */
TEST_CASE("ref(std::array)" * doctest::test_suite("view::ref")) // ref with 1D std::array
{
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==1 );
    CHECK( isequal(array_ref.shape(),std::array{3}) );
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // LOG_TYPEINFO( decltype(array_ref) );
    STATIC_CHECK(( nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3; 

    {
        nmtools::at(array,0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    {
        // view should have meta::fixed_ndarray_shape if its underlying array have too
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
        STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    }
}

/**
 * @test test case for const ref view to 1D std::array, created using make_view
 * 
 */
TEST_CASE("make_view<ref_t>(std::array)" * doctest::test_suite("view::ref")) // ref 1D from make_view
{
    using view::ref_t;
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::make_view<ref_t>(array);
    STATIC_CHECK(( nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    CHECK( isequal(array_ref.shape(),std::array{3}) );
    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3; 

    {
        nmtools::at(array,0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    {
        // view::decorator_t should have meta::fixed_ndarray_shape if its underlying view have too
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
        STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_vector_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const ref view to 2D std::array
 * 
 */
TEST_CASE("ref(std::array<std::array>)" * doctest::test_suite("view::ref")) // ref with 2D std::array
{
    auto array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    auto array_ref = view::ref(array);
    STATIC_CHECK(( nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==2 );
    CHECK( isequal(array_ref.shape(),std::array{2,3}) );

    {
        auto expected = std::array{
            std::array{1.,2.,3.},
            std::array{3.,4.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{
            std::array{1.,6.,3.},
            std::array{7.,4.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }

    {
        STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test case for const ref view to 1D std::vector
 * 
 */
TEST_CASE("ref(std::vector)" * doctest::test_suite("view::ref")) // ref with 1D std::vector
{
    auto array = std::vector{1.,2.,3.};
    auto array_ref = view::ref(array);
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    CHECK( isequal(array_ref.shape(),std::array{3}) );
    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3; 

    {
        nmtools::at(array,0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    {
        STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_vector_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const ref view to 2D std::vector
 * 
 */
TEST_CASE("ref(std::vector<std::vector>)" * doctest::test_suite("view::ref")) // ref with 2D std::vector
{
    auto array = std::vector{
        std::vector{1.,2.,3.},
        std::vector{3.,4.,5.},
    };
    auto array_ref = view::ref(array);
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==2 );
    CHECK( isequal(array_ref.shape(),std::array{2,3}) );

    {
        auto expected = std::array{
            std::array{1.,2.,3.},
            std::array{3.,4.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{
            std::array{1.,6.,3.},
            std::array{7.,4.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }

    {
        STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const ref view to fixed_vector
 * 
 */
TEST_CASE("ref(fixed_vector)" * doctest::test_suite("view::ref")) // ref with fixed_vector
{
    auto array = fixed_vector({1.,2.,3.});
    auto array_ref = view::ref(array);
    STATIC_CHECK(( nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    CHECK( isequal(array_ref.shape(),std::array{3}) );

    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3; 

    {
        nmtools::at(array,0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    {
        STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_vector_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const ref view to fixed_matrix
 * 
 */
TEST_CASE("ref(fixed_matrix)" * doctest::test_suite("view::ref")) // ref with fixed_matrix
{
    auto array = fixed_matrix{{
        {1.,2.,3.},
        {3.,4.,5.},
    }};
    auto array_ref = view::ref(array);
    STATIC_CHECK(( nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==2 );
    CHECK( isequal(array_ref.shape(), std::array{2,3}) );

    {
        auto expected = std::array{
            std::array{1.,2.,3.},
            std::array{3.,4.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{
            std::array{1.,6.,3.},
            std::array{7.,4.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }

    {
        STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const ref view to dynamic_vector
 * 
 */
TEST_CASE("ref(dynamic_vector)" * doctest::test_suite("view::ref")) // ref with dynamic_vector
{
    auto array = dynamic_vector{1.,2.,3.};
    auto array_ref = view::ref(array);
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    CHECK( isequal(array_ref.shape(),std::array{3}) );
    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3; 

    {
        nmtools::at(array,0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    {
        STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_vector_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const ref view to dynamic_matrix
 * 
 */
TEST_CASE("ref(dynamic_matrix)" * doctest::test_suite("view::ref")) // ref with dynamic_matrix
{
    auto array = dynamic_matrix{
        {1.,2.,3.},
        {3.,4.,5.},
    };
    auto array_ref = view::ref(array);
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==2 );
    CHECK( isequal(array_ref.shape(), std::array{2,3}) );

    {
        auto expected = std::array{
            std::array{1.,2.,3.},
            std::array{3.,4.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{
            std::array{1.,6.,3.},
            std::array{7.,4.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }

    {
        STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
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
    CHECK( isequal(array_ref.shape(),std::array{3}) );

    array = std::array{1.,2.,3.};

    {
        STATIC_CHECK(( nmtools::meta::is_ndarray_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_ndarray_value_type_t<decltype(array_ref)>> ));
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
    CHECK( isequal(array_ref.shape(),std::array{3,2}) );

    CHECK( array_ref(0,1)==2 );
    CHECK( array_ref(1,0)==3 );

    nmtools::at(array,0,1) = 6;
    nmtools::at(array,1,0) = 7;
    
    CHECK( array_ref(0,1)==6 );
    CHECK( array_ref(1,0)==7 );

    {
        STATIC_CHECK(( nmtools::meta::is_ndarray_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_ndarray_value_type_t<decltype(array_ref)>> ));
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
    CHECK( isequal(array_ref.shape(),std::array{3,2,4}) );

    // @todo provide constructor/assignment op from 3D array

    nmtools::at(array,0,1,0) = 6;
    CHECK( array_ref(0,1,0)==6 );

    {
        STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_ndarray_value_type_t<decltype(array_ref)>> ));
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
    CHECK( isequal(array_ref.shape(),std::array{3,2,4,1}) );

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
    CHECK( isequal(array_ref.shape(),std::array{3}) );
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
    CHECK( isequal(array_ref.shape(),std::array{2,3}) );
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
    CHECK( isequal(array_ref.shape(),std::array{1,3,1}) );

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
    CHECK( isequal(array_ref.shape(),std::array{1,2,2,1}) );

    // @todo provide constructor/assignment op from 3D array

    CHECK( array_ref(0,1,1,0)==4 );
    nmtools::at(array,0,1,1,0) = 6;
    CHECK( array_ref(0,1,1,0)==6 );
}