/**
 * @file mutable_slice.cpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief test file for mutable_slice view
 * @date 2020-10-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
// @note need to includ array impl first to make sure overaload/specialization is visible
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/view.hpp"
#include "nmtools/utility/helper.hpp"
#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/isequal.hpp"
#include "testing/testing.hpp"

#include "doctest/doctest.h"

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
 * @test test case for mutable slice view to 1D std::array
 */
TEST_CASE("mutable_slice(std::array)"*doctest::test_suite("view::mutable_slice")) // mutable_slice with 1D std::array
{
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::mutable_slice(array,0,1);
    // @note even if the referenced array is fixed-size (std::array), the slice args are not!
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    auto shape = array_ref.shape();
    // single dimension, known at compile time
    STATIC_CHECK_IS_SAME( decltype(shape), std::tuple<size_t> );
    // the shape (of mutable_slice view) may be runtime value
    CHECK( std::get<0>(shape)==1 );
    // CHECK( isclose(array_ref.shape(),std::array{1}) );

    {
        auto expected = std::array{1.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        array_ref(0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }

    // @todo make sure is_fixed_size, meta::fixed_vector_size, meta::fixed_ndarray_shape is preserved
}

/**
 * @test test case for mutable slice view to 1D std::array using make_view
 */
TEST_CASE("make_view<mutable_slice_t>(std::array)"*doctest::test_suite("view::mutable_slice")) // make_view<slice_t>
{
    using view::mutable_slice_t;
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::make_view<mutable_slice_t>(array,0,1);
    // @note even if the referenced array is fixed-size (std::array), the slice args are not!
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    auto shape = array_ref.shape();
    // single dimension, known at compile time
    STATIC_CHECK_IS_SAME( decltype(shape), std::tuple<size_t> );
    // the shape (of mutable_slice view) may be runtime value
    CHECK( std::get<0>(shape)==1 );
    // CHECK( isclose(array_ref.shape(),std::array{1}) );
    {
        auto expected = std::array{1.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        array_ref(0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }

    // @todo make sure is_fixed_size, meta::fixed_vector_size, meta::fixed_ndarray_shape is preserved
}

/**
 * @test test case for mutable slice view 2D std::array
 */
TEST_CASE("mutable_slice(std::array[2])"*doctest::test_suite("view::mutable_slice"))
{
    auto array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    // @note only support tuple for now, cant be pair
    auto array_ref = view::mutable_slice(array, std::tuple{0,1}, std::tuple{1,2});
    // @note even if the referenced array is fixed-size (std::array), the slice args are not!
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));

    CHECK(array_ref.dim()==2);
    // @note that isequal can also handle comparison between pair/tuple with array
    CHECK( isequal(array_ref.shape(),std::array{1,1}) );

    {
        // @note somehow this deduced to std::array<double, 1ul>
        // auto expected = std::array{
        //     std::array{2.},
        // };
        // LOG_TYPEINFO(decltype(expected));
        auto expected = std::array<std::array<double,1>,1>{{{2.}}};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,0,0) = 6;
        auto expected = std::array{
            std::array{1.,6.,3.},
            std::array{3.,4.,5.},
        };
        CHECK( isclose(array,expected) );
    }

    // @note should CRASH, since assert will fail
    // @todo provide support for throw for easy testing
    // CHECK( array_ref(0,1)==6 );
    // CHECK( array_ref(1,0)==7 );

    {
        STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for mutable slice view to 1D std::vector
 */
TEST_CASE("mutable_slice(std::vector)"*doctest::test_suite("view::mutable_slice")) // mutable_slice with 1D std::vector
{
    auto array = std::vector{1.,2.,3.};
    auto array_ref = view::mutable_slice(array,0,1);
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    auto shape = array_ref.shape();
    // single dimension, known at compile time
    STATIC_CHECK_IS_SAME( decltype(shape), std::tuple<size_t> );
    // the shape (of mutable_slice view) may be runtime value
    CHECK( std::get<0>(shape)==1 );
    // CHECK( isclose(array_ref.shape(),std::array{1}) );
    {
        auto expected = std::array{1.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        array_ref(0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }

    // @todo make sure is_fixed_size, meta::fixed_vector_size, meta::fixed_ndarray_shape is preserved
}

/**
 * @test test case for mutable slice view 2D std::vector
 */
TEST_CASE("mutable_slice(std::vector[2])"*doctest::test_suite("view::mutable_slice"))
{
    auto array = std::vector{
        std::vector{1.,2.,3.},
        std::vector{3.,4.,5.},
    };
    // @note only support tuple for now, cant be pair
    auto array_ref = view::mutable_slice(array, std::tuple{0,1}, std::tuple{1,2});
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));

    CHECK(array_ref.dim()==2);
    // @note that isequal can also handle comparison between pair/tuple with array
    CHECK( isequal(array_ref.shape(),std::array{1,1}) );

    {
        // @note somehow this deduced to std::array<double, 1ul>
        // auto expected = std::array{
        //     std::array{2.},
        // };
        // LOG_TYPEINFO(decltype(expected));
        auto expected = std::array<std::array<double,1>,1>{{{2.}}};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,0,0) = 6;
        auto expected = std::array{
            std::array{1.,6.,3.},
            std::array{3.,4.,5.},
        };
        CHECK( isclose(array,expected) );
    }

    // @note should CRASH, since assert will fail
    // @todo provide support for throw for easy testing
    // CHECK( array_ref(0,1)==6 );
    // CHECK( array_ref(1,0)==7 );

    {
        STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

namespace nm = nmtools;

/**
 * @test test case for mutable slice view to fixed_vector
 */
TEST_CASE("mutable_slice(fixed_vector)"*doctest::test_suite("view::mutable_slice")) // mutable_slice with 1D std::vector
{
    auto array = fixed_vector<double,3>{1.,2.,3.};
    auto array_ref = view::mutable_slice(array,1,nm::end_t{});
    // @note even if the referenced array is fixed-size (fixed_vector), the slice args are not!
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    auto shape = array_ref.shape();
    // single dimension, known at compile time
    STATIC_CHECK_IS_SAME( decltype(shape), std::tuple<size_t> );
    // the shape (of mutable_slice view) may be runtime value
    CHECK( std::get<0>(shape)==2 );
    // CHECK( isclose(array_ref.shape(),std::array{1}) );
    {
        auto expected = std::array{2.,3.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        array_ref(0) = 3;
        auto expected = std::array{1.,3.,3.};
        CHECK( isclose(array,expected) );
    }

    // @todo make sure is_fixed_size, meta::fixed_vector_size, meta::fixed_ndarray_shape is preserved
}

/**
 * @test test case for mutable slice view to fixed_matrix
 */
TEST_CASE("mutable_slice(fixed_matrix)"*doctest::test_suite("view::mutable_slice")) // mutable_slice with 2D fixed_ndarray
{
    auto array = fixed_matrix<double,3,2>{};
    auto array_ref = view::mutable_slice(array,std::tuple{1,0},std::tuple{nm::end_t{},nm::end_t{}});
    // @note even if the referenced array is fixed-size (fixed_matrix), the slice args are not!
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));

    array = std::array{
        std::array{1.,2.},
        std::array{3.,4.},
        std::array{4.,5.},
    };

    CHECK( array_ref.dim()==2 );
    CHECK( isequal(array_ref.shape(),std::array{2,2}) );
    
    {
        auto expected = std::array{
            std::array{3.,4.},
            std::array{4.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,0,1) = 6;
        nmtools::at(array_ref,1,0) = 7;
        auto expected = std::array{
            std::array{1.,2.},
            std::array{3.,6.},
            std::array{7.,5.},
        };
        CHECK( isclose(array,expected) );
    }

    {
        STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}