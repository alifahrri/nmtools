#ifndef NMTOOLS_ARRAY_DETAIL_HPP
#define NMTOOLS_ARRAY_DETAIL_HPP

// TODO: remove this file

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <tuple>

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"

#include "nmtools/array/index/as_tuple.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/index/compute_strides.hpp"

namespace nmtools::detail
{
    using ::nmtools::index::as_tuple;
} // namespace nmtools::detail

#endif // NMTOOLS_ARRAY_DETAIL_HPP