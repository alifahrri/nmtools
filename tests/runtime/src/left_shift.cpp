#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/array/ufuncs/left_shift.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/runtime/cpu/left_shift.hpp"
#include "nmtools/runtime/cpu.hpp"
#include "nmtools/core/transform/gvn.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace nrt = nmtools::runtime;
namespace utils = nm::utils;

TEST_CASE("left_shift(i32,i32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine<nm::int32_t>(0,5);
    auto dtype = nm::int32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    /*********************************************************************** */

    auto result = nm::left_shift(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Int32 );
    CHECK( !result.is_evaluated() );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    {
        auto fn = nrt::cpu_left_shift(nrt::DType::Int32,nrt::DType::Int32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::left_shift(lhs.view(dtype),rhs.view(dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::left_shift(lhs.view(dtype),rhs.view(dtype))) );
    }
}
