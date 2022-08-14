#include "nmtools/utility/flatten_either.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

using nmtools_array;
using nm::none_t, nm::ellipsis_t;

TEST_CASE("flatten_either")
{
    {
        using either_t = nmtools_either<int,double>;
        using result_t = meta::resolve_optype_t<nm::flatten_either_t,either_t>;
        using expect_t = nmtools_tuple<int*,double*>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using either_t = nmtools_either<nmtools_either<int,double>,int>;
        using result_t = meta::resolve_optype_t<nm::flatten_either_t,either_t>;
        using expect_t = nmtools_tuple<int*,double*,int*>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using either_t = nmtools_either<nmtools_either<int,nmtools_either<float,double>>,int>;
        using result_t = meta::resolve_optype_t<nm::flatten_either_t,either_t>;
        using expect_t = nmtools_tuple<int*,float*,double*,int*>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using either_t = nmtools_either<int,nmtools_either<double,int>>;
        using result_t = meta::resolve_optype_t<nm::flatten_either_t,either_t>;
        using expect_t = nmtools_tuple<int*,double*,int*>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using either_t = nmtools_either<int,nmtools_either<nmtools_either<float,double>,int>>;
        using result_t = meta::resolve_optype_t<nm::flatten_either_t,either_t>;
        using expect_t = nmtools_tuple<int*,float*,double*,int*>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using either_t = nmtools_either<nmtools_either<float,double>,nmtools_either<size_t,int>>;
        using result_t = meta::resolve_optype_t<nm::flatten_either_t,either_t>;
        using expect_t = nmtools_tuple<float*,double*,size_t*,int*>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using either_t = nmtools_either<nmtools_either<float,double>,nmtools_either<array<size_t,3>,int>>;
        using result_t = meta::resolve_optype_t<nm::flatten_either_t,either_t>;
        using expect_t = nmtools_tuple<float*,double*,array<size_t,3>*,int*>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using index_t  = int;
        using array_t  = nmtools_array<int,2>;
        using tuple_t  = nmtools_tuple<none_t,int>;
        using tuple_slice_t = nmtools_either<tuple_t,ellipsis_t>;
        using pack_slice_t  = nmtools_either<array_t,tuple_slice_t>;
        using slice_t  = nmtools_either<pack_slice_t,index_t>;
        using result_t = meta::resolve_optype_t<nm::flatten_either_t,slice_t>;
        using expect_t = nmtools_tuple<array_t*,tuple_t*,ellipsis_t*,int*>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}