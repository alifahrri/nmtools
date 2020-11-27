#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "nmtools/utils/isclose.hpp"
#include <gtest/gtest.h>
#include <array>

namespace nmt = nmtools;
using nmt::utils::isclose;
using nmt::array::fixed_vector;
using nmt::array::fixed_matrix;

TEST(array, fixed_vector)
{
    /* aggregate initialization */
    {
        auto a = fixed_vector<double,3>{1., 2., 3.};
        auto e = std::array<double,3>{1.,2.,3.};
        EXPECT_TRUE(isclose(a,e));
    }
    /* get element */
    {
        auto a = fixed_vector<double,3>{1., 2., 3.};
        auto e = a(2);
        EXPECT_TRUE(isclose(e,3.));
    }
    /* set element */
    {
        auto a = fixed_vector<double,3>{1., 2., 3.};
        a(2) = 10.;
        auto e = std::array<double,3>{1.,2.,10.};
        EXPECT_TRUE(isclose(a,e));
    }
    /* constexpr fixed_vector */
    {
        constexpr auto a = fixed_vector<double,3>{1., 2., 3.};
        constexpr auto e = std::array<double,3>{1.,2.,3.};
        static_assert(isclose(a,e));
    }
    /* at get element */
    {
        auto a = fixed_vector<double,3>{1., 2., 3.};
        auto r = nmt::at(a,2);
        EXPECT_TRUE(isclose(r,3.));
    }
    /* at set element */
    {
        auto a = fixed_vector<double,3>{1., 2., 3.};
        nmt::at(a,2) = 10.;
        auto e = std::array<double,3>{1.,2.,10.};
        EXPECT_TRUE(isclose(a,e));
    }
}

TEST(array, fixed_matrix)
{
    /* aggregate initialization */
    {
        /* TODO: support nesed initializer list */
        auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        auto e = std::array<std::array<double,3>,2>{{
            {1., 2., 3.},
            {4., 5., 6.},
        }};
        EXPECT_TRUE(isclose(a,e));
    }
    /* compile-time */
    {
        constexpr auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        constexpr auto e = std::array<std::array<double,3>,2>{{
            {1., 2., 3.},
            {4., 5., 6.},
        }};
        static_assert(isclose(a,e));
    }
    /* get element */
    {
        auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        EXPECT_TRUE(isclose(a(1,1),5.));
    }
    /* set element */
    {
        auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        a(1,1) = 7.;
        auto e = std::array<std::array<double,3>,2>{{
            {1., 2., 3.},
            {4., 7., 6.},
        }};
        EXPECT_TRUE(isclose(a,e));
    }
    /* at get element */
    {
        auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        EXPECT_TRUE(isclose(nmt::at(a,1,1),5.));
    }
    /* at set element */
    {
        auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        nmt::at(a,1,1) = 7.;
        auto e = std::array<std::array<double,3>,2>{{
            {1., 2., 3.},
            {4., 7., 6.},
        }};
        EXPECT_TRUE(isclose(a,e));
    }
}

TEST(array, fixed_matrix_row)
{
    {
        /* TODO: support nesed initializer list */
        auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        /* NOTE: should be explicit size_t */
        auto r = nmt::row(a,size_t{1});
        auto e = std::array<double,3>{4., 5., 6.};
        EXPECT_TRUE(isclose(r,e));
    }
}

TEST(array, fixed_vector_blas_fabs)
{
    {
        auto a = fixed_vector<double,3>{-1,0,1};
        auto f = nmt::blas::fabs(a);
        auto e = std::array<double,3>{1,0,1};
        static_assert(std::is_same_v<decltype(f),fixed_vector<double,3>>);
        EXPECT_TRUE(isclose(f,e));
    }
}

TEST(array, fixed_vector_zeros_like)
{
    /* fixed_vector with runtime value */
    {
        auto a = fixed_vector<double,3>{1., 2., 3.};
        auto z = nmt::blas::zeros_like(a);
        auto e = std::array<double,3>{0.,0.,0.};
        static_assert(std::is_same_v<decltype(z),fixed_vector<double,3>>);
        EXPECT_TRUE(isclose(z,e));
    }
    /* fixed_vector with compile-time value */
    {
        constexpr auto a = fixed_vector<double,3>{1., 2., 3.};
        constexpr auto z = nmt::blas::zeros_like(a);
        constexpr auto e = std::array<double,3>{0,0,0};
        static_assert(std::is_same_v<decltype(z),const fixed_vector<double,3>>);
        static_assert(isclose(z,e));
    }
}

TEST(array, fixed_vector_ones_like)
{
    /* fixed_vector with runtime value */
    {
        auto a = fixed_vector<double,3>{1., 2., 3.};
        auto z = nmt::blas::ones_like(a);
        auto e = std::array<double,3>{1,1,1};
        static_assert(std::is_same_v<decltype(z),fixed_vector<double,3>>);
        EXPECT_TRUE(isclose(z,e));
    }
    /* fixed_vector with compile-time value */
    {
        constexpr auto a = fixed_vector<double,3>{1., 2., 3.};
        constexpr auto z = nmt::blas::ones_like(a);
        constexpr auto e = std::array<double,3>{1,1,1};
        static_assert(std::is_same_v<decltype(z),const fixed_vector<double,3>>);
        static_assert(isclose(z,e));
    }
}

TEST(array, fixed_matrix_blas_fabs)
{
    {
        auto a = fixed_matrix<double,2,3>{
            -1., 2., 3.,
            4., -5., 6.,
        };
        auto f = nmt::blas::fabs(a);
        auto e = std::array<std::array<double,3>,2>{{
            {1., 2., 3.},
            {4., 5., 6.},
        }};
        static_assert(std::is_same_v<decltype(f),fixed_matrix<double,2,3>>);
        EXPECT_TRUE(isclose(f,e));
    }
}

TEST(array, fixed_matrix_blas_zeros_like)
{
    /* fixed_matrix with runtime value */
    {
        auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        auto z = nmt::blas::zeros_like(a);
        auto e = std::array<std::array<double,3>,2>{{
            {0,0,0},
            {0,0,0},
        }};
        static_assert(std::is_same_v<decltype(z),fixed_matrix<double,2,3>>);
        EXPECT_TRUE(isclose(z,e));
    }
    /* fixed_matrix with comile-time value */
    {
        constexpr auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        constexpr auto z = nmt::blas::zeros_like(a);
        constexpr auto e = std::array<std::array<double,3>,2>{{
            {0,0,0},
            {0,0,0},
        }};
        static_assert(std::is_same_v<decltype(z),const fixed_matrix<double,2,3>>);
        static_assert(isclose(z,e));
    }
}

TEST(array, fixed_matrix_blas_ones_like)
{
    /* fixed_matrix with runtime value */
    {
        auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        auto z = nmt::blas::ones_like(a);
        auto e = std::array<std::array<double,3>,2>{{
            {1,1,1},
            {1,1,1},
        }};
        static_assert(std::is_same_v<decltype(z),fixed_matrix<double,2,3>>);
        EXPECT_TRUE(isclose(z,e));
    }
    /* fixed_matrix with comile-time value */
    {
        constexpr auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        constexpr auto z = nmt::blas::ones_like(a);
        constexpr auto e = std::array<std::array<double,3>,2>{{
            {1,1,1},
            {1,1,1},
        }};
        static_assert(std::is_same_v<decltype(z),const fixed_matrix<double,2,3>>);
        static_assert(isclose(z,e));
    }
}

TEST(array, fixed_matrix_blas_identity)
{
    /* fixed_matrix with runtime value */
    {
        auto a = fixed_matrix<double,3,3>{
            1., 2., 3.,
            4., 5., 6.,
            7., 8., 9.,
        };
        auto i = nmt::blas::identity(a);
        auto e = std::array<std::array<double,3>,3>{{
            {1,0,0},
            {0,1,0},
            {0,0,1},
        }};
        static_assert(std::is_same_v<decltype(i),fixed_matrix<double,3,3>>);
        EXPECT_TRUE(isclose(i,e));
    }
}

TEST(array, fixed_vector_blas_clone)
{
    /* fixed_vector with runtime value */
    {
        auto a = fixed_vector<double,3>{1., 2., 3.};
        auto z = nmt::blas::clone(a);
        auto e = std::array<double,3>{1,2,3};
        static_assert(std::is_same_v<decltype(z),fixed_vector<double,3>>);
        EXPECT_TRUE(isclose(z,e));
    }
    /* fixed_vector with compile-time value */
    {
        constexpr auto a = fixed_vector<double,3>{1., 2., 3.};
        constexpr auto z = nmt::blas::clone(a);
        constexpr auto e = std::array<double,3>{1,2,3};
        static_assert(std::is_same_v<decltype(z),const fixed_vector<double,3>>);
        static_assert(isclose(z,e));
    }
}

TEST(array, fixed_matrix_blas_clone)
{
    /* fixed_matrix with runtime value */
    {
        auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        auto z = nmt::blas::clone(a);
        auto e = std::array<std::array<double,3>,2>{{
            {1,2,3},
            {4,5,6},
        }};
        static_assert(std::is_same_v<decltype(z),fixed_matrix<double,2,3>>);
        EXPECT_TRUE(isclose(z,e));
    }
    /* fixed_matrix with comile-time value */
    {
        constexpr auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        constexpr auto z = nmt::blas::clone(a);
        constexpr auto e = std::array<std::array<double,3>,2>{{
            {1,2,3},
            {4,5,6},
        }};
        static_assert(std::is_same_v<decltype(z),const fixed_matrix<double,2,3>>);
        static_assert(isclose(z,e));
    }
}

TEST(array, fixed_matrix_blas_transpose)
{
    /* fixed_matrix with runtime value */
    {
        auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        auto z = nmt::blas::transpose(a);
        auto e = std::array<std::array<double,2>,3>{{
            {1,4},
            {2,5},
            {3,6}
        }};
        static_assert(std::is_same_v<decltype(z),fixed_matrix<double,3,2>>);
        EXPECT_TRUE(isclose(z,e));
    }
    /* fixed_matrix with comile-time value */
    {
        constexpr auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        constexpr auto z = nmt::blas::transpose(a);
        constexpr auto e = std::array<std::array<double,2>,3>{{
            {1,4},
            {2,5},
            {3,6}
        }};
        static_assert(std::is_same_v<decltype(z),const fixed_matrix<double,3,2>>);
        static_assert(isclose(z,e));
    }
}

TEST(array, fixed_vector_blas_vvadd)
{
    /* fixed_vector with runtime value */
    {
        auto a = fixed_vector<double,3>{1., 2., 3.};
        auto b = fixed_vector<double,3>{1., 2., 3.};
        auto v = nmt::blas::add(a,b);
        auto e = std::array<double,3>{2.,4.,6.};
        static_assert(std::is_same_v<decltype(v),fixed_vector<double,3>>);
        EXPECT_TRUE(isclose(v,e)) << v(0) << v(1) << v(2);
    }
    /* fixed_vector with compile-time value */
    {
        constexpr auto a = fixed_vector<double,3>{1., 2., 3.};
        constexpr auto b = fixed_vector<double,3>{1., 2., 3.};
        constexpr auto v = nmt::blas::add(a,b);
        constexpr auto e = std::array<double,3>{2.,4.,6.};
        static_assert(std::is_same_v<decltype(v),const fixed_vector<double,3>>);
        static_assert(isclose(v,e));
    }
}

TEST(array, fixed_vector_blas_vsmul)
{
    /* fixed_vector with runtime value */
    {
        auto a = fixed_vector<double,3>{1., 2., 3.};
        auto b = 2;
        auto v = nmt::blas::mul(a,b);
        auto e = std::array<double,3>{2.,4.,6.};
        static_assert(std::is_same_v<decltype(v),fixed_vector<double,3>>);
        EXPECT_TRUE(isclose(v,e)) << v(0) << v(1) << v(2);
    }
    /* fixed_vector with compile-time value */
    {
        constexpr auto a = fixed_vector<double,3>{1., 2., 3.};
        constexpr auto b = 2;
        constexpr auto v = nmt::blas::mul(a,b);
        constexpr auto e = std::array<double,3>{2.,4.,6.};
        static_assert(std::is_same_v<decltype(v),const fixed_vector<double,3>>);
        static_assert(isclose(v,e));
    }
}

TEST(array, fixed_vector_blas_saxpy)
{
    /* fixed_vector with runtime value */
    {
        auto a = 2;
        auto x = fixed_vector<double,3>{1., 2., 3.};
        auto y = fixed_vector<double,3>{1., 2., 3.};
        auto v = nmt::blas::saxpy(a,x,y);
        auto e = std::array<double,3>{3.,6.,9.};
        static_assert(std::is_same_v<decltype(v),fixed_vector<double,3>>);
        EXPECT_TRUE(isclose(v,e)) << v(0) << v(1) << v(2);
    }
    /* fixed_vector with compile-time value */
    {
        constexpr auto a = 2;
        constexpr auto x = fixed_vector<double,3>{1., 2., 3.};
        constexpr auto y = fixed_vector<double,3>{1., 2., 3.};
        constexpr auto v = nmt::blas::saxpy(a,x,y);
        constexpr auto e = std::array<double,3>{3.,6.,9.};
        static_assert(std::is_same_v<decltype(v),const fixed_vector<double,3>>);
        static_assert(isclose(v,e));
    }
}

TEST(array, fixed_vector_blas_dot)
{
    /* fixed_vector with runtime value */
    {
        auto x = fixed_vector<double,3>{1.,2.,3.};
        auto y = fixed_vector<double,3>{1.,2.,3.};
        auto v = nmt::blas::dot(x,y);
        auto e = 1.*1 + 2*2 + 3*3;
        static_assert(std::is_same_v<decltype(v),double>);
        EXPECT_TRUE(isclose(v,e));
    }
    /* fixed_vector with compile-time value */
    {
        constexpr auto x = fixed_vector<double,3>{1.,2.,3.};
        constexpr auto y = fixed_vector<double,3>{1.,2.,3.};
        constexpr auto v = nmt::blas::dot(x,y);
        constexpr auto e = 1.*1 + 2*2 + 3*3;
        static_assert(std::is_same_v<decltype(v),const double>);
        static_assert(isclose(v,e));
    }
}

TEST(array, fixed_vector_blas_outer)
{
    {
        auto x = fixed_vector<double,3>{1.,2.,3.};
        auto y = fixed_vector<double,3>{3.,4.,5.};
        auto r = nmt::blas::outer(x,y);
        auto e = std::array<std::array<double,3>,3>{{
            {1*3, 1*4, 1*5},
            {2*3, 2*4, 2*5},
            {3*3, 3*4, 3*5},
        }};
        static_assert(std::is_same_v<decltype(r),fixed_matrix<double,3,3>>);
        EXPECT_TRUE(isclose(r,e));
    }
    {
        constexpr auto x = fixed_vector<double,3>{1.,2.,3.};
        constexpr auto y = fixed_vector<double,3>{3.,4.,5.};
        constexpr auto r = nmt::blas::outer(x,y);
        constexpr auto e = std::array<std::array<double,3>,3>{{
            {1*3, 1*4, 1*5},
            {2*3, 2*4, 2*5},
            {3*3, 3*4, 3*5},
        }};
        static_assert(std::is_same_v<decltype(r),const fixed_matrix<double,3,3>>);
        static_assert(isclose(r,e));
    }
}

TEST(array, fixed_matrix_blas_add)
{
    /* fixed_matrix with runtime-value */
    {
        /* TODO: support nesed initializer list */
        auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        /* TODO: support nesed initializer list */
        auto b = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        auto r = nmt::blas::add(a,b);
        auto e = std::array<std::array<double,3>,2>{{
            {2,4,6},
            {8,10,12},
        }};
        auto [rows, cols] = nmt::matrix_size(r);
        static_assert(std::is_same_v<decltype(r),fixed_matrix<double,2,3>>);
        EXPECT_EQ(rows,2);
        EXPECT_EQ(cols,3);
        EXPECT_TRUE(isclose(r,e));
    }
    /* fixed_matrix with compile-time value */
    {
        /* TODO: support nesed initializer list */
        constexpr auto a = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        /* TODO: support nesed initializer list */
        constexpr auto b = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        constexpr auto r = nmt::blas::add(a,b);
        constexpr auto e = std::array<std::array<double,3>,2>{{
            {2,  4,  6},
            {8, 10, 12},
        }};
        constexpr auto shape = nmt::matrix_size(r);
        constexpr auto rows  = std::get<0>(shape);
        constexpr auto cols  = std::get<1>(shape);
        static_assert((rows==2)&&(cols==3));
        static_assert(std::is_same_v<decltype(r),const fixed_matrix<double,2,3>>);
        static_assert(isclose(r,e));
    }
}

TEST(array, fixed_matrix_blas_msmul)
{
    /* fixed_matrix with runtime value */
    {
        /* TODO: support nesed initializer list */
        auto m = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        auto s = 2.;
        auto r = nmt::blas::mul(m,s);
        auto e = std::array<std::array<double,3>,2>{{
            {1*2,2*2,3*2},
            {4*2,5*2,6*2},
        }};
        auto [rows, cols] = nmt::matrix_size(r);
        static_assert(std::is_same_v<decltype(r),fixed_matrix<double,2,3>>);
        EXPECT_TRUE((rows==2)&&(cols==3));
        EXPECT_TRUE(isclose(r,e));
    }
    /* fixed_matrix with compile-time value */
    {
        /* TODO: support nesed initializer list */
        constexpr auto m = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        constexpr auto s = 2.;
        constexpr auto r = nmt::blas::mul(m,s);
        constexpr auto e = std::array<std::array<double,3>,2>{{
            {1*2,2*2,3*2},
            {4*2,5*2,6*2},
        }};
        constexpr auto shape = nmt::matrix_size(r);
        constexpr auto rows = std::get<0>(shape);
        constexpr auto cols = std::get<1>(shape);
        static_assert((rows==2)&&(cols==3));
        static_assert(std::is_same_v<decltype(r),const fixed_matrix<double,2,3>>);
        static_assert(isclose(r,e));
    }
}

TEST(array, fixed_matrix_blas_mvmul)
{
    /* fixed_matrix & fixed_vector with runtime value */
    {
        /* TODO: support nesed initializer list */
        auto m = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        auto v = fixed_vector<double,3>{1,2,3};
        auto r = nmt::blas::mul(m,v);
        auto e = std::array<double,2>{
            1*1+2*2+3*3,
            4*1+5*2+6*3
        };
        static_assert(std::is_same_v<decltype(r),fixed_vector<double,2>>);
        EXPECT_TRUE(isclose(r,e));
    }
    /* fixed_matrix & fixed_vector with compile-time value */
    {
        /* TODO: support nesed initializer list */
        constexpr auto m = fixed_matrix<double,2,3>{
            1., 2., 3.,
            4., 5., 6.,
        };
        constexpr auto v = fixed_vector<double,3>{1,2,3};
        constexpr auto r = nmt::blas::mul(m,v);
        constexpr auto e = std::array<double,2>{
            1*1+2*2+3*3,
            4*1+5*2+6*3
        };
        static_assert(std::is_same_v<decltype(r),const fixed_vector<double,2>>);
        static_assert(isclose(r,e));
    }
}

TEST(array, fixed_matrix_blas_mmmul)
{
    /* fixed_matrix with runtime value */
    {
        /* TODO: support nesed initializer list */
        auto m = fixed_matrix<double,2,3>{
            1.,2.,3.,
            3.,4.,5.,
        };
        /* TODO: support nesed initializer list */
        auto n = fixed_matrix<double,3,2>{
            1.,2.,
            3.,4.,
            5.,6.,
        };
        auto e = std::array<std::array<double,2>,2>{{
            {1*1+2*3+3*5, 1*2+2*4+3*6},
            {3*1+4*3+5*5, 3*2+4*4+5*6},
        }};
        auto r = nmt::blas::mul(m,n);
        /* return type should be same as vector */
        static_assert(std::is_same_v<decltype(r),fixed_matrix<double,2,2>>);
        /* result should be as expected */
        EXPECT_TRUE(isclose(r,e));
    }
    /* fixed_matrix with compile-time value */
    {
        /* TODO: support nesed initializer list */
        constexpr auto m = fixed_matrix<double,2,3>{
            1.,2.,3.,
            3.,4.,5.,
        };
        /* TODO: support nesed initializer list */
        constexpr auto n = fixed_matrix<double,3,2>{
            1.,2.,
            3.,4.,
            5.,6.,
        };
        constexpr auto e = std::array<std::array<double,2>,2>{{
            {1*1+2*3+3*5, 1*2+2*4+3*6},
            {3*1+4*3+5*5, 3*2+4*4+5*6},
        }};
        constexpr auto r = nmt::blas::mul(m,n);
        /* return type should be same as vector */
        static_assert(std::is_same_v<decltype(r),const fixed_matrix<double,2,2>>);
        /* result should be as expected */
        static_assert(isclose(r,e));
    }
}

TEST(array, fixed_matrix_gaxpy)
{
    /* fixed_matrix with runtime value */
    {
        /* TODO: support nesed initializer list */
        auto a = fixed_matrix<double,2,3>{
            1.,2.,3.,
            3.,4.,5.,
        };
        auto x = fixed_vector<double,3>{1,2,3};
        auto y = fixed_vector<double,2>{4,5};
        auto e = std::array<double,2>{
            1*1+2*2+3*3+4,
            3*1+4*2+5*3+5
        };
        auto r = nmt::blas::gaxpy(a,x,y);
        static_assert(std::is_same_v<decltype(r),fixed_vector<double,2>>);
        EXPECT_TRUE(isclose(r,e));
    }
    /* fixed_matrix with compile-time value */
    {
        /* TODO: support nesed initializer list */
        constexpr auto a = fixed_matrix<double,2,3>{
            1.,2.,3.,
            3.,4.,5.,
        };
        constexpr auto x = fixed_vector<double,3>{1,2,3};
        constexpr auto y = fixed_vector<double,2>{4,5};
        constexpr auto e = std::array<double,2>{
            1*1+2*2+3*3+4,
            3*1+4*2+5*3+5
        };
        constexpr auto r = nmt::blas::gaxpy(a,x,y);
        static_assert(std::is_same_v<decltype(r),const fixed_vector<double,2>>);
        static_assert(isclose(r,e));
    }
}