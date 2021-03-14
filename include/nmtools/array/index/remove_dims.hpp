#ifndef NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP
#define NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/constants.hpp"

#include <cstddef>
#include <utility>

namespace nmtools::index
{
    struct remove_dims_t {};

    template <typename shape_t, typename axis_t, typename keepdims_t>
    constexpr auto remove_dims(const shape_t& shape, const axis_t& axis, keepdims_t keepdims)
    {
        // note: axis as reference to prevent raw array to ptr
        using return_t = meta::resolve_optype_t<remove_dims_t,shape_t,axis_t,keepdims_t>;
        auto res = return_t {};

        // number of axis to be removed
        // also take keepdims into accounts
        auto n = [&](){
            if constexpr (meta::is_index_array_v<axis_t>)
                return len(axis);
            else return 1;
        }();
        auto dim = len(shape);
        auto new_dim = [&](){
            if (static_cast<bool>(keepdims))
                return dim;
            else return dim-n;
        }();
        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(new_dim);

        // fn to check if given i is detected in axis
        // representing axis to be removed
        auto in_axis = [&](auto i){
            if constexpr (std::is_integral_v<axis_t>)
                return i==axis;
            else {
                auto f_predicate = [i](auto axis){
                    return i==axis;
                };
                auto found = where(f_predicate, axis);
                return static_cast<bool>(len(found));
            }
        };

        // res and shape have different size
        // index to fill res
        size_t idx = 0;
        for (size_t i=0; i<dim; i++) {
            auto in_axis_ = in_axis(i);
            if (in_axis_ && !keepdims)
                continue;
            else
                at(res,idx++) = in_axis_ ? 1 : at(shape,i);
        }

        return res;
    } // remove_dims

    template <typename shape_t, typename axis_t>
    constexpr auto remove_dims(const shape_t& shape, const axis_t& axis)
    {
        return remove_dims(shape,axis,False);
    } // remove_dims

} // namespace nmtools::index

namespace nmtools
{

    template <typename shape_t, typename axis_t, typename keepdims_t>
    struct meta::resolve_optype<
        std::enable_if_t<
            meta::is_index_array_v<shape_t>
            && !meta::is_fixed_index_array_v<shape_t>
        >,
        index::remove_dims_t, shape_t, axis_t, keepdims_t
    >
    {
        using type = shape_t;
    }; // resolve_optype remove_dims_t

    template <typename shape_t, typename axis_t, typename keepdims_t>
    struct meta::resolve_optype<
        std::enable_if_t<
            meta::is_index_array_v<shape_t>
            && meta::is_fixed_index_array_v<shape_t>
            && (meta::is_index_array_v<axis_t> || std::is_integral_v<axis_t>)
            && (std::is_integral_v<keepdims_t> || meta::is_integral_constant_v<keepdims_t>)
        >,
        index::remove_dims_t, shape_t, axis_t, keepdims_t
    >
    {
        static constexpr auto DIM = fixed_index_array_size_v<shape_t>;
        static constexpr auto N   = [](){
            // this is the number of axis to be removed at compile-time,
            // if required information is not available, make this 0 and
            // make the return type resizeable
            if constexpr (is_fixed_index_array_v<axis_t> && meta::is_integral_constant_v<keepdims_t>)
                return (keepdims_t::value ? 0 : fixed_index_array_size_v<axis_t>);
            else if constexpr (std::is_integral_v<axis_t> && meta::is_integral_constant_v<keepdims_t>)
                return (keepdims_t::value ? 0 : 1);
            else return 0;
        }();
        // keepdim at compile time:
        // if keepdims_t is compile-time constant, we can know in advance
        // otherwise, assume it's false and should return resizeable type
        // note that this keepdims options doesnt depend on axis param,
        // don't care if axis is integer or array, if keepdims is true,
        // the dimension will follow the original
        static constexpr auto KEEPDIMS = [](){
            if constexpr (meta::is_integral_constant_v<keepdims_t>)
                return keepdims_t::value;
            else return false;
        }();
        using common_t = meta::get_element_or_common_type_t<shape_t>;
        using fixed_array_t = std::array<common_t,DIM-N>;
        using hybrid_array_t = array::hybrid_ndarray<common_t,DIM,1>;
        // select fixed array if axis is fixed index array or is integral,
        // select hybrid array with DIM as upper-bound otherwise
        using type = std::conditional_t<
            KEEPDIMS, fixed_array_t, hybrid_array_t
        >;
    }; // resolve_optype remove_dims_t
} // namespace nmtools

#endif // NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP