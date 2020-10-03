#ifndef NMTOOLS_TESTING_DATA_BLAS_VSMUL_HPP
#define NMTOOLS_TESTING_DATA_BLAS_VSMUL_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(blas, vsmul)
{
    template <typename T>
    constexpr T h = static_cast<T>(0.5);

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        using common::v5;
        using vsmul::h;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v5);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,5);
        // NOTE: DECLARE_SCALAR use cast which can handle scalar type
        NMTOOLS_TESTING_DATA_DECLARE_SCALAR(y,h);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr auto res = std::array<double,5>{8.50000,   12.00000,    0.50000,    4.00000,    7.50000};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        using common::v10;
        using vsmul::h;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v10);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,10);
        // NOTE: DECLARE_SCALAR use cast which can handle scalar type
        NMTOOLS_TESTING_DATA_DECLARE_SCALAR(y,h);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr auto res = std::array<double,10>{46.00000,   49.50000,    0.50000,    4.00000,    7.50000,   33.50000,   37.00000,   25.50000,   29.00000,   20.00000};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        using common::v15;
        using vsmul::h;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v15);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,15);
        // NOTE: DECLARE_SCALAR use cast which can handle scalar type
        NMTOOLS_TESTING_DATA_DECLARE_SCALAR(y,h);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr auto res = std::array<double,15>{61.00000,    69.50000,    78.00000,    86.50000,    95.00000,   103.50000,   112.00000,     0.50000,     9.00000,    17.50000,    26.00000,    34.50000,    43.00000,    51.50000,    60.00000};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        using common::v20;
        using vsmul::h;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v20);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,20);
        // NOTE: DECLARE_SCALAR use cast which can handle scalar type
        NMTOOLS_TESTING_DATA_DECLARE_SCALAR(y,h);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr auto res = std::array<double,20>{200.0000,     1.0000,     1.5000,   198.5000,   198.0000,     3.0000,     3.5000,   196.5000,   196.0000,     5.0000,     5.5000,   194.5000,   194.0000,     7.0000,     7.5000,   192.5000,   192.0000,     9.0000,     9.5000,   190.5000};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        using common::v25;
        using vsmul::h;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v25);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,25);
        // NOTE: DECLARE_SCALAR use cast which can handle scalar type
        NMTOOLS_TESTING_DATA_DECLARE_SCALAR(y,h);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr auto res = std::array<double,25>{163.50000,   177.00000,   190.50000,   204.00000,   217.50000,   231.00000,   244.50000,   258.00000,   271.50000,   285.00000,   298.50000,   312.00000,     0.50000,    14.00000,    27.50000,    41.00000,    54.50000,    68.00000,    81.50000,    95.00000,   108.50000,   122.00000,   135.50000,   149.00000,   162.50000};
    }
}

#endif // NMTOOLS_TESTING_DATA_BLAS_VSMUL_HPP