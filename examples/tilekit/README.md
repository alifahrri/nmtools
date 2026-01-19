## Tilekit Example

Vector add kernel:
```C++
/* includes */

/* Multicore + SIMD */
using mt_vector = tk::thread_pool<tk::vector::context_t>;

struct add_kernel_t
{
    template <typename tile_shape_t=tuple<nm::ct<2>,nm::ct<4>>, typename context_t, typename out_t, typename a_t, typename b_t>
    auto operator()(context_t ctx, out_t& out, const a_t& a, const b_t& b, const tile_shape_t t_shape=tile_shape_t{})
    {
        auto [t_id] = tk::worker_id(ctx);
        auto [t_size] = tk::worker_size(ctx);

        auto a_shape = shape(a);
        auto offset  = tk::ndoffset(a_shape,t_shape);
        // t_size num workers
        auto n_iter = (offset.size()/t_size);
        for (nm_size_t i=0; i<n_iter; i++) {
            auto tile_offset = offset[(t_id*n_iter)+i];
            auto block_a = tk::load(ctx,a,tile_offset,t_shape);
            auto block_b = tk::load(ctx,b,tile_offset,t_shape);
            auto result  = block_a + block_b;

            tk::store(ctx,out,tile_offset,result);
        }
    }
};
inline auto add_kernel = add_kernel_t{};

int main(int argc, char** argv)
{
    /* setup a,b,c*/

    auto tile_shape  = tuple{2_ct,16_ct};
    auto num_threads = 4;
    auto ctx         = mt_vector(num_threads);
    auto worker_size = num_threads;

    ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);

    /* check or use result */
    
    return 0;
}
```

### Build

To build, simply use g++. You can change the micro-architecture in the `-march` flag, e.g. `-march=native`.
```sh
export NMTOOLS_INCLUDE_DIR=${HOME}/projects/nmtools/include
g++ -std=c++17 -Og -O3 -march=znver5 -I$NMTOOLS_INCLUDE_DIR add.cpp
```

### Run

```sh
./a.out
```

To run it under perf:
```sh
sudo perf record -a -g -F 999 -- ./a.out
```
To visualize the call tree, flame graph along with the timeline view for each threads:
```sh
sudo perf script > out.perf
```
![perf-script.png](perf-script.png)  
As you can see, we have 8 worker threads saturated with works.


To see the assembly hotspot, run the following command then select annotate:
```sh
sudo perf report
```
This is useful to show the actual instruction that's running.  
![perf-report.png](perf-report.png)  
As you can see, the add is vectorized using simd instruction.