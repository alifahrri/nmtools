#ifndef NMTOOLS_TESTING_DATA_INDEX_LOGICAL_NOT_HPP
#define NMTOOLS_TESTING_DATA_INDEX_LOGICAL_NOT_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(logical_not)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline nm_bool_t x[5] = {true, false, false, true, false};
        NMTOOLS_CAST_INDEX_ARRAYS(x);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline nm_bool_t x[5] = {false, true, true, false, true};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_LOGICAL_NOT_HPP