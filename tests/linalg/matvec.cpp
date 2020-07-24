#include "nmtools/linalg/matvec.hpp"
#include "nmtools/utility/helper.hpp"
#include <gtest/gtest.h>
#include <array>
#include <vector>

namespace nmt = nmtools;
namespace nla = nmt::linalg;

using std::array;
using std::vector;

using nmt::helper::isclose;

TEST(linalg, zeros_like)
{
    auto a = array<double,3>{ 1, 2, 3 };
    auto v = vector<double>{ 1, 2, 3 };
    constexpr double r[3] = { 1, 2, 3, };
    auto ma = array<array<double,3>,3> {
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
    };
    auto mv = vector<vector<double>> {
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
    };
    constexpr double mr[3][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
    };
    /* test for vector with array container at runtime */
    {
        auto zero = array<double,3>{ 0, 0, 0 };
        auto z = nla::zeros_like(a);
        EXPECT_TRUE(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for vector with array container at compile-time */
    {
        constexpr auto zero = array<double,3>{ 0, 0, 0 };
        constexpr auto z = nla::zeros_like(a);
        static_assert(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for vector with vector container at runtime */
    {
        auto zero = vector<double>{ 0, 0, 0 };
        auto z = nla::zeros_like(v);
        EXPECT_TRUE(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for vector with raw array at runtime */
    {
        auto zero = array<double,3>{ 0, 0, 0 };
        auto z = nla::zeros_like(r);
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
        EXPECT_TRUE(isclose(z,zero));
    }
    /* test for vector with raw array at compile-time */
    {
        constexpr auto zero = array<double,3>{ 0, 0, 0 };
        constexpr auto z = nla::zeros_like(r);
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
        static_assert(isclose(z,zero));
    }
    /* test for matrix with array container at runtime */
    {
        auto zero = array<array<double,3>,3>{ 
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
        };
        auto z = nla::zeros_like(ma);
        EXPECT_TRUE(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for matrix with array container at compile-time */
    {
        constexpr auto zero = array<array<double,3>,3>{ 
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
        };
        constexpr auto z = nla::zeros_like(ma);
        static_assert(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for matrix with vector container at runtime */
    {
        auto zero = vector<vector<double>>{ 
            vector<double>{0, 0, 0 },
            vector<double>{0, 0, 0 },
            vector<double>{0, 0, 0 },
        };
        auto z = nla::zeros_like(mv);
        EXPECT_TRUE(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for matrix with raw array at runtime */
    {
        auto zero = array<array<double,3>,3>{ 
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
        };
        auto z = nla::zeros_like(mr);
        EXPECT_TRUE(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for matrix with raw array at compile-time */
    {
        constexpr auto zero = array<array<double,3>,3>{ 
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
        };
        constexpr auto z = nla::zeros_like(mr);
        static_assert(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
}

TEST(linalg, clone)
{
    constexpr auto a = array<double,3>{ 1, 2, 3 };
    auto v = vector<double>{ 1, 2, 3 };
    constexpr double r[3] = { 1, 2, 3, };
    constexpr auto ma = array<array<double,3>,3> {
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
    };
    auto mv = vector<vector<double>> {
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
    };
    constexpr double mr[3][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
    };
    /* test for vector with array container at runtime */
    {
        using return_t = array<double,3>;
        auto z = nla::clone(a);
        EXPECT_TRUE(isclose(z,a));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for vector with array container at compile-time */
    {
        using return_t = const array<double,3>;
        constexpr auto z = nla::clone(a);
        static_assert(isclose(z,a));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for vector with vector container at runtime */
    {
        using return_t = vector<double>;
        auto z = nla::clone(v);
        EXPECT_TRUE(isclose(z,v));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for vector with raw array at runtime */
    {
        using return_t = array<double,3>;
        auto z = nla::clone(r);
        static_assert(std::is_same_v<return_t,decltype(z)>);
        EXPECT_TRUE(isclose(z,a));
    }
    /* test for vector with raw array at compile-time */
    {
        using return_t = const array<double,3>;
        constexpr auto z = nla::clone(r);
        static_assert(std::is_same_v<return_t,decltype(z)>);
        static_assert(isclose(z,a));
    }
    /* test for matrix with array container at runtime */
    {
        using return_t = array<array<double,3>,3>;
        auto z = nla::clone(ma);
        EXPECT_TRUE(isclose(z,ma));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for matrix with array container at compile-time */
    {
        using return_t = const array<array<double,3>,3>;
        constexpr auto z = nla::clone(ma);
        static_assert(isclose(z,ma));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for matrix with vector container at runtime */
    {
        using return_t = vector<vector<double>>;
        auto z = nla::clone(mv);
        EXPECT_TRUE(isclose(z,mv));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for matrix with raw array at runtime */
    {
        using return_t = array<array<double,3>,3>;
        auto z = nla::clone(mr);
        EXPECT_TRUE(isclose(z,ma));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for matrix with raw array at compile-time */
    {
        using return_t = const array<array<double,3>,3>;
        constexpr auto z = nla::clone(mr);
        static_assert(isclose(z,ma));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
}

TEST(linalg, identity)
{
    auto ma = array<array<double,3>,3> {
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
    };
    auto mv = vector<vector<double>> {
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
    };
    constexpr double mr[3][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
    };
    /* test for matrix with array container at runtime */
    {
        auto i = array<array<double,3>,3>{ 
            array<double,3>{1, 0, 0 },
            array<double,3>{0, 1, 0 },
            array<double,3>{0, 0, 1 },
        };
        auto z = nla::identity(ma);
        EXPECT_TRUE(isclose(z,i));
        static_assert(std::is_same_v<decltype(i),decltype(z)>);
    }
    /* test for matrix with array container at compile time */
    {
        constexpr auto i = array<array<double,3>,3>{ 
            array<double,3>{1, 0, 0 },
            array<double,3>{0, 1, 0 },
            array<double,3>{0, 0, 1 },
        };
        constexpr auto z = nla::identity(ma);
        static_assert(isclose(z,i));
        static_assert(std::is_same_v<decltype(i),decltype(z)>);
    }
    /* test for matrix with vector container at runtime */
    {
        auto i = vector<vector<double>>{
            vector<double>{1, 0, 0 },
            vector<double>{0, 1, 0 },
            vector<double>{0, 0, 1 },
        };
        static_assert(nmt::traits::is_resizeable_v<decltype(mv)>);
        auto z = nla::identity(mv);
        EXPECT_TRUE(isclose(z,i));
        static_assert(std::is_same_v<decltype(i),decltype(z)>);
    }
    /* test for matrix with raw array at runtime */
    {
        auto i = array<array<double,3>,3>{ 
            array<double,3>{1, 0, 0 },
            array<double,3>{0, 1, 0 },
            array<double,3>{0, 0, 1 },
        };
        auto z = nla::identity(mr);
        EXPECT_TRUE(isclose(z,i));
        static_assert(std::is_same_v<decltype(i),decltype(z)>);
    }
    /* test for matrix with raw array at compile time */
    {
        constexpr auto i = array<array<double,3>,3>{ 
            array<double,3>{1, 0, 0 },
            array<double,3>{0, 1, 0 },
            array<double,3>{0, 0, 1 },
        };
        constexpr auto z = nla::identity(mr);
        static_assert(isclose(z,i));
        static_assert(std::is_same_v<decltype(i),decltype(z)>);
    }
}

TEST(linalg, zeros)
{
    /* test 1D zeros with vector container */
    {
        using array_t = vector<double>;
        using return_t = array_t;
        auto z = nla::zeros<array_t>(3);
        auto zero = array_t{0, 0, 0};
        static_assert(std::is_same_v<decltype(z),array_t>);
        EXPECT_TRUE(isclose(z,zero));
    }
    /* test 1D zeros with array container */
    {
        using array_t = array<double,3>;
        using return_t = array<double,6>;
        auto z = nla::zeros<array_t,6>();
        auto zero = return_t{0, 0, 0, 0, 0, 0};
        static_assert(std::is_same_v<decltype(z),return_t>);
        EXPECT_TRUE(isclose(z,zero));
    }
    /* test 2D zeros with vector container */
    {
        using array_t = vector<vector<double>>;
        using return_t = array_t;
        auto z = nla::zeros<array_t>(2,3);
        auto zero = array_t{{{0,0,0},{0,0,0}}};
        static_assert(std::is_same_v<decltype(z),return_t>);
        EXPECT_TRUE(isclose(z,zero));
    }
    /* test 2D zeros with array container */
    {
        using array_t = array<array<double,3>,3>;
        using return_t = array<array<double,3>,2>;
        auto z = nla::zeros<array_t,2,3>();
        static_assert(std::is_same_v<decltype(z),return_t>);
        auto zero = return_t{{{0,0,0},{0,0,0}}};
        EXPECT_TRUE(isclose(z,zero));
    }
}

TEST(linalg, transpose)
{
    /* test transpose with vector container */
    {
        using array_t = vector<vector<double>>;
        using return_t = array_t;
        auto a = array_t{{
            {1,2,3},
            {4,5,6}
        }};
        auto transposed = nla::transpose(a);
        auto expected = array_t{{
            {1,4},
            {2,5},
            {3,6}
        }};
        static_assert(std::is_same_v<decltype(transposed),return_t>);
        EXPECT_TRUE(isclose(transposed,expected));
    }
    /* test transpose with array container */
    {
        using array_t = array<array<double,3>,2>;
        using return_t = array<array<double,2>,3>;
        auto a = array_t{{
            {1,2,3},
            {4,5,6}
        }};
        auto transposed = nla::transpose(a);
        auto expected = return_t{{
            {1,4},
            {2,5},
            {3,6}
        }};
        static_assert(std::is_same_v<decltype(transposed),return_t>);
        EXPECT_TRUE(isclose(transposed,expected));
    }
}

TEST(linalg, mmmul)
{
    /* test mmmul with array container */
    {
        using AType = array<array<double,2>,3>;
        using BType = array<array<double,3>,2>;
        using return_t = array<array<double,3>,3>;
        auto A = AType{{
            {1,2},
            {3,4},
            {5,6}
        }};
        auto B = BType{{
            {1,3,5},
            {2,4,6}
        }};
        auto C = nla::mmmul(A,B);
        auto expected = return_t{{
            {1+4,    3+8,  5+12},
            {3+8,   9+16, 15+24},
            {5+12, 15+24, 25+36},
        }};
        static_assert(std::is_same_v<decltype(C),return_t>);
        EXPECT_TRUE(isclose(C,expected));
    }
    /* test mmmul with vector container */
    {
        using AType = vector<vector<double>>;
        using BType = vector<vector<double>>;
        using return_t = vector<vector<double>>;
        auto A = AType{{
            {1,2},
            {3,4},
            {5,6}
        }};
        auto B = BType{{
            {1,3,5},
            {2,4,6}
        }};
        auto C = nla::mmmul(A,B);
        auto expected = return_t{{
            {1+4,    3+8,  5+12},
            {3+8,   9+16, 15+24},
            {5+12, 15+24, 25+36},
        }};
        static_assert(std::is_same_v<decltype(C),return_t>);
        EXPECT_TRUE(isclose(C,expected));
    }
    /* test mmmul with array vector container */
    {
        using AType = array<array<double,2>,3>;
        using BType = vector<vector<double>>;
        using return_t = vector<vector<double>>;
        auto A = AType{{
            {1,2},
            {3,4},
            {5,6}
        }};
        auto B = BType{{
            {1,3,5},
            {2,4,6}
        }};
        static_assert(nmt::traits::is_array2d_v<BType>);
        static_assert(nmt::traits::is_array2d_v<AType>);
        auto C = nla::mmmul(A,B);
        auto expected = return_t{{
            {1+4,    3+8,  5+12},
            {3+8,   9+16, 15+24},
            {5+12, 15+24, 25+36},
        }};
        static_assert(std::is_same_v<decltype(C),return_t>);
        EXPECT_TRUE(isclose(C,expected));
    }
}

TEST(linalg, mvmul)
{
    /* test mul with matrix-vector */
    {
        auto ayd = array<double,15>{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        auto ZT = array<array<double,15>,2>{{
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        }};
        auto ZTy = nla::mvmul(ZT,ayd);
        auto expected = array<double,2>{15,15};
        static_assert(std::is_same_v<decltype(ZTy),array<double,2>>);
        EXPECT_TRUE(isclose(ZTy,expected));
    }
}

TEST(linalg, make_array)
{
    /* test make array with array container */
    {
        using vector_t = array<double,3>;
        using return_t = array<vector_t,4>;
        auto a = vector_t{1, 2, 3};
        auto b = vector_t{4, 5, 6};
        auto c = vector_t{7, 8, 9};
        auto d = vector_t{1, 2, 3};
        auto arr = nla::detail::make_array(a,b,c,d);
        auto expected = return_t{{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
            {1, 2, 3},
        }};
        static_assert(std::is_same_v<decltype(arr),return_t>);
        EXPECT_TRUE(isclose(arr,expected));
    }
}

TEST(linalg, ones_like)
{
    /* test ones_like 1D with array container */
    {
        using vector_t = array<double,3>;
        using return_t = array<double,3>;
        auto a = vector_t{1, 2, 3};
        auto ones = nla::ones_like(a);
        auto expected = vector_t{1., 1., 1.};
        static_assert(std::is_same_v<decltype(ones),return_t>);
        EXPECT_TRUE(isclose(ones,expected));
    }
    /* test ones_like 2D with array container */
    {
        using AType = array<array<double,2>,3>;
        using return_t = AType;
        auto A = AType{{
            {1,2},
            {3,4},
            {5,6}
        }};
        auto ones = nla::ones_like(A);
        auto expected = return_t{{
            {1,1},
            {1,1},
            {1,1}
        }};
        static_assert(std::is_same_v<decltype(ones),return_t>);
        EXPECT_TRUE(isclose(ones,expected));
    }
}