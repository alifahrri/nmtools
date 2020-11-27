#include "nmtools/blas/blas.hpp"
#include "nmtools/utils/isclose.hpp"
#include <gtest/gtest.h>
#include <array>
#include <vector>

namespace nmt = nmtools;
namespace nla = nmt::blas;

using std::array;
using std::vector;

using nmt::utils::isclose;

TEST(blas, zeros_like)
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

TEST(blas, clone)
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

TEST(blas, identity)
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
        static_assert(nmt::meta::is_resizeable_v<decltype(mv)>);
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

TEST(blas, zeros)
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

TEST(blas, transpose)
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
    /* test transpose with raw container */
    {
        using array_t = array<array<double,3>,2>;
        using return_t = array<array<double,2>,3>;
        double a[2][3] = {
            {1,2,3},
            {4,5,6}
        };
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

TEST(blas, mmmul)
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
    /* test mmmul with raw container */
    {
        using return_t = array<array<double,3>,3>;
        constexpr double A[3][2] = {
            {1,2},
            {3,4},
            {5,6}
        };
        constexpr double B[2][3] = {
            {1,3,5},
            {2,4,6}
        };
        constexpr auto C = nla::mmmul(A,B);
        constexpr auto expected = return_t{{
            {1+4,    3+8,  5+12},
            {3+8,   9+16, 15+24},
            {5+12, 15+24, 25+36},
        }};
        static_assert(std::is_same_v<decltype(C),const return_t>);
        static_assert(isclose(C,expected));
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
        static_assert(nmt::meta::is_array2d_v<BType>);
        static_assert(nmt::meta::is_array2d_v<AType>);
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

TEST(blas, mvmul)
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
    {
        constexpr double ayd[15] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        constexpr double ZT[2][15] = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        };
        constexpr auto ZTy = nla::mvmul(ZT,ayd);
        constexpr auto expected = array<double,2>{15,15};
        static_assert(std::is_same_v<decltype(ZTy),const array<double,2>>);
        EXPECT_TRUE(isclose(ZTy,expected));
    }
}

TEST(blas, make_array)
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

TEST(blas, ones_like)
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

TEST(blas, vvadd)
{
    using nla::vvadd;
    {
        using vector_t = array<double,3>;
        constexpr auto v = vector_t{1., 2., 3.};
        constexpr auto r = vvadd(v,v);
        constexpr auto expected = vector_t{2., 4., 6.};
        static_assert(isclose(r,expected));
    }
    {
        using vector_t = vector<double>;
        auto v = vector_t{1., 2., 3.};
        auto r = vvadd(v,v);
        auto expected = vector_t{2., 4., 6.};
        EXPECT_TRUE(isclose(r,expected));
    }
    {
        using vector_t = array<double,3>;
        constexpr double v[3] = {1., 2., 3.};
        constexpr auto r = vvadd(v,v);
        constexpr auto expected = vector_t{2., 4., 6.};
        static_assert(std::is_same_v<decltype(r),const vector_t>);
        static_assert(isclose(r,expected));
    }
}

TEST(blas, mmadd)
{
    using nla::mmadd;
    {
        using vector_t = array<double,3>;
        using matrix_t = array<vector_t,3>;
        constexpr auto m1 = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        constexpr auto m2 = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        constexpr auto r = mmadd(m1,m2);
        constexpr auto expected = matrix_t{{
            {2., 2., 2.},
            {2., 2., 2.},
            {2., 2., 2.},
        }};
        static_assert(isclose(r,expected));
    }
    {
        using vector_t = vector<double>;
        using matrix_t = vector<vector_t>;
        auto m1 = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        auto m2 = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        auto r = mmadd(m1,m2);
        auto expected = matrix_t{{
            {2., 2., 2.},
            {2., 2., 2.},
            {2., 2., 2.},
        }};
        EXPECT_TRUE(isclose(r,expected));
    }
    {
        using vector_t = array<double,3>;
        using matrix_t = array<vector_t,3>;
        constexpr double m1[3][3] = {
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        };
        constexpr double m2[3][3] = {
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        };
        constexpr auto r = mmadd(m1,m2);
        constexpr auto expected = matrix_t{{
            {2., 2., 2.},
            {2., 2., 2.},
            {2., 2., 2.},
        }};
        static_assert(std::is_same_v<decltype(r),const matrix_t>);
        static_assert(isclose(r,expected));
    }
}

TEST(blas, vsmul)
{
    using nla::vsmul;
    using vector_t = array<double,3>;
    using matrix_t = array<vector_t,3>;
    using scalar_t = double;

    /* fixed */
    {
        constexpr auto v = vector_t{1., 2., 3.};
        constexpr auto s = 3.;
        constexpr auto r = vsmul(v,s);
        constexpr auto e = vector_t{3, 6, 9};
        static_assert(std::is_same_v<decltype(r),const vector_t>);
        static_assert(isclose(r,e));
    }
    /* raw */
    {
        constexpr double v[3] = {1.,2.,3.};
        constexpr auto s = 3.;
        constexpr auto r = vsmul(v,s);
        constexpr auto e = vector_t{3, 6, 9};
        static_assert(std::is_same_v<decltype(r),const vector_t>);
        static_assert(isclose(r,e));
    }
}

TEST(blas, msmul)
{
    using nla::msmul;
    {
        using vector_t = array<double,3>;
        using matrix_t = array<vector_t,3>;
        constexpr auto m = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        constexpr auto s = 2.;
        constexpr auto r = msmul(m,s);
        constexpr auto expected = matrix_t{{
            {2., 2., 2.},
            {2., 2., 2.},
            {2., 2., 2.},
        }};
        static_assert(isclose(r,expected));
    }
    {
        using vector_t = vector<double>;
        using matrix_t = vector<vector_t>;
        auto m = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        auto s = 2.;
        auto r = msmul(m,s);
        auto expected = matrix_t{{
            {2., 2., 2.},
            {2., 2., 2.},
            {2., 2., 2.},
        }};
        EXPECT_TRUE(isclose(r,expected));
    }
    {
        using vector_t = array<double,3>;
        using matrix_t = array<vector_t,3>;
        constexpr double m[3][3] = {
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        };
        constexpr auto s = 2.;
        constexpr auto r = msmul(m,s);
        constexpr auto expected = matrix_t{{
            {2., 2., 2.},
            {2., 2., 2.},
            {2., 2., 2.},
        }};
        static_assert(std::is_same_v<decltype(r),const matrix_t>);
        static_assert(isclose(r,expected));
    }
}

namespace nlt =  nla::tag;

TEST(blas, get_tag)
{
    using vector_t = array<double,3>;
    using matrix_t = array<vector_t,3>;
    using scalar_t = double;

    using vv_t = nlt::get_t<vector_t,vector_t>;
    static_assert( std::is_same_v<vv_t,nlt::vector_vector_t>);
    static_assert(!std::is_same_v<vv_t,nlt::vector_scalar_t>);
    static_assert(!std::is_same_v<vv_t,nlt::matrix_scalar_t>);
    static_assert(!std::is_same_v<vv_t,nlt::matrix_vector_t>);
    static_assert(!std::is_same_v<vv_t,nlt::matrix_matrix_t>);
    static_assert(!std::is_same_v<vv_t,nlt::scalar_scalar_t>);

    using mm_t = nlt::get_t<matrix_t,matrix_t>;
    static_assert(!std::is_same_v<mm_t,nlt::vector_vector_t>);
    static_assert(!std::is_same_v<mm_t,nlt::vector_scalar_t>);
    static_assert(!std::is_same_v<mm_t,nlt::matrix_scalar_t>);
    static_assert(!std::is_same_v<mm_t,nlt::matrix_vector_t>);
    static_assert( std::is_same_v<mm_t,nlt::matrix_matrix_t>);
    static_assert(!std::is_same_v<mm_t,nlt::scalar_scalar_t>);

    using ss_t = nlt::get_t<scalar_t,scalar_t>;
    static_assert(!std::is_same_v<ss_t,nlt::vector_vector_t>);
    static_assert(!std::is_same_v<ss_t,nlt::vector_scalar_t>);
    static_assert(!std::is_same_v<ss_t,nlt::matrix_scalar_t>);
    static_assert(!std::is_same_v<ss_t,nlt::matrix_vector_t>);
    static_assert(!std::is_same_v<ss_t,nlt::matrix_matrix_t>);
    static_assert( std::is_same_v<ss_t,nlt::scalar_scalar_t>);

    using mv_t = nlt::get_t<matrix_t,vector_t>;
    static_assert(!std::is_same_v<mv_t,nlt::vector_vector_t>);
    static_assert(!std::is_same_v<mv_t,nlt::vector_scalar_t>);
    static_assert(!std::is_same_v<mv_t,nlt::matrix_scalar_t>);
    static_assert( std::is_same_v<mv_t,nlt::matrix_vector_t>);
    static_assert(!std::is_same_v<mv_t,nlt::matrix_matrix_t>);
    static_assert(!std::is_same_v<mv_t,nlt::scalar_scalar_t>);

    using ms_t = nlt::get_t<matrix_t,scalar_t>;
    static_assert(!std::is_same_v<ms_t,nlt::vector_vector_t>);
    static_assert(!std::is_same_v<ms_t,nlt::vector_scalar_t>);
    static_assert( std::is_same_v<ms_t,nlt::matrix_scalar_t>);
    static_assert(!std::is_same_v<ms_t,nlt::matrix_vector_t>);
    static_assert(!std::is_same_v<ms_t,nlt::matrix_matrix_t>);
    static_assert(!std::is_same_v<ms_t,nlt::scalar_scalar_t>);

    using vs_t = nlt::get_t<vector_t,scalar_t>;
    static_assert(!std::is_same_v<vs_t,nlt::vector_vector_t>);
    static_assert( std::is_same_v<vs_t,nlt::vector_scalar_t>);
    static_assert(!std::is_same_v<vs_t,nlt::matrix_scalar_t>);
    static_assert(!std::is_same_v<vs_t,nlt::matrix_vector_t>);
    static_assert(!std::is_same_v<vs_t,nlt::matrix_matrix_t>);
    static_assert(!std::is_same_v<vs_t,nlt::scalar_scalar_t>);
}

TEST(blas, mul)
{
    using nla::mul;
    using vector_t = array<double,3>;
    using matrix_t = array<vector_t,3>;
    using scalar_t = double;

    /* scalar-scalar multiplication */
    {
        constexpr auto a = mul(3.,3.);
        static_assert(isclose(a,9.));
    }
    /* vector-scalar multiplication */
    {
        constexpr auto v = vector_t{1., 2., 3.};
        constexpr auto r = mul(v,3.);
        constexpr auto expected = vector_t{3., 6., 9.};
        static_assert(isclose(r,expected));
    }
    /* matrix-scalar multiplication */
    {
        constexpr auto m = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        constexpr auto r = mul(m,3.);
        constexpr auto expected = matrix_t{{
            {3., 3., 3.},
            {3., 3., 3.},
            {3., 3., 3.},
        }};
        static_assert(isclose(r,expected));
    }
    /* matrix-vector multiplication */
    {
        constexpr auto m = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        constexpr auto v = vector_t{
            1.,
            2.,
            3.
        };
        constexpr auto r = mul(m,v);
        constexpr auto expected = vector_t{
            6.,
            6.,
            6.
        };
        static_assert(isclose(r,expected));
    }
    /* matrix-matrix multiplication */
    {
        constexpr auto m1 = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        constexpr auto m2 = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        constexpr auto r = mul(m1,m2);
        constexpr auto expected = matrix_t{{
            {3., 3., 3.},
            {3., 3., 3.},
            {3., 3., 3.},
        }};
        static_assert(isclose(r,expected));
    }
}

TEST(blas, add)
{
    using nla::add;
    using vector_t = array<double,3>;
    using matrix_t = array<vector_t,3>;
    using scalar_t = double;

    /* scalar-scalar add */
    {
        constexpr auto a = add(3., 3.);
        static_assert(isclose(a,6.));
    }
    /* vector-vector add */
    {
        constexpr auto v = vector_t{1., 2., 3.};
        constexpr auto r = add(v,v);
        constexpr auto expected = vector_t{2., 4., 6.};
        static_assert(isclose(r,expected));
    }
    /* matrix-matrix multiplication */
    {
        constexpr auto m1 = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        constexpr auto m2 = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        constexpr auto r = add(m1,m2);
        constexpr auto expected = matrix_t{{
            {2., 2., 2.},
            {2., 2., 2.},
            {2., 2., 2.},
        }};
        static_assert(isclose(r,expected));
    }
}

TEST(blas, saxpy)
{
    using nla::saxpy;
    using vector_t = array<double,3>;
    using matrix_t = array<vector_t,3>;
    using scalar_t = double;

    using dvector_t = std::vector<double>;

    /* compile-time version */
    {
        constexpr auto a = 2.;
        constexpr auto v = vector_t{1., 2., 3.};
        constexpr auto r = saxpy(a,v,v);
        constexpr auto expected = vector_t{2.*1.+1., 2*2.+2., 2*3.+3};
        /* return type of r should be the same as y type (vector_t), need const since this is computed at compile-time */
        static_assert(std::is_same_v<decltype(r),const vector_t>);
        static_assert(isclose(r,expected));
    }
    /* dynamic version */
    {
        auto a = 2.;
        auto x = vector_t {1., 2., 3.};
        auto y = dvector_t{1. ,2., 3.};
        auto r = saxpy(a,x,y);
        auto expected = vector_t{2.*1.+1., 2*2.+2., 2*3.+3};
        /* return type of r should be the same as y type (vector_t) */
        static_assert(std::is_same_v<decltype(r),dvector_t>);
        EXPECT_TRUE(isclose(r,expected));
    }
}

TEST(blas, gaxpy)
{
    using nla::gaxpy;
    using vector_t = array<double,3>;
    using matrix_t = array<vector_t,3>;
    using scalar_t = double;

    using dvector_t = std::vector<double>;

    /* compile-time version */
    {
        constexpr auto a = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        constexpr auto x = vector_t{1., 2., 3.};
        constexpr auto y = vector_t{1., 2., 3.};
        constexpr auto r = gaxpy(a,x,y);
        constexpr auto expected = vector_t{
            1.*1.+1.*2.+1.*3.+1.,
            1.*1.+1.*2.+1.*3.+2.,
            1.*1.+1.*2.+1.*3.+3.,
        };
        /* return type of r should be the same as y type (vector_t), need const since this is computed at compile-time */
        static_assert(std::is_same_v<decltype(r),const vector_t>);
        static_assert(isclose(r,expected));
    }
    /* dynamic version */
    {
        constexpr auto a = matrix_t{{
            {1., 1., 1.},
            {1., 1., 1.},
            {1., 1., 1.},
        }};
        auto x = vector_t {1., 2., 3.};
        auto y = dvector_t{1. ,2., 3.};
        auto r = gaxpy(a,x,y);
        auto expected = vector_t{
            1.*1.+1.*2.+1.*3.+1.,
            1.*1.+1.*2.+1.*3.+2.,
            1.*1.+1.*2.+1.*3.+3.,
        };
        /* return type of r should be the same as y type (vector_t) */
        static_assert(std::is_same_v<decltype(r),dvector_t>);
        EXPECT_TRUE(isclose(r,expected));
    }
}

TEST(blas, dot)
{
    using vector_t = array<double,3>;
    using matrix_t = array<vector_t,3>;
    using scalar_t = double;
    using dvector_t = vector<double>;
    /* fixed-size runtime version */
    {
        auto a = vector_t{1.,2.,3.};
        auto b = vector_t{3.,4.,5.};
        auto r = nla::dot(a,b);
        auto e = 1.*3 + 2*4 + 3*5;
        EXPECT_TRUE(isclose(r,e));
    }
    /* compile-time */
    {
        constexpr auto a = vector_t{1.,2.,3.};
        constexpr auto b = vector_t{3.,4.,5.};
        constexpr auto r = nla::dot(a,b);
        constexpr auto e = 1.*3 + 2*4 + 3*5;
        static_assert(isclose(r,e));
    }
    /* dynamic-size runtime */
    {
        auto a = dvector_t{1.,2.,3.};
        auto b = dvector_t{3.,4.,5.};
        auto r = nla::dot(a,b);
        auto e = 1.*3 + 2*4 + 3*5;
        EXPECT_TRUE(isclose(r,e));
    }
    /* raw array runtime */
    {
        double a[3] = {1.,2.,3.};
        double b[3] = {3.,4.,5.};
        auto r = nla::dot(a,b);
        auto e = 1.*3 + 2*4 + 3*5;
        EXPECT_TRUE(isclose(r,e));
    }
}

TEST(blas, outer)
{
    using vector_t = array<double,3>;
    using matrix_t = array<vector_t,3>;
    using scalar_t = double;
    using dvector_t = vector<double>;
    /* fixed-size runtime version */
    {
        auto a = vector_t{1.,2.,3.};
        auto b = vector_t{3.,4.,5.};
        auto r = nla::outer(a,b);
        auto e = matrix_t{{
            {1*3, 1*4, 1*5},
            {2*3, 2*4, 2*5},
            {3*3, 3*4, 3*5},
        }};
        static_assert(std::is_same_v<decltype(r),matrix_t>);
        EXPECT_TRUE(isclose(r,e));
    }
    /* compile-time */
    {
        constexpr auto a = vector_t{1.,2.,3.};
        constexpr auto b = vector_t{3.,4.,5.};
        constexpr auto r = nla::outer(a,b);
        constexpr auto e = matrix_t{{
            {1*3, 1*4, 1*5},
            {2*3, 2*4, 2*5},
            {3*3, 3*4, 3*5},
        }};
        static_assert(std::is_same_v<decltype(r),const matrix_t>);
        static_assert(isclose(r,e));
    }
    /* dynamic-size runtime */
    {
        auto a = dvector_t{1.,2.,3.};
        auto b = dvector_t{3.,4.,5.};
        auto r = nla::outer(a,b);
        auto e = matrix_t{{
            {1*3, 1*4, 1*5},
            {2*3, 2*4, 2*5},
            {3*3, 3*4, 3*5},
        }};
        EXPECT_TRUE(isclose(r,e));
    }
    /* raw array runtime */
    {
        double a[3] = {1.,2.,3.};
        double b[3] = {3.,4.,5.};
        auto r = nla::outer(a,b);
        auto e = matrix_t{{
            {1*3, 1*4, 1*5},
            {2*3, 2*4, 2*5},
            {3*3, 3*4, 3*5},
        }};
        EXPECT_TRUE(isclose(r,e));
    }
    /* mix vector-array */
    {
        auto a = dvector_t{1.,2.,3.};
        auto b = vector_t{3.,4.,5.};
        auto r = nla::outer(a,b);
        auto e = matrix_t{{
            {1*3, 1*4, 1*5},
            {2*3, 2*4, 2*5},
            {3*3, 3*4, 3*5},
        }};
        static_assert(std::is_same_v<decltype(r),std::vector<std::array<double,3>>>);
        EXPECT_TRUE(isclose(r,e));
    }
}