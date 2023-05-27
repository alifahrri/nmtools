#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/compute_strides.hpp"

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
        constexpr auto compute_indices(indices_t& indices, const offset_t& offset, const shape_t& shape, const strides_t& strides)
        {
            constexpr auto n = meta::len_v<shape_t>;
            constexpr auto m = meta::len_v<strides_t>;

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
                for (size_t i=0; i<len(shape); i++)
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
    constexpr auto compute_indices(const offset_t& offset, const shape_t& shape, const strides_t& strides)
    {
        using return_t = meta::resolve_optype_t<compute_indices_t,offset_t,shape_t,strides_t>;
        static_assert( !meta::is_void_v<return_t>
            , "unsupported return type for compute_indices" );
        auto indices = return_t{};
        if constexpr (meta::is_resizable_v<return_t>)
            indices.resize(len(shape));

        impl::compute_indices(indices, offset, shape, strides);

        return indices;
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
            constexpr auto DIM = len_v<shape_t>;
            [[maybe_unused]] constexpr auto B_DIM = bounded_size_v<shape_t>;
            using index_type = get_index_element_type_t<shape_t>;
            if constexpr (!is_index_array_v<shape_t>) {
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
            #if 0
            using type = transform_bounded_array_t<tuple_to_array_t<shape_t>>;
            // temporary workaround:
            // the element type may be constant index,
            // especially when shape is tuple with single element
            if constexpr (is_constant_index_array_v<shape_t>) {
                constexpr auto N = fixed_index_array_size_v<shape_t>;
                using result_t = make_array_type_t<size_t,N>;
                return as_value_v<result_t>;
            }
            // TODO: better deduction for clipped index
            else if constexpr (
                is_clipped_index_array_v<shape_t>
            ) {
                using type = resolve_optype_t<index::compute_indices_t,offset_t,decltype(to_value_v<shape_t>),strides_t>;
                return as_value_v<type>;
            }
            else return as_value_v<type>;
            #endif
        }();
        using type = type_t<remove_cvref_t<decltype(vtype)>>;
    }; // resolve_optype

} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP