#include "nmtools/tilekit/scalar.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/maximum.hpp"

#include <nanobench.h>

namespace nm = nmtools;
using namespace nmtools::literals;

template <typename shape_m_t, typename shape_n_t>
constexpr auto make_shape(shape_m_t shape_m, shape_n_t shape_n)
{
    if constexpr (nm::is_constant_index_v<shape_m_t>
        || nm::is_constant_index_v<shape_n_t>
    ) {
        return nmtools_tuple{shape_m,shape_n};
    } else {
        return nmtools_array{shape_m,shape_n};
    }
}

#define SCALAR_ST_MAXIMUM_CASE(case_name, shape, tile_shape) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto a = nm::random(shape,dtype,gen); \
    auto b = nm::random(shape,dtype,gen); \
    auto c = nm::Array::zeros(shape,dtype); \
\
    auto ctx = tk::Scalar; \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            maximum_kernel(ctx,c,a,b,tile_shape); \
        }); \
\
    auto expected = nm::maximum(a,b); \
    NMTOOLS_ASSERT_CLOSE( c, expected ); \
}

SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.1024_1024.fp32.2x4, (make_shape(1024,1024)), (tuple{2_ct,4_ct}))