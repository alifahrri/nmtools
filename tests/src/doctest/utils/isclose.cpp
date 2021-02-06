#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/utils/isclose.hpp"
#if __has_include("doctest/doctest.h")
    #if __has_include("doctest/doctest.h")
    #include "doctest/doctest.h"
#else
   #include "doctest.h"
#endif
#else
    #include "doctest.h"
#endif
#include <array>
#include <tuple>
#include <vector>

using std::vector;
using std::array;
using std::tuple;
using nmtools::array::fixed_ndarray;
using nmtools::array::dynamic_ndarray;
using nmtools::utils::isclose;

/**
 * @test isclose(tuple,tuple)
 * 
 */
TEST_CASE("isclose(tuple,tuple)" * doctest::test_suite("utils"))
{
    {
        auto lhs = tuple{1., 2., 3., 4., 5.};
        auto rhs = tuple{1., 2., 3., 4., 5.};
        CHECK( isclose(lhs,rhs) );
    }
    {
        auto lhs = tuple{1., 2., 3., 4., 5.};
        auto rhs = tuple{1., 2., 3., 4., 1.};
        CHECK( !isclose(lhs,rhs) );
    }
}

/**
 * @test isclose(array,array)
 * 
 */
TEST_CASE("isclose(array,array)" * doctest::test_suite("utils"))
{
    {
        auto lhs = array{1., 2., 3., 4., 5.};
        auto rhs = array{1., 2., 3., 4., 5.};
        CHECK( isclose(lhs,rhs) );
    }
    {
        auto lhs = array{1., 2., 3., 4., 5.};
        auto rhs = array{1., 2., 2., 4., 5.};
        CHECK( !isclose(lhs,rhs) );
    }
}

TEST_CASE("isclose(vector,vector)" * doctest::test_suite("utils"))
{
    {
        auto lhs = vector{1., 2., 3., 4., 5.};
        auto rhs = vector{1., 2., 3., 4., 5.};
        CHECK( isclose(lhs,rhs) );
    }
    {
        auto lhs = vector{1., 2., 3., 4., 5.};
        auto rhs = vector{1., 2., 3., 4., 1.};
        CHECK( !isclose(lhs,rhs) );
    }
}

TEST_CASE("isclose(int[],int[])" * doctest::test_suite("utils"))
{
    {
        double lhs[5] = {1., 2., 3., 4., 5.};
        double rhs[5] = {1., 2., 3., 4., 5.};
        CHECK( isclose(lhs,rhs) );
    }
    {
        double lhs[5] = {1., 2., 3., 4., 5.};
        double rhs[5] = {1., 2., 3., 4., 1.};
        CHECK( !isclose(lhs,rhs) );
    }
}

// should NOT COMPILE static assertion failed: unsupported isclose; only support integral element type
// TEST_CASE("isclose(double[],double[])" * doctest::test_suite("utils"))
// {
//     {
//         double lhs[5] = {1., 2., 3., 4., 5.};
//         double rhs[5] = {1., 2., 3., 4., 5.};
//         CHECK( isclose(lhs,rhs) );
//     }
//     {
//         double lhs[5] = {1., 2., 3., 4., 5.};
//         double rhs[5] = {1., 2., 3., 4., 1.};
//         CHECK( !isclose(lhs,rhs) );
//     }
// }

/**
 * @test isclose(tuple,array)
 * 
 */
TEST_CASE("isclose(tuple,array)" * doctest::test_suite("utils"))
{
    {
        auto lhs = tuple{1., 2., 3., 4., 5.};
        auto rhs = array{1., 2., 3., 4., 5.};
        CHECK( isclose(lhs,rhs) );
    }
    {
        auto lhs = tuple{1., 2., 3., 4., 5.};
        auto rhs = array{1., 2., 2., 4., 5.};
        CHECK( !isclose(lhs,rhs) );
    }
}

/**
 * @test isclose(array,tuple)
 * 
 */
TEST_CASE("isclose(array,tuple)" * doctest::test_suite("utils"))
{
    {
        auto lhs = array{1., 2., 3., 4., 5.};
        auto rhs = tuple{1., 2., 3., 4., 5.};
        CHECK( isclose(lhs,rhs) );
    }
    {
        auto lhs = array{1., 2., 3., 4., 5.};
        auto rhs = tuple{1., 2., 2., 4., 5.};
        CHECK( !isclose(lhs,rhs) );
    }
}

/**
 * @test isclose(array[2],array[2])
 * 
 */
TEST_CASE("isclose(array[2],array[2])" * doctest::test_suite("utils"))
{
    {
        auto lhs = array{
            array{1., 2., 3.},
            array{4., 5., 6.}
        };
        auto rhs = array{
            array{1., 2., 3.},
            array{4., 5., 6.}
        };
        CHECK( isclose(lhs,rhs) );
    }
    {
        auto lhs = array{
            array{1., 2., 3.},
            array{4., 5., 6.}
        };
        auto rhs = array{
            array{1., 2., 3.},
            array{4., 1., 6.}
        };
        CHECK( !isclose(lhs,rhs) );
    }
}

TEST_CASE("isclose(vector[2],vector[2])" * doctest::test_suite("utils"))
{
    {
        auto lhs = vector{
            vector{1., 2., 3.},
            vector{4., 5., 6.}
        };
        auto rhs = vector{
            vector{1., 2., 3.},
            vector{4., 5., 6.}
        };
        CHECK( isclose(lhs,rhs) );
    }
    {
        auto lhs = vector{
            vector{1., 2., 3.},
            vector{4., 5., 6.}
        };
        auto rhs = vector{
            vector{1., 2., 3.},
            vector{4., 1., 6.}
        };
        CHECK( !isclose(lhs,rhs) );
    }
}

TEST_CASE("isclose(int[][],int[][])" * doctest::test_suite("utils"))
{
    {
        double lhs[2][3] = {
            {1., 2., 3.},
            {4., 5., 6.}
        };
        double rhs[2][3] = {
            {1., 2., 3.},
            {4., 5., 6.}
        };
        CHECK( isclose(lhs,rhs) );
    }
    {
        double lhs[2][3] = {
            {1., 2., 3.},
            {4., 5., 6.}
        };
        double rhs[2][3] = {
            {1., 2., 3.},
            {4., 1., 6.}
        };
        CHECK( !isclose(lhs,rhs) );
    }
}

TEST_CASE("isclose(array[2],tuple[2])" * doctest::test_suite("utils"))
{
    {
        auto lhs = array{
            array{1., 2., 3.},
            array{4., 5., 6.}
        };
        auto rhs = tuple{
            tuple{1., 2., 3.},
            tuple{4., 5., 6.}
        };
        CHECK( isclose(lhs,rhs) );
    }
    {
        auto lhs = array{
            array{1., 2., 3.},
            array{4., 5., 6.}
        };
        auto rhs = tuple{
            tuple{1., 2., 3.},
            tuple{4., 1., 6.}
        };
        CHECK( !isclose(lhs,rhs) );
    }
}

/**
 * @brief isclose(array[3],array[3])
 * 
 */
TEST_CASE("isclose(array[3],array[3])" * doctest::test_suite("utils"))
{
    {
        auto lhs = array{
            array{
                array{1., 2., 3.},
                array{4., 5., 6.},
            },
            array{
                array{ 7.,  8.,  9.},
                array{10., 11., 12.},
            }
        };
        auto rhs = array{
            array{
                array{1., 2., 3.},
                array{4., 5., 6.}
            },
            array{
                array{ 7.,  8.,  9.},
                array{10., 11., 12.},
            }
        };
        CHECK( isclose(lhs,rhs) );
    }
    {
        auto lhs = array{
            array{
                array{1., 2., 3.},
                array{4., 5., 6.},
            },
            array{
                array{ 7.,  8.,  9.},
                array{10., 11., 12.},
            }
        };
        auto rhs = array{
            array{
                array{1., 2., 3.},
                array{4., 5., 6.}
            },
            array{
                array{ 7.,  8.,  9.},
                array{10., 11., 13.},
            }
        };
        CHECK( !isclose(lhs,rhs) );
    }
}

TEST_CASE("isclose(vector[3],vector[3])" * doctest::test_suite("utils"))
{
    {
        auto lhs = vector{
            vector{
                vector{1., 2., 3.},
                vector{4., 5., 6.},
            },
            vector{
                vector{ 7.,  8.,  9.},
                vector{10., 11., 12.},
            }
        };
        auto rhs = vector{
            vector{
                vector{1., 2., 3.},
                vector{4., 5., 6.}
            },
            vector{
                vector{ 7.,  8.,  9.},
                vector{10., 11., 12.},
            }
        };
        CHECK( isclose(lhs,rhs) );
    }
    {
        auto lhs = vector{
            vector{
                vector{1., 2., 3.},
                vector{4., 5., 6.},
            },
            vector{
                vector{ 7.,  8.,  9.},
                vector{10., 11., 12.},
            }
        };
        auto rhs = vector{
            vector{
                vector{1., 2., 3.},
                vector{4., 5., 6.}
            },
            vector{
                vector{ 7.,  8.,  9.},
                vector{10., 11., 13.},
            }
        };
        CHECK( !isclose(lhs,rhs) );
    }
}

TEST_CASE("isclose(int[][][],int[][][])" * doctest::test_suite("utils"))
{
    {
        double lhs[2][2][3] = {
            {
                {1., 2., 3.},
                {4., 5., 6.},
            },
            {
                { 7.,  8.,  9.},
                {10., 11., 12.},
            }
        };
        double rhs[2][2][3] = {
            {
                {1., 2., 3.},
                {4., 5., 6.}
            },
            {
                { 7.,  8.,  9.},
                {10., 11., 12.},
            }
        };
        CHECK( isclose(lhs,rhs) );
    }
    {
        double lhs[2][2][3] = {
            {
                {1., 2., 3.},
                {4., 5., 6.},
            },
            {
                { 7.,  8.,  9.},
                {10., 11., 12.},
            }
        };
        double rhs[2][2][3] = {
            {
                {1., 2., 3.},
                {4., 5., 6.}
            },
            {
                { 7.,  8.,  9.},
                {10., 11., 13.},
            }
        };
        CHECK( !isclose(lhs,rhs) );
    }
}

/**
 * @test isclose(array[4],array[4])
 * 
 */
TEST_CASE("isclose(array[4],array[4])" * doctest::test_suite("utils"))
{
    {
        auto lhs = array{
            array{
                array{
                    array{1., 2., 3.},
                    array{4., 5., 6.},
                },
                array{
                    array{7., 8., 9.},
                    array{9., 8., 7.},
                },
            },
            array{
                array{
                    array{ 8.,  9., 10.},
                    array{11., 12., 13.},
                },
                array{
                    array{14., 15., 16.},
                    array{17., 18., 19.},
                },
            },
        };
        auto rhs = array{
            array{
                array{
                    array{1., 2., 3.},
                    array{4., 5., 6.},
                },
                array{
                    array{7., 8., 9.},
                    array{9., 8., 7.},
                },
            },
            array{
                array{
                    array{ 8.,  9., 10.},
                    array{11., 12., 13.},
                },
                array{
                    array{14., 15., 16.},
                    array{17., 18., 19.},
                },
            },
        };
        CHECK( isclose(lhs,rhs) );
    }
    {
        auto lhs = array{
            array{
                array{
                    array{1., 2., 3.},
                    array{4., 5., 6.},
                },
                array{
                    array{7., 8., 9.},
                    array{9., 8., 7.},
                },
            },
            array{
                array{
                    array{ 8.,  9., 10.},
                    array{11., 12., 13.},
                },
                array{
                    array{14., 15., 16.},
                    array{17., 18., 19.},
                },
            },
        };
        auto rhs = array{
            array{
                array{
                    array{1., 2., 3.},
                    array{4., 5., 6.},
                },
                array{
                    array{7., 8., 9.},
                    array{9., 8., 7.},
                },
            },
            array{
                array{
                    array{ 8.,  9., 10.},
                    array{11., 12., 13.},
                },
                array{
                    array{14., 15., 16.},
                    array{18., 18., 19.},
                },
            },
        };
        CHECK( !isclose(lhs,rhs) );
    }
}

TEST_CASE("isclose(vector[4],vector[4])" * doctest::test_suite("utils"))
{
    {
        auto lhs = vector{
            vector{
                vector{
                    vector{1., 2., 3.},
                    vector{4., 5., 6.},
                },
                vector{
                    vector{7., 8., 9.},
                    vector{9., 8., 7.},
                },
            },
            vector{
                vector{
                    vector{ 8.,  9., 10.},
                    vector{11., 12., 13.},
                },
                vector{
                    vector{14., 15., 16.},
                    vector{17., 18., 19.},
                },
            },
        };
        auto rhs = vector{
            vector{
                vector{
                    vector{1., 2., 3.},
                    vector{4., 5., 6.},
                },
                vector{
                    vector{7., 8., 9.},
                    vector{9., 8., 7.},
                },
            },
            vector{
                vector{
                    vector{ 8.,  9., 10.},
                    vector{11., 12., 13.},
                },
                vector{
                    vector{14., 15., 16.},
                    vector{17., 18., 19.},
                },
            },
        };
        CHECK( isclose(lhs,rhs) );
    }
    {
        auto lhs = vector{
            vector{
                vector{
                    vector{1., 2., 3.},
                    vector{4., 5., 6.},
                },
                vector{
                    vector{7., 8., 9.},
                    vector{9., 8., 7.},
                },
            },
            vector{
                vector{
                    vector{ 8.,  9., 10.},
                    vector{11., 12., 13.},
                },
                vector{
                    vector{14., 15., 16.},
                    vector{17., 18., 19.},
                },
            },
        };
        auto rhs = vector{
            vector{
                vector{
                    vector{1., 2., 3.},
                    vector{4., 5., 6.},
                },
                vector{
                    vector{7., 8., 9.},
                    vector{9., 8., 7.},
                },
            },
            vector{
                vector{
                    vector{ 8.,  9., 10.},
                    vector{11., 12., 13.},
                },
                vector{
                    vector{14., 15., 16.},
                    vector{18., 18., 19.},
                },
            },
        };
        CHECK( !isclose(lhs,rhs) );
    }
}

TEST_CASE("isclose(int[][][][],int[][][][])" * doctest::test_suite("utils"))
{
    {
        double lhs[2][2][2][3] = {
            {
                {
                    {1., 2., 3.},
                    {4., 5., 6.},
                },
                {
                    {7., 8., 9.},
                    {9., 8., 7.},
                },
            },
            {
                {
                    { 8.,  9., 10.},
                    {11., 12., 13.},
                },
                {
                    {14., 15., 16.},
                    {17., 18., 19.},
                },
            },
        };
        double rhs[2][2][2][3] = {
            {
                {
                    {1., 2., 3.},
                    {4., 5., 6.},
                },
                {
                    {7., 8., 9.},
                    {9., 8., 7.},
                },
            },
            {
                {
                    { 8.,  9., 10.},
                    {11., 12., 13.},
                },
                {
                    {14., 15., 16.},
                    {17., 18., 19.},
                },
            },
        };
        CHECK( isclose(lhs,rhs) );
    }
    {
        double lhs[2][2][2][3] = {
            {
                {
                    {1., 2., 3.},
                    {4., 5., 6.},
                },
                {
                    {7., 8., 9.},
                    {9., 8., 7.},
                },
            },
            {
                {
                    { 8.,  9., 10.},
                    {11., 12., 13.},
                },
                {
                    {14., 15., 16.},
                    {17., 18., 19.},
                },
            },
        };
        double rhs[2][2][2][3] = {
            {
                {
                    {1., 2., 3.},
                    {4., 5., 6.},
                },
                {
                    {7., 8., 9.},
                    {9., 8., 7.},
                },
            },
            {
                {
                    { 8.,  9., 10.},
                    {11., 12., 13.},
                },
                {
                    {14., 15., 16.},
                    {18., 18., 19.},
                },
            },
        };
        CHECK( !isclose(lhs,rhs) );
    }
}

// should NOT COMPILE static assertion failed: unsupported isclose, mismatched size for packed type
// TEST_CASE("isclose(array[2],array[2])" * doctest::test_suite("utils"))
// {
//     {
//         auto lhs = array{
//             array{
//                 array{1., 2., 3.},
//                 array{4., 5., 6.},
//             },
//             array{
//                 array{ 7.,  8.,  9.},
//                 array{10., 11., 12.},
//             }
//         };
//         auto rhs = array{
//             array{
//                 array{1, 2, 3, 10},
//                 array{4, 5, 6, 10}
//             },
//             array{
//                 array{ 7,  8,  9, 10},
//                 array{10, 11, 12, 10},
//             }
//         };
//         CHECK( isclose(lhs,rhs) );
//     }
// }

// should NOT COMPILE static assertion failed: unsupported isclose, mismatched size for packed type
// TEST_CASE("isclose(array[2],tuple[2])" * doctest::test_suite("utils"))
// {
//     {
//         auto lhs = array{
//             array{1., 2., 3.},
//             array{4., 5., 6.}
//         };
//         auto rhs = tuple{
//             tuple{1., 2., 3.},
//             tuple{4, 5, 6, 1}
//         };
//         CHECK( isclose(lhs,rhs) );
//     }
// }

// should NOT COMPILE:
// multiple static assert fails, the first one is
// static assertion failed: unsupported isclose, mismatched size for packed type
// TEST_CASE("isclose(array[2],array[2])" * doctest::test_suite("utils"))
// {
//     {
//         auto lhs = array{
//             array{1., 2., 3.},
//             array{4., 5., 6.}
//         };
//         auto rhs = array{
//             array{1., 2., 3.},
//         };
//         CHECK( !isclose(lhs,rhs) );
//     }
// }

// should NOT COMPILE static assertion failed: unsupported isclose, mismatched size for packed type
// TEST_CASE("isclose(array,tuple)" * doctest::test_suite("utils"))
// {
//     {
//         auto lhs = array{1., 2., 3., 4., 5.};
//         auto rhs = tuple{1, 2, 3, 4, 5, 6};
//         CHECK( isclose(lhs,rhs) );
//     }
//     {
//         auto lhs = array{1., 2., 3., 4., 5.};
//         auto rhs = tuple{1, 2, 2, 4, 5, 6};
//         CHECK( !isclose(lhs,rhs) );
//     }
// }