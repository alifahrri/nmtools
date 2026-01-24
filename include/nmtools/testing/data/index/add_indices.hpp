#ifndef NMTOOLS_TESTING_DATA_INDEX_ADD_INDICES_HPP
#define NMTOOLS_TESTING_DATA_INDEX_ADD_INDICES_HPP

#include "nmtools/testing/doctest.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, add_indices)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int lhs_indices[3] = {0,1,2};
        inline int rhs_indices[3] = {1,0,0};
        NMTOOLS_CAST_INDEX_ARRAYS(lhs_indices)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_indices)

        inline auto lhs_indices_ct = nmtools_tuple{0_ct,1_ct,2_ct};
        inline auto rhs_indices_ct = nmtools_tuple{1_ct,0_ct,0_ct};

        inline auto lhs_indices_nl1 = nmtools_array{nullable_int(0),nullable_int(),nullable_int()};
        inline auto rhs_indices_nl1 = nmtools_array{nullable_int(1),nullable_int(),nullable_int()};

        inline auto lhs_indices_nl2 = nmtools_array{nullable_int(0),nullable_int(1),nullable_int()};
        inline auto rhs_indices_nl2 = nmtools_array{nullable_int(1),nullable_int(0),nullable_int()};

        inline auto lhs_indices_mx1 = nmtools_tuple{0_ct,1,2};
        inline auto rhs_indices_mx1 = nmtools_tuple{1_ct,0,0};

        inline auto lhs_indices_mx2 = nmtools_tuple{0_ct,1_ct,2};
        inline auto rhs_indices_mx2 = nmtools_tuple{1_ct,0_ct,0};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3] = {1,1,2};
        inline auto result_nl1 = nmtools_array{nullable_int(1),nullable_int(),nullable_int()};
        inline auto result_nl2 = nmtools_array{nullable_int(1),nullable_int(1),nullable_int()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int lhs_indices[2] = {1,2};
        inline int rhs_indices[2] = {4,5};

        NMTOOLS_CAST_INDEX_ARRAYS(lhs_indices)
        NMTOOLS_CAST_INDEX_ARRAYS(rhs_indices)

        inline auto lhs_indices_ct = nmtools_tuple{1_ct,2_ct};
        inline auto rhs_indices_ct = nmtools_tuple{4_ct,5_ct};

        inline auto lhs_indices_nl1 = nmtools_array{nullable_int(1),nullable_int()};
        inline auto rhs_indices_nl1 = nmtools_array{nullable_int(4),nullable_int()};

        inline auto lhs_indices_nl2 = nmtools_array{nullable_int(1),nullable_int(2)};
        inline auto rhs_indices_nl2 = nmtools_array{nullable_int(4),nullable_int(5)};

        inline auto lhs_indices_mx1 = nmtools_tuple{1_ct,2};
        inline auto rhs_indices_mx1 = nmtools_tuple{4_ct,5};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {5,7};
        inline auto result_nl1 = nmtools_array{nullable_int(5),nullable_int()};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_ADD_INDICES_HPP