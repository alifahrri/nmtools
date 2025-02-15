#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/array/dot.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nmtools::view;

// TODO: fix to accept maybe type
using nmtools_array, nmtools_tuple, nmtools::unwrap;

#define SYCL_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,na::sycl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define SYCL_LINEAR_TEST(fun,...) \
{ \
    auto ctx = na::sycl::default_context(); \
    auto expect = na::fun(__VA_ARGS__); \
    auto view   = view::fun(__VA_ARGS__); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#if 0
TEST_CASE("dot(case1)" * doctest::test_suite("array::dot") * doctest::skip())
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto a = na::random(array{2,3,2},dtype,gen);
    auto b = na::random(array{2,4,2,2},dtype,gen);

    SYCL_TEST(dot,a,b);
}
#endif

#if 1
// got weird error on ci:
// dlsym("/root/.cache/pocl/kcache/GB/BHCEBJDLMGHCLBGJMGNBIJEGMAOOJAFJIGODP/_Z18__acpp_sscp_kernelI.CLDLOLNJMBIEDNEFAOCFCGEJOMBLDIOLKOOGDCLI/32-1-1-goffs0-smallgrid/_Z18__acpp_sscp_ke.CLDLOLNJMBIEDNEFAOCFCGEJOMBLDIOLKOOGDCLI.so", "pocl_kernel__Z18__acpp_sscp_kernelIN7hipsycl4glue15__sscp_dispatch20ndrange_parallel_forIZZN7nmtools5array4sycl9context_t4run_INS5_9ndarray_tINS4_3utl6vectorIfNSA_9allocatorIfEEEENSB_ImNSC_ImEEEENS5_21resolve_stride_type_tENS5_18row_major_offset_tEvEENS4_10functional21functor_composition_tINSA_7tuplev2IJNSK_9functor_tINSK_6fmap_tINSK_3fun6reduceINS4_6none_tEEELm1ELm1EEENS4_4meta16empty_operands_tENSM_IJNS4_4args6reduceINSU_17integral_constantIiLin1EEESR_SR_NSU_10false_typeENS4_4view3fun3addISR_SR_SR_vEEEEEEEEENSN_INSO_INSP_22broadcast_binary_ufuncISR_EELm2ELm1EEESV_NSM_IJNSW_5ufuncINS12_8multiplyISR_SR_SR_vEEEEEEEEENSN_INSO_INS4_10combinator5dig_tILi1EEELm2ELm2EEESV_NSU_18empty_attributes_tEEENSN_INSO_INSP_8indexingELm1ELm1EEESV_NSM_IJNSW_8indexingINS11_11transpose_tINSA_5arrayImLm4EEES1S_mEEEEEEEEENSN_INSO_INS1H_6bury_tILi1EEELm2ELm2EEESV_S1L_EENSN_IS1O_SV_NSM_IJNS1P_INSA_5maybeINS11_9reshape_tINS1R_ImLm3EEENS1R_ImLm6EEEmEEvEEEEEEEEENSN_IS1O_SV_NSM_IJNS1P_INS11_6tile_tIS23_S23_EEEEEEEEEEEESV_EEJSt10shared_p") failed with '/root/.cache/pocl/kcache/GB/BHCEBJDLMGHCLBGJMGNBIJEGMAOOJAFJIGODP/_Z18__acpp_sscp_kernelI.CLDLOLNJMBIEDNEFAOCFCGEJOMBLDIOLKOOGDCLI/32-1-1-goffs0-smallgrid/_Z18__acpp_sscp_ke.CLDLOLNJMBIEDNEFAOCFCGEJOMBLDIOLKOOGDCLI.so: undefined symbol: pocl_kernel__Z18__acpp_sscp_kernelIN7hipsycl4glue15__sscp_dispatch20ndrange_parallel_forIZZN7nmtools5array4sycl9context_t4run_INS5_9ndarray_tINS4_3utl6vectorIfNSA_9allocatorIfEEEENSB_ImNSC_ImEEEENS5_21resolve_stride_type_tENS5_18row_major_offset_tEvEENS4_10functional21functor_composition_tINSA_7tuplev2IJNSK_9functor_tINSK_6fmap_tINSK_3fun6reduceINS4_6none_tEEELm1ELm1EEENS4_4meta16empty_operands_tENSM_IJNS4_4args6reduceINSU_17integral_constantIiLin1EEESR_SR_NSU_10false_typeENS4_4view3fun3addISR_SR_SR_vEEEEEEEEENSN_INSO_INSP_22broadcast_binary_ufuncISR_EELm2ELm1EEESV_NSM_IJNSW_5ufuncINS12_8multiplyISR_SR_SR_vEEEEEEEEENSN_INSO_INS4_10combinator5dig_tILi1EEELm2ELm2EEESV_NSU_18empty_attributes_tEEENSN_INSO_INSP_8indexingELm1ELm1EEESV_NSM_IJNSW_8indexingINS11_11transpose_tINSA_5arrayImLm4EEES1S_mEEEEEEEEENSN_INSO_INS1H_6bury_tILi1EEELm2ELm2EEESV_S1L_EENSN_IS1O_SV_NSM_IJNS1P_INSA_5maybeINS11_9reshape_tINS1R_ImLm3EEENS1R_ImLm6EEEmEEvEEEEEEEEENSN_IS1O_SV_NSM_IJNS1P_INS11_6tile_tIS23_S23_EEEEEEEEEEEESV_EEJSt10shared_p'.
TEST_CASE("dot(case1b)" * doctest::test_suite("array::dot") * doctest::skip())
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto a = na::random(array{2,3,2},dtype,gen);
    auto b = na::random(array{2,4,2,2},dtype,gen);

    SYCL_LINEAR_TEST(dot,a,b);
}
#endif

/**
[doctest] run with "--help" for options
[nmtools sycl] number of sycl devices: 2
[nmtools sycl] platform #0:
- name: OpenCL (platform 0)
- vendor: The AdaptiveCpp project
- version: AdaptiveCpp 24.10.0+git.7677cf6e.20241220.branch.HEAD
- profile: FULL_PROFILE
- extensions: 
[nmtools sycl] platform #1:
- name: OpenMP (platform 0)
- vendor: The AdaptiveCpp project
- version: AdaptiveCpp 24.10.0+git.7677cf6e.20241220.branch.HEAD
- profile: FULL_PROFILE
- extensions: 
[nmtools sycl] default context using platform #0
- name: cpu-znver3-AMD EPYC 7763 64-Core Processor
- vendor: cpu-znver3-AMD EPYC 7763 64-Core Processor
- driver_version: 6.0
- profile: FULL_PROFILE
- version: OpenCL OpenCL C 1.2 PoCL
- opencl_c_version: 1.2 HIPSYCL
- extensions: 
- device_type: CPU
- vendor_id: 65542
- max_compute_units: 4
- max_work_item_dimensions: 3
- max_work_item_sizes<1>: 4096
- max_work_item_sizes<2>: 4096, 4096
- max_work_item_sizes<3>: 4096, 4096, 4096
- max_work_group_size: 4096
- preferred_vector_width_char: 16
- preferred_vector_width_short: 16
- preferred_vector_width_int: 8
- preferred_vector_width_long: 4
- preferred_vector_width_float: 8
- preferred_vector_width_double: 4
- preferred_vector_width_half: 16
- native_vector_width_char: 16
- native_vector_width_short: 16
- native_vector_width_int: 8
- native_vector_width_long: 4
- native_vector_width_float: 8
- native_vector_width_double: 4
- native_vector_width_half: 16
- max_clock_frequency: 2445
- address_bits: 64
- max_mem_alloc_size: 4294967296
- image_support: 0
- max_read_image_args: 0
- max_write_image_args: 0
- image2d_max_height: 0
- image2d_max_width: 0
- image3d_max_height: 0
- image3d_max_width: 0
- image3d_max_depth: 0
- image_max_buffer_size: 0
- image_max_array_size: 0
- max_samplers: 0
- max_parameter_size: 1024
- mem_base_addr_align: 1024
- half_fp_config: Denorm, Inf-Nan, Round-to-Nearest, Round-to-Zero, Round-to-Inf, FMA, Correctly-Rounded-Divide-Sqrt
- single_fp_config: Denorm, Inf-Nan, Round-to-Nearest, Round-to-Zero, Round-to-Inf, FMA, Correctly-Rounded-Divide-Sqrt
- double_fp_config: Denorm, Inf-Nan, Round-to-Nearest, Round-to-Zero, Round-to-Inf, FMA, Correctly-Rounded-Divide-Sqrt
- global_mem_cache_type: Read-Only
- global_mem_cache_line_size: 64
- global_mem_cache_size: 33554432
- global_mem_size: 14620839936
- max_constant_buffer_size: 524288
- max_constant_args: 8
- local_mem_type: Global
- local_mem_size: 524288
- error_correction_support: 0
- host_unified_memory: 0
- profiling_timer_resolution: 1
- is_endian_little: 1
- is_available: 1
- is_compiler_available: 1
- is_linker_available: 1
- execution_capabilities: Exec-Kernel
- queue_profiling: 0
- built_in_kernels: 
- printf_buffer_size: 16777216
- preferred_interop_user_sync: 1
- partition_max_sub_devices: 0
- partition_properties: 
- partition_affinity_domains: Not-Applicable
- partition_type_property: No-Partition
- partition_type_affinity_domain: Not-Applicable
- reference_count: 1
 */