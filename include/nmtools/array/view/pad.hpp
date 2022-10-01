#ifndef NMTOOLS_ARRAY_VIEW_PAD_HPP
#define NMTOOLS_ARRAY_VIEW_PAD_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/pad.hpp"
#include "nmtools/array/index/product.hpp"

namespace nmtools::view
{
    // only support constant pad for now
    enum class PADDING_MODE
    {
        CONSTANT,
    };

    /**
     * @brief Type constructor for pad view.
     * 
     * @tparam array_t 
     * @tparam pad_width_t 
     * @tparam value_t 
     */
    template <typename array_t, typename pad_width_t, typename value_t>
    struct pad_t
    {
        using array_type     = resolve_array_type_t<array_t>;
        using pad_width_type = resolve_attribute_type_t<pad_width_t>;
        using pad_value_type = resolve_attribute_type_t<value_t>;
        using value_type     = meta::get_element_type_t<array_t>;
        using src_shape_type = decltype(nmtools::shape</*force_constant_index*/true>(meta::declval<array_t>()));
        using dst_shape_type = meta::resolve_optype_t<index::shape_pad_t,src_shape_type,pad_width_t>;

        array_type     array;
        pad_width_type pad_width;
        pad_value_type pad_value;
        dst_shape_type shape_;

        // only support constant pad for now
        // TODO: add reflect and edge mode
        const PADDING_MODE mode = PADDING_MODE::CONSTANT;

        constexpr pad_t(const array_t& array_, const pad_width_t& pad_width, const value_t pad_value)
            : array(initialize(array_, meta::as_value_v<array_type>))
            , pad_width(init_attribute(pad_width, meta::as_value_v<pad_width_type>))
            , pad_value(init_attribute(pad_value, meta::as_value_v<pad_value_type>))
            , shape_(*index::shape_pad(nmtools::shape</*force_constant_index*/true>(array_),pad_width))
        {}
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            auto indices_   = pack_indices(indices...);
            auto tf_indices = index::pad(indices_,detail::shape(array),shape(),pad_width);

            // TODO: consider to provide view_at with either type [apply_at(...),value_type]
            // by doing so, it may help the evaluator dealing with inner loop
            if (static_cast<bool>(tf_indices)) {
                return static_cast<value_type>(detail::apply_at(array,*tf_indices));
            } else {
                return static_cast<value_type>(pad_value);
            }
        } // operator()
    }; // pad_t

    /**
     * @brief Create a padded view to an array.
     * 
     * @tparam array_t 
     * @tparam pad_width_t 
     * @tparam value_t 
     * @param array     input array
     * @param pad_width number of padding to be applied to each edge of the axes.
     * @param value     constant value
     * @return constexpr auto 
     */
    template <typename array_t, typename pad_width_t, typename value_t=float>
    constexpr auto pad(const array_t& array, const pad_width_t& pad_width, value_t value=static_cast<value_t>(0))
    {
        // TODO: error handling using maybe, check the shape, if success the proceed
        using view_t = decorator_t<pad_t,array_t,pad_width_t,value_t>;
        return view_t{{array,pad_width,value}};
    } // pad
} // namespace nmtools::view

namespace nmtools::meta
{
    /**
     * @brief Infer the dimension of pad view at compile-time.
     * 
     * @tparam array_t 
     * @tparam pad_width_t 
     * @tparam value_t 
     */
    template <typename array_t, typename pad_width_t, typename value_t>
    struct fixed_dim<
        view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >
    >
    {
        using view_type  = view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >;
        using dst_shape_type = typename view_type::dst_shape_type;

        static inline constexpr auto value = [](){
            // padding doesn't change dimension, only change shape
            #if 1
            if constexpr (is_fixed_index_array_v<dst_shape_type>) {
                return len_v<dst_shape_type>;
            } else {
                return error::FIXED_DIM_UNSUPPORTED<view_type>{};
            }
            #else
            if constexpr (is_fixed_dim_ndarray_v<array_t>) {
                return fixed_dim_v<array_t>;
            } else {
                return error::FIXED_DIM_UNSUPPORTED<view_type>{};
            }
            #endif
        }();
        using value_type = decltype(value);
        using type = value_type;
    }; // fixed_dim

    template <typename array_t, typename pad_width_t, typename value_t>
    struct fixed_size<
        view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >
    >
    {
        using view_type  = view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >;
        using dst_shape_type = typename view_type::dst_shape_type;

        static inline constexpr auto value = [](){
            // can only know the resulting size if the shape is constant
            // since pad width affect the shape
            if constexpr (is_constant_index_array_v<dst_shape_type>) {
                return index::product(dst_shape_type{});
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_size

    // NOTE: bounded size (but not fixed) is not possible because pad width changes shape
    template <typename array_t, typename pad_width_t, typename value_t>
    struct bounded_size<
        view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >
    > : fixed_size<
        view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >
    > {};

    template <typename array_t, typename pad_width_t, typename value_t>
    struct is_ndarray< view::decorator_t<view::pad_t, array_t, pad_width_t, value_t> >
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_VIEW_PAD_HPP