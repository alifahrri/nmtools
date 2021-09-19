/**
 * @file mutable_ref.cpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief test file for mutable_ref view
 * @date 2020-10-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "nmtools/array/view.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/isequal.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <vector>

namespace view = nmtools::view;
using nmtools::utils::isclose;
using nmtools::utils::isequal;
using nmtools::array::fixed_ndarray;
using nmtools::array::dynamic_ndarray;

/**
 * @test test case for mutable ref view to 1D std::array
 * 
 */
TEST_CASE("mutable_ref(std::array)" * doctest::test_suite("view::mutable_ref")) // mutable_ref with 1D std::array
{
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::mutable_ref(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );

    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    {
        array_ref(0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }

    {
        // view should have meta::fixed_ndarray_shape if its underlying array have too
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
    }
}

/**
 * @test test case for mutable ref view to 1D std::array created using make_view
 * 
 */
TEST_CASE("make_view<mutable_ref_t>(std::array)"*doctest::test_suite("view::mutable_ref")) // make_view<mutable_ref_t>
{
    using view::mutable_ref_t;
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::make_view<mutable_ref_t>(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isequal(array_ref.shape(),std::array{3}) );
    
    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    {
        array_ref(0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }

    {
        // view should have meta::fixed_ndarray_shape if its underlying array have too
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
    }
}

/**
 * @test test case for mutable ref view to std::vector
 * 
 */
TEST_CASE("mutable_ref(std::vector[1])"*doctest::test_suite("view::mutable_ref")) // ref with 1D std::vector
{
    auto array = std::vector{1.,2.,3.};
    auto array_ref = view::mutable_ref(array);

    CHECK( array_ref.dim()==1 );
    CHECK( isequal(array_ref.shape(),std::array{3}) );
    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        array_ref(0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }
    CHECK( nmtools::at(array_ref,0)==3 );
}

/**
 * @test test case for mutable ref view to 1D fixed_ndarray
 * 
 */
TEST_CASE("mutable_ref(fixed_ndarray[1])" * doctest::test_suite("view::mutable_ref")) // ref with 1D fixed_ndarray
{
    auto array = fixed_ndarray{{1.,2.,3.}};
    auto array_ref = view::mutable_ref(array);
    CHECK( array_ref.dim()==1 );
    CHECK( isequal(array_ref.shape(),std::array{3}) );

    array = std::array{1.,2.,3.};
}

/**
 * @test test case for mutable ref view to 2D fixed_ndarray
 * 
 */
TEST_CASE("mutable_ref(fixed_ndarray[2])" * doctest::test_suite("view::mutable_ref")) // ref with 2D fixed_ndarray
{
    auto array = fixed_ndarray{{
        {1.,2.},
        {3.,4.},
        {4.,5.},
    }};
    auto array_ref = view::mutable_ref(array);

    {
        auto expected = std::array{
            std::array{1.,2.},
            std::array{3.,4.},
            std::array{4.,5.},
        };
        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }

    CHECK( array_ref.dim()==2 );
    CHECK( isequal(array_ref.shape(),std::array{3,2}) );

    CHECK( array_ref(0,1)==2 );
    CHECK( array_ref(1,0)==3 );

    nmtools::at(array_ref,0,1) = 6;
    nmtools::at(array_ref,1,0) = 7;
    
    CHECK( nmtools::at(array,0,1)==6 );
    CHECK( nmtools::at(array,1,0)==7 );
}

/**
 * @test test case for mutable ref to 3D fixed_ndarray
 * 
 */
TEST_CASE("mutable_ref(fixed_ndarray[3])"*doctest::test_suite("view::mutable_ref")) // ref with 3D fixed_ndarray
{
    auto array = fixed_ndarray<double,3,2,4>{};
    auto array_ref = view::mutable_ref(array);
    CHECK( array_ref.dim()==3 );
    CHECK( isequal(array_ref.shape(),std::array{3,2,4}) );

    // @todo provide constructor/assignment op from 3D array

    nmtools::at(array_ref,0,1,0) = 6;
    CHECK( nmtools::at(array,0,1,0)==6 );
}

/**
 * @test test case for mutable ref to 4D fixed_ndarray
 * 
 */
TEST_CASE("mutable_ref(fixed_ndarray[4])"*doctest::test_suite("view::mutable_ref")) // // ref with 4D fixed_ndarray
{
    auto array = fixed_ndarray<double,3,2,4,1>{};
    auto array_ref = view::mutable_ref(array);
    CHECK( array_ref.dim()==4 );
    CHECK( isequal(array_ref.shape(),std::array{3,2,4,1}) );

    // @todo provide constructor/assignment op from 4D array

    nmtools::at(array_ref,0,1,3,0) = 6;
    CHECK( nmtools::at(array,0,1,3,0)==6 );
}

/**
 * @test test case for mutable ref view to 1D dynamic_ndarray
 * 
 */
TEST_CASE("mutable_ref(dynamic_ndarray[1])"*doctest::test_suite("view::mutable_ref")) // ref with 1D dynamic_ndarray
{
    auto array = dynamic_ndarray({1.,2.,3.});
    auto array_ref = view::mutable_ref(array);
    CHECK( array_ref.dim()==1 );
    CHECK( isequal(array_ref.shape(),std::array{3}) );
}

/**
 * @test test case for mutable ref view to 2D dynamic_ndarray
 * 
 */
TEST_CASE("mutable_ref(dynamic_ndarray[2])"*doctest::test_suite("view::mutable_ref")) // ref with 2D dynamic_ndarray
{
    auto array = dynamic_ndarray({
        {1.,2.,3.},
        {3.,4.,5.}
    });
    auto array_ref = view::mutable_ref(array);
    CHECK( array_ref.dim()==2 );
    CHECK( isequal(array_ref.shape(),std::array{2,3}) );
}

/**
 * @test test case for mutable ref view to 3D dynamic_ndarray
 * 
 */
TEST_CASE("mutable_ref(dynamic_ndarray[3]"*doctest::test_suite("view::mutable_ref")) // ref with 3D dynamic_ndarray
{
    // @note initialize 3D ndarray from flat storage with specified shape
    auto array = dynamic_ndarray<double>();
    array.resize({1,3,1});
    // @note ambiguous
    // array = {{{1},{2},{3}}};
    double a[1][3][1] = {{{1},{2},{3}}};
    array = std::move(a);
    auto array_ref = view::mutable_ref(array);
    CHECK( array_ref.dim()==3 );
    CHECK( isequal(array_ref.shape(),std::array{1,3,1}) );

    // @todo provide constructor/assignment op from 3D array
}

/**
 * @brief test case for mutable ref view to 4D dynamic_ndarray
 * 
 */
TEST_CASE("mutable_ref(dynamic_ndarray[3])"*doctest::test_suite("view::mutable_ref")) // ref with 4D dynamic_ndarray
{
    // @note initialize 3D ndarray from flat storage with specified shape
    auto array = dynamic_ndarray<double>();
    array.resize({1,2,2,1});
    // @note ambiguous because the size of the last axis is 1
    // array = {{{{1.},{2.}},{{3.},{4.}}}};
    double a[1][2][2][1] = {{{{1.},{2.}},{{3.},{4.}}}};
    array = std::move(a);
    auto array_ref = view::mutable_ref(array);
    CHECK( array_ref.dim()==4 );
    CHECK( isequal(array_ref.shape(),std::array{1,2,2,1}) );

    // @todo provide constructor/assignment op from 3D array

    CHECK( array_ref(0,1,1,0)==4 );
    nmtools::at(array_ref,0,1,1,0) = 6;
    CHECK( nmtools::at(array,0,1,1,0)==6 );
}