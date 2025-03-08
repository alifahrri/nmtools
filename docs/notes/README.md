## Compiler Notes

Notes on compiler differences :(

1. Parameter packs:

```
➜  notes nvcc -x cu nvcc-1.cpp -I/workspace/nmtools/include/ -std=c++17 --gpu-architecture=sm_80
nvcc-1.cpp:104:63: error: parameter packs not expanded with '...':
  104 |         static constexpr auto value = std::array{index_t(Max)...};
      |                                                               ^
nvcc-1.cpp:104:63: note:         'Max'
```
works fine on clang:
```
➜  notes clang -x cuda nvcc-1.cpp -I/workspace/nmtools/include/ -std=c++17 --cuda-gpu-arch=sm_80
clang: warning: CUDA version is newer than the latest supported version 12.3 [-Wunknown-cuda-version]
```