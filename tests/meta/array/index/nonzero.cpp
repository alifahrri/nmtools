#include "nmtools/index/nonzero.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"

#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <tuple>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace meta = nm::meta;

TEST_CASE("nonzero(vector)" * doctest::test_suite("index::nonzero"))
{
    {
        using arg_t = nmtools_list<bool>;
        using ret_t = meta::resolve_optype_t<nm::index::nonzero_t,arg_t>;
        using exp_t = nmtools_list<size_t>;
        STATIC_CHECK_IS_SAME( ret_t, exp_t );
    }
    {
        using arg_t = nmtools_list<int>;
        using ret_t = meta::resolve_optype_t<nm::index::nonzero_t,arg_t>;
        using exp_t = nmtools_list<meta::make_unsigned_t<int>>;
        STATIC_CHECK_IS_SAME( ret_t, exp_t );
    }
}

TEST_CASE("nonzero(array)" * doctest::test_suite("index::nonzero"))
{
    {
        using arg_t = nmtools_array<bool,3>;
        using ret_t = meta::resolve_optype_t<nm::index::nonzero_t,arg_t>;
        using exp_t = nmtools_static_vector<size_t,3>;
        STATIC_CHECK_IS_SAME( ret_t, exp_t );
    }
    {
        using arg_t = nmtools_array<int,3>;
        using ret_t = meta::resolve_optype_t<nm::index::nonzero_t,arg_t>;
        using exp_t = nmtools_static_vector<meta::make_unsigned_t<int>,3>;
        STATIC_CHECK_IS_SAME( ret_t, exp_t );
    }
}

TEST_CASE("nonzero(tuple)" * doctest::test_suite("index::nonzero"))
{
    {
        using arg_t = nmtools_array<bool,3>;
        using ret_t = meta::resolve_optype_t<nm::index::nonzero_t,arg_t>;
        using exp_t = nmtools_static_vector<size_t,3>;
        STATIC_CHECK_IS_SAME( ret_t, exp_t );
    }
    {
        using arg_t = nmtools_array<int,3>;
        using ret_t = meta::resolve_optype_t<nm::index::nonzero_t,arg_t>;
        using exp_t = nmtools_static_vector<meta::make_unsigned_t<int>,3>;
        STATIC_CHECK_IS_SAME( ret_t, exp_t );
    }
}