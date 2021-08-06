#include "nmtools/array/view/reshape.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view"))
{
    // shape is known at compile time
    {
        using array_t = int[2][3][2];
        using shape_t = std::tuple<meta::ct<12>>;
        using view_t  = view::reshape_t<array_t,shape_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t = na::fixed_ndarray<int,2,3,2>;
        using shape_t = std::tuple<meta::ct<12>>;
        using view_t  = view::reshape_t<array_t,shape_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t = na::hybrid_ndarray<int,12,3>;
        using shape_t = std::tuple<meta::ct<12>>;
        using view_t  = view::reshape_t<array_t,shape_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
}