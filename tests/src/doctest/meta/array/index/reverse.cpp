#include "nmtools/array/index/reverse.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

using nm::index::reverse_t;
using namespace nm::literals;

TEST_CASE("reverse" * doctest::test_suite("index"))
{
    {
        using indices_t  = int[2];
        using result_t   = meta::resolve_optype_t<reverse_t, indices_t>;
        using expected_t = std::array<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using indices_t  = std::array<int,2>;
        using result_t   = meta::resolve_optype_t<reverse_t, indices_t>;
        using expected_t = std::array<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using indices_t  = std::vector<int>;
        using result_t   = meta::resolve_optype_t<reverse_t, indices_t>;
        using expected_t = std::vector<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using indices_t  = na::fixed_ndarray<int,2>;
        using result_t   = meta::resolve_optype_t<reverse_t, indices_t>;
        using expected_t = na::fixed_ndarray<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using indices_t  = na::hybrid_ndarray<int,2,1>;
        using result_t   = meta::resolve_optype_t<reverse_t, indices_t>;
        using expected_t = na::hybrid_ndarray<int,2,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using indices_t  = decltype(std::tuple{1_ct,2_ct});
        using result_t   = meta::resolve_optype_t<reverse_t, indices_t>;
        using expected_t = decltype(std::tuple{2_ct,1_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using indices_t  = decltype(std::tuple{2_ct,0_ct,1_ct});
        using result_t   = meta::resolve_optype_t<reverse_t, indices_t>;
        using expected_t = decltype(std::tuple{1_ct,0_ct,2_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}