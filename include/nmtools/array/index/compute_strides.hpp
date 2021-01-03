#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_STRIDES_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_STRIDES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <tuple>

namespace nmtools::index
{
    /**
     * @brief compute stride for ndarray offset
     * 
     * @param shape container of shape, should have value_type member type
     * @param k k-th stride to compute
     * @return constexpr auto
     */
    template <typename array_t, typename size_type>
    constexpr auto stride(const array_t& shape, size_type k)
    {
        if constexpr (meta::is_specialization_v<array_t,std::tuple> || meta::is_specialization_v<array_t,std::pair>)
        {
            using value_type = meta::apply_t<std::common_type,array_t>;
            static_assert( meta::is_integral_constant_v<size_type>
                , "unsupported size_type for stride. for tuple type, k must be integral constant"
            );
            constexpr auto n = std::tuple_size_v<array_t>;
            auto p = value_type{1};
            meta::template_for<n>([&](auto index){
                constexpr auto i = decltype(index)::value;
                if constexpr (i>=k+1)
                    p *= std::get<i>(shape);
            });
            return p;
        }
        else
        {
            using value_type = typename std::decay_t<decltype(shape)>::value_type;
            auto p = value_type{1};
            for (auto j=k+1; j<tuple_size(shape); j++)
                p *= at(shape,j);
            return p;
        }
    } // stride

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
    constexpr auto compute_strides(const array_t& shape)
    {
        // handle if all elements in array_t is integral_constant
        // return type can not have same type as shape, assignment is not available
        // convert to value and then compute
        if constexpr (meta::apply_logical_and_v<meta::is_integral_constant,array_t>)
        {
            constexpr auto shape_   = meta::constant_to_value<array_t>::value;
            constexpr auto strides_ = compute_strides(shape_);
            // @todo value_to_constant
            return strides_;
        }
        // otherwise value of array_t is only known at runtime
        // return type can have same type as shape, assignment is ok
        else
        {
            auto strides_ = shape;
            if constexpr (meta::is_specialization_v<array_t,std::tuple> || meta::is_specialization_v<array_t,std::pair>)
            {
                constexpr auto n = std::tuple_size_v<array_t>;
                meta::template_for<n>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    auto k = std::integral_constant<size_t,i>{};
                    std::get<i>(strides_) = stride(shape, k);
                });
            }
            else
                for (size_t i=0; i<tuple_size(strides_); i++)
                    at(strides_,i) = stride(shape,i);
            return strides_;
        }       
    } // strides
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_STRIDES_HPP