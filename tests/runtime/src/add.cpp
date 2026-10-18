#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/runtime/cpu/add.hpp"
#include "nmtools/runtime/cpu.hpp"
#include "nmtools/core/transform/gvn.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace nrt = nmtools::runtime;
namespace utils = nm::utils;

// f32,f32
TEST_CASE("add(case1)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    /*********************************************************************** */

    auto result = nm::add(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Float32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    {
        auto fn = nrt::cpu_add(nrt::DType::Float32,nrt::DType::Float32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(dtype),rhs.view(dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(dtype),rhs.view(dtype))) );
    }
}

// f32,i32
TEST_CASE("add(case2)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto lhs_dtype = nm::float32;
    auto rhs_dtype = nm::int32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,lhs_dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,rhs_dtype,gen);

    /*********************************************************************** */

    auto result = nm::add(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Float32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    auto dtype = nm::float32;
    {
        auto fn = nrt::cpu_add(nrt::DType::Float32,nrt::DType::Int32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto res_hashed = fn::gvn(result.graph(),false,false);
        CHECK( res_hashed.size() != 0 );
        for (const auto& [k,v] : res_hashed) {
            auto key = k;
            auto value = v;
            CHECK_MESSAGE( true, key );
            CHECK_MESSAGE( true, value );
        }
        for (const auto& fn : ctx.functors()) {
            auto fn_hashes = fn::gvn(fn->graph(),false,false);
            CHECK( fn_hashes.size() != 0 );
            for (const auto& [k,v] : fn_hashes) {
                auto key = k;
                auto value = v;
                CHECK_MESSAGE( true, key );
                CHECK_MESSAGE( true, value );
            }
        }
        for (const auto h : ctx.hashes()) {
            CHECK_MESSAGE( true, h );
        }
        auto fn = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
    }
}

// f32,f32
// operator+
TEST_CASE("add(case3)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    /*********************************************************************** */

    auto result = lhs + rhs;

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Float32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    {
        auto fn = nrt::cpu_add(nrt::DType::Float32,nrt::DType::Float32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(dtype),rhs.view(dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(dtype),rhs.view(dtype))) );
    }
}

// i32,i32
TEST_CASE("add(case4)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto lhs_dtype = nm::int32;
    auto rhs_dtype = nm::int32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,lhs_dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,rhs_dtype,gen);

    /*********************************************************************** */

    auto result = nm::add(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Int32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    auto dtype = nm::int32;
    {
        auto fn = nrt::cpu_add(nrt::DType::Int32,nrt::DType::Int32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
    }
}

// i32,i32
// operator+
TEST_CASE("add(case5)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto lhs_dtype = nm::int32;
    auto rhs_dtype = nm::int32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,lhs_dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,rhs_dtype,gen);

    /*********************************************************************** */

    auto result = lhs + rhs;

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );

    CHECK( result.dtype() == nrt::DType::Int32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    auto dtype = nm::int32;
    {
        auto fn = nrt::cpu_add(nrt::DType::Int32,nrt::DType::Int32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(lhs_dtype),rhs.view(rhs_dtype))) );
    }
}

TEST_CASE("add(case7)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = nrt::IndexType{3,4};
    auto rhs_shape = nrt::IndexType{4};

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    /*********************************************************************** */

    auto result = nm::add(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );
    CHECK( !lhs.is_scalar() );
    CHECK( !rhs.is_scalar() );

    CHECK( result.dtype() == nrt::DType::Float32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    {
        auto fn = nrt::cpu_add(nrt::DType::Float32,nrt::DType::Float32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(dtype),rhs.view(dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(dtype),rhs.view(dtype))) );
    }
}

TEST_CASE("add(case8)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = nrt::IndexType{4};
    auto rhs_shape = nrt::IndexType{3,4};

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    /*********************************************************************** */

    auto result = nm::add(lhs,rhs);

    CHECK( lhs.is_evaluated() );
    CHECK( rhs.is_evaluated() );
    CHECK( !lhs.is_scalar() );
    CHECK( !rhs.is_scalar() );

    CHECK( result.dtype() == nrt::DType::Float32 );
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );

    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    {
        auto fn = nrt::cpu_add(nrt::DType::Float32,nrt::DType::Float32);
        auto result = fn({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(dtype),rhs.view(dtype))) );
        CHECK_MESSAGE( true, utils::to_string(fn.graph(),utils::Graphviz) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto result = (*fn)({lhs,rhs});
        CHECK( result.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( result.view(dtype), (nmtools::add(lhs.view(dtype),rhs.view(dtype))) );
    }
}

// f32,f32 col-major (transposed) operands: same shape and broadcast
TEST_CASE("add(case6)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    // transposing {4,3} row-major arrays yields col-major strides of {3,4}
    nrt::ndarray lhs = nm::random(nrt::IndexType{4,3},dtype,gen);
    nrt::ndarray rhs = nm::random(nrt::IndexType{4,3},dtype,gen);
    auto lhs_t = lhs.transpose();
    auto rhs_t = rhs.transpose();
    CHECK( lhs_t.is_col_major() );
    CHECK_FALSE( lhs_t.is_row_major() );
    CHECK( rhs_t.is_col_major() );

    auto result = nm::add(lhs_t,rhs_t);
    CHECK( !result.is_evaluated() );
    NMTOOLS_ASSERT_EQUAL( result.shape(), (nrt::IndexType{3,4}) );
    CHECK_MESSAGE( true, utils::to_string(result.graph(),utils::Graphviz) );

    /*********************************************************************** */
    {
        auto fn = nrt::cpu_add(nrt::DType::Float32,nrt::DType::Float32);
        auto evaluated = fn({lhs_t,rhs_t});
        CHECK( evaluated.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( evaluated.view(dtype), (nmtools::add(lhs_t.view(dtype),rhs_t.view(dtype))) );
    }
    {
        auto ctx = nrt::cpu();
        auto fn  = ctx.get_functor(result.graph());
        auto evaluated = (*fn)({lhs_t,rhs_t});
        CHECK( evaluated.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( evaluated.view(dtype), (nmtools::add(lhs_t.view(dtype),rhs_t.view(dtype))) );
    }

    // col-major operand broadcast with a row vector: {3,4} + {4}
    nrt::ndarray vec = nm::random(nrt::IndexType{4},dtype,gen);
    auto bresult = nm::add(lhs_t,vec);
    NMTOOLS_ASSERT_EQUAL( bresult.shape(), (nrt::IndexType{3,4}) );
    {
        auto fn = nrt::cpu_add(nrt::DType::Float32,nrt::DType::Float32);
        auto evaluated = fn({lhs_t,vec});
        CHECK( evaluated.is_evaluated() );
        NMTOOLS_ASSERT_CLOSE( evaluated.view(dtype), (nmtools::add(lhs_t.view(dtype),vec.view(dtype))) );
    }
}

// f32,f32 incompatible shapes must throw instead of reading out of bounds
TEST_CASE("add(case9)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    nrt::ndarray lhs = nm::random(nrt::IndexType{3,4},dtype,gen);
    nrt::ndarray rhs = nm::random(nrt::IndexType{2,3},dtype,gen); // 4 vs 3: not broadcastable

    // graph construction unwraps a failed broadcast_shape and throws
    CHECK_THROWS_AS( nm::add(lhs,rhs), std::runtime_error );

    // cpu execution rejects as well
    auto fn = nrt::cpu_add(nrt::DType::Float32,nrt::DType::Float32);
    CHECK_THROWS_AS( fn({lhs,rhs}), std::runtime_error );
}
