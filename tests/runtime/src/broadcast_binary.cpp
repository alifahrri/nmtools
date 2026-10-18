#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/context/default.hpp"
// compile-time ufuncs for the reference expressions (some are not pulled in
// transitively; without them nmtools::OP(view,view) would silently prefer the
// runtime ndarray overload)
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/fmax.hpp"
#include "nmtools/array/ufuncs/fmin.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/ufuncs/minimum.hpp"
#include "nmtools/array/ufuncs/power.hpp"
#include "nmtools/array/ufuncs/hypot.hpp"
#include "nmtools/array/ufuncs/ldexp.hpp"
#include "nmtools/array/ufuncs/fmod.hpp"
#include "nmtools/array/ufuncs/mod.hpp"
#include "nmtools/array/ufuncs/left_shift.hpp"
#include "nmtools/array/ufuncs/right_shift.hpp"
#include "nmtools/array/ufuncs/bitwise_and.hpp"
#include "nmtools/array/ufuncs/bitwise_or.hpp"
#include "nmtools/array/ufuncs/bitwise_xor.hpp"
#include "nmtools/array/ufuncs/less.hpp"
#include "nmtools/array/ufuncs/less_equal.hpp"
#include "nmtools/array/ufuncs/greater.hpp"
#include "nmtools/array/ufuncs/greater_equal.hpp"
#include "nmtools/array/ufuncs/equal.hpp"
#include "nmtools/runtime/cpu/subtract.hpp"
#include "nmtools/runtime/cpu/multiply.hpp"
#include "nmtools/runtime/cpu/divide.hpp"
#include "nmtools/runtime/cpu/fmax.hpp"
#include "nmtools/runtime/cpu/fmin.hpp"
#include "nmtools/runtime/cpu/maximum.hpp"
#include "nmtools/runtime/cpu/minimum.hpp"
#include "nmtools/runtime/cpu/power.hpp"
#include "nmtools/runtime/cpu/hypot.hpp"
#include "nmtools/runtime/cpu/ldexp.hpp"
#include "nmtools/runtime/cpu/fmod.hpp"
#include "nmtools/runtime/cpu/mod.hpp"
#include "nmtools/runtime/cpu/left_shift.hpp"
#include "nmtools/runtime/cpu/right_shift.hpp"
#include "nmtools/runtime/cpu/bitwise_and.hpp"
#include "nmtools/runtime/cpu/bitwise_or.hpp"
#include "nmtools/runtime/cpu/bitwise_xor.hpp"
#include "nmtools/runtime/cpu/less.hpp"
#include "nmtools/runtime/cpu/less_equal.hpp"
#include "nmtools/runtime/cpu/greater.hpp"
#include "nmtools/runtime/cpu/greater_equal.hpp"
#include "nmtools/runtime/cpu/equal.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace nrt = nmtools::runtime;

// every binary cpu functor, broadcast over two patterns:
// {3,4} + {4} (trailing dim) and {3,1} + {1,4} (both sides expand)
#define CHECK_BCAST(CPUFN, OP, LDT_V, RDT_V, LDT_C, RDT_C, OUT_V, GEN_L, GEN_R) { \
    auto fn = nrt::CPUFN(LDT_C,RDT_C); \
    { \
        nrt::ndarray lhs = nm::random(nrt::IndexType{3,4},LDT_V,GEN_L); \
        nrt::ndarray rhs = nm::random(nrt::IndexType{4},RDT_V,GEN_R); \
        auto evaluated = fn({lhs,rhs}); \
        CHECK( evaluated.is_evaluated() ); \
        NMTOOLS_ASSERT_EQUAL( evaluated.shape(), (nrt::IndexType{3,4}) ); \
        NMTOOLS_ASSERT_CLOSE( evaluated.view(OUT_V), (nmtools::OP(lhs.view(LDT_V),rhs.view(RDT_V))) ); \
    } \
    { \
        nrt::ndarray lhs = nm::random(nrt::IndexType{3,1},LDT_V,GEN_L); \
        nrt::ndarray rhs = nm::random(nrt::IndexType{1,4},RDT_V,GEN_R); \
        auto evaluated = fn({lhs,rhs}); \
        CHECK( evaluated.is_evaluated() ); \
        NMTOOLS_ASSERT_EQUAL( evaluated.shape(), (nrt::IndexType{3,4}) ); \
        NMTOOLS_ASSERT_CLOSE( evaluated.view(OUT_V), (nmtools::OP(lhs.view(LDT_V),rhs.view(RDT_V))) ); \
    } \
}

TEST_CASE("cpu binary broadcast" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    // safe ranges for integer div/mod (mod by zero is SIGFPE) and shifts
    auto gen_i  = nm::random_engine<nm::int32_t>(0,10);
    auto gen_nz = nm::random_engine<nm::int32_t>(1,5);
    auto gen_s  = nm::random_engine<nm::int32_t>(0,5);
    auto f32v = nm::float32;
    auto i32v = nm::int32;
    auto u8v  = nm::uint8;
    auto F32 = nrt::DType::Float32;
    auto I32 = nrt::DType::Int32;

    CHECK_BCAST(cpu_subtract, subtract, f32v, f32v, F32, F32, f32v, gen, gen)
    CHECK_BCAST(cpu_multiply, multiply, f32v, f32v, F32, F32, f32v, gen, gen)
    CHECK_BCAST(cpu_divide, divide, f32v, f32v, F32, F32, f32v, gen, gen)
    CHECK_BCAST(cpu_fmax, fmax, f32v, f32v, F32, F32, f32v, gen, gen)
    CHECK_BCAST(cpu_fmin, fmin, f32v, f32v, F32, F32, f32v, gen, gen)
    CHECK_BCAST(cpu_maximum, maximum, f32v, f32v, F32, F32, f32v, gen, gen)
    CHECK_BCAST(cpu_minimum, minimum, f32v, f32v, F32, F32, f32v, gen, gen)
    CHECK_BCAST(cpu_power, power, f32v, f32v, F32, F32, f32v, gen, gen)
    CHECK_BCAST(cpu_hypot, hypot, f32v, f32v, F32, F32, f32v, gen, gen)
    CHECK_BCAST(cpu_fmod, fmod, f32v, f32v, F32, F32, f32v, gen, gen)
    CHECK_BCAST(cpu_ldexp, ldexp, f32v, i32v, F32, I32, f32v, gen, gen)
    CHECK_BCAST(cpu_mod, mod, i32v, i32v, I32, I32, i32v, gen_i, gen_nz)
    CHECK_BCAST(cpu_left_shift, left_shift, i32v, i32v, I32, I32, i32v, gen_s, gen_s)
    CHECK_BCAST(cpu_right_shift, right_shift, i32v, i32v, I32, I32, i32v, gen_s, gen_s)
    CHECK_BCAST(cpu_bitwise_and, bitwise_and, i32v, i32v, I32, I32, i32v, gen, gen)
    CHECK_BCAST(cpu_bitwise_or, bitwise_or, i32v, i32v, I32, I32, i32v, gen, gen)
    CHECK_BCAST(cpu_bitwise_xor, bitwise_xor, i32v, i32v, I32, I32, i32v, gen, gen)
    CHECK_BCAST(cpu_less, less, f32v, f32v, F32, F32, u8v, gen, gen)
    CHECK_BCAST(cpu_less_equal, less_equal, f32v, f32v, F32, F32, u8v, gen, gen)
    CHECK_BCAST(cpu_greater, greater, f32v, f32v, F32, F32, u8v, gen, gen)
    CHECK_BCAST(cpu_greater_equal, greater_equal, f32v, f32v, F32, F32, u8v, gen, gen)
    CHECK_BCAST(cpu_equal, equal, f32v, f32v, F32, F32, u8v, gen, gen)

    // col-major operand with broadcast: transpose of {4,3} -> col-major {3,4}
    {
        nrt::ndarray src = nm::random(nrt::IndexType{4,3},f32v,gen);
        nrt::ndarray vec = nm::random(nrt::IndexType{4},f32v,gen);
        auto src_t = src.transpose();
        CHECK( src_t.is_col_major() );
        auto fn = nrt::cpu_subtract(F32,F32);
        auto evaluated = fn({src_t,vec});
        CHECK( evaluated.is_evaluated() );
        NMTOOLS_ASSERT_EQUAL( evaluated.shape(), (nrt::IndexType{3,4}) );
        NMTOOLS_ASSERT_CLOSE( evaluated.view(f32v), (nmtools::subtract(src_t.view(f32v),vec.view(f32v))) );
    }
}

#undef CHECK_BCAST
