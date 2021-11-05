#include "nmtools/array/view/transpose.hpp"
#include "nmtools/testing/doctest.hpp"

#define declval(type) std::declval<type>()

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("transpose" * doctest::test_suite("view"))
{
    SUBCASE("is_fixed_size_ndarray")
    {
        {
            using array_t = int[2][3];
            using axes_t  = nm::none_t;
            using view_t  = decltype(view::transpose(declval(array_t),declval(axes_t)));
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using array_t = std::array<std::array<int,3>,2>;
            using axes_t  = nm::none_t;
            using view_t  = decltype(view::transpose(declval(array_t),declval(axes_t)));
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using array_t = na::fixed_ndarray<int,2,3>;
            using axes_t  = nm::none_t;
            using view_t  = decltype(view::transpose(declval(array_t),declval(axes_t)));
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
    }
}