#ifndef NMTOOLS_ARRAY_INDEX_SLIDING_WINDOW_HPP
#define NMTOOLS_ARRAY_INDEX_SLIDING_WINDOW_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/index/normalize_axis.hpp"
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
                    for (nm_size_t i=0; i<src_dim; i++) {
                        if (i==(nm_size_t)normalized_axis) {
                            auto res_i = at(src_shape,i) - (window_shape-1);
                            at(result,i) = res_i;
                        } else {
                            at(result,i) = at(src_shape,i);
                        }
                    }
                    at(result,src_dim) = window_shape;
                } else if constexpr (meta::is_num_v<window_shape_t> && is_none_v<axis_t>) {
                    for (nm_size_t i=0; i<src_dim; i++) {
                        auto res_i = at(src_shape,i) - (window_shape-1);
                        at(result,i) = res_i;
                    }
                    at(result,src_dim) = window_shape;
                } else if constexpr (is_none_v<axis_t>) {
                    for (nm_size_t i=0; i<src_dim; i++) {
                        auto res_i = at(src_shape,i) - (at(window_shape,i)-1);
                        at(result,i) = res_i;
                    }
                    for (nm_size_t i=src_dim; i<dst_dim; i++) {
                        at(result,i) = at(window_shape,i-src_dim);
                    }
                } else /* if constexpr (is_index_array_v<axis_t>) */ {
                    for (nm_size_t i=0; i<src_dim; i++) {
                        auto res_i = at(src_shape,i);
                        at(result,i) = res_i;
                    }
                    // assume len(axis) == len(window_shape)
                    // TODO: check lens
                    for (nm_size_t i=0; i<len(normalized_axis); i++) {
                        auto axis_i = at(normalized_axis,i);
                        at(result,axis_i) -= (at(window_shape,i) - 1);
                    }
                    for (nm_size_t i=src_dim; i<dst_dim; i++) {
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

        for (nm_size_t i=0; i<src_dim; i++) {
            at(result,i) = at(indices,i);
        }

        if constexpr (is_none_v<axis_t>) {
            for (nm_size_t i=0; i<win_dim; i++) {
                at(result,i) = at(result,i) + at(indices,i+src_dim);
            }
        } else if constexpr (meta::is_index_array_v<axis_t>) {
            auto axis_dim = len(axis);
            for (nm_size_t a_i=0; a_i<axis_dim; a_i++) {
                auto i = at(axis,a_i);
                at(result,i) = at(result,i) + at(indices,a_i+src_dim);
            }
        } else if constexpr (meta::is_num_v<axis_t>) {
            // at(result,axis) = at(result,axis) + at(indices,axis);
            auto m_axis = nmtools_array{axis};
            auto axis_dim = len(m_axis);
            for (nm_size_t a_i=0; a_i<axis_dim; a_i++) {
                auto i = at(m_axis,a_i);
                at(result,i) = at(result,i) + at(indices,a_i+src_dim);
            }
        }

        return result;
    } // sliding_window

    struct normalize_sliding_window_arg_t {};

    template <typename src_shape_t, typename axis_t, typename arg_t>
    constexpr auto normalize_sliding_window_arg(const src_shape_t& src_shape, const axis_t& axis, const arg_t& arg)
    {
        using result_t = meta::resolve_optype_t<normalize_sliding_window_arg_t,src_shape_t,axis_t,arg_t>;

        auto result = result_t {};

        auto src_dim = len(src_shape);
        auto dst_dim = src_dim;

        if constexpr (is_none_v<axis_t> && meta::is_index_v<arg_t>) {
            dst_dim = src_dim;
        } else if constexpr (meta::is_index_v<axis_t> && meta::is_index_v<arg_t>) {
            dst_dim = 1;
        } else if constexpr (meta::is_index_array_v<arg_t>) {
            dst_dim = len(arg);
        } else if constexpr (meta::is_index_array_v<axis_t>) {
            dst_dim = len(axis);
        }

        if constexpr (meta::is_resizable_v<result_t>) {
            result.resize(dst_dim);
        }

        for (nm_size_t i=0; i<dst_dim; i++) {
            if constexpr (meta::is_index_v<arg_t>) {
                at(result,i) = arg;
            } else if constexpr (meta::is_index_array_v<arg_t>) {
                at(result,i) = at(arg,i);
            }
        }

        return result;
    }

    struct normalize_sliding_window_stride_t {};

    template <typename src_shape_t, typename window_shape_t, typename axis_t, typename stride_t>
    constexpr auto normalize_sliding_window_stride(const src_shape_t& src_shape, [[maybe_unused]] const window_shape_t& window_shape, const axis_t& axis, const stride_t& stride)
    {
        using result_t = meta::resolve_optype_t<normalize_sliding_window_stride_t,src_shape_t,window_shape_t,axis_t,stride_t>;
        using return_t = nmtools_maybe<result_t>;

        auto result = result_t {};

        auto src_dim = len(src_shape);
        [[maybe_unused]]
        auto res_dim = src_dim;

        if constexpr (is_none_v<axis_t> && meta::is_index_v<stride_t>) {
            res_dim += src_dim;
        } else if constexpr (meta::is_index_v<axis_t> && meta::is_index_v<stride_t>) {
            res_dim += 1;
        } else if constexpr (meta::is_index_array_v<stride_t>) {
            res_dim += len(stride);
        } else if constexpr (meta::is_index_array_v<axis_t>) {
            res_dim += len(axis);
        } else if constexpr (is_none_v<axis_t> && meta::is_index_array_v<window_shape_t> && meta::is_index_v<stride_t>) {
            res_dim += len(window_shape);
        }

        if constexpr (meta::is_resizable_v<result_t>) {
            result.resize(res_dim);
        }

        for (nm_size_t i=0; i<(nm_size_t)len(result); i++) {
            at(result,i) = 0;
        }

        if constexpr (meta::is_index_array_v<axis_t> && meta::is_index_array_v<stride_t>) {
            // axis can be duplicated, check for errors
            auto normalized_axis = normalize_axis(axis,src_dim);
            if (!has_value(normalized_axis)) {
                return return_t{meta::Nothing};
            } else {
                for (nm_size_t i=0; i<(nm_size_t)len(unwrap(normalized_axis)); i++) {
                    auto ai = at(unwrap(normalized_axis),i);
                    if (at(result,ai) == 0) {
                        // first time, simply store
                        at(result,ai) = at(stride,i);
                    } else {
                        // not first time, check for errors
                        auto si = at(stride,i);
                        if ((nm_size_t)at(result,ai) != (nm_size_t)si) {
                            return return_t{meta::Nothing};
                        }
                    }
                }
            }
        } else if constexpr (meta::is_index_array_v<axis_t> && meta::is_index_v<stride_t>) {
            auto normalized_axis = normalize_axis(axis,src_dim);
            if (!has_value(normalized_axis)) {
                return return_t{meta::Nothing};
            } else {
                for (nm_size_t i=0; i<(nm_size_t)len(unwrap(normalized_axis)); i++) {
                    auto ai = at(unwrap(normalized_axis),i);
                    at(result,ai) = stride;
                }
            }
        } else if constexpr (meta::is_index_v<axis_t>) {
            auto normalized_axis = normalize_axis(axis,src_dim);
            auto is_valid_stride = [&](){
                if constexpr (meta::is_index_v<stride_t>) {
                    return true;
                } else {
                    return len(stride) == 1;
                }
            }();
            if (!has_value(normalized_axis) || !is_valid_stride) {
                return return_t{meta::Nothing};
            } else {
                if constexpr (meta::is_index_v<stride_t>) {
                    at(result,unwrap(normalized_axis)) = stride;
                } else {
                    at(result,unwrap(normalized_axis)) = at(stride,meta::ct_v<0>);
                }
            }
        } else if constexpr (meta::is_index_v<stride_t> && meta::is_index_v<window_shape_t>) {
            // assume axis is None
            at(result,0) = stride;
        } else /* if constexpr (meta::is_none_v<axis_t> && meta::is_index_array_v<window_shape_t>) */ {
            // fill from 0
            for (nm_size_t i=0; i<(nm_size_t)len(window_shape); i++) {
                if constexpr (meta::is_index_v<stride_t>) {
                    at(result,i) = stride;
                } else {
                    // assume same len
                    at(result,i) = at(stride,i);
                }
            }
        }

        // fill the rest with 1
        for (nm_size_t i=0; i<(nm_size_t)res_dim; i++) {
            if (at(result,i) == 0) {
                at(result,i) = 1;
            }
        }

        return return_t{result};
    }

    struct slice_sliding_window_t {};

    template <typename src_shape_t
        , typename window_shape_t
        , typename axis_t
        , typename stride_t>
    constexpr auto slice_sliding_window(const src_shape_t& src_shape
        , const window_shape_t& window_shape
        , const axis_t& axis
        , const stride_t& stride)
    {
        if constexpr (meta::is_maybe_v<src_shape_t>
            || meta::is_maybe_v<window_shape_t>
            || meta::is_maybe_v<axis_t>
            || meta::is_maybe_v<stride_t>
        ) {
            using result_t = decltype(slice_sliding_window(
                unwrap(src_shape)
                , unwrap(window_shape)
                , unwrap(axis)
                , unwrap(stride)
            ));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_shape)
                    && has_value(window_shape)
                    && has_value(axis)
                    && has_value(stride)
                ? return_t{slice_sliding_window(
                    unwrap(src_shape)
                    , unwrap(window_shape)
                    , unwrap(axis)
                    , unwrap(stride)
                )}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<slice_sliding_window_t
                , src_shape_t
                , window_shape_t
                , axis_t
                , stride_t>;
            
            // TODO: support constant slice arg, then return without maybe type when possible
            using return_t = nmtools_maybe<result_t>;
            
            auto result = result_t {};

            auto src_dim = len(src_shape);

            auto normalized_window_shape = normalize_sliding_window_arg(src_shape,axis,window_shape);
            auto normalized_stride = normalize_sliding_window_stride(src_shape,window_shape,axis,stride);

            if (!has_value(normalized_stride) || !has_value(normalized_window_shape)) {
                return return_t{meta::Nothing};
            }

            auto m_window_shape = unwrap(normalized_window_shape);
            auto m_stride = unwrap(normalized_stride);

            [[maybe_unused]] auto window_dim = len(m_window_shape);
            [[maybe_unused]] auto stride_dim = len(m_stride);

            // here assume stride_dim == window_dim
            [[maybe_unused]]
            auto res_dim = src_dim + window_dim;

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(res_dim);
            }

            for (nm_size_t i=0; i<(nm_size_t)len(m_stride); i++) {
                at(result,i) = nmtools_tuple{None,None,at(m_stride,i)};
            }

            return return_t{result};
        }
    }
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct SHAPE_SLIDING_WINDOW_UNSUPPORTED : detail::fail_t {};

        template<typename...>
        struct SLIDING_WINDOW_UNSUPPORTED : detail::fail_t {};

        template<typename...>
        struct SLICE_SLIDING_WINDOW_UNSUPPORTED : detail::fail_t {};

        template<typename...>
        struct NORMALIZE_SLIDING_WINDOW_STRIDE_UNSUPPORTED : detail::fail_t {};
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

    template <typename src_shape_t, typename axis_t, typename arg_t>
    struct resolve_optype<
        void, index::normalize_sliding_window_arg_t, src_shape_t, axis_t, arg_t
    > {
        static constexpr auto vtype = [](){
            [[maybe_unused]] constexpr auto SRC_DIM = len_v<src_shape_t>;
            [[maybe_unused]] constexpr auto SRC_B_DIM = bounded_size_v<src_shape_t>;

            if constexpr (is_none_v<axis_t> && is_index_v<arg_t>) {
                if constexpr (SRC_DIM > 0) {
                    using type = nmtools_array<nm_size_t,SRC_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!meta::is_fail_v<decltype(SRC_B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,SRC_B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (is_index_v<axis_t> && is_index_v<arg_t>) {
                using type = nmtools_array<nm_size_t,1>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<arg_t>) {
                [[maybe_unused]] constexpr auto ARG_DIM = len_v<arg_t>;
                [[maybe_unused]] constexpr auto ARG_B_DIM = bounded_size_v<arg_t>;
                if constexpr (ARG_DIM > 0) {
                    using type = nmtools_array<nm_size_t,ARG_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(ARG_B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,ARG_B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            } else /* if constexpr (is_index_array_v<axis_t>)*/ {
                [[maybe_unused]] constexpr auto AXIS_DIM = len_v<axis_t>;
                [[maybe_unused]] constexpr auto AXIS_B_DIM = bounded_size_v<axis_t>;
                if constexpr (AXIS_DIM > 0) {
                    using type = nmtools_array<nm_size_t,AXIS_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(AXIS_B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,AXIS_B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // normalize_sliding_window_arg_t

    template <typename src_shape_t, typename window_shape_t, typename axis_t, typename stride_t>
    struct resolve_optype<
        void, index::normalize_sliding_window_stride_t, src_shape_t, window_shape_t, axis_t, stride_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>
                || !(is_index_array_v<window_shape_t> || is_index_v<window_shape_t>)
                || !(is_index_array_v<axis_t> || is_index_v<axis_t> || is_none_v<axis_t>)
                || !(is_index_array_v<stride_t> || is_index_v<stride_t>)
            ) {
                using type = error::NORMALIZE_SLIDING_WINDOW_STRIDE_UNSUPPORTED<src_shape_t,window_shape_t,axis_t,stride_t>;
                return as_value_v<type>;
            } else {
                [[maybe_unused]] constexpr auto SRC_DIM = len_v<src_shape_t>;
                [[maybe_unused]] constexpr auto SRC_B_DIM = bounded_size_v<src_shape_t>;
                if constexpr (is_none_v<axis_t> && is_index_v<stride_t>) {
                    if constexpr (SRC_DIM > 0) {
                        constexpr auto RES_DIM = SRC_DIM * 2;
                        using type = nmtools_array<nm_size_t,RES_DIM>;
                        return as_value_v<type>;
                    } else if constexpr (!is_fail_v<decltype(SRC_B_DIM)>) {
                        constexpr auto RES_B_DIM = SRC_B_DIM * 2;
                        using type = nmtools_static_vector<nm_size_t,RES_B_DIM>;
                        return as_value_v<type>;
                    } else {
                        // TODO: support small vector
                        using type = nmtools_list<nm_size_t>;
                        return as_value_v<type>;
                    }
                } else if constexpr (is_index_v<axis_t> && is_index_v<stride_t>) {
                    if constexpr (SRC_DIM > 0) {
                        constexpr auto RES_DIM = SRC_DIM + 1;
                        using type = nmtools_array<nm_size_t,RES_DIM>;
                        return as_value_v<type>;
                    } else if constexpr (!is_fail_v<decltype(SRC_B_DIM)>) {
                        constexpr auto RES_B_DIM = SRC_B_DIM + 1;
                        using type = nmtools_static_vector<nm_size_t,RES_B_DIM>;
                        return as_value_v<type>;
                    } else {
                        // TODO: support small vector
                        using type = nmtools_list<nm_size_t>;
                        return as_value_v<type>;
                    }
                } else if constexpr (is_index_array_v<stride_t>) {
                    [[maybe_unused]] constexpr auto STRIDE_DIM = len_v<stride_t>;
                    [[maybe_unused]] constexpr auto STRIDE_B_DIM = bounded_size_v<stride_t>;
                    if constexpr ((SRC_DIM > 0) && (STRIDE_DIM > 0)) {
                        constexpr auto RES_DIM = SRC_DIM + STRIDE_DIM;
                        using type = nmtools_array<nm_size_t,RES_DIM>;
                        return as_value_v<type>;
                    } else if constexpr (!is_fail_v<decltype(SRC_B_DIM)> && !is_fail_v<decltype(STRIDE_B_DIM)>) {
                        constexpr auto RES_B_DIM = SRC_B_DIM + STRIDE_B_DIM;
                        using type = nmtools_static_vector<nm_size_t,RES_B_DIM>;
                        return as_value_v<type>;
                    } else {
                        // TODO: support small vector
                        using type = nmtools_list<nm_size_t>;
                        return as_value_v<type>;
                    }
                } else if constexpr (is_index_array_v<axis_t>) {
                    [[maybe_unused]] constexpr auto AXIS_DIM = len_v<axis_t>;
                    [[maybe_unused]] constexpr auto AXIS_B_DIM = bounded_size_v<axis_t>;
                    if constexpr ((SRC_DIM > 0) && (AXIS_DIM > 0)) {
                        constexpr auto RES_DIM = SRC_DIM + AXIS_DIM;
                        using type = nmtools_array<nm_size_t,RES_DIM>;
                        return as_value_v<type>;
                    } else if constexpr (!is_fail_v<decltype(SRC_B_DIM)> && !is_fail_v<decltype(AXIS_B_DIM)>) {
                        constexpr auto RES_B_DIM = SRC_B_DIM + AXIS_B_DIM;
                        using type = nmtools_static_vector<nm_size_t,RES_B_DIM>;
                        return as_value_v<type>;
                    } else {
                        // TODO: support small vector
                        using type = nmtools_list<nm_size_t>;
                        return as_value_v<type>;
                    }
                } else /* if constexpr (is_none_v<axis_t> && is_index_array_v<window_shape_t> && is_index_v<stride_t>) */ {
                    [[maybe_unused]] constexpr auto WINDOW_DIM = len_v<window_shape_t>;
                    [[maybe_unused]] constexpr auto WINDOW_B_DIM = bounded_size_v<window_shape_t>;
                    if constexpr ((SRC_DIM > 0) && (WINDOW_DIM > 0)) {
                        constexpr auto RES_DIM = SRC_DIM + WINDOW_DIM;
                        using type = nmtools_array<nm_size_t,RES_DIM>;
                        return as_value_v<type>;
                    } else if constexpr (!is_fail_v<decltype(SRC_B_DIM)> && !is_fail_v<decltype(WINDOW_B_DIM)>) {
                        constexpr auto RES_B_DIM = SRC_B_DIM + WINDOW_B_DIM;
                        using type = nmtools_static_vector<nm_size_t,RES_B_DIM>;
                        return as_value_v<type>;
                    } else {
                        // TODO: support small vector
                        using type = nmtools_list<nm_size_t>;
                        return as_value_v<type>;
                    }
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

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

    template <typename src_shape_t, typename window_shape_t, typename axis_t, typename stride_t>
    struct resolve_optype<
        void, index::slice_sliding_window_t, src_shape_t, window_shape_t, axis_t, stride_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (
                !is_index_array_v<src_shape_t>
                || !(is_index_v<window_shape_t> || is_index_array_v<window_shape_t>)
                || !(is_index_v<axis_t> || is_index_array_v<axis_t> || is_none_v<axis_t>)
                || !(is_index_v<stride_t> || is_index_array_v<stride_t> || is_none_v<stride_t>)
            ) {
                using type = error::SLICE_SLIDING_WINDOW_UNSUPPORTED<src_shape_t,window_shape_t,axis_t,stride_t>;
                return as_value_v<type>;
            } else {
                using m_window_shape_t = resolve_optype_t<index::normalize_sliding_window_arg_t,src_shape_t,axis_t,window_shape_t>;
                using m_stride_t = resolve_optype_t<index::normalize_sliding_window_arg_t,src_shape_t,axis_t,stride_t>;

                [[maybe_unused]] constexpr auto SRC_DIM = len_v<src_shape_t>;
                [[maybe_unused]] constexpr auto SRC_B_DIM = bounded_size_v<src_shape_t>;

                [[maybe_unused]] constexpr auto WINDOW_DIM = len_v<m_window_shape_t>;
                [[maybe_unused]] constexpr auto WINDOW_B_DIM = bounded_size_v<m_window_shape_t>;

                [[maybe_unused]] constexpr auto STRIDE_DIM = len_v<m_stride_t>;
                [[maybe_unused]] constexpr auto STRIDE_B_DIM = bounded_size_v<m_stride_t>;

                using slice_t = nmtools_tuple<none_t,none_t,nm_size_t>;

                if constexpr ((SRC_DIM > 0) && (WINDOW_DIM > 0)) {
                    using type = nmtools_array<slice_t,SRC_DIM + WINDOW_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(SRC_B_DIM)> && !is_fail_v<decltype(WINDOW_B_DIM)>) {
                    using type = nmtools_static_vector<slice_t,SRC_B_DIM+WINDOW_B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<slice_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_SLIDING_WINDOW_HPP

#ifndef NMTOOLS_ARRAY_VIEW_SLIDING_WINDOW_HPP
#define NMTOOLS_ARRAY_VIEW_SLIDING_WINDOW_HPP

#include "nmtools/core/indexing.hpp"
#include "nmtools/core/slice.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/index/normalize_axis.hpp"
#include "nmtools/core/decorator.hpp"
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

    template <typename array_t, typename window_shape_t, typename axis_t=none_t, typename stride_t=none_t>
    constexpr auto sliding_window(const array_t& array
        , const window_shape_t& window_shape, const axis_t& axis=axis_t{}, const stride_t& stride=stride_t{})
    {
        auto f = [](const auto& array, const auto& window_shape, const auto& axis){
            auto src_shape = shape<true>(array);
            auto indexer   = sliding_window_indexer(src_shape,window_shape,axis);
            return indexing(array,indexer);
        };
        auto window = lift_indexing(f,array,window_shape,axis);
        if constexpr (is_none_v<stride_t>) {
            return window;
        } else {
            auto src_shape = shape<true>(array);
            auto slice_args = index::slice_sliding_window(src_shape,window_shape,axis,stride);
            return view::apply_slice(window,slice_args);
        }
    } // sliding_window
} // namespace nmtools::view

namespace nmtools::array
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::sliding_window_t<args_t...>, max_dim
    > {
        using attribute_type = view::sliding_window_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape    = as_static<max_dim>(attribute.src_shape);
            auto window_shape = as_static<max_dim>(attribute.window_shape);
            auto axis         = as_static<max_dim>(attribute.axis);
            return view::sliding_window_indexer(src_shape,window_shape,axis);
        }
    };
} // namespace nmtools::array

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

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SLIDING_WINDOW_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SLIDING_WINDOW_HPP

#include "nmtools/core/functor.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct sliding_window
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::sliding_window(args...);
            }
        };
    } // namespace fun

    constexpr auto inline sliding_window = functor_t{unary_fmap_t<fun::sliding_window>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SLIDING_WINDOW_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_RESIZE_HPP
#define NMTOOLS_ARRAY_ARRAY_RESIZE_HPP

#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename window_shape_t, typename axis_t=none_t>
    constexpr auto sliding_window(const array_t& array, const window_shape_t& window_shape, const axis_t& axis=axis_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto sliding_window = view::sliding_window(array,window_shape,axis);
        return eval(
            sliding_window
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // sliding_window
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_RESIZE_HPP