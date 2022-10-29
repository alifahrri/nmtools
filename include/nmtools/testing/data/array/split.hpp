#ifndef NMTOOLS_TESTING_DATA_ARRAY_SPLIT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_SPLIT_HPP

#include "nmtools/testing/array_cast.hpp"
#include "nmtools/testing/testing.hpp"

namespace nm = nmtools;
namespace na = nm::array;

// create slice args from split args
NMTOOLS_TESTING_DECLARE_CASE(index, split_args)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[1] = {9};
        inline auto indices_or_sections = 3;
        inline auto axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto split0 = nmtools_tuple{nmtools_array{0,3}};
        inline auto split1 = nmtools_tuple{nmtools_array{3,6}};
        inline auto split2 = nmtools_tuple{nmtools_array{6,9}};
        inline auto result = nmtools_tuple{split0,split1,split2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[1] = {9};
        inline auto indices_or_sections = 9;
        inline auto axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto split0 = nmtools_tuple{nmtools_array{0,1}};
        inline auto split1 = nmtools_tuple{nmtools_array{1,2}};
        inline auto split2 = nmtools_tuple{nmtools_array{2,3}};
        inline auto split3 = nmtools_tuple{nmtools_array{3,4}};
        inline auto split4 = nmtools_tuple{nmtools_array{4,5}};
        inline auto split5 = nmtools_tuple{nmtools_array{5,6}};
        inline auto split6 = nmtools_tuple{nmtools_array{6,7}};
        inline auto split7 = nmtools_tuple{nmtools_array{7,8}};
        inline auto split8 = nmtools_tuple{nmtools_array{8,9}};
        inline auto result = nmtools_tuple{split0,split1,split2,split3,split4,split5,split6,split7,split8};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[1] = {9};
        inline auto indices_or_sections = 1;
        inline auto axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto split0 = nmtools_tuple{nmtools_array{0,9}};
        inline auto result = nmtools_tuple{split0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[1] = {9};
        inline auto indices_or_sections = 3;
        inline auto axis = -1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto split1 = nmtools_tuple{nmtools_array{0,3}};
        inline auto split2 = nmtools_tuple{nmtools_array{3,6}};
        inline auto split3 = nmtools_tuple{nmtools_array{6,9}};
        inline auto result = nmtools_tuple{split1,split2,split3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[1] = {9}; 
        inline auto indices_or_sections = 9;
        inline auto axis = -1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        using case2::expect::result;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[1] = {9};
        inline auto indices_or_sections = 1;
        inline auto axis = -1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        using case3::expect::result;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[1] = {6};
        inline auto indices_or_sections = nmtools_array{2,4};
        inline auto axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline auto split1 = nmtools_tuple{nmtools_array{0,2}};
        inline auto split2 = nmtools_tuple{nmtools_array{2,4}};
        inline auto split3 = nmtools_tuple{nmtools_array{4,6}};
        inline auto result = nmtools_tuple{split1,split2,split3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int shape[1] = {6};
        inline auto indices_or_sections = nmtools_array{2,5};
        inline auto axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline auto split1 = nmtools_tuple{nmtools_array{0,2}};
        inline auto split2 = nmtools_tuple{nmtools_array{2,5}};
        inline auto split3 = nmtools_tuple{nmtools_array{5,6}};
        inline auto result = nmtools_tuple{split1,split2,split3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int shape[2] = {2,6};
        inline auto indices_or_sections = 2;
        inline auto axis = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto split1 = nmtools_tuple{
            nmtools_array{0,1}, 
            nmtools_array{0,6}
        };
        inline auto split2 = nmtools_tuple{
            nmtools_array{1,2}, 
            nmtools_array{0,6}
        };
        inline auto result = nmtools_tuple{split1,split2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int shape[2] = {2,6};
        inline auto indices_or_sections = 2;
        inline auto axis = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline auto split1 = nmtools_tuple{
            nmtools_array{0,2},
            nmtools_array{0,3}
        };
        inline auto split2 = nmtools_tuple{
            nmtools_array{0,2},
            nmtools_array{3,6}
        };
        inline auto result = nmtools_tuple{split1,split2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int shape[2] = {2,6};
        inline auto indices_or_sections = nmtools_array{2,4};
        inline auto axis = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline auto split0 = nmtools_tuple{
            nmtools_array{0,2},
            nmtools_array{0,2}
        };
        inline auto split1 = nmtools_tuple{
            nmtools_array{0,2},
            nmtools_array{2,4}
        };
        inline auto split2 = nmtools_tuple{
            nmtools_array{0,2},
            nmtools_array{4,6}
        };
        inline auto result = nmtools_tuple{split0,split1,split2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int shape[2] = {2,6};
        inline auto indices_or_sections = nmtools_array{2,5};
        inline auto axis = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline auto split0 = nmtools_tuple{
            nmtools_array{0,2},
            nmtools_array{0,2}
        };
        inline auto split1 = nmtools_tuple{
            nmtools_array{0,2},
            nmtools_array{2,5}
        };
        inline auto split2 = nmtools_tuple{
            nmtools_array{0,2},
            nmtools_array{5,6}
        };
        inline auto result = nmtools_tuple{split0,split1,split2};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(array, split)
{
    using namespace nmtools::literals;
    using meta::ct_v;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[9] = {0,1,2,3,4,5,6,7,8};
        inline auto indices_or_sections = 3;
        inline auto axis = 0;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto split0 = nmtools_array{0,1,2};
        inline auto split1 = nmtools_array{3,4,5};
        inline auto split2 = nmtools_array{6,7,8};
        inline auto result = nmtools_tuple{split0,split1,split2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[9] = {0,1,2,3,4,5,6,7,8};
        inline auto indices_or_sections = 9_ct;
        inline auto axis = 0_ct;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto split0 = nmtools_array{0};
        inline auto split1 = nmtools_array{1};
        inline auto split2 = nmtools_array{2};
        inline auto split3 = nmtools_array{3};
        inline auto split4 = nmtools_array{4};
        inline auto split5 = nmtools_array{5};
        inline auto split6 = nmtools_array{6};
        inline auto split7 = nmtools_array{7};
        inline auto split8 = nmtools_array{8};
        inline auto result = nmtools_tuple{split0,split1,split2,split3,split4,split5,split6,split7,split8};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[9] = {0,1,2,3,4,5,6,7,8};
        inline auto indices_or_sections = 1_ct;
        inline auto axis = 0_ct;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto split0 = nmtools_array{0,1,2,3,4,5,6,7,8};
        inline auto result = nmtools_tuple{split0};
    }

    // negative -1 also ok
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[9] = {0,1,2,3,4,5,6,7,8};
        inline auto indices_or_sections = 3_ct;
        inline auto axis = ct_v<-1>;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto split0 = nmtools_array{0,1,2};
        inline auto split1 = nmtools_array{3,4,5};
        inline auto split2 = nmtools_array{6,7,8};
        inline auto result = nmtools_tuple{split0,split1,split2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int a[9] = {0,1,2,3,4,5,6,7,8};
        inline auto indices_or_sections = 9_ct;
        inline auto axis = ct_v<-1>;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto split0 = nmtools_array{0};
        inline auto split1 = nmtools_array{1};
        inline auto split2 = nmtools_array{2};
        inline auto split3 = nmtools_array{3};
        inline auto split4 = nmtools_array{4};
        inline auto split5 = nmtools_array{5};
        inline auto split6 = nmtools_array{6};
        inline auto split7 = nmtools_array{7};
        inline auto split8 = nmtools_array{8};
        inline auto result = nmtools_tuple{split0,split1,split2,split3,split4,split5,split6,split7,split8};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int a[9] = {0,1,2,3,4,5,6,7,8};
        inline auto indices_or_sections = 1_ct;
        inline auto axis = ct_v<-1>;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline auto split0 = nmtools_array{0,1,2,3,4,5,6,7,8};
        inline auto result = nmtools_tuple{split0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int a[6] = {0,1,2,3,4,5};
        inline auto indices_or_sections = nmtools_array{2,4};
        inline auto axis = 0_ct;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline auto split0 = nmtools_array{0,1};
        inline auto split1 = nmtools_array{2,3};
        inline auto split2 = nmtools_array{4,5};
        inline auto result = nmtools_tuple{split0,split1,split2};
    }

#ifndef ARDUINO
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int a[6] = {0,1,2,3,4,5};
        inline auto indices_or_sections = nmtools_array{2,5};
        inline auto axis = 0_ct;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline auto split0 = nmtools_array{0,1};
        inline auto split1 = nmtools_array{2,3,4};
        inline auto split2 = nmtools_array{5};
        inline auto result = nmtools_tuple{split0,split1,split2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int a[2][6] = {
            {0,1,2,3, 4, 5},
            {6,7,8,9,10,11},
        };
        inline auto indices_or_sections = 2_ct;
        inline auto axis = 0_ct;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto split0 = nmtools_array{0,1,2,3, 4, 5};
        inline auto split1 = nmtools_array{6,7,8,9,10,11};
        inline auto result = nmtools_tuple{split0,split1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int a[2][6] = {
            {0,1,2,3, 4, 5},
            {6,7,8,9,10,11},
        };
        inline auto indices_or_sections = 2_ct;
        inline auto axis = 1_ct;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        using split_t = nmtools_array<nmtools_array<int,3>,2>;
        using result_t = nmtools_tuple<split_t,split_t>;
        inline auto split0 = split_t{{
            {0,1,2},
            {6,7,8},
        }};
        inline auto split1 = split_t{{
            {3, 4, 5},
            {9,10,11},
        }};
        inline auto result = result_t{split0,split1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int a[2][6] = {
            {0,1,2,3, 4, 5},
            {6,7,8,9,10,11},
        };
        inline auto indices_or_sections = nmtools_array{2,4};
        inline auto axis = 1_ct;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int split0[2][2] = {
            {0,1},
            {6,7},
        };
        inline int split1[2][2] = {
            {2,3},
            {8,9},
        };
        inline int split2[2][2] = {
            { 4, 5},
            {10,11},
        };
        NMTOOLS_CAST_ARRAYS(split0)
        NMTOOLS_CAST_ARRAYS(split1)
        NMTOOLS_CAST_ARRAYS(split2)
        inline auto result = nmtools_tuple{split0_a,split1_a,split2_a};
    }
#endif // ARDUINO

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int a[2][6] = {
            {0,1,2,3, 4, 5},
            {6,7,8,9,10,11},
        };
        inline auto indices_or_sections = nmtools_tuple{2_ct,5_ct};
        inline auto axis = 1_ct;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        // NOTE: to allow utl, somehow argument deduction doesn't work properly
        // TODO: fix utl::array nested argument deduction
        using split0_t = nmtools_array<nmtools_array<int,2>,2>;
        using split1_t = nmtools_array<nmtools_array<int,3>,2>;
        using split2_t = nmtools_array<nmtools_array<int,1>,2>;
        inline auto split0 = split0_t{{
            {0,1},
            {6,7},
        }};
        inline auto split1 = split1_t{{
            {2,3, 4},
            {8,9,10},
        }};
        inline auto split2 = split2_t{{
            { 5},
            {11},
        }};
        inline auto result = nmtools_tuple{split0,split1,split2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int a[6] = {0,1,2,3,4,5};
        inline auto indices_or_sections = nmtools_tuple{2_ct,4_ct};
        inline auto axis = 0_ct;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline auto split0 = nmtools_array{0,1};
        inline auto split1 = nmtools_array{2,3};
        inline auto split2 = nmtools_array{4,5};
        inline auto result = nmtools_tuple{split0,split1,split2};
    }

    // TODO: error cases
    // TODO: ValueError: array split does not result in an equal division
    // - axis=1
    // - indices_or_sections=2
    // TODO: ZeroDivisionError: integer division or modulo by zero
    // - indices_or_sections must be nonzero

}
#endif // NMTOOLS_TESTING_DATA_ARRAY_SPLIT_HPP