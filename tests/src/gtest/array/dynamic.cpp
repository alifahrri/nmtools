#include "nmtools/array/dynamic.hpp"
#include "nmtools/utils/isclose.hpp"
#include "nmtools/blas/blas.hpp"
#include <gtest/gtest.h>
#include <array>

namespace nmt = nmtools;
using nmt::utils::isclose;
using nmt::array::dynamic_vector;
using nmt::array::dynamic_matrix;
using nmt::array::fixed_vector;

TEST(array, traits)
{
    using namespace nmt::meta;
    static_assert( is_array1d_v<dynamic_vector<double>>);
    static_assert(!is_array2d_v<dynamic_vector<double>>);
    static_assert(!is_array1d_v<dynamic_matrix<double>>);
    static_assert( is_array2d_v<dynamic_matrix<double>>);
    static_assert( is_resizeable_v<dynamic_vector<double>>);
    static_assert( is_resizeable_v<dynamic_matrix<double>>);
    static_assert(!is_resizeable2d_v<dynamic_vector<double>>);
    static_assert( is_resizeable2d_v<dynamic_matrix<double>>);
}

TEST(array, dynamic_vector)
{
    /* aggregate initialization */
    {
        auto v = dynamic_vector<double>({1.,2.,3});
        auto e = std::array<double,3>{1.,2.,3.};
        EXPECT_TRUE(isclose(v,e));
    }
    /* get element */
    {
        auto v = dynamic_vector<double>({1.,2.,3});
        auto e = v(2);
        EXPECT_TRUE(isclose(e,3));
    }
    /* set element */
    {
        auto v = dynamic_vector<double>({1.,2.,3});
        v(2) = 10.;
        auto e = std::array<double,3>{1.,2.,10.};
        EXPECT_TRUE(isclose(v,e));
    }
    /* at get element */
    {
        auto v = dynamic_vector<double>({1.,2.,3});
        auto r = nmt::at(v,2);
        EXPECT_TRUE(isclose(r,3));
    }
    /* at set element */
    {
        auto v = dynamic_vector<double>({1.,2.,3});
        nmt::at(v,2) = 10.;
        auto e = std::array<double,3>{1.,2.,10.};
        EXPECT_TRUE(isclose(v,e));
    }
}

TEST(array, dynamic_matrix)
{
    /* aggregate initialization */
    {
        auto m = dynamic_matrix<double>({
            {1.,2.,3.},
            {3.,4.,5.},
        });
        auto e = std::array<std::array<double,3>,2>{{
            {1.,2.,3.},
            {3.,4.,5.},
        }};
        auto [row, col] = nmt::matrix_size(m);
        EXPECT_TRUE(row==2 && col==3);
        EXPECT_TRUE(isclose(m,e));
    }
    /* get element */
    {
        auto m = dynamic_matrix<double>({
            {1.,2.,3.},
            {3.,4.,5.},
        });

        auto v = m(1,2);
        EXPECT_TRUE(isclose(v,5));
    }
    /* set element */
    {
        auto m = dynamic_matrix<double>({
            {1.,2.,3.},
            {3.,4.,5.},
        });
        m(1,2) = 10.;
        auto e = std::array<std::array<double,3>,2>{{
            {1.,2.,3.},
            {3.,4.,10.},
        }};
        EXPECT_TRUE(isclose(m,e));
    }
    /* at get element */
    {
        auto m = dynamic_matrix<double>({
            {1.,2.,3.},
            {3.,4.,5.},
        });

        auto v = nmt::at(m,1,2);
        EXPECT_TRUE(isclose(v,5));
    }
    /* set element */
    {
        auto m = dynamic_matrix<double>({
            {1.,2.,3.},
            {3.,4.,5.},
        });
        nmt::at(m,1,2) = 10.;
        auto e = std::array<std::array<double,3>,2>{{
            {1.,2.,3.},
            {3.,4.,10.},
        }};
        EXPECT_TRUE(isclose(m,e));
    }
}

TEST(array, dynamic_vector_blas_add)
{
    /* vector vector add */
    {
        auto a = dynamic_vector<double>({1.,2.,3});
        auto b = dynamic_vector<double>({1.,2.,3});
        auto v = nmt::blas::add(a,b);
        auto e = std::array<double,3>{2.,4.,6.};
        static_assert(std::is_same_v<decltype(v),dynamic_vector<double>>);
        EXPECT_TRUE(isclose(v,e)) << v(0) << v(1) << v(2);
    }
    /* vector vector add */
    {
        auto a = dynamic_vector<double>({1.,2.,3});
        auto b = fixed_vector<double,3>({1.,2.,3});
        auto v = nmt::blas::add(a,b);
        auto e = std::array<double,3>{2.,4.,6.};
        static_assert(std::is_same_v<decltype(v),dynamic_vector<double>>);
        EXPECT_TRUE(isclose(v,e)) << v(0) << v(1) << v(2);
    }
    /* vector scalar mul */
    {
        auto a = dynamic_vector<double>({1.,2.,3});
        auto b = 2;
        auto v = nmt::blas::mul(a,b);
        auto e = std::array<double,3>{2.,4.,6.};
        static_assert(std::is_same_v<decltype(v),dynamic_vector<double>>);
        EXPECT_TRUE(isclose(v,e)) << v(0) << v(1) << v(2);
    }
}

TEST(array, dynamic_vector_blas_saxpy)
{
    {
        auto a = 2;
        auto x = dynamic_vector<double>({1.,2.,3});
        auto y = dynamic_vector<double>({1.,2.,3});
        auto v = nmt::blas::saxpy(a,x,y);
        auto e = std::array<double,3>{3.,6.,9.};
        EXPECT_TRUE(isclose(v,e)) << v(0) << v(1) << v(2);
    }
    {
        auto a = 2;
        auto x = dynamic_vector<double>({1.,2.,3});
        auto y = fixed_vector<double,3>({1.,2.,3});
        auto v = nmt::blas::saxpy(a,x,y);
        auto e = std::array<double,3>{3.,6.,9.};
        EXPECT_TRUE(isclose(v,e)) << v(0) << v(1) << v(2);
    }
}

TEST(array, dynamic_vector_blas_dot)
{
    {
        auto x = dynamic_vector<double>({1.,2.,3});
        auto y = dynamic_vector<double>({1.,2.,3});
        auto v = nmt::blas::dot(x,y);
        auto e = 1.*1 + 2*2 + 3*3;
        EXPECT_TRUE(isclose(v,e));
    }
    {
        auto x = dynamic_vector<double>({1.,2.,3});
        auto y = fixed_vector<double,3>({1.,2.,3});
        auto v = nmt::blas::dot(x,y);
        auto e = 1.*1 + 2*2 + 3*3;
        EXPECT_TRUE(isclose(v,e));
    }
    {
        auto x = fixed_vector<double,3>({1.,2.,3});
        auto y = dynamic_vector<double>({1.,2.,3});
        auto v = nmt::blas::dot(x,y);
        auto e = 1.*1 + 2*2 + 3*3;
        EXPECT_TRUE(isclose(v,e));
    }
}

TEST(array, dynamic_vector_outer)
{
    {
        auto x = dynamic_vector<double>({1.,2.,3});
        auto y = dynamic_vector<double>({3.,4.,5});
        auto r = nmt::blas::outer(x,y);
        auto e = std::array<std::array<double,3>,3>{{
            {1*3, 1*4, 1*5},
            {2*3, 2*4, 2*5},
            {3*3, 3*4, 3*5},
        }};
        static_assert(std::is_same_v<decltype(r),dynamic_matrix<double>>);
        auto [rows,cols] = nmt::matrix_size(r);
        EXPECT_EQ(rows,3);
        EXPECT_EQ(cols,3);
        EXPECT_TRUE(isclose(r,e));
    }
    {
        auto x = dynamic_vector<double>({1.,2.,3});
        auto y = fixed_vector<double,3>({3.,4.,5});
        auto r = nmt::blas::outer(x,y);
        auto e = std::array<std::array<double,3>,3>{{
            {1*3, 1*4, 1*5},
            {2*3, 2*4, 2*5},
            {3*3, 3*4, 3*5},
        }};
        static_assert(std::is_same_v<decltype(r),dynamic_matrix<double>>);
        auto [rows,cols] = nmt::matrix_size(r);
        EXPECT_EQ(rows,3);
        EXPECT_EQ(cols,3);
        EXPECT_TRUE(isclose(r,e));
    }
    {
        auto x = fixed_vector<double,3>({1.,2.,3});
        auto y = dynamic_vector<double>({3.,4.,5});
        auto r = nmt::blas::outer(x,y);
        auto e = std::array<std::array<double,3>,3>{{
            {1*3, 1*4, 1*5},
            {2*3, 2*4, 2*5},
            {3*3, 3*4, 3*5},
        }};
        static_assert(std::is_same_v<decltype(r),dynamic_matrix<double>>);
        auto [rows,cols] = nmt::matrix_size(r);
        EXPECT_EQ(rows,3);
        EXPECT_EQ(cols,3);
        EXPECT_TRUE(isclose(r,e));
    }
}

TEST(array, dynamic_matrix_blas_add)
{
    {
        auto m = dynamic_matrix<double>({
            {1.,2.,3.},
            {3.,4.,5.},
        });
        auto n = dynamic_matrix<double>({
            {1.,2.,3.},
            {3.,4.,5.},
        });
        auto r = nmt::blas::add(m,n);
        auto e = std::array<std::array<double,3>,2>{{
            {2,4,6},
            {6,8,10},
        }};
        auto [row, col] = nmt::matrix_size(r);
        EXPECT_EQ(row,2);
        EXPECT_EQ(col,3);
        EXPECT_TRUE(isclose(r,e))
            << r(0,0) << r(0,1) << r(0,2)
            << r(1,0) << r(1,1) << r(1,2);
    }
}

TEST(array, dynamic_matrix_blas_msmul)
{
    {
        auto m = dynamic_matrix<double>({
            {1.,2.,3.},
            {3.,4.,5.},
        });
        auto s = 2.;
        auto r = nmt::blas::mul(m,s);
        auto e = std::array<std::array<double,3>,2>{{
            {1.*2,2.*2,3.*2},
            {3.*2,4.*2,5.*2},
        }};
        static_assert(std::is_same_v<decltype(r),decltype(m)>);
        auto [rows, cols] = nmt::matrix_size(r);
        EXPECT_EQ(rows,2);
        EXPECT_EQ(cols,3);
        EXPECT_TRUE(isclose(r,e));
    }
}

TEST(array, dynamic_matrix_blas_mvmul)
{
    {
        auto m = dynamic_matrix<double>({
            {1.,2.,3.},
            {3.,4.,5.},
        });
        auto v = dynamic_vector<double>({1.,2.,3});
        auto e = std::array<double,2>{
            1.*1.+2.*2.+3.*3.,
            3.*1.+4.*2.+5.*3.,
        };
        auto r = nmt::blas::mul(m,v);
        /* return type should be same as vector */
        static_assert(std::is_same_v<decltype(r),decltype(v)>);
        /* matrix 2x3 * vector 3x1 results in vector 2x1 */
        EXPECT_EQ(nmt::vector_size(r),2);
        /* result should be as expected */
        EXPECT_TRUE(isclose(r,e));
    }
}

TEST(array, dynamic_matrix_blas_mmmul)
{
    {
        auto m = dynamic_matrix<double>({
            {1.,2.,3.},
            {3.,4.,5.},
        });
        auto n = dynamic_matrix<double>({
            {1.,2.},
            {3.,4.},
            {5.,6.},
        });
        auto e = std::array<std::array<double,2>,2>{{
            {1*1+2*3+3*5, 1*2+2*4+3*6},
            {3*1+4*3+5*5, 3*2+4*4+5*6},
        }};
        auto r = nmt::blas::mul(m,n);
        /* return type should be same as vector */
        static_assert(std::is_same_v<decltype(r),decltype(m)>);
        /* result should be as expected */
        EXPECT_TRUE(isclose(r,e));
    }
}

TEST(array, dynamic_matrix_gaxpy)
{
    {
        auto a = dynamic_matrix<double>({
            {1.,2.,3.},
            {3.,4.,5.},
        });
        auto x = dynamic_vector<double>({1.,2.,3.});
        auto y = dynamic_vector<double>({4.,5.});
        auto e = std::array<double,2>{
            1*1+2*2+3*3+4,
            3*1+4*2+5*3+5
        };
        auto r = nmt::blas::gaxpy(a,x,y);
        /* return type should be same as vector */
        static_assert(std::is_same_v<decltype(r),decltype(y)>);
        /* result should be as expected */
        EXPECT_TRUE(isclose(r,e));
    }
}