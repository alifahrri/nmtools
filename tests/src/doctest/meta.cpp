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

namespace meta = nmtools::meta;
namespace traits = nmtools::traits;

/**
 * @test compile-time tests
 * @note that meta::get_element_type call/use the following traits/metafunctions:
 * - nmtools::traits::is_array1d_v
 * - nmtools::traits::is_array2d_v
 * - nmtools::meta::get_matrix_value_type_t
 * - nmtools::meta::get_vector_value_type_t
 * 
 */
TEST_CASE("meta" * doctest::skip(true))
{
    using array_t = std::array<std::array<double,5>,2>;
    using value_t = meta::get_matrix_value_type_t<array_t>;
    using element_t = meta::get_element_type_t<array_t>;
    LOG_TYPEINFO(array_t);
    LOG_TYPEINFO(value_t);
    LOG_TYPEINFO(element_t);
    // @note that nmtools::traits::is_array1d_v and nmtools::traits::is_array2d_v may not mutually exclusive!
    // STATIC_CHECK((!traits::is_array1d_v<array_t>));
    STATIC_CHECK(( traits::is_array2d_v<array_t> ));
    STATIC_CHECK(( std::is_same_v<value_t,double> ));
    STATIC_CHECK(( std::is_same_v<element_t,double> ));
}

TEST_CASE("traits" * doctest::skip(true))
{
    // @note since fail on static assert means compilation error,
    // just skip runtime test by default since it will only success
    using array_t = std::array<std::array<double,5>,2>;
    LOG_TYPEINFO(array_t);
    STATIC_CHECK(( traits::is_fixed_size_matrix_v<array_t> ));
}

TEST_CASE("traits" * doctest::skip(true)) // has_atnd
{
    using vector_t   = std::array<double,3>;
    using array_t    = std::array<std::array<double,5>,2>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    using dndarray_t = nmtools::array::dynamic_ndarray<double>;
    LOG_TYPEINFO(array_t);
    LOG_TYPEINFO(vector_t);
    LOG_TYPEINFO(dndarray_t);
    STATIC_CHECK(( !traits::has_atnd_v<array_t,size_t,size_t> ));
    STATIC_CHECK(( !traits::has_atnd_v<vector_t,size_t,size_t> ));
    STATIC_CHECK(( traits::has_atnd_v<vector_t,size_t> ));
    STATIC_CHECK(( traits::has_atnd_v<array_t,size_t> ));
}

TEST_CASE("traits" * doctest::skip(true)) // is_ndarray
{
    using vector_t   = std::array<double,3>;
    using array_t    = std::array<std::array<double,5>,3>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    using dndarray_t = nmtools::array::dynamic_ndarray<double>;
    LOG_TYPEINFO(array_t);
    LOG_TYPEINFO(vector_t);
    LOG_TYPEINFO(ndarray_t);
    LOG_TYPEINFO(dndarray_t);
    STATIC_CHECK(( !traits::is_ndarray_v<vector_t> ));
    STATIC_CHECK(( !traits::is_ndarray_v<array_t> ));
    STATIC_CHECK(( traits::is_ndarray_v<ndarray_t> ));
    STATIC_CHECK(( traits::is_ndarray_v<dndarray_t> ));
}

TEST_CASE("meta" * doctest::skip(true)) // get_ndarray_value_type
{
    using vector_t   = std::array<double,3>;
    using array_t    = std::array<std::array<double,5>,3>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    using dndarray_t = nmtools::array::dynamic_ndarray<double>;
    LOG_TYPEINFO(array_t);
    LOG_TYPEINFO(vector_t);
    LOG_TYPEINFO(ndarray_t);
    LOG_TYPEINFO(dndarray_t);
    STATIC_CHECK(( std::is_same_v<meta::get_ndarray_value_type_t<array_t>,void> ));
    STATIC_CHECK(( std::is_same_v<meta::get_ndarray_value_type_t<vector_t>,void> ));
    STATIC_CHECK(( std::is_same_v<meta::get_ndarray_value_type_t<ndarray_t>,double> ));
    STATIC_CHECK(( std::is_same_v<meta::get_ndarray_value_type_t<dndarray_t>,double> ));
}

TEST_CASE("traits" * doctest::skip(true)) // has_funcnd
{
    using vector_t   = std::array<double,3>;
    using array_t    = std::array<std::array<double,5>,2>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    using ndarray3_t = nmtools::array::fixed_ndarray<double,5,3,1>;
    using dndarray_t = nmtools::array::dynamic_ndarray<double>;
    LOG_TYPEINFO(array_t);
    LOG_TYPEINFO(vector_t);
    LOG_TYPEINFO(ndarray_t);
    LOG_TYPEINFO(dndarray_t);
    LOG_TYPEINFO(ndarray3_t);

    STATIC_CHECK(( !traits::has_funcnd_v<array_t,size_t> ));
    STATIC_CHECK(( !traits::has_funcnd_v<array_t,size_t,size_t> ));

    STATIC_CHECK(( !traits::has_funcnd_v<vector_t,size_t> ));
    STATIC_CHECK(( !traits::has_funcnd_v<vector_t,size_t,size_t> ));

    STATIC_CHECK(( !traits::has_funcnd_v<ndarray_t,size_t> ));
    STATIC_CHECK((  traits::has_funcnd_v<ndarray_t,size_t,size_t> ));
    STATIC_CHECK(( !traits::has_funcnd_v<ndarray_t,size_t,size_t,size_t> ));

    STATIC_CHECK(( !traits::has_funcnd_v<ndarray3_t,size_t> ));
    STATIC_CHECK(( !traits::has_funcnd_v<ndarray3_t,size_t,size_t> ));
    STATIC_CHECK((  traits::has_funcnd_v<ndarray3_t,size_t,size_t,size_t> ));

    // @note dynamic_ndarray has shape only known at runtime so all of has_funcnd_v returns true
    STATIC_CHECK(( traits::has_funcnd_v<dndarray_t,size_t,size_t,size_t> ));
    STATIC_CHECK(( traits::has_funcnd_v<dndarray_t,size_t,size_t> ));
    STATIC_CHECK(( traits::has_funcnd_v<dndarray_t,size_t> ));
}

TEST_CASE("traits" * doctest::skip(true)) // has_bracketnd
{
    using vector_t   = std::array<double,3>;
    using array_t    = std::array<std::array<double,5>,2>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    using ndarray3_t = nmtools::array::fixed_ndarray<double,5,3,1>;
    using dndarray_t = nmtools::array::dynamic_ndarray<double>;
    LOG_TYPEINFO(array_t);
    LOG_TYPEINFO(vector_t);
    LOG_TYPEINFO(ndarray_t);
    LOG_TYPEINFO(dndarray_t);
    LOG_TYPEINFO(ndarray3_t);

    STATIC_CHECK((  traits::has_bracketnd_v<array_t,size_t> ));
    STATIC_CHECK(( !traits::has_bracketnd_v<array_t,size_t,size_t> ));

    STATIC_CHECK((  traits::has_bracketnd_v<vector_t,size_t> ));
    STATIC_CHECK(( !traits::has_bracketnd_v<vector_t,size_t,size_t> ));

    STATIC_CHECK(( !traits::has_bracketnd_v<ndarray3_t,size_t> ));
    STATIC_CHECK(( !traits::has_bracketnd_v<ndarray3_t,size_t,size_t> ));
    STATIC_CHECK(( !traits::has_bracketnd_v<ndarray3_t,size_t,size_t,size_t> ));

    STATIC_CHECK(( !traits::has_bracketnd_v<ndarray_t,size_t> ));
    STATIC_CHECK(( !traits::has_bracketnd_v<ndarray_t,size_t,size_t> ));
    STATIC_CHECK(( !traits::has_bracketnd_v<ndarray_t,size_t,size_t,size_t> ));

    STATIC_CHECK(( !traits::has_bracketnd_v<dndarray_t,size_t,size_t,size_t> ));
    STATIC_CHECK(( !traits::has_bracketnd_v<dndarray_t,size_t,size_t> ));
    STATIC_CHECK(( !traits::has_bracketnd_v<dndarray_t,size_t> ));
}

TEST_CASE("meta" * doctest::skip(true)) // fixed_array_shape
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
        constexpr auto shape = nmtools::fixed_array_shape_v<fvector_t>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
    }
    {
        constexpr auto shape = nmtools::fixed_array_shape_v<array_t>;
        STATIC_CHECK(( std::get<0>(shape)==5 ));
        STATIC_CHECK(( std::get<1>(shape)==3 ));
    }
    {
        constexpr auto shape = nmtools::fixed_array_shape_v<fmatrix_t>;
        STATIC_CHECK(( std::get<0>(shape)==5 ));
        STATIC_CHECK(( std::get<1>(shape)==3 ));
    }
    {
        constexpr auto shape = nmtools::fixed_array_shape_v<ndarray_t>;
        STATIC_CHECK(( std::get<0>(shape)==5 ));
        STATIC_CHECK(( std::get<1>(shape)==3 ));
    }
    {
        constexpr auto shape = nmtools::fixed_array_shape_v<ndarray3_t>;
        STATIC_CHECK(( std::get<0>(shape)==5 ));
        STATIC_CHECK(( std::get<1>(shape)==3 ));
        STATIC_CHECK(( std::get<2>(shape)==1 ));
    }
}

TEST_CASE("meta" * doctest::skip(true)) // fixed_matrix_size
{
    using fmatrix_t  = nmtools::array::fixed_matrix<double,5,3>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    LOG_TYPEINFO(fmatrix_t);
    LOG_TYPEINFO(ndarray_t);

    {
        constexpr auto shape = nmtools::fixed_matrix_size_v<fmatrix_t>;
        STATIC_CHECK(( std::get<0>(shape)==5 ));
        STATIC_CHECK(( std::get<1>(shape)==3 ));
    }
    {
        constexpr auto shape = nmtools::fixed_matrix_size_v<ndarray_t>;
        STATIC_CHECK(( std::get<0>(shape)==5 ));
        STATIC_CHECK(( std::get<1>(shape)==3 ));
    }
}

TEST_CASE("meta" * doctest::skip(true)) // fixed_vector_size
{
    using fvector_t  = nmtools::array::fixed_vector<double,5>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5>;
    LOG_TYPEINFO(fvector_t);
    LOG_TYPEINFO(ndarray_t);

    {
        constexpr auto shape = nmtools::fixed_vector_size_v<fvector_t>;
        STATIC_CHECK(( shape==5 ));
    }
    {
        constexpr auto shape = nmtools::fixed_vector_size_v<ndarray_t>;
        STATIC_CHECK(( shape==5 ));
    }
}

TEST_CASE("traits" * doctest::skip(true)) // type_list_disjunction
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
        using type_list_t = std::tuple<array_t,fmatrix_t>;
        LOG_TYPEINFO(type_list_t);
        // any type in type_list_t satisfy is_array2d
        STATIC_CHECK(( traits::type_list_disjunction_v<type_list_t,traits::is_array2d> ));   
    }
    {
        using type_list_t = std::tuple<array_t,fvector_t>;
        LOG_TYPEINFO(type_list_t);
        // any type in type_list_t satisfy is_array2d
        STATIC_CHECK(( traits::type_list_disjunction_v<type_list_t,traits::is_array2d> ));   
    }
    {
        using type_list_t = std::tuple<ndarray_t,ndarray3_t,dndarray_t>;
        LOG_TYPEINFO(type_list_t);
        // any type in type_list_t satisfy is_ndarray
        STATIC_CHECK(( traits::type_list_disjunction_v<type_list_t,traits::is_ndarray> ));   
    }
}

TEST_CASE("traits" * doctest::skip(true)) // type_list_conjunction
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
        using type_list_t = std::tuple<array_t,fmatrix_t>;
        LOG_TYPEINFO(type_list_t);
        // all type in type_list_t satisfy is_array2d
        STATIC_CHECK(( traits::type_list_conjunction_v<type_list_t,traits::is_array2d> ));   
    }
    {
        using type_list_t = std::tuple<array_t,fvector_t>;
        LOG_TYPEINFO(type_list_t);
        // all type in type_list_t satisfy is_array2d
        STATIC_CHECK(( !traits::type_list_conjunction_v<type_list_t,traits::is_array2d> ));   
    }
    {
        using type_list_t = std::tuple<ndarray_t,ndarray3_t,dndarray_t>;
        LOG_TYPEINFO(type_list_t);
        // all type in type_list_t satisfy is_ndarray
        STATIC_CHECK(( traits::type_list_conjunction_v<type_list_t,traits::is_ndarray> ));   
    }
    {
        using type_list_t = std::tuple<ndarray_t,ndarray3_t,dndarray_t>;
        LOG_TYPEINFO(type_list_t);
        // all type in type_list_t satisfy is_array2d
        STATIC_CHECK(( !traits::type_list_conjunction_v<type_list_t,traits::is_array2d> ));   
    }
}

using meta::type_merge_t;
using meta::type_push_back_t;
using meta::pop_first_t;
using meta::pop_last_t;
using meta::type_reverse_t;
using meta::make_reversed_index_sequence;

TEST_CASE("meta" * doctest::skip(true))
{
    // type_merge test
    STATIC_CHECK(( std::is_same_v<type_merge_t<std::tuple<int,char>,std::tuple<double>>, std::tuple<int,char,double>> ));
    STATIC_CHECK(( std::is_same_v<type_merge_t<std::tuple<int,char>,double>, std::tuple<int,char,double>> ));
    STATIC_CHECK(( std::is_same_v<type_merge_t<int,std::tuple<char,double>>, std::tuple<int,char,double>> ));

    // type_push_back test
    STATIC_CHECK(( std::is_same_v<type_push_back_t<std::tuple<int,char>,double>, std::tuple<int,char,double>> ));

    // pop_first test
    STATIC_CHECK(( std::is_same_v<pop_first_t<std::tuple<int,char>>,std::tuple<char>> ));
    STATIC_CHECK(( std::is_same_v<pop_first_t<std::tuple<int,char,double>>,std::tuple<char,double>> ));

    // pop_last test
    STATIC_CHECK(( std::is_same_v<pop_last_t<std::tuple<int,char>>,std::tuple<int>> ));
    STATIC_CHECK(( std::is_same_v<pop_last_t<std::tuple<int,char,double>>,std::tuple<int,char>> ));

    // type_reverse test
    STATIC_CHECK(( std::is_same_v<type_reverse_t<std::tuple<int,char,double>>,std::tuple<double,char,int>> ));

    // make_reversed_index_sequence test
    STATIC_CHECK(( std::is_same_v<make_reversed_index_sequence<3>,std::index_sequence<2,1,0>> ));
}

TEST_CASE("meta" * doctest::skip(true))
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

    STATIC_CHECK(( traits::is_fixed_size_array_v<array_t> ));
}

TEST_CASE("meta" * doctest::skip(true))
{
    using vvector_t   = std::vector<double>;
    using marray_t    = std::array<std::array<double,3>,5>;
    using fvector_t  = nmtools::array::fixed_vector<double,3>;
    using fmatrix_t  = nmtools::array::fixed_matrix<double,5,3>;
    using dvector_t  = nmtools::array::dynamic_vector<double>;
    using dmatrix_t  = nmtools::array::dynamic_matrix<double>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    using ndarray3_t = nmtools::array::fixed_ndarray<double,5,3,1>;
    using dndarray_t = nmtools::array::dynamic_ndarray<double>;

    LOG_TYPEINFO(marray_t);
    LOG_TYPEINFO(vvector_t);
    LOG_TYPEINFO(fvector_t);
    LOG_TYPEINFO(fmatrix_t);
    LOG_TYPEINFO(ndarray_t);
    LOG_TYPEINFO(dndarray_t);
    LOG_TYPEINFO(ndarray3_t);

    STATIC_CHECK((  traits::is_resizeable_v<vvector_t> ));
    STATIC_CHECK(( !traits::is_resizeable_v<fmatrix_t> ));
    // STATIC_CHECK((  traits::is_resizeable_v<dmatrix_t> ));
    STATIC_CHECK((  traits::is_resizeable_nd_v<dmatrix_t,size_t,size_t> ));
}