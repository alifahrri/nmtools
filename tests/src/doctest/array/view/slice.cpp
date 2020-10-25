// @note need to includ array impl first to make sure overaload/specialization is visible
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/view.hpp"
#include "nmtools/utility/helper.hpp"
#include "testing/testing.hpp"

#include "doctest/doctest.h"

#include <array>
#include <vector>

namespace view = nmtools::view;
using nmtools::helper::isclose;
using nmtools::array::fixed_vector;
using nmtools::array::fixed_matrix;
using nmtools::array::fixed_ndarray;
using nmtools::array::dynamic_vector;
using nmtools::array::dynamic_matrix;
using nmtools::array::dynamic_ndarray;

TEST_CASE("view::slice") // slice with 1D std::array
{
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::slice(array,0,1);

    {
        auto offset = view::detail::offset(array,0,2);
        STATIC_CHECK(( std::is_same_v<decltype(offset),std::tuple<std::tuple<size_t>,std::tuple<size_t>>> ));
        auto start = std::get<0>(offset);
        auto stop  = std::get<1>(offset);
        CHECK( std::get<0>(start)==0 );
        CHECK( std::get<0>(stop)==2 );
    }

    CHECK( array_ref.dim()==1 );
    auto shape = array_ref.shape();
    // single dimension, known at compile time
    STATIC_CHECK(( std::is_same_v<decltype(shape),std::tuple<size_t>> ));
    // the shape (of slice view) may be runtime value
    CHECK( std::get<0>(shape)==1 );
    // CHECK( isclose(array_ref.shape(),std::array{1}) );
    CHECK( array_ref(0)==1 );

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3;

    array[0] = 3;
    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );

    // @todo make sure is_fixed_size, fixed_vector_size, fixed_array_shape is preserved
}

TEST_CASE("view::slice") // make_view<slice_t>
{
    using view::slice_t;
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::make_view<slice_t>(array,0,1);

    {
        auto offset = view::detail::offset(array,0,2);
        STATIC_CHECK(( std::is_same_v<decltype(offset),std::tuple<std::tuple<size_t>,std::tuple<size_t>>> ));
        auto start = std::get<0>(offset);
        auto stop  = std::get<1>(offset);
        CHECK( std::get<0>(start)==0 );
        CHECK( std::get<0>(stop)==2 );
    }

    CHECK( array_ref.dim()==1 );
    auto shape = array_ref.shape();
    // single dimension, known at compile time
    STATIC_CHECK(( std::is_same_v<decltype(shape),std::tuple<size_t>> ));
    // the shape (of slice view) may be runtime value
    CHECK( std::get<0>(shape)==1 );
    // CHECK( isclose(array_ref.shape(),std::array{1}) );
    CHECK( array_ref(0)==1 );

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3;

    array[0] = 3;
    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );

    // @todo make sure is_fixed_size, fixed_vector_size, fixed_array_shape is preserved
}

TEST_CASE("view::slice")
{
    auto array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    // @note only support tuple for now, cant be pair
    auto array_ref = view::slice(array, std::tuple{0,1}, std::tuple{1,2});
    CHECK(array_ref.dim()==2);
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{1,1}) );

    CHECK( array_ref(0,0)==2 );

    nmtools::at(array,0,1) = 6;

    CHECK( array_ref(0,0)==6 );

    // @note should CRASH, since assert will fail
    // @todo provide support for throw for easy testing
    // CHECK( array_ref(0,1)==6 );
    // CHECK( array_ref(1,0)==7 );

    {
        STATIC_CHECK(( nmtools::traits::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::slice") // slice with 1D std::vector
{
    auto array = std::vector{1.,2.,3.};
    auto array_ref = view::slice(array,0,1);

    CHECK( array_ref.dim()==1 );
    auto shape = array_ref.shape();
    // single dimension, known at compile time
    STATIC_CHECK(( std::is_same_v<decltype(shape),std::tuple<size_t>> ));
    // the shape (of slice view) may be runtime value
    CHECK( std::get<0>(shape)==1 );
    // CHECK( isclose(array_ref.shape(),std::array{1}) );
    CHECK( array_ref(0)==1 );

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3;

    array[0] = 3;
    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );

    // @todo make sure is_fixed_size, fixed_vector_size, fixed_array_shape is preserved
}

TEST_CASE("view::slice")
{
    auto array = std::vector{
        std::vector{1.,2.,3.},
        std::vector{3.,4.,5.},
    };
    // @note only support tuple for now, cant be pair
    auto array_ref = view::slice(array, std::tuple{0,1}, std::tuple{1,2});
    CHECK(array_ref.dim()==2);
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{1,1}) );

    CHECK( array_ref(0,0)==2 );

    nmtools::at(array,0,1) = 6;

    CHECK( array_ref(0,0)==6 );

    // @note should CRASH, since assert will fail
    // @todo provide support for throw for easy testing
    // CHECK( array_ref(0,1)==6 );
    // CHECK( array_ref(1,0)==7 );

    {
        STATIC_CHECK(( nmtools::traits::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

namespace nm = nmtools;

TEST_CASE("view::slice") // slice with 1D std::vector
{
    auto array = fixed_vector<double,3>{1.,2.,3.};
    auto array_ref = view::slice(array,1,nm::end_t{});

    CHECK( array_ref.dim()==1 );
    auto shape = array_ref.shape();
    // single dimension, known at compile time
    STATIC_CHECK(( std::is_same_v<decltype(shape),std::tuple<size_t>> ));
    // the shape (of slice view) may be runtime value
    CHECK( std::get<0>(shape)==2 );
    // CHECK( isclose(array_ref.shape(),std::array{1}) );
    CHECK( array_ref(0)==2 );
    CHECK( array_ref(1)==3 );

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3;

    array(0) = 3;
    CHECK( array_ref(0)==2 );
    CHECK( nmtools::at(array_ref,0)==2 );

    array(1) = 3;
    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );

    // @todo make sure is_fixed_size, fixed_vector_size, fixed_array_shape is preserved
}

TEST_CASE("view::ref") // slice with 2D fixed_ndarray
{
    auto array = fixed_matrix<double,3,2>{};
    auto array_ref = view::slice(array,std::tuple{1,0},std::tuple{nm::end_t{},nm::end_t{}});

    array = std::array{
        std::array{1.,2.},
        std::array{3.,4.},
        std::array{4.,5.},
    };

    CHECK( array_ref.dim()==2 );
    CHECK( isclose(array_ref.shape(),std::array{2,2}) );

    CHECK( array_ref(0,1)==4 );
    CHECK( array_ref(1,0)==4 );
    CHECK( array_ref(1,1)==5 );
    CHECK( array_ref(0,0)==3 );

    nmtools::at(array,0,1) = 6;
    nmtools::at(array,1,0) = 7;
    
    CHECK( array_ref(0,1)==4 );
    CHECK( array_ref(0,0)==7 );

    {
        STATIC_CHECK(( nmtools::traits::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}