#ifndef NMTOOLS_ARRAY_VIEW_EXPAND_HPP
#define NMTOOLS_ARRAY_VIEW_EXPAND_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/unwrap.hpp"

/*=====================================================================*/

#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/normalize_axis.hpp"

namespace nmtools::index
{
    struct shape_expand_t {};

    template <typename src_shape_t, typename axis_t, typename spacing_t>
    constexpr auto shape_expand(const src_shape_t& src_shape, const axis_t& axis, const spacing_t& spacing)
    {
        using result_t = meta::resolve_optype_t<shape_expand_t,src_shape_t,axis_t,spacing_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto src_dim = len(src_shape);

            auto m_axis = [&](){
                // TODO: propagate error
                auto normalized = unwrap(normalize_axis(axis,src_dim));
                if constexpr (meta::is_index_v<axis_t>) {
                    return nmtools_array{normalized};
                } else {
                    return normalized;
                }
            }();

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(src_dim);
            }

            for (nm_size_t i=0; i<src_dim; i++) {
                at(result,i) = at(src_shape,i);
            }

            // TODO: add to_index_array helper, make spacing index array to simplify the following logic
            if constexpr (meta::is_index_array_v<axis_t> ) {
                for (nm_size_t i=0; i<len(m_axis); i++) {
                    auto idx = at(m_axis,i);
                    if constexpr (meta::is_index_array_v<spacing_t>) {
                        at(result,idx) += (at(result,idx)-1) * at(spacing,i);
                    } else {
                        at(result,idx) += (at(result,idx)-1) * spacing;
                    }
                }
            } else {
                // assume axis is single size
                auto idx = at(m_axis,0);
                if constexpr (meta::is_index_array_v<spacing_t>) {
                    // assume spacing also single size
                    // TODO: error handling
                    at(result,idx) += (at(result,idx)-1) * at(spacing,0);
                } else {
                    at(result,idx) += (at(result,idx)-1) * spacing;
                }
            }
        }

        return result;
    }

    struct expand_t {};

    template <typename indices_t, typename src_shape_t, typename axis_t, typename spacing_t>
    constexpr auto expand(const indices_t& indices, const src_shape_t& src_shape, const axis_t& axis, const spacing_t& spacing)
    {
        using result_t = meta::resolve_optype_t<expand_t,indices_t,src_shape_t,axis_t,spacing_t>;

        // assume result is either of index array or None
        using left_t = meta::get_either_left_t<result_t>;
        using right_t [[maybe_unused]] = meta::get_either_right_t<result_t>;

        [[maybe_unused]]
        auto src_dim = len(src_shape);

        auto result = left_t {};
        if constexpr (meta::is_resizable_v<left_t>) {
            result.resize(src_dim);
        }
        for (size_t i=0; i<src_dim; i++) {
            at(result,i) = at(indices,i);
        }

        // normalized axis
        auto m_axis = [&](){
            auto normalized = unwrap(normalize_axis(axis,src_dim));
            if constexpr (meta::is_index_v<axis_t>) {
                return nmtools_array{normalized};
            } else {
                return normalized;
            }
        }();

        auto return_none = false;

        if constexpr (meta::is_index_array_v<axis_t>) {
            for (nm_size_t i=0; i<len(m_axis); i++) {
                auto idx = at(m_axis,i);
                auto divisor = [&](){
                    if constexpr (meta::is_index_array_v<spacing_t>) {
                        return at(spacing,i) + 1;
                    } else {
                        return spacing + 1;
                    }
                }();
                auto remainder = at(result,idx) % divisor;
                if (remainder > 0) {
                    return_none = true;
                    break;
                } else {
                    at(result,idx) = at(result,idx) / divisor;
                }
            }
        } else {
            // axis=0
            auto axis = at(m_axis,0);
            // divisor=2
            auto divisor = [&](){
                if constexpr (meta::is_index_array_v<spacing_t>) {
                    return at(spacing,0) + 1;
                } else {
                    return spacing + 1;
                }
            }();
            // remainder=at([0],0)%2=0
            // remainder=at([1],0)%2=1
            // remainder=at([2],0)%2=0
            // remainder=at([3],0)%2=1
            // remainder=at([4],0)%2=0
            auto remainder = at(result,axis) % divisor;
            if (remainder > 0) {
                return_none = true;
            } else {
                at(result,axis) = at(result,axis) / divisor;
            }
        }

        if (return_none) {
            return result_t{None};
        } else {
            return result_t{result};
        }
    }
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct SHAPE_EXPAND_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct INDEX_EXPAND_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t, typename axis_t, typename spacing_t>
    struct resolve_optype<void,index::shape_expand_t,src_shape_t,axis_t,spacing_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>
                || !(is_index_array_v<axis_t> || is_index_v<axis_t>)
                || !(is_index_array_v<spacing_t> || is_index_v<spacing_t>)
            ) {
                using type = error::SHAPE_EXPAND_UNSUPPORTED<src_shape_t,axis_t,spacing_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<src_shape_t>
                && (is_constant_index_array_v<axis_t> || is_constant_index_v<axis_t>)
                && (is_constant_index_array_v<spacing_t> || is_constant_index_v<spacing_t>)
            ) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto axis      = to_value_v<axis_t>;
                constexpr auto spacing  = to_value_v<spacing_t>;
                constexpr auto result    = index::shape_expand(src_shape,axis,spacing);
                using nmtools::at, nmtools::len;
                // TODO: handle maybe result error
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,index)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
                constexpr auto DIM = len_v<src_shape_t>;

                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_size_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // shape_expand_t

    template <typename indices_t, typename src_shape_t, typename axis_t, typename spacing_t>
    struct resolve_optype<void,index::expand_t,indices_t,src_shape_t,axis_t,spacing_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (
                !is_index_array_v<indices_t>
                || !is_index_array_v<src_shape_t>
                || !(is_index_v<axis_t> || is_index_array_v<axis_t>)
                || !(is_index_v<spacing_t> || is_index_array_v<spacing_t>)
            )  {
                using type = error::INDEX_EXPAND_UNSUPPORTED<indices_t,src_shape_t,axis_t,spacing_t>;
                return as_value_v<type>;
            } else {
                // TODO: support constant indexing

                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
                constexpr auto DIM   = len_v<src_shape_t>;
                if constexpr (DIM > 0) {
                    using array_type = nmtools_array<nm_size_t,DIM>;
                    using type = nmtools_either<array_type,none_t>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using array_type = nmtools_static_vector<nm_size_t,B_DIM>;
                    using type = nmtools_either<array_type,none_t>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using array_type = nmtools_list<nm_size_t>;
                    using type = nmtools_either<array_type,none_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

/*=====================================================================*/

#include "nmtools/array/as_static.hpp"
#include "nmtools/utils/isequal/isequal.hpp"
#include "nmtools/utils/isclose/isclose.hpp"
#include "nmtools/utils/to_string/to_string.hpp"

namespace nmtools::args
{
    template <typename axis_t, typename spacing_t, typename fill_value_t>
    struct expand
    {
        using axis_type       = axis_t;
        using spacing_type    = spacing_t;
        using fill_value_type = fill_value_t;

        axis_type       axis;
        spacing_type    spacing;
        fill_value_type fill_value;

        template <typename...args_t>
        constexpr auto operator==(const expand<args_t...>& other) const
        {
            return utils::isequal(axis,other.axis)
                && utils::isequal(spacing,other.spacing)
                && utils::isclose(fill_value,other.fill_value)
            ;
        }
    };

    template <typename...args_t>
    expand(args_t...) -> expand<args_t...>;
} // namespace nmtools::args

namespace nmtools::array
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        args::expand<args_t...>, max_dim
    > {
        using attribute_type = args::expand<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto axis = as_static<max_dim>(attribute.axis);
            auto spacing = as_static<max_dim>(attribute.spacing);
            // TODO: handle errors
            return args::expand{axis,spacing,attribute.fill_value};
        }
    };
} // namespace nmtools::array

namespace nmtools::meta
{
    template <typename...args_t>
    struct is_attribute<args::expand<args_t...>> : true_type {};
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        args::expand<args_t...>,fmt_string_t<fmt_args...>
    > {
        using formatter_type = fmt_string_t<fmt_args...>;
        using result_type = nmtools_string;

        auto operator()(const args::expand<args_t...>& args) const noexcept
        {
            nmtools_string str;
            str += "{";

            str += ".axis=";
            str += to_string(args.axis,formatter_type{});
            str += ".spacing=";
            str += to_string(args.spacing,formatter_type{});
            str += ".fill_value=";
            str += to_string(args.fill_value,formatter_type{});

            str += "}";
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

/*=====================================================================*/

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/indexing.hpp"
#include "nmtools/array/view/alias.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/utility/fwd.hpp"

namespace nmtools::view
{
    template <typename src_shape_t, typename axis_t, typename spacing_t, typename src_size_t>
    struct expand_t
        : base_indexer_t<expand_t<src_shape_t,axis_t,spacing_t,src_size_t>>
    {
        using axis_type    = meta::fwd_attribute_t<axis_t>;
        using spacing_type = meta::fwd_attribute_t<spacing_t>;

        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using dst_shape_type = meta::resolve_optype_t<index::shape_expand_t,src_shape_type,axis_type,spacing_type>;

        using src_size_type = src_size_t;
        using dst_size_type = decltype(index::product(meta::declval<dst_shape_type>()));

        static constexpr auto n_inputs  = 2;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const axis_type      axis;
        const spacing_type   spacing;
        const dst_shape_type dst_shape;
        const src_size_type  src_size;
        const dst_size_type  dst_size;

        constexpr expand_t(const src_shape_t& src_shape
            , const axis_t& axis
            , const spacing_t& spacing
            , src_size_t src_size
        )
            : src_shape(fwd_attribute(src_shape))
            , axis(fwd_attribute(axis))
            , spacing(fwd_attribute(spacing))
            , dst_shape(index::shape_expand(src_shape,axis,spacing))
            , src_size(src_size)
            , dst_size(index::product(dst_shape))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::expand(indices,src_shape,axis,spacing);
            return src_indices;
        }

        template <typename...args_t>
        constexpr auto operator==(expand_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(axis,other.axis)
                && utils::isequal(spacing,other.spacing)
            ;
        }
    };

    template <typename src_shape_t, typename axis_t, typename spacing_t, typename src_size_t>
    constexpr auto expander(const src_shape_t& src_shape, const axis_t& axis, const spacing_t& spacing, src_size_t src_size)
    {
        if constexpr (meta::is_maybe_v<src_shape_t>) {
            using result_t = decltype(expander(unwrap(src_shape),axis,spacing,src_size));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (src_shape
                ? return_t{expander(unwrap(src_shape),axis,spacing,src_size)}
                : return_t{meta::Nothing}
            );
        } else if constexpr (meta::is_maybe_v<axis_t>) {
            using result_t = decltype(expander(src_shape,unwrap(axis),spacing,src_size));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (axis
                ? return_t{expander(src_shape,unwrap(axis),spacing,src_size)}
                : return_t{meta::Nothing}
            );
        } else if constexpr (meta::is_maybe_v<spacing_t>) {
            using result_t = decltype(expander(src_shape,axis,unwrap(spacing),src_size));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (spacing
                ? return_t{expander(src_shape,axis,unwrap(spacing),src_size)}
                : return_t{meta::Nothing}
            );
        } else {
            auto dst_shape = index::shape_expand(src_shape,axis,spacing);
            if constexpr (meta::is_fail_v<decltype(dst_shape)>) {
                // let the caller handle type error
                return dst_shape;
            } else if constexpr (meta::is_maybe_v<decltype(dst_shape)>) {
                using result_t = decltype(expand_t{unwrap(src_shape),unwrap(axis),unwrap(spacing),unwrap(src_size)});
                using return_t = nmtools_maybe<result_t>;
                return (dst_shape
                    ? return_t{expand_t{unwrap(src_shape),unwrap(axis),unwrap(spacing),unwrap(src_shape)}}
                    : return_t{meta::Nothing}
                );
            } else {
                return expand_t{unwrap(src_shape),unwrap(axis),unwrap(spacing),unwrap(src_size)};
            }
        }
    }

    template <typename array_t, typename axis_t, typename spacing_t=nm_index_t, typename fill_value_t=nm_index_t>
    constexpr auto expand(const array_t& array, const axis_t& axis, const spacing_t& spacing=spacing_t{1}, fill_value_t fill_value=fill_value_t{0})
    {
        auto f = [](const auto& array, const auto& axis, const auto& spacing, auto fill_value){
            using element_t = meta::get_element_type_t<meta::remove_cvref_pointer_t<decltype(array)>>;
            auto src_shape  = shape<true>(array);
            auto src_size   = size<true>(array);
            auto indexer    = expander(src_shape,axis,spacing,src_size);
            auto operands   = view::aliased(array,static_cast<element_t>(fill_value));
            return indexing(operands,indexer);
        };
        return lift_indexing(f,array,axis,spacing,fill_value);
    }
} // namespace nmtools::view

namespace nmtools::array
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::expand_t<args_t...>, max_dim
    > {
        using attribute_type = view::expand_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            auto axis      = as_static<max_dim>(attribute.axis);
            auto spacing   = as_static<max_dim>(attribute.spacing);
            auto src_size  = as_static<max_dim>(attribute.src_size);
            return view::expander(src_shape,axis,spacing,src_size);
        }
    };
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::expand_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::expand_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "expand";
            str += "{";
            str += ".src_shape=";
            str += to_string(kwargs.src_shape,Compact);
            str += ",.axis=";
            str += to_string(kwargs.axis,Compact);
            str += ",.spacing=";
            str += to_string(kwargs.spacing,Compact);
            str += ",.src_size=";
            str += to_string(kwargs.src_size,Compact);
            str += "}";
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_EXPAND_HPP