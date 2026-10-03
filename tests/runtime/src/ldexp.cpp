#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/array/ufuncs/ldexp.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/runtime/cpu/ldexp.hpp"
#include "nmtools/runtime/cpu.hpp"
#include "nmtools/core/transform/gvn.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace nrt = nmtools::runtime;
namespace utils = nm::utils;

TEST_CASE("ldexp(f32,i32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine<nm::int32_t>(0,5);
    auto dtype = nm::float32;
    auto rhs_dtype = nm::int32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,rhs_dtype,gen);

    /*********************************************************************** */

    auto result = nm::ldexp(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Float32 );
    CHECK( !result.is_evaluated() );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    {
        auto fn = nrt::cpu_ldexp(nrt::DType::Float32,nrt::DType::Int32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::ldexp(lhs.view(dtype),rhs.view(rhs_dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::ldexp(lhs.view(dtype),rhs.view(rhs_dtype))) );
    }
}
