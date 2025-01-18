#include "nmtools/index/filter.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/testing/doctest.hpp"

// to allow std::array, vector, tuple identified as array/index
#include "nmtools/meta/stl.hpp"
#include "nmtools/array/impl/stl.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;

#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("filter(vector)" * doctest::test_suite("index::filter"))
{
    {
        auto array = std::vector{3,1,4,1,5,9,2};
        auto f = [](auto a){
            return a == 1;
        };
        // @note clang refuse to compile this:
        // error: reference to local binding 'filtered' declared in enclosing function
        // auto [arg, filtered] = nm::index::filter(f,array);
        auto result = nm::index::filter(f,array);
        auto filtered = nmtools::get<1>(result);
        auto expected = std::vector{1,1};
        NMTOOLS_ASSERT_CLOSE( filtered, expected );
    }
    {
        auto array = std::vector{3,1,4,1,5,9,2};
        auto f = [](auto a){
            return a > 1;
        };
        // @note clang refuse to compile this:
        // error: reference to local binding 'filtered' declared in enclosing function
        // auto [arg, filtered] = nm::index::filter(f,array);
        auto result = nm::index::filter(f,array);
        auto filtered = nmtools::get<1>(result);
        auto expected = std::vector{3,4,5,9,2};
        NMTOOLS_ASSERT_CLOSE( filtered, expected );
    }
    {
        auto array = std::vector{3,1,4,1,5,9,2};
        auto f = [](auto a){
            return a < 1;
        };
        // @note clang refuse to compile this:
        // error: reference to local binding 'filtered' declared in enclosing function
        // auto [arg, filtered] = nm::index::filter(f,array);
        auto result = nm::index::filter(f,array);
        auto filtered = nmtools::get<1>(result);
        auto expected = std::vector<int>{};
        NMTOOLS_ASSERT_CLOSE( filtered, expected );
    }
    {
        auto array = std::vector{3,1,4,1,5,9,2};
        auto f = [](auto a){
            return a > 0;
        };
        // @note clang refuse to compile this:
        // error: reference to local binding 'filtered' declared in enclosing function
        // auto [arg, filtered] = nm::index::filter(f,array);
        auto result = nm::index::filter(f,array);
        auto filtered = nmtools::get<1>(result);
        auto expected = std::vector{3,1,4,1,5,9,2};
        NMTOOLS_ASSERT_CLOSE( filtered, expected );
    }
}
#endif // NMTOOLS_DISABLE_STL

TEST_CASE("filter(array)" * doctest::test_suite("index::filter"))
{
    {
        auto array = nmtools_array{3,1,4,1,5,9,2};
        auto f = [](auto a){
            return a == 1;
        };
        // @note clang refuse to compile this:
        // error: reference to local binding 'filtered' declared in enclosing function
        // auto [arg, filtered] = nm::index::filter(f,array);
        auto result = nm::index::filter(f,array);
        auto filtered = nmtools::get<1>(result);
        auto expected = nmtools_array{1,1};
        NMTOOLS_ASSERT_CLOSE( filtered, expected );
    }
    {
        auto array = nmtools_array{3,1,4,1,5,9,2};
        auto f = [](auto a){
            return a > 1;
        };
        // @note clang refuse to compile this:
        // error: reference to local binding 'filtered' declared in enclosing function
        // auto [arg, filtered] = nm::index::filter(f,array);
        auto result = nm::index::filter(f,array);
        auto filtered = nmtools::get<1>(result);
        auto expected = nmtools_array{3,4,5,9,2};
        NMTOOLS_ASSERT_CLOSE( filtered, expected );
    }
    #ifndef NMTOOLS_DISABLE_STL
    {
        auto array = nmtools_array{3,1,4,1,5,9,2};
        auto f = [](auto a){
            return a < 1;
        };
        // @note clang refuse to compile this:
        // error: reference to local binding 'filtered' declared in enclosing function
        // auto [arg, filtered] = nm::index::filter(f,array);
        auto result = nm::index::filter(f,array);
        auto filtered = nmtools::get<1>(result);
        auto expected = std::vector<int>{};
        NMTOOLS_ASSERT_CLOSE( filtered, expected );
    }
    #endif // NMTOOLS_DISABLE_STL
    {
        auto array = nmtools_array{3,1,4,1,5,9,2};
        auto f = [](auto a){
            return a > 0;
        };
        // @note clang refuse to compile this:
        // error: reference to local binding 'filtered' declared in enclosing function
        // auto [arg, filtered] = nm::index::filter(f,array);
        auto result = nm::index::filter(f,array);
        auto filtered = nmtools::get<1>(result);
        auto expected = nmtools_array{3,1,4,1,5,9,2};
        NMTOOLS_ASSERT_CLOSE( filtered, expected );
    }
}

// using tuple with runtime value not supported yet
// TEST_CASE("filter(tuple)" * doctest::test_suite("index::filter"))
// {
//     {
//         auto array = std::tuple{3,1,4,1,5,9,2};
//         auto f = [](auto a){
//             return a == 1;
//         };
//         // @note clang refuse to compile this:
//         // error: reference to local binding 'filtered' declared in enclosing function
//         // auto [arg, filtered] = nm::index::filter(f,array);
//         auto result = nm::index::filter(f,array);
//         auto arg = nmtools::get<0>(result);
//         auto filtered = nmtools::get<1>(result);
//         auto expected = nmtools_array{1,1};
//         NMTOOLS_ASSERT_CLOSE( filtered, expected );
//     }
//     {
//         auto array = std::tuple{3,1,4,1,5,9,2};
//         auto f = [](auto a){
//             return a > 1;
//         };
//         // @note clang refuse to compile this:
//         // error: reference to local binding 'filtered' declared in enclosing function
//         // auto [arg, filtered] = nm::index::filter(f,array);
//         auto result = nm::index::filter(f,array);
//         auto arg = nmtools::get<0>(result);
//         auto filtered = nmtools::get<1>(result);
//         auto expected = nmtools_array{3,4,5,9,2};
//         NMTOOLS_ASSERT_CLOSE( filtered, expected );
//     }
//     {
//         auto array = std::tuple{3,1,4,1,5,9,2};
//         auto f = [](auto a){
//             return a < 1;
//         };
//         // @note clang refuse to compile this:
//         // error: reference to local binding 'filtered' declared in enclosing function
//         // auto [arg, filtered] = nm::index::filter(f,array);
//         auto result = nm::index::filter(f,array);
//         auto arg = nmtools::get<0>(result);
//         auto filtered = nmtools::get<1>(result);
//         auto expected = std::vector<int>{};
//         NMTOOLS_ASSERT_CLOSE( filtered, expected );
//     }
//     {
//         auto array = std::tuple{3,1,4,1,5,9,2};
//         auto f = [](auto a){
//             return a > 0;
//         };
//         // @note clang refuse to compile this:
//         // error: reference to local binding 'filtered' declared in enclosing function
//         // auto [arg, filtered] = nm::index::filter(f,array);
//         auto result = nm::index::filter(f,array);
//         auto arg = nmtools::get<0>(result);
//         auto filtered = nmtools::get<1>(result);
//         auto expected = nmtools_array{3,1,4,1,5,9,2};
//         NMTOOLS_ASSERT_CLOSE( filtered, expected );
//     }
// }

TEST_CASE("filter(hybrid_ndarray)" * doctest::test_suite("index::filter"))
{
    {
        auto array = na::hybrid_ndarray({3,1,4,1,5,9,2});
        auto f = [](auto a){
            return a == 1;
        };
        // @note clang refuse to compile this:
        // error: reference to local binding 'filtered' declared in enclosing function
        // auto [arg, filtered] = nm::index::filter(f,array);
        auto result = nm::index::filter(f,array);
        auto filtered = nmtools::get<1>(result);
        auto expected = nmtools_array{1,1};
        NMTOOLS_ASSERT_CLOSE( filtered, expected );
    }
    {
        auto array = na::hybrid_ndarray({3,1,4,1,5,9,2});
        auto f = [](auto a){
            return a > 1;
        };
        // @note clang refuse to compile this:
        // error: reference to local binding 'filtered' declared in enclosing function
        // auto [arg, filtered] = nm::index::filter(f,array);
        auto result = nm::index::filter(f,array);
        auto filtered = nmtools::get<1>(result);
        auto expected = nmtools_array{3,4,5,9,2};
        NMTOOLS_ASSERT_CLOSE( filtered, expected );
    }
    #ifndef NMTOOLS_DISABLE_STL
    {
        auto array = na::hybrid_ndarray({3,1,4,1,5,9,2});
        auto f = [](auto a){
            return a < 1;
        };
        // @note clang refuse to compile this:
        // error: reference to local binding 'filtered' declared in enclosing function
        // auto [arg, filtered] = nm::index::filter(f,array);
        auto result = nm::index::filter(f,array);
        auto filtered = nmtools::get<1>(result);
        auto expected = std::vector<int>{};
        NMTOOLS_ASSERT_CLOSE( filtered, expected );
    }
    #endif // NMTOOLS_DISABLE_STL
    {
        auto array = na::hybrid_ndarray({3,1,4,1,5,9,2});
        auto f = [](auto a){
            return a > 0;
        };
        // @note clang refuse to compile this:
        // error: reference to local binding 'filtered' declared in enclosing function
        // auto [arg, filtered] = nm::index::filter(f,array);
        auto result = nm::index::filter(f,array);
        auto filtered = nmtools::get<1>(result);
        auto expected = nmtools_array{3,1,4,1,5,9,2};
        NMTOOLS_ASSERT_CLOSE( filtered, expected );
    }
}