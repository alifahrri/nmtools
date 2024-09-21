#ifndef NMTOOLS_TESTING_DATA_ARRAY_LINSPACE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_LINSPACE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,linspace)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float start = 2.0;
        inline float stop  = 3.0;
        inline int num = 5;
        // inline auto endpoint = True;
        // inline auto retstep  = False;

        inline auto num_ct = 5_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[5] = {2.0,2.25,2.5,2.75,3.0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float start = 2.0;
        inline float stop  = 3.0;
        inline int num = 5;
        inline auto endpoint = False;
        // inline auto retstep = False;

        inline auto num_ct = 5_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[5] = {2.0,2.2,2.4,2.6,2.8};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline float start = 2.0;
        inline float stop  = 3.0;
        inline int num = 5;
        inline auto endpoint = True;
        inline auto retstep  = True;

        inline auto num_ct = 5_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto result = nmtools_tuple{
            nmtools_array{2.0,2.25,2.5,2.75,3.0}
            , 0.25f
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline float start = 0.0;
        inline float stop  = 5.0;
        inline int num = 10;

        inline auto num_ct = 10_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline float result[10] = {
            0.f        , 0.55555556f, 1.11111111f, 1.66666667f, 2.22222222f,
            2.77777778f, 3.33333333f, 3.88888889f, 4.44444444f, 5.f        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline float start = 0.0;
        inline float stop  = 5.0;
        inline int num = 10;
        inline auto endpoint = False;

        inline auto num_ct = 10_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline float result[10] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int start = 2;
        inline int stop  = 3;
        inline int num   = 5;
        // inline auto endpoint = True;
        // inline auto retstep  = False;

        inline auto num_ct = 5_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline float result[5] = {2.0,2.25,2.5,2.75,3.0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int start = 0;
        inline int stop  = 5;
        inline int num = 10;
        inline auto endpoint = False;

        inline auto num_ct = 10_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline float result[10] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_LINSPACE_HPP