#ifndef NMTOOLS_ARRAY_DETAIL_HPP
#define NMTOOLS_ARRAY_DETAIL_HPP

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <tuple>

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"

#include "nmtools/array/index/make_array.hpp"
#include "nmtools/array/index/as_tuple.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/index/compute_strides.hpp"

namespace nmtools::detail
{
    using ::nmtools::index::make_array;
    using ::nmtools::index::as_tuple;
} // namespace nmtools::detail

namespace nmtools::array::detail
{

    using ::nmtools::index::product;
    using ::nmtools::index::stride;
    using ::nmtools::index::compute_indices;
    using ::nmtools::index::compute_offset;
    using ::nmtools::index::compute_strides;

    using ::nmtools::index::make_array;
    using ::nmtools::index::make_array_ref;
}

#endif // NMTOOLS_ARRAY_DETAIL_HPP