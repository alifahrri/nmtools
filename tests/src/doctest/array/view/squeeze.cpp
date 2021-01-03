#include "nmtools/array/view/squeeze.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace view = nm::view;

TEST_CASE("squeeze(raw(6)->(6))" * doctest::test_suite("view::squeeze"))
{
    double array[6] = {1,2,3,4,5,6};
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(array(6)->(6))" * doctest::test_suite("view::squeeze"))
{
    auto array = std::array{1,2,3,4,5,6};
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(vector(6)->(6))" * doctest::test_suite("view::squeeze"))
{
    auto array = std::vector{1,2,3,4,5,6};
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(fixed_vector(6)->(6))" * doctest::test_suite("view::squeeze"))
{
    auto array = na::fixed_vector{{1,2,3,4,5,6}};
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(dynamic_vector(6)->(6))" * doctest::test_suite("view::squeeze"))
{
    auto array = na::dynamic_vector{{1,2,3,4,5,6}};
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(raw(6x1)->(6))" * doctest::test_suite("view::squeeze"))
{
    double array[6][1] = {
        {1},
        {2},
        {3},
        {4},
        {5},
        {6}
    };
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(raw(6x2)->(6x2))" * doctest::test_suite("view::squeeze"))
{
    double array[6][2] = {
        {1,1},
        {2,2},
        {3,3},
        {4,4},
        {5,5},
        {6,6}
    };
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6,2};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6][2] = {
        {1,1},
        {2,2},
        {3,3},
        {4,4},
        {5,5},
        {6,6}
    };

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(raw(1x6)->(6))" * doctest::test_suite("view::squeeze"))
{
    double array[1][6] = {
        {1,2,3,4,5,6}
    };
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(raw(6x1x1)->(6))" * doctest::test_suite("view::squeeze"))
{
    double array[6][1][1] = {
        {
            {1}
        },
        {
            {2}
        },
        {
            {3}
        },
        {
            {4}
        },
        {
            {5}
        },
        {
            {6}
        }
    };
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(raw(1x6x1)->(6))" * doctest::test_suite("view::squeeze"))
{
    double array[1][6][1] = {
        {
            {1},
            {2},
            {3},
            {4},
            {5},
            {6}
        }
    };
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(raw(1x1x6)->(6))" * doctest::test_suite("view::squeeze"))
{
    double array[1][1][6] = {
        {
            {1,2,3,4,5,6}
        }
    };
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(array(1x6)->(6))" * doctest::test_suite("view::squeeze"))
{
    std::array<std::array<double,6>,1> array = {
        {1,2,3,4,5,6}
    };
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(array(6x1)->(6))" * doctest::test_suite("view::squeeze"))
{
    // gcc error too many initializer, clang error excess element in struct init
    // std::array<std::array<double,1>,6> array = {
    //     {1},
    //     {2},
    //     {3},
    //     {4},
    //     {5},
    //     {6}
    // };
    std::array<std::array<double,1>,6> array = {1,2,3,4,5,6};
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(array(6x2)->(6x2))" * doctest::test_suite("view::squeeze"))
{
    std::array<std::array<double,2>,6> array = {{
        {1,1},
        {2,2},
        {3,3},
        {4,4},
        {5,5},
        {6,6}
    }};
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6,2};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6][2] = {
        {1,1},
        {2,2},
        {3,3},
        {4,4},
        {5,5},
        {6,6}
    };

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(array(1x6x1)->(6))" * doctest::test_suite("view::squeeze"))
{
    // :'D
    // std::array<std::array<std::array<double,1>,6>,1> array = {
    //     {
    //         {1},
    //         {2},
    //         {3},
    //         {4},
    //         {5},
    //         {6}
    //     }
    // };
    std::array<std::array<std::array<double,1>,6>,1> array = {1,2,3,4,5,6};
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(vector(6x1)->(6))" * doctest::test_suite("view::squeeze"))
{
    std::vector<std::vector<double>> array = {
        {1},
        {2},
        {3},
        {4},
        {5},
        {6}
    };
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(vector(1x6)->(6))" * doctest::test_suite("view::squeeze"))
{
    std::vector<std::vector<double>> array = {
        {1,2,3,4,5,6}
    };
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(vector(6x1x1)->(6))" * doctest::test_suite("view::squeeze"))
{
    std::vector<std::vector<std::vector<double>>> array = {
        {
            {1}
        },
        {
            {2}
        },
        {
            {3}
        },
        {
            {4}
        },
        {
            {5}
        },
        {
            {6}
        }
    };
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(vector(1x6x1)->(6))" * doctest::test_suite("view::squeeze"))
{
    std::vector<std::vector<std::vector<double>>> array = {
        {
            {1},
            {2},
            {3},
            {4},
            {5},
            {6}
        }
    };
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(vector(1x1x6)->(6))" * doctest::test_suite("view::squeeze"))
{
    std::vector<std::vector<std::vector<double>>> array = {
        {
            {1,2,3,4,5,6}
        }
    };
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(vector(6x1)->(6))" * doctest::test_suite("view::squeeze"))
{
    double init[6][1] = {
        {1},
        {2},
        {3},
        {4},
        {5},
        {6}
    };
    auto array = na::dynamic_ndarray(std::move(init));
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};
    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(vector(1x6)->(6))" * doctest::test_suite("view::squeeze"))
{
    auto array = na::dynamic_ndarray({
        {1,2,3,4,5,6}
    });
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(dynamic_ndarray(6x1x1)->(6))" * doctest::test_suite("view::squeeze"))
{
    // auto array = na::dynamic_ndarray({
    //     {
    //         {1}
    //     },
    //     {
    //         {2}
    //     },
    //     {
    //         {3}
    //     },
    //     {
    //         {4}
    //     },
    //     {
    //         {5}
    //     },
    //     {
    //         {6}
    //     }
    // });
    double init[6][1][1] = {
        {
            {1}
        },
        {
            {2}
        },
        {
            {3}
        },
        {
            {4}
        },
        {
            {5}
        },
        {
            {6}
        }
    };
    auto array = na::dynamic_ndarray(std::move(init));
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};
    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

// gcc accept but clang doesnt
// clang error: call to constructor of 'na::dynamic_ndarray<int, std::vector, std::vector>' 
// (aka 'nmtools::array::dynamic_ndarray<int, std::vector, std::vector>') is ambiguous
// somehow using this macro doesnt work
// #ifndef __GNUC__
#ifndef __clang__
TEST_CASE("squeeze(dynamic_ndarray(1x6x1)->(6))" * doctest::test_suite("view::squeeze"))
{
    // ambiguous call
    // auto array = na::dynamic_ndarray({
    //     {
    //         {1},
    //         {2},
    //         {3},
    //         {4},
    //         {5},
    //         {6}
    //     }
    // });
    double init[1][6][1] = {
        {
            {1},
            {2},
            {3},
            {4},
            {5},
            {6}
        }
    };
    auto array = na::dynamic_ndarray(std::move(init));
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};
    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(vector(1x1x6)->(6))" * doctest::test_suite("view::squeeze"))
{
    auto array = na::dynamic_ndarray({
        {
            {1,2,3,4,5,6}
        }
    });
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}
#endif // __GNUC__

TEST_CASE("squeeze(fixed_ndarray(1x6)->(6))" * doctest::test_suite("view::squeeze"))
{
    auto array = na::fixed_ndarray{{
        {1,2,3,4,5,6}
    }};
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(fixed_ndarray(6x1)->(6))" * doctest::test_suite("view::squeeze"))
{
    auto array = na::fixed_ndarray<double,6,1>{{
        {1},
        {2},
        {3},
        {4},
        {5},
        {6}
    }};
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(fixed_ndarray(1x6)->(6))" * doctest::test_suite("view::squeeze"))
{
    auto array = na::fixed_ndarray<double,1,6>{{
        {1,2,3,4,5,6}
    }};
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

// TEST_CASE("squeeze(fixed_ndarray(6x1x1)->(6))" * doctest::test_suite("view::squeeze"))
// {
//     auto array = na::fixed_ndarray<double,6,1,1>{{
//         {
//             {1}
//         },
//         {
//             {2}
//         },
//         {
//             {3}
//         },
//         {
//             {4}
//         },
//         {
//             {5}
//         },
//         {
//             {6}
//         }
//     }};
//     auto squeezed = view::squeeze(array);
//     using squeezed_t = decltype(squeezed);

//     auto shape = std::array{6};
//     NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
//     NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

//     double expected[6] = {1,2,3,4,5,6};
//     NMTOOLS_ASSERT_CLOSE( squeezed, expected );
// }

// TEST_CASE("squeeze(fixed_ndarrayr(1x6x1)->(6))" * doctest::test_suite("view::squeeze"))
// {
//     auto array = na::fixed_ndarray<double,1,6,1>{{
//         {
//             {1},
//             {2},
//             {3},
//             {4},
//             {5},
//             {6}
//         }
//     }};
//     auto squeezed = view::squeeze(array);
//     using squeezed_t = decltype(squeezed);

//     auto shape = std::array{6};
//     NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
//     NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

//     double expected[6] = {1,2,3,4,5,6};
//     NMTOOLS_ASSERT_CLOSE( squeezed, expected );
// }

TEST_CASE("squeeze(fixed_ndarray(1x1x6)->(6))" * doctest::test_suite("view::squeeze"))
{
    auto array = na::fixed_ndarray{{
        {
            {1,2,3,4,5,6}
        }
    }};
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    STATIC_CHECK_TRAIT( meta::is_ndarray, squeezed_t );

    auto shape = std::array{6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 1 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[6] = {1,2,3,4,5,6};

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}

TEST_CASE("squeeze(fixed_ndarray(1x2x6)->(6))" * doctest::test_suite("view::squeeze"))
{
    auto array = na::fixed_ndarray{{
        {
            {1,2,3,4,5,6},
            {1,2,3,4,5,6}
        }
    }};
    auto squeezed = view::squeeze(array);
    using squeezed_t = decltype(squeezed);

    STATIC_CHECK_TRAIT( meta::is_ndarray, squeezed_t );

    auto shape = std::array{2,6};
    NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

    double expected[2][6] = {
        {1,2,3,4,5,6},
        {1,2,3,4,5,6}
    };

    NMTOOLS_ASSERT_CLOSE( squeezed, expected );
}