#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/array/conv2d.hpp"
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
// runtime error
TEST_CASE("conv2d(case1)" * doctest::test_suite("array::conv2d") * doctest::skip())
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto input  = na::random(array{1,1,4,4},dtype,gen);
    auto weight = na::random(array{1,1,3,3},dtype,gen);

    SYCL_TEST(conv2d,input,weight,nm::None,nm::None,nm::None,nm::None,meta::ct_v<1>);
}
#endif

// NOTE: weird error on ci
// dlsym("/root/.cache/pocl/kcache/NH/JAPJOILDDIGOJJLMHOKFGOKEOGDLBDMFIHOPB/_Z18__acpp_sscp_kernelI.IENLHCOKILPFFNHCDFDPNAMDGLAHPCMIPMDHOPID/32-1-1-goffs0-smallgrid/_Z18__acpp_sscp_ke.IENLHCOKILPFFNHCDFDPNAMDGLAHPCMIPMDHOPID.so", "pocl_kernel__Z18__acpp_sscp_kernelIN7syclsycl4glue15__sscp_dispatch20ndrange_parallel_forIZZN7nmtools5array4sycl9context_t4run_INS5_9ndarray_tINS4_3utl6vectorIfNSA_9allocatorIfEEEENSB_ImNSC_ImEEEENS5_21resolve_stride_type_tENS5_18row_major_offset_tEvEENS4_10functional21functor_composition_tINSA_7tuplev2IJNSK_9functor_tINSK_6fmap_tINSK_3fun8indexingELm1ELm1EEENS4_4meta16empty_operands_tENSM_IJNS4_4args8indexingINSA_5maybeINS4_4view9reshape_tINSA_5arrayImLm5EEENSZ_ImLm4EEEmEEvEEEEEEEEENSN_INSO_INSP_6reduceINS4_6none_tEEELm1ELm1EEEST_NSM_IJNSU_6reduceINSM_IJNSS_17integral_constantIiLin1EEENS1C_IiLin2EEENS1C_IiLi3EEEEEES18_S18_NSS_10false_typeENSX_3fun3addIS18_S18_S18_vEEEEEEEEENSN_INSO_INSP_22broadcast_binary_ufuncIS18_EELm2ELm1EEEST_NSM_IJNSU_5ufuncINS1I_8multiplyIS18_S18_S18_vEEEEEEEEENSN_INSO_INS4_10combinator5dig_tILi1EEELm2ELm2EEEST_NSS_18empty_attributes_tEEENSN_ISR_ST_NSM_IJNSV_INSX_16sliding_window_tIS10_NSZ_IiLm2EEENSM_IJS1D_S1E_EEEEEEEEEEEENSN_ISR_ST_NSM_IJNSV_INSW_INSY_IS11_S10_mEEvEEEEEEEEENSN_INSO_I") failed with '/root/.cache/pocl/kcache/NH/JAPJOILDDIGOJJLMHOKFGOKEOGDLBDMFIHOPB/_Z18__acpp_sscp_kernelI.IENLHCOKILPFFNHCDFDPNAMDGLAHPCMIPMDHOPID/32-1-1-goffs0-smallgrid/_Z18__acpp_sscp_ke.IENLHCOKILPFFNHCDFDPNAMDGLAHPCMIPMDHOPID.so: undefined symbol: pocl_kernel__Z18__acpp_sscp_kernelIN7syclsycl4glue15__sscp_dispatch20ndrange_parallel_forIZZN7nmtools5array4sycl9context_t4run_INS5_9ndarray_tINS4_3utl6vectorIfNSA_9allocatorIfEEEENSB_ImNSC_ImEEEENS5_21resolve_stride_type_tENS5_18row_major_offset_tEvEENS4_10functional21functor_composition_tINSA_7tuplev2IJNSK_9functor_tINSK_6fmap_tINSK_3fun8indexingELm1ELm1EEENS4_4meta16empty_operands_tENSM_IJNS4_4args8indexingINSA_5maybeINS4_4view9reshape_tINSA_5arrayImLm5EEENSZ_ImLm4EEEmEEvEEEEEEEEENSN_INSO_INSP_6reduceINS4_6none_tEEELm1ELm1EEEST_NSM_IJNSU_6reduceINSM_IJNSS_17integral_constantIiLin1EEENS1C_IiLin2EEENS1C_IiLi3EEEEEES18_S18_NSS_10false_typeENSX_3fun3addIS18_S18_S18_vEEEEEEEEENSN_INSO_INSP_22broadcast_binary_ufuncIS18_EELm2ELm1EEEST_NSM_IJNSU_5ufuncINS1I_8multiplyIS18_S18_S18_vEEEEEEEEENSN_INSO_INS4_10combinator5dig_tILi1EEELm2ELm2EEEST_NSS_18empty_attributes_tEEENSN_ISR_ST_NSM_IJNSV_INSX_16sliding_window_tIS10_NSZ_IiLm2EEENSM_IJS1D_S1E_EEEEEEEEEEEENSN_ISR_ST_NSM_IJNSV_INSW_INSY_IS11_S10_mEEvEEEEEEEEENSN_INSO_I'.
// note: missing symbols in the kernel binary might be reported as 'file not found' errors.
TEST_CASE("conv2d(case1b)" * doctest::test_suite("array::conv2d") * doctest::skip())
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto input  = na::random(array{1,1,4,4},dtype,gen);
    auto weight = na::random(array{1,1,3,3},dtype,gen);

    SYCL_LINEAR_TEST(conv2d,input,weight,nm::None,nm::None,nm::None,nm::None,meta::ct_v<1>);
}

/**
[doctest] doctest version is "2.4.8"
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