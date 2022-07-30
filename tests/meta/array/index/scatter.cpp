#include "nmtools/array/index/scatter.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/testing/doctest.hpp"

#include <tuple>

namespace nm = nmtools;
namespace meta = nm::meta;

using nm::index::scatter_t;
using namespace nm::literals;
using nmtools_tuple;

TEST_CASE("scatter" * doctest::test_suite("index"))
{
    {
        using indices_t = decltype(tuple{1_ct,2_ct,3_ct});
        using order_t   = decltype(tuple{0_ct,1_ct,2_ct});
        using result_t  = meta::resolve_optype_t<scatter_t,indices_t,order_t>;
        using expect_t  = decltype(tuple{1_ct,2_ct,3_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t = decltype(tuple{1_ct,2_ct,3_ct});
        using order_t   = decltype(tuple{1_ct,0_ct,2_ct});
        using result_t  = meta::resolve_optype_t<scatter_t,indices_t,order_t>;
        using expect_t  = decltype(tuple{2_ct,1_ct,3_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}