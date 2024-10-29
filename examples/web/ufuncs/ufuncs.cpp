#include "nmtools/array/array/sum.hpp"
#include "nmtools/array/view/ufuncs/clip.hpp"
#include "nmtools/array/array/ufuncs/exp.hpp"

#include "nmtools/platform/embind.hpp"
#include <emscripten/bind.h>

namespace em = emscripten;

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

template <typename T>
em::val add(em::val a, em::val b)
{
    NMTOOLS_FROM_JS_ARRAY(a_array, T, a);
    NMTOOLS_FROM_JS_ARRAY(b_array, T, b);

    auto res = view::add(a_array, b_array);

    // convert back to javascript object.
    // "data" represent flat memory, "shape" represents the resulting shape
    NMTOOLS_TO_JS_ARRAY(ret, res);
    return ret;
}

template <typename T>
em::val exp(em::val a)
{
    NMTOOLS_FROM_JS_ARRAY(ndarray, T, a);

    // compute exp, 
    // actually create a view,
    // the actual compute is when flattening (NMTOOLS_TO_JS_ARRAY)
    auto exp = view::exp(ndarray);

    NMTOOLS_TO_JS_ARRAY(ret, exp);
    return ret;
}

template <typename T>
em::val clip(em::val a, em::val b, em::val c)
{
    NMTOOLS_FROM_JS_ARRAY(a_array, T, a);
    NMTOOLS_FROM_JS_ARRAY(b_array, T, b);
    NMTOOLS_FROM_JS_ARRAY(c_array, T, c);

    auto res = view::clip(a_array,b_array,c_array);

    NMTOOLS_TO_JS_ARRAY(ret, res);
    return ret;
}

NMTOOLS_EMBIND_TYPE(exp_i32, exp, int)
NMTOOLS_EMBIND_TYPE(exp_f32, exp, float)
NMTOOLS_EMBIND_TYPE_BINARY(add_i32, add, int)
NMTOOLS_EMBIND_TYPE_BINARY(add_f32, add, float)
NMTOOLS_EMBIND_TYPE_TERNARY(clip_i32, clip, int)
NMTOOLS_EMBIND_TYPE_TERNARY(clip_f32, clip, float)

EMSCRIPTEN_BINDINGS(my_module) {
    em::function("exp_i32", &exp_i32);
    em::function("exp_f32", &exp_f32);
    em::function("add_i32", &add_i32);
    em::function("add_f32", &add_f32);
    em::function("clip_i32", &clip_i32);
    em::function("clip_f32", &clip_f32);
}
