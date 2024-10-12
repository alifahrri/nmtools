#ifndef NMTOOLS_TESTING_DATA_ARRAY_RADIANS_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_RADIANS_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,radians)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[12] = {0.,  30.,  60.,  90., 120., 150., 180., 210., 240., 270., 300., 330.};
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[12] = {
            0.        , 0.52359878, 1.04719755, 1.57079633, 2.0943951 ,
            2.61799388, 3.14159265, 3.66519143, 4.1887902 , 4.71238898,
            5.23598776, 5.75958653
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[4][3] = {
            {  0.,  60., 120.},
            {180., 240., 300.},
            {360., 420., 480.},
            {540., 600., 660.}
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[4][3] = {
            { 0.        ,  1.04719755,  2.0943951 },
            { 3.14159265,  4.1887902 ,  5.23598776},
            { 6.28318531,  7.33038286,  8.37758041},
            { 9.42477796, 10.47197551, 11.51917306}
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_RADIANS_HPP