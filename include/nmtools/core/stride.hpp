#ifndef NMTOOLS_CORE_STRIDE_HPP
#define NMTOOLS_CORE_STRIDE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core/decorator.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/index/compute_strides.hpp"
#include "nmtools/index/compute_offset.hpp"
#include "nmtools/index/product.hpp"

namespace nmtools::index
{
    struct flatten_nested_shape_t {};

    template <typename shape_t>
    constexpr auto flatten_nested_shape(const shape_t& shape)
    {
        if constexpr (is_maybe_v<shape_t>) {
            using result_t = decltype(flatten_nested_shape(unwrap(shape)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(shape)
                ? return_t{flatten_nested_shape(shape)}
                : return_t{Nothing}
            );
        } else {
            using result_t = resolve_optype_t<flatten_nested_shape_t,shape_t>;

            auto result = result_t {};

            if constexpr (!is_fail_v<result_t>
                && !is_constant_index_array_v<result_t>
            ) {
                [[maybe_unused]]
                auto n = len(shape);

                if constexpr (is_resizable_v<result_t>) {
                    result.resize(n);
                }

                constexpr auto N = len_v<shape_t>;
                if constexpr (N > 0) {
                    template_for<N>([&](auto i){
                        using result_i_t = decltype(at(result,i));
                        auto shape_i = at(shape,i);
                        if constexpr (is_index_array_v<decltype(shape_i)>
                            && !is_constant_index_v<result_i_t>
                        ) {
                            auto product = index::product(shape_i);
                            if (has_value(product)) {
                                at(result,i) = product;
                            }
                        } else if constexpr (!is_constant_index_v<result_i_t>) {
                            if (has_value(shape_i)) {
                                at(result,i) = shape_i;
                            }
                        }
                    });
                } else {
                    // TODO: handle runtime nested index array
                    for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                        at(result,i) = at(shape,i);
                    }
                }
            }

            return result;
        }
    }
} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct FLATTEN_NESTED_SHAPE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename shape_t>
    struct resolve_optype<
        void, index::flatten_nested_shape_t, shape_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<shape_t>) {
                using type = error::FLATTEN_NESTED_SHAPE_UNSUPPORTED<shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<shape_t>
                || is_mixed_index_array_v<shape_t>
            ) {
                // TODO: handle mixed index array
                // TODO: handle constant nested index array
                constexpr auto shape  = to_value_v<shape_t>;
                constexpr auto result = index::flatten_nested_shape(shape);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    constexpr auto res_i = at(result,I);
                    if constexpr (has_value(res_i)) {
                        using type = append_type_t<init_t,ct<unwrap(res_i)>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_t,nm_size_t>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]]
                constexpr auto MAX_LEN = max_len_v<shape_t>;
                constexpr auto LEN = len_v<shape_t>;

                using index_t = conditional_t<is_nullable_index_array_v<shape_t>, null_size_t, size_t>;

                if constexpr (LEN > 0) {
                    using type = nmtools_array<index_t,LEN>;
                    return as_value_v<type>;
                } else if constexpr (MAX_LEN > 0) {
                    using type = nmtools_static_vector<index_t,MAX_LEN>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // nmtools::meta

namespace nmtools::view
{
    // stride is only for 1D array
    template <typename src_shape_t, typename shape_t, typename striding_t, typename bsize_t>
    struct stride_t
        : base_indexer_t<stride_t<src_shape_t,shape_t,striding_t,bsize_t>>
    {
        // shape maybe nested
        using shape_type     = meta::fwd_attribute_t<shape_t>;
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using dst_shape_type = resolve_optype_t<index::flatten_nested_shape_t,shape_type>;
        using striding_type  = meta::fwd_attribute_t<striding_t>;

        static constexpr auto dst_size_vtype = [](){
            if constexpr (is_none_v<bsize_t> && is_index_array_v<dst_shape_type>) {
                using type = decltype(index::product(declval<dst_shape_type>()));
                return as_value_v<type>;
            } else {
                using type = conditional_t<is_index_v<bsize_t>,bsize_t,nm_size_t>;
                return as_value_v<type>;
            }
        }();
        using dst_size_type = type_t<decltype(dst_size_vtype)>;

        static constexpr auto src_dim_vtype = [](){
            constexpr auto N = len_v<src_shape_type>;
            if constexpr (N > 0) {
                using type = ct<N>;
                return as_value_v<type>;
            } else {
                using type = nm_size_t;
                return as_value_v<type>;
            }
        }();
        using src_dim_type = type_t<decltype(src_dim_vtype)>;

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const shape_type     m_shape;
        const dst_shape_type dst_shape;
        const striding_type  striding;
        const dst_size_type  dst_size;
        const src_dim_type   src_dim;

        constexpr stride_t(const src_shape_t& src_shape, const shape_t& shape, const striding_t& striding, const bsize_t bsize)
            : src_shape(fwd_attribute(src_shape))
            , m_shape(fwd_attribute(shape))
            , dst_shape(index::flatten_nested_shape(m_shape))
            , striding(fwd_attribute(striding))
            , dst_size([&](){
                if constexpr (is_none_v<bsize_t> && is_index_array_v<dst_shape_type>) {
                    return index::product(dst_shape);
                } else {
                    return fwd_attribute(bsize);
                }
            }())
            , src_dim([&](){
                if constexpr (is_constant_index_v<src_dim_type>) {
                    return src_dim_type{};
                } else {
                    return len(src_shape);
                }
            }())
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            // TODO: handle non buffer
            // TODO: allow to return a single index
            return pack_indices(index::compute_offset(indices,m_shape,striding));
        }

        template <typename...args_t>
        constexpr auto operator==(const stride_t<args_t...>& other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(m_shape,other.m_shape)
                && utils::isequal(dst_shape,other.dst_shape)
                && utils::isequal(striding,other.striding)
            ;
        }
    };

    template <typename src_shape_t, typename shape_t, typename striding_t, typename bsize_t>
    constexpr auto strider(const src_shape_t& src_shape, const shape_t& shape, const striding_t& striding, bsize_t bsize)
    {
        if constexpr (is_maybe_v<src_shape_t> || is_maybe_v<shape_t> || is_maybe_v<striding_t> || is_maybe_v<bsize_t>) {
            using result_t = decltype(strider(unwrap(src_shape),unwrap(shape),unwrap(striding),unwrap(bsize)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_shape) && has_value(shape) && has_value(striding) && has_value(bsize)
                ? return_t{strider(unwrap(src_shape),unwrap(shape),unwrap(striding),unwrap(bsize))}
                : return_t{Nothing}
            );
        } else {
            // TODO: check dim of src is exactly 1
            // TODO: check if dim of shape match dim of striding
            return stride_t{src_shape,shape,striding,bsize};
        }
    }

    template <typename array_t, typename shape_t, typename striding_t, typename bsize_t=none_t>
    constexpr auto stride(const array_t& array, const shape_t& shape, const striding_t& striding, bsize_t bsize=bsize_t{})
    {
        // TODO: check if array is 1D
        // TODO: validate shape w/ striding
        auto f = [](const auto& array, const auto& shape, const auto& striding, const auto bsize){
            const auto src_shape = nmtools::shape<true>(array);
            auto indexer = strider(src_shape,shape,striding,bsize);
            return indexing(array,indexer);
        };
        return lift_indexing(f,array,shape,striding,bsize);
    }
} // nmtools::view

namespace nmtools
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::stride_t<args_t...>, max_dim
    > {
        using indexer_type = view::stride_t<args_t...>;

        indexer_type indexer;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(indexer.src_shape);
            auto m_shape   = as_static<max_dim>(indexer.m_shape);
            auto striding  = as_static<max_dim>(indexer.striding);
            auto bsize     = as_static<max_dim>(indexer.bsize);
            return view::strider(src_shape,shape,striding,bsize);
        }
    };
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::stride_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::stride_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "stride";
            str += "{";
            str += ".src_shape=";   str += to_string(kwargs.src_shape,Compact);
            str += ",.shape=";      str += to_string(kwargs.shape,Compact);
            str += ",.striding=";   str += to_string(kwargs.striding,Compact);
            str += ",.bsize=";      str += to_string(kwargs.dst_size,Compact);
            str += "}";
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_CORE_STRIDE_HPP