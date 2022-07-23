#include "nmtools/array/view/transpose.hpp"
#include "nmtools/array/utility/cast.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/utils/to_string.hpp"
#include "nmtools/array/cast.hpp"

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
    auto axes = std::array{2,0,1};
    DESC("\ntransposing an std::array")
    {
        using array_t = std::array<std::array<std::array<int,3>,2>,2>;
        int raw[2][2][3] = {
            {
                {1,2,3},
                {3,4,5}
            },
            {
                {5,6,7},
                {7,8,9}
            },
        };
        // use helper cast to cast to array_t, need too many braces otherwise
        auto array = nm::cast<int>(raw);
        // we can check the type is the same
        static_assert ( std::is_same_v<decltype(array),array_t> );
        auto transposed = view::transpose(array,axes);
        PRINT(array)
        PRINT(transposed)
    }
    DESC("\ntransposing an na::fixed_ndarray")
    {
        auto array = na::fixed_ndarray{{
            {
                {1,2,3},
                {3,4,5}
            },
            {
                {5,6,7},
                {7,8,9}
            },
        }};
        auto transposed = view::transpose(array,axes);
        PRINT(array)
        PRINT(transposed)
    }
    DESC("\ntransposing an na::dynamic_ndarray")
    {
        auto array = na::dynamic_ndarray({
            {
                {1,2,3},
                {3,4,5}
            },
            {
                {5,6,7},
                {7,8,9}
            },
        });
        auto transposed = view::transpose(array,axes);
        PRINT(array)
        PRINT(transposed)
    }
}
