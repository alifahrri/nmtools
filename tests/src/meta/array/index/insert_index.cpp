#include "nmtools/array/index/insert_index.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace ix = nm::index;
namespace meta = nm::meta;

TEST_CASE("insert_index" * doctest::test_suite("index"))
{
    SUBCASE("case1")
    {
        using indices_t = nmtools_list<int>;
        using index_t   = int;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::insert_index_t,indices_t,index_t,axis_t>;
        using expect_t  = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case2")
    {
        using indices_t = nmtools_array<int,3>;
        using index_t   = int;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::insert_index_t,indices_t,index_t,axis_t>;
        using expect_t  = nmtools_array<int,4>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case3")
    {
        using indices_t = nmtools_list<int>;
        using index_t   = nm::ellipsis_t;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::insert_index_t,indices_t, index_t, axis_t>;
        using expect_t  = nmtools_list<nmtools_either<int,nm::ellipsis_t>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case4")
    {
        using indices_t = nmtools_array<int,3>;
        using index_t   = nm::ellipsis_t;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::insert_index_t,indices_t, index_t, axis_t>;
        using expect_t  = nmtools_array<nmtools_either<int,nm::ellipsis_t>,4>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case5")
    {
        using indices_t = nmtools_list<int>;
        using index_t   = nmtools_tuple<nm::none_t,nm::none_t>;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::insert_index_t,indices_t, index_t, axis_t>;
        using expect_t  = nmtools_list<nmtools_either<int,index_t>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case6")
    {
        using indices_t = nmtools_array<int,3>;
        using index_t   = nmtools_tuple<nm::none_t,nm::none_t>;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::insert_index_t,indices_t, index_t, axis_t>;
        using expect_t  = nmtools_array<nmtools_either<int,index_t>,4>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}
