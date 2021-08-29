#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
// NOTE: need to include utility for std::array fixed_size specialization
#include "nmtools/array/utility.hpp"
#include "testing/testing.hpp"

#if __has_include("doctest/doctest.h")
    #include "doctest/doctest.h"
#else
   #include "doctest.h"
#endif
#include <array>

namespace meta = nmtools::meta;
namespace meta = nmtools::meta;

TEST_CASE("traits" * doctest::skip(true))
{
    // @note since fail on static assert means compilation error,
    // just skip runtime test by default since it will only success
    using array_t = std::array<std::array<double,5>,2>;
    LOG_TYPEINFO(array_t);
    STATIC_CHECK(( meta::is_fixed_size_matrix_v<array_t> ));
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
    STATIC_CHECK(( !meta::has_atnd_v<array_t,size_t,size_t> ));
    STATIC_CHECK(( !meta::has_atnd_v<vector_t,size_t,size_t> ));
    STATIC_CHECK(( meta::has_atnd_v<vector_t,size_t> ));
    STATIC_CHECK(( meta::has_atnd_v<array_t,size_t> ));
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

    STATIC_CHECK(( !meta::has_funcnd_v<array_t,size_t> ));
    STATIC_CHECK(( !meta::has_funcnd_v<array_t,size_t,size_t> ));

    STATIC_CHECK(( !meta::has_funcnd_v<vector_t,size_t> ));
    STATIC_CHECK(( !meta::has_funcnd_v<vector_t,size_t,size_t> ));

    STATIC_CHECK(( !meta::has_funcnd_v<ndarray_t,size_t> ));
    STATIC_CHECK((  meta::has_funcnd_v<ndarray_t,size_t,size_t> ));
    STATIC_CHECK(( !meta::has_funcnd_v<ndarray_t,size_t,size_t,size_t> ));

    STATIC_CHECK(( !meta::has_funcnd_v<ndarray3_t,size_t> ));
    STATIC_CHECK(( !meta::has_funcnd_v<ndarray3_t,size_t,size_t> ));
    STATIC_CHECK((  meta::has_funcnd_v<ndarray3_t,size_t,size_t,size_t> ));

    // @note dynamic_ndarray has shape only known at runtime so all of has_funcnd_v returns true
    STATIC_CHECK(( meta::has_funcnd_v<dndarray_t,size_t,size_t,size_t> ));
    STATIC_CHECK(( meta::has_funcnd_v<dndarray_t,size_t,size_t> ));
    STATIC_CHECK(( meta::has_funcnd_v<dndarray_t,size_t> ));
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

    STATIC_CHECK((  meta::has_bracketnd_v<array_t,size_t> ));
    STATIC_CHECK(( !meta::has_bracketnd_v<array_t,size_t,size_t> ));

    STATIC_CHECK((  meta::has_bracketnd_v<vector_t,size_t> ));
    STATIC_CHECK(( !meta::has_bracketnd_v<vector_t,size_t,size_t> ));

    STATIC_CHECK(( !meta::has_bracketnd_v<ndarray3_t,size_t> ));
    STATIC_CHECK(( !meta::has_bracketnd_v<ndarray3_t,size_t,size_t> ));
    STATIC_CHECK(( !meta::has_bracketnd_v<ndarray3_t,size_t,size_t,size_t> ));

    STATIC_CHECK(( !meta::has_bracketnd_v<ndarray_t,size_t> ));
    STATIC_CHECK(( !meta::has_bracketnd_v<ndarray_t,size_t,size_t> ));
    STATIC_CHECK(( !meta::has_bracketnd_v<ndarray_t,size_t,size_t,size_t> ));

    STATIC_CHECK(( !meta::has_bracketnd_v<dndarray_t,size_t,size_t,size_t> ));
    STATIC_CHECK(( !meta::has_bracketnd_v<dndarray_t,size_t,size_t> ));
    STATIC_CHECK(( !meta::has_bracketnd_v<dndarray_t,size_t> ));
}

TEST_CASE("meta" * doctest::skip(true)) // meta::fixed_matrix_size
{
    using fmatrix_t  = nmtools::array::fixed_matrix<double,5,3>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    LOG_TYPEINFO(fmatrix_t);
    LOG_TYPEINFO(ndarray_t);

    {
        constexpr auto shape = nmtools::meta::fixed_matrix_size_v<fmatrix_t>;
        STATIC_CHECK(( std::get<0>(shape)==5 ));
        STATIC_CHECK(( std::get<1>(shape)==3 ));
    }
    {
        constexpr auto shape = nmtools::meta::fixed_matrix_size_v<ndarray_t>;
        STATIC_CHECK(( std::get<0>(shape)==5 ));
        STATIC_CHECK(( std::get<1>(shape)==3 ));
    }
}

using meta::merge_t;
using meta::type_push_back_t;
using meta::pop_first_t;
using meta::pop_last_t;
using meta::type_reverse_t;
using meta::make_reversed_index_sequence;

TEST_CASE("meta" * doctest::skip(true))
{
    // merge test
    STATIC_CHECK(( std::is_same_v<merge_t<std::tuple<int,char>,std::tuple<double>>, std::tuple<int,char,double>> ));
    STATIC_CHECK(( std::is_same_v<merge_t<std::tuple<int,char>,double>, std::tuple<int,char,double>> ));
    STATIC_CHECK(( std::is_same_v<merge_t<int,std::tuple<char,double>>, std::tuple<int,char,double>> ));

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
    using vvector_t   = std::vector<double>;
    using marray_t    = std::array<std::array<double,3>,5>;
    using fmatrix_t  = nmtools::array::fixed_matrix<double,5,3>;
    using dmatrix_t  = nmtools::array::dynamic_matrix<double>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    using ndarray3_t = nmtools::array::fixed_ndarray<double,5,3,1>;
    using dndarray_t = nmtools::array::dynamic_ndarray<double>;

    LOG_TYPEINFO(marray_t);
    LOG_TYPEINFO(vvector_t);
    LOG_TYPEINFO(fmatrix_t);
    LOG_TYPEINFO(ndarray_t);
    LOG_TYPEINFO(dndarray_t);
    LOG_TYPEINFO(ndarray3_t);

    STATIC_CHECK((  meta::is_resizeable_v<vvector_t> ));
    STATIC_CHECK(( !meta::is_resizeable_v<fmatrix_t> ));
    // STATIC_CHECK((  meta::is_resizeable_v<dmatrix_t> ));
    STATIC_CHECK((  meta::is_resizeable_nd_v<dmatrix_t,size_t,size_t> ));
}