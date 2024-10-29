#include "nmtools/array/view/reshape.hpp"
#include "nmtools/array/ndarray.hpp"
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
    auto newshape = std::array{3,2,2};
    DESC("\nreshaping an std::array")
    {
        auto array = std::array{1,2,3,4,5,6,7,8,9,10,11,12};
        auto reshaped = view::reshape(array,newshape);
        PRINT(array)
        PRINT(reshaped)
    }
    DESC("\nreshaping an std::vector")
    {
        auto array = std::vector{1,2,3,4,5,6,7,8,9,10,11,12};
        auto reshaped = view::reshape(array,newshape);
        PRINT(array)
        PRINT(reshaped)
    }
    DESC("\nreshaping an na::fixed_ndarray")
    {
        auto array = na::fixed_ndarray{{1,2,3,4,5,6,7,8,9,10,11,12}};
        auto reshaped = view::reshape(array,newshape);
        PRINT(array)
        PRINT(reshaped)
    }
    DESC("\nreshaping an na::dynamic_ndarray")
    {
        auto array = na::dynamic_ndarray({1,2,3,4,5,6,7,8,9,10,11,12});
        auto reshaped = view::reshape(array,newshape);
        PRINT(array)
        PRINT(reshaped)
    }
}
