#include "nmtools/array/index/slice.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

/*
error: redefinition of 'index' as different kind of symbol
namespace index = nm::index;
          ^
/usr/include/strings.h:68:14: note: previous definition is here
extern char *index (const char *__s, int __c)
*/
namespace ix = nm::index;

using nm::Ellipsis, nm::None, nm::none_t, nm::ellipsis_t;

TEST_CASE("shape_slice" * doctest::test_suite("meta::index"))
{
    {
        using shape_t  = int[3];
        using slice0_t = decltype(Ellipsis);
        using slice1_t = decltype(nmtools_tuple{None,None});
        using result_t = meta::resolve_optype_t<nm::index::shape_slice_t,shape_t,slice0_t,slice1_t>;
        using expected_t = nmtools_array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using shape_t  = nmtools_array<int,3>;
        using slice0_t = decltype(Ellipsis);
        using slice1_t = decltype(nmtools_tuple{None,None});
        using result_t = meta::resolve_optype_t<nm::index::shape_slice_t,shape_t,slice0_t,slice1_t>;
        using expected_t = nmtools_array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using shape_t  = nmtools_list<int>;
        using slice0_t = decltype(Ellipsis);
        using slice1_t = decltype(nmtools_tuple{None,None});
        using result_t = meta::resolve_optype_t<nm::index::shape_slice_t,shape_t,slice0_t,slice1_t>;
        using expected_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using shape_t  = na::fixed_ndarray<int,3>;
        using slice0_t = decltype(Ellipsis);
        using slice1_t = decltype(nmtools_tuple{None,None});
        using result_t = meta::resolve_optype_t<nm::index::shape_slice_t,shape_t,slice0_t,slice1_t>;
        using expected_t = nmtools_array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        // using shape_t = nmtools_array<size_t,3>;
        // using slice0_t = size_t, size_t, size_t, none_t, none_t;
    }
}

TEST_CASE("shape_dynamic_slice" * doctest::test_suite("meta::index"))
{
    {
        using shape_t  = nmtools_list<size_t>;
        using slice_t  = nmtools_tuple<none_t,size_t>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_list<size_t>;
        using slice_t  = nmtools_tuple<none_t,none_t>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_list<size_t>;
        using slice_t  = nmtools_tuple<int,int>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_list<size_t>;
        using slice_t  = nmtools_array<int,2>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_list<size_t>;
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_list<size_t>;
        using slice_t  = nmtools_tuple<int,none_t,size_t>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_list<size_t>;
        using slice_t  = nmtools_either<ellipsis_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_list<size_t>;
        using slice_t  = nmtools_tuple<ellipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_list<size_t>;
        using slice_t  = nmtools_either<int,nmtools_either<ellipsis_t,nmtools_tuple<none_t,none_t,int>>>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_list<size_t>;
        using slice_t  = nmtools_either<int,nmtools_either<ellipsis_t,nmtools_array<int,3>>>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    // shape_t array
    {
        using shape_t  = nmtools_array<size_t,3>;
        using slice_t  = nmtools_tuple<none_t,size_t>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        // TODO: deduce as fixed array if all slices is range
        using expect_t = nmtools_static_vector<size_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_array<size_t,3>;
        using slice_t  = nmtools_tuple<none_t,none_t>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_static_vector<size_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_array<size_t,3>;
        using slice_t  = nmtools_tuple<int,int>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_static_vector<size_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_array<size_t,3>;
        using slice_t  = nmtools_array<int,2>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_static_vector<size_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_array<size_t,3>;
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_static_vector<size_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_array<size_t,3>;
        using slice_t  = nmtools_either<ellipsis_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_static_vector<size_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
        {
        using shape_t  = nmtools_array<size_t,3>;
        using slice_t  = nmtools_tuple<ellipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_static_vector<size_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_array<size_t,3>;
        using slice_t  = nmtools_either<int,nmtools_either<ellipsis_t,nmtools_tuple<none_t,none_t,int>>>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_static_vector<size_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_array<size_t,3>;
        using slice_t  = nmtools_either<int,nmtools_either<ellipsis_t,nmtools_array<int,3>>>;
        using slices_t = nmtools_list<slice_t>;
        using result_t = meta::resolve_optype_t<ix::shape_dynamic_slice_t,shape_t,slices_t>;
        using expect_t = nmtools_static_vector<size_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}

TEST_CASE("dynamic_slice" * doctest::test_suite("meta::index"))
{
    {
        using indices_t = nmtools_list<size_t>;
        using shape_t   = nmtools_list<size_t>;
        using slice_t   = nmtools_tuple<none_t,size_t>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_list<size_t>;
        using shape_t   = nmtools_list<size_t>;
        using slice_t   = nmtools_tuple<none_t,none_t>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_list<size_t>;
        using shape_t   = nmtools_list<size_t>;
        using slice_t   = nmtools_tuple<int,int>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_list<size_t>;
        using shape_t   = nmtools_list<size_t>;
        using slice_t   = nmtools_array<int,2>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_list<size_t>;
        using shape_t   = nmtools_list<size_t>;
        using slice_t   = nmtools_tuple<none_t,none_t,int>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_list<size_t>;
        using shape_t   = nmtools_list<size_t>;
        using slice_t   = nmtools_tuple<int,none_t,size_t>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_list<size_t>;
        using shape_t   = nmtools_list<size_t>;
        using slice_t   = nmtools_either<ellipsis_t,nmtools_tuple<none_t,none_t>>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_list<size_t>;
        using shape_t   = nmtools_list<size_t>;
        using slice_t   = nmtools_tuple<ellipsis_t,int>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_list<size_t>;
        using shape_t   = nmtools_list<size_t>;
        using slice_t   = nmtools_either<int,nmtools_either<ellipsis_t,nmtools_tuple<none_t,none_t,int>>>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_list<size_t>;
        using shape_t   = nmtools_list<size_t>;
        using slice_t  = nmtools_either<int,nmtools_either<ellipsis_t,nmtools_array<int,3>>>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    // shape_t array
    {
        using indices_t = nmtools_static_vector<size_t,3>;
        using shape_t   = nmtools_array<size_t,3>;
        using slice_t   = nmtools_tuple<none_t,size_t>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_static_vector<size_t,3>;
        using shape_t   = nmtools_array<size_t,3>;
        using slice_t   = nmtools_tuple<none_t,none_t>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_static_vector<size_t,3>;
        using shape_t   = nmtools_array<size_t,3>;
        using slice_t   = nmtools_tuple<int,int>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_static_vector<size_t,3>;
        using shape_t   = nmtools_array<size_t,3>;
        using slice_t   = nmtools_array<int,2>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_static_vector<size_t,3>;
        using shape_t   = nmtools_array<size_t,3>;
        using slice_t   = nmtools_tuple<none_t,none_t,int>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_static_vector<size_t,3>;
        using shape_t   = nmtools_array<size_t,3>;
        using slice_t   = nmtools_either<ellipsis_t,nmtools_tuple<none_t,none_t>>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_static_vector<size_t,3>;
        using shape_t   = nmtools_array<size_t,3>;
        using slice_t   = nmtools_tuple<ellipsis_t,int>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_static_vector<size_t,3>;
        using shape_t   = nmtools_array<size_t,3>;
        using slice_t   = nmtools_either<int,nmtools_either<ellipsis_t,nmtools_tuple<none_t,none_t,int>>>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = nmtools_static_vector<size_t,3>;
        using shape_t   = nmtools_array<size_t,3>;
        using slice_t   = nmtools_either<int,nmtools_either<ellipsis_t,nmtools_array<int,3>>>;
        using slices_t  = nmtools_list<slice_t>;
        using result_t  = meta::resolve_optype_t<ix::dynamic_slice_t,indices_t,shape_t,slices_t>;
        using expect_t  = shape_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}