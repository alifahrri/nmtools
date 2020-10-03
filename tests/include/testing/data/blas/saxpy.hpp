#ifndef NMTOOLS_TESTING_DATA_BLAS_SAXPY_HPP
#define NMTOOLS_TESTING_DATA_BLAS_SAXPY_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(blas, saxpy)
{
    template <typename T>
    constexpr T s = static_cast<T>(0.5);

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        using common::v5;
        using common::r5;
        using saxpy::s;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v5);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,5);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,r5);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,5);
        // NOTE: DECLARE_SCALAR use cast which can handle scalar type
        NMTOOLS_TESTING_DATA_DECLARE_SCALAR(a,s);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr auto res = std::array<double,5>{9.50,   14.00,    3.50,    8.00,   12.50};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        using common::v10;
        using common::r10;
        using saxpy::s;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v10);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,10);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,r10);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,10);
        // NOTE: DECLARE_SCALAR use cast which can handle scalar type
        NMTOOLS_TESTING_DATA_DECLARE_SCALAR(a,s);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr auto res = std::array<double,10>{47.00,   51.50,    3.50,    8.00,   12.50,   39.50,   44.00,   33.50,   38.00,   30.00};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        using common::v15;
        using common::r15;
        using saxpy::s;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v15);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,15);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,r15);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,15);
        // NOTE: DECLARE_SCALAR use cast which can handle scalar type
        NMTOOLS_TESTING_DATA_DECLARE_SCALAR(a,s);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr auto res = std::array<double,15>{62.00,    71.50,    81.00,    90.50,   100.00,   109.50,   119.00,     8.50,    18.00,    27.50,    37.00,    46.50,    56.00,    65.50,    75.00};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        using common::v20;
        using common::r20;
        using saxpy::s;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v20);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,20);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,r20);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,20);
        // NOTE: DECLARE_SCALAR use cast which can handle scalar type
        NMTOOLS_TESTING_DATA_DECLARE_SCALAR(a,s);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr auto res = std::array<double,20>{201.00,     3.00,     4.50,   202.50,   203.00,     9.00,    10.50,   204.50,   205.00,    15.00,    16.50,   206.50,   207.00,    21.00,    22.50,   208.50,   209.00,    27.00,    28.50,   210.50};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        using common::v25;
        using common::r25;
        using saxpy::s;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v25);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,25);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,r25);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,25);
        // NOTE: DECLARE_SCALAR use cast which can handle scalar type
        NMTOOLS_TESTING_DATA_DECLARE_SCALAR(a,s);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr auto res = std::array<double,25>{164.50,   179.00,   193.50,   208.00,   222.50,   237.00,   251.50,   266.00,   280.50,   295.00,   309.50,   324.00,    13.50,    28.00,    42.50,    57.00,    71.50,    86.00,   100.50,   115.00,   129.50,   144.00,   158.50,   173.00,   187.50};
    }
}

#endif // NMTOOLS_TESTING_DATA_BLAS_SAXPY_HPP