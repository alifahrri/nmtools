#define NMTOOLS_CIRCLE_CONTEXT_IMPLEMENTATION
#define NMTOOLS_DISABLE_STL
#include "nmtools/evaluator/circle/transform.hxx"
#include "nmtools/meta.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/evaluator/kernel_helper.hpp"
#include "nmtools/array/relu.hpp"
#include "nmtools/exception.hpp"
#include <cstdio>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

using namespace mgpu::vk;

template<int NT = 128, typename type_t>
[[using spirv: comp, local_size(NT), push]]
void compute_shader(int count, type_t a, type_t* x, type_t* y) {
  int gid = glcomp_GlobalInvocationID.x;
  if(gid < count) {
    auto shape = nmtools_array{count};
    auto input = na::create_array(x,shape);
    auto result = view::relu(input);
    x[gid] = nm::at(result,gid);
  }
}

int main() {
  context_t context;

  // Allocate test data storage.
  int count = 100;
  float a = 1.618f;     // A saxpy coefficient.
  float* x = context.alloc_gpu<float>(count);
  float* y = context.alloc_gpu<float>(count);

  // Create a command buffer.
  cmd_buffer_t cmd_buffer(context);
  cmd_buffer.begin();

  // Three ways to launch kernels with mgpu-shaders for Vulkan:

  // 1. Use chevron launch syntax. This calls spirv_chevron_comp and 
  //    passes the shader reference as the template argument. In mgpu's 
  //    implementation, num_blocks and cmd_buffer are the chevron arguments.
  const int NT = 64;    // Use 64 threads per block.
  int num_blocks = mgpu::div_up(count, NT);
  #if 1
  compute_shader<NT><<<num_blocks, cmd_buffer>>>(count, M_PIf32, x, y);
  #endif

  #if 0
  // 2. Use launch(). This is like a chevron launch, but you don't even have
  //    to write a shader. Pass it a function object or lambda. The lambda
  //    gets called back with the glcomp_LocalInvocation.x and 
  //    glcomp_WorkGroupID.x values. As with the chevron launch, specify the
  //    grid size. You must also specify the workgroup size as a template
  //    argument, since you aren't defining a compute on which to attach
  //    local_size.
  launch<NT>(num_blocks, cmd_buffer, [=](int tid, int cta) {
    // tid and cta are the thread and workgroup IDs.
    // combine them for a global ID or read glcomp_GlobalInvocationID.x.
    int gid = tid + NT * cta;

    // Use the default-copy closure to capture the kernel parameters.
    if(gid < count) {
      // SAXPY these terms.
      y[gid] += a * x[gid];
    }
  });
  #endif

  #if 0
  // 3. Use transform(). This is for embarrassingly parallel tasks. It
  //    executes the function object once for each request. You can pass it
  //    the group size as an optional template argument, or use an 
  //    implementation-defined group size.
  transform(count, cmd_buffer, [=](int index) {
    auto shape = nmtools_array{count};
    auto input = na::create_array(y,shape);
    auto result = view::relu(input);
    x[index] = nm::at(result,index);
  });
  #endif

  // Copy the data to host memory.
  float* host = context.alloc_cpu<float>(count);

  cmd_buffer.host_barrier();
  context.memcpy(cmd_buffer, host, x, sizeof(float) * count);
  cmd_buffer.host_barrier();

  // End and submit the command buffer.
  cmd_buffer.end();
  context.submit(cmd_buffer);

  // And wait for it to be done.
  vkQueueWaitIdle(context.queue);

  // Print our results.
  for(int i = 0; i < count; ++i)
    printf("%3d: %f\n", i, host[i]);

  context.free(x);
  context.free(y);
  context.free(host);

  return 0;
}

