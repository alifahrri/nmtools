#include "nmtools/array/index/argfilter.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("argfilter" * doctest::test_suite("meta::index"))
{
    {
        using arg_t = std::array<int,4>;
        using idx_t = size_t;
        using res_t = meta::resolve_optype_t<nm::index::argfilter_t,arg_t,idx_t>;
        using exp_t = nm::array::hybrid_ndarray<idx_t,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using arg_t = std::vector<int>;
        using idx_t = size_t;
        using res_t = meta::resolve_optype_t<nm::index::argfilter_t,arg_t,idx_t>;
        using exp_t = std::vector<idx_t>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using arg_t = std::tuple<int,size_t,int,size_t>;
        using idx_t = size_t;
        using res_t = meta::resolve_optype_t<nm::index::argfilter_t,arg_t,idx_t>;
        using exp_t = nm::array::hybrid_ndarray<idx_t,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        // doesn't have common type
        using arg_t = std::tuple<int,size_t,int,std::tuple<double>>;
        using idx_t = size_t;
        using res_t = meta::resolve_optype_t<nm::index::argfilter_t,arg_t,idx_t>;
        using exp_t = void;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using arg_t = nm::array::hybrid_ndarray<int,4,1>;
        using idx_t = size_t;
        using res_t = meta::resolve_optype_t<nm::index::argfilter_t,arg_t,idx_t>;
        using exp_t = nm::array::hybrid_ndarray<idx_t,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}