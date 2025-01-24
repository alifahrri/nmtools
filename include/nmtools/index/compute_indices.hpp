#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/index/tuple_at.hpp"
#include "nmtools/index/compute_strides.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve op type of compute_indices
     * 
     */
    struct compute_indices_t {};

    namespace impl
    {
        template <typename indices_t, typename offset_t, typename shape_t, typename strides_t>
        nmtools_index_attribute
        constexpr auto compute_indices(indices_t& indices, const offset_t& offset, const shape_t& shape, const strides_t& strides)
        {
            constexpr auto n = meta::len_v<shape_t>;
            constexpr auto m = meta::len_v<strides_t>;

            using size_type = size_t;

            if constexpr ((n>0) && (m>0))
            {
                static_assert (m==n
                    , "unsupported compute_indices, mismatched shape for shape and strides"
                );
                meta::template_for<n>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    at<i>(indices) = (offset / at<i>(strides)) % at<i>(shape);
                });
            }
            else
                for (size_type i=0; i<(size_type)len(shape); i++)
                    at(indices,i) = (offset / at(strides,i)) % at(shape,i);
        } // compute_indices
    } // namespace impl

    // TODO: cleanup index functions
    /**
     * @brief inverse operation of compute_offset
     * 
     * @param offset flat indices to be mapped
     * @param shape desired shape
     * @param strides computed strides, should be computed from shape
     * @return constexpr auto 
     */
    template <typename offset_t, typename shape_t, typename strides_t>
    nmtools_index_attribute
    constexpr auto compute_indices(const offset_t& offset, const shape_t& shape, const strides_t& strides)
    {
        using return_t = meta::resolve_optype_t<compute_indices_t,offset_t,shape_t,strides_t>;
        if constexpr (meta::is_maybe_v<offset_t>) {
            if (static_cast<bool>(offset)) {
                auto result = compute_indices(*offset,shape,strides);
                if constexpr (meta::is_maybe_v<decltype(result)>) {
                    return (result ? return_t{*result} : return_t{meta::Nothing});
                } else {
                    return return_t{result};
                }
            } else {
                return return_t{meta::Nothing};
            }
        } else if constexpr (meta::is_maybe_v<shape_t>) {
            if (static_cast<bool>(shape)) {
                auto result = compute_indices(offset,*shape,strides);
                if constexpr (meta::is_maybe_v<decltype(result)>) {
                    return (result ? return_t{*result} : return_t{meta::Nothing});
                } else {
                    return return_t{result};
                }
            } else {
                return return_t{meta::Nothing};
            }
        } else if constexpr (meta::is_maybe_v<strides_t>) {
            if (static_cast<bool>(strides)) {
                auto result = compute_indices(offset,shape,*strides);
                return return_t{result};
            } else {
                return return_t{meta::Nothing};
            }
        } else if constexpr (meta::is_constant_index_array_v<return_t>) {
            auto result = return_t{};
            return result;
        } else {
            auto indices = return_t{};
            if constexpr (meta::is_resizable_v<return_t>)
                indices.resize(len(shape));

            impl::compute_indices(indices, offset, shape, strides);

            return indices;
        }
    } // compute indices

    /**
     * @brief inverse operation of compute_offset
     * 
     * Offset (flat index) to indices.
     * 
     * @param offset flat indices to be mapped
     * @param shape desired shape
     * @return constexpr auto 
     */
    template <typename offset_t, typename shape_t>
    nmtools_index_attribute
    constexpr auto compute_indices(const offset_t& offset, const shape_t& shape)
    {
        auto strides = compute_strides(shape);
        return compute_indices(offset, shape, strides);
    } // compute_indices
} // namespace nmtools::index

namespace nmtools::meta
{

    namespace error
    {
        template <typename...>
        struct COMPUTE_INDICES_UNSUPPORTED : detail::fail_t {};
    }

    // TODO: improve type deduction
    /**
     * @brief resolve return type for compute_indices
     * 
     * @tparam offset_t 
     * @tparam shape_t 
     * @tparam strides_t 
     */
    template <typename offset_t, typename shape_t, typename strides_t>
    struct resolve_optype< void, index::compute_indices_t, offset_t, shape_t, strides_t >
    {
        static constexpr auto vtype = [](){
            [[maybe_unused]] constexpr auto DIM = len_v<shape_t>;
            [[maybe_unused]] constexpr auto B_DIM = bounded_size_v<shape_t>;
            using index_type [[maybe_unused]] = get_index_element_type_t<shape_t>;
            if constexpr (is_maybe_v<offset_t>) {
                using offset_type = get_maybe_type_t<offset_t>;
                using result_type = resolve_optype_t<index::compute_indices_t,offset_type,shape_t,strides_t>;
                if constexpr (is_maybe_v<result_type>) {
                    using type = result_type;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_maybe<result_type>;
                    return as_value_v<type>;
                }
            } else if constexpr (is_maybe_v<shape_t>) {
                using shape_type  = get_maybe_type_t<shape_t>;
                using result_type = resolve_optype_t<index::compute_indices_t,offset_t,shape_type,strides_t>;
                if constexpr (is_maybe_v<result_type>) {
                    using type = result_type;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_maybe<result_type>;
                    return as_value_v<type>;
                }
            } else if constexpr (is_maybe_v<strides_t>) {
                using strides_type = get_maybe_type_t<strides_t>;
                using result_type  = resolve_optype_t<index::compute_indices_t,offset_t,shape_t,strides_type>;
                using type = nmtools_maybe<result_type>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_v<offset_t>
                && is_constant_index_array_v<shape_t>
                && is_constant_index_array_v<strides_t>
            ) {
                constexpr auto offset  = to_value_v<offset_t>;
                constexpr auto shape   = to_value_v<shape_t>;
                constexpr auto strides = to_value_v<strides_t>;
                constexpr auto result  = index::compute_indices(offset,shape,strides);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto result_i = at(result,index);
                    using type = append_type_t<type_t<decltype(init)>,ct<result_i>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (!is_index_array_v<shape_t>) {
                using type = error::COMPUTE_INDICES_UNSUPPORTED<offset_t,shape_t,strides_t>;
                return as_value_v<type>;
            } else if constexpr (DIM > 0) {
                using type = nmtools_array<index_type,DIM>;
                return as_value_v<type>;
            } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                using type = utl::static_vector<index_type,B_DIM>;
                return as_value_v<type>;
            } else {
                using type = nmtools_list<index_type>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<remove_cvref_t<decltype(vtype)>>;
    }; // resolve_optype

} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP