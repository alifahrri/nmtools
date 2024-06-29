#include "nmtools/array/index/sum.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/testing/doctest.hpp"

#include <tuple>

namespace nm = nmtools;
namespace meta = nm::meta;

using nm::index::sum_t;
using namespace nm::literals;
using nmtools_tuple;

TEST_CASE("sum" * doctest::test_suite("index"))
{
    {
        using array_t = decltype(nmtools_tuple{1_ct,2_ct,3_ct});
        using result_t = meta::resolve_optype_t<sum_t,array_t>;
        using expect_t = decltype(6_ct);
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}