#include "nmtools/array/index/choose.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;



TEST_CASE("choose(vector)" * doctest::test_suite("index::choose"))
{
    {
        auto indices = std::vector{0,1,2,3};
        auto array   = std::vector{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::vector{3ul,1ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::vector{1,0,2,3};
        auto array   = std::vector{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::vector{1ul,3ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::vector{2};
        auto array   = std::vector{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::vector{4ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }

    {
        auto indices = std::vector{0,1,2,3};
        auto array   = na::hybrid_ndarray({3ul,1ul,4ul,1ul,5ul,9ul,2ul});
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::vector{3ul,1ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::vector{1,0,2,3};
        auto array   = na::hybrid_ndarray({3ul,1ul,4ul,1ul,5ul,9ul,2ul});
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::vector{1ul,3ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::vector{2};
        auto array   = na::hybrid_ndarray({3ul,1ul,4ul,1ul,5ul,9ul,2ul});
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::vector{4ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
}

TEST_CASE("choose(array)" * doctest::test_suite("index::choose"))
{
    {
        auto indices = std::array{0,1,2,3};
        auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{3ul,1ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::array{1,0,2,3};
        auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{1ul,3ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::array{2};
        auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{4ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }

    {
        auto indices = std::array{0,1,2,3};
        auto array   = na::hybrid_ndarray({3ul,1ul,4ul,1ul,5ul,9ul,2ul});
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{3ul,1ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::array{1,0,2,3};
        auto array   = na::hybrid_ndarray({3ul,1ul,4ul,1ul,5ul,9ul,2ul});
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{1ul,3ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = std::array{2};
        auto array   = na::hybrid_ndarray({3ul,1ul,4ul,1ul,5ul,9ul,2ul});
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{4ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
}

// TEST_CASE("choose(tuple)" * doctest::test_suite("index::choose"))
// {
//     {
//         auto indices = std::tuple{0,1,2,3};
//         auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{3ul,1ul,4ul,1ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::tuple{1,0,2,3};
//         auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{1ul,3ul,4ul,1ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::tuple{2};
//         auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{4ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::array{0,1,2,3};
//         auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{3ul,1ul,4ul,1ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::array{1,0,2,3};
//         auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{1ul,3ul,4ul,1ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::array{2};
//         auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{4ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::tuple{0,1,2,3};
//         auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{3ul,1ul,4ul,1ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::tuple{1,0,2,3};
//         auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{1ul,3ul,4ul,1ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
//     {
//         auto indices = std::tuple{2};
//         auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
//         auto chosen  = nm::index::choose(indices,array);
//         auto expected = std::tuple{4ul};
//         NMTOOLS_ASSERT_CLOSE( chosen, expected );
//     }
// }

TEST_CASE("choose(hybrid_ndarray)" * doctest::test_suite("index::choose"))
{
    // {
    //     auto indices = na::hybrid_ndarray({0,1,2,3});
    //     auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
    //     auto chosen  = nm::index::choose(indices,array);
    //     auto expected = std::array{3ul,1ul,4ul,1ul};
    //     NMTOOLS_ASSERT_CLOSE( chosen, expected );
    // }
    // {
        // auto indices = na::hybrid_ndarray({1,0,2,3});
        // auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        // auto chosen  = nm::index::choose(indices,array);
        // auto expected = std::array{1ul,3ul,4ul,1ul};
        // NMTOOLS_ASSERT_CLOSE( chosen, expected );
    // }
    // {
    //     auto indices = na::hybrid_ndarray({2});
    //     auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
    //     auto chosen  = nm::index::choose(indices,array);
    //     auto expected = std::array{4ul};
    //     NMTOOLS_ASSERT_CLOSE( chosen, expected );
    // }
    // {
    //     auto indices = na::hybrid_ndarray({0,1,2,3});
    //     auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
    //     auto chosen  = nm::index::choose(indices,array);
    //     auto expected = std::array{3ul,1ul,4ul,1ul};
    //     NMTOOLS_ASSERT_CLOSE( chosen, expected );
    // }
    // {
    //     auto indices = na::hybrid_ndarray({1,0,2,3});
    //     auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
    //     auto chosen  = nm::index::choose(indices,array);
    //     auto expected = std::array{1ul,3ul,4ul,1ul};
    //     NMTOOLS_ASSERT_CLOSE( chosen, expected );
    // }
    // {
    //     auto indices = na::hybrid_ndarray({2});
    //     auto array   = std::tuple{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
    //     auto chosen  = nm::index::choose(indices,array);
    //     auto expected = std::array{4ul};
    //     NMTOOLS_ASSERT_CLOSE( chosen, expected );
    // }
    {
        auto indices = na::hybrid_ndarray({0,1,2,3});
        auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{3ul,1ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = na::hybrid_ndarray({1,0,2,3});
        auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{1ul,3ul,4ul,1ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
    {
        auto indices = na::hybrid_ndarray({2});
        auto array   = std::array{3ul,1ul,4ul,1ul,5ul,9ul,2ul};
        auto chosen  = nm::index::choose(indices,array);
        auto expected = std::array{4ul};
        NMTOOLS_ASSERT_CLOSE( chosen, expected );
    }
}