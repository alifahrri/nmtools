#include "nmtools/array/transpose.hpp"
#include "nmtools/utility/cast.hpp"
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
    DESC("\ntransposing an nm::fixed_ndarray")
    {
        auto array = nm::fixed_ndarray{{
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
    DESC("\ntransposing an nm::dynamic_ndarray")
    {
        auto array = nm::dynamic_ndarray({
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
