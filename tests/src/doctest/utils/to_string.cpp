#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/utils/to_string.hpp"
#include "nmtools/testing/doctest.hpp"
#include <array>
#include <tuple>
#include <vector>

using std::vector;
using std::array;
using std::tuple;

namespace na = nmtools::array;
using nmtools::array::fixed_ndarray;
using nmtools::array::dynamic_ndarray;
using nmtools::utils::to_string;

// doctest MESSAGE macro doesnt work with emscripten
#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__) && !defined(__arm__) && !defined(__MINGW32__)
#undef MESSAGE
#define MESSAGE(...) {}
#endif

TEST_CASE("to_string(double[1])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        double arg[1] = {1.};
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(double[1][1])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        double arg[1][1] = {{1.}};
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(double[1][1][1])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        double arg[1][1][1] = {{{1.}}};
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(double[1][1][1][1])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        double arg[1][1][1][1] = {{{{1.}}}};
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

/**
 * @test to_string(tuple)
 * 
 */
TEST_CASE("to_string(tuple)" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        auto arg = tuple{1., 2., 3., 4., 5.};
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

/**
 * @test to_string(array)
 * 
 */
TEST_CASE("to_string(array)" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        auto arg = array{1., 2., 3., 4., 5.};
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(vector)" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        auto arg = vector{1., 2., 3., 4., 5.};
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(double[5])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        double arg[5] = {1., 2., 3., 4., 5.};
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

/**
 * @test to_string(tuple[2])
 * 
 */
TEST_CASE("to_string(tuple[2])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        auto arg = tuple{
            tuple{1., 2., 3.},
            tuple{4., 5., 6.}
        };
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

/**
 * @test to_string(array[2])
 * 
 */
TEST_CASE("to_string(array[2])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        auto arg = array{
            array{1., 2., 3.},
            array{4., 5., 6.}
        };
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(vector[2])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        auto arg = vector{
            vector{1., 2., 3.},
            vector{4., 5., 6.}
        };
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(double[2][3])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        double arg[2][3] = {
            {1., 2., 3.},
            {4., 5., 6.}
        };
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

/**
 * @brief to_string(tuple[3])
 * 
 */
TEST_CASE("to_string(tuple[3])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        auto arg = tuple{
            tuple{
                tuple{1., 2., 3.},
                tuple{4., 5., 6.},
            },
            tuple{
                tuple{ 7.,  8.,  9.},
                tuple{10., 11., 12.},
            }
        };
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

/**
 * @brief to_string(array[3])
 * 
 */
TEST_CASE("to_string(array[3])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        auto arg = array{
            array{
                array{1., 2., 3.},
                array{4., 5., 6.},
            },
            array{
                array{ 7.,  8.,  9.},
                array{10., 11., 12.},
            }
        };
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(vector[3])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        auto arg = vector{
            vector{
                vector{1., 2., 3.},
                vector{4., 5., 6.},
            },
            vector{
                vector{ 7.,  8.,  9.},
                vector{10., 11., 12.},
            }
        };
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(double[2][2][3])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        double arg[2][2][3] = {
            {
                {1., 2., 3.},
                {4., 5., 6.},
            },
            {
                { 7.,  8.,  9.},
                {10., 11., 12.},
            }
        };
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(fixed_ndarray[3])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        auto arg = na::fixed_ndarray<double,2,2,3>{};
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

/**
 * @test to_string(array[4],array[4])
 * 
 */
TEST_CASE("to_string(array[4])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        auto arg = array{
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
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(vector[4])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        auto arg = vector{
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
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(double[2][2][2][3])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        double arg[2][2][2][3] = {
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
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(fixed_ndarray[4])" * doctest::test_suite("utils") * doctest::skip(true))
{
    {
        auto arg = na::fixed_ndarray<double,2,2,2,3>{};
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(variant)" * doctest::test_suite("utils") * doctest::skip(true))
{
    SUBCASE("None")
    {
        using arg_t = std::variant<nmtools::none_t,std::array<size_t,3>>;
        auto arg = arg_t{nmtools::None};
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
    SUBCASE("array")
    {
        using arg_t = std::variant<nmtools::none_t,std::array<size_t,3>>;
        auto arg = arg_t{std::array<size_t,3>{1ul,2ul,3ul}};
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

TEST_CASE("to_string(optional)" * doctest::test_suite("utils") * doctest::skip(true))
{
    using arg_t = std::optional<std::array<size_t,3>>;
    SUBCASE("nullopt")
    {
        auto arg = std::nullopt;
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( !str.size() );
    }
    SUBCASE("array")
    {
        auto arg = std::array<size_t,3>{1ul,2ul,3ul};
        auto str = to_string(arg);
        auto to_print = std::string("\n") + str;
        MESSAGE( to_print );
        CHECK( str.size() );
    }
}

// @note not yet supported
// TEST_CASE("to_string(dynamic_ndarray[4])" * doctest::test_suite("utils") * doctest::skip(true))
// {
//     {
//         auto arg = na::dynamic_ndarray<double>(std::vector{2ul,2ul,2ul,3ul});
//         auto str = to_string(arg);
//         auto to_print = std::string("\n") + str;
//         MESSAGE( to_print );
//         CHECK( str.size() );
//     }
// }