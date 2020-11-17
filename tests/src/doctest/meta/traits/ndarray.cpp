/**
 * @file ndarray.cpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief Test file for ndarray traits
 * @date 2020-11-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
// NOTE: need to include utility for std::array fixed_size specialization
#include "nmtools/array/utility.hpp"
#include "testing/testing.hpp"

#include "doctest/doctest.h"
#include <boost/type_index.hpp>
#include <array>

namespace nm   = nmtools;
namespace meta = nmtools::meta;

TEST_CASE("is_fixed_size_ndarray_v" * doctest::test_suite("array"))
{
    {
        using arg_t = double[3][2][4][5];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3][2][4];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3][2];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( !meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2,3,4,5>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2,3,4>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2,3>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = nmtools::array::dynamic_ndarray<double>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( !meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::array<std::array<std::array<std::array<std::array<double,5>,4>,3>,2>,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::array<std::array<std::array<std::array<double,4>,3>,2>,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::array<std::array<std::array<double,3>,2>,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::array<std::array<double,2>,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::array<double,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::vector<std::vector<std::vector<double>>>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( !meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::vector<std::vector<double>>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( !meta::is_fixed_size_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::vector<double>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( !meta::is_fixed_size_ndarray_v<arg_t> ));
    }
}

TEST_CASE("fixed_ndarray_dim_v" * doctest::test_suite("array"))
{
    {
        using arg_t = double[3][2][4][5];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::fixed_ndarray_dim_v<arg_t> == 4 ));
    }
    {
        using arg_t = double[3][2][4];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::fixed_ndarray_dim_v<arg_t> == 3 ));
    }
    {
        using arg_t = double[3][2];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::fixed_ndarray_dim_v<arg_t> == 2 ));
    }
    {
        using arg_t = double[3];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::fixed_ndarray_dim_v<arg_t> == 1 ));
    }
    {
        using arg_t = double;
        using result_t = meta::fixed_ndarray_dim<arg_t>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK_IS_SAME( typename result_t::value_type, void );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2,3,4,5>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 4 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2,3,4>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 3 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2,3>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 2 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,2>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 1 );
    }
    {
        using arg_t = std::array<std::array<std::array<std::array<std::array<double,5>,4>,3>,2>,1>;
        LOG_TYPEINFO(arg_t);
        CHECK( meta::fixed_ndarray_dim_v<arg_t> == 5 );
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 5 );
    }
    {
        using arg_t = std::array<std::array<std::array<std::array<double,4>,3>,2>,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 4 );
    }
    {
        using arg_t = std::array<std::array<std::array<double,3>,2>,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 3 );
    }
    {
        using arg_t = std::array<std::array<double,2>,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 2 );
    }
    {
        using arg_t = std::array<double,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 1 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,5,4,3,2,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 5 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,5,4,3,2>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 4 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,5,4,3>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 3 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,5,4>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 2 );
    }
    {
        using arg_t = nmtools::array::fixed_ndarray<double,5>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_ndarray_dim_v<arg_t> == 1 );
    }
}

TEST_CASE("fixed_ndarray_shape_v" * doctest::test_suite("array"))
{
    using vector_t   = std::array<double,3>;
    using array_t    = std::array<std::array<double,3>,5>;
    using fvector_t  = nmtools::array::fixed_vector<double,3>;
    using fmatrix_t  = nmtools::array::fixed_matrix<double,5,3>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    using ndarray3_t = nmtools::array::fixed_ndarray<double,5,3,1>;
    using dndarray_t = nmtools::array::dynamic_ndarray<double>;
    LOG_TYPEINFO(array_t);
    LOG_TYPEINFO(vector_t);
    LOG_TYPEINFO(fvector_t);
    LOG_TYPEINFO(fmatrix_t);
    LOG_TYPEINFO(ndarray_t);
    LOG_TYPEINFO(dndarray_t);
    LOG_TYPEINFO(ndarray3_t);

    {
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<fvector_t>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
    }
    {
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<array_t>;
        STATIC_CHECK(( std::get<0>(shape)==5 ));
        STATIC_CHECK(( std::get<1>(shape)==3 ));
    }
    {
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<fmatrix_t>;
        STATIC_CHECK(( std::get<0>(shape)==5 ));
        STATIC_CHECK(( std::get<1>(shape)==3 ));
    }
    {
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<ndarray_t>;
        STATIC_CHECK(( std::get<0>(shape)==5 ));
        STATIC_CHECK(( std::get<1>(shape)==3 ));
    }
    {
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<ndarray3_t>;
        STATIC_CHECK(( std::get<0>(shape)==5 ));
        STATIC_CHECK(( std::get<1>(shape)==3 ));
        STATIC_CHECK(( std::get<2>(shape)==1 ));
    }
}

TEST_CASE("is_ndarray_v" * doctest::test_suite("array"))
{
    using vvector_t = std::vector<double>;
    using varray_t  = std::array<double,3>;
    using fvector_t = nmtools::array::fixed_vector<double,3>;
    using dvector_t = nmtools::array::dynamic_vector<double>;
    using mvector_t = std::vector<double>;
    using marray_t  = std::array<std::array<double,3>,2>;
    using fmatrix_t = nmtools::array::fixed_matrix<double,2,3>;
    using dmatrix_t = nmtools::array::dynamic_matrix<double>;
    using ftensor_t = nmtools::array::fixed_ndarray<double,2,3,4>;
    using dtensor_t = nmtools::array::dynamic_ndarray<double>;

    {
        using arg_t = vvector_t;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = mvector_t;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = varray_t;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = marray_t;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = fvector_t;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = fmatrix_t;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = dvector_t;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = dmatrix_t;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = ftensor_t;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = dtensor_t;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3][1][2][4][5];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3][1][2][4];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3][1][2];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3][1];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[3];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( !meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::array<std::array<std::array<std::array<std::array<double,5>,4>,3>,2>,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::array<std::array<std::array<std::array<double,4>,3>,2>,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::array<std::array<std::array<double,3>,2>,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::array<std::array<double,2>,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::array<double,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::vector<std::vector<std::vector<double>>>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::vector<std::vector<double>>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::vector<double>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::tuple<double,int>;
        LOG_TYPEINFO( arg_t );
        STATIC_CHECK( !meta::is_ndarray_v<arg_t> );
    }
}

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("array"))
{
    {
        using arg_t = double;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( !meta::is_fixed_dim_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[1];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_dim_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[1][1];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_dim_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[1][1][1];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_dim_ndarray_v<arg_t> ));
    }
    {
        using arg_t = double[1][1][1][1];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_dim_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::array<double,2>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_dim_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::array<std::array<double,3>,2>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_dim_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::array<std::array<std::array<double,1>,3>,2>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_dim_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::vector<double>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_dim_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::vector<std::vector<double>>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_dim_ndarray_v<arg_t> ));
    }
    {
        using arg_t = std::vector<std::vector<std::vector<double>>>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(( meta::is_fixed_dim_ndarray_v<arg_t> ));
    }
}

TEST_CASE("fixed_dim" * doctest::test_suite("array"))
{
    {
        using arg_t = double[1];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_dim_v<arg_t> == 1 );
    }
    {
        using arg_t = double[1][1];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_dim_v<arg_t> == 2 );
    }
    {
        using arg_t = double[1][1][1];
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_dim_v<arg_t> == 3 );
    }
    {
        using arg_t = std::array<double,2>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_dim_v<arg_t> == 1);
    }
    {
        using arg_t = std::array<std::array<double,3>,2>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_dim_v<arg_t> == 2);
    }
    {
        using arg_t = std::array<std::array<std::array<double,1>,3>,2>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_dim_v<arg_t> == 3);
    }
    {
        using arg_t = std::vector<double>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_dim_v<arg_t> == 1);
    }
    {
        using arg_t = std::vector<std::vector<double>>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_dim_v<arg_t> == 2);
    }
    {
        using arg_t = std::vector<std::vector<std::vector<double>>>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_dim_v<arg_t> == 3);
    }
    {
        using arg_t = nm::array::fixed_ndarray<double,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_dim_v<arg_t> == 1);
    }
    {
        using arg_t = nm::array::fixed_ndarray<double,1,2>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_dim_v<arg_t> == 2);
    }
    {
        using arg_t = nm::array::fixed_ndarray<double,2,3,1>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK( meta::fixed_dim_v<arg_t> == 3);
    }
}