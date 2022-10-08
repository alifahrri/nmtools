#include "nmtools/array/view/prod.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using nm::none_t;
using namespace nm::literals;

#define declval(type) std::declval<type>()

#ifdef NMTOOLS_DISABLE_STL
using meta::true_type, meta::false_type;
#else
using std::true_type, std::false_type;
#endif

TEST_CASE("view(prod)" * doctest::test_suite("view"))
{
    // is_fixed_shape
    {
        using array_t   = int[3][2];
        using axis_t    = none_t;
        using dtype_t   = none_t;
        using initial_t = none_t;
        using keepdims_t = true_type;
        using view_t     = decltype(view::prod(declval(array_t),declval(axis_t),declval(dtype_t),declval(initial_t),declval(keepdims_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }
    {
        using array_t   = int[3][2];
        using axis_t    = none_t;
        using dtype_t   = none_t;
        using initial_t = none_t;
        using keepdims_t = false_type;
        using view_t     = decltype(view::prod(declval(array_t),declval(axis_t),declval(dtype_t),declval(initial_t),declval(keepdims_t)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
    }
    {
        using array_t   = int[3][2];
        using axis_t    = none_t;
        using dtype_t   = none_t;
        using initial_t = none_t;
        using keepdims_t = bool;
        using view_t     = decltype(view::prod(declval(array_t),declval(axis_t),declval(dtype_t),declval(initial_t),declval(keepdims_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_either, view_t );
    }
}