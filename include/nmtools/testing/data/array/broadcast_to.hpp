#ifndef NMTOOLS_TESTING_DATA_ARRAY_BROADCAST_TO_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_BROADCAST_TO_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(index, broadcast_to)
{
    using nmtools_tuple;
    using namespace nmtools::literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int ashape[2] = {3,1};
        inline int bshape[2] = {3,1};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        inline auto ashape_ct = nmtools_tuple{3_ct,1_ct};
        inline auto bshape_ct = nmtools_tuple{3_ct,1_ct};
        inline auto ashape_cl = nmtools_tuple{"3:[3]"_ct,"1:[1]"_ct};
        inline auto bshape_cl = nmtools_tuple{"3:[3]"_ct,"1:[1]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto success = true;
        inline auto shape   = nmtools_array{3,1};
        inline auto free    = nmtools_array{false,false};
        inline auto results = nmtools_tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int ashape[2] = {3,1};
        inline int bshape[2] = {3,3};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        inline auto ashape_ct = nmtools_tuple{3_ct,1_ct};
        inline auto bshape_ct = nmtools_tuple{3_ct,3_ct};
        inline auto ashape_cl = nmtools_tuple{"3:[3]"_ct,"1:[1]"_ct};
        inline auto bshape_cl = nmtools_tuple{"3:[3]"_ct,"3:[3]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto success = true;
        inline auto shape   = nmtools_array{3,3};
        inline auto free    = nmtools_array{false,true};
        inline auto results = nmtools_tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int ashape[2] = {3,1};
        inline int bshape[3] = {3,3,1};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        inline auto ashape_ct = nmtools_tuple{3_ct,1_ct};
        inline auto bshape_ct = nmtools_tuple{3_ct,3_ct,1_ct};
        inline auto ashape_cl = nmtools_tuple{"3:[3]"_ct,"1:[1]"_ct};
        inline auto bshape_cl = nmtools_tuple{"3:[3]"_ct,"3:[3]"_ct,"1:[1]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto success = true;
        inline auto shape   = nmtools_array{3,3,1};
        inline auto free    = nmtools_array{true,false,false};
        inline auto results = nmtools_tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int ashape[2] = {3,1};
        inline int bshape[3] = {3,3,6};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        inline auto ashape_ct = nmtools_tuple{3_ct,1_ct};
        inline auto bshape_ct = nmtools_tuple{3_ct,3_ct,6_ct};
        inline auto ashape_cl = nmtools_tuple{"3:[3]"_ct,"1:[1]"_ct};
        inline auto bshape_cl = nmtools_tuple{"3:[3]"_ct,"3:[3]"_ct,"6:[6]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto success = true;
        inline auto shape   = nmtools_array{3,3,6};
        inline auto free    = nmtools_array{true,false,true};
        inline auto results = nmtools_tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int ashape[2] = {3,1};
        inline int bshape[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        inline auto ashape_ct = nmtools_tuple{3_ct,1_ct};
        inline auto bshape_ct = nmtools_tuple{3_ct};
        inline auto ashape_cl = nmtools_tuple{"3:[3]"_ct,"1:[1]"_ct};
        inline auto bshape_cl = nmtools_tuple{"3:[3]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto success = false;
        inline auto shape   = nmtools_array{0};
        inline auto free    = nmtools_array{false};
        inline auto results = nmtools_tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int ashape[2] = {3,1};
        inline int bshape[3] = {3,6,6};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        inline auto ashape_ct = nmtools_tuple{3_ct,1_ct};
        inline auto bshape_ct = nmtools_tuple{3_ct,6_ct,6_ct};
        inline auto ashape_cl = nmtools_tuple{"3:[3]"_ct,"1:[1]"_ct};
        inline auto bshape_cl = nmtools_tuple{"3:[3]"_ct,"6:[6]"_ct,"6:[6]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline auto success = false;
        inline auto shape   = nmtools_array{0,0,6};
        inline auto free    = nmtools_array{false,false,true};
        inline auto results = nmtools_tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int ashape[2] = {3,1};
        inline int bshape[4] = {7,3,3,6};
        NMTOOLS_CAST_INDEX_ARRAYS(ashape)
        NMTOOLS_CAST_INDEX_ARRAYS(bshape)
        inline auto ashape_ct = nmtools_tuple{3_ct,1_ct};
        inline auto bshape_ct = nmtools_tuple{7_ct,3_ct,3_ct,6_ct};
        inline auto ashape_cl = nmtools_tuple{"3:[3]"_ct,"1:[1]"_ct};
        inline auto bshape_cl = nmtools_tuple{"7:[7]"_ct,"3:[3]"_ct,"3:[3]"_ct,"6:[6]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline auto success = true;
        inline auto shape   = nmtools_array{7,3,3,6};
        inline auto free    = nmtools_array{true,true,false,true};
        inline auto results = nmtools_tuple{success,shape,free};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(broadcast_to)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t x[3] = {1,2,3};
        inline auto shape = nmtools_array{1,3};
        inline auto shape_ct = nmtools_tuple{1_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct, "3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t expected[1][3] = {
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int8_t x[1][3] = {{1,2,3}};
        inline auto shape = nmtools_array{3,3};
        inline auto shape_ct = nmtools_tuple{3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"3:[3]"_ct, "3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int8_t expected[3][3] = {
            {1,2,3},
            {1,2,3},
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int8_t x = 1;
        inline auto shape = nmtools_array{1,3};
        inline auto shape_ct = nmtools_tuple{1_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct, "3:[3]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int8_t expected[1][3] = {
            {1,1,1}
        };
    }

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int8_t x[3] = {1,2,3};
        inline auto shape = nmtools_array{3,3};
        inline auto shape_ct = nmtools_tuple{3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"3:[3]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t expected[3][3] = {
            {1,2,3},
            {1,2,3},
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int8_t x[3] = {1,2,3};
        inline auto shape = nmtools_array{2,3,3};
        inline auto shape_ct = nmtools_tuple{2_ct,3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int8_t expected[2][3][3] = {
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int8_t x[3][1] = {
            {1},
            {2},
            {3}
        };
        inline auto shape = nmtools_array{3,3};
        inline auto shape_ct = nmtools_tuple{3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"3:[3]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int8_t expected[3][3] = {
            {1,1,1},
            {2,2,2},
            {3,3,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int8_t x[3][1] = {
            {1},
            {2},
            {3}
        };
        inline auto shape = nmtools_array{2,3,3};
        inline auto shape_ct = nmtools_tuple{2_ct,3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int8_t expected[2][3][3] = {
            {
                {1,1,1},
                {2,2,2},
                {3,3,3}
            },
            {
                {1,1,1},
                {2,2,2},
                {3,3,3}
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int8_t x[1][3] = {{1,2,3}};
        inline auto shape = nmtools_array{1,3};
        inline auto shape_ct = nmtools_tuple{1_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int8_t expected[1][3] = {
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int8_t x[1][3] = {{1,2,3}};
        inline auto shape = nmtools_array{2,3,3};
        inline auto shape_ct = nmtools_tuple{2_ct,3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int8_t expected[2][3][3] = {
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
        };
    }


    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int8_t x[2][1][3] = {
            {
                {1,2,3}
            },
            {
                {4,5,6}
            },
        };
        inline auto shape = nmtools_array{2,3,3};
        inline auto shape_ct = nmtools_tuple{2_ct,3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int8_t expected[2][3][3] = {
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
            {
                {4,5,6},
                {4,5,6},
                {4,5,6},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int8_t x = 1;
        inline auto shape = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int8_t expected = 1;
    }
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_BROADCAST_TO_HPP