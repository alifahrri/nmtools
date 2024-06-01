#ifndef NMTOOLS_ARRAY_INDEX_NORMALIZE_AXIS_HPP
#define NMTOOLS_ARRAY_INDEX_NORMALIZE_AXIS_HPP

#include "nmtools/array/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/utl.hpp"

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
    template <typename axis_t, typename m_ndim_t>
    constexpr auto normalize_axis(const axis_t& axis, [[maybe_unused]] const m_ndim_t ndim_)
    {
        using result_t = meta::resolve_optype_t<normalize_axis_t,axis_t,m_ndim_t>;

        [[maybe_unused]] auto ndim = [&](){
            if constexpr (meta::is_constant_index_v<m_ndim_t>) {
                return meta::to_value_v<m_ndim_t>;
            } else {
                return ndim_;
            }
        }();
        using ndim_t [[maybe_unused]] = decltype(ndim);

        if constexpr (! (meta::is_constant_index_v<result_t> || meta::is_constant_index_array_v<result_t>)) {
            using return_t = meta::make_maybe_type_t<result_t>;
            // using return_t = utl::maybe<result_t>;

            // auto ret = return_t {};

            if constexpr (meta::is_index_array_v<result_t>) {
                auto res = result_t{};
                [[maybe_unused]] auto n = len(axis);
                bool valid = true;
                if constexpr (meta::is_resizable_v<result_t>) {
                    res.resize(n);
                }
                using ai_t  = meta::get_element_or_common_type_t<axis_t>;
                using idx_t = meta::promote_index_t<ndim_t,ai_t>;
                auto normalize_axis_impl = [&](auto i){
                    auto ai = at(axis,i);
                    if constexpr (meta::is_unsigned_v<ai_t>) {
                        if ((idx_t)ai < (idx_t)ndim) {
                            at(res,i) = (idx_t)ai;
                        } else {
                            valid = false;
                        }
                    } else if ((-(idx_t)ndim <= (idx_t)ai) && ((idx_t)ai < (idx_t)ndim)) {
                        at(res,i) = ((idx_t)ai < (idx_t)0) ? (ndim + ai) : ai;
                    } else {
                        valid = false;
                    }
                };
                if constexpr (meta::is_tuple_v<axis_t>) {
                    meta::template_for<meta::len_v<axis_t>>([&](auto i){
                        normalize_axis_impl(i);
                    });
                } else {
                    for (size_t i=0; i<(size_t)n; i++) {
                        normalize_axis_impl(i);
                    }
                }
                if (valid) {
                    // ret = res;
                    return return_t{res};
                } else {
                    // operator= from stl's optional not constexpr 😭
                    // ret = meta::Nothing;
                    return return_t{meta::Nothing};
                }
            } else if constexpr (meta::is_num_v<result_t>) {
                auto res = result_t{};
                using idx_t = meta::make_signed_t<meta::promote_index_t<ndim_t,axis_t>>;
                if ((-(idx_t)ndim <= (idx_t)axis) && ((idx_t)axis < (idx_t)ndim)) {
                    res = (axis < 0)  ? nm_index_t(ndim + axis) : nm_index_t(axis);
                    // ret = res;
                    return return_t{res};
                } else {
                    // operator= from stl's optional not constexpr 😭
                    // ret = meta::Nothing;
                    return return_t{meta::Nothing};
                }
            }

            // return ret;
        } else {
            // NOTE: quick-hack
            // TODO: no need to return maybe type
            using return_t = meta::make_maybe_type_t<result_t>;

            auto valid = [&](){
                const auto result = result_t {};
                if constexpr (meta::is_index_array_v<result_t>) {
                    for (size_t i=0; i<(size_t)len(result); i++) {
                        const auto result_i = at(result,i);
                        if (result_i < 0 || result_i >= ndim) {
                            return false;
                        }
                    }
                    return true;
                } else {
                    return ((size_t)result >= (size_t)0) && ((size_t)result < (size_t)ndim);
                }
            }();

            if (!valid) {
                return return_t{meta::Nothing};
            } else {
                auto ret = return_t {result_t{}};
                return ret;
            }
        }
    } // normalize_axis
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct INDEX_NORMALIZE_AXIS_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct INDEX_NORMALIZE_AXIS_INVALID : detail::fail_t {};
    } // namespace error
    
    template <typename axis_t, typename ndim_t>
    struct resolve_optype<
        void, index::normalize_axis_t, axis_t, ndim_t
    >
    {
        static constexpr auto vtype = [](){
            // TODO: compute at compile-time if both shape and axes are constant index
            if constexpr (is_constant_index_v<axis_t> && is_constant_index_v<ndim_t>) {
                constexpr auto axis = to_value_v<axis_t>;
                constexpr auto ndim = to_value_v<ndim_t>;
                constexpr auto res  = index::normalize_axis(axis,ndim);
                if constexpr (static_cast<bool>(res)) {
                    return as_value_v<ct<*res>>;
                } else {
                    using type = error::INDEX_NORMALIZE_AXIS_INVALID<axis_t,ndim_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (is_constant_index_array_v<axis_t> && is_constant_index_v<ndim_t>) {
                constexpr auto axis   = to_value_v<axis_t>;
                constexpr auto ndim   = to_value_v<ndim_t>;
                constexpr auto result = index::normalize_axis(axis,ndim);
                using nmtools::len, nmtools::at;
                if constexpr (static_cast<bool>(result)) {
                    constexpr auto res = *result;
                    return template_reduce<len(res)-1>([&](auto init, auto index){
                        using init_type = type_t<decltype(init)>;
                        return as_value_v<append_type_t<init_type,ct<at(res,index+1)>>>;
                    }, as_value_v<nmtools_tuple<ct<at(res,0)>>>);
                } else {
                    using type = error::INDEX_NORMALIZE_AXIS_INVALID<axis_t,ndim_t>;
                    return as_value_v<type>;
                }
            } else if constexpr ((is_constant_index_array_v<axis_t> || is_constant_index_v<axis_t>) && is_index_v<ndim_t>) {
                using type = resolve_optype_t<index::normalize_axis_t,remove_cvref_t<decltype(to_value_v<axis_t>)>,ndim_t>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<axis_t> && is_index_v<ndim_t>) {
                constexpr auto DIM = len_v<axis_t>;
                [[maybe_unused]] constexpr auto B_DIM = bounded_size_v<axis_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_size_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small_vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (is_index_v<axis_t> && is_index_v<ndim_t>) {
                using type = make_unsigned_t<axis_t>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::INDEX_NORMALIZE_AXIS_UNSUPPORTED<axis_t,ndim_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_NORMALIZE_AXIS_HPP