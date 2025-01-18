#include "nmtools/meta.hpp"
#include "nmtools/array/where.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nm::view;
namespace meta = nm::meta;

#define declval(T) meta::declval<T>()

TEST_CASE("is_ndarray" * doctest::test_suite("view::where"))
{
    {
        using condition_t = bool[10];
        using x_t = int[10];
        using y_t = int[10];
        using view_t = meta::remove_cvref_t<decltype(nm::unwrap(view::where(declval(condition_t),declval(x_t),declval(y_t))))>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
    }
}