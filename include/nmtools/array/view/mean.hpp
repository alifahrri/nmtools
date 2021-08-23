#ifndef NMTOOLS_ARRAY_VIEW_MEAN_HPP
#define NMTOOLS_ARRAY_VIEW_MEAN_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/divide.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/dtypes.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::meta
{
    // specific tag to promote mean
    struct promote_mean {};

    namespace error {
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
            if constexpr (is_integer_v<reduced_t> && is_integer_v<divisor_t>) {
                // mean op involves division, return float
                using type = dtype::float32_t;
                return as_value_v<type>;
            } else if constexpr (std::is_same_v<reduced_t,double>) {
                // for double, just return double
                using type = dtype::float64_t;
                return as_value_v<type>;
            } else if constexpr (std::is_same_v<reduced_t,float>) {
                using type = dtype::float32_t;
                return as_value_v<type>;
            } else {
                return as_value_v<error::PROMOTE_TYPE_MEAN_ERROR>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // promote_types
} // nmtools::meta

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
    template <typename array_t, typename axis_t, typename dtype_t=none_t, typename keepdims_t=std::false_type>
    constexpr auto mean(const array_t& array, const axis_t& axis, dtype_t dtype=dtype_t{}, keepdims_t keepdims=keepdims_t{})
    {
        // note that this mean view is created not by create new view type,
        // but by composing two view (add.reduce + divide) instead

        auto divisor = [&](){
            auto shape = ::nmtools::shape(array);
            if constexpr (is_none_v<axis_t>) {
                return index::product(shape);
            } else {
                return at(shape,axis);
            }
        }();
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
        auto mean_   = divide(reduced,divisor);
        return mean_;
    } // mean
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_MEAN_HPP