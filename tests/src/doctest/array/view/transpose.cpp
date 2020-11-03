/**
 * @file transpose.cpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief test file for transpose view
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

/**
 * @test test case for const transpose view to 1D std::array
 */
TEST_CASE("transpose(std::array)"*doctest::test_suite("view::transpose"))
{
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::transpose(array);

    // LOG_TYPEINFO( decltype(array_ref) );
    STATIC_CHECK(( nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );

    STATIC_CHECK(( std::is_same_v<decltype(array_ref.shape()),std::array<size_t,1>> ));
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( nmtools::vector_size(array_ref)==3 );

    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3; 

    {
        array[0] = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    {
        // view should have meta::fixed_array_shape if its underlying array have too
        constexpr auto shape = nmtools::meta::fixed_array_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
        STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    }
}

/**
 * @test test case for const transpose view to 1D std::array using make_view
 */
TEST_CASE("make_view<transpose_t>(std::array)"*doctest::test_suite("view::transpose")) // make_view<transpose_t)>
{
    using view::transpose_t;
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::make_view<transpose_t>(array);

    // @note using make_view results in tparams to view_t (Ts...) of decorator_t to be ref
    // for example, this calls prints:
    // ```
    // decltype(array_ref) = nmtools::view::decorator_t<nmtools::view::transpose_t, std::array<double, 3ul>&>
    // ```
    // LOG_TYPEINFO( decltype(array_ref) );

    STATIC_CHECK(( nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );

    STATIC_CHECK(( std::is_same_v<decltype(array_ref.shape()),std::array<size_t,1>> ));
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( nmtools::vector_size(array_ref)==3 );
    
    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    {
        array[0] = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    {
        // view::decorator_t should have meta::fixed_array_shape if its underlying view have too
        constexpr auto shape = nmtools::meta::fixed_array_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
        STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_vector_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

static_assert( nmtools::meta::has_tuple_size_v<std::pair<size_t,size_t>> );

/**
 * @test test case for const transpose view to 2D std::array
 */
TEST_CASE("transpose(std::array[2])"*doctest::test_suite("view::transpose")) // ref with 2D std::arra)y
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
        STATIC_CHECK(( nmtools::meta::has_tuple_size_v<shape_t> ));
        STATIC_CHECK(( std::is_same_v<array_t,std::array<size_t,2>> ));
    }

    CHECK(array_ref.dim()==2);

    auto shape = array_ref.shape();

    // LOG_TYPEINFO(decltype(shape));
    STATIC_CHECK(( std::is_same_v<decltype(shape),std::array<size_t,2>> ));
    // @note since the transpose doesnt specify axes (that is none_t),
    // the view should be also fixed size
    STATIC_CHECK(( nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));

    CHECK( isclose(shape,std::array{3,2}) );
    CHECK( isclose(nmtools::matrix_size(array_ref),std::tuple{3,2}) );

    {
        auto expected = std::array{
            std::array{1.,3.},
            std::array{2.,4.},
            std::array{3.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }

    {
        nmtools::at(array,1,0) = 10;
        auto expected = std::array{
            std::array{1.,10.},
            std::array{2.,4.},
            std::array{3.,5.},
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
 * @test test case for const transpose view to 2D std::array
 */
TEST_CASE("transpose(std::array[2],tuple{0,1})"*doctest::test_suite("view::transpose")) // ref with 2D std::arra)y
{
    auto array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    auto array_ref = view::transpose(array,std::tuple{0,1});
    // @note even if the underlying array is fixed, but the axes are not compile-time value
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));

    CHECK(array_ref.dim()==2);

    auto shape = array_ref.shape();

    // LOG_TYPEINFO(decltype(shape));
    STATIC_CHECK(( std::is_same_v<decltype(shape),std::array<size_t,2>> ));
    CHECK( isclose(shape,std::array{2,3}) );
    CHECK( isclose(nmtools::matrix_size(array_ref),std::tuple{2,3}) );

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
        STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const transpose view to 2D std::array
 */
TEST_CASE("transpose(std::array[2],tuple{1,0})"*doctest::test_suite("view::transpose")) // ref with 2D std::arra)y
{
    auto array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    auto array_ref = view::transpose(array,std::tuple{1,0});
    // @note even if the underlying array is fixed, but the axes are not compile-time value
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));
    CHECK(array_ref.dim()==2);

    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{3,2}) );
    CHECK( isclose(nmtools::matrix_size(array_ref),std::tuple{3,2}) );

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
        STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const transpose view to 1D std::vector
 */
TEST_CASE("transpose(std::vector)"*doctest::test_suite("view::transpose"))
{
    auto array = std::vector{1.,2.,3.};
    auto array_ref = view::transpose(array);

    STATIC_CHECK(( !nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );

    STATIC_CHECK(( std::is_same_v<decltype(array_ref.shape()),std::array<size_t,1>> ));
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( nmtools::vector_size(array_ref)==3 );

    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3; 

    {
        array[0] = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }
}

/**
 * @test test case for const transpose view to 2D std::vector
 */
TEST_CASE("transpose(std::vector[2])"*doctest::test_suite("view::transpose")) // ref with 2D std::arra)y
{
    auto array = std::vector{
        std::vector{1.,2.,3.},
        std::vector{3.,4.,5.},
    };
    auto array_ref = view::transpose(array);

    // @note since the referenced array is not fixed-size, the the view itself is not either
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));

    CHECK(array_ref.dim()==2);

    auto shape = array_ref.shape();
    CHECK( isclose(shape,std::array{3,2}) );
    CHECK( isclose(nmtools::matrix_size(array_ref),std::tuple{3,2}) );

    {
        auto expected = std::array{
            std::array{1.,3.},
            std::array{2.,4.},
            std::array{3.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }

    {
        nmtools::at(array,1,0) = 10;
        auto expected = std::array{
            std::array{1.,10.},
            std::array{2.,4.},
            std::array{3.,5.},
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
 * @test test case for const transpose view to fixed_vector
 */
TEST_CASE("transpose(fixed_vector)"*doctest::test_suite("view::transpose"))
{
    auto array = fixed_vector<double,3>{1.,2.,3.};
    auto array_ref = view::transpose(array);

    // LOG_TYPEINFO( decltype(array_ref) );
    STATIC_CHECK(( nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );

    STATIC_CHECK(( std::is_same_v<decltype(array_ref.shape()),std::array<size_t,1>> ));
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( nmtools::vector_size(array_ref)==3 );

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
        // view should have meta::fixed_array_shape if its underlying array have too
        constexpr auto shape = nmtools::meta::fixed_array_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
        STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    }
}

/**
 * @test test case for const transpose view to fixed_matrix
 */
TEST_CASE("transpose(fixed_matrix)"*doctest::test_suite("view::transpose")) // ref with 2D std::arra)y
{
    auto array = fixed_matrix<double,2,3>{};
    auto array_ref = view::transpose(array);
    array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    // @note since the referenced array is fixed-size and axes_t of array_ref is none_t, the view is also fixed-size
    STATIC_CHECK(( nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));
    CHECK(array_ref.dim()==2);

    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{3,2}) );
    CHECK( isclose(nmtools::matrix_size(array_ref),std::tuple{3,2}) );

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
        STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const transpose view to fixed_matrix
 */
TEST_CASE("transpose(fixed_matrix,tuple{1,0})"*doctest::test_suite("view::transpose")) // ref with 2D std::arra)y
{
    auto array = fixed_matrix<double,2,3>{};
    auto array_ref = view::transpose(array,std::tuple{1,0});
    array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    // @note even if the referenced array is fixed-size, when the axes value is only known at runtime, then the view is not fixed-size
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));
    CHECK(array_ref.dim()==2);

    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{3,2}) );
    CHECK( isclose(nmtools::matrix_size(array_ref),std::tuple{3,2}) );

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
        STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

/**
 * @test test case for const transpose view to dynamic_vector
 */
TEST_CASE("transpose(dynamic_vector)"*doctest::test_suite("view::transpose"))
{
    auto array = dynamic_vector{1.,2.,3.};
    auto array_ref = view::transpose(array);

    STATIC_CHECK(( !nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );

    STATIC_CHECK(( std::is_same_v<decltype(array_ref.shape()),std::array<size_t,1>> ));
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( nmtools::vector_size(array_ref)==3 );

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
}

/**
 * @test test case for const transpose view to dynamic_matrix
 */
TEST_CASE("transpose(dynamic_matrix)"*doctest::test_suite("view::transpose")) // ref with 2D std::arra)y
{
    auto array = dynamic_matrix{
        {1.,2.,3.},
        {3.,4.,5.},
    };
    auto array_ref = view::transpose(array);

    // @note since the referenced array is not fixed-size, the the view itself is not either
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));

    CHECK(array_ref.dim()==2);

    auto shape = array_ref.shape();
    CHECK( isclose(shape,std::array{3,2}) );
    CHECK( isclose(nmtools::matrix_size(array_ref),std::tuple{3,2}));

    {
        auto expected = std::array{
            std::array{1.,3.},
            std::array{2.,4.},
            std::array{3.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }

    {
        nmtools::at(array,1,0) = 10;
        auto expected = std::array{
            std::array{1.,10.},
            std::array{2.,4.},
            std::array{3.,5.},
        };
        CHECK( isclose(array_ref,expected) );
    }

    {
        STATIC_CHECK(( nmtools::meta::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}