#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_STRIDES_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_STRIDES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::index
{
    // tag to resolve stride return type
    struct stride_t {};

    /**
     * @brief compute stride for ndarray offset
     * 
     * @param shape container of shape, should have value_type member type
     * @param k k-th stride to compute
     * @return constexpr auto
     */
    template <typename array_t, typename m_size_type>
    nmtools_index_attribute
    constexpr auto stride(const array_t& shape, m_size_type k)
    {
        using result_t = meta::resolve_optype_t<stride_t,array_t,m_size_type>;
        using size_type = size_t;
        auto p = result_t {};
        if constexpr (!meta::is_constant_index_v<result_t>) {
            constexpr auto n = meta::len_v<array_t>;
            p = 1;
            if constexpr (n > 0) {
                // note that k may be runtime value
                meta::template_for<n>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    if ((size_type)i>=(size_type)(k+1))
                        p *= at<i>(shape);
                });
            } else {
                for (size_type j=k+1; j<(size_type)len(shape); j++) {
                    p *= at(shape,j);
                }
            }
        }
        return p;
    } // stride

    /**
     * @brief specific tag to resolve return type of compute_strides
     * 
     */
    struct compute_strides_t {};

    /**
     * @brief compute stride for ndarray offset.
     *
     * This follows numpy's row-major
     * <a href="https://numpy.org/doc/stable/reference/arrays.ndarray.html#internal-memory-layout-of-an-ndarray">stride computation</a>.
     * 
     * @param shape container of shape, should have value_type member type
     * @return constexpr auto
     */
    template <typename array_t>
    nmtools_index_attribute
    constexpr auto compute_strides(const array_t& shape)
    {
        using return_t  = meta::resolve_optype_t<compute_strides_t,array_t>;
        // assume when return_t is maybe then shape_t is also maybe
        if constexpr (meta::is_maybe_v<return_t>) {
            if (static_cast<bool>(shape)) {
                auto result = compute_strides(*shape);
                return return_t{result};
            } else {
                return return_t{meta::Nothing};
            }
        } else {
            using size_type = size_t;
            auto strides_ = return_t{};
            if constexpr (!meta::is_constant_index_array_v<return_t> && meta::is_index_array_v<return_t>) {
                [[maybe_unused]] auto n = (size_type)len(shape);
                if constexpr (meta::is_resizable_v<return_t>) {
                    strides_.resize(n);
                }
                constexpr auto N = meta::len_v<return_t>;
                if constexpr (N>0) {
                    // this may be clipped shape
                    meta::template_for<N>([&](auto i){
                        at(strides_,i) = stride(shape,i);
                    });
                } else {
                    for (size_type i=0; i<n; i++) {
                        at(strides_,i) = stride(shape,i);
                    }
                }
            }
            return strides_;
        }
    } // compute_strides
} // namespace nmtools::index

namespace nmtools::meta
{

    namespace error
    {
        template <typename...>
        struct INDEX_COMPUTE_STRIDE_UNSUPPORTED : detail::fail_t{};
    } // namespace error
    
    template <typename shape_t>
    struct resolve_optype<
        void, index::compute_strides_t, shape_t
    >
    {
        static constexpr auto vtype = [](){
            [[maybe_unused]] constexpr auto DIM = len_v<shape_t>;
            using index_type [[maybe_unused]] = get_index_element_type_t<shape_t>;
            if constexpr (is_maybe_v<shape_t>) {
                using shape_type = remove_cvref_t<get_maybe_type_t<shape_t>>;
                using type = nmtools_maybe<resolve_optype_t<index::compute_strides_t,shape_type>>;
                return as_value_v<type>;
            } else
            if constexpr (
                (DIM > 0)
                && (is_constant_index_array_v<shape_t>
                    || is_clipped_index_array_v<shape_t>)
            ) {
                constexpr auto shape = to_value_v<shape_t>;
                constexpr auto strides = index::compute_strides(shape);
                // convert back to type
                constexpr auto N = ::nmtools::len(strides);
                using nmtools::at;
                return template_reduce<N>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = at(strides,index);
                    if constexpr (is_constant_index_array_v<shape_t>) {
                        using result_t = append_type_t<init_t,ct<I>>;
                        return as_value_v<result_t>;
                    } else {
                        using result_t = append_type_t<init_t,clipped_size_t<I>>;
                        return as_value_v<result_t>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_clipped_index_array_v<shape_t>) {
                return as_value_v<nmtools_list<index_type>>;
            } else if constexpr (is_index_array_v<shape_t>) {
                [[maybe_unused]] constexpr auto B_DIM = bounded_size_v<shape_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<index_type,DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    // TODO: provide macro nmtools_static_vector
                    using type = utl::static_vector<index_type,B_DIM>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<index_type>;
                    return as_value_v<type>;
                }
                #if 0
                // some fn may produce tuple of (runtime) index,
                // also shape may be raw array
                using type [[maybe_unused]] = tuple_to_array_t<transform_bounded_array_t<shape_t>>;
                return as_value_v<type>;
                #endif
            } else {
                // forwarding params may be helpful for testing/debugging
                return as_value_v<error::INDEX_COMPUTE_STRIDE_UNSUPPORTED<shape_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype

    namespace error
    {
        struct INDEX_STRIDE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename array_t, typename size_type>
    struct resolve_optype<
        void, index::stride_t, array_t, size_type
    >
    {
        static constexpr auto vtype = [](){
            using element_t = get_element_or_common_type_t<array_t>;
            if constexpr (is_constant_index_array_v<array_t> && is_constant_index_v<size_type>) {
                constexpr auto array = to_value_v<array_t>;
                constexpr auto k = to_value_v<size_type>;
                constexpr auto stride = index::stride(array,k);
                // convert back to type
                return as_value_v<ct<stride>>;
            } else if constexpr (is_constant_index_v<element_t>) {
                return as_value_v<typename element_t::value_type>;
            } else if constexpr (is_clipped_integer_v<element_t>) {
                return as_value_v<typename element_t::value_type>;
            } else if constexpr (is_index_v<element_t>) {
                return as_value_v<element_t>;
            } else {
                return as_value_v<error::INDEX_STRIDE_UNSUPPORTED>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_STRIDES_HPP