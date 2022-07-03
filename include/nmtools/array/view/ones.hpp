#ifndef NMTOOLS_ARRAY_VIEW_ONES_HPP
#define NMTOOLS_ARRAY_VIEW_ONES_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    namespace detail
    {
        // TODO: remove
        template <typename shape_t>
        constexpr auto get_ones_shape(const shape_t& shape)
        {
            static_assert (meta::is_index_array_v<shape_t>
                , "unsupported ones shape, expects index array"
            );
            using return_t = meta::transform_bounded_array_t<
                meta::tuple_to_array_t<shape_t>
            >;
            auto res = return_t{};

            [[maybe_unused]] const auto n = len(shape);
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
        } // get_ones_shape
    }

    template <typename shape_t, typename T>
    struct ones_t
    {
        using shape_type   = resolve_attribute_type_t<shape_t>;
        using element_type = T;

        using array_type = none_t;

        shape_type shape_;

        constexpr ones_t(const shape_t& shape)
            : shape_(init_attribute<shape_type>(shape)) {}
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape_);
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types.../*indices*/) const
        {
            // TODO: assert if indices < shape

            return static_cast<element_type>(1);
        } // operator()
    }; // ones_t

    /**
     * @brief Creates a ones view with given shape and dtype.
     * 
     * All elements in the view has value of 1.
     * 
     * @tparam shape_t 
     * @tparam T 
     * @param shape desired shape
     * @return constexpr auto 
     */
    template <typename shape_t, typename T>
    constexpr auto ones(const shape_t& shape, dtype_t<T>)
    {
        using view_t = decorator_t<ones_t, shape_t, T>;
        return view_t{{shape}};
    } // ones
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename shape_t, typename T>
    struct get_element_type< view::decorator_t<view::ones_t, shape_t, T> >
    {
        using type = T;
    };

    // TODO: remove
    template <typename shape_t, typename T>
    struct fixed_ndarray_shape< view::ones_t<shape_t, T> >
        : fixed_shape< view::ones_t<shape_t, T> > {};
    #if 0
    {
        static inline constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_t>)
                return view::detail::get_ones_shape(shape_t{});
            else
                return detail::fail_t{};
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape
    #endif

    template <typename shape_t, typename T>
    struct is_ndarray< view::decorator_t< view::ones_t, shape_t, T >>
    {
        static constexpr auto value = is_num_v<T>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ONES_HPP