#ifndef NMTOOLS_TESTING_DATA_ARRAY_MEAN_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_MEAN_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(array, mean)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto shape  = None;
        inline auto result = 5.5f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 0;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t shape[2] = {3,2};
        inline int8_t result[3][2] = {
            {3,4},
            {5,6},
            {7,8}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int8_t shape[2] = {2,2};
        inline int8_t result[2][2] = {
            {2,3},
            {8,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int8_t shape[2] = {2,3};
        inline float result[2][3] = {
            {0.5f,2.5f, 4.5f},
            {6.5f,8.5f,10.5f}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        using namespace literals;
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int8_t shape[2] = {3,2};
        inline int8_t result[3][2] = {
            {3,4},
            {5,6},
            {7,8}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = None;
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int8_t shape[3] = {1,1,1};
        inline float result[1][1][1] = {{{5.5f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = None;
        inline auto keepdims = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int8_t shape[3] = {1,1,1};
        inline float result[1][1][1] = {{{5.5f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = None;
        inline auto keepdims = false;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline auto shape = None;
        inline float result = 5.5f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 0;
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int8_t shape[3] = {1,3,2};
        inline int8_t result[1][3][2] = {
            {
                {3,4},
                {5,6},
                {7,8},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 1;
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int8_t shape[3] = {2,1,2};
        inline int8_t result[2][1][2] = {
            {
                {2,3},
            },
            {
                {8,9},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 2;
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int8_t shape[3] = {2,3,1};
        inline float result[2][3][1] = {
            {
                {0.5f},
                {2.5f},
                { 4.5f}
            },
            {
                {6.5f},
                {8.5f},
                {10.5f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        using namespace literals;
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 0_ct;
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int8_t shape[3] = {1,3,2};
        inline int8_t result[1][3][2] = {
            {
                {3,4},
                {5,6},
                {7,8}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 0;
        inline auto keepdims = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int8_t shape[3] = {1,3,2};
        inline int8_t result[1][3][2] = {
            {
                {3,4},
                {5,6},
                {7,8},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 1;
        inline auto keepdims = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int8_t shape[3] = {2,1,2};
        inline int8_t result[2][1][2] = {
            {
                {2,3},
            },
            {
                {8,9},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 2;
        inline auto keepdims = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int8_t shape[3] = {2,3,1};
        inline float result[2][3][1] = {
            {
                {0.5f},
                {2.5f},
                { 4.5f}
            },
            {
                {6.5f},
                {8.5f},
                {10.5f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        using namespace literals;
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 0_ct;
        inline auto keepdims = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline int8_t shape[3] = {1,3,2};
        inline int8_t result[1][3][2] = {
            {
                {3,4},
                {5,6},
                {7,8}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 0;
        inline auto keepdims = false;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline int8_t shape[2] = {3,2};
        inline int8_t result[3][2] = {
            {3,4},
            {5,6},
            {7,8}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 1;
        inline auto keepdims = false;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int8_t shape[2] = {2,2};
        inline int8_t result[2][2] = {
            {2,3},
            {8,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 2;
        inline auto keepdims = false;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline int8_t shape[2] = {2,3};
        inline float result[2][3] = {
            {0.5f,2.5f, 4.5f},
            {6.5f,8.5f,10.5f}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        using namespace literals;
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = 0_ct;
        inline auto keepdims = false;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline int8_t shape[2] = {3,2};
        inline int8_t result[3][2] = {
            {3,4},
            {5,6},
            {7,8}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = nmtools_array{0,1};
        inline auto keepdims = False;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline int8_t shape[1] = {2};
        inline float result[2] = {5.f, 6.f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = nmtools_array{0,2};
        inline auto keepdims = False;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline int8_t shape[1] = {3};
        inline float result[3] = {3.5f, 5.5f, 7.5f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case23)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = nmtools_array{1,2};
        inline auto keepdims = False;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        inline int8_t shape[1] = {2};
        inline float result[2] = {2.5f, 8.5f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = nmtools_array{0,1};
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        inline int8_t shape[3] = {1,1,2};
        inline float result[1][1][2] = {{{5.f, 6.f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case25)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = nmtools_array{0,2};
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case25)
    {
        inline int8_t shape[3] = {1,3,1};
        inline float result[1][3][1] = {{{3.5f}, {5.5f}, {7.5f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case26)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = nmtools_array{1,2};
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case26)
    {
        inline int8_t shape[3] = {2,1,1};
        inline float result[2][1][1] = {{{2.5f}}, {{8.5f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case27)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = nmtools_array{0,1};
        inline auto keepdims = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case27)
    {
        inline int8_t shape[3] = {1,1,2};
        inline float result[1][1][2] = {{{5.f, 6.f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case28)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = nmtools_array{0,2};
        inline auto keepdims = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case28)
    {
        inline int8_t shape[3] = {1,3,1};
        inline float result[1][3][1] = {{{3.5f}, {5.5f}, {7.5f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case29)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = nmtools_array{1,2};
        inline auto keepdims = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case29)
    {
        inline int8_t shape[3] = {2,1,1};
        inline float result[2][1][1] = {{{2.5f}}, {{8.5f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case30)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = nmtools_array{0,1};
        inline auto keepdims = false;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case30)
    {
        inline int8_t shape[1] = {2};
        inline float result[2] = {5.f, 6.f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case31)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = nmtools_array{0,2};
        inline auto keepdims = false;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case31)
    {
        inline int8_t shape[1] = {3};
        inline float result[3] = {3.5f, 5.5f, 7.5f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case32)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = nmtools_array{1,2};
        inline auto keepdims = false;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case32)
    {
        inline int8_t shape[1] = {2};
        inline float result[2] = {2.5f, 8.5f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case33)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = -1;
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case33)
    {
        inline int shape[3] = {2,3,1};
        inline float result[2][3][1] = {
            {
                {0.5},
                {2.5},
                {4.5},
            },
            {
                { 6.5},
                { 8.5},
                {10.5},
            }
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(array, constexpr_mean)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a)
        constexpr inline auto axis = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto shape  = None;
        constexpr inline auto result = 5.5f;
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_MEAN_HPP