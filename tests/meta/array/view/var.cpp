#include "nmtools/array/var.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

#define declval(type) std::declval<type>()

namespace nm = nmtools;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("is_ndarray" * doctest::test_suite("view::var"))
{
    {
        using array_t = int[2][3][2];
        using axis_t  = int[1];
        using view_t  = meta::remove_cvref_t<decltype(nm::unwrap(view::var(declval(array_t),declval(axis_t))))>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
    }
    {
        using array_t = int[2][3][2];
        using axis_t  = nmtools_list<int>;
        using view_t  = meta::remove_cvref_t<decltype(nm::unwrap(view::var(declval(array_t),declval(axis_t))))>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
    }
}

TEST_CASE("get_element_type" * doctest::test_suite("view::var"))
{
    {
        using array_t = int[2][3][2];
        using axis_t  = int[1];
        using view_t  = meta::remove_cvref_t<decltype(nm::unwrap(view::var(declval(array_t),declval(axis_t))))>;
        using elem_t  = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( elem_t, float );
    }
}