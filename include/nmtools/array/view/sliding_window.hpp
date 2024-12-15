#ifndef NMTOOLS_ARRAY_INDEX_SLIDING_WINDOW_HPP
#define NMTOOLS_ARRAY_INDEX_SLIDING_WINDOW_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/platform/math/constexpr.hpp"
#include "nmtools/utility/tuple_cat.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::index
{
    struct shape_sliding_window_t {};

    template <typename src_shape_t
        , typename window_shape_t
        , typename axis_t=none_t>
    constexpr inline auto shape_sliding_window(
        const src_shape_t& src_shape
        , const window_shape_t& window_shape
        , [[maybe_unused]] const axis_t& axis=axis_t{}
    ) {
        if constexpr (meta::is_maybe_v<src_shape_t>
            || meta::is_maybe_v<window_shape_t>
            || meta::is_maybe_v<axis_t>
        ) {
            using result_t = decltype(shape_sliding_window(unwrap(src_shape),unwrap(window_shape),unwrap(axis)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_shape) && has_value(window_shape) && has_value(axis)
                ? return_t{shape_sliding_window(unwrap(src_shape),unwrap(window_shape),unwrap(axis))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<
                shape_sliding_window_t,src_shape_t,window_shape_t,axis_t>;

            auto result = result_t{};

            if constexpr (!meta::is_constant_index_array_v<result_t>) {
                auto src_dim = len(src_shape);

                auto window_dim = [&](){
                    if constexpr (meta::is_num_v<window_shape_t>) {
                        return 0;
                    } else {
                        return len(window_shape);
                    }
                }();

                [[maybe_unused]]
                auto dst_dim = [&](){
                    if constexpr (meta::is_num_v<window_shape_t>) {
                        return src_dim + 1;
                    } else {
                        return src_dim + window_dim;
                    }
                }();
                
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(dst_dim);
                }

                [[maybe_unused]]
                auto normalized_axis = [&](){
                    if constexpr (is_none_v<axis_t>) {
                        return axis;
                    } else {
                        // TODO: propagate error
                        return unwrap(normalize_axis(axis,src_dim));
                    }
                }();

                if constexpr (meta::is_num_v<window_shape_t> && meta::is_num_v<axis_t>) {
                    for (size_t i=0; i<src_dim; i++) {
                        if (i==(size_t)normalized_axis) {
                            auto res_i = at(src_shape,i) - (window_shape-1);
                            at(result,i) = res_i;
                        } else {
                            at(result,i) = at(src_shape,i);
                        }
                    }
                    at(result,src_dim) = window_shape;
                } else if constexpr (meta::is_num_v<window_shape_t> && is_none_v<axis_t>) {
                    for (size_t i=0; i<src_dim; i++) {
                        auto res_i = at(src_shape,i) - (window_shape-1);
                        at(result,i) = res_i;
                    }
                    at(result,src_dim) = window_shape;
                } else if constexpr (is_none_v<axis_t>) {
                    for (size_t i=0; i<src_dim; i++) {
                        auto res_i = at(src_shape,i) - (at(window_shape,i)-1);
                        at(result,i) = res_i;
                    }
                    for (size_t i=src_dim; i<dst_dim; i++) {
                        at(result,i) = at(window_shape,i-src_dim);
                    }
                } else /* if constexpr (is_index_array_v<axis_t>) */ {
                    for (size_t i=0; i<src_dim; i++) {
                        auto res_i = at(src_shape,i);
                        at(result,i) = res_i;
                    }
                    // assume len(axis) == len(window_shape)
                    // TODO: check lens
                    for (size_t i=0; i<len(normalized_axis); i++) {
                        auto axis_i = at(normalized_axis,i);
                        at(result,axis_i) -= (at(window_shape,i) - 1);
                    }
                    for (size_t i=src_dim; i<dst_dim; i++) {
                        at(result,i) = at(window_shape,i-src_dim);
                    }
                }
            }

            return result;
        }
    } // shape_sliding_window

    struct sliding_window_t {};

    template <typename indices_t
        , typename dst_shape_t
        , typename src_shape_t
        , typename window_shape_t
        , typename axis_t=none_t>
    constexpr auto sliding_window(const indices_t& indices
        , const dst_shape_t& dst_shape
        , const src_shape_t& src_shape
        , [[maybe_unused]] const window_shape_t& window_shape
        , [[maybe_unused]] const axis_t& axis=axis_t{}
    ) {
        using result_t = meta::resolve_optype_t<
            sliding_window_t,indices_t,dst_shape_t,
            src_shape_t,window_shape_t,axis_t>;
        
        auto result = result_t{};

        auto src_dim = len(src_shape);

        [[maybe_unused]]
        auto win_dim = len(dst_shape) - src_dim;

        if constexpr (meta::is_resizable_v<result_t>) {
            result.resize(src_dim);
        }

        for (size_t i=0; i<src_dim; i++) {
            at(result,i) = at(indices,i);
        }

        if constexpr (is_none_v<axis_t>) {
            for (size_t i=0; i<win_dim; i++) {
                at(result,i) = at(result,i) + at(indices,i+src_dim);
            }
        } else if constexpr (meta::is_index_array_v<axis_t>) {
            auto axis_dim = len(axis);
            for (size_t a_i=0; a_i<axis_dim; a_i++) {
                auto i = at(axis,a_i);
                at(result,i) = at(result,i) + at(indices,a_i+src_dim);
            }
        } else if constexpr (meta::is_num_v<axis_t>) {
            // at(result,axis) = at(result,axis) + at(indices,axis);
            auto m_axis = nmtools_array{axis};
            auto axis_dim = len(m_axis);
            for (size_t a_i=0; a_i<axis_dim; a_i++) {
                auto i = at(m_axis,a_i);
                at(result,i) = at(result,i) + at(indices,a_i+src_dim);
            }
        }

        return result;
    } // sliding_window

} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct SHAPE_SLIDING_WINDOW_UNSUPPORTED : detail::fail_t {};

        template<typename...>
        struct SLIDING_WINDOW_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t, typename window_shape_t, typename axis_t>
    struct resolve_optype<
        void, index::shape_sliding_window_t, src_shape_t, window_shape_t, axis_t
    >
    {
        static constexpr auto vtype = [](){

            using index_t = get_index_element_type_t<src_shape_t>;

            [[maybe_unused]] constexpr auto src_dim    = len_v<src_shape_t>;
            [[maybe_unused]] constexpr auto src_b_dim  = bounded_size_v<src_shape_t>;
            [[maybe_unused]] constexpr auto window_dim = [](){
                if constexpr (is_index_v<window_shape_t>) {
                    return 1;
                } else {
                    return len_v<window_shape_t>;
                }
            }();
            [[maybe_unused]] constexpr auto b_window_dim = [](){
                if constexpr (is_index_v<window_shape_t>) {
                    return 1;
                } else {
                    return bounded_size_v<window_shape_t>;
                }
            }();

            if constexpr (is_constant_index_array_v<src_shape_t>
                && (is_constant_index_array_v<window_shape_t> || is_constant_index_v<window_shape_t>)
                && (is_none_v<axis_t> || is_constant_index_v<axis_t>)
            ) {
                constexpr auto axis = to_value_v<axis_t>;
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto window_shape = to_value_v<window_shape_t>;
                constexpr auto result = index::shape_sliding_window(
                    src_shape,window_shape,axis
                );
                using nmtools::len, nmtools::at;
                if constexpr (is_maybe_v<decltype(result)>) {
                    // TODO: implement
                } else {
                    constexpr auto result_ct = template_reduce<len(result)>([&](auto init, auto index){
                        constexpr auto v = at(result,index);
                        return utility::tuple_append(init,ct_v<v>);
                    }, nmtools_tuple{});
                    using type = remove_cvref_t<decltype(result_ct)>;
                    return as_value_v<type>;
                }
            } else if constexpr ((src_dim > 0) && (window_dim > 0)) {
                using type = nmtools_array<index_t,src_dim+window_dim>;
                return as_value_v<type>;
            } else if constexpr (!is_fail_v<decltype(src_b_dim)> && !is_fail_v<decltype(b_window_dim)>) {
                using type = nmtools_static_vector<index_t,src_b_dim+b_window_dim>;
                return as_value_v<type>;
            } else {
                using type = nmtools_list<index_t>;
                return as_value_v<type>;
            }
        }();

        using type = type_t<decltype(vtype)>;
    }; // shape_sliding_window_t

    template <typename indices_t, typename dst_shape_t, typename src_shape_t, typename window_shape_t, typename axis_t>
    struct resolve_optype<
        void, index::sliding_window_t, indices_t, dst_shape_t, src_shape_t, window_shape_t, axis_t
    >
    {
        using index_t = get_index_element_type_t<src_shape_t>;

        static constexpr auto vtype = [](){

            [[maybe_unused]] constexpr auto src_dim   = len_v<src_shape_t>;
            [[maybe_unused]] constexpr auto src_b_dim = bounded_size_v<src_shape_t>;

            if constexpr (!is_index_array_v<indices_t>
                || !is_index_array_v<src_shape_t>
            ) {
                using type = error::SLIDING_WINDOW_UNSUPPORTED<indices_t,dst_shape_t,src_shape_t,window_shape_t,axis_t>;
                return as_value_v<type>;
            } else if constexpr (src_dim > 0) {
                using type = nmtools_array<index_t,src_dim>;
                return as_value_v<type>;
            } else if constexpr (!is_fail_v<decltype(src_b_dim)>) {
                using type = nmtools_static_vector<index_t,src_b_dim>;
                return as_value_v<type>;
            } else {
                using type = nmtools_list<index_t>;
                return as_value_v<type>;
            }
        }();

        using type = type_t<decltype(vtype)>;
    }; // sliding_window_t
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_SLIDING_WINDOW_HPP

#ifndef NMTOOLS_ARRAY_VIEW_SLIDING_WINDOW_HPP
#define NMTOOLS_ARRAY_VIEW_SLIDING_WINDOW_HPP

#include "nmtools/array/view/indexing.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/utility/to_string/to_string.hpp"

namespace nmtools::view
{
    template <typename src_shape_t
        , typename window_shape_t
        , typename axis_t>
    struct sliding_window_t
        : base_indexer_t<sliding_window_t<src_shape_t,window_shape_t,axis_t>>
    {
        using src_shape_type    = meta::fwd_attribute_t<src_shape_t>;
        using window_shape_type = meta::fwd_attribute_t<window_shape_t>;
        using axis_type         = meta::fwd_attribute_t<axis_t>;
        using dst_shape_type = meta::resolve_optype_t<index::shape_sliding_window_t
            , src_shape_type, window_shape_type, axis_type>;
        using dst_size_type = meta::resolve_optype_t<index::product_t,dst_shape_type>;
        using src_size_type = meta::resolve_optype_t<index::product_t,src_shape_type>;

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const window_shape_type window_shape;
        const axis_type axis;
        const dst_shape_type dst_shape;

        constexpr sliding_window_t(const src_shape_t& src_shape
            , const window_shape_t& window_shape
            , const axis_t& axis
        )
            : src_shape(fwd_attribute(src_shape))
            , window_shape(fwd_attribute(window_shape))
            , axis(fwd_attribute(axis))
            , dst_shape(index::shape_sliding_window(
                src_shape,window_shape,axis))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::sliding_window(indices
                , unwrap(dst_shape), src_shape, window_shape, axis);
            return src_indices;
        }

        template <typename...args_t>
        constexpr auto operator==(sliding_window_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(dst_shape,other.dst_shape)
                && utils::isequal(window_shape,other.window_shape)
                && utils::isequal(axis,other.axis)
            ;
        }
    }; // sliding_window_t

    template <typename src_shape_t, typename window_shape_t, typename axis_t=none_t>
    constexpr auto sliding_window_indexer(const src_shape_t& src_shape
        , const window_shape_t& window_shape, const axis_t& axis=axis_t{})
    {
        // TODO: ValueError: Since axis is `None`, must provide window_shape for all dimensions of `x`;
        // check if we can compute the resulting shape
        auto dst_shape = index::shape_sliding_window(src_shape,window_shape,axis);
        if constexpr (meta::is_fail_v<decltype(dst_shape)>) {
            // let the caller handle compile error
            auto error = dst_shape;
            return error;
        } else if constexpr (meta::is_maybe_v<decltype(dst_shape)>) {
            using result_t = decltype(sliding_window_t{src_shape,window_shape,axis});
            using return_t = nmtools_maybe<result_t>;
            return (dst_shape
                ? return_t{result_t{src_shape,window_shape,axis}}
                : return_t{meta::Nothing}
            );
        } else {
            auto indexer = sliding_window_t{src_shape,window_shape,axis};
            return indexer;
        }
    } // sliding_window_indexer

    template <typename array_t, typename window_shape_t, typename axis_t=none_t>
    constexpr auto sliding_window(const array_t& array
        , const window_shape_t& window_shape, const axis_t& axis=axis_t{})
    {
        auto f = [](const auto& array, const auto& window_shape, const auto& axis){
            auto src_shape = shape<true>(array);
            auto indexer   = sliding_window_indexer(src_shape,window_shape,axis);
            return indexing(array,indexer);
        };
        return lift_indexing(f,array,window_shape,axis);
    } // sliding_window
} // namespace nmtools::view

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::sliding_window_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::sliding_window_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "sliding_window";
            str += "{";
            str += ".src_shape=";
            str += to_string(kwargs.src_shape,Compact);
            str += ",.window_shape=";
            str += to_string(kwargs.window_shape,Compact);
            str += ",.axis=";
            str += to_string(kwargs.axis,Compact);
            str += "}";
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING


#endif // NMTOOLS_ARRAY_VIEW_SLIDING_WINDOW_HPP