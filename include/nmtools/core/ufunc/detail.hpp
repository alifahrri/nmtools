#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_DETAIL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_DETAIL_HPP

#include "nmtools/core/ufunc/meta.hpp"

namespace nmtools::view::detail
{
    using meta::get_operands_type;
    using meta::get_operands_type_t;

    using meta::has_result_type;
    using meta::has_result_type_v;

    using meta::get_ufunc_result_type;
    using meta::get_ufunc_result_type_t;

    using meta::get_reducer_result_type;
    using meta::get_reducer_result_type_t;

    using meta::get_result_type;
}

#endif // NMTOOLS_ARRAY_VIEW_UFUNC_DETAIL_HPP