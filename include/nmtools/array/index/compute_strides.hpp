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
            constexpr auto vtype = [](){
                using value_type = meta::apply_t<std::common_type,array_t>;
                if constexpr (meta::is_integral_constant_v<value_type>)
                    return meta::as_value_v<typename value_type::value_type>;
                else return meta::as_value_v<value_type>;
            }();
            using value_type = meta::type_t<decltype(vtype)>;
            static_assert( meta::is_integral_constant_v<size_type>
                , "unsupported size_type for stride. for tuple type, k must be integral constant"
            );
            constexpr auto n = std::tuple_size_v<array_t>;
            auto p = value_type{1};
            meta::template_for<n>([&](auto index){
                constexpr auto i = decltype(index)::value;
                // k cant be used in constant expression
                if (i>=k+1)
                    p *= std::get<i>(shape);
            });
            return p;
        }
        else
        {
            constexpr auto vtype = [](){
                using value_type = meta::get_element_type_t<array_t>;
                if constexpr (meta::is_integral_constant_v<value_type>)
                    return meta::as_value_v<typename value_type::value_type>;
                else return meta::as_value_v<value_type>;
            }();
            using value_type = meta::type_t<decltype(vtype)>;
            auto p = value_type{1};
            for (auto j=k+1; j<len(shape); j++)
                p *= at(shape,j);
            return p;
        }
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
    constexpr auto compute_strides(const array_t& shape)
    {
        // handle if all elements in array_t is integral_constant
        // return type can not have same type as shape, assignment is not available
        // convert to value and then compute
        if constexpr (meta::is_constant_index_array_v<array_t>)
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
            using element_t = meta::get_element_or_common_type_t<array_t>;
            using return_t  = meta::resolve_optype_t<compute_strides_t,array_t>;
            // for now compute_strides only support integral, not index
            // TODO: may be support index
            static_assert( std::is_integral_v<element_t>
                , "unsupported compute_strides" );
            auto strides_ = return_t{};
            if constexpr (meta::is_resizeable_v<return_t>)
                strides_.resize(len(shape));
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
                for (size_t i=0; i<len(strides_); i++)
                    at(strides_,i) = stride(shape,i);
            return strides_;
        }       
    } // strides
} // namespace nmtools::index

namespace nmtools::meta
{

    template <typename shape_t>
    struct resolve_optype<
        void, index::compute_strides_t, shape_t
    >
    {
        static constexpr auto vtype = [](){
            using type = tuple_to_array_t<transform_bounded_array_t<shape_t>>;
            // temporary workaround:
            // the element type may be constant index,
            // especially when shape is tuple with single element
            if constexpr (is_constant_index_array_v<shape_t>) {
                constexpr auto N = fixed_index_array_size_v<shape_t>;
                using result_t = std::array<size_t,N>;
                return as_value_v<result_t>;
            }
            else return as_value_v<type>;
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_STRIDES_HPP