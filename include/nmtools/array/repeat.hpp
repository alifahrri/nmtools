#ifndef NMTOOLS_ARRAY_VIEW_REPEAT_HPP
#define NMTOOLS_ARRAY_VIEW_REPEAT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/utility/isequal/isequal.hpp"

#include "nmtools/index/product.hpp"
#include "nmtools/index/compute_indices.hpp"
#include "nmtools/index/where.hpp"
#include "nmtools/index/cumsum.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/index/sum.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve repeat return type
     * 
     */
    struct shape_repeat_t {};

    /**
     * @brief Compute the shape of a repeat view.
     * 
     * If axis is none, the shape is reduced to 1D, with size: numel * repeats.
     * Otherwise, the dimension is remains the same.
     * 
     * @tparam shape_t 
     * @tparam repeats_t 
     * @tparam axis_t 
     * @param shape shape of src array
     * @param repeats number of repetitions of each elements
     * @param axis 
     * @return constexpr auto 
     */
    template <typename shape_t, typename repeats_t, typename axis_t>
    constexpr auto shape_repeat(const shape_t& shape, const repeats_t& repeats, [[maybe_unused]] axis_t axis)
    {
        using result_t = resolve_optype_t<shape_repeat_t,shape_t,repeats_t,axis_t>;
        auto res = result_t {};

        if constexpr (!is_fail_v<result_t>
            && !is_constant_index_array_v<result_t>
        ) {
            // when axis is None, repeat the flattened array
            // so the resulting shape is 1-dimensional
            if constexpr (is_none_v<axis_t>) {
                auto p = product(shape);
                at(res,ct_v<0>) = p * repeats;
            } else {
                [[maybe_unused]]
                auto n = len(shape);

                if constexpr (is_resizable_v<result_t>) {
                    res.resize(n);
                }

                constexpr auto N = len_v<result_t>;
                if constexpr (N > 0) {
                    template_for<N>([&](auto i){
                        auto shape_i = at(shape,i);
                        if constexpr (!is_constant_index_v<decltype(at(res,i))>) {
                            if (has_value(shape_i)) {
                                at(res,i) = shape_i;
                            }
                        }
                    });
                } else {
                    for (nm_size_t i=0; i<n; i++) {
                        auto shape_i = at(shape,i);
                        if (has_value(shape_i)) {
                            at(res,i) = shape_i;
                        }
                    }
                }

                if constexpr (!is_constant_index_v<decltype(at(res,axis))>) {
                    if constexpr (is_index_array_v<repeats_t>) {

                        // when axis is specified and repeats is index array,
                        // the number of element at the specified axis is simply the sum of the repeats
                        // for example:
                        // >>> x = np.array([[1,2],[3,4]])
                        // >>> np.repeat(x, [1, 2], axis=0)
                        // array([[1, 2],
                        //        [3, 4],
                        //        [3, 4]])
                        // at axis 0, first element x(axis,0) is not repeated (repeats(0)=1)
                        // while the second element x(axis,1) is repeated once (repeats(1)=2)

                        // TODO: error handling
                        auto n_repeats = len(repeats);
                        if (n_repeats == 1) {
                            at(res,axis) = at(res,axis) * at(repeats,ct_v<0>);
                        } else {
                            at(res,axis) = index::sum(repeats);
                        }
                    } else {
                        at(res,axis) = at(res,axis) * repeats;
                    }
                }
            }
        }

        return res;
    } // repeat
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_REPEAT_UNSUPPORTED : detail::fail_t {};
    }
    /**
     * @brief resolve return type for index::shape_repeat op
     * 
     * @tparam shape_t 
     * @tparam repeats_t 
     * @tparam axis_t 
     */
    template <typename shape_t, typename repeats_t, typename axis_t>
    struct resolve_optype <
        void, index::shape_repeat_t, shape_t, repeats_t, axis_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<shape_t>
                || !(is_index_v<repeats_t> || is_index_array_v<repeats_t>)
                || !(is_index_v<axis_t> || is_index_array_v<axis_t> || is_none_v<axis_t>)
            ) {
                using type = error::SHAPE_REPEAT_UNSUPPORTED<shape_t,repeats_t,axis_t>;
                return as_value_v<type>;
            } else if constexpr (
                (is_constant_index_array_v<shape_t> || is_clipped_index_array_v<shape_t> || is_mixed_index_array_v<shape_t>)
                && (is_constant_index_v<repeats_t> || is_constant_index_array_v<repeats_t> || is_clipped_index_array_v<repeats_t> || is_mixed_index_array_v<repeats_t>)
                && (is_none_v<axis_t> || is_constant_index_v<axis_t>)
            ) {
                constexpr auto shape   = to_value_v<shape_t>;
                constexpr auto repeats = to_value_v<repeats_t>;
                constexpr auto axis    = to_value_v<axis_t>;
                constexpr auto result  = index::shape_repeat(shape,repeats,axis);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_type = type_t<decltype(init)>;
                    constexpr auto result_i = at(result,I);
                    if constexpr (is_clipped_index_array_v<shape_t> || is_clipped_index_array_v<repeats_t>) {
                        using result_t  = append_type_t<init_type,clipped_size_t<result_i>>;
                        return as_value_v<result_t>;
                    } else if constexpr (has_value(result_i)) {
                        using result_t  = append_type_t<init_type,ct<(nm_size_t)result_i>>;
                        return as_value_v<result_t>;
                    } else {
                        using result_t  = append_type_t<init_type,nm_size_t>;
                        return as_value_v<result_t>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else {
                // TODO deduce width & sign of null type result from array_t
                using index_t = conditional_t<
                    is_nullable_index_array_v<shape_t> || is_nullable_index_array_v<repeats_t> || is_nullable_index_v<repeats_t>
                    , null_size_t
                    , get_index_element_type_t<shape_t>
                >;
                [[maybe_unused]] constexpr auto len = len_v<shape_t>;
                [[maybe_unused]] constexpr auto max_len = max_len_v<shape_t>;
                if constexpr (is_none_v<axis_t>) {
                    using type = nmtools_array<index_t,1>;
                    return as_value_v<type>;
                } else if constexpr (len > 0) {
                    using type = nmtools_array<index_t,len>;
                    return as_value_v<type>;
                } else if constexpr (max_len > 0) {
                    using type = nmtools_static_vector<index_t,max_len>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type of repeat op
     * 
     */
    struct repeat_t {};

    /**
     * @brief Transform indices from repeated view (dst) to indices for origin shape (src).
     * 
     * @tparam shape_t 
     * @tparam indices_t 
     * @tparam repeats_t 
     * @tparam axis_t 
     * @param shape original shape
     * @param indices indices from repeat view
     * @param repeats number of repetitions
     * @param axis the axis along which to repeat values
     * @return constexpr auto 
     */
    template <typename shape_t, typename indices_t, typename repeats_t, typename axis_t>
    constexpr auto repeat(const shape_t& shape, const indices_t& indices, const repeats_t& repeats, [[maybe_unused]] axis_t axis)
    {
        using result_t = resolve_optype_t<repeat_t,shape_t,indices_t,repeats_t,axis_t>;
        static_assert (is_index_array_v<result_t>
            , "unsupported index::repeat, could not deduce return type" );
        auto ret = result_t {};

        // following numpy, when axis is None, repeat the flattened array
        // and indices must be integral type or array with size exactly 1
        if constexpr (is_none_v<axis_t>
            && !is_fail_v<result_t>
            && !is_constant_index_array_v<result_t>
        ) {
            auto i = [&](){
                if constexpr (is_integral_v<indices_t>)
                    return indices / repeats;
                else {
                    static_assert (len_v<indices_t> == 1
                        , "unsupported index::repeat, expect array with size of 1 when axis is None"
                    );
                    return at<0>(indices) / repeats;
                }
            }();

            auto indices = compute_indices(i,shape);
            if constexpr (is_resizable_v<result_t>) {
                ret.resize(len(indices));
            }
            auto assign_result = [&](auto i){
                at(ret,i) = at(indices,i);
            };
            if constexpr (is_tuple_v<result_t>) {
                constexpr auto N = len_v<result_t>;
                template_for<N>(assign_result);
            } else {
                for (size_t i=0; i<len(ret); i++) {
                    assign_result(i);
                }
            }
        } else if constexpr (!is_fail_v<result_t>
            && !is_constant_index_array_v<result_t>
        ) {
            auto n = len(indices);
            if constexpr (is_resizable_v<result_t>) {
                ret.resize(n);
            }
            for (size_t i=0; i<n; i++) {
                using common_t = promote_index_t<size_t,axis_t>;
                auto idx = at(indices,i);
                if constexpr (is_index_v<repeats_t>) {
                    at(ret,i) = (static_cast<common_t>(i)==static_cast<common_t>(axis) ? idx / repeats : idx);
                } else {
                    auto csum = index::cumsum(repeats);
                    if (static_cast<common_t>(i)==static_cast<common_t>(axis)) {
                        // note: len(repeats) == shape[axis]
                        // simply find arg of repeats such that idx >= accumulate(repeats)[args]
                        auto f = [&](auto a){
                            using common_t = promote_index_t<decltype(idx),decltype(a)>;
                            return (common_t)idx<(common_t)a;
                        };
                        auto arg = where(f, csum);
                        at(ret,i) = at(arg,0); // take first
                    } else {
                        at(ret,i) = idx;
                    }
                }
            } // for
        }

        return ret;
    } // repeat
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct REPEAT_UNSUPPORTED : detail::fail_t {};
    }
    /**
     * @brief resolve return type for repeat op that transform indices from view (dst) to src
     * follow shape_t
     * 
     * @tparam shape_t 
     * @tparam indices_t 
     * @tparam repeats_t 
     */
    template <typename shape_t, typename indices_t, typename repeats_t, typename axis_t>
    struct resolve_optype<
        void, index::repeat_t, shape_t, indices_t, repeats_t, axis_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<shape_t>
                || !(is_index_array_v<indices_t> || is_index_v<indices_t>)
                || !(is_index_array_v<repeats_t> || is_index_v<repeats_t>)
                || !(is_index_v<axis_t> || is_index_array_v<axis_t> || is_none_v<axis_t>)
            ) {
                using type = error::REPEAT_UNSUPPORTED<shape_t,indices_t,repeats_t,axis_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<shape_t>
                && is_constant_index_array_v<indices_t>
                && is_constant_index_v<repeats_t>
                && (is_constant_index_v<axis_t> || is_none_v<axis_t>)
            ) {
                constexpr auto shape   = to_value_v<shape_t>;
                constexpr auto indices = to_value_v<indices_t>;
                constexpr auto repeats = repeats_t{};
                constexpr auto axis    = axis_t{};
                constexpr auto result  = index::repeat(shape,indices,repeats,axis);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto i){
                    constexpr auto I = decltype(i)::value;
                    using init_t = type_t<decltype(init)>;
                    constexpr auto res_i = at(result,I);
                    if constexpr (has_value(res_i)) {
                        using type = append_type_t<init_t,ct<(nm_size_t)res_i>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_t,nm_size_t>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto N = len_v<shape_t>;
                [[maybe_unused]]
                constexpr auto MAX_N = max_len_v<shape_t>;
                using index_t = get_index_element_type_t<shape_t>;
                if constexpr (N > 0) {
                    using type = nmtools_array<index_t,N>;
                    return as_value_v<type>;
                } else if constexpr (MAX_N > 0) {
                    using type = nmtools_static_vector<index_t,MAX_N>;
                    return as_value_v<type>;
                } else {
                    // TODO: small buffer optimization
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<remove_cvref_t<decltype(vtype)>>;
    }; // resolve_optype
} // namespace nmtools::meta

/*************************************************************************** */

namespace nmtools::view
{
    template <typename src_shape_t, typename repeats_t, typename axis_t, typename src_size_t>
    struct repeat_t
        : base_indexer_t<repeat_t<src_shape_t,repeats_t,axis_t,src_size_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using src_size_type  = meta::fwd_attribute_t<src_size_t>;
        using repeats_type   = meta::fwd_attribute_t<repeats_t>;
        using axis_type      = meta::fwd_attribute_t<axis_t>;
        using dst_shape_type = meta::resolve_optype_t<index::shape_repeat_t,src_shape_type,repeats_type,axis_type>;

        // TODO: support repeat size inference
        // using dst_size_type  = src_size_type;
        using dst_size_type = decltype(index::product(meta::declval<dst_shape_type>()));

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const repeats_type   repeats;
        const axis_type      axis;
        const src_size_type  src_size;
        const dst_shape_type dst_shape;
        const dst_size_type  dst_size;

        constexpr repeat_t(const src_shape_t& src_shape_
            , const repeats_t& repeats_
            , const axis_t& axis_
            , const src_size_t& src_size_
        )
            : src_shape(fwd_attribute(src_shape_))
            , repeats(fwd_attribute(repeats_))
            , axis(fwd_attribute(axis_))
            , src_size(fwd_attribute(src_size_))
            , dst_shape(index::shape_repeat(src_shape,repeats,axis))
            , dst_size(index::product(dst_shape))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::repeat(src_shape,indices,repeats,axis);
            return src_indices;
        }

        template <typename...args_t>
        constexpr auto operator==(repeat_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(repeats,other.repeats)
                && utils::isequal(axis,other.axis)
            ;
        }
    }; // repeat_t

    template <typename src_shape_t, typename src_size_t, typename repeats_t, typename axis_t>
    constexpr auto repeater(const src_shape_t& src_shape, const repeats_t& repeats, const axis_t& axis, const src_size_t& src_size)
    {
        auto m_dst_shape = index::shape_repeat(src_shape,repeats,axis);
        if constexpr (meta::is_maybe_v<decltype(m_dst_shape)>) {
            using result_t = decltype(repeat_t{unwrap(src_shape),unwrap(repeats),unwrap(axis),unwrap(src_size)});
            using return_t = nmtools_maybe<result_t>;
            if (static_cast<bool>(m_dst_shape)) {
                return return_t{repeat_t{unwrap(src_shape),unwrap(repeats),unwrap(axis),unwrap(src_size)}};
            } else {
                return return_t{meta::Nothing};
            }
        } else {
            return repeat_t{unwrap(src_shape),unwrap(repeats),unwrap(axis),unwrap(src_size)};
        }
    }

    template <typename array_t, typename repeats_t, typename axis_t=none_t>
    constexpr auto repeat(const array_t& array, const repeats_t& repeats, const axis_t& axis=axis_t{})
    {
        auto f = [](const auto& array, const auto& repeats, const auto& axis){
            auto src_shape = shape<true>(array);
            auto src_size  = size<true>(array);
            auto indexer   = repeater(src_shape,repeats,axis,src_size);
            return indexing(array,indexer);
        };
        return lift_indexing(f,array,repeats,axis);
    }
} // namespace nmtools::view

/*************************************************************************** */

namespace nmtools
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::repeat_t<args_t...>, max_dim
    > {
        using attribute_type = view::repeat_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            auto src_size  = as_static<max_dim>(attribute.src_size);
            auto repeats   = as_static<max_dim>(attribute.repeats);
            auto axis      = as_static<max_dim>(attribute.axis);
            return view::repeater(src_shape,repeats,axis,src_size);
        }
    };
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::repeat_t<args_t...>, fmt_string_t<fmt_args...>
    >
    {
        using result_type = nmtools_string;

        auto operator()(const view::repeat_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "repeat";
            str += "{";
            str += ".src_shape="; str += to_string(kwargs.src_shape,Compact);
            str += ",.repeats=";  str += to_string(kwargs.repeats,Compact);
            str += ",.axis=";     str += to_string(kwargs.axis,Compact);
            str += ",.src_size="; str += to_string(kwargs.src_size,Compact);
            str += "}";
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

/*************************************************************************** */

#endif // NMTOOLS_ARRAY_VIEW_REPEAT_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_REPEAT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_REPEAT_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/array/repeat.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct repeat_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::repeat(args...);
            }
        };
    }

    constexpr inline auto repeat = functor_t{unary_fmap_t<fun::repeat_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_REPEAT_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_REPEAT_HPP
#define NMTOOLS_ARRAY_ARRAY_REPEAT_HPP

#include "nmtools/array/repeat.hpp"
#include "nmtools/core/eval.hpp"

/*************************************************************************** */

namespace nmtools
{
    /**
     * @brief Eagerly evaluate repeat op. Repeats elements of an array.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam repeats_t 
     * @tparam axis_t 
     * @param array     input array
     * @param repeats   the number of repetititons for each element
     * @param axis      the axis aloong which repeat values.
     * @param context   evaluation context.
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=default_context_t<>,
        typename array_t, typename repeats_t, typename axis_t=none_t>
    constexpr auto repeat(const array_t& array, const repeats_t& repeats, axis_t axis=axis_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto repeated = view::repeat(array,repeats,axis);
        return eval(repeated
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
        );
    } // repeat
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_REPEAT_HPP