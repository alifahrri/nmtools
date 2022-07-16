#ifndef NMTOOLS_ARRAY_UTILITY_CAST_HPP
#define NMTOOLS_ARRAY_UTILITY_CAST_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/apply_resize.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/mutable_flatten.hpp"

#include "nmtools/utils/isequal.hpp"

namespace nmtools
{
    /**
     * @brief tag to resolve return type of cast op
     * 
     */
    struct cast_t {};

    struct cast_kind_t {};

    namespace meta::error
    {
        template <typename...>
        struct CAST_KIND_UNSUPPORTED : detail::fail_t {};
    }
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_CAST_HPP