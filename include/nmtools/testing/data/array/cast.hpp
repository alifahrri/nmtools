#ifndef NMTOOLS_TESTING_DATA_ARRAY_CAST_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_CAST_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,cast)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline double array[6] = {1,2,3,4,5,6};
        inline auto dtype = float32;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline double array[6] = {1,2,3,4,5,6};
        inline auto dtype = uint8;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float expected[6] = {1,2,3,4,5,6};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_CAST_HPP