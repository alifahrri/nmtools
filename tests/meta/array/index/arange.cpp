#include "nmtools/array/index/arange.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace meta = nm::meta;

using namespace nm::literals;

TEST_CASE("arange" * doctest::test_suite("index"))
{
    {
        using start_t = int;
        using stop_t  = int;
        using step_t  = nm::none_t;
        using result_t = meta::resolve_optype_t<ix::arange_shape_t,start_t,stop_t,step_t>;
        using expect_t = nmtools_array<size_t,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using start_t = decltype(0_ct);
        using stop_t  = decltype(4_ct);
        using step_t  = nm::none_t;
        using result_t = meta::resolve_optype_t<ix::arange_shape_t,start_t,stop_t,step_t>;
        using expect_t = nmtools_tuple<meta::ct<4ul>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_constant_index_array, result_t );
    }
}