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

using meta::merge_t;
using meta::pop_first_t;
using meta::pop_last_t;

TEST_CASE("meta" * doctest::skip(true))
{
    // merge test
    STATIC_CHECK(( std::is_same_v<merge_t<std::tuple<int,char>,std::tuple<double>>, std::tuple<int,char,double>> ));
    STATIC_CHECK(( std::is_same_v<merge_t<std::tuple<int,char>,double>, std::tuple<int,char,double>> ));
    STATIC_CHECK(( std::is_same_v<merge_t<int,std::tuple<char,double>>, std::tuple<int,char,double>> ));

    // pop_first test
    STATIC_CHECK(( std::is_same_v<pop_first_t<std::tuple<int,char>>,std::tuple<char>> ));
    STATIC_CHECK(( std::is_same_v<pop_first_t<std::tuple<int,char,double>>,std::tuple<char,double>> ));

    // pop_last test
    STATIC_CHECK(( std::is_same_v<pop_last_t<std::tuple<int,char>>,std::tuple<int>> ));
    STATIC_CHECK(( std::is_same_v<pop_last_t<std::tuple<int,char,double>>,std::tuple<int,char>> ));
}

TEST_CASE("meta" * doctest::skip(true))
{
    using vvector_t   = std::vector<double>;
    using marray_t    = std::array<std::array<double,3>,5>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    using ndarray3_t = nmtools::array::fixed_ndarray<double,5,3,1>;
    using dndarray_t = nmtools::array::dynamic_ndarray<double>;

    LOG_TYPEINFO(marray_t);
    LOG_TYPEINFO(vvector_t);
    LOG_TYPEINFO(ndarray_t);
    LOG_TYPEINFO(dndarray_t);
    LOG_TYPEINFO(ndarray3_t);

    STATIC_CHECK((  meta::is_resizeable_v<vvector_t> ));
}