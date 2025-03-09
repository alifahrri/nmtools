// nvcc -x cu nvcc-2.cpp -I/workspace/nmtools/include/ -std=c++17 --gpu-architecture=sm_80
// clang -x cuda nvcc-2.cpp -I/workspace/nmtools/include/ -std=c++17 --cuda-gpu-arch=sm_80
// nvc++ -x cu nvcc-2.cpp -I/workspace/nmtools/include/ -std=c++17 -gpu=cc80
#include "nmtools/core/ufunc.hpp"
#include "nmtools/array/activations/relu.hpp"
#include "nmtools/evaluator/cuda/context.hpp"

int main()
{
    return 0;
}