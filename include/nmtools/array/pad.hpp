#ifndef NMTOOLS_ARRAY_PAD_HPP
#define NMTOOLS_ARRAY_PAD_HPP

#include "nmtools/core/decorator.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/index/pad.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/utility/isequal/isequal.hpp"
#include "nmtools/utility/isclose/isclose.hpp"
#include "nmtools/utility/to_string/to_string.hpp"

namespace nmtools::index
{
    struct parse_pad_width_t {};

    template <typename pad_width_t>
    constexpr auto parse_pad_width(const pad_width_t& pad_width)
    {
        if constexpr (meta::is_maybe_v<pad_width_t>) {

        } else {
            using result_t = meta::resolve_optype_t<parse_pad_width_t,pad_width_t>;

            auto result = result_t {};

            if constexpr (!meta::is_constant_index_array_v<result_t>
                && !meta::is_fail_v<result_t>
            ) {
                const auto pad_shape = shape(pad_width);
                const auto pad_size = nmtools::size(pad_width);

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(pad_size);
                }

                // assume pad_shape[1] == 2
                // TODO: handle error

                const auto src_dim = at(pad_shape,0);
                for (nm_size_t i=0; i<(nm_size_t)src_dim; i++) {
                    at(result,i) = at(pad_width,i,0);
                }
                for (nm_size_t i=src_dim; i<(nm_size_t)src_dim*2; i++) {
                    at(result,i) = at(pad_width,i-src_dim,1);
                }
            }
            
            return result;
        }
    }
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct PARSE_PAD_WIDTH_UNSUPPORTED : detail::fail_t {};
    }

    template <typename pad_width_t>
    struct resolve_optype<
        void, index::parse_pad_width_t, pad_width_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_ndarray_v<pad_width_t>) {
                using type = error::PARSE_PAD_WIDTH_UNSUPPORTED<pad_width_t>;
                return as_value_v<type>;
            } else {
                constexpr auto FIXED_SIZE = fixed_size_v<pad_width_t>;
                [[maybe_unused]]
                constexpr auto BOUNDED_SIZE = bounded_size_v<pad_width_t>;
                if constexpr (!is_fail_v<decltype(FIXED_SIZE)>) {
                    constexpr auto SIZE = FIXED_SIZE;
                    using type = nmtools_array<nm_size_t,SIZE>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(BOUNDED_SIZE)>) {
                    using type = nmtools_static_vector<nm_size_t,BOUNDED_SIZE>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::index

namespace nmtools::view
{
    enum class PADDING_MODE
    {
        CONSTANT,
    };

    template <typename src_shape_t, typename pads_t, typename src_size_t>
    struct pad_t
        : base_indexer_t<pad_t<src_shape_t,pads_t,src_size_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using pads_type = meta::fwd_attribute_t<pads_t>;
        using dst_shape_type = meta::resolve_optype_t<index::shape_pad_t,src_shape_type,pads_type>;

        using src_size_type = src_size_t;
        using dst_size_type = decltype(unwrap(index::product(meta::declval<dst_shape_type>())));

        static constexpr auto n_inputs  = 2;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const pads_type pads;
        const dst_shape_type dst_shape;
        const src_size_type  src_size;
        const dst_size_type  dst_size;

        constexpr pad_t(const src_shape_t& src_shape
            , const pads_t& pads
            , src_size_t src_size
        )
            : src_shape(fwd_attribute(src_shape))
            , pads(fwd_attribute(pads))
            , dst_shape(unwrap(index::shape_pad(src_shape,pads)))
            , src_size(src_size)
            , dst_size(unwrap(index::product(dst_shape)))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::pad(indices,src_shape,dst_shape,pads);
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
                && utils::isequal(pads,other.pads)
            ;
        }
    };

    template <typename src_shape_t, typename pads_t, typename src_size_t>
    constexpr auto padder(const src_shape_t& src_shape, const pads_t& pads, src_size_t src_size)
    {
        if constexpr (meta::is_maybe_v<src_shape_t>) {
            using result_t = decltype(padder(unwrap(src_shape),pads,src_size));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (src_shape
                ? return_t{padder(unwrap(src_shape),pads,src_size)}
                : return_t{meta::Nothing}
            );
        } else if constexpr (meta::is_maybe_v<pads_t>) {
            using result_t = decltype(padder(src_shape,unwrap(pads),src_size));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (pads
                ? return_t{padder(src_shape,unwrap(pads),src_size)}
                : return_t{meta::Nothing}
            );
        } else {
            [[maybe_unused]]
            auto dst_shape = index::shape_pad(src_shape,pads);
            if constexpr (meta::is_fail_v<decltype(dst_shape)>) {
                // let the caller handle type error
                return dst_shape;
            } else if constexpr (meta::is_maybe_v<decltype(dst_shape)>) {
                using result_t = decltype(pad_t{src_shape,pads,unwrap(src_size)});
                using return_t = nmtools_maybe<result_t>;
                return (dst_shape
                    ? return_t{pad_t{src_shape,pads,unwrap(src_size)}}
                    : return_t{meta::Nothing}
                );
            } else {
                return pad_t{src_shape,pads,unwrap(src_size)};
            }
        }
    } // padder

    template <typename array_t, typename pads_t, typename value_t=float>
    constexpr auto pad2(const array_t& array, const pads_t& pads, value_t value=static_cast<value_t>(0))
    {
        auto f = [](const auto& array, const auto& pads, value_t value){
            using element_t = meta::get_element_type_t<meta::remove_cvref_t<decltype(array)>>;
            auto src_shape  = shape<true>(array);
            auto src_size   = size<true>(array);
            auto indexer    = padder(src_shape,pads,src_size);
            auto operands   = pack_operands(array,static_cast<element_t>(value));
            return indexing(operands,indexer);
        };
        return lift_indexing(f,array,pads,value);
    }

    template <typename array_t, typename pad_width_t, typename constant_values_t=float>
    constexpr auto pad(const array_t& array, const pad_width_t& pad_width
        , constant_values_t constant_values=static_cast<constant_values_t>(0))
    {
        auto pads = index::parse_pad_width(pad_width);
        return view::pad2(array,pads,constant_values);
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
            auto pads = as_static<max_dim>(attribute.pads);
            auto src_size  = as_static<max_dim>(attribute.src_size);
            return view::padder(src_shape,pads,src_size);
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
            str += ".pads=";
            str += to_string(kwargs.pads,Compact);
            str += ".src_size=";
            str += to_string(kwargs.src_size,Compact);
            str += "}";
            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct pad2
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::pad2(args...);
            }
        };

        struct pad
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::pad(args...);
            }
        };
    }

    constexpr inline auto pad2 = functor_t{unary_fmap_t<fun::pad2>{}};

    constexpr inline auto pad = functor_t{unary_fmap_t<fun::pad>{}};
} // namespace nmtools::functional

#include "nmtools/array/pad.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly pad an array
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam pads_t 
     * @tparam value_t 
     * @param array     input array
     * @param pads number of padding to be applied to each edge of the axes.
     * @param value     constant value
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename pads_t, typename value_t=float>
    constexpr auto pad2(const array_t& array, const pads_t& pads, value_t value=static_cast<value_t>(0),
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto padded = view::pad2(array,pads,value);
        return eval(padded
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // pad2

    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename pad_width_t, typename constant_values_t=float>
    constexpr auto pad(const array_t& array, const pad_width_t& pad_width, constant_values_t constant_values=static_cast<constant_values_t>(0),
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto padded = view::pad(array,pad_width,constant_values);
        return eval(padded
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // pad
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_PAD_HPP