
## GPU Example

```C++
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto input = nm::random(array{4096,4},dtype,gen);

    // Change hip to cuda/sycl if using nvidia/neutral
    // auto ctx  = nm::cuda::default_context();
    // auto ctx  = nm::sycl::default_context();
    auto ctx  = nm::hip::default_context();
    auto axis = 1;
    auto gpu_res = nm::tanh(input,ctx);
    auto cpu_res = nm::tanh(input);
```

### Build

```
export NMTOOLS_INCLUDE_DIR=${HOME}/projects/nmtools/include
hipcc -I$NMTOOLS_INCLUDE_DIR tanh.cpp
```

### Run

```
./a.out
```