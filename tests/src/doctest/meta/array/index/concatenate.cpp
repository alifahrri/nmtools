#include "nmtools/array/index/concatenate.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/constants.hpp"

#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace idx  = nm::index;

TEST_CASE("concatenate" * doctest::test_suite("meta::index"))
{
    {
        using ashape_t   = std::array<int,3>;
        using indices_t  = std::array<int,3>;
        using axis_t     = int;
        using return_t   = meta::resolve_optype_t<idx::concatenate_t,ashape_t,indices_t,axis_t>;
        using expected_t = std::array<int,3>;
        STATIC_CHECK_IS_SAME( return_t, expected_t );
    }
    {
        using ashape_t   = std::array<int,3>;
        using indices_t  = int[3];
        using axis_t     = int;
        using return_t   = meta::resolve_optype_t<idx::concatenate_t,ashape_t,indices_t,axis_t>;
        using expected_t = std::array<int,3>;
        STATIC_CHECK_IS_SAME( return_t, expected_t );
    }
    {
        using ashape_t   = int[3];
        using indices_t  = int[3];
        using axis_t     = int;
        using return_t   = meta::resolve_optype_t<idx::concatenate_t,ashape_t,indices_t,axis_t>;
        using expected_t = std::array<int,3>;
        STATIC_CHECK_IS_SAME( return_t, expected_t );
    }
    {
        using ashape_t   = std::array<int,3>;
        using indices_t  = std::vector<int>;
        using axis_t     = int;
        using return_t   = meta::resolve_optype_t<idx::concatenate_t,ashape_t,indices_t,axis_t>;
        using expected_t = std::array<int,3>;
        STATIC_CHECK_IS_SAME( return_t, expected_t );
    }
    {
        using ashape_t   = std::vector<int>;
        using indices_t  = std::array<int,3>;
        using axis_t     = int;
        using return_t   = meta::resolve_optype_t<idx::concatenate_t,ashape_t,indices_t,axis_t>;
        using expected_t = std::vector<int>;
        STATIC_CHECK_IS_SAME( return_t, expected_t );
    }
    {
        using ashape_t   = std::vector<int>;
        using indices_t  = std::vector<int>;
        using axis_t     = int;
        using return_t   = meta::resolve_optype_t<idx::concatenate_t,ashape_t,indices_t,axis_t>;
        using expected_t = std::vector<int>;
        STATIC_CHECK_IS_SAME( return_t, expected_t );
    }
    {
        using ashape_t   = std::tuple<int,int,int>;
        using indices_t  = std::array<int,3>;
        using axis_t     = int;
        using return_t   = meta::resolve_optype_t<idx::concatenate_t,ashape_t,indices_t,axis_t>;
        using expected_t = std::array<int,3>;
        STATIC_CHECK_IS_SAME( return_t, expected_t );
    }
    {
        using ashape_t   = na::hybrid_ndarray<int,3,1>;
        using indices_t  = std::array<int,3>;
        using axis_t     = int;
        using return_t   = meta::resolve_optype_t<idx::concatenate_t,ashape_t,indices_t,axis_t>;
        using expected_t = na::hybrid_ndarray<int,3,1>;
        STATIC_CHECK_IS_SAME( return_t, expected_t );
    }
}