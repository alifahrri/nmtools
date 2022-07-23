#include "nmtools/array/view/tile.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/utils/to_string.hpp"

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

using std::tuple;

int main()
{
    auto reps = std::array{2,1,2};
    DESC("\n tiling an std::array")
    {
        auto array = std::array{0,1,2};
        auto tiled = view::tile(array,reps);
        PRINT(array)
        PRINT(tiled)
    }
    DESC("\n tiling an std::vector")
    {
        auto array = std::array{0,1,2};
        auto tiled = view::tile(array,reps);
        PRINT(array)
        PRINT(tiled)
    }
    DESC("\n tiling an na::fixed_ndarray")
    {
        auto array = na::fixed_ndarray{{0,1,2}};
        auto tiled = view::tile(array,reps);
        PRINT(array)
        PRINT(tiled)
    }
    DESC("\n tiling an na::dynamic_ndarray")
    {
        auto array = na::dynamic_ndarray({0,1,2});
        auto tiled = view::tile(array,reps);
        PRINT(array)
        PRINT(tiled)
    }
}