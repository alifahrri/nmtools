#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/view/mutable_ref.hpp"
#include "nmtools/array/eval/opencl/kernel_helper.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;
namespace opencl = nm::array::opencl;

#define compute_offset_kernel_name "test_compute_offset"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

kernel void test_compute_offset(
    global int* out_ptr
    , global const int* indices_ptr
    , global const int* strides_ptr
    , const int out_size
    , const int indices_size
    , const int strides_size
) {
    auto id = get_global_id(0);
    if (id == 0) {
        auto output  = view::mutable_ref(out_ptr,out_size);
        auto indices = opencl::create_vector(indices_ptr,indices_size);
        auto strides = opencl::create_vector(strides_ptr,strides_size);

        auto result = ix::compute_offset(indices,strides);
        nm::at(output,0) = result;
    }
}

#else

#endif