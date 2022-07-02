#ifndef NMTOOLS_ARRAY_VIEW_RESHAPE_HPP
#define NMTOOLS_ARRAY_VIEW_RESHAPE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/flatten.hpp"

#include "nmtools/array/index/reshape.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/assert.hpp"

#include "nmtools/utils/isequal.hpp"

namespace nmtools::view
{
    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */
    
    /**
     * @brief reshape view type
     * 
     * @tparam array_t type of array to be reshaped
     * @tparam shape_t type of new shape
     */
    template <typename array_t, typename shape_t>
    struct reshape_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = resolve_array_type_t<array_t>;
        using shape_type = resolve_attribute_type_t<shape_t>;
        
        array_type array;
        shape_type new_shape;

        /**
         * @brief construct reshape view
         * 
         */
        constexpr reshape_t(const array_t& array, const shape_t& shape)
            : array(initialize(array, meta::as_value_v<array_type>))
            , new_shape(init_attribute(shape, meta::as_value_v<shape_type>)) {}
        
        /**
         * @brief simply return size of new_shape
         * 
         * @return constexpr auto 
         */
        constexpr auto dim() const noexcept
        {
            return len(new_shape);
        } // dim
        
        /**
         * @brief simply return new_shape
         * 
         * @return constexpr decltype(auto) 
         */
        constexpr decltype(auto) shape() const noexcept
        {
            // NOTE: must normalize raw bounded array
            return new_shape;
        } // shape

        /**
         * @brief index transformer for reshape view
         * 
         * @tparam size_types
         * @param indices variadic of integral type or single packed indices
         * @return constexpr auto transformed indices, mapped to original array shape
         */
        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);
            auto shape_   = detail::shape(array); // src shape
            auto strides  = index::compute_strides(new_shape);
            auto offset   = index::compute_offset(indices_,strides);
            auto tf_idx   = index::compute_indices(offset,shape_);
            return tf_idx;
        } // index
    }; // reshape_t

    /**
     * @brief return reshape view
     * 
     * @tparam array_t 
     * @tparam shape_t 
     * @param array array to be reshaped
     * @param new_shape 
     * @return constexpr auto reshape view
     */
    template <typename array_t, typename shape_t>
    constexpr auto reshape(const array_t& array, const shape_t& new_shape)
    {
        auto new_shape_ = [&](){
            if constexpr (meta::is_fixed_size_ndarray_v<array_t> && meta::is_constant_index_array_v<shape_t>) {
                constexpr auto shape_ = meta::fixed_ndarray_shape_v<array_t>;
                constexpr auto m_result = index::shape_reshape(shape_,shape_t{});
                if constexpr (meta::is_maybe_v<decltype(m_result)>) {
                    static_assert( static_cast<bool>(m_result), "cannot reshape array");
                }
                constexpr auto result = [&](){
                    if constexpr (meta::is_maybe_v<decltype(m_result)>) {
                        return *m_result;
                    } else {
                        return m_result;
                    }
                }();
                // NOTE: using this triggers internal compiler error for gcc (9.4.0)
                // internal compiler error: in lookup_template_class_1, at cp/pt.c:9897
                // https://github.com/alifahrri/nmtools/runs/5617131903?check_suite_focus=true
                // TODO: enable compile-time shape inference for GCC
                #ifdef __clang__
                {
                    using nmtools::none_t;
                    constexpr auto DIM = nmtools::len(result);
                    using index_t = decltype(DIM);
                    constexpr auto vtype = meta::template_reduce<DIM>([&](auto init, auto index){
                        using init_t = meta::type_t<decltype(init)>;
                        if constexpr (meta::is_same_v<init_t,none_t>) {
                            using type = nmtools_tuple<meta::ct<(index_t)at(result,index)>>;
                            return meta::as_value_v<type>;
                        } else {
                            using type = meta::append_type_t<init_t,meta::ct<(index_t)at(result,index)>>;
                            return meta::as_value_v<type>;
                        }
                    }, meta::as_value_v<none_t>);
                    return meta::type_t<decltype(vtype)>{};
                }
                #else
                return result;
                #endif
            } else {
                return index::shape_reshape(shape(array),new_shape);
            }
        }();
        using new_shape_t = decltype(new_shape_);
        // TODO: consider to make the return type as maybe type instead, when runtime check is needed
        if constexpr (meta::is_maybe_v<new_shape_t>) {
            // TODO: better error handling
            nmtools_assert( static_cast<bool>(new_shape_)
                , "unsupported reshape, mismatched number of elements"
            );
            using m_shape_t = meta::get_maybe_type_t<new_shape_t>;
            return decorator_t<reshape_t,array_t,m_shape_t>{{array,*new_shape_}};
        } else {
            return decorator_t<reshape_t,array_t,new_shape_t>{{array,new_shape_}};
        }
    } // reshape

    /** @} */ // end group view

} // namespace nmtools::view

namespace nmtools
{
    /**
     * @brief specialization fo is_ndarray for reshape view
     *
     * Note that this specialization bypass the specialization from decorator_t
     * by being more specific on view_t (reshape_t in this case)
     * 
     * @tparam array_t referenced array of reshape view
     * @tparam shape_t type of new shape of reshape view
     */
    template <typename array_t, typename shape_t>
    struct meta::is_ndarray< view::decorator_t<view::reshape_t, array_t, shape_t> >
    {
        static constexpr auto value = meta::is_ndarray_v<meta::remove_cvref_t<array_t>>;
        using value_type = decltype(value);
    }; // is_ndarray

    /**
     * @brief specialization of meta::fixed_ndarray_shape for reshape view
     *
     * Enabled for fixed size ndarray.
     * Results in fail_t when shape_t is not integral_constant.
     * 
     * @tparam array_t 
     * @tparam shape_t 
     */
    template <typename array_t, typename shape_t>
    struct meta::fixed_ndarray_shape<
        view::reshape_t< array_t, shape_t>
    >
    {
        static constexpr auto value = []()
        {
            // for now, simply return the new shape
            // when both src shape and dst shape is known at compile time.
            // it should be possible to allow array with runtime shape
            // to be reshaped with fixed shape.
            if constexpr (is_fixed_size_ndarray_v<array_t> && (is_constant_index_v<shape_t> || is_constant_index_array_v<shape_t>)) {
                return shape_t{};
            } else {
                return detail::Fail;
            }
        }();
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
    }; // fixed_ndarray_shape

} // namespace nmtools

namespace nmtools::meta
{
    template <typename array_t, typename shape_t>
    struct fixed_dim<
        view::decorator_t<view::reshape_t, array_t, shape_t>
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_fixed_index_array_v<shape_t>) {
                return len_v<shape_t>;
            } else {
                return detail::Fail;
            }
        }();
        using value_type = decltype(value);
    };

    template <typename array_t, typename shape_t>
    struct hybrid_ndarray_max_size<
        view::decorator_t< view::reshape_t, array_t, shape_t >
    >
    {
        static constexpr auto value = [](){
            // NOTE: reshape doesn't change number of elements, runtime error handled at runtime.
            // only enable if fixed dim because of current eval type inference implementation
            // TODO: also enable if not fixed dim
            if constexpr (is_hybrid_ndarray_v<array_t> && is_fixed_index_array_v<shape_t>) {
                return hybrid_ndarray_max_size_v<array_t>;
            } else if constexpr (is_fixed_size_ndarray_v<array_t> && is_fixed_index_array_v<shape_t>) {
                constexpr auto shape = fixed_ndarray_shape_v<array_t>;
                return index::product(shape);
            } else {
                return detail::Fail;
            }
        }();
        using value_type = decltype(value);
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_RESHAPE_HPP