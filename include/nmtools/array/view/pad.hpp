#ifndef NMTOOLS_ARRAY_VIEW_PAD_HPP
#define NMTOOLS_ARRAY_VIEW_PAD_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/pad.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/view/indexing.hpp"
#include "nmtools/utils/isequal/isequal.hpp"
#include "nmtools/utils/isclose/isclose.hpp"
#include "nmtools/utils/to_string/to_string.hpp"

#if 1

namespace nmtools::view
{
    enum class PADDING_MODE
    {
        CONSTANT,
    };

    template <typename src_shape_t, typename pad_width_t, typename src_size_t>
    struct pad_t
        : base_indexer_t<pad_t<src_shape_t,pad_width_t,src_size_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using pad_width_type = meta::fwd_attribute_t<pad_width_t>;
        using dst_shape_type = meta::resolve_optype_t<index::shape_pad_t,src_shape_type,pad_width_type>;

        using src_size_type = src_size_t;
        using dst_size_type = decltype(unwrap(index::product(meta::declval<dst_shape_type>())));

        static constexpr auto n_inputs  = 2;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const pad_width_type pad_width;
        const dst_shape_type dst_shape;
        const src_size_type  src_size;
        const dst_size_type  dst_size;

        constexpr pad_t(const src_shape_t& src_shape
            , const pad_width_t& pad_width
            , src_size_t src_size
        )
            : src_shape(fwd_attribute(src_shape))
            , pad_width(fwd_attribute(pad_width))
            , dst_shape(unwrap(index::shape_pad(src_shape,pad_width)))
            , src_size(src_size)
            , dst_size(unwrap(index::product(dst_shape)))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::pad(indices,src_shape,dst_shape,pad_width);
            using src_indices_t = meta::get_maybe_type_t<decltype(src_indices)>;
            // TODO: change index::pad to return either<indices,None>
            using result_t = nmtools_either<src_indices_t,none_t>;
            if (src_indices) {
                return result_t{unwrap(src_indices)};
            } else {
                return result_t{None};
            }
        }

        template <typename...args_t>
        constexpr auto operator==(pad_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(pad_width,other.pad_width)
            ;
        }
    };

    template <typename src_shape_t, typename pad_width_t, typename src_size_t>
    constexpr auto padder(const src_shape_t& src_shape, const pad_width_t& pad_width, src_size_t src_size)
    {
        if constexpr (meta::is_maybe_v<src_shape_t>) {
            using result_t = decltype(padder(unwrap(src_shape),pad_width,src_size));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (src_shape
                ? return_t{padder(unwrap(src_shape),pad_width,src_size)}
                : return_t{meta::Nothing}
            );
        } else if constexpr (meta::is_maybe_v<pad_width_t>) {
            using result_t = decltype(padder(src_shape,unwrap(pad_width),src_size));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (pad_width
                ? return_t{padder(src_shape,unwrap(pad_width),src_size)}
                : return_t{meta::Nothing}
            );
        } else {
            [[maybe_unused]]
            auto dst_shape = index::shape_pad(src_shape,pad_width);
            if constexpr (meta::is_fail_v<decltype(dst_shape)>) {
                // let the caller handle type error
                return dst_shape;
            } else if constexpr (meta::is_maybe_v<decltype(dst_shape)>) {
                using result_t = decltype(pad_t{src_shape,pad_width,unwrap(src_size)});
                using return_t = nmtools_maybe<result_t>;
                return (dst_shape
                    ? return_t{pad_t{src_shape,pad_width,unwrap(src_size)}}
                    : return_t{meta::Nothing}
                );
            } else {
                return pad_t{src_shape,pad_width,unwrap(src_size)};
            }
        }
    } // padder

    template <typename array_t, typename pad_width_t, typename value_t=float>
    constexpr auto pad(const array_t& array, const pad_width_t& pad_width, value_t value=static_cast<value_t>(0))
    {
        auto f = [](const auto& array, const auto& pad_width, value_t value){
            using element_t = meta::get_element_type_t<meta::remove_cvref_t<decltype(array)>>;
            auto src_shape  = shape<true>(array);
            auto src_size   = size<true>(array);
            auto indexer    = padder(src_shape,pad_width,src_size);
            auto operands   = pack_operands(array,static_cast<element_t>(value));
            return indexing(operands,indexer);
        };
        return lift_indexing(f,array,pad_width,value);
    }
} // namespace nmtools::view

namespace nmtools::array
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::pad_t<args_t...>, max_dim
    > {
        using attribute_type = view::pad_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            auto pad_width = as_static<max_dim>(attribute.pad_width);
            auto src_size  = as_static<max_dim>(attribute.src_size);
            return view::padder(src_shape,pad_width,src_size);
        }
    };
} // namespace nmtools::array

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::pad_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::pad_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "pad";
            str += "{";
            str += ".src_shape=";
            str += to_string(kwargs.src_shape,Compact);
            str += ".pad_width=";
            str += to_string(kwargs.pad_width,Compact);
            str += ".src_size=";
            str += to_string(kwargs.src_size,Compact);
            str += "}";
            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#else

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

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        }

        constexpr auto attributes() const noexcept
        {
            return nmtools_tuple{pad_width,pad_value};
        }
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        nmtools_index_attribute
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
        #if !defined(NMTOOLS_NO_BASE_ACCESS)
        // TODO: error handling using maybe, check the shape, if success the proceed
        using view_t = decorator_t<pad_t,array_t,pad_width_t,value_t>;
        return view_t{{array,pad_width,value}};
        #else
        using array_type = meta::remove_address_space_t<array_t>;
        using view_t   = pad_t<array_type,pad_width_t,value_t>;
        using result_t = decorator_t<pad_t,array_type,pad_width_t,value_t>;
        return result_t{view_t{array,pad_width,value}};
        #endif
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
        using view_type = view::pad_t< array_t, pad_width_t, value_t >;
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
        using view_type = view::pad_t< array_t, pad_width_t, value_t >;
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

#endif

#endif // NMTOOLS_ARRAY_VIEW_PAD_HPP