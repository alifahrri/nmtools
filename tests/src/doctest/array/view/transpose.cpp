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

TEST_CASE("view::transpose")
{
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::transpose(array);

    CHECK( array_ref.dim()==1 );

    STATIC_CHECK(( std::is_same_v<decltype(array_ref.shape()),std::array<size_t,1>> ));
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( array_ref(0)==1 );

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3; 

    array[0] = 3;
    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );

    {
        // view should have fixed_array_shape if its underlying array have too
        constexpr auto shape = nmtools::fixed_array_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
        STATIC_CHECK(( nmtools::traits::is_array1d_v<decltype(array_ref)> ));
    }
}

TEST_CASE("view::transpose") // make_view<transpose_t>
{
    using view::transpose_t;
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::make_view<transpose_t>(array);
    CHECK( array_ref.dim()==1 );

    STATIC_CHECK(( std::is_same_v<decltype(array_ref.shape()),std::array<size_t,1>> ));
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( array_ref(0)==1 );

    array[0] = 3;
    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );

    {
        // view::decorator_t should have fixed_array_shape if its underlying view have too
        constexpr auto shape = nmtools::fixed_array_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
        STATIC_CHECK(( nmtools::traits::is_array1d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_vector_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

static_assert( nmtools::traits::has_tuple_size_v<std::pair<size_t,size_t>> );

TEST_CASE("view::transpose") // ref with 2D std::array
{
    auto array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    auto array_ref = view::transpose(array);

    {
        using shape_t = decltype(view::detail::shape(array_ref.array));
        using array_t = decltype(nmtools::detail::make_array<std::array>(std::declval<shape_t>()));
        // LOG_TYPEINFO(array_t);
        STATIC_CHECK(( nmtools::traits::has_tuple_size_v<shape_t> ));
        STATIC_CHECK(( std::is_same_v<array_t,std::array<size_t,2>> ));
    }

    CHECK(array_ref.dim()==2);

    auto shape = array_ref.shape();
    // LOG_TYPEINFO(decltype(shape));
    STATIC_CHECK(( std::is_same_v<decltype(shape),std::array<size_t,2>> ));
    CHECK( isclose(shape,std::array{3,2}) );

    // CHECK( array_ref(0,1)==2 );
    // CHECK( array_ref(1,0)==3 );

    // nmtools::at(array,0,1) = 6;
    // nmtools::at(array,1,0) = 7;
    
    // CHECK( array_ref(0,1)==6 );
    // CHECK( array_ref(1,0)==7 );

    {
        STATIC_CHECK(( nmtools::traits::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::transpose") // ref with 2D std::array
{
    auto array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    auto array_ref = view::transpose(array,std::tuple{0,1});

    {
        using shape_t = decltype(view::detail::shape(array_ref.array));
        using array_t = decltype(nmtools::detail::make_array<std::array>(std::declval<shape_t>()));
        // LOG_TYPEINFO(array_t);
        STATIC_CHECK(( nmtools::traits::has_tuple_size_v<shape_t> ));
        STATIC_CHECK(( std::is_same_v<array_t,std::array<size_t,2>> ));
    }

    CHECK(array_ref.dim()==2);

    auto shape = array_ref.shape();

    // LOG_TYPEINFO(decltype(shape));
    STATIC_CHECK(( std::is_same_v<decltype(shape),std::array<size_t,2>> ));
    CHECK( isclose(shape,std::array{2,3}) );

    {
        auto expected = std::array{
            std::array{1.,2.,3.},
            std::array{3.,4.,5.},
        };
        CHECK( isclose(expected,array_ref) );
    }

    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{
            std::array{1.,6.,3.},
            std::array{7.,4.,5.},
        };
        CHECK( isclose(expected,array_ref) );
    }

    {
        STATIC_CHECK(( nmtools::traits::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::transpose") // ref with 2D std::array
{
    auto array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    auto array_ref = view::transpose(array,std::tuple{1,0});
    CHECK(array_ref.dim()==2);

    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{3,2}) );

    {
        auto expected = std::array{
            std::array{1.,3.},
            std::array{2.,4.},
            std::array{3.,5.},
        };
        CHECK( nmtools::helper::isclose(array_ref,expected) );
    }
    
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{
            std::array{1.,7.},
            std::array{6.,4.},
            std::array{3.,5.},
        };
        CHECK( nmtools::helper::isclose(array_ref,expected) );
    }

    {
        STATIC_CHECK(( nmtools::traits::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}