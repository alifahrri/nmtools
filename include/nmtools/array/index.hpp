#ifndef NMTOOLS_ARRAY_INDEX_HPP
#define NMTOOLS_ARRAY_INDEX_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"

#include "nmtools/array/index/as_tuple.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/index/gather.hpp"
#include "nmtools/array/index/ndindex.hpp"
#include "nmtools/array/index/make_array.hpp"
#include "nmtools/array/index/make_slice_index.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/reverse.hpp"
#include "nmtools/array/index/scatter.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/unpack_slice_indices.hpp"

#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools
{
    using std::size;
    using std::get;
    using std::common_type_t;
    using meta::remove_cvref_t;

    using ::nmtools::index::end_t;
    using ::nmtools::index::end;
    using ::nmtools::index::make_slice_index;
    using ::nmtools::index::ndindex;
    using ::nmtools::index::ndindex_t;

    namespace detail
    {
        using ::nmtools::index::reverse;
        using ::nmtools::index::gather;
        using ::nmtools::index::scatter;
        using ::nmtools::index::unpack_slice_indices;
    } // namespace detail
} // namespace nmtools

#endif // NMTOOLS_ARRAY_INDEX_HPP