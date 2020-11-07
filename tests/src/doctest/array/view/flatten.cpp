/**
 * @file flatten.cpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief test file for flatten view
 * @date 2020-10-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/view.hpp"
#include "nmtools/utility/helper.hpp"
#include "testing/doctest.hpp"

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

TEST_CASE("flatten(std::array)" * doctest::test_suite("view::flatten"))
{
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::flatten(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );

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

    // {
    //     // view should have meta::fixed_ndarray_shape if its underlying array have too
    //     constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
    //     STATIC_CHECK(( std::get<0>(shape)==3 ));
    //     STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // }
}

TEST_CASE("make_view<flatten_t>(std::array)" * doctest::test_suite("view::flatten"))
{
    using view::flatten_t;
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::make_view<flatten_t>(array);
    
    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );

    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // LOG_TYPEINFO( decltype(array_ref) );
    // STATIC_CHECK(( nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

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

    // {
    //     // view should have meta::fixed_ndarray_shape if its underlying array have too
    //     constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
    //     STATIC_CHECK(( std::get<0>(shape)==3 ));
    //     STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // }
}

TEST_CASE("flatten(std::array[2])" * doctest::test_suite("view::flatten"))
{
    auto array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    auto array_ref = view::flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{6}) );

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{1.,6.,3.,7.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
}

TEST_CASE("flatten(std::vector)" * doctest::test_suite("view::flatten"))
{
    auto array = std::vector{1.,2.,3.};
    auto array_ref = view::flatten(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );

    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // LOG_TYPEINFO( decltype(array_ref) );
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

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

    // {
    //     // view should have meta::fixed_ndarray_shape if its underlying array have too
    //     constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
    //     STATIC_CHECK(( std::get<0>(shape)==3 ));
    //     STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // }
}

TEST_CASE("flatten(std::array[2])" * doctest::test_suite("view::flatten"))
{
    auto array = std::vector{
        std::vector{1.,2.,3.},
        std::vector{3.,4.,5.},
    };
    auto array_ref = view::flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{6}) );

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{1.,6.,3.,7.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
}

TEST_CASE("flatten(fixed_vector)" * doctest::test_suite("view::flatten"))
{
    auto array = fixed_vector<double,3>{1.,2.,3.};
    auto array_ref = view::flatten(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );

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

    // {
    //     // view should have meta::fixed_ndarray_shape if its underlying array have too
    //     constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
    //     STATIC_CHECK(( std::get<0>(shape)==3 ));
    //     STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // }
}

TEST_CASE("flatten(fixed_matrix)" * doctest::test_suite("view::flatten"))
{
    auto array = fixed_matrix<double,2,3>{};
    auto array_ref = view::flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{6}) );

    array = {
        {1.,2.,3.},
        {3.,4.,5.},
    };

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{1.,6.,3.,7.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
}

TEST_CASE("flatten(dynamic_vector)" * doctest::test_suite("view::flatten"))
{
    auto array = dynamic_vector{1.,2.,3.};
    auto array_ref = view::flatten(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );

    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // LOG_TYPEINFO( decltype(array_ref) );
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

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

    // {
    //     // view should have meta::fixed_ndarray_shape if its underlying array have too
    //     constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
    //     STATIC_CHECK(( std::get<0>(shape)==3 ));
    //     STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // }
}

TEST_CASE("flatten(dynamic_matrix)" * doctest::test_suite("view::flatten"))
{
    auto array = dynamic_matrix{
        {1.,2.,3.},
        {3.,4.,5.},
    };
    auto array_ref = view::flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{6}) );

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{1.,6.,3.,7.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
}

TEST_CASE("flatten(fixed_ndarray[1])" * doctest::test_suite("view::flatten"))
{
    auto array = fixed_ndarray<double,3>{1.,2.,3.};
    auto array_ref = view::flatten(array);
    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{3}) );

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

TEST_CASE("flatten(fixed_ndarray[2])" * doctest::test_suite("view::flatten"))
{
    auto array = fixed_ndarray<double,2,3>{};
    auto array_ref = view::flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array,0,1) = 6;
        nmtools::at(array,1,0) = 7;
        auto expected = std::array{1.,6.,3.,7.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
}

TEST_CASE("flatten(fixed_ndarray[3])" * doctest::test_suite("view::flatten"))
{
    auto array = fixed_ndarray<double,3,2,3>{};
    auto array_ref = view::flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{3*2*3}) );

    nmtools::at(array,0,0,0) = 6;
    CHECK( array_ref(0)==6 );
    nmtools::at(array,0,0,0) = 7;
    CHECK( array_ref(0)==7 );
    nmtools::at(array,2,0,1) = 9;
    CHECK( array_ref(13)==9 );
    nmtools::at(array,2,0,1) = 10;
    CHECK( array_ref(13)==10 );
}

TEST_CASE("flatten(fixed_ndarary[4])" * doctest::test_suite("view::flatten"))
{
    auto array = fixed_ndarray<double,2,3,4,1>{};
    auto array_ref = view::flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{2*3*4*1}) );

    nmtools::at(array,0,0,0,0) = 6;
    CHECK( array_ref(0)==6 );

    nmtools::at(array,0,0,0,0) = 7;
    CHECK( array_ref(0)==7 );
    nmtools::at(array,0,0,1,0) = 8;
    CHECK( array_ref(1)==8 );
    nmtools::at(array,0,0,2,0) = 9;
    CHECK( array_ref(2)==9 );
    nmtools::at(array,0,0,3,0) = 2;
    CHECK( array_ref(3)==2 );

    nmtools::at(array,0,1,0,0) = 1;
    CHECK( array_ref(4)==1 );
    nmtools::at(array,0,1,1,0) = 5;
    CHECK( array_ref(5)==5 );
    nmtools::at(array,0,1,2,0) = 8;
    CHECK( array_ref(6)==8 );
    nmtools::at(array,0,1,3,0) = 10;
    CHECK( array_ref(7)==10 );

    nmtools::at(array,0,2,0,0) = 1;
    CHECK( array_ref(8)==1 );
    nmtools::at(array,0,2,1,0) = 5;
    CHECK( array_ref(9)==5 );
    nmtools::at(array,0,2,2,0) = 8;
    CHECK( array_ref(10)==8 );
    nmtools::at(array,0,2,3,0) = 10;
    CHECK( array_ref(11)==10 );

    nmtools::at(array,1,0,0,0) = 1;
    CHECK( array_ref(12)==1 );
    nmtools::at(array,1,0,1,0) = 5;
    CHECK( array_ref(13)==5 );
    nmtools::at(array,1,0,2,0) = 8;
    CHECK( array_ref(14)==8 );
    nmtools::at(array,1,0,3,0) = 10;
    CHECK( array_ref(15)==10 );
}

TEST_CASE("flatten(fixed_ndarary[5])" * doctest::test_suite("view::flatten"))
{
    auto array = fixed_ndarray<double,2,3,4,1,2>{};
    auto array_ref = view::flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{2*3*4*1*2}) );

    nmtools::at(array,0,0,0,0,0) = 7;
    CHECK( array_ref(0)==7 );
    nmtools::at(array,0,0,0,0,1) = 6;
    CHECK( array_ref(1)==6 );
    nmtools::at(array,0,0,1,0,0) = 5;
    CHECK( array_ref(2)==5 );
    nmtools::at(array,0,0,1,0,1) = 4;
    CHECK( array_ref(3)==4 );
    nmtools::at(array,0,0,2,0,0) = 4;
    CHECK( array_ref(4)==4 );
    nmtools::at(array,0,0,2,0,1) = 3;
    CHECK( array_ref(5)==3 );
    nmtools::at(array,0,0,3,0,0) = 2;
    CHECK( array_ref(6)==2 );
    nmtools::at(array,0,0,3,0,1) = 1;
    CHECK( array_ref(7)==1 );

}