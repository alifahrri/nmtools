#include "nmtools/array/index/remove_single_dims.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

#include <tuple>

namespace nm = nmtools;
namespace ix = nm::index;
namespace meta = nm::meta;

using nm::index::remove_single_dims_t;
using namespace nm::literals;
#ifdef NMTOOLS_DISABLE_STL
using nmtools_tuple;
#else
using std::tuple;
#endif

TEST_CASE("remove_single_dims" * doctest::test_suite("index"))
{
    {
        using shape_t = decltype(tuple{1_ct,2_ct,3_ct});
        using result_t = meta::resolve_optype_t<remove_single_dims_t,shape_t>;
        using expected_t = decltype(tuple{2_ct,3_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}