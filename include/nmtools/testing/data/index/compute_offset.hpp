#ifndef NMTOOLS_TESTING_DATA_INDEX_COMPUTE_OFFSET_HPP
#define NMTOOLS_TESTING_DATA_INDEX_COMPUTE_OFFSET_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, compute_offset)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        // note that this is strides not shape
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {0,0};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {0,1};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result = 1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {1,0};
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result = 2;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1d)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {1,1};
        inline auto indices_ct = nmtools_tuple{1_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1d)
    {
        inline int result = 3;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1e)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {2,0};
        inline auto indices_ct = nmtools_tuple{2_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"2:[2]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1e)
    {
        inline int result = 4;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1f)
    {
        inline int strides[2] = {2,1};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[2] = {2,1};
        inline auto indices_ct = nmtools_tuple{2_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"2:[2]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1f)
    {
        inline int result = 5;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,0,0};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"0:[1]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,0,1};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"0:[1]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result = 1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,0,2};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,2_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"0:[1]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result = 2;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,1,0};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"0:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result = 3;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,1,1};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"1:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int result = 4;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2f)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {0,1,2};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct,2_ct};
        inline auto indices_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2f)
    {
        inline int result = 5;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2g)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {1,0,0};
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct,0_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"0:[1]"_ct,"0:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2g)
    {
        inline int result = 6;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2h)
    {
        inline int strides[3] = {6,3,1};
        inline auto strides_ct = nmtools_tuple{6_ct,3_ct,1_ct};
        inline auto strides_cl = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(strides);

        inline int indices[3] = {1,0,1};
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct,1_ct};
        inline auto indices_cl = nmtools_tuple{"1:[1]"_ct,"0:[1]"_ct,"1:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);

        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides);
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2h)
    {
        inline int result = 7;
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_COMPUTE_OFFSET_HPP