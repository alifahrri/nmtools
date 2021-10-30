#ifndef NMTOOLS_ARRAY_UTILITY_EMBIND_HPP
#define NMTOOLS_ARRAY_UTILITY_EMBIND_HPP

#include "nmtools/array/view/reshape.hpp"
#include "nmtools/array/array/flatten.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/array/utility/cast.hpp"
#include "nmtools/array/shape.hpp"

#include <emscripten/bind.h>
#include <vector>

// Collections of helper macros to convert from/to javascript via emscripten.
// Use macro instead of function, to avoid returning and avoid preparing placeholder at caller site.

#define NMTOOLS_FROM_JS_ARRAY(array, type, js) \
auto array##_data  = ::emscripten::convertJSArrayToNumberVector<type>(js["data"]); \
auto array##_shape = ::emscripten::convertJSArrayToNumberVector<size_t>(js["shape"]); \
auto array = ::nmtools::view::reshape(array##_data,array##_shape);

#define NMTOOLS_TO_JS_ARRAY(js, ndarray) \
using ndarray##_element_t = ::nmtools::meta::get_element_type_t<decltype(ndarray)>; \
auto js##_rtype = ::nmtools::meta::as_value_v<std::vector<ndarray##_element_t>>; \
auto js##_rdata = ::nmtools::array::flatten(ndarray,/*context=*/::nmtools::None,js##_rtype); \
auto js = ::emscripten::val::object(); \
js.set("data", ::emscripten::val::array(js##_rdata)); \
js.set("shape", ::emscripten::val::array(::nmtools::cast(::nmtools::shape(ndarray),::nmtools::meta::as_value_v<std::vector<size_t>>))); \

#define NMTOOLS_EMBIND_TYPE(dst_name, src_name, type) \
::emscripten::val dst_name(::emscripten::val val) { return src_name<type>(val); }

#define NMTOOLS_EMBIND_TYPE_BINARY(dst_name, src_name, type) \
::emscripten::val dst_name(::emscripten::val a, ::emscripten::val b) { return src_name<type>(a,b); }

#define NMTOOLS_EMBIND_TYPE_TERNARY(dst_name, src_name, type) \
::emscripten::val dst_name(::emscripten::val a, ::emscripten::val b, ::emscripten::val c) { return src_name<type>(a,b,c); }

#endif // NMTOOLS_ARRAY_UTILITY_EMBIND_HPP