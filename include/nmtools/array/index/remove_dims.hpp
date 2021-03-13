#ifndef NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP
#define NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"

#include <cstddef>
#include <utility>

namespace nmtools::index
{
    struct remove_dims_t {};

    template <typename shape_t, typename axis_t>
    constexpr auto remove_dims(const shape_t& shape, const axis_t& axis)
    {
        // note: axis as reference to prevent raw array to ptr
        using return_t = meta::resolve_optype_t<remove_dims_t,shape_t,axis_t>;
        auto res = return_t {};

        // number of axis to be removed
        auto n = [&](){
            if constexpr (meta::is_index_array_v<axis_t>)
                return len(axis);
            else return 1;
        }();
        auto dim = len(shape);
        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(dim-n);

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
            if (in_axis(i))
                continue;
            else at(res,idx++) = at(shape,i);
        }

        return res;
    } // remove_dims

} // namespace nmtools::index

namespace nmtools
{

    template <typename shape_t, typename axis_t>
    struct meta::resolve_optype<
        std::enable_if_t<
            meta::is_index_array_v<shape_t>
            && !meta::is_fixed_index_array_v<shape_t>
        >,
        index::remove_dims_t, shape_t, axis_t
    >
    {
        using type = shape_t;
    }; // resolve_optype remove_dims_t

    template <typename shape_t, typename axis_t>
    struct meta::resolve_optype<
        std::enable_if_t<
            meta::is_index_array_v<shape_t>
            && meta::is_fixed_index_array_v<shape_t>
            && (meta::is_index_array_v<axis_t> || std::is_integral_v<axis_t>)
        >,
        index::remove_dims_t, shape_t, axis_t
    >
    {
        static constexpr auto DIM = fixed_index_array_size_v<shape_t>;
        static constexpr auto N   = [](){
            if constexpr (is_fixed_index_array_v<axis_t>)
                return fixed_index_array_size_v<axis_t>;
            else if constexpr (std::is_integral_v<axis_t>)
                return 1;
            else return 0;
        }();
        using common_t = meta::get_element_or_common_type_t<shape_t>;
        using fixed_array_t = std::array<common_t,DIM-N>;
        using hybrid_array_t = array::hybrid_ndarray<common_t,DIM,1>;
        // select fixed array if axis is fixed index array or is integral,
        // select hybrid array with DIM as upper-bound otherwise
        using type = std::conditional_t<
            meta::is_fixed_index_array_v<axis_t> || std::is_integral_v<axis_t>,
            fixed_array_t, hybrid_array_t
        >;
    }; // resolve_optype remove_dims_t
} // namespace nmtools

#endif // NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP