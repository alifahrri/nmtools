#ifndef TESTS_TILEKIT_KERNEL_MATMUL_HPP
#define TESTS_TILEKIT_KERNEL_MATMUL_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using namespace nmtools::literals;

// matmul
struct matmul_kernel_t
{
    template <typename ctx_t, typename out_t, typename lhs_t, typename rhs_t, typename mkn_shape_t>
    auto operator()(ctx_t& ctx, out_t& out, const lhs_t& lhs, const rhs_t& rhs, const mkn_shape_t mkn_shape) const
    {
        using nmtools_tuple;
        nmtools_tracy_zone_scoped("matmul kernel");

        [[maybe_unused]] auto [w_id] = tk::worker_id(ctx);
        [[maybe_unused]] auto [w_size] = tk::worker_size(ctx);

        const auto [m_block,k_block,n_block] = mkn_shape;
        static_assert( nm::is_constant_index_array_v<mkn_shape_t> );

        auto lhs_tile = tuple{m_block,k_block};
        auto rhs_tile = tuple{k_block,n_block};
        auto acc_tile = tuple{m_block,k_block,n_block};
        auto out_tile = tuple{m_block,n_block};

        auto dtype = nm::type(out);

        auto a_shape = tk::shape(lhs);
        auto b_shape = tk::shape(rhs);
        auto c_shape = tk::shape(out);

        auto a_nditer = tk::nditer(a_shape,lhs_tile);
        auto b_nditer = tk::nditer(b_shape,rhs_tile);
        auto c_nditer = tk::nditer(c_shape,out_tile);

        auto M = nm::at(c_shape,-2_ct) / m_block;
        auto K = nm::at(a_shape,-1_ct) / k_block;
        auto N = nm::at(c_shape,-1_ct) / n_block;

        using unroll_ctx_t = nm::unroll_context_t<false,true>;

        for (nm_size_t m=0; m<M; m++) {
            for (nm_size_t n=0; n<N; n++) {
                auto accumulator = nm::Array::zeros(acc_tile,dtype,ctx);
                for (nm_size_t k=0; k<K; k++) {
                    auto lhs_ndoffset = tk::packed_at(a_nditer,m,k);
                    auto rhs_ndoffset = tk::packed_at(b_nditer,k,n);
                    
                    auto block_a = tk::load(ctx,lhs,lhs_ndoffset,lhs_tile);
                    auto block_b = tk::load(ctx,rhs,rhs_ndoffset,rhs_tile);
                    
                    static_assert( nm::is_fixed_shape_v<decltype(block_a)> );
                    static_assert( nm::is_fixed_shape_v<decltype(block_b)> );
                    {
                        auto mctx = nm::get_context(block_a);
                        static_assert( nm::is_same_v<decltype(mctx),unroll_ctx_t> );
                    }

                    auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
                    auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

                    static_assert( nm::is_fixed_shape_v<decltype(tmp1a)> );
                    static_assert( nm::is_fixed_shape_v<decltype(tmp1b)> );
                    {
                        auto mctx = nm::get_context(tmp1a);
                        static_assert( nm::is_same_v<decltype(mctx),unroll_ctx_t> );
                    }

                    auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
                    auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

                    static_assert( nm::is_fixed_shape_v<decltype(tmp2a)> );
                    static_assert( nm::is_fixed_shape_v<decltype(tmp2b)> );
                    {
                        auto mctx = nm::get_context(tmp2a);
                        static_assert( nm::is_same_v<decltype(mctx),unroll_ctx_t> );
                    }

                    auto result = tmp2a * tmp2b;
                    static_assert( nm::is_fixed_shape_v<decltype(result)> );

                    accumulator = accumulator + result;
                }
                auto mctx = nm::get_context(accumulator);
                static_assert( nm::is_same_v<decltype(mctx),unroll_ctx_t> );

                auto out_offset = tk::packed_at(c_nditer,m,n);
                auto result = accumulator.sum(-2_ct);
                tk::store(ctx,out,out_offset,result);
            }
        }
    }
};

constexpr inline auto matmul_kernel = matmul_kernel_t {};

#endif // TESTS_TILEKIT_KERNEL_MATMUL_HPP