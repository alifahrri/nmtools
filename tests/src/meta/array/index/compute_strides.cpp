#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

#include <tuple>

namespace nm = nmtools;
namespace meta = nm::meta;

using nm::index::compute_strides_t;
using namespace nm::literals;
using std::tuple;

TEST_CASE("computes_strides" * doctest::test_suite("index"))
{
    {
        using shape_t   = decltype(tuple{3_ct});
        using strides_t = meta::resolve_optype_t<compute_strides_t,shape_t>;
        using expect_t  = decltype(tuple{1_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( strides_t, expect_t );
    }
    {
        using shape_t   = decltype(tuple{3_ct,2_ct});
        using strides_t = meta::resolve_optype_t<compute_strides_t,shape_t>;
        using expect_t  = decltype(tuple{2_ct,1_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( strides_t, expect_t );
    }
    {
        using shape_t   = decltype(tuple{3_ct,2_ct,1_ct});
        using strides_t = meta::resolve_optype_t<compute_strides_t,shape_t>;
        using expect_t  = decltype(tuple{2_ct,1_ct,1_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( strides_t, expect_t );
    }
    {
        using shape_t   = decltype(tuple{3_ct,2_ct,3_ct});
        using strides_t = meta::resolve_optype_t<compute_strides_t,shape_t>;
        using expect_t  = decltype(tuple{6_ct,3_ct,1_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( strides_t, expect_t );
    }
}