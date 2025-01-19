#include "nmtools/meta.hpp"
#include "nmtools/utl/tuple.hpp"
#include "nmtools/array/broadcast_to.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;
namespace view = nm::view;
namespace meta = nm::meta;

#define declval(T) meta::declval<T>()

TEST_CASE("broadcast_to" * doctest::test_suite("view"))
{
    {
        using array_t = int[10];
        using shape_t = utl::tuple<meta::ct<10>>;
        using broadcasted_t = meta::remove_cvref_t<decltype(nm::unwrap(view::broadcast_to(declval(array_t),declval(shape_t))))>;
        static_assert( meta::is_ndarray_v<broadcasted_t> );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, broadcasted_t );
    }
    {
        using array_t = int[10];
        using shape_t = utl::tuple<meta::ct<1>,meta::ct<10>>;
        using broadcasted_t = meta::remove_cvref_t<decltype(nm::unwrap(view::broadcast_to(declval(array_t),declval(shape_t))))>;
        static_assert( meta::is_ndarray_v<broadcasted_t> );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, broadcasted_t );
    }
}