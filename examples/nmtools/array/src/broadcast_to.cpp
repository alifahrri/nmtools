#include "nmtools/array/broadcast_to.hpp"
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
    auto shape = std::array{3,2,3};
    DESC("\nbroadcasting an std::array")
    {
        auto array = std::array{1,2,3};
        auto broadcasted = view::broadcast_to(array,shape);
        PRINT(array)
        PRINT(broadcasted)
    }
    DESC("\nbroadcasting an std::vector")
    {
        auto array = std::vector{1,2,3};
        auto broadcasted = view::broadcast_to(array,shape);
        PRINT(array)
        PRINT(broadcasted)
    }
    DESC("\nbroadcasting an na::fixed_ndarray")
    {
        auto array = na::fixed_ndarray{{1,2,3}};
        auto broadcasted = view::broadcast_to(array,shape);
        PRINT(array)
        PRINT(broadcasted)
    }
    DESC("\nbroadcasting an na::dynamic_ndarray")
    {
        auto array = na::dynamic_ndarray({1,2,3});
        auto broadcasted = view::broadcast_to(array,shape);
        PRINT(array)
        PRINT(broadcasted)
    }
}