#include "nmtools/index/logical_not.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"
#include <tuple>

namespace nm = nmtools;
namespace meta = nm::meta;

using nm::index::logical_not_t;
using namespace nm::literals;
#ifdef NMTOOLS_DISABLE_STL
using nmtools_tuple, meta::false_type, meta::true_type;
#else
using std::tuple, std::false_type, std::true_type;
#endif

TEST_CASE("logical_not" * doctest::test_suite("index"))
{
    {
        using x_t = decltype(nmtools_tuple{true_type{},false_type{},false_type{},true_type{},false_type{}});
        using res_t = meta::resolve_optype_t<logical_not_t,x_t>;
        // using exp_t = decltype(nmtools_tuple{meta::false_type{},meta::true_type{},meta::true_type{},meta::false_type{},meta::true_type{}});
        using exp_t = decltype(nmtools_tuple{meta::integral_constant<nm_bool_t,false>{},meta::integral_constant<nm_bool_t,true>{},meta::integral_constant<nm_bool_t,true>{},meta::integral_constant<nm_bool_t,false>{},meta::integral_constant<nm_bool_t,true>{}});
        NMTOOLS_STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}