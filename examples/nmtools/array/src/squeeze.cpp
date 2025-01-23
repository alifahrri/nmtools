#include "nmtools/array/squeeze.hpp"
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
    DESC("\nsqueezing an std::array")
    {
        using array_t = std::array<std::array<int,1>,3>;
        array_t array = {1,2,3};
        auto squeezed = view::squeeze(array);
        PRINT(array)
        PRINT(squeezed)
    }
    DESC("\nsqueezing an std::vector")
    {
        using array_t = std::vector<std::vector<int>>;
        array_t array = {{1},{2},{3}};
        auto squeezed = view::squeeze(array);
        PRINT(array)
        PRINT(squeezed)
    }
    DESC("\nsqueezing an na::fixed_ndarray")
    {
        auto array = na::fixed_ndarray<int,3,1>{{{1},{2},{3}}};
        auto squeezed = view::squeeze(array);
        PRINT(array)
        PRINT(squeezed)
    }
    DESC("\nsqueezing an na::dynamic_ndarray")
    {
        int raw[3][1] = {
            {1},
            {2},
            {3}
        };
        auto array = na::dynamic_ndarray(std::move(raw));
        auto squeezed = view::squeeze(array);
        PRINT(array)
        PRINT(squeezed)
    }
}