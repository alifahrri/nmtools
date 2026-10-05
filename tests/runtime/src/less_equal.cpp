#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/array/ufuncs/less_equal.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/runtime/cpu/less_equal.hpp"
#include "nmtools/runtime/cpu.hpp"
#include "nmtools/core/transform/gvn.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace nrt = nmtools::runtime;
namespace utils = nm::utils;

TEST_CASE("less_equal(i32,i32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine<nm::int32_t>(0,15);
    auto dtype = nm::int32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    /*********************************************************************** */

    auto result = nm::less_equal(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::UInt8 );
    CHECK( !result.is_evaluated() );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    {
        auto fn = nrt::cpu_less_equal(nrt::DType::Int32,nrt::DType::Int32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        CHECK( result.dtype() == nrt::DType::UInt8 );
        NMTOOLS_ASSERT_CLOSE( result.view(nm::uint8), (nmtools::less_equal(lhs.view(dtype),rhs.view(dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        CHECK( result.dtype() == nrt::DType::UInt8 );
        NMTOOLS_ASSERT_CLOSE( result.view(nm::uint8), (nmtools::less_equal(lhs.view(dtype),rhs.view(dtype))) );
    }
}

TEST_CASE("less_equal(u8,u8)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine<nm::uint8_t>(0,15);
    auto dtype = nm::uint8;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    /*********************************************************************** */

    auto result = nm::less_equal(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::UInt8 );
    CHECK( !result.is_evaluated() );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    {
        auto fn = nrt::cpu_less_equal(nrt::DType::UInt8,nrt::DType::UInt8);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        CHECK( result.dtype() == nrt::DType::UInt8 );
        NMTOOLS_ASSERT_CLOSE( result.view(nm::uint8), (nmtools::less_equal(lhs.view(dtype),rhs.view(dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        CHECK( result.dtype() == nrt::DType::UInt8 );
        NMTOOLS_ASSERT_CLOSE( result.view(nm::uint8), (nmtools::less_equal(lhs.view(dtype),rhs.view(dtype))) );
    }
}

TEST_CASE("less_equal(f32,f32)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    /*********************************************************************** */

    auto result = nm::less_equal(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::UInt8 );
    CHECK( !result.is_evaluated() );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    {
        auto fn = nrt::cpu_less_equal(nrt::DType::Float32,nrt::DType::Float32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        CHECK( result.dtype() == nrt::DType::UInt8 );
        NMTOOLS_ASSERT_CLOSE( result.view(nm::uint8), (nmtools::less_equal(lhs.view(dtype),rhs.view(dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        CHECK( result.dtype() == nrt::DType::UInt8 );
        NMTOOLS_ASSERT_CLOSE( result.view(nm::uint8), (nmtools::less_equal(lhs.view(dtype),rhs.view(dtype))) );
    }
}