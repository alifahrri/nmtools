#include "nmtools/array/index/argsort.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

using nm::index::argsort_t;
using namespace nm::literals;
using nmtools_tuple;

TEST_CASE("argsort" * doctest::test_suite("index"))
{
    {
        using array_t  = decltype(nmtools_tuple{0_ct,1_ct,2_ct,3_ct});
        using result_t = meta::resolve_optype_t<argsort_t,array_t>;
        using expected_t = decltype(nmtools_tuple{0_ct,1_ct,2_ct,3_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using array_t  = decltype(nmtools_tuple{1_ct,2_ct,3_ct,4_ct});
        using result_t = meta::resolve_optype_t<argsort_t,array_t>;
        using expected_t = decltype(nmtools_tuple{0_ct,1_ct,2_ct,3_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using array_t  = decltype(nmtools_tuple{2_ct,1_ct,3_ct,4_ct});
        using result_t = meta::resolve_optype_t<argsort_t,array_t>;
        using expected_t = decltype(nmtools_tuple{1_ct,0_ct,2_ct,3_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using array_t  = decltype(nmtools_tuple{3_ct,1_ct,2_ct,4_ct});
        using result_t = meta::resolve_optype_t<argsort_t,array_t>;
        using expected_t = decltype(nmtools_tuple{1_ct,2_ct,0_ct,3_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}