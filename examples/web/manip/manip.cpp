#include "nmtools/array/array/transpose.hpp"
#include "nmtools/array/array/zeros.hpp"
#include "nmtools/array/array/where.hpp"
#include "nmtools/array/array/tile.hpp"
#include "nmtools/array/array/take.hpp"
#include "nmtools/array/array/squeeze.hpp"
#include "nmtools/array/array/slice.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/repeat.hpp"
#include "nmtools/array/array/pad.hpp"
#include "nmtools/array/array/ones.hpp"
#include "nmtools/array/array/full.hpp"
#include "nmtools/array/array/flip.hpp"
#include "nmtools/array/array/flatten.hpp"
#include "nmtools/array/array/expand_dims.hpp"
#include "nmtools/array/array/concatenate.hpp"
#include "nmtools/array/array/compress.hpp"
#include "nmtools/array/array/broadcast_to.hpp"
#include "nmtools/array/array/atleast_3d.hpp"
#include "nmtools/array/array/atleast_2d.hpp"
#include "nmtools/array/array/atleast_1d.hpp"
#include "nmtools/array/array/arange.hpp"

#include "nmtools/platform/embind.hpp"
#include <emscripten/bind.h>

namespace em = emscripten;

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

template <typename T>
auto transpose(em::val a)
{
    NMTOOLS_FROM_JS_ARRAY(a_array, T, a);

    auto res = view::transpose(a_array);

    NMTOOLS_TO_JS_ARRAY(ret, res);
    return ret;
}

NMTOOLS_EMBIND_TYPE(transpose_i32, transpose, int)

EMSCRIPTEN_BINDINGS(my_module) {
    em::function("transpose_i32", &transpose_i32);
}
