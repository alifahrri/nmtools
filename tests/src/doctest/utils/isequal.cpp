#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/utils/isequal.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>
#include <variant>
#include <optional>

using std::vector;
using std::array;
using std::tuple;
using nmtools::array::fixed_ndarray;
using nmtools::array::fixed_vector;
using nmtools::array::fixed_matrix;
using nmtools::array::dynamic_ndarray;
using nmtools::array::dynamic_vector;
using nmtools::array::dynamic_matrix;
using nmtools::utils::isequal;

/**
 * @test isequal(tuple,tuple)
 * 
 */
TEST_CASE("isequal(tuple,tuple)" * doctest::test_suite("utils"))
{
    {
        auto lhs = tuple{1, 2, 3, 4, 5};
        auto rhs = tuple{1, 2, 3, 4, 5};
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = tuple{1, 2, 3, 4, 5};
        auto rhs = tuple{1, 2, 3, 4, 1};
        CHECK( !isequal(lhs,rhs) );
    }
}

/**
 * @test isequal(array,array)
 * 
 */
TEST_CASE("isequal(array,array)" * doctest::test_suite("utils"))
{
    {
        auto lhs = array{1, 2, 3, 4, 5};
        auto rhs = array{1, 2, 3, 4, 5};
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = array{1, 2, 3, 4, 5};
        auto rhs = array{1, 2, 2, 4, 5};
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(vector,vector)" * doctest::test_suite("utils"))
{
    {
        auto lhs = vector{1, 2, 3, 4, 5};
        auto rhs = vector{1, 2, 3, 4, 5};
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = vector{1, 2, 3, 4, 5};
        auto rhs = vector{1, 2, 3, 4, 1};
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(int[],int[])" * doctest::test_suite("utils"))
{
    {
        int lhs[5] = {1, 2, 3, 4, 5};
        int rhs[5] = {1, 2, 3, 4, 5};
        CHECK( isequal(lhs,rhs) );
    }
    {
        int lhs[5] = {1, 2, 3, 4, 5};
        int rhs[5] = {1, 2, 3, 4, 1};
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(fixed_vector,fixed_vector)" * doctest::test_suite("utils"))
{
    {
        auto lhs = fixed_vector({1, 2, 3, 4, 5});
        auto rhs = fixed_vector({1, 2, 3, 4, 5});
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = fixed_vector({1, 2, 3, 4, 5});
        auto rhs = fixed_vector({1, 2, 3, 4, 1});
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(dynamic_vector,dynamic_vector)" * doctest::test_suite("utils"))
{
    {
        auto lhs = dynamic_vector{1, 2, 3, 4, 5};
        auto rhs = dynamic_vector{1, 2, 3, 4, 5};
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = dynamic_vector{1, 2, 3, 4, 5};
        auto rhs = dynamic_vector{1, 2, 3, 4, 1};
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(fixed_ndarray,fixed_ndarray)" * doctest::test_suite("utils"))
{
    {
        auto lhs = fixed_ndarray<int,5>{};
        auto rhs = fixed_ndarray<int,5>{};
        lhs = {1, 2, 3, 4, 5};
        rhs = {1, 2, 3, 4, 5};
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = fixed_ndarray<int,5>{};
        auto rhs = fixed_ndarray<int,5>{};
        lhs = {1, 2, 3, 4, 5};
        rhs = {1, 2, 3, 4, 1};
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(dynamic_ndarray,dynamic_ndarray)" * doctest::test_suite("utils"))
{
    {
        auto lhs = dynamic_ndarray<int>({1, 2, 3, 4, 5});
        auto rhs = dynamic_ndarray<int>({1, 2, 3, 4, 5});
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = dynamic_ndarray<int>({1, 2, 3, 4, 5});
        auto rhs = dynamic_ndarray<int>({1, 2, 3, 4, 1});
        CHECK( !isequal(lhs,rhs) );
    }
}

// should NOT COMPILE static assertion failed: unsupported isequal; only support integral element type
// TEST_CASE("isequal(double[],double[])" * doctest::test_suite("utils"))
// {
//     {
//         double lhs[5] = {1, 2, 3, 4, 5};
//         double rhs[5] = {1, 2, 3, 4, 5};
//         CHECK( isequal(lhs,rhs) );
//     }
//     {
//         double lhs[5] = {1, 2, 3, 4, 5};
//         double rhs[5] = {1, 2, 3, 4, 1};
//         CHECK( !isequal(lhs,rhs) );
//     }
// }

/**
 * @test isequal(tuple,array)
 * 
 */
TEST_CASE("isequal(tuple,array)" * doctest::test_suite("utils"))
{
    {
        auto lhs = tuple{1, 2, 3, 4, 5};
        auto rhs = array{1, 2, 3, 4, 5};
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = tuple{1, 2, 3, 4, 5};
        auto rhs = array{1, 2, 2, 4, 5};
        CHECK( !isequal(lhs,rhs) );
    }
}

/**
 * @test isequal(array,tuple)
 * 
 */
TEST_CASE("isequal(array,tuple)" * doctest::test_suite("utils"))
{
    {
        auto lhs = array{1, 2, 3, 4, 5};
        auto rhs = tuple{1, 2, 3, 4, 5};
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = array{1, 2, 3, 4, 5};
        auto rhs = tuple{1, 2, 2, 4, 5};
        CHECK( !isequal(lhs,rhs) );
    }
}

/**
 * @test isequal(array[2],array[2])
 * 
 */
TEST_CASE("isequal(array[2],array[2])" * doctest::test_suite("utils"))
{
    {
        auto lhs = array{
            array{1, 2, 3},
            array{4, 5, 6}
        };
        auto rhs = array{
            array{1, 2, 3},
            array{4, 5, 6}
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = array{
            array{1, 2, 3},
            array{4, 5, 6}
        };
        auto rhs = array{
            array{1, 2, 3},
            array{4, 1, 6}
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(vector[2],vector[2])" * doctest::test_suite("utils"))
{
    {
        auto lhs = vector{
            vector{1, 2, 3},
            vector{4, 5, 6}
        };
        auto rhs = vector{
            vector{1, 2, 3},
            vector{4, 5, 6}
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = vector{
            vector{1, 2, 3},
            vector{4, 5, 6}
        };
        auto rhs = vector{
            vector{1, 2, 3},
            vector{4, 1, 6}
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(int[][],int[][])" * doctest::test_suite("utils"))
{
    {
        int lhs[2][3] = {
            {1, 2, 3},
            {4, 5, 6}
        };
        int rhs[2][3] = {
            {1, 2, 3},
            {4, 5, 6}
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        int lhs[2][3] = {
            {1, 2, 3},
            {4, 5, 6}
        };
        int rhs[2][3] = {
            {1, 2, 3},
            {4, 1, 6}
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(array[2],tuple[2])" * doctest::test_suite("utils"))
{
    {
        auto lhs = array{
            array{1, 2, 3},
            array{4, 5, 6}
        };
        auto rhs = tuple{
            tuple{1, 2, 3},
            tuple{4, 5, 6}
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = array{
            array{1, 2, 3},
            array{4, 5, 6}
        };
        auto rhs = tuple{
            tuple{1, 2, 3},
            tuple{4, 1, 6}
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(fixed_ndarray[2],fixed_ndarray[2])" * doctest::test_suite("utils"))
{
    {
        auto lhs = fixed_ndarray<int,2,3>{};
        auto rhs = fixed_ndarray<int,2,3>{};
        lhs = {
            {1, 2, 3},
            {4, 5, 6}
        };
        rhs = {
            {1, 2, 3},
            {4, 5, 6}
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = fixed_ndarray<int,2,3>{};
        auto rhs = fixed_ndarray<int,2,3>{};
        lhs = {
            {1, 2, 3},
            {4, 5, 6}
        };
        rhs = {
            {1, 2, 3},
            {4, 1, 6}
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(fixed_matrix,fixed_matrix)" * doctest::test_suite("utils"))
{
    {
        auto lhs = fixed_matrix<int,2,3>{};
        auto rhs = fixed_matrix<int,2,3>{};
        lhs = {
            {1, 2, 3},
            {4, 5, 6}
        };
        rhs = {
            {1, 2, 3},
            {4, 5, 6}
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = fixed_matrix<int,2,3>{};
        auto rhs = fixed_matrix<int,2,3>{};
        lhs = {
            {1, 2, 3},
            {4, 5, 6}
        };
        rhs = {
            {1, 2, 3},
            {4, 1, 6}
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(dynamic_matrix,dynamic_matrix)" * doctest::test_suite("utils"))
{
    {
        auto lhs = dynamic_matrix{
            {1, 2, 3},
            {4, 5, 6}
        };
        auto rhs = dynamic_matrix{
            {1, 2, 3},
            {4, 5, 6}
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = dynamic_matrix{
            {1, 2, 3},
            {4, 5, 6}
        };
        auto rhs = dynamic_matrix{
            {1, 2, 3},
            {4, 1, 6}
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

/**
 * @brief isequal(array[3],array[3])
 * 
 */
TEST_CASE("isequal(array[3],array[3])" * doctest::test_suite("utils"))
{
    {
        auto lhs = array{
            array{
                array{1, 2, 3},
                array{4, 5, 6},
            },
            array{
                array{ 7,  8,  9},
                array{10, 11, 12},
            }
        };
        auto rhs = array{
            array{
                array{1, 2, 3},
                array{4, 5, 6}
            },
            array{
                array{ 7,  8,  9},
                array{10, 11, 12},
            }
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = array{
            array{
                array{1, 2, 3},
                array{4, 5, 6},
            },
            array{
                array{7,   8,  9},
                array{10, 11, 12},
            }
        };
        auto rhs = array{
            array{
                array{1, 2, 3},
                array{4, 5, 6}
            },
            array{
                array{ 7,  8,  9},
                array{10, 11, 13},
            }
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(vector[3],vector[3])" * doctest::test_suite("utils"))
{
    {
        auto lhs = vector{
            vector{
                vector{1, 2, 3},
                vector{4, 5, 6},
            },
            vector{
                vector{ 7,  8,  9},
                vector{10, 11, 12},
            }
        };
        auto rhs = vector{
            vector{
                vector{1, 2, 3},
                vector{4, 5, 6}
            },
            vector{
                vector{ 7,  8,  9},
                vector{10, 11, 12},
            }
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = vector{
            vector{
                vector{1, 2, 3},
                vector{4, 5, 6},
            },
            vector{
                vector{7,   8,  9},
                vector{10, 11, 12},
            }
        };
        auto rhs = vector{
            vector{
                vector{1, 2, 3},
                vector{4, 5, 6}
            },
            vector{
                vector{ 7,  8,  9},
                vector{10, 11, 13},
            }
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(int[][][],int[][][])" * doctest::test_suite("utils"))
{
    {
        int lhs[2][2][3] = {
            {
                {1, 2, 3},
                {4, 5, 6},
            },
            {
                { 7,  8,  9},
                {10, 11, 12},
            }
        };
        int rhs[2][2][3] = {
            {
                {1, 2, 3},
                {4, 5, 6}
            },
            {
                { 7,  8,  9},
                {10, 11, 12},
            }
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        int lhs[2][2][3] = {
            {
                {1, 2, 3},
                {4, 5, 6},
            },
            {
                {7,   8,  9},
                {10, 11, 12},
            }
        };
        int rhs[2][2][3] = {
            {
                {1, 2, 3},
                {4, 5, 6}
            },
            {
                { 7,  8,  9},
                {10, 11, 13},
            }
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(fixed_ndarray[3],fixed_ndarray[3])" * doctest::test_suite("utils"))
{
    {
        auto lhs = fixed_ndarray<int,2,2,3>{};
        auto rhs = fixed_ndarray<int,2,2,3>{};
        lhs = {
            {
                {1, 2, 3},
                {4, 5, 6},
            },
            {
                { 7,  8,  9},
                {10, 11, 12},
            }
        };
        rhs = {
            {
                {1, 2, 3},
                {4, 5, 6}
            },
            {
                { 7,  8,  9},
                {10, 11, 12},
            }
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = fixed_ndarray<int,2,2,3>{};
        auto rhs = fixed_ndarray<int,2,2,3>{};
        lhs = {
            {
                {1, 2, 3},
                {4, 5, 6},
            },
            {
                {7,   8,  9},
                {10, 11, 12},
            }
        };
        rhs = {
            {
                {1, 2, 3},
                {4, 5, 6}
            },
            {
                { 7,  8,  9},
                {10, 11, 13},
            }
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

/**
 * @test isequal(array[4],array[4])
 * 
 */
TEST_CASE("isequal(array[4],array[4])" * doctest::test_suite("utils"))
{
    {
        auto lhs = array{
            array{
                array{
                    array{1, 2, 3},
                    array{4, 5, 6},
                },
                array{
                    array{7, 8, 9},
                    array{9, 8, 7},
                },
            },
            array{
                array{
                    array{ 8,  9, 10},
                    array{11, 12, 13},
                },
                array{
                    array{14, 15, 16},
                    array{17, 18, 19},
                },
            },
        };
        auto rhs = array{
            array{
                array{
                    array{1, 2, 3},
                    array{4, 5, 6},
                },
                array{
                    array{7, 8, 9},
                    array{9, 8, 7},
                },
            },
            array{
                array{
                    array{ 8,  9, 10},
                    array{11, 12, 13},
                },
                array{
                    array{14, 15, 16},
                    array{17, 18, 19},
                },
            },
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = array{
            array{
                array{
                    array{1, 2, 3},
                    array{4, 5, 6},
                },
                array{
                    array{7, 8, 9},
                    array{9, 8, 7},
                },
            },
            array{
                array{
                    array{ 8,  9, 10},
                    array{11, 12, 13},
                },
                array{
                    array{14, 15, 16},
                    array{17, 18, 19},
                },
            },
        };
        auto rhs = array{
            array{
                array{
                    array{1, 2, 3},
                    array{4, 5, 6},
                },
                array{
                    array{7, 8, 9},
                    array{9, 8, 7},
                },
            },
            array{
                array{
                    array{ 8,  9, 10},
                    array{11, 12, 13},
                },
                array{
                    array{14, 15, 16},
                    array{18, 18, 19},
                },
            },
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(vector[4],vector[4])" * doctest::test_suite("utils"))
{
    {
        auto lhs = vector{
            vector{
                vector{
                    vector{1, 2, 3},
                    vector{4, 5, 6},
                },
                vector{
                    vector{7, 8, 9},
                    vector{9, 8, 7},
                },
            },
            vector{
                vector{
                    vector{ 8,  9, 10},
                    vector{11, 12, 13},
                },
                vector{
                    vector{14, 15, 16},
                    vector{17, 18, 19},
                },
            },
        };
        auto rhs = vector{
            vector{
                vector{
                    vector{1, 2, 3},
                    vector{4, 5, 6},
                },
                vector{
                    vector{7, 8, 9},
                    vector{9, 8, 7},
                },
            },
            vector{
                vector{
                    vector{ 8,  9, 10},
                    vector{11, 12, 13},
                },
                vector{
                    vector{14, 15, 16},
                    vector{17, 18, 19},
                },
            },
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = vector{
            vector{
                vector{
                    vector{1, 2, 3},
                    vector{4, 5, 6},
                },
                vector{
                    vector{7, 8, 9},
                    vector{9, 8, 7},
                },
            },
            vector{
                vector{
                    vector{ 8,  9, 10},
                    vector{11, 12, 13},
                },
                vector{
                    vector{14, 15, 16},
                    vector{17, 18, 19},
                },
            },
        };
        auto rhs = vector{
            vector{
                vector{
                    vector{1, 2, 3},
                    vector{4, 5, 6},
                },
                vector{
                    vector{7, 8, 9},
                    vector{9, 8, 7},
                },
            },
            vector{
                vector{
                    vector{ 8,  9, 10},
                    vector{11, 12, 13},
                },
                vector{
                    vector{14, 15, 16},
                    vector{18, 18, 19},
                },
            },
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(int[][][][],int[][][][])" * doctest::test_suite("utils"))
{
    {
        int lhs[2][2][2][3] = {
            {
                {
                    {1, 2, 3},
                    {4, 5, 6},
                },
                {
                    {7, 8, 9},
                    {9, 8, 7},
                },
            },
            {
                {
                    { 8,  9, 10},
                    {11, 12, 13},
                },
                {
                    {14, 15, 16},
                    {17, 18, 19},
                },
            },
        };
        int rhs[2][2][2][3] = {
            {
                {
                    {1, 2, 3},
                    {4, 5, 6},
                },
                {
                    {7, 8, 9},
                    {9, 8, 7},
                },
            },
            {
                {
                    { 8,  9, 10},
                    {11, 12, 13},
                },
                {
                    {14, 15, 16},
                    {17, 18, 19},
                },
            },
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        int lhs[2][2][2][3] = {
            {
                {
                    {1, 2, 3},
                    {4, 5, 6},
                },
                {
                    {7, 8, 9},
                    {9, 8, 7},
                },
            },
            {
                {
                    { 8,  9, 10},
                    {11, 12, 13},
                },
                {
                    {14, 15, 16},
                    {17, 18, 19},
                },
            },
        };
        int rhs[2][2][2][3] = {
            {
                {
                    {1, 2, 3},
                    {4, 5, 6},
                },
                {
                    {7, 8, 9},
                    {9, 8, 7},
                },
            },
            {
                {
                    { 8,  9, 10},
                    {11, 12, 13},
                },
                {
                    {14, 15, 16},
                    {18, 18, 19},
                },
            },
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(fixed_ndarray[4],fixed_ndarray[4])" * doctest::test_suite("utils"))
{
    {
        auto lhs = fixed_ndarray<int,2,2,2,3>{};
        auto rhs = fixed_ndarray<int,2,2,2,3>{};
        lhs = {
            {
                {
                    {1, 2, 3},
                    {4, 5, 6},
                },
                {
                    {7, 8, 9},
                    {9, 8, 7},
                },
            },
            {
                {
                    { 8,  9, 10},
                    {11, 12, 13},
                },
                {
                    {14, 15, 16},
                    {17, 18, 19},
                },
            },
        };
        rhs = {
            {
                {
                    {1, 2, 3},
                    {4, 5, 6},
                },
                {
                    {7, 8, 9},
                    {9, 8, 7},
                },
            },
            {
                {
                    { 8,  9, 10},
                    {11, 12, 13},
                },
                {
                    {14, 15, 16},
                    {17, 18, 19},
                },
            },
        };
        CHECK( isequal(lhs,rhs) );
    }
    {
        auto lhs = fixed_ndarray<int,2,2,2,3>{};
        auto rhs = fixed_ndarray<int,2,2,2,3>{};
        lhs = {
            {
                {
                    {1, 2, 3},
                    {4, 5, 6},
                },
                {
                    {7, 8, 9},
                    {9, 8, 7},
                },
            },
            {
                {
                    { 8,  9, 10},
                    {11, 12, 13},
                },
                {
                    {14, 15, 16},
                    {17, 18, 19},
                },
            },
        };
        rhs = {
            {
                {
                    {1, 2, 3},
                    {4, 5, 6},
                },
                {
                    {7, 8, 9},
                    {9, 8, 7},
                },
            },
            {
                {
                    { 8,  9, 10},
                    {11, 12, 13},
                },
                {
                    {14, 15, 16},
                    {18, 18, 19},
                },
            },
        };
        CHECK( !isequal(lhs,rhs) );
    }
}

TEST_CASE("isequal(variant)" * doctest::test_suite("isequal"))
{
    {
        using lhs_t = std::variant<nmtools::none_t,int>;
        using rhs_t = std::variant<nmtools::none_t,int>;
        CHECK(  isequal(lhs_t{nmtools::None},rhs_t{nmtools::None}) );
        CHECK( !isequal(lhs_t{nmtools::None},rhs_t{1}) );
        CHECK( !isequal(lhs_t{1},rhs_t{nmtools::None}) );
        CHECK(  isequal(lhs_t{1},rhs_t{1}) );
    }
    {
        using lhs_t = std::variant<nmtools::none_t,std::array<long int,3>>;
        using rhs_t = std::variant<nmtools::none_t,std::vector<long int>>;
        CHECK((  isequal(lhs_t{nmtools::None},rhs_t{nmtools::None}) ));
        CHECK(( !isequal(lhs_t{nmtools::None},rhs_t{std::vector{1l,2l,3l}}) ));
        CHECK(( !isequal(lhs_t{std::array{1l,2l,3l}},rhs_t{nmtools::None}) ));
        CHECK((  isequal(lhs_t{std::array{1l,2l,3l}},rhs_t{std::vector{1l,2l,3l}}) ));
    }
    {
        using lhs_t = std::variant<nmtools::none_t,std::array<long int,3>>;
        using rhs_t = std::vector<long int>;
        auto rhs = rhs_t{1l,2l,3l};
        CHECK(( !isequal(lhs_t{nmtools::None},rhs) ));
        CHECK((  isequal(lhs_t{std::array{1l,2l,3l}},rhs) ));
    }
    {
        using lhs_t = std::vector<long int>;
        using rhs_t = std::variant<nmtools::none_t,std::array<long int,3>>;
        auto lhs = lhs_t{1l,2l,3l};
        CHECK(( !isequal(lhs,rhs_t{nmtools::None}) ));
        CHECK((  isequal(lhs,rhs_t{std::array{1l,2l,3l}}) ));
    }
}

TEST_CASE("isequal(optional)" * doctest::test_suite("isequal"))
{
    SUBCASE("int")
    {
        using lhs_t = std::optional<int>;
        using rhs_t = std::optional<int>;
        CHECK(  isequal(lhs_t{0},rhs_t{0}) );
        CHECK(  isequal(lhs_t{std::nullopt},rhs_t{std::nullopt}));
        CHECK( !isequal(lhs_t{std::nullopt},rhs_t{0}));
        CHECK( !isequal(lhs_t{0},rhs_t{std::nullopt}));
    }
    SUBCASE("array")
    {
        using array_t = std::array<int,3>;
        using vector_t = std::vector<int>;
        using lhs_t = std::optional<array_t>;
        using rhs_t = std::optional<vector_t>;
        CHECK(  isequal(lhs_t{array_t{1,2,3}},rhs_t{vector_t{1,2,3}}) );
        CHECK(  isequal(lhs_t{std::nullopt},rhs_t{std::nullopt}) );
        CHECK( !isequal(lhs_t{array_t{1,2,3}},rhs_t{std::nullopt}) );
        CHECK( !isequal(lhs_t{std::nullopt},rhs_t{vector_t{1,2,3}}) );
    }
}

TEST_CASE("isequal(integral_constant)" * doctest::test_suite("isequal"))
{
    using namespace nmtools::literals;
    SUBCASE("ct")
    {
        auto lhs = 1_ct;
        auto rhs = 1;
        CHECK( isequal(lhs,rhs) );
    }
    SUBCASE("tuple(ct)")
    {
        {
            auto lhs = std::tuple{1_ct};
            auto rhs = std::array{1};
            CHECK( isequal(lhs,rhs) );
        }
        {
            auto lhs = std::tuple{1_ct};
            auto rhs = std::vector{1};
            CHECK( isequal(lhs,rhs) );
        }
    }
}

// should NOT COMPILE static assertion failed: unsupported isequal, mismatched size for packed type
// TEST_CASE("isequal(array[2],array[2])" * doctest::test_suite("utils"))
// {
//     {
//         auto lhs = array{
//             array{
//                 array{1, 2, 3},
//                 array{4, 5, 6},
//             },
//             array{
//                 array{ 7,  8,  9},
//                 array{10, 11, 12},
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
//         CHECK( isequal(lhs,rhs) );
//     }
// }

// should NOT COMPILE static assertion failed: unsupported isequal, mismatched size for packed type
// TEST_CASE("isequal(array[2],tuple[2])" * doctest::test_suite("utils"))
// {
//     {
//         auto lhs = array{
//             array{1, 2, 3},
//             array{4, 5, 6}
//         };
//         auto rhs = tuple{
//             tuple{1, 2, 3},
//             tuple{4, 5, 6, 1}
//         };
//         CHECK( isequal(lhs,rhs) );
//     }
// }

// should NOT COMPILE:
// multiple static assert fails, the first one is
// static assertion failed: unsupported isequal, mismatched size for packed type
// TEST_CASE("isequal(array[2],array[2])" * doctest::test_suite("utils"))
// {
//     {
//         auto lhs = array{
//             array{1, 2, 3},
//             array{4, 5, 6}
//         };
//         auto rhs = array{
//             array{1, 2, 3},
//         };
//         CHECK( !isequal(lhs,rhs) );
//     }
// }

// should NOT COMPILE static assertion failed: unsupported isequal, mismatched size for packed type
// TEST_CASE("isequal(array,tuple)" * doctest::test_suite("utils"))
// {
//     {
//         auto lhs = array{1, 2, 3, 4, 5};
//         auto rhs = tuple{1, 2, 3, 4, 5, 6};
//         CHECK( isequal(lhs,rhs) );
//     }
//     {
//         auto lhs = array{1, 2, 3, 4, 5};
//         auto rhs = tuple{1, 2, 2, 4, 5, 6};
//         CHECK( !isequal(lhs,rhs) );
//     }
// }