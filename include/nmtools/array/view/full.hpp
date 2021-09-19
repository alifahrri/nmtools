#ifndef NMTOOLS_ARRAY_VIEW_FULL_HPP
#define NMTOOLS_ARRAY_VIEW_FULL_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/shape.hpp"

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    namespace detail
    {
        template <typename shape_t>
        constexpr auto get_full_shape(const shape_t& shape)
        {
            static_assert (meta::is_index_array_v<shape_t>
                , "unsupported full shape, expects index array"
            );
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
        } // get_full_shape
    }

    /**
     * @brief view object to represent array with fill_value.
     * 
     * @tparam shape_t 
     * @tparam fill_value_t 
     */
    template <typename shape_t, typename fill_value_t>
    struct full_t
    {
        using shape_type = const shape_t&;
        using fill_value_type = fill_value_t;
        using element_type = fill_value_type;

        using array_type = none_t;

        shape_type shape_;
        fill_value_type fill_value;

        constexpr full_t(const shape_t& shape, fill_value_type fill_value)
            : shape_(shape), fill_value(fill_value) {}
        
        constexpr auto shape() const
        {
            // may transform raw array to std::array
            return detail::get_full_shape(shape_);
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

            return fill_value;
        } // operator()
    }; // full_t

    /**
     * @brief Creates a view that returns specified fill_value with given shape.
     * 
     * @tparam shape_t 
     * @tparam fill_value_t 
     * @param shape 
     * @param fill_value fill value
     * @return constexpr auto 
     */
    template <typename shape_t, typename fill_value_t>
    constexpr auto full(const shape_t& shape, fill_value_t fill_value)
    {
        using view_t = decorator_t<full_t, shape_t, fill_value_t>;
        return view_t{{shape, fill_value}};
    } // full
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename shape_t, typename fill_value_t>
    struct get_element_type< view::decorator_t<view::full_t, shape_t, fill_value_t> >
    {
        using type = fill_value_t;
    };

    template <typename shape_t, typename fill_value_t>
    struct fixed_ndarray_shape< view::full_t<shape_t, fill_value_t> >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_t>)
                return view::detail::get_full_shape(shape_t{});
            else
                return detail::fail_t{};
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename shape_t, typename fill_value_t>
    struct is_ndarray< view::decorator_t< view::full_t, shape_t, fill_value_t >>
    {
        static constexpr auto value = std::is_arithmetic_v<fill_value_t> && is_index_array_v<shape_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_FULL_HPP