#include "nmtools/tilekit/vector.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/array/matmul.hpp"

#include "kernels/matmul.hpp"

#include <nanobench.h>

// due to different ordering of summation, the result may be different
// especially on big array
#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-1)

namespace nm = nmtools;
using namespace nmtools::literals;
using nmtools_tuple;

using context_t = tk::vector::context_t<128>;

template <typename shape_0_t, typename...shape_n_t>
constexpr auto make_shape(shape_0_t shape_0, shape_n_t...shape_n)
{
    if constexpr (nm::is_constant_index_v<shape_0_t>
        || (nm::is_constant_index_v<shape_n_t> || ...)
    ) {
        return nmtools_tuple{shape_0,shape_n...};
    } else {
        return nmtools_array{shape_0,shape_n...};
    }
}

#define V128_MATMUL_CASE( case_name, M, K, N, mkn_tile ) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen = nm::random_engine(); \
    auto dtype = nm::float32; \
    auto shape = [&](){ \
        if constexpr (nm::is_constant_index_v<decltype(M)> || nm::is_constant_index_v<decltype(K)>) { \
            return nmtools_tuple{M,K}; \
        } else { \
            return nmtools_array{M,K}; \
        } \
    }(); \
    auto rhs_shape = [&](){ \
        if constexpr (nm::is_constant_index_v<decltype(K)> || nm::is_constant_index_v<decltype(N)>) { \
            return nmtools_tuple{K,N}; \
        } else { \
            return nmtools_array{K,N}; \
        } \
    }(); \
    auto out_shape = [&](){ \
        if constexpr (nm::is_constant_index_v<decltype(M)> || nm::is_constant_index_v<decltype(N)>) { \
            return nmtools_tuple{M,N}; \
        } else { \
            return nmtools_array{M,N}; \
        } \
    }(); \
\
    auto lhs = nm::random(shape,dtype,gen); \
    auto rhs = nm::random(rhs_shape,dtype,gen); \
    auto out = nm::Array::zeros(out_shape,dtype); \
\
    auto ctx = context_t(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            matmul_kernel(ctx,out,lhs,rhs,mkn_tile); \
        }); \
\
    auto expected = nm::matmul(lhs,rhs); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

V128_MATMUL_CASE( v128_st.matmul.4_16_4.fp32.4x2x4, 4, 16, 4, (tuple{4_ct,4_ct,4_ct}) );