#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

// TODO: remove
#if 0
TEST_CASE("hybrid_ndarray_max_size" * doctest::test_suite("hybrid_ndarray_max_size"))
{
    {
        using op_t   = view::add_t<>;
        using array_t = view::decorator_t< view::ufunc_t, op_t, na::hybrid_ndarray<int,3,2>, na::hybrid_ndarray<int,3,2> >;
        constexpr auto max_size = meta::hybrid_ndarray_max_size_v<array_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( max_size, 3 );
    }
}
#endif