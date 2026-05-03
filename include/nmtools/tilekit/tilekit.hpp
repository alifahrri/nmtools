#ifndef NMTOOLS_TILEKIT_TILEKIT_HPP
#define NMTOOLS_TILEKIT_TILEKIT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core.hpp"
#include "nmtools/array/tiling_window.hpp"
#include "nmtools/index/array.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/index/add_indices.hpp"
#include "nmtools/ndarray/array.hpp"
#include "nmtools/context/default.hpp"

// useful for work partitioning
#include "nmtools/array/transpose.hpp"
#include "nmtools/array/moveaxis.hpp"

namespace nmtools::tilekit
{
    template <typename ctx_t, typename array_t, typename tile_shape_t, typename padding_t, typename=void>
    struct load_t;

    template <typename ctx_t, typename output_t, typename padding_t, typename=void>
    struct store_t;

    template <typename ctx_t, typename array_t, typename offset_t, typename tile_shape_t, typename padding_t=ct<0>>
    __attribute__((always_inline))
    constexpr auto load(ctx_t&& ctx, const array_t& array, const offset_t& offset, const tile_shape_t& tile_shape, const padding_t& padding=padding_t{})
    {
        auto load = load_t<remove_cvref_t<ctx_t>,array_t,tile_shape_t,padding_t>{};
        return load(nmtools::forward<ctx_t>(ctx),array,offset,tile_shape,padding);
    }

    template <typename ctx_t, typename output_t, typename offset_t, typename result_t, typename padding_t=ct<0>>
    constexpr auto store([[maybe_unused]] ctx_t&& ctx, output_t& output, const offset_t& offset, const result_t& result, const padding_t& padding=padding_t{})
    {
        auto store = store_t<remove_cvref_t<ctx_t>,output_t,padding_t>{};
        return store(nmtools::forward<ctx_t>(ctx),output,offset,result,padding);
    }
}

// nditer
/******************************************************************************************************************* */

namespace nmtools::tilekit
{
    template <typename array_shape_t, typename block_shape_t, typename tile_shape_t>
    struct nditer_t
    {
        // TODO: constraint the array shape to be fixed len
        // as well as the block shape
        // tile shape must be constant index
        using array_shape_type  = array_shape_t;
        using block_shape_type  = block_shape_t;
        using block_stride_type = resolve_optype_t<index::compute_strides_t,block_shape_type>;
        using tile_shape_type   = tile_shape_t;
        using size_type = resolve_optype_t<index::product_t,block_shape_t>;

        array_shape_type  array_shape_;
        block_shape_type  block_shape_;
        block_stride_type block_stride_;
        tile_shape_type   tile_shape_;

        size_type size_;

        constexpr nditer_t(const array_shape_t& array_shape
            , const block_shape_t& block_shape
            , const tile_shape_t& tile_shape)
            : array_shape_(array_shape)
            , block_shape_(block_shape)
            , block_stride_(index::compute_strides(block_shape))
            , tile_shape_(tile_shape)
            , size_(index::product(block_shape))
        {}

        template <typename idx_t=none_t>
        constexpr auto iter_shape(idx_t idx=idx_t{}) const noexcept
        {
            if constexpr (is_none_v<idx_t>) {
                return block_shape_;
            } else {
                return block_shape_[idx];
            }
        }

        constexpr auto iter_dim() const noexcept
        {
            return len(block_shape_);
        }

        constexpr auto dim() const noexcept
        {
            return ct_v<len_v<array_shape_t> + 1>;
        }

        constexpr auto shape() const noexcept
        {
            constexpr auto DIM = len_v<array_shape_t>;
            using result_t = nmtools_array<nm_size_t,DIM+1>;

            auto result = result_t {};
            template_for<DIM>([&](auto i){
                result[i] = at(block_shape_,i);
            });
            result[DIM] = DIM;
            return result;
        }

        constexpr auto iter_size() const noexcept
        {
            return size_;
        }

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            auto dst_indices = index::array(index::pack_indices(indices...));
            if constexpr (sizeof...(size_types) == len_v<array_shape_t>) {
                // TODO: generalize this "packed element type" support
                auto src_indices = dst_indices * tile_shape_;
                return src_indices;
            } else {
                // TODO: return single
                auto src_indices = dst_indices.remove_dims(ct_v<-1>) * tile_shape_;
                auto last_idx = dst_indices[ct_v<-1>];
                return src_indices[last_idx];
            }
        }
    }; // nditer_t

    using view::transpose;

    template <typename view_t, typename idx_t=none_t>
    constexpr auto iter_shape(const view_t& view, idx_t idx={})
    {
        // TODO: check if the underlying array is nditer_t
        auto src_shape = nmtools::shape(view);
        if constexpr (is_none_v<idx_t>) {
            constexpr auto DIM = len_v<view_t>;
            using result_t = nmtools_array<nm_size_t,DIM-1>;
            auto result = result_t{};
            for (nm_size_t i=0; i<(nm_size_t)DIM-1; i++) {
                result[i] = src_shape[i];
            }
            return result;
        } else {
            return src_shape[idx];
        }
    } // iter_shape

    // TODO: generalize this "packed element type" support
    template <typename view_t, typename...size_types>
    __attribute__((always_inline))
    constexpr auto packed_at(const view_t& view, size_types...indices)
    {
        // TODO: check if the underlying array is nditer_t
        constexpr auto DIM = fixed_dim_v<view_t>;
        constexpr auto num_indices = sizeof...(size_types);
        if constexpr (num_indices == DIM) {
            return view(indices...);
        } else {
            using result_t = nmtools_array<nm_size_t,DIM-1>;
            auto result = result_t {};
            auto last_dim = nmtools::shape(view)[DIM-1];
            for (nm_size_t i=0; i<(nm_size_t)last_dim; i++) {
                result[i] = view(indices...,i);
            }
            return result;
        }
    } // packed_at

    template <typename iter_t, typename source_t, typename destination_t>
    constexpr auto moveaxis(const iter_t& iter, source_t src, destination_t dst)
    {
        constexpr auto SRC = to_value_v<source_t>;
        constexpr auto DST = to_value_v<destination_t>;

        auto moveaxis = [&](auto src, auto dst){
            // TODO: transform/normalize negative axis with DIM-1 length
            constexpr auto DIM = fixed_dim_v<iter_t>;
            auto normalized_src = unwrap(index::normalize_axis(src,ct_v<DIM-1>));
            auto normalized_dst = unwrap(index::normalize_axis(dst,ct_v<DIM-1>));
            auto view = view::moveaxis(iter,normalized_src,normalized_dst);
            if constexpr (is_maybe_v<decltype(view)>) {
                return *view;
            } else {
                return view;
            }
        };

        if constexpr (!is_fail_v<decltype(src)> && !is_fail_v<decltype(dst)>) {
            if constexpr (SRC == DST) {
                return iter;
            } else {
                return moveaxis(src,dst);
            }
        } else {
            return moveaxis(src,dst);
        }
    }

    struct compute_block_shape_t {};

    template <typename array_shape_t, typename tile_shape_t, typename padding_t=ct<0>>
    constexpr auto compute_block_shape(const array_shape_t& array_shape, const tile_shape_t& tile_shape, padding_t padding=padding_t{})
    {
        using result_t = resolve_optype_t<compute_block_shape_t,array_shape_t,tile_shape_t,padding_t>;

        auto result = result_t {};

        if constexpr (!is_fail_v<result_t>
            && !is_constant_index_array_v<result_t>
        ) {
            constexpr auto DIM = len_v<result_t>;

            if constexpr (DIM > 0) {
                template_for<DIM>([&](auto i){
                    if constexpr (!is_constant_index_v<decltype(at(result,i))>) {
                        const auto& a_i = at(array_shape,i);
                        const auto& t_i = at(tile_shape,i);
                        if (has_value(a_i) && has_value(t_i)) {
                            at(result,i) = (a_i / t_i) + (padding ? ((a_i % t_i) ? 1 : 0) : 0);
                        }
                    }
                });
            } else {
                // TODO: check if len(array_shape) == len(tile_shape);
                auto dim = len(array_shape);
                if constexpr (is_resizable_v<result_t>) {
                    result.resize(dim);
                }
                for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                    const auto& a_i = at(array_shape,i);
                    const auto& t_i = at(tile_shape,i);
                    if (has_value(a_i) && has_value(t_i)) {
                        at(result,i) = (a_i / t_i) + (padding ? ((a_i % t_i) ? 1 : 0) : 0);
                    }
                }
            }
        }

        return result;
    }
}

// nditer meta
/******************************************************************************************************************* */

namespace nmtools::meta
{
    namespace error {
        template <typename...>
        struct COMPUTE_BLOCK_SHAPE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename...args_t>
    struct is_ndarray<
        tilekit::nditer_t<args_t...>
    > : true_type {};

    template <typename array_shape_t, typename...args_t>
    struct fixed_dim<
        tilekit::nditer_t<array_shape_t, args_t...>
    > {
        static constexpr auto value = len_v<array_shape_t> + 1;
    };

    template <typename...args_t>
    struct get_element_type<
        tilekit::nditer_t<args_t...>
    > {
        // quick
        using type = nm_size_t;
    };

    template <typename array_shape_t, typename tile_shape_t, typename padding_t>
    struct resolve_optype<
        void, tilekit::compute_block_shape_t, array_shape_t, tile_shape_t, padding_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<array_shape_t>
                || !is_index_array_v<tile_shape_t>
                || !is_index_v<padding_t>
            ) {
                using type = error::COMPUTE_BLOCK_SHAPE_UNSUPPORTED<array_shape_t,tile_shape_t,padding_t>;
                return as_value_v<type>;
            } else if constexpr (
                (is_constant_index_array_v<array_shape_t> || is_mixed_index_array_v<array_shape_t>)
                && (is_constant_index_array_v<tile_shape_t> || is_mixed_index_array_v<tile_shape_t>)
                && (is_constant_index_v<padding_t>)
            ) {
                constexpr auto array_shape = to_value_v<array_shape_t>;
                constexpr auto tile_shape  = to_value_v<tile_shape_t>;
                constexpr auto padding     = to_value_v<padding_t>;
                constexpr auto result = tilekit::compute_block_shape(array_shape,tile_shape,padding);
                using ::nmtools::at, ::nmtools::len;
                constexpr auto N = len(result);
                // check if should return array
                constexpr auto return_array = [&](){
                    auto all_none = !has_value(at(result,0));
                    for (nm_size_t i=1; i<(nm_size_t)N; i++) {
                        all_none &= !has_value(at(result,i));
                    }
                    return all_none;
                }();
                if constexpr (return_array) {
                    using type = nmtools_array<nm_size_t,N>;
                    return as_value_v<type>;
                } else {
                    return template_reduce<N>([&](auto init, auto I){
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
                }
            } else if constexpr (
                is_nullable_index_array_v<array_shape_t>
                || is_nullable_index_array_v<tile_shape_t>
            ) {
                using type = conditional_t<
                    is_nullable_index_array_v<array_shape_t>
                    , array_shape_t
                    , tile_shape_t
                >;
                return as_value_v<type>;
            } else {
                constexpr auto A_DIM = len_v<array_shape_t>;
                constexpr auto T_DIM = len_v<tile_shape_t>;
                [[maybe_unused]] constexpr auto A_MAX_DIM = max_len_v<array_shape_t>;
                [[maybe_unused]] constexpr auto T_MAX_DIM = max_len_v<tile_shape_t>;
                if constexpr ((A_DIM > 0) && (T_DIM > 0)) {
                    // TODO: assert if A_DIM == T_DIM
                    using type = nmtools_array<nm_size_t,A_DIM>;
                    return as_value_v<type>;
                } else if constexpr (A_MAX_DIM > 0) {
                    using type = nmtools_static_vector<nm_size_t,A_MAX_DIM>;
                    return as_value_v<type>;
                } else if constexpr (T_MAX_DIM > 0) {
                    using type = nmtools_static_vector<nm_size_t,T_MAX_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

/******************************************************************************************************************* */

// tilekit utility

namespace nmtools::tilekit
{
    template <typename array_t>
    constexpr auto shape(const array_t& array)
    {
        return index::array(nmtools::shape(array));
    }

    template <typename index_t>
    constexpr auto index(const index_t& idx)
    {
        return nmtools::index::array(idx);
    }

    template <typename block_shape_t>
    constexpr auto product(const block_shape_t& b_shape)
    {
        return nmtools::index::product(b_shape);
    }

    template <typename block_shape_t, typename tile_shape_t>
    struct ndoffset_t
    {
        using block_shape_type  = block_shape_t;
        using block_stride_type = meta::resolve_optype_t<index::compute_strides_t,block_shape_type>;
        using tile_shape_type   = tile_shape_t;
        using size_type = meta::resolve_optype_t<index::product_t,block_shape_t>;

        block_shape_type  block_shape_;
        block_stride_type block_stride_;
        tile_shape_type   tile_shape_;

        size_type size_;

        constexpr ndoffset_t(const block_shape_t& block_shape
            , const tile_shape_t& tile_shape)
            : block_shape_(block_shape)
            , block_stride_(index::compute_strides(block_shape))
            , tile_shape_(tile_shape)
            , size_(index::product(block_shape))
        {}

        constexpr auto size() const noexcept
        {
            return size_;
        }

        template <typename index_t>
        constexpr auto operator[](index_t i) const
        {
            auto indices = index::compute_indices(i,block_shape_,block_stride_);
            // assume fixed dim
            constexpr auto DIM = len_v<decltype(indices)>;
            meta::template_for<DIM>([&](auto i){
                constexpr auto I = decltype(i)::value;
                nmtools::get<I>(indices) *= nmtools::get<I>(tile_shape_);
            });
            return indices;
        }
    };

    template <typename array_shape_t, typename tile_shape_t, typename padding_t=ct<0>>
    constexpr auto ndoffset([[maybe_unused]] const array_shape_t& a_shape
        , [[maybe_unused]] const tile_shape_t& t_shape
        , padding_t padding=padding_t{})
    {
        auto b_shape = compute_block_shape(a_shape,t_shape,padding);
        return ndoffset_t(b_shape,t_shape);
    }

    template <typename array_shape_t, typename tile_shape_t, typename padding_t=ct<0>>
    constexpr auto nditer([[maybe_unused]] const array_shape_t& a_shape
        , [[maybe_unused]] const tile_shape_t& t_shape
        , padding_t padding=padding_t{})
    {
        auto b_shape = compute_block_shape(a_shape,t_shape,padding);
        return nditer_t(a_shape,b_shape,t_shape);
    }
} // namespace nmtools::tilekit

#endif // NMTOOLS_TILEKIT_TILEKIT_HPP