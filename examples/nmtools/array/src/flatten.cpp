#include "nmtools/array/flatten.hpp"
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
namespace view = nm::view;

int main()
{
    DESC("\n flattening an std::array")
    {
        using array_t = std::array<std::array<int,2>,2>;
        array_t array = {{{1,2},{3,4}}};
        auto flattened = view::flatten(array);
        PRINT(array)
        PRINT(flattened)
    }
    DESC("\n flattening an std::vector")
    {
        using array_t = std::vector<std::vector<int>>;
        array_t array = {{{1,2},{3,4}}};
        auto flattened = view::flatten(array);
        PRINT(array)
        PRINT(flattened)
    }
    DESC("\n flattening an nm::fixed_ndarray")
    {
        nm::fixed_ndarray array = {{{1,2},{3,4}}};
        auto flattened = view::flatten(array);
        PRINT(array)
        PRINT(flattened)
    }
    DESC("\n flattening an nm::dynamic_ndarray")
    {
        auto array = nm::dynamic_ndarray{{{1,2},{3,4}}};
        auto flattened = view::flatten(array);
        PRINT(array)
        PRINT(flattened)
    }
}