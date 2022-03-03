#ifndef NMTOOLS_TESTING_DATA_ARRAY_SLICE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_SLICE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, slice)
{

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = nmtools_tuple{None,None};
        inline auto slice1 = nmtools_tuple{0,1};
        inline auto slice2 = nmtools_tuple{None,None};
        inline auto slices = nmtools_tuple{slice0,slice1,slice2};
        using slice_t  = nmtools_tuple<none_t,int>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,3>;
        inline auto dslices = dslices_t{{None,2},{None,1},{None,2}};
        inline auto aslices = aslices_t{{{None,2},{None,1},{None,2}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2][1][2] = {
            {{0,1}},

            {{6,7}}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = nmtools_tuple{None,None};
        inline auto slice1 = nmtools_tuple{None,None};
        inline auto slice2 = nmtools_tuple{None,None};
        inline auto slices = nmtools_tuple{slice0,slice1,slice2};
        using slice_t  = nmtools_tuple<none_t,none_t>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,3>;
        inline auto dslices = dslices_t{slice0,slice1,slice2};
        inline auto aslices = aslices_t{slice0,slice1,slice2};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = nmtools_tuple{1,2};
        inline auto slice1 = nmtools_tuple{0,1};
        inline auto slice2 = nmtools_tuple{None,None};
        inline auto slices = nmtools_tuple{slice0,slice1,slice2};
        using slice_t  = nmtools_tuple<int,int>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,3>;
        inline auto dslices = dslices_t{{1,2},{0,1},{0,2}};
        inline auto aslices = aslices_t{{{1,2},{0,1},{0,2}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[1][1][2] = {{{6,7}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = nmtools_tuple{1,3};
        inline auto slice1 = nmtools_tuple{0,1};
        inline auto slice2 = nmtools_tuple{None,None};
        inline auto slices = nmtools_tuple{slice0,slice1,slice2};
        using slice_t  = nmtools_array<int,2>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,3>;
        inline auto dslices = dslices_t{{1,3},{0,1},{0,2}};
        inline auto aslices = aslices_t{{{1,3},{0,1},{0,2}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[1][1][2] = {{{6,7}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = nmtools_tuple{None,None};
        inline auto slice1 = nmtools_tuple{0,2};
        inline auto slice2 = nmtools_tuple{None,-1};
        inline auto slices = nmtools_tuple{slice0,slice1,slice2};
        using slice_t  = nmtools_tuple<none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto dslices = slices_t{{None,2},{None,2},{None,-1}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[2][2][1] = {
            {
                {0},
                {2},
            },
            {
                {6},
                {8},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = nmtools_tuple{None,None};
        inline auto slice1 = 0;
        inline auto slice2 = nmtools_tuple{None,-1};
        using slices_t = nmtools_tuple<decltype(slice0),decltype(slice1),decltype(slice2)>;
        inline auto slices = slices_t{slice0,slice1,slice2};
        using slice_t   = nmtools_either<decltype(slice0),nmtools_either<decltype(slice1),decltype(slice2)>>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,3>;
        inline auto dslices = dslices_t{slice0,slice1,slice2};
        inline auto aslices = aslices_t{slice0,slice1,slice2};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[2][1] = {
            {0},
            {6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = 1;
        inline auto slice1 = nmtools_tuple{0,2};
        inline auto slice2 = nmtools_tuple{None,-1};
        inline auto slices = nmtools_tuple{slice0,slice1,slice2};
        using slice_t   = nmtools_either<decltype(slice0),nmtools_either<decltype(slice1),decltype(slice2)>>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,3>;
        inline auto dslices = dslices_t{slice0,slice1,slice2};
        inline auto aslices = aslices_t{slice0,slice1,slice2};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[2][1] = {
            {6},
            {8},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = nmtools_tuple{None,None,-1};
        inline auto slice1 = nmtools_tuple{None,None};
        inline auto slice2 = nmtools_tuple{None,None};
        inline auto slices = nmtools_tuple{slice0,slice1,slice2};
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,3>;
        inline auto dslices = dslices_t{{None,None,-1},{None,None,1},{None,None,1}};
        inline auto aslices = aslices_t{{{None,None,-1},{None,None,1},{None,None,1}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[2][3][2] = {
            {
                {6,7},
                {8,9},
                {10,11},
            },
            {
                {0,1},
                {2,3},
                {4,5},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = nmtools_tuple{None,None};
        inline auto slice1 = nmtools_tuple{None,None,-1};
        inline auto slice2 = nmtools_tuple{None,None};
        inline auto slices = nmtools_tuple{slice0,slice1,slice2};
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,3>;
        inline auto dslices = dslices_t{{None,None,1},{None,None,-1},{None,None,1}};
        inline auto aslices = aslices_t{{{None,None,1},{None,None,-1},{None,None,1}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[2][3][2] = {
            {
                {4,5},
                {2,3},
                {0,1},
            },
            {
                {10,11},
                {8,9},
                {6,7},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = nmtools_tuple{None,None,-1};
        inline auto slice1 = nmtools_tuple{None,None};
        inline auto slice2 = nmtools_tuple{None,None,-1};
        inline auto slices = nmtools_tuple{slice0,slice1,slice2};
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,3>;
        inline auto dslices = dslices_t{{None,None,-1},{None,None,1},{None,None,-1}};
        inline auto aslices = aslices_t{{{None,None,-1},{None,None,1},{None,None,-1}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[2][3][2] = {
            {
                {7,6},
                {9,8},
                {11,10},
            },
            {
                {1,0},
                {3,2},
                {5,4},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = nmtools_tuple{None,None,2};
        inline auto slice1 = nmtools_tuple{None,None};
        inline auto slices = nmtools_tuple{slice0,slice1};
        using slice_t  = nmtools_tuple<none_t,none_t,size_t>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{{None,None,2},{None,None,1}};
        inline auto aslices = aslices_t{{{None,None,2},{None,None,1}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result[2][2] = {
            {0,1},
            {4,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = nmtools_tuple{None,None,2};
        inline auto slice1 = nmtools_tuple{None,2};
        inline auto slices = nmtools_tuple{slice0,slice1};
        using slice_t  = nmtools_tuple<none_t,int,int>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{{None,4,2},{None,2,1}};
        inline auto aslices = aslices_t{{{None,4,2},{None,2,1}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result[2][2] = {
            {0,1},
            {4,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = nmtools_tuple{None,None,2};
        inline auto slice1 = nmtools_tuple{1,None};
        inline auto slices = nmtools_tuple{slice0,slice1};
        using slice_t  = nmtools_tuple<int,none_t,size_t>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{{0,None,2},{1,None,1}};
        inline auto aslices = aslices_t{{{0,None,2},{1,None,1}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int result[2][1] = {
            {1},
            {5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = nmtools_tuple{None,None,2};
        inline auto slice1 = nmtools_tuple{1,None,2};
        inline auto slices = nmtools_tuple{slice0,slice1};
        using slice_t  = nmtools_tuple<size_t,none_t,int>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{{0,None,2},{1,None,2}};
        inline auto aslices = aslices_t{{{0,None,2},{1,None,2}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int result[2][1] = {
            {1},
            {5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = nmtools_tuple{None,None,-2};
        inline auto slice1 = nmtools_tuple{1,None,-2};
        inline auto slices = nmtools_tuple{slice0,slice1};
        using slice_t  = nmtools_tuple<size_t,none_t,int>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{{3,None,-2},{1,None,-2}};
        inline auto aslices = aslices_t{{{3,None,-2},{1,None,-2}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int result[2][1] = {
            {7},
            {3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = nmtools_tuple{3,None,-2};
        inline auto slice1 = nmtools_tuple{1,None,-2};
        inline auto slices = nmtools_tuple{slice0,slice1};
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{{None,None,-2},{None,None,-2}};
        inline auto aslices = aslices_t{{{None,None,-2},{None,None,-2}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline int result[2][1] = {
            {7},
            {3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = nmtools_tuple{3,None,2};
        inline auto slice1 = nmtools_tuple{1,None,-2};
        inline auto slices = nmtools_tuple{slice0,slice1};
        using slice_t  = nmtools_tuple<size_t,none_t,int>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{{3,None,2},{1,None,-2}};
        inline auto aslices = aslices_t{{{3,None,2},{1,None,-2}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline int result[1][1] = {{7}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = nmtools_tuple{1,None,-2};
        inline auto slice1 = nmtools_tuple{1,None,-2};
        inline auto slices = nmtools_tuple{slice0,slice1};
        using slice_t  = nmtools_tuple<int,none_t,int>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{{1,None,-2},{1,None,-2}};
        inline auto aslices = aslices_t{{{1,None,-2},{1,None,-2}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int result[1][1] = {{3}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = nmtools_tuple{2,None,-2};
        inline auto slice1 = nmtools_tuple{1,None,-2};
        inline auto slices = nmtools_tuple{slice0,slice1};
        using slice_t  = nmtools_tuple<int,none_t,int>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{{2,None,-2},{1,None,-2}};
        inline auto aslices = aslices_t{{{2,None,-2},{1,None,-2}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline int result[2][1] = {
            {5},
            {1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = nmtools_tuple{None,None};
        inline auto slice1 = nmtools_tuple{1,None,4};
        inline auto slices = nmtools_tuple{slice0,slice1};
        using slice_t  = nmtools_tuple<int,none_t,int>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{{0,None,1},{1,None,4}};
        inline auto aslices = aslices_t{{{0,None,1},{1,None,4}}};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline int result[4][1] = {
            {1},
            {3},
            {5},
            {7},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = Ellipsis;
        inline auto slice1 = nmtools_tuple{None,None};
        inline auto slices = nmtools_tuple{slice0,slice1};
        NMTOOLS_CAST_ARRAYS(array);
        using slice_t  = nmtools_either<ellipsis_t,nmtools_tuple<none_t,none_t>>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{slice0,slice1};
        inline auto aslices = aslices_t{{slice0,slice1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline int result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = Ellipsis;
        inline auto slice1 = nmtools_tuple{None,Last};
        inline auto slices = nmtools_tuple{slice0,slice1};
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<decltype(slice0),decltype(slice1)>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{slice0,slice1};
        inline auto aslices = aslices_t{{slice0,slice1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline int result[2][3][1] = {
            {
                {0},
                {2},
                {4},
            },
            {
                {6},
                {8},
                {10},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case23)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = Ellipsis;
        inline auto slice1 = nmtools_tuple{0,Last};
        inline auto slices = nmtools_tuple{slice0,slice1};
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<decltype(slice0),decltype(slice1)>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{slice0,slice1};
        inline auto aslices = aslices_t{{slice0,slice1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        inline int result[2][3][1] = {
            {
                {0},
                {2},
                {4},
            },
            {
                {6},
                {8},
                {10},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = nmtools_tuple{0ul,Last};
        inline auto slice1 = Ellipsis;
        inline auto slices = nmtools_tuple{slice0,slice1};
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<decltype(slice0),decltype(slice1)>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{slice0,slice1};
        inline auto aslices = aslices_t{{slice0,slice1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        inline int result[1][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case25)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = 0ul;
        inline auto slice1 = Ellipsis;
        inline auto slices = nmtools_tuple{slice0,slice1};
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<decltype(slice0),decltype(slice1)>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{slice0,slice1};
        inline auto aslices = aslices_t{{slice0,slice1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case25)
    {
        inline int result[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case26)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = Ellipsis;
        inline auto slice1 = 0;
        inline auto slices = nmtools_tuple{slice0,slice1};
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<decltype(slice0),decltype(slice1)>;
        using dslices_t = nmtools_list<slice_t>;
        using aslices_t = nmtools_array<slice_t,2>;
        inline auto dslices = dslices_t{slice0,slice1};
        inline auto aslices = aslices_t{{slice0,slice1}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case26)
    {
        inline int result[2][3] = {
            {0,2,4},
            {6,8,10},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case27)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = 0;
        inline auto slice1 = Ellipsis;
        inline auto slice2 = 0;
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<decltype(slice0),decltype(slice1)>;
        using slices_t = nmtools_list<slice_t>;
        inline auto dslices = slices_t{slice0,slice1,slice2};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case27)
    {
        inline int result[3] = {0,2,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case28)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = Ellipsis;
        inline auto slice1 = 0;
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<decltype(slice0),decltype(slice1)>;
        using slices_t = nmtools_list<slice_t>;
        inline auto dslices = slices_t{slice0,slice1};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case28)
    {
        inline int result[2][1][3] = {
            {
                {0,2,4}
            },
            {
                {6,8,10}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case29)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = Ellipsis;
        inline auto slice1 = 1;
        inline auto slice2 = 0;
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<decltype(slice0),decltype(slice1)>;
        using slices_t = nmtools_list<slice_t>;
        inline auto dslices = slices_t{slice0,slice1,slice2};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case29)
    {
        inline int result[2][1] = {
            {2},
            {8}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case30)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = 1;
        inline auto slice1 = Ellipsis;
        inline auto slice2 = 0;
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<decltype(slice0),decltype(slice1)>;
        using slices_t = nmtools_list<slice_t>;
        inline auto dslices = slices_t{slice0,slice1,slice2};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case30)
    {
        inline int result[1][3] = {
            {6,8,10}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case31)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = Ellipsis;
        inline auto slice1 = -1;
        inline auto slice2 = nmtools_tuple{None,None,-1};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case31)
    {
        inline int result[2][2] = {
            {5,4},
            {11,10},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case32)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = Ellipsis;
        inline auto slice1 = -2;
        inline auto slice2 = nmtools_tuple{None,None,-1};
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case32)
    {
        inline int result[2][2] = {
            {3,2},
            {9,8},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case33)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = 0;
        inline auto slice1 = Ellipsis;
        inline auto slice2 = -1;
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<decltype(slice0),decltype(slice1)>;
        using slices_t = nmtools_list<slice_t>;
        inline auto dslices = slices_t{slice0,slice1,slice2};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case33)
    {
        inline int result[3] = {1,3,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case34)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = Ellipsis;
        inline auto slice1 = -1;
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<decltype(slice0),decltype(slice1)>;
        using slices_t = nmtools_list<slice_t>;
        inline auto dslices = slices_t{slice0,slice1};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case34)
    {
        inline int result[2][1][3] = {
            {
                {1,3,5},
            },
            {
                {7,9,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case35)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = Ellipsis;
        inline auto slice1 = -1;
        inline auto slice2 = 0;
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<decltype(slice0),decltype(slice1)>;
        using slices_t = nmtools_list<slice_t>;
        inline auto dslices = slices_t{slice0,slice1,slice2};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case35)
    {
        inline int result[2][1] = {
            {4},
            {10},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case36)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = -1;
        inline auto slice1 = Ellipsis;
        inline auto slice2 = 0;
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<decltype(slice0),decltype(slice1)>;
        using slices_t = nmtools_list<slice_t>;
        inline auto dslices = slices_t{slice0,slice1,slice2};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case36)
    {
        inline int result[1][3] = {
            {6,8,10}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case37)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = 1;
        inline auto slice1 = Ellipsis;
        inline auto slice2 = nmtools_tuple{None,None,-1};
        inline auto slice3 = 0;
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<int,nmtools_either<ellipsis_t,nmtools_tuple<none_t,none_t,int>>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto dslices = slices_t{slice0,slice1,slice2,slice3};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case37)
    {
        inline int result[1][3] = {
            {10,8,6}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case38)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = 1;
        inline auto slice1 = Ellipsis;
        inline auto slice2 = nmtools_tuple{None,None,1};
        inline auto slice3 = 1;
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<int,nmtools_either<ellipsis_t,nmtools_tuple<none_t,none_t,int>>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto dslices = slices_t{slice0,slice1,slice2,slice3};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case38)
    {
        inline int result[1][3] = {
            {7,9,11}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case39)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = 1;
        inline auto slice1 = Ellipsis;
        inline auto slice2 = nmtools_array{2,0,-1};
        inline auto slice3 = 0;
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<int,nmtools_either<ellipsis_t,nmtools_array<int,3>>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto dslices = slices_t{slice0,slice1,slice2,slice3};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case39)
    {
        inline int result[1][2] = {
            {10,8}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case40)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = 1;
        inline auto slice1 = Ellipsis;
        inline auto slice2 = nmtools_array{0,2,1};
        inline auto slice3 = 0;
        NMTOOLS_CAST_ARRAYS(array)
        using slice_t  = nmtools_either<int,nmtools_either<ellipsis_t,nmtools_array<int,3>>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto dslices = slices_t{slice0,slice1,slice2,slice3};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case40)
    {
        inline int result[1][2] = {
            {6,8}
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_SLICE_HPP