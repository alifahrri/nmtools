#include "nmtools/nmtools.hpp"
// Change hip to cuda if using nvidia
#include "nmtools/evaluator/hip.hpp"

#include <iostream>

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

template <typename array_t>
auto print(const array_t& x)
{
    std::cout << "shape: " << utils::to_string(nm::shape(x))
        << std::endl
        << utils::to_string(x)
        << std::endl;
}

int main(int argc, char** argv)
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto input = nm::random(array{4096,4},dtype,gen);

    // Change hip to cuda if using nvida
    auto ctx  = nm::hip::default_context();
    auto axis = 1;
    auto gpu_res = nm::tanh(input,ctx);
    auto cpu_res = nm::tanh(input);

    auto isclose = utils::isclose(gpu_res,cpu_res);

    std::cout << "isclose: "
        << std::boolalpha
        << isclose
        << std::endl;

    return 0;
}