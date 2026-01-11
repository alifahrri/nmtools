## Tilekit Example

Vector add kernel:
```C++
template <typename context_t, typename out_t, typename a_t, typename b_t>
auto vector_add(context_t& ctx, out_t& out, const a_t& a, const b_t& b)
{
    auto t_shape  = tuple{4_ct};
    auto [dim0]   = t_shape;
    auto a_shape  = shape(a);
    auto [a_dim0] = a_shape;
    auto n_iter   = a_dim0 / dim0;

    for (nm_size_t i=0; i<n_iter; i++) {
        auto offset  = tuple{i};
        auto block_a = tk::load(ctx,a,offset,t_shape);
        auto block_b = tk::load(ctx,b,offset,t_shape);
        auto result  = block_a + block_b;

        tk::store(ctx,out,offset,result);
    }
}
```

### Build

To build, simply use g++. You can change the micro-architecture in the `-march` flag, e.g. `-march=native`.
```sh
export NMTOOLS_INCLUDE_DIR=${HOME}/projects/nmtools/include
g++ -std=c++17 -O3 -Og -march=znver5 -I$NMTOOLS_INCLUDE_DIR vector_add.cpp
```

### Run

```sh
./a.out
```

To run it under perf:
```sh
sudo perf record ./a.out
sudo perf report
```
This is useful to show the actual instruction that's running.
![perf-report.png](perf-report.png)
As you can see, the vector_add is vectorized using simd instruction.