/**
 * @file ndarray.cpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief Test file for ndarray traits
 * @date 2020-11-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "nmtools/meta.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
// NOTE: need to include utility for nmtools_array fixed_size specialization
#include "nmtools/array/utility.hpp"
#include "nmtools/testing/testing.hpp"

#if __has_include("doctest/doctest.h")
    #include "doctest/doctest.h"
#else
   #include "doctest.h"
#endif
#include <array>

namespace nm   = nmtools;
namespace meta = nmtools::meta;

TEST_CASE("is_fixed_size_ndarray_v" * doctest::test_suite("array"))
{
    {
        using arg_t = double[3][2][4][5];
        NMTOOLS_STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3][2][4];
        NMTOOLS_STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3][2];
        NMTOOLS_STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3];
        NMTOOLS_STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double;
        NMTOOLS_STATIC_CHECK(( !meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2,3,4,5>;
        NMTOOLS_STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2,3,4>;
        NMTOOLS_STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2,3>;
        NMTOOLS_STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2>;
        NMTOOLS_STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools::array::dynamic_ndarray<double>;
        NMTOOLS_STATIC_CHECK(( !meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_array<nmtools_array<nmtools_array<nmtools_array<nmtools_array<double,5>,4>,3>,2>,1>;
        NMTOOLS_STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_array<nmtools_array<nmtools_array<nmtools_array<double,4>,3>,2>,1>;
        NMTOOLS_STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_array<nmtools_array<nmtools_array<double,3>,2>,1>;
        NMTOOLS_STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_array<nmtools_array<double,2>,1>;
        NMTOOLS_STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_array<double,1>;
        NMTOOLS_STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_list<nmtools_list<nmtools_list<double>>>;
        NMTOOLS_STATIC_CHECK(( !meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_list<nmtools_list<double>>;
        NMTOOLS_STATIC_CHECK(( !meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_list<double>;
        NMTOOLS_STATIC_CHECK(( !meta::is_fixed_size_ndarray_v<arg_t> ));
    }
}

TEST_CASE("fixed_ndarray_dim_v" * doctest::test_suite("array"))
{
    {
        using arg_t = double[3][2][4][5];
        NMTOOLS_STATIC_CHECK(( meta::fixed_ndarray_dim_v<arg_t> == 4 ));
    }
    {
        using arg_t = double[3][2][4];
        NMTOOLS_STATIC_CHECK(( meta::fixed_ndarray_dim_v<arg_t> == 3 ));
    }
    {
        using arg_t = double[3][2];
        NMTOOLS_STATIC_CHECK(( meta::fixed_ndarray_dim_v<arg_t> == 2 ));
    }
    {
        using arg_t = double[3];
        NMTOOLS_STATIC_CHECK(( meta::fixed_ndarray_dim_v<arg_t> == 1 ));
    }
    {
        using arg_t = double;
        using result_t = meta::fixed_ndarray_dim<arg_t>;
        STATIC_CHECK_IS_SAME( typename result_t::value_type, void );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2,3,4,5>;
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 4 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2,3,4>;
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 3 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2,3>;
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 2 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2>;
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 1 );
    }
    {
        using arg_t = nmtools_array<nmtools_array<nmtools_array<nmtools_array<nmtools_array<double,5>,4>,3>,2>,1>;
        CHECK( meta::fixed_ndarray_dim_v<arg_t> == 5 );
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 5 );
    }
    {
        using arg_t = nmtools_array<nmtools_array<nmtools_array<nmtools_array<double,4>,3>,2>,1>;
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 4 );
    }
    {
        using arg_t = nmtools_array<nmtools_array<nmtools_array<double,3>,2>,1>;
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 3 );
    }
    {
        using arg_t = nmtools_array<nmtools_array<double,2>,1>;
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 2 );
    }
    {
        using arg_t = nmtools_array<double,1>;
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 1 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,5,4,3,2,1>;
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 5 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,5,4,3,2>;
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 4 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,5,4,3>;
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 3 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,5,4>;
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 2 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,5>;
        NMTOOLS_STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 1 );
    }
}

TEST_CASE("fixed_ndarray_shape_v" * doctest::test_suite("array"))
{
    // using vector_t   = nmtools_array<double,3>;
    using array_t    = nmtools_array<nmtools_array<double,3>,5>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    using ndarray3_t = nmtools::array::fixed_ndarray<double,5,3,1>;
    // using dndarray_t = nmtools::array::dynamic_ndarray<double>;

    {
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<array_t>;
        NMTOOLS_STATIC_CHECK(( nm::get<0>(shape)==5 ));
        NMTOOLS_STATIC_CHECK(( nm::get<1>(shape)==3 ));
    }
    {
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<ndarray_t>;
        NMTOOLS_STATIC_CHECK(( nm::get<0>(shape)==5 ));
        NMTOOLS_STATIC_CHECK(( nm::get<1>(shape)==3 ));
    }
    {
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<ndarray3_t>;
        NMTOOLS_STATIC_CHECK(( nm::get<0>(shape)==5 ));
        NMTOOLS_STATIC_CHECK(( nm::get<1>(shape)==3 ));
        NMTOOLS_STATIC_CHECK(( nm::get<2>(shape)==1 ));
    }
}

TEST_CASE("is_ndarray_v" * doctest::test_suite("array"))
{
    using vvector_t = nmtools_list<double>;
    using varray_t  = nmtools_array<double,3>;
    using mvector_t = nmtools_list<double>;
    using marray_t  = nmtools_array<nmtools_array<double,3>,2>;
    using ftensor_t = nmtools::array::fixed_ndarray<double,2,3,4>;
    using dtensor_t = nmtools::array::dynamic_ndarray<double>;

    {
        using arg_t = vvector_t;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = mvector_t;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = varray_t;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = marray_t;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = ftensor_t;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = dtensor_t;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3][1][2][4][5];
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3][1][2][4];
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3][1][2];
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3][1];
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3];
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double;
        NMTOOLS_STATIC_CHECK(( !meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_array<nmtools_array<nmtools_array<nmtools_array<nmtools_array<double,5>,4>,3>,2>,1>;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_array<nmtools_array<nmtools_array<nmtools_array<double,4>,3>,2>,1>;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_array<nmtools_array<nmtools_array<double,3>,2>,1>;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_array<nmtools_array<double,2>,1>;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_array<double,1>;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    // TODO: remove support for nested vector
    #if 0
    {
        using arg_t = nmtools_list<nmtools_list<nmtools_list<double>>>;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_list<nmtools_list<double>>;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    #endif
    {
        using arg_t = nmtools_list<double>;
        NMTOOLS_STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools_tuple<double,int>;
        NMTOOLS_STATIC_CHECK( !meta::is_ndarray_v<arg_t> );
    }
}

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("array"))
{
    {
        using arg_t = double;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, arg_t );
    }
    {
        using arg_t = double[1];
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, arg_t );
    }
    {
        using arg_t = double[1][1];
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, arg_t );
    }
    {
        using arg_t = double[1][1][1];
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, arg_t );
    }
    {
        using arg_t = double[1][1][1][1];
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, arg_t );
    }
    {
        using arg_t = nmtools_array<double,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, arg_t );
    }
    {
        using arg_t = nmtools_array<nmtools_array<double,3>,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, arg_t );
    }
    {
        using arg_t = nmtools_array<nmtools_array<nmtools_array<double,1>,3>,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, arg_t );
    }
    {
        using arg_t = nmtools_list<double>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, arg_t );
    }
    // TODO: remove nested vector support
    #if 0
    {
        using arg_t = nmtools_list<nmtools_list<double>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, arg_t );
    }
    {
        using arg_t = nmtools_list<nmtools_list<nmtools_list<double>>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, arg_t );
    }
    #endif
}

TEST_CASE("fixed_dim" * doctest::test_suite("array"))
{
    {
        using arg_t = double[1];
        NMTOOLS_STATIC_CHECK( meta::fixed_dim_v<arg_t> == 1 );
    }
    {
        using arg_t = double[1][1];
        NMTOOLS_STATIC_CHECK( meta::fixed_dim_v<arg_t> == 2 );
    }
    {
        using arg_t = double[1][1][1];
        NMTOOLS_STATIC_CHECK( meta::fixed_dim_v<arg_t> == 3 );
    }
    {
        using arg_t = nmtools_array<double,2>;
        NMTOOLS_STATIC_CHECK( meta::fixed_dim_v<arg_t> == 1);
    }
    {
        using arg_t = nmtools_array<nmtools_array<double,3>,2>;
        NMTOOLS_STATIC_CHECK( meta::fixed_dim_v<arg_t> == 2);
    }
    {
        using arg_t = nmtools_array<nmtools_array<nmtools_array<double,1>,3>,2>;
        NMTOOLS_STATIC_CHECK( meta::fixed_dim_v<arg_t> == 3);
    }
    {
        using arg_t = nmtools_list<double>;
        NMTOOLS_STATIC_CHECK( meta::fixed_dim_v<arg_t> == 1);
    }
    // TODO: disable nested array
    #if 0
    {
        using arg_t = nmtools_list<nmtools_list<double>>;
        NMTOOLS_STATIC_CHECK( meta::fixed_dim_v<arg_t> == 2);
    }
    {
        using arg_t = nmtools_list<nmtools_list<nmtools_list<double>>>;
        NMTOOLS_STATIC_CHECK( meta::fixed_dim_v<arg_t> == 3);
    }
    #endif
    {
        using arg_t = nm::array::fixed_ndarray<double,1>;
        NMTOOLS_STATIC_CHECK( meta::fixed_dim_v<arg_t> == 1);
    }
    {
        using arg_t = nm::array::fixed_ndarray<double,1,2>;
        NMTOOLS_STATIC_CHECK( meta::fixed_dim_v<arg_t> == 2);
    }
    {
        using arg_t = nm::array::fixed_ndarray<double,2,3,1>;
        NMTOOLS_STATIC_CHECK( meta::fixed_dim_v<arg_t> == 3);
    }
}

TEST_CASE("is_array1d_v" * doctest::test_suite("array"))
{
    {
        using arg_t = std::initializer_list<double>;
        NMTOOLS_STATIC_CHECK( !meta::is_array1d_v<arg_t> );
    }
}