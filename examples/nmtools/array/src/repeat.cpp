#include "nmtools/array/repeat.hpp"
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
    auto repeats = std::array{1,2};
    int axis = 1;
    DESC("\n repeating an std::array")
    {
        using array_t = std::array<std::array<int,2>,2>;
        array_t array = {{{1,2},{3,4}}};
        auto repeated = view::repeat(array,repeats,axis);
        PRINT(array)
        PRINT(repeated)
    }
    DESC("\n repeating an std::vector")
    {
        using array_t = std::vector<std::vector<int>>;
        array_t array = {{{1,2},{3,4}}};
        auto repeated = view::repeat(array,repeats,axis);
        PRINT(array)
        PRINT(repeated)
    }
    DESC("\n repeating an na::fixed_ndarray")
    {
        na::fixed_ndarray array = {{{1,2},{3,4}}};
        auto repeated = view::repeat(array,repeats,axis);
        PRINT(array)
        PRINT(repeated)
    }
    DESC("\n repeating an na::dynamic_ndarray")
    {
        auto array = na::dynamic_ndarray{{{1,2},{3,4}}};
        auto repeated = view::repeat(array,repeats,axis);
        PRINT(array)
        PRINT(repeated)
    }
}