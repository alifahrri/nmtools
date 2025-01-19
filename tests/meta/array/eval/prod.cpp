#include "nmtools/array/prod.hpp"
#include "nmtools/core/eval.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using nm::none_t;
using namespace nm::literals;

#define declval(type) std::declval<type>()

TEST_CASE("eval(prod)" * doctest::test_suite("eval"))
{
    // None axis
    {
        using array_t = int[3][2];
        using axis_t  = none_t;
        // using initial_t  = none_t;
        // using keepdims_t = std::false_type;
        using eval_t     = decltype(na::prod(declval(array_t),declval(axis_t)));
        using expect_t   = int;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expect_t );
    }

    // None axis, keepdims True
    {
        using array_t = int[3][2];
        using axis_t  = none_t;
        using dtype_t = none_t;
        using initial_t  = none_t;
        using keepdims_t = meta::true_type;
        using eval_t     = decltype(na::prod(declval(array_t),declval(axis_t),declval(dtype_t),declval(initial_t),declval(keepdims_t)));
        using expect_t   = na::ndarray_t<nmtools_array<int,1>,decltype(nmtools_tuple{1_ct,1_ct})>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expect_t );
    }

    // None axis, runtime keepdims
    {
        using array_t = int[3][2];
        using axis_t  = none_t;
        using dtype_t = none_t;
        using initial_t  = none_t;
        using keepdims_t = bool;
        using eval_t     = decltype(na::prod(declval(array_t),declval(axis_t),declval(dtype_t),declval(initial_t),declval(keepdims_t)));
        using expect_t   = nmtools_either<na::ndarray_t<nmtools_array<int,1>,decltype(nmtools_tuple{1_ct,1_ct})>,int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expect_t );
    }
}