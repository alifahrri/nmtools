#include "nmtools/evaluator/hip.hpp"
#include "nmtools/array/vector_norm.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nmtools::view;

// TODO: fix to accept maybe type
using nmtools_array, nmtools_tuple, nmtools::unwrap;

#define HIP_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,na::hip::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define HIP_LINEAR_TEST(fun,...) \
{ \
    auto ctx = na::hip::default_context(); \
    auto expect = na::fun(__VA_ARGS__); \
    auto view   = view::fun(__VA_ARGS__); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

// crashed:
// Cannot find Symbol with name:
// _Z19nm_hip_run_functionITnDaLi0EN7nmtools10functional21functor_composition_tINS0_3utl7tuplev2IJNS1_9functor_tINS1_6fmap_tINS1_3fun22broadcast_binary_ufuncINS0_6none_tEEELm2ELm1EEENS0_4meta16empty_operands_tENS4_IJNS0_4args5ufuncINS0_4view7power_tIS9_S9_S9_vEEEEEEEEENS5_INS6_INS7_6reduceIS9_EELm1ELm1EEESD_NS4_IJNSE_6reduceINS3_5arrayIiLm2EEES9_S9_NSC_9true_typeENSG_3fun3addIS9_S9_S9_vEEEEEEEEESL_NS5_INS6_INS7_11unary_ufuncIS9_EELm1ELm1EEESD_NS4_IJNSF_INST_4fabsEEEEEEEEEEESD_EEdmmNS3_5tupleEJNS0_5array12device_arrayIfNS3_13static_vectorImLm8EEEmEEifEEvT0_PT1_PKT2_T3_T4_IJDpT5_EE
#if 0
TEST_CASE("vector_norm(case1)" * doctest::test_suite("array::vector_norm"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto x = na::random(array{2,3,2},dtype,gen);
    auto axis = array{-2,-1};
    auto keepdims = nm::True;
    auto ord = 1;

    HIP_TEST(vector_norm,x,axis,keepdims,ord);
}
#endif

// crashed:
// Cannot find Symbol with name:
// _Z19nm_hip_run_functionITnDaLi0EN7nmtools10functional21functor_composition_tINS0_3utl7tuplev2IJNS1_9functor_tINS1_6fmap_tINS1_3fun22broadcast_binary_ufuncINS0_6none_tEEELm2ELm1EEENS0_4meta16empty_operands_tENS4_IJNS0_4args5ufuncINS0_4view7power_tIS9_S9_S9_vEEEEEEEEENS5_INS6_INS7_6reduceIS9_EELm1ELm1EEESD_NS4_IJNSE_6reduceINS3_5arrayIiLm2EEES9_S9_NSC_9true_typeENSG_3fun3addIS9_S9_S9_vEEEEEEEEESL_NS5_INS6_INS7_11unary_ufuncIS9_EELm1ELm1EEESD_NS4_IJNSF_INST_4fabsEEEEEEEEEEESD_EEdmmNS3_5tupleEJNS0_5array12device_arrayIfNS3_13static_vectorImLm8EEEmEEifEEvT0_PT1_PKT2_T3_T4_IJDpT5_EE
#if 0
TEST_CASE("vector_norm(case1b)" * doctest::test_suite("array::vector_norm"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto x = na::random(array{2,3,2},dtype,gen);
    auto axis = array{-2,-1};
    auto keepdims = nm::True;
    auto ord = 1;

    HIP_LINEAR_TEST(vector_norm,x,axis,keepdims,ord);
}
#endif