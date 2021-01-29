#include "nmtools/array/index/nonzero.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "testing/doctest.hpp"

#include <vector>
#include <tuple>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

TEST_CASE("nonzero(vector)" * doctest::test_suite("index::nonzero"))
{
    {
        using arg_t = std::vector<bool>;
        using ret_t = meta::resolve_optype_t<nm::index::nonzero_t,arg_t>;
        using exp_t = std::vector<size_t>;
        STATIC_CHECK_IS_SAME( ret_t, exp_t );
    }
    {
        using arg_t = std::vector<int>;
        using ret_t = meta::resolve_optype_t<nm::index::nonzero_t,arg_t>;
        using exp_t = std::vector<size_t>;
        STATIC_CHECK_IS_SAME( ret_t, exp_t );
    }
}

TEST_CASE("nonzero(array)" * doctest::test_suite("index::nonzero"))
{
    {
        using arg_t = std::array<bool,3>;
        using ret_t = meta::resolve_optype_t<nm::index::nonzero_t,arg_t>;
        using exp_t = na::hybrid_ndarray<size_t,3,1>;
        STATIC_CHECK_IS_SAME( ret_t, exp_t );
    }
    {
        using arg_t = std::array<int,3>;
        using ret_t = meta::resolve_optype_t<nm::index::nonzero_t,arg_t>;
        using exp_t = na::hybrid_ndarray<size_t,3,1>;
        STATIC_CHECK_IS_SAME( ret_t, exp_t );
    }
}

TEST_CASE("nonzero(tuple)" * doctest::test_suite("index::nonzero"))
{
    {
        using arg_t = std::tuple<bool,bool,bool>;
        using ret_t = meta::resolve_optype_t<nm::index::nonzero_t,arg_t>;
        using exp_t = na::hybrid_ndarray<size_t,3,1>;
        STATIC_CHECK_IS_SAME( ret_t, exp_t );
    }
    {
        using arg_t = std::tuple<int,int,int>;
        using ret_t = meta::resolve_optype_t<nm::index::nonzero_t,arg_t>;
        using exp_t = na::hybrid_ndarray<size_t,3,1>;
        STATIC_CHECK_IS_SAME( ret_t, exp_t );
    }
}