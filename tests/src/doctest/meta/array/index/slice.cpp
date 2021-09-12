#include "nmtools/array/index/slice.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

/*
error: redefinition of 'index' as different kind of symbol
namespace index = nm::index;
          ^
/usr/include/strings.h:68:14: note: previous definition is here
extern char *index (const char *__s, int __c)
*/
// namespace index = nm::index;

using nm::Elipsis, nm::None;

TEST_CASE("shape_slice" * doctest::test_suite("meta::index"))
{
    {
        using shape_t  = int[3];
        using slice0_t = decltype(Elipsis);
        using slice1_t = decltype(std::tuple{None,None});
        using result_t = meta::resolve_optype_t<nm::index::shape_slice_t,shape_t,slice0_t,slice1_t>;
        using expected_t = std::array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using shape_t  = std::array<int,3>;
        using slice0_t = decltype(Elipsis);
        using slice1_t = decltype(std::tuple{None,None});
        using result_t = meta::resolve_optype_t<nm::index::shape_slice_t,shape_t,slice0_t,slice1_t>;
        using expected_t = std::array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using shape_t  = na::fixed_ndarray<int,3>;
        using slice0_t = decltype(Elipsis);
        using slice1_t = decltype(std::tuple{None,None});
        using result_t = meta::resolve_optype_t<nm::index::shape_slice_t,shape_t,slice0_t,slice1_t>;
        using expected_t = na::fixed_ndarray<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using shape_t = std::array<size_t,3>;
        // using slice0_t = size_t, size_t, size_t, none_t, none_t;
    }
}