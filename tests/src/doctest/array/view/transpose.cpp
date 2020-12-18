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
#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/isequal.hpp"
#include "testing/testing.hpp"

#include "testing/doctest.hpp"

#include <array>
#include <vector>

// defer static assertion to runtime
#undef NMTOOLS_STATIC_ASSERT
#define NMTOOLS_STATIC_ASSERT NMTOOLS_DEFERRED_STATIC_ASSERT

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
    CHECK( isequal(array_ref.shape(),std::array{3}) );
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
        // view should have meta::fixed_ndarray_shape if its underlying array have too
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
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
    CHECK( isequal(array_ref.shape(),std::array{3}) );
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
        // view::decorator_t should have meta::fixed_ndarray_shape if its underlying view have too
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
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
        using shape_t = decltype(nmtools::shape(array_ref.array));
        using array_t = decltype(nmtools::detail::make_array<std::array>(std::declval<shape_t>()));
        // LOG_TYPEINFO(array_t);
        STATIC_CHECK(( nmtools::meta::has_tuple_size_v<shape_t> ));
        STATIC_CHECK(( std::is_same_v<array_t,std::array<size_t,2>> ));
    }

    CHECK(array_ref.dim()==2);

    auto shape = array_ref.shape();

    // LOG_TYPEINFO(decltype(shape));
    using expected_t = std::array<size_t,2>;
    STATIC_CHECK_IS_SAME( decltype(shape), expected_t );
    // @note since the transpose doesnt specify axes (that is none_t),
    // the view should be also fixed size
    STATIC_CHECK(( nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));

    CHECK( isequal(shape,std::array{3,2}) );
    CHECK( isequal(nmtools::matrix_size(array_ref),std::tuple{3,2}) );

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
    using expected_t = std::array<size_t,2>;
    STATIC_CHECK_IS_SAME( decltype(shape), expected_t );
    CHECK( isequal(shape,std::array{2,3}) );
    CHECK( isequal(nmtools::matrix_size(array_ref),std::tuple{2,3}) );

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

    CHECK( isequal(array_ref.shape(),std::array{3,2}) );
    CHECK( isequal(nmtools::matrix_size(array_ref),std::tuple{3,2}) );

    {
        auto expected = std::array{
            std::array{1.,3.},
            std::array{2.,4.},
            std::array{3.,5.},
        };
        CHECK( nmtools::utils::isclose(array_ref,expected) );
    }
    
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{
            std::array{1.,7.},
            std::array{6.,4.},
            std::array{3.,5.},
        };
        CHECK( nmtools::utils::isclose(array_ref,expected) );
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

    using expected_t = std::array<size_t,1>;
    STATIC_CHECK_IS_SAME( decltype(array_ref.shape()), expected_t );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isequal(array_ref.shape(),std::array{3}) );
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
    CHECK( isequal(shape,std::array{3,2}) );
    CHECK( isequal(nmtools::matrix_size(array_ref),std::tuple{3,2}) );

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
    auto array = fixed_vector({1.,2.,3.});
    auto array_ref = view::transpose(array);

    // LOG_TYPEINFO( decltype(array_ref) );
    STATIC_CHECK(( nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );

    using expected_t = std::tuple<size_t>;
    STATIC_CHECK_IS_SAME( decltype(array_ref.shape()), expected_t );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isequal(array_ref.shape(),std::array{3}) );
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
        // view should have meta::fixed_ndarray_shape if its underlying array have too
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
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

    CHECK( isequal(array_ref.shape(),std::array{3,2}) );
    CHECK( isequal(nmtools::matrix_size(array_ref),std::tuple{3,2}) );

    {
        auto expected = std::array{
            std::array{1.,3.},
            std::array{2.,4.},
            std::array{3.,5.},
        };
        CHECK( nmtools::utils::isclose(array_ref,expected) );
    }
    
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{
            std::array{1.,7.},
            std::array{6.,4.},
            std::array{3.,5.},
        };
        CHECK( nmtools::utils::isclose(array_ref,expected) );
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

    CHECK( isequal(array_ref.shape(),std::array{3,2}) );
    CHECK( isequal(nmtools::matrix_size(array_ref),std::tuple{3,2}) );

    {
        auto expected = std::array{
            std::array{1.,3.},
            std::array{2.,4.},
            std::array{3.,5.},
        };
        CHECK( nmtools::utils::isclose(array_ref,expected) );
    }
    
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{
            std::array{1.,7.},
            std::array{6.,4.},
            std::array{3.,5.},
        };
        CHECK( nmtools::utils::isclose(array_ref,expected) );
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

    using expected_t = std::tuple<size_t>;
    STATIC_CHECK_IS_SAME( decltype(array_ref.shape()), expected_t );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isequal(array_ref.shape(),std::array{3}) );
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

TEST_CASE("transpose(dynamic_ndarray)"*doctest::test_suite("view::transpose"))
{
    auto array = dynamic_ndarray({1.,2.,3.});
    auto array_ref = view::transpose(array);

    STATIC_CHECK(( !nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );

    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), (std::array{3}) );
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), std::array{3} );

    {
        auto expected = std::array{1.,2.,3.};
        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3; 

    {
        nmtools::at(array,0) = 3;
        auto expected = std::array{3.,2.,3.};
        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
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
    CHECK( isequal(shape,std::array{3,2}) );
    CHECK( isequal(nmtools::matrix_size(array_ref),std::tuple{3,2}));

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

TEST_CASE("transpose(dynamic_ndarray)"*doctest::test_suite("view::transpose")) // ref with 2D std::arra)y
{
    double expected[3][2] = {
        {1.,3.},
        {2.,4.},
        {3.,5.},
    };
    double expected2[3][2] = {
        {1.,10.},
        {2.,4.},
        {3.,5.},
    };

    // test without axes as parameter
    {
        auto array = dynamic_ndarray({
            {1.,2.,3.},
            {3.,4.,5.},
        });
        auto array_ref = view::transpose(array);

        // @note since the referenced array is not fixed-size, the the view itself is not either
        STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));

        CHECK(array_ref.dim()==2);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,2}) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
        nmtools::at(array,1,0) = 10;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected2 );
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }

    // test with axes as parameter
    {
        auto array = dynamic_ndarray({
            {1.,2.,3.},
            {3.,4.,5.},
        });
        auto array_ref = view::transpose(array, std::array{1,0});

        // @note since the referenced array is not fixed-size, the the view itself is not either
        STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));

        CHECK(array_ref.dim()==2);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,2}) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
        nmtools::at(array,1,0) = 10;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected2 );
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("transpose(dynamic_ndarray)"*doctest::test_suite("view::transpose")) // ref with 2D std::arra)y
{
    double expected[3][2][2] = {
        {
            {1.,5.},
            {3.,7.},
        },
        {
            {2.,6.},
            {4.,8.},
        },
        {
            {3.,7.},
            {5.,9.},
        },
    };
    double expected2[3][2][2] = {
        {
            {1.,10.},
            {3.,7.},
        },
        {
            {2.,6.},
            {4.,8.},
        },
        {
            {3.,7.},
            {5.,9.},
        },
    };

    {
        auto array = dynamic_ndarray({
            {
                {1.,2.,3.},
                {3.,4.,5.}
            },
            {
                {5.,6.,7.},
                {7.,8.,9.}
            },
        });
        auto array_ref = view::transpose(array);

        // @note since the referenced array is not fixed-size, the the view itself is not either
        STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));

        CHECK(array_ref.dim()==3);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,2,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,2,2}) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
        nmtools::at(array,1,0,0) = 10;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected2 );
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
    {
        auto array = dynamic_ndarray({
            {
                {1.,2.,3.},
                {3.,4.,5.}
            },
            {
                {5.,6.,7.},
                {7.,8.,9.}
            },
        });
        auto array_ref = view::transpose(array,std::array{2,1,0});

        // @note since the referenced array is not fixed-size, the the view itself is not either
        STATIC_CHECK(( !nmtools::meta::is_fixed_size_matrix_v<decltype(array_ref)> ));

        CHECK(array_ref.dim()==3);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,2,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,2,2}) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
        nmtools::at(array,1,0,0) = 10;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected2 );
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));

        // check index mapping
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{0,0,0})), (std::array{0,0,0}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{0,0,1})), (std::array{1,0,0}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{0,1,0})), (std::array{0,1,0}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{0,1,1})), (std::array{1,1,0}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{1,0,0})), (std::array{0,0,1}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{1,0,1})), (std::array{1,0,1}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{1,1,0})), (std::array{0,1,1}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{1,1,1})), (std::array{1,1,1}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{2,0,1})), (std::array{1,0,2}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{2,1,0})), (std::array{0,1,2}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{2,1,1})), (std::array{1,1,2}) );
    }
    {
        auto array = dynamic_ndarray({
            {
                {1.,2.,3.},
                {3.,4.,5.}
            },
        });
        auto array_ref = view::transpose(array,std::array{2,0,1});

        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));

        CHECK(array_ref.dim()==3);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,1,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,1,2}) );

        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{0,0,0})), (std::array{0,0,0}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{0,0,1})), (std::array{0,1,0}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{1,0,0})), (std::array{0,0,1}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{1,0,1})), (std::array{0,1,1}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{2,0,0})), (std::array{0,0,2}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{2,0,1})), (std::array{0,1,2}) );
    }
    {
        auto array = dynamic_ndarray({
            {
                {1.,2.,3.},
                {3.,4.,5.}
            },
            {
                {5.,6.,7.},
                {7.,8.,9.}
            },
        });
        auto array_ref = view::transpose(array,std::array{2,0,1});

        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));

        CHECK(array_ref.dim()==3);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,2,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,2,2}) );

        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{0,0,0})), (std::array{0,0,0}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{0,0,1})), (std::array{0,1,0}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{0,1,0})), (std::array{1,0,0}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{0,1,1})), (std::array{1,1,0}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{1,0,0})), (std::array{0,0,1}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{1,0,1})), (std::array{0,1,1}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{1,1,0})), (std::array{1,0,1}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{1,1,1})), (std::array{1,1,1}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{2,0,0})), (std::array{0,0,2}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{2,0,1})), (std::array{0,1,2}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{2,1,0})), (std::array{1,0,2}) );
        NMTOOLS_ASSERT_EQUAL( (array_ref.index(std::array{2,1,1})), (std::array{1,1,2}) );

        double expected[3][2][2] = {
            {
                {1.,3.},
                {5.,7.},
            },
            {
                {2.,4.},
                {6.,8.},
            },
            {
                {3.,5.},
                {7.,9.},
            },
        };
        double expected2[3][2][2] = {
            {
                {1.,3.},
                {10.,7.},
            },
            {
                {2.,4.},
                {6.,8.},
            },
            {
                {3.,5.},
                {7.,9.},
            },
        };

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
        nmtools::at(array,1,0,0) = 10;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected2 );
    }
}

TEST_CASE("transpose(dynamic_ndarray)"*doctest::test_suite("view::transpose")) // ref with 2D std::arra)y
{
    double expected[3][1][2][2] = {
        {
            {
                {1.,5.},
                {3.,7.},
            }
        },
        {
            {
                {2.,6.},
                {4.,8.},
            }
        },
        {
            {
                {3.,7.},
                {5.,9.},
            }
        },
    };

    double expected2[3][1][2][2] = {
        {
            {
                {1.,10.},
                {3.,7.},
            }
        },
        {
            {
                {2.,6.},
                {4.,8.},
            }
        },
        {
            {
                {3.,7.},
                {5.,9.},
            }
        },
    };

    double expected3[3][2][1][2] = {
        {
            {
                {1.,5.},
            },
            {
                {3.,7.},
            }
        },
        {
            {
                {2.,6.},
            },
            {
                {4.,8.},
            }
        },
        {
            {
                {3.,7.},
            },
            {
                {5.,9.},
            }
        },
    };

    double expected4[3][2][1][2] = {
        {
            {
                {1.,10.},
            },
            {
                {3.,7.},
            }
        },
        {
            {
                {2.,6.},
            },
            {
                {4.,8.},
            }
        },
        {
            {
                {3.,7.},
            },
            {
                {5.,9.},
            }
        },
    };

    auto array = dynamic_ndarray({
        {
            {
                {1.,2.,3.},
            },
            {
                {3.,4.,5.}
            }
        },
        {
            {
                {5.,6.,7.},
            },
            {
                {7.,8.,9.}
            }
        },
    });
    {
        auto array_ref = view::transpose(array);

        STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(array_ref) );

        CHECK(array_ref.dim()==4);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,1,2,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,1,2,2}) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
        nmtools::at(array,1,0,0,0) = 10;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected2 );
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
    {
        auto array_ref = view::transpose(array,std::array{3,2,1,0});

        STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(array_ref) );

        CHECK(array_ref.dim()==4);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,1,2,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,1,2,2}) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected2 );
        nmtools::at(array,1,0,0,0) = 5;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
    {
        auto array_ref = view::transpose(array,std::array{3,1,2,0});

        STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(array_ref) );

        CHECK(array_ref.dim()==4);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,2,1,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,2,1,2}) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected3 );
        nmtools::at(array,1,0,0,0) = 10;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected4 );
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("transpose(fixed_ndarray)"*doctest::test_suite("view::transpose"))
{
    auto array = fixed_ndarray{{1.,2.,3.}};
    auto array_ref = view::transpose(array);

    CHECK( array_ref.dim()==1 );

    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), (std::array{3}) );
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), std::array{3} );

    {
        auto expected = std::array{1.,2.,3.};
        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3; 

    {
        nmtools::at(array,0) = 3;
        auto expected = std::array{3.,2.,3.};
        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("transpose(fixed_ndarray)"*doctest::test_suite("view::transpose")) // ref with 2D std::arra)y
{
    auto array = fixed_ndarray{{
        {1.,2.,3.},
        {3.,4.,5.},
    }};
    auto array_ref = view::transpose(array);

    CHECK(array_ref.dim()==2);

    auto shape = array_ref.shape();
    NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,2}) );
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,2}) );

    {
        auto expected = std::array{
            std::array{1.,3.},
            std::array{2.,4.},
            std::array{3.,5.},
        };
        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }

    {
        nmtools::at(array,1,0) = 10;
        auto expected = std::array{
            std::array{1.,10.},
            std::array{2.,4.},
            std::array{3.,5.},
        };
        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }

    {
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("transpose(fixed_ndarray)"*doctest::test_suite("view::transpose")) // ref with 2D std::arra)y
{
    double expected[3][2][2] = {
        {
            {1.,5.},
            {3.,7.},
        },
        {
            {2.,6.},
            {4.,8.},
        },
        {
            {3.,7.},
            {5.,9.},
        },
    };
    double expected2[3][2][2] = {
        {
            {1.,10.},
            {3.,7.},
        },
        {
            {2.,6.},
            {4.,8.},
        },
        {
            {3.,7.},
            {5.,9.},
        },
    };
    auto array = fixed_ndarray{{
        {
            {1.,2.,3.},
            {3.,4.,5.}
        },
        {
            {5.,6.,7.},
            {7.,8.,9.}
        },
    }};
    {
        auto array_ref = view::transpose(array);

        CHECK(array_ref.dim()==3);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,2,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,2,2}) );

        STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(array_ref) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
        nmtools::at(array,1,0,0) = 10;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected2 );
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
    {
        auto array_ref = view::transpose(array,std::array{2,1,0});

        CHECK(array_ref.dim()==3);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,2,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,2,2}) );

        STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(array_ref) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected2 );
        nmtools::at(array,1,0,0) = 5;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
    {
        auto array = fixed_ndarray{{
            {
                {1.,2.,3.},
                {3.,4.,5.}
            },
        }};
        auto array_ref = view::transpose(array,std::array{2,0,1});

        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));

        CHECK(array_ref.dim()==3);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,1,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,1,2}) );
    }
    {
        auto array = fixed_ndarray{{
            {
                {1.,2.,3.},
                {3.,4.,5.}
            },
            {
                {5.,6.,7.},
                {7.,8.,9.}
            },
        }};
        auto array_ref = view::transpose(array,std::array{2,0,1});

        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));

        CHECK(array_ref.dim()==3);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,2,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,2,2}) );

        double expected[3][2][2] = {
            {
                {1.,3.},
                {5.,7.},
            },
            {
                {2.,4.},
                {6.,8.},
            },
            {
                {3.,5.},
                {7.,9.},
            },
        };
        double expected2[3][2][2] = {
            {
                {1.,3.},
                {10.,7.},
            },
            {
                {2.,4.},
                {6.,8.},
            },
            {
                {3.,5.},
                {7.,9.},
            },
        };

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
        nmtools::at(array,1,0,0) = 10;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected2 );
    }
}

TEST_CASE("transpose(fixed_ndarray)"*doctest::test_suite("view::transpose")) // ref with 2D std::arra)y
{
    double expected[3][1][2][2] = {
        {
            {
                {1.,5.},
                {3.,7.},
            }
        },
        {
            {
                {2.,6.},
                {4.,8.},
            }
        },
        {
            {
                {3.,7.},
                {5.,9.},
            }
        },
    };

    double expected2[3][1][2][2] = {
        {
            {
                {1.,10.},
                {3.,7.},
            }
        },
        {
            {
                {2.,6.},
                {4.,8.},
            }
        },
        {
            {
                {3.,7.},
                {5.,9.},
            }
        },
    };

    double expected3[3][2][1][2] = {
        {
            {
                {1.,5.},
            },
            {
                {3.,7.},
            }
        },
        {
            {
                {2.,6.},
            },
            {
                {4.,8.},
            }
        },
        {
            {
                {3.,7.},
            },
            {
                {5.,9.},
            }
        },
    };

    double expected4[3][2][1][2] = {
        {
            {
                {1.,10.},
            },
            {
                {3.,7.},
            }
        },
        {
            {
                {2.,6.},
            },
            {
                {4.,8.},
            }
        },
        {
            {
                {3.,7.},
            },
            {
                {5.,9.},
            }
        },
    };

    auto array = fixed_ndarray{{
        {
            {
                {1.,2.,3.},
            },
            {
                {3.,4.,5.}
            }
        },
        {
            {
                {5.,6.,7.},
            },
            {
                {7.,8.,9.}
            }
        },
    }};
    {
        auto array_ref = view::transpose(array);

        STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(array_ref) );

        CHECK(array_ref.dim()==4);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,1,2,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,1,2,2}) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
        nmtools::at(array,1,0,0,0) = 10;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected2 );
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
    {
        auto array_ref = view::transpose(array,std::array{3,2,1,0});

        STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(array_ref) );

        CHECK(array_ref.dim()==4);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,1,2,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,1,2,2}) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected2 );
        nmtools::at(array,1,0,0,0) = 5;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
    {
        auto array_ref = view::transpose(array,std::array{3,1,2,0});

        STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(array_ref) );

        CHECK(array_ref.dim()==4);

        auto shape = array_ref.shape();
        NMTOOLS_ASSERT_EQUAL( shape, (std::array{3,2,1,2}) );
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), (std::array{3,2,1,2}) );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected3 );
        nmtools::at(array,1,0,0,0) = 10;
        NMTOOLS_ASSERT_CLOSE( array_ref, expected4 );
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}