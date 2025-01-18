#ifndef NMTOOLS_ARRAY_EVAL_SIMD_INDEX_MATMUL_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_INDEX_MATMUL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/array/evaluator/simd/index/common.hpp"

namespace nmtools::index
{
    template <typename index_t=size_t
        , auto N_ELEM_PACK
        , typename out_shape_t
        , typename lhs_shape_t
        , typename rhs_shape_t>
    auto matmul_simd_shape(meta::as_type<N_ELEM_PACK>
        , [[maybe_unused]] const out_shape_t& out_shape
        , const lhs_shape_t&
        , const rhs_shape_t&)
    {
        using result_t = out_shape_t;

        auto result = result_t{};

        if constexpr (!meta::is_constant_index_array_v<result_t>) {
            auto dim = len(out_shape);
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dim);
            }
            for (size_t i=0; i<dim; i++) {
                at(result,i) = at(out_shape,i);
            }
        }

        return result;
    }

    template <typename index_t=size_t
        , auto N_ELEM_PACK
        , typename out_offset_t
        , typename out_shape_t
        , typename lhs_shape_t
        , typename rhs_shape_t>
    constexpr auto matmul_simd_inner_size(meta::as_type<N_ELEM_PACK>
        , [[maybe_unused]] const out_offset_t out_offset
        , [[maybe_unused]] const out_shape_t& out_shape
        , [[maybe_unused]] const lhs_shape_t& lhs_shape
        , [[maybe_unused]] const rhs_shape_t& rhs_shape)
    {
        // assume the lhs' layout is row major and the rhs' layout is col major
        // assume lhs' cols == rhs' rows

        auto n_cols = at(lhs_shape,meta::ct_v<-1>);
        auto n_simd = n_cols / N_ELEM_PACK;
        auto n_rest = (n_cols % N_ELEM_PACK) ? 1 : 0; // now we use padding, so the rest must be 1 or 0

        return (n_simd + n_rest);
    }

    template <typename index_t=size_t
        , auto N_ELEM_PACK
        , typename out_offset_t
        , typename inner_step_t
        , typename out_shape_t
        , typename lhs_shape_t
        , typename rhs_shape_t>
    constexpr auto matmul_simd_inner(meta::as_type<N_ELEM_PACK>
        , [[maybe_unused]] const out_offset_t out_offset
        , [[maybe_unused]] const inner_step_t inner_step
        , [[maybe_unused]] const out_shape_t& out_shape
        , [[maybe_unused]] const lhs_shape_t& lhs_shape
        , [[maybe_unused]] const rhs_shape_t& rhs_shape)
    {
        using tagged_index_t = nmtools_tuple<SIMD,index_t>;
        using result_t = nmtools_array<tagged_index_t,3>;

        // assume output layout is row major
        // assume the lhs' layout is row major and the rhs' layout is col major
        // assume lhs' cols == rhs' rows

        const auto n_fmadd = at(lhs_shape,meta::ct_v<-1>);
        const auto n_simd = n_fmadd / N_ELEM_PACK;
        const auto n_rest = n_fmadd - (n_simd * N_ELEM_PACK);

        const auto out_cols = at(out_shape,meta::ct_v<-1>);

        const auto out_row = out_offset / out_cols;
        const auto out_col = out_offset % out_cols;

        const auto lhs_offset = out_row * n_fmadd;
        const auto rhs_offset = out_col * n_fmadd;

        const auto res_l = lhs_offset + (inner_step * N_ELEM_PACK);
        const auto res_r = rhs_offset + (inner_step * N_ELEM_PACK);

        const auto tag_l = (nm_size_t(inner_step * N_ELEM_PACK + N_ELEM_PACK) <= nm_size_t(n_fmadd)) ? SIMD::PACKED : static_cast<SIMD>(N_ELEM_PACK - n_rest);
        const auto tag_r = (nm_size_t(inner_step * N_ELEM_PACK + N_ELEM_PACK) <= nm_size_t(n_fmadd)) ? SIMD::PACKED : static_cast<SIMD>(N_ELEM_PACK - n_rest);

        auto result  = result_t{};
        at(result,0) = tagged_index_t{SIMD::SCALAR,static_cast<index_t>(out_offset)};
        at(result,1) = tagged_index_t{tag_l,static_cast<index_t>(res_l)};
        at(result,2) = tagged_index_t{tag_r,static_cast<index_t>(res_r)};

        return result;
    }

    // enumerate on inner loop
    // e.g. matmul_simd_inne with fixed out_offset and running inner_step
    template <typename index_t, auto N_ELEM_PACK, typename out_offset_t, typename out_shape_t, typename lhs_shape_t, typename rhs_shape_t>
    struct matmul_simd_inner_enumerator_t
    {
        using out_offset_type = const out_offset_t;
        using out_shape_type  = const out_shape_t;
        using lhs_shape_type  = const lhs_shape_t;
        using rhs_shape_type  = const rhs_shape_t;
        using inner_step_type = const index_t;
        using size_type       = index_t; // assume unsigned (?)

        meta::as_type<N_ELEM_PACK> n_elem_pack;
        out_offset_type out_offset;
        out_shape_type  out_shape;
        lhs_shape_type  lhs_shape;
        rhs_shape_type  rhs_shape;

        matmul_simd_inner_enumerator_t(meta::as_type<N_ELEM_PACK>, out_offset_t out_offset, const out_shape_t& out_shape, const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
            : n_elem_pack{}
            , out_offset(out_offset)
            , out_shape(out_shape)
            , lhs_shape(lhs_shape)
            , rhs_shape(rhs_shape)
        {}

        constexpr auto size() const noexcept
        {
            return matmul_simd_inner_size(n_elem_pack,out_offset,out_shape,lhs_shape,rhs_shape);
        }

        constexpr auto operator[](size_type i) const noexcept
        {
            return matmul_simd_inner(n_elem_pack,out_offset,/*inner_step*/i,out_shape,lhs_shape,rhs_shape);
        }

        // proxy to track i (inner_step) from range for loop
        struct ref_t
        {
            using size_type = typename matmul_simd_inner_enumerator_t::size_type;

            const matmul_simd_inner_enumerator_t& enumerator;
            size_type inner_step = 0;

            constexpr decltype(auto) operator*() const
            {
                return enumerator[inner_step];
            } 
            
            constexpr bool operator==(const ref_t& rhs) const
            {
                return inner_step == rhs.inner_step;
            }

            constexpr bool operator!=(const ref_t& rhs) const
            {
                return !operator==(rhs);
            }

            constexpr auto operator++()
            {
                inner_step++;
            }
        };
    }; // matmul_simd_inner_enumerator_t

    template <typename index_t=size_t, auto N_ELEM_PACK, typename...args_t>
    constexpr auto begin(const matmul_simd_inner_enumerator_t<index_t,N_ELEM_PACK,args_t...>& enumerator)
    {
        using enumerator_t = meta::remove_cvref_t<decltype(enumerator)>;
        using result_t = typename enumerator_t::ref_t;
        return result_t{enumerator,0};
    }

    template <typename index_t=size_t, auto N_ELEM_PACK, typename...args_t>
    constexpr auto end(const matmul_simd_inner_enumerator_t<index_t,N_ELEM_PACK,args_t...>& enumerator)
    {
        using enumerator_t = meta::remove_cvref_t<decltype(enumerator)>;
        using result_t = typename enumerator_t::ref_t;
        return result_t{enumerator,enumerator.size()};
    }

    template <typename index_t=size_t, auto N_ELEM_PACK, typename out_offset_t, typename out_shape_t, typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto matmul_simd_inner_enumerator(meta::as_type<N_ELEM_PACK> n_elem_pack, out_offset_t out_offset, const out_shape_t& out_shape, const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
    {
        using enumerator_t = matmul_simd_inner_enumerator_t<index_t,N_ELEM_PACK,out_offset_t,out_shape_t,lhs_shape_t,rhs_shape_t>;
        return enumerator_t(
            n_elem_pack
            , out_offset
            , out_shape
            , lhs_shape
            , rhs_shape
        );
    }

    template <typename index_t, auto N_ELEM_PACK, typename out_shape_t, typename lhs_shape_t, typename rhs_shape_t>
    struct matmul_simd_enumerator_t
    {
        using out_shape_type  = const out_shape_t;
        using lhs_shape_type  = const lhs_shape_t;
        using rhs_shape_type  = const rhs_shape_t;
        using size_type = index_t; // assume unsigned (?)

        meta::as_type<N_ELEM_PACK> n_elem_pack;
        out_shape_type  out_shape;
        lhs_shape_type  lhs_shape;
        rhs_shape_type  rhs_shape;

        matmul_simd_enumerator_t(meta::as_type<N_ELEM_PACK>, const out_shape_t& out_shape, const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
            : n_elem_pack{}
            , out_shape(out_shape)
            , lhs_shape(lhs_shape)
            , rhs_shape(rhs_shape)
        {}

        constexpr auto size() const noexcept
        {
            return index::product(out_shape);
        }

        constexpr auto operator[](size_type i) const noexcept
        {
            auto out_offset = i;
            auto enumerator = matmul_simd_inner_enumerator(n_elem_pack,out_offset,out_shape,lhs_shape,rhs_shape);
            return nmtools_tuple{SIMD::ACCUMULATE,out_offset,enumerator};
        }

        // proxy object to track out_offset (i) from range for loop
        struct ref_t
        {
            using size_type = typename matmul_simd_enumerator_t::size_type;

            const matmul_simd_enumerator_t& enumerator;
            size_type i = 0;

            constexpr decltype(auto) operator*() const
            {
                return enumerator[i];
            } 
            
            constexpr bool operator==(const ref_t& rhs) const
            {
                return i == rhs.i;
            }

            constexpr bool operator!=(const ref_t& rhs) const
            {
                return !operator==(rhs);
            }

            constexpr auto operator++()
            {
                i++;
            }
        };
    }; // matmul_simd_enumerator_t

    template <typename index_t=size_t, auto N_ELEM_PACK, typename...args_t>
    constexpr auto begin(const matmul_simd_enumerator_t<index_t,N_ELEM_PACK,args_t...>& enumerator)
    {
        using enumerator_t = meta::remove_cvref_t<decltype(enumerator)>;
        using result_t = typename enumerator_t::ref_t;
        return result_t{enumerator,0};
    }

    template <typename index_t=size_t, auto N_ELEM_PACK, typename...args_t>
    constexpr auto end(const matmul_simd_enumerator_t<index_t,N_ELEM_PACK,args_t...>& enumerator)
    {
        using enumerator_t = meta::remove_cvref_t<decltype(enumerator)>;
        using result_t = typename enumerator_t::ref_t;
        return result_t{enumerator,(index_t)enumerator.size()};
    }

    template <typename index_t=size_t, auto N_ELEM_PACK, typename out_shape_t, typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto matmul_simd_enumerator(meta::as_type<N_ELEM_PACK> n_elem_pack, const out_shape_t& out_shape, const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
    {
        using enumerator_t = matmul_simd_enumerator_t<index_t,N_ELEM_PACK,out_shape_t,lhs_shape_t,rhs_shape_t>;
        return enumerator_t(
            n_elem_pack
            , out_shape
            , lhs_shape
            , rhs_shape
        );
    }
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_EVAL_SIMD_INDEX_MATMUL_HPP