#ifndef NMTOOLS_ARRAY_VIEW_ZEROS_HPP
#define NMTOOLS_ARRAY_VIEW_ZEROS_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    namespace detail
    {
        template <typename shape_t>
        constexpr auto get_zeros_shape(const shape_t& shape)
        {
            using return_t = meta::transform_bounded_array_t<
                meta::tuple_to_array_t<shape_t>
            >;
            auto res = return_t{};

            const auto n = len(shape);
            if constexpr (meta::is_resizeable_v<return_t>)
                res.resize(n);
            
            if constexpr (meta::is_constant_index_array_v<shape_t>) {
                constexpr auto N = meta::fixed_index_array_size_v<shape_t>;
                meta::template_for<N>([&](auto i){
                    at(res,i) = at(shape,i);
                });
            }
            else
                for (size_t i=0; i<n; i++)
                    at(res,i) = at(shape,i);

            return res;
        } // get_zeros_shape
    }

    template <typename shape_t, typename T>
    struct zeros_t
    {
        using shape_type = const shape_t&;
        using element_type = T;

        using array_type = none_t;

        shape_type shape_;

        constexpr zeros_t(const shape_t& shape)
            : shape_(shape) {}
        
        constexpr auto shape() const
        {
            return detail::get_zeros_shape(shape_);
        } // shape

        constexpr auto dim() const
        {
            return len(shape_);
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            using ::nmtools::index::make_array;
            using common_t = std::common_type_t<size_types...>;
            auto indices_ = [&](){
                // handle non-packed indices
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                // handle packed indices, number of indices must be 1
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for broadcast_to view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();

            // TODO: assert if indices < shape

            return static_cast<element_type>(0);
        } // operator()
    }; // zeros_t

    /**
     * @brief Creates zeros view with given shape and dtype.
     *
     * All elements of this views has value of 0.
     * 
     * @tparam shape_t 
     * @tparam T 
     * @param shape 
     * @return constexpr auto 
     */
    template <typename shape_t, typename T>
    constexpr auto zeros(const shape_t& shape, dtype_t<T>)
    {
        using view_t = decorator_t<zeros_t, shape_t, T>;
        return view_t{{shape}};
    } // zeros
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename shape_t, typename T>
    struct get_element_type< view::decorator_t<view::zeros_t, shape_t, T> >
    {
        using type = T;
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename shape_t, typename T>
    struct fixed_matrix_size< view::zeros_t<shape_t, T> >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_t>) {
                if constexpr (fixed_index_array_size_v<shape_t> == 2)
                    return fixed_ndarray_shape_v<shape_t>;
                else return detail::fail_t{};
            }
            return detail::fail_t{};
        }();
        using value_type = decltype(value);
    };

    template <typename shape_t, typename T>
    struct fixed_vector_size< view::zeros_t<shape_t, T> >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_t>) {
                if constexpr (fixed_index_array_size_v<shape_t> == 1)
                    return fixed_ndarray_shape_v<shape_t>;
                else return detail::fail_t{};
            }
            return detail::fail_t{};
        }();
        using value_type = decltype(value);
    };

    template <typename shape_t, typename T>
    struct fixed_ndarray_shape< view::zeros_t<shape_t, T> >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_t>)
                return view::detail::get_zeros_shape(shape_t{});
            else
                return detail::fail_t{};
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename shape_t, typename T>
    struct is_ndarray< view::decorator_t< view::zeros_t, shape_t, T >>
    {
        static constexpr auto value = std::is_arithmetic_v<T>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ZEROS_HPP