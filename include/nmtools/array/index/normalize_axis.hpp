#ifndef NMTOOLS_ARRAY_INDEX_NORMALIZE_AXIS_HPP
#define NMTOOLS_ARRAY_INDEX_NORMALIZE_AXIS_HPP

#include "nmtools/array/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::index
{
    struct normalize_axis_t {};

    /**
     * @brief Normalize axis (or axes) to given number of dimension.
     * 
     * @tparam axis_t 
     * @tparam ndim_t 
     * @param axis      input axis to be normalized, can be index or index array
     * @param ndim      number of dimension for reference
     * @return constexpr auto 
     */
    template <typename axis_t, typename ndim_t>
    constexpr auto normalize_axis(const axis_t& axis, const ndim_t ndim)
    {
        using result_t = meta::resolve_optype_t<normalize_axis_t,axis_t,ndim_t>;
        using return_t = meta::make_maybe_type_t<result_t>;

        auto ret = return_t {};

        if constexpr (meta::is_index_array_v<result_t>) {
            auto res = result_t{};
            auto n = len(axis);
            bool valid = true;
            if constexpr (meta::is_resizeable_v<result_t>) {
                res.resize(n);
            }
            for (size_t i=0; i<(size_t)n; i++) {
                auto ai = at(axis,i);
                using ai_t  = meta::get_element_or_common_type_t<axis_t>;
                using idx_t = meta::promote_index_t<ndim_t,ai_t>;
                if ((-(idx_t)ndim <= (idx_t)ai) && ((idx_t)ai < (idx_t)ndim)) {
                    at(res,i) = (ai < (ai_t)0) ? (ndim + ai) : ai;
                } else {
                    valid = false;
                }
            }
            if (valid) {
                ret = res;
            } else {
                ret = meta::Nothing;
            }
        } else if constexpr (meta::is_num_v<result_t>) {
            auto res = result_t{};
            using idx_t = meta::promote_index_t<ndim_t,axis_t>;
            if ((-(idx_t)ndim <= (idx_t)axis) && ((idx_t)axis < (idx_t)ndim)) {
                res = (axis < (axis_t)0)  ? (ndim + axis) : axis;
                ret = res;
            } else {
                ret = meta::Nothing;
            }
        }

        return ret;
    } // normalize_axis
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        struct INDEX_NORMALIZE_AXIS_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    template <typename axis_t, typename ndim_t>
    struct resolve_optype<
        void, index::normalize_axis_t, axis_t, ndim_t
    >
    {
        static constexpr auto vtype = [](){
            // TODO: compute at compile-time if both shape and axes are constant index
            if constexpr (is_index_array_v<axis_t> && is_index_v<ndim_t>) {
                // simply make unsigned
                using index_t    = get_element_type_t<axis_t>;
                using unsigned_t = make_unsigned_t<index_t>;
                using index_array_t = transform_bounded_array_t<axis_t>;
                using type = replace_element_type_t<index_array_t,unsigned_t>;
                return as_value_v<type>;
            } else if constexpr (is_index_v<axis_t> && is_index_v<ndim_t>) {
                using type = make_unsigned_t<axis_t>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::INDEX_NORMALIZE_AXIS_UNSUPPORTED>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_NORMALIZE_AXIS_HPP