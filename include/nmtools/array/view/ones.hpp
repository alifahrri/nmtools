#ifndef NMTOOLS_ARRAY_VIEW_ONES_HPP
#define NMTOOLS_ARRAY_VIEW_ONES_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    template <typename shape_t, typename T>
    struct ones_t
    {
        using shape_type   = resolve_attribute_type_t<shape_t>;
        using element_type = T;

        // TODO: rename array_type to operand_type
        using array_type = nmtools_tuple<>;

        shape_type shape_;
        array_type array{};

        constexpr ones_t(const shape_t& shape)
            : shape_(init_attribute<shape_type>(shape))
        {}

        constexpr auto attributes() const
        {
            return nmtools_tuple{shape_,dtype_t<T>{}};
        }
        
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

    template <typename shape_t, typename T>
    struct fixed_size<
        view::decorator_t<view::ones_t,shape_t,T>
    > {
        using view_type  = view::decorator_t<view::ones_t,shape_t,T>;
        using shape_type = typename view_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                constexpr auto shape = to_value_v<shape_type>;
                return index::product(shape);
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    };

    template <typename shape_t, typename T>
    struct fixed_shape<
        view::decorator_t<view::ones_t,shape_t,T>
    > {
        using view_type  = view::decorator_t<view::ones_t,shape_t,T>;
        using shape_type = typename view_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                constexpr auto shape = to_value_v<shape_type>;
                return shape;
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<view_type>{};
            }
        }();
    };

    template <typename shape_t, typename T>
    struct bounded_size<
        view::decorator_t<view::ones_t,shape_t,T>
    > {
        using view_type  = view::decorator_t<view::ones_t,shape_t,T>;
        using shape_type = typename view_type::shape_type;

        static constexpr auto value = [](){
            constexpr auto shape = to_value_v<shape_type>;
            if constexpr (!is_fail_v<decltype(shape)>) {
                return index::product(shape);
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    };

    template <typename shape_t, typename T>
    struct is_ndarray< view::decorator_t< view::ones_t, shape_t, T >>
    {
        static constexpr auto value = is_num_v<T>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ONES_HPP