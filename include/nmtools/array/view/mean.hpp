#ifndef NMTOOLS_ARRAY_VIEW_MEAN_HPP
#define NMTOOLS_ARRAY_VIEW_MEAN_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/divide.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/ref.hpp"
#include "nmtools/array/dtypes.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::meta
{
    // specific tag to promote mean
    struct promote_mean {};

    namespace error
    {
        template <typename...>
        struct PROMOTE_TYPE_MEAN_ERROR : detail::fail_t {};
    } // error

    /**
     * @brief Specialization of type promotion for mean op.
     * 
     * Prefer float32, even if bot reduced and divisor are both integer.
     * 
     * @tparam reduced_t 
     * @tparam divisor_t 
     */
    template <typename reduced_t, typename divisor_t>
    struct promote_types<promote_mean,reduced_t,divisor_t>
    {
        static constexpr auto vtype = [](){
            // TODO: follow numpy type promotion rules
            if constexpr (is_integer_v<reduced_t> && (is_integer_v<divisor_t> || is_integral_constant_v<divisor_t>)) {
                // mean op involves division, return float
                using type = dtype::float32_t;
                return as_value_v<type>;
            } else if constexpr (meta::is_same_v<reduced_t,double>) {
                // for double, just return double
                using type = dtype::float64_t;
                return as_value_v<type>;
            } else if constexpr (meta::is_same_v<reduced_t,float>) {
                using type = dtype::float32_t;
                return as_value_v<type>;
            } else {
                return as_value_v<error::PROMOTE_TYPE_MEAN_ERROR<reduced_t,divisor_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // promote_types
} // nmtools::meta

namespace nmtools::view::detail
{
    /**
     * @brief Compute the divisor for mean view.
     * 
     * Can also used for compute divisor for var view.
     * 
     * @tparam shape_t 
     * @tparam axis_t 
     * @param shape     original array shape
     * @param axis      desired axis
     * @return constexpr auto 
     */
    template <typename shape_t, typename axis_t>
    constexpr auto mean_divisor(const shape_t& shape, const axis_t& axis)
    {
        [[maybe_unused]] auto shape_ = [&](){
            if constexpr (meta::is_constant_index_array_v<shape_t>) {
                return meta::to_value_v<shape_t>;
            } else {
                return index::ref(shape);
            }
        }();
        if constexpr (is_none_v<axis_t>) {
            return index::product(shape);
        } else if constexpr (meta::is_index_array_v<axis_t>) {
            using index_t = meta::get_element_or_common_type_t<axis_t>;
            auto divisor = index_t{1};
            // TODO: decide what todo when shape is tuple
            if constexpr (meta::is_tuple_v<axis_t>) {
                constexpr auto N = meta::len_v<axis_t>;
                meta::template_for<N>([&](auto index){
                    auto idx = at(axis,index);
                    divisor *= static_cast<index_t>(at(shape_,idx));
                });
            } else {
                for (size_t i=0; i<len(axis); i++) {
                    auto idx = at(axis,i);
                    divisor *= at(shape_,idx);
                }
            }
            return divisor;
        } else /* if constexpr (meta::is_num_v<axis_t>) */ {
            return at(shape_,axis);
        }
    } // mean_divisor
}

namespace nmtools::view
{
    /**
     * @brief Returns mean view of an array, along the specified axis.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @tparam keepdims_t 
     * @param array     input array
     * @param axis      axis or axes along which the means are to be computed.
     * @param dtype     type to use to compute the means. 
     * @param keepdims  set if the reduced axis are to be kept.
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t, typename dtype_t=none_t, typename keepdims_t=meta::false_type>
    constexpr auto mean(const array_t& array, const axis_t& axis, dtype_t dtype=dtype_t{}, keepdims_t keepdims=keepdims_t{})
    {
        // note that this mean view is created not by create new view type,
        // but by composing two view (add.reduce + divide) instead

        auto shape = ::nmtools::shape<true>(array);
        // TODO: error handling
        auto divisor = detail::mean_divisor(unwrap(shape),axis);
        using divisor_t = decltype(divisor);
        using element_t = meta::get_element_type_t<array_t>;
        auto dtype_  = [&](){
            if constexpr (is_none_v<dtype_t>) {
                // explicitly promote using mean promotion rule
                using dtype = meta::promote_types_t<meta::promote_mean,element_t,divisor_t>;
                return dtype{};
            } else {
                return dtype;
            }
        }();
        auto initial = None;
        // TODO: proper type promotions
        auto reduced = reduce_add(array,axis,dtype_,initial,keepdims);
        #if 0
        // failed on clang with no-stl config, but okay on gcc with no-stl config 🤷
        auto mean_   = divide(reduced,divisor);
        return mean_;
        #else
        return divide(reduced,divisor);
        #endif
    } // mean
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_MEAN_HPP