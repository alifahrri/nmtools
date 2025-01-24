#include "nmtools/array/expand_dims.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/utility/to_string.hpp"

#include <iostream>
#include <array>
#include <vector>

#define DESC(x) std::cout << x << std::endl;
#define PRINT(x) \
std::cout << #x << ":\n" \
    << nm::utils::to_string(x) \
    << std::endl; \

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

int main()
{
    auto axis = std::array{0,2};
    DESC("\nexpanding an std::array")
    {
        auto array = std::array{1,2,3};
        auto expanded = view::expand_dims(array,axis);
        PRINT(array)
        PRINT(expanded)
    }
    DESC("\nexpanding an std::vector")
    {
        auto array = std::vector{1,2,3};
        auto expanded = view::expand_dims(array,axis);
        PRINT(array)
        PRINT(expanded)
    }
    DESC("\nexpanding an na::fixed_ndarray")
    {
        auto array = na::fixed_ndarray{{1,2,3}};
        auto expanded = view::expand_dims(array,axis);
        PRINT(array)
        PRINT(expanded)
    }
    DESC("\nexpanding an na::dynamic_ndarray")
    {
        auto array = na::dynamic_ndarray({1,2,3});
        auto expanded = view::expand_dims(array,axis);
        PRINT(array)
        PRINT(expanded)
    }
}
