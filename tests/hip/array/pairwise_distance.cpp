#include "nmtools/evaluator/hip.hpp"
#include "nmtools/array/pairwise_distance.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
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
// _Z19nm_hip_run_functionITnDaLi0EN7nmtools10functional21functor_composition_tINS0_3utl7tuplev2IJNS1_9functor_tINS1_6fmap_tINS1_3fun22broadcast_binary_ufuncINS0_6none_tEEELm2ELm1EEENS0_4meta16empty_operands_tENS4_IJNS0_4args5ufuncINS0_4view7power_tIS9_S9_S9_vEEEEEEEEENS5_INS6_INS7_6reduceIS9_EELm1ELm1EEESD_NS4_IJNSE_6reduceINSC_17integral_constantIiLin1EEES9_S9_NSC_10false_typeENSG_3fun3addIS9_S9_S9_vEEEEEEEEESL_NS5_INS6_INS7_11unary_ufuncIS9_EELm1ELm1EEESD_NS4_IJNSF_INST_4fabsEEEEEEEENS5_ISB_SD_NS4_IJNSF_ISV_EEEEEEENS5_ISB_SD_NS4_IJNSF_INST_8subtractIS9_S9_S9_vEEEEEEEEEEEESD_EEdmmNS3_5tupleEJNS0_5array12device_arrayIfNS3_13static_vectorImLm8EEEmEES1L_fNSQ_IiLi2EEEfEEvT0_PT1_PKT2_T3_T4_IJDpT5_EE
#if 0
TEST_CASE("pairwise_distance(case1)" * doctest::test_suite("array::pairwise_distance"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto lhs = na::random(array{3,4},dtype,gen);
    auto rhs = na::random(array{2,1,4},dtype,gen);

    HIP_TEST(pairwise_distance,lhs,rhs,meta::ct_v<2>,1e-6f,nm::False);
}
#endif

// crashed:
// Cannot find Symbol with name:
// _Z19nm_hip_run_functionITnDaLi0EN7nmtools10functional21functor_composition_tINS0_3utl7tuplev2IJNS1_9functor_tINS1_6fmap_tINS1_3fun22broadcast_binary_ufuncINS0_6none_tEEELm2ELm1EEENS0_4meta16empty_operands_tENS4_IJNS0_4args5ufuncINS0_4view7power_tIS9_S9_S9_vEEEEEEEEENS5_INS6_INS7_6reduceIS9_EELm1ELm1EEESD_NS4_IJNSE_6reduceINSC_17integral_constantIiLin1EEES9_S9_NSC_10false_typeENSG_3fun3addIS9_S9_S9_vEEEEEEEEESL_NS5_INS6_INS7_11unary_ufuncIS9_EELm1ELm1EEESD_NS4_IJNSF_INST_4fabsEEEEEEEENS5_ISB_SD_NS4_IJNSF_ISV_EEEEEEENS5_ISB_SD_NS4_IJNSF_INST_8subtractIS9_S9_S9_vEEEEEEEEEEEESD_EEdmmNS3_5tupleEJNS0_5array12device_arrayIfNS3_13static_vectorImLm8EEEmEES1L_fNSQ_IiLi2EEEfEEvT0_PT1_PKT2_T3_T4_IJDpT5_EE
#if 0
TEST_CASE("pairwise_distance(case1b)" * doctest::test_suite("array::pairwise_distance"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto lhs = na::random(array{3,4},dtype,gen);
    auto rhs = na::random(array{2,1,4},dtype,gen);

    HIP_LINEAR_TEST(pairwise_distance,lhs,rhs,meta::ct_v<2>,1e-6f,nm::False);
}
#endif