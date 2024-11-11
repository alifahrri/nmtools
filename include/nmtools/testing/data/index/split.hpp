#ifndef NMTOOLS_TESTING_DATA_INDEX_SPLIT_HPP
#define NMTOOLS_TESTING_DATA_INDEX_SPLIT_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, split)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int lhs[1] = {2};
        inline int rhs[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = 2;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int lhs[2] = {2,3};
        inline int rhs[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = -2;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int lhs[1] = {2};
        inline int rhs[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = -1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int lhs[2] = {2,3};
        inline int rhs[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto lhs = nmtools_list<int>{};
        inline int rhs[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[3] = {2,3,2};
        inline auto N = 3;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int lhs[3] = {2,3,2};
        inline auto rhs = nmtools_list<int>{};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[1] = {6};
        inline auto N = -1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline auto lhs = nmtools_list<int>{};
        inline int rhs[1] = {6};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_SPLIT_HPP