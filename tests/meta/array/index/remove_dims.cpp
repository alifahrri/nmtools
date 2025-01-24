#include "nmtools/index/remove_dims.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

#include <tuple>

namespace nm = nmtools;
namespace meta = nm::meta;

using nm::index::remove_dims_t;
using namespace nm::literals;

TEST_CASE("remove_dims" * doctest::test_suite("meta"))
{
    {
        using shape_t = decltype(nmtools_tuple{1_ct,2_ct,3_ct});
        using axis_t  = decltype(1_ct);
        using keepdims_t = meta::false_type;
        using result_t   = meta::resolve_optype_t<remove_dims_t,shape_t,axis_t,keepdims_t>;
        using expected_t = decltype(nmtools_tuple{1_ct,3_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using shape_t = decltype(nmtools_tuple{1_ct,2_ct,3_ct});
        using axis_t  = decltype(1_ct);
        using keepdims_t = meta::true_type;
        using result_t   = meta::resolve_optype_t<remove_dims_t,shape_t,axis_t,keepdims_t>;
        using expected_t = decltype(nmtools_tuple{1_ct,1_ct,3_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}